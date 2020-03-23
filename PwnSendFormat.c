#include "PwnSendFormat.h"
#include "PwnSendTimes.h"
#include "PwnError.h"
#include "PwnSend.h"
#include "PwnMisc.h"
#include <string.h>
#include <stdio.h>
/*
 * PRIVATE ========================================================================================
 */
uint64_t (*pwnSendFunctionTable(const char placeholder))(const PIO *const, va_list) {
	switch (placeholder) {
	case 'C': return pwnSendByte;
	case 'S': return pwnSendString;
	case 'D': return pwnSendSignedInteger;
	case 'U': return pwnSendUnsignedInteger;
	case 'a': return pwnSendFourBytes;
	case 'A': return pwnSendEightBytes;
	case 'F': return pwnSendFile;
	case 'r': return pwnSendFourBytesROPChain;
	case 'R': return pwnSendEightBytesROPChain;
	default: pwnCustomError("pwnSendFormat(): invalid format string");
	}
}

uint64_t (*pwnSendTimesFunctionTable(const char placeholder))(const PIO *const, va_list, const uint64_t) {
	switch(placeholder) {
	case 'C': return pwnSendByteTimes;
	case 'a': return pwnSendFourBytesTimes;
	case 'A': return pwnSendEightBytesTimes;
	default: pwnCustomError("pwnSendFormat(): invalid format string");
	}
}

uint64_t pwnSendFormatWorkhorse(const PIO *const pio, const char **const format, va_list parameters) {
	const char *const ptr = *format;

	char specifier;
	uint64_t times, sendCount = 0;
	if (sscanf(ptr, "%%%lu%c", &times, &specifier) == 2) {
		sendCount = pwnSendTimesFunctionTable(specifier)(pio, parameters, times);
	} else if (sscanf(ptr, "%%%c", &specifier) == 1) {
		sendCount = pwnSendFunctionTable(specifier)(pio, parameters);
	} else {
		pwnCustomError("pwnSendFormat(): invalid format string");
	}

	*format = pwnGetStringAfter(ptr, specifier);

	return sendCount;
}
/*
 * PUBLIC =========================================================================================
 */
uint64_t pwnSendFormat(const PIO *const pio, const char *const formatString, va_list parameters) {
	const char *ptr = formatString;

	uint64_t sendBytes = 0;
	while ((*ptr) != '\0') {
		if (strncmp(ptr, "%%", 2) == 0) {
			pioSend(pio, ptr, sizeof(*ptr));
			sendBytes += sizeof(*ptr);
			ptr += 2;
		} else if ((*ptr) == '%') {
			sendBytes += pwnSendFormatWorkhorse(pio, &ptr, parameters);
		} else {
			pioSend(pio, ptr, sizeof(*ptr));
			sendBytes += sizeof(*ptr);
			++ptr;
		}
	}

	return sendBytes;
}