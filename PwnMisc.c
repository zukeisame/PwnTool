#include "PwnMisc.h"
#include "PwnError.h"
#include <ctype.h>
#include <stdio.h>
#include <time.h>
/*
 * PUBLIC =========================================================================================
 */
void pwnSleep(const unsigned long microseonds) {
	struct timespec interval;
	interval.tv_sec = microseonds / 1000lu;
	interval.tv_nsec = (microseonds % 1000lu) * 1000000lu;

	if (nanosleep(&interval, NULL) < 0) {
		pwnStandardError("nanosleep()");
	}
}

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