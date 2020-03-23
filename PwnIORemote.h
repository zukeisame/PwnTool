#ifndef _PWN_IO_REMOTE_
#define _PWN_IO_REMOTE_

#include <stdint.h>
/*
 * remote io
 */
typedef struct PwnIORemote PIORemote;

void* piorOpen(const char *const domainName, const uint16_t port);

void piorClose(void *const pior);

int piorGetSocketFD(const void *const pior);

int64_t piorSend(const void *const pior, const void *const buffer, const uint64_t size);

int64_t piorRecv(const void *const pior, void *const buffer, const uint64_t size);


#endif