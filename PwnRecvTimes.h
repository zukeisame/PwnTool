#ifndef _PWN_RECV_TIMES_
#define _PWN_RECV_TIMES_

#include "PwnIO.h"
#include <stdarg.h>
#include <stdint.h>
/*
 * recv functions
 */
uint64_t pwnDiscardTimes(const PIO *const pio, va_list parameters, const uint64_t times);

uint64_t pwnPrintTimes(const PIO *const pio, va_list parameters, const uint64_t times);

uint64_t pwnRecvFourBytes(const PIO *const pio, va_list parameters, const uint64_t times);

uint64_t pwnRecvEightBytes(const PIO *const pio, va_list parameters, const uint64_t times);

uint64_t pwnRecvByteTimes(const PIO *const pio, va_list parameters, const uint64_t times);

uint64_t pwnRecvLineTimes(const PIO *const pio, va_list parameters, const uint64_t times);


#endif