#ifndef _PWN_IO_LOCAL_
#define _PWN_IO_LOCAL_

#include <stdint.h>
/*
 * local io
 */
typedef struct PwnIOLocal PIOLocal;

void* piolOpen(const char *const program);

void piolClose(void *const piol);

int piolGetSendFD(const void *const piol);

int piolGetRecvFD(const void *const piol);

int64_t piolSend(const void *const piol, const void *const buffer, const uint64_t size);

int64_t piolRecv(const void *const piol, void *const buffer, const uint64_t size);

#endif