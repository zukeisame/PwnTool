#include "PwnRecvFormat.h"
#include "PwnRecvTimes.h"
#include "PwnError.h"
#include "PwnRecv.h"
#include "PwnMisc.h"
#include <stdio.h>
/*
 * PRIVATE ========================================================================================
 */
void (*pwnRecvFunctionTable(const char c))(const PIO *const, va_list) {
	switch (c) {
	case 'J': return pwnDiscardAll;
	case 'S': return pwnDiscardUntil;
	case 'P': return pwnPrintAll;
	default: pwnCustomError("pwnRecvFormat(): invalid format string");
	}
}

void (*pwnRecvTimesFunctionTable(const char c))(const PIO *const, va_list, const uint64_t) {
	switch (c) {
	case 'J': return pwnDiscardTimes;
	case 'P': return pwnPrintTimes;
	case 'a': return pwnRecvFourBytes;
	case 'A': return pwnRecvEightBytes;
	default: pwnCustomError("pwnRecvFormat(): invalid format string");
	}
}

void pwnRecvFormatWorkhorse(const PIO *const pio, const char **const format, va_list parameters) {
	const char *ptr = *format;

	char specifier;
	uint64_t times;
	if (sscanf(ptr, "%%%lu%c", &times, &specifier) == 2) {
		pwnRecvTimesFunctionTable(specifier)(pio, parameters, times);
	} else if (sscanf(ptr, "%%%c", &specifier) == 1) {
		pwnRecvFunctionTable(specifier)(pio, parameters);
	} else {
		pwnCustomError("pwnRecvFormat(): invalid format string");
	}

	*format = pwnGetStringAfter(ptr, specifier);
}
/*
 * PUBLIC =========================================================================================
 */
void pwnRecvFormat(const PIO *const pio, const char *const formatString, va_list parameters) {
	const char *ptr = formatString;

	while ((*ptr) != '\0') {
		if ((*ptr) == '%') {
			pwnRecvFormatWorkhorse(pio, &ptr, parameters);
		} else {
			pwnCustomError("pwnRecvFormat(): invalid format string");
		}
	}
}