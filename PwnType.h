#ifndef _PWN_TYPE_
#define _PWN_TYPE_

#include <stdint.h>
#include <stdarg.h>
/*
 * pwn type!!!
 */
typedef struct PwnType PT;

PT* ptLocal(const char *const program);

PT* ptRemote(const char *const domainName, const uint16_t port);

void ptClose(PT *const pt);

uint64_t ptSendf(const PT *const pt, const char *const format, ...);

void ptRecvf(const PT *const pt, const char *const format, ...);

void ptFlush(const PT *const pt);

void ptShell(const PT *const pt);


#endif