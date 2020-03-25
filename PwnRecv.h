#ifndef _PWN_RECV_
#define _PWN_RECV_

#include "PwnIO.h"
#include <stdarg.h>
#include <stdint.h>
/*
 * recv functions
 */
uint64_t pwnDiscardAll(const PIO *const pio, va_list parameters);

uint64_t pwnDiscardUntil(const PIO *const pio, va_list parameters);

uint64_t pwnPrintAll(const PIO *const pio, va_list parameters);



#endif