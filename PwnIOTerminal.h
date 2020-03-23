#ifndef _PWN_IO_TERMINAL_
#define _PWN_IO_TERMINAL_

#include <stdint.h>
/*
 * local terminal
 */
typedef struct PwnIOTerminal PIOTerminal;

void* piotOpen(void);

void piotClose(void *const piot);

int piotGetSendFD(const void *const piot);

int piotGetRecvFD(const void *const piot);

int64_t piotSend(const void *const piot, const void *const buffer, const uint64_t size);

int64_t piotRecv(const void *const piot, void *const buffer, const uint64_t size);


#endif