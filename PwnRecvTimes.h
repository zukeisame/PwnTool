#ifndef _PWN_RECV_TIMES_
#define _PWN_RECV_TIMES_

#include "PwnIO.h"
#include <stdarg.h>
#include <stdint.h>
/*
 * recv functions
 */
void pwnDiscardTimes(const PIO *const pio, va_list parameters, const uint64_t times);

void pwnPrintTimes(const PIO *const pio, va_list parameters, const uint64_t times);

void pwnRecvFourBytes(const PIO *const pio, va_list parameters, const uint64_t times);

void pwnRecvEightBytes(const PIO *const pio, va_list parameters, const uint64_t times);


#endif