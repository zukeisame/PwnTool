#include "PwnSend.h"
#include "PwnDef.h"
#include "PwnError.h"
#include <string.h>
#include <stdio.h>
/*
 * PRIVATE ========================================================================================
 */
/*
 * PUBLIC =========================================================================================
 */
uint64_t pwnSendByte(const PIO *const pio, va_list parameters) {
	const Byte byte = (Byte) va_arg(parameters, int);

	pioSend(pio, &byte, sizeof(byte));

	return sizeof(byte);
}

uint64_t pwnSendString(const PIO *const pio, va_list parameters) {
	const char *const string = va_arg(parameters, const char*);

	const uint64_t length = strlen(string);
	pioSend(pio, string, length);

	return length;
}

uint64_t pwnSendSignedInteger(const PIO *const pio, va_list parameters) {
	const int64_t number = va_arg(parameters, int64_t);

	char buffer[32];
	sprintf(buffer, "%ld", number);
	const uint64_t length = strlen(buffer);
	pioSend(pio, buffer, length);

	return length;
}

uint64_t pwnSendUnsignedInteger(const PIO *const pio, va_list parameters) {
	const uint64_t number = va_arg(parameters, uint64_t);

	char buffer[32];
	sprintf(buffer, "%lu", number);
	const uint64_t length = strlen(buffer);
	pioSend(pio, buffer, length);

	return length;
}

uint64_t pwnSendFourBytes(const PIO *const pio, va_list parameters) {
	const FourBytes fourBytes = va_arg(parameters, FourBytes);

	pioSend(pio, &fourBytes, sizeof(fourBytes));

	return sizeof(fourBytes);
}

uint64_t pwnSendEightBytes(const PIO *const pio, va_list parameters) {
	const EightBytes eightBytes = va_arg(parameters, EightBytes);

	pioSend(pio, &eightBytes, sizeof(eightBytes));

	return sizeof(eightBytes);
}

uint64_t pwnSendFile(const PIO *const pio, va_list parameters) {
	const char *const filename = va_arg(parameters, const char*);

	FILE *const fin = fopen(filename, "r");
	if (fin == NULL) {
		pwnStandardError("fopen()");
	}

	Byte byte;
	int returnValue;
	uint64_t sendCount = 0;
	while ((returnValue = fgetc(fin)) != EOF) {
		byte = (Byte) returnValue;
		pioSend(pio, &byte, sizeof(byte));
		++sendCount;
	}

	if (fclose(fin) < 0) {
		pwnStandardError("fclose()");
	}

	return sendCount;
}

uint64_t pwnSendFourBytesROPChain(const PIO *const pio, va_list parameters) {
	uint64_t sendCount = 0;

	FourBytes fourBytes = va_arg(parameters, FourBytes); // read first
	while (fourBytes != PWN_END_OF_FOUR_BYTES) {
		pioSend(pio, &fourBytes, sizeof(fourBytes));
		++sendCount;
		fourBytes = va_arg(parameters, FourBytes); // read next
	}

	return sendCount * sizeof(fourBytes);
}

uint64_t pwnSendEightBytesROPChain(const PIO *const pio, va_list parameters) {
	uint64_t sendCount = 0;

	EightBytes eightBytes = va_arg(parameters, EightBytes); // read first
	while (eightBytes != PWN_END_OF_EIGHT_BYTES) {
		pioSend(pio, &eightBytes, sizeof(eightBytes));
		++sendCount;
		eightBytes = va_arg(parameters, EightBytes); // read next
	}

	return sendCount * sizeof(eightBytes);
}