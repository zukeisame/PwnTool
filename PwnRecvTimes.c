#include "PwnRecvTimes.h"
#include "PwnError.h"
#include "PwnMisc.h"
#include "PwnDef.h"
/*
 * PRIVATE ========================================================================================
 */

/*
 * PUBLIC =========================================================================================
 */
 void pwnDiscardTimes(const PIO *const pio, va_list parameters, const uint64_t times) {
	const int recvFD = pioGetRecvFD(pio);

	Byte byte;
	for (uint64_t i = 0; i < times; ++i) {
		if (pioRecv(pio, &byte, sizeof(byte)) != sizeof(byte)) {
			pwnStandardError("pwnDiscardTimes()");
		}
	}
}

void pwnPrintTimes(const PIO *const pio, va_list parameters, const uint64_t times) {
	const int recvFD = pioGetRecvFD(pio);

	Byte byte;
	for (uint64_t i = 0; i < times; ++i) {
		if (pioRecv(pio, &byte, sizeof(byte)) != sizeof(byte)) {
			pwnStandardError("pwnDumpTimes()");
		}
		pwnPrintByte(i, byte);
	}
}

void pwnRecvFourBytes(const PIO *const pio, va_list parameters, const uint64_t times) {
	if (times > sizeof(FourBytes)) {
		pwnStandardError("pwnRecvFourBytes(): invalid format string");
	}

	Byte *ptr = (Byte*) va_arg(parameters, FourBytes*);
	for (uint32_t i = 0; i < times; ++i) {
		if (pioRecv(pio, ptr + i, sizeof(*ptr)) != sizeof(*ptr)) {
			pwnStandardError("pwnRecvFourBytes()");
		}
	}
}

void pwnRecvEightBytes(const PIO *const pio, va_list parameters, const uint64_t times) {
	if (times > sizeof(EightBytes)) {
		pwnStandardError("pwnRecvEightBytes(): invalid format string");
	}

	Byte *ptr = (Byte*) va_arg(parameters, EightBytes*);
	for (uint32_t i = 0; i < times; ++i) {
		if (pioRecv(pio, ptr + i, sizeof(*ptr)) != sizeof(*ptr)) {
			pwnStandardError("pwnRecvEightBytes()");
		}
	}
}