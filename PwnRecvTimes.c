#include "PwnRecvTimes.h"
#include "PwnFcntl.h"
#include "PwnError.h"
#include "PwnMisc.h"
#include "PwnDef.h"
/*
 * PRIVATE ========================================================================================
 */

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
		pwnStandardError("pwnRecvFourBytes(): invalid format string");
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
		pwnStandardError("pwnRecvEightBytes(): invalid format string");
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
	char *const ptr = va_arg(parameters, char*);

	pwnNonBlockFD(pioGetRecvFD(pio));
	uint64_t i;
	for (i = 0; i < times; ++i) {
		if (pioRecv(pio, ptr + i, sizeof(char)) != sizeof(char)) {
			break;
		}
	}
	pwnBlockFD(pioGetRecvFD(pio));

	*(ptr + i) = '\0'; // end buffer
	return i;
}

uint64_t pwnRecvLineTimes(const PIO *const pio, va_list parameters, const uint64_t times) {
	char *const ptr = va_arg(parameters, char*);

	uint64_t i;
	for (i = 0; i < times; ++i) {
		if (pioRecv(pio, ptr + i, sizeof(char)) != sizeof(char)) {
			pwnStandardError("pwnRecvLineTimes()");
		} else if (*(ptr + i) == '\n') {
			break;
		}
	}

	*(ptr + i) = '\0'; // end buffer
	return i;
}