#ifndef _PWN_ERROR_
#define _PWN_ERROR_

#include <stdarg.h>
/*
 * error handling
 */
void pwnStandardError(const char *msg);

void pwnCustomError(const char *const message, ...);


#endif