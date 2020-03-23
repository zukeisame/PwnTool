#ifndef _PWN_RECV_
#define _PWN_RECV_

#include "PwnIO.h"
#include <stdarg.h>
/*
 * recv functions
 */
void pwnDiscardAll(const PIO *const pio, va_list parameters);

void pwnDiscardUntil(const PIO *const pio, va_list parameters);

void pwnPrintAll(const PIO *const pio, va_list parameters);



#endif