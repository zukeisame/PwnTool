#ifndef _PWN_SEND_
#define _PWN_SEND_

#include "PwnIO.h"
#include <stdint.h>
#include <stdarg.h>
/*
 * send functions
 */
uint64_t pwnSendByte(const PIO *const pio, va_list parameters);

uint64_t pwnSendString(const PIO *const pio, va_list parameters);

uint64_t pwnSendSignedInteger(const PIO *const pio, va_list parameters);

uint64_t pwnSendUnsignedInteger(const PIO *const pio, va_list parameters);

uint64_t pwnSendFourBytes(const PIO *const pio, va_list parameters);

uint64_t pwnSendEightBytes(const PIO *const pio, va_list parameters);

uint64_t pwnSendFile(const PIO *const pio, va_list parameters);

uint64_t pwnSendFourBytesROPChain(const PIO *const pio, va_list parameters);

uint64_t pwnSendEightBytesROPChain(const PIO *const pio, va_list parameters);


#endif