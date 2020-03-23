#ifndef _PWN_IO_
#define _PWN_IO_

#include <stdint.h>
/*
 * an abstract layer to io operations
 * and provide buffering
 */
typedef struct PwnIO PIO;

PIO* pioOpenLocal(const char *const program);

PIO* pioOpenRemote(const char *const domainName, const uint16_t port);

PIO* pioOpenTerminal(void);

void pioClose(PIO *const pio);

int pioGetSendFD(const PIO *const pio);

int pioGetRecvFD(const PIO *const pio);

void pioFlush(const PIO *const pio);

void pioSend(const PIO *const pio, const void *const buffer, const uint64_t size);

int64_t pioRecv(const PIO *const pio, void *const buffer, const uint64_t size);


#endif