#ifndef _PWN_RECV_FORMAT_
#define _PWN_RECV_FORMAT_

#include "PwnIO.h"
#include <stdarg.h>
/*
 * ptRecvf workhorse
 */
uint64_t pwnRecvFormat(const PIO *const pio, const char *const formatString, va_list parameters);


#endif