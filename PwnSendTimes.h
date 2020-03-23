#ifndef _PWN_SEND_TIMES_
#define _PWN_SEND_TIMES_

#include "PwnIO.h"
#include <stdint.h>
#include <stdarg.h>
/*
 * send functions
 */
uint64_t pwnSendByteTimes(const PIO *const pio, va_list parameters, const uint64_t times);

uint64_t pwnSendFourBytesTimes(const PIO *const pio, va_list parameters, const uint64_t times);

uint64_t pwnSendEightBytesTimes(const PIO *const pio, va_list parameters, const uint64_t times);


#endif