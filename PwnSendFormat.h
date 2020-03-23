#ifndef _PWN_SEND_FORMAT_
#define _PWN_SEND_FORMAT_

#include <stdint.h>
#include <stdarg.h>
#include "PwnIO.h"
/* 
 * sendf workhorses
 */
uint64_t pwnSendFormat(const PIO *const pio, const char *const formatString, va_list parameters);


#endif