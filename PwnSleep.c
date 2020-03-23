#include "PwnSleep.h"
#include "PwnError.h"
#include <time.h>


void pwnSleep(const unsigned long microseonds) {
	struct timespec interval;
	interval.tv_sec = microseonds / 1000lu;
	interval.tv_nsec = (microseonds % 1000lu) * 1000000lu;

	if (nanosleep(&interval, NULL) < 0) {
		pwnStandardError("nanosleep()");
	}
}