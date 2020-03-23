#include "PwnMisc.h"
#include <ctype.h>
#include <stdio.h>
/*
 * PUBLIC =========================================================================================
 */
void pwnPrintByte(const uint64_t index, const Byte byte) {
	if (isprint(byte)) {
		printf("%8ld: \'\\x%02x\' (\'%c\')\n", index, byte & 0xff, byte);
	} else {
		printf("%8ld: \'\\x%02x\'\n", index, byte & 0xff);
	}
}

const char* pwnGetStringAfter(const char *const current, const char c) {
	const char *ptr = current;

	while((*ptr) != c) {
		++ptr;
	}

	return ++ptr;
}