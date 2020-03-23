#include "PwnError.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


void pwnStandardError(const char *msg) {
	perror(msg);
	exit(1);
}

void pwnCustomError(const char *const message, ...) {
	va_list argv;
	fprintf(stderr, "[!] Fatal: ");
	va_start(argv, message);
	vfprintf(stderr, message, argv);
	va_end(argv);
	fprintf(stderr, "\n");
	exit(1);
}