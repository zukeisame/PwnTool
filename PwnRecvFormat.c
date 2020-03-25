#include "PwnRecvFormat.h"
#include "PwnRecvTimes.h"
#include "PwnError.h"
#include "PwnRecv.h"
#include "PwnMisc.h"
#include <stdio.h>
/*
 * PRIVATE ========================================================================================
 */
uint64_t (*pwnRecvFunctionTable(const char c))(const PIO *const, va_list) {
	switch (c) {
	case 'J': return pwnDiscardAll;
	case 'S': return pwnDiscardUntil;
	case 'P': return pwnPrintAll;
	default: pwnCustomError("pwnRecvFormat(): invalid format string");
	}
}

uint64_t (*pwnRecvTimesFunctionTable(const char c))(const PIO *const, va_list, const uint64_t) {
	switch (c) {
	case 'J': return pwnDiscardTimes;
	case 'P': return pwnPrintTimes;
	case 'a': return pwnRecvFourBytes;
	case 'A': return pwnRecvEightBytes;
	case 'C': return pwnRecvByteTimes;
	case 'L': return pwnRecvLineTimes;
	default: pwnCustomError("pwnRecvFormat(): invalid format string");
	}
}

uint64_t pwnRecvFormatWorkhorse(const PIO *const pio, const char **const format, va_list parameters) {
	const char *ptr = *format;

	char specifier;
	uint64_t times, recvdBytes = 0;
	if (sscanf(ptr, "%%%lu%c", &times, &specifier) == 2) {
		recvdBytes = pwnRecvTimesFunctionTable(specifier)(pio, parameters, times);
	} else if (sscanf(ptr, "%%%c", &specifier) == 1) {
		recvdBytes = pwnRecvFunctionTable(specifier)(pio, parameters);
	} else {
		pwnCustomError("pwnRecvFormat(): invalid format string");
	}

	*format = pwnGetStringAfter(ptr, specifier);
	return recvdBytes;
}
/*
 * PUBLIC =========================================================================================
 */
uint64_t pwnRecvFormat(const PIO *const pio, const char *const formatString, va_list parameters) {
	const char *ptr = formatString;
	uint64_t recvdBytes = 0;

	while ((*ptr) != '\0') {
		if ((*ptr) == '%') {
			recvdBytes += pwnRecvFormatWorkhorse(pio, &ptr, parameters);
		} else {
			pwnCustomError("pwnRecvFormat(): invalid format string");
		}
	}

	return recvdBytes;
}