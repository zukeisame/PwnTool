#include "PwnRecv.h"
#include "PwnMisc.h"
#include "PwnError.h"
#include "PwnFcntl.h"
#include <stdio.h>
#include <string.h>
/*
 * PRIVATE ========================================================================================
 */

/*
 * PUBLIC =========================================================================================
 */
uint64_t pwnDiscardAll(const PIO *const pio, va_list parameters) {
	const int recvFD = pioGetRecvFD(pio);

	pwnNonBlockFD(recvFD);

	Byte byte;
	uint64_t recvdBytes = 0;
	while (pioRecv(pio, &byte, 1) == sizeof(byte)){
		++recvdBytes;
	}

	pwnBlockFD(recvFD);

	return recvdBytes;
}

uint64_t pwnDiscardUntil(const PIO *const pio, va_list parameters) {
	const char *const pattern = va_arg(parameters, const char*);

	Byte byte;
	uint64_t i = 0, recvdBytes = 0;
	const uint64_t length = strlen(pattern);

	while (i != length) {
		if (pioRecv(pio, &byte, sizeof(byte)) != sizeof(byte)) {
			pwnStandardError("pwnDiscardUntil()");
		} else {
			++recvdBytes;
		}

		if (pattern[i] == byte) {
			if ((++i) == length) {
				return recvdBytes;
			}
		} else {
			i = 0;
		}
	}
}

uint64_t pwnPrintAll(const PIO *const pio, va_list parameters) {
	const int recvFD = pioGetRecvFD(pio);

	Byte byte;
	uint64_t index = 0;
	if (pioRecv(pio, &byte, sizeof(byte)) == sizeof(byte)) { // wait for first byte
		pwnPrintByte(index++, byte);
		// read remainders
		pwnNonBlockFD(recvFD);
		while (pioRecv(pio, &byte, sizeof(byte)) == sizeof(byte)) {
			pwnPrintByte(index++, byte);
		}
		pwnBlockFD(recvFD);
	}

	return index;
}