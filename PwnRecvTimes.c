#include "PwnRecvTimes.h"
#include "PwnFcntl.h"
#include "PwnError.h"
#include "PwnMisc.h"
#include "PwnDef.h"
/*
 * PRIVATE ========================================================================================
 */
// #include <signal.h>
/*
 * PUBLIC =========================================================================================
 */
 uint64_t pwnDiscardTimes(const PIO *const pio, va_list parameters, const uint64_t times) {
	const int recvFD = pioGetRecvFD(pio);

	Byte byte;
	for (uint64_t i = 0; i < times; ++i) {
		if (pioRecv(pio, &byte, sizeof(byte)) != sizeof(byte)) {
			pwnStandardError("pwnDiscardTimes()");
		}
	}

	return times;
}

uint64_t pwnPrintTimes(const PIO *const pio, va_list parameters, const uint64_t times) {
	const int recvFD = pioGetRecvFD(pio);

	Byte byte;
	for (uint64_t i = 0; i < times; ++i) {
		if (pioRecv(pio, &byte, sizeof(byte)) != sizeof(byte)) {
			pwnStandardError("pwnDumpTimes()");
		}
		pwnPrintByte(i, byte);
	}

	return times;
}

uint64_t pwnRecvFourBytes(const PIO *const pio, va_list parameters, const uint64_t times) {
	if (times > sizeof(FourBytes)) {
		pwnCustomError("pwnRecvFourBytes(): invalid format string");
	}

	Byte *ptr = (Byte*) va_arg(parameters, FourBytes*);
	for (uint32_t i = 0; i < times; ++i) {
		if (pioRecv(pio, ptr + i, sizeof(*ptr)) != sizeof(*ptr)) {
			pwnStandardError("pwnRecvFourBytes()");
		}
	}

	return times;
}

uint64_t pwnRecvEightBytes(const PIO *const pio, va_list parameters, const uint64_t times) {
	if (times > sizeof(EightBytes)) {
		pwnCustomError("pwnRecvEightBytes(): invalid format string");
	}

	Byte *ptr = (Byte*) va_arg(parameters, EightBytes*);
	for (uint32_t i = 0; i < times; ++i) {
		if (pioRecv(pio, ptr + i, sizeof(*ptr)) != sizeof(*ptr)) {
			pwnStandardError("pwnRecvEightBytes()");
		}
	}

	return times;
}

uint64_t pwnRecvByteTimes(const PIO *const pio, va_list parameters, const uint64_t times) {
	if (times == 0) {
		return 0;
	}
	char *const ptr = va_arg(parameters, char*);

	if (pioRecv(pio, ptr, sizeof(char)) != sizeof(char)) { // recv first byte
		pwnStandardError("pwnRecvByteTimes()");
	}

	pwnNonBlockFD(pioGetRecvFD(pio)); // recv remaining bytes
	uint64_t i = 1;
	for (; i < times - 1; ++i) {
		if (pioRecv(pio, ptr + i, sizeof(char)) != sizeof(char)) {
			break;
		}
	}
	pwnBlockFD(pioGetRecvFD(pio));

	*(ptr + i) = '\0'; // end buffer
	return i;
}

uint64_t pwnRecvLineTimes(const PIO *const pio, va_list parameters, const uint64_t times) {
	if (times == 0) {
		return 0;
	}
	char *const ptr = va_arg(parameters, char*);

	uint64_t i;
	for (i = 0; i < times - 1; ++i) {
		if (pioRecv(pio, ptr + i, sizeof(char)) != sizeof(char)) {
			pwnStandardError("pwnRecvLineTimes()");
			/* raise(SIGUSR1);
			break;*/
		} else if (*(ptr + i) == '\n') {
			break;
		}
	}

	*(ptr + i) = '\0'; // end buffer
	return i;
}