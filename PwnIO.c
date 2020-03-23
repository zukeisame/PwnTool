#include "PwnIO.h"
#include "PwnVB.h"
#include "PwnDef.h"
#include "PwnError.h"
#include "PwnIOLocal.h"
#include "PwnIORemote.h"
#include "PwnIOTerminal.h"
#include <stdlib.h>
/*
 * PRIVATE ========================================================================================
 */
typedef enum PwnIOType {
	PIO_LOCAL, 
	PIO_REMOTE, 
	PIO_TERMINAL, 
	PIO_LIMIT
} PIOType;

typedef struct PwnIOFunctionTable {

	void (*const close)(void *const);

	int (*const getSendFD)(const void *const);

	int (*const getRecvFD)(const void *const);

	int64_t (*const send)(const void *const, const void *const, const uint64_t);

	int64_t (*const recv)(const void *const, void *const, const uint64_t);

} PIOFunctionTable;

const PIOFunctionTable pioFunctionTable[PIO_LIMIT] = {
	[PIO_LOCAL] = {
		.close = piolClose, 
		.getSendFD = piolGetSendFD, 
		.getRecvFD = piolGetRecvFD, 
		.send = piolSend, 
		.recv = piolRecv
	}, 

	[PIO_REMOTE] = {
		.close = piorClose, 
		.getSendFD = piorGetSocketFD, 
		.getRecvFD = piorGetSocketFD, 
		.send = piorSend, 
		.recv = piorRecv
	}, 

	[PIO_TERMINAL] = {
		.close = piotClose, 
		.getSendFD = piotGetSendFD, 
		.getRecvFD = piotGetRecvFD, 
		.send = piotSend, 
		.recv = piotRecv
	}
};

struct PwnIO {

	PIOType pioType;

	void *pioStruct;

	VB *buffer;
};

PIO* pioMalloc(void) {
	PIO *const tmp = malloc(sizeof(PIO));
	if (tmp == NULL) {
		pwnStandardError("malloc()");
	}
	return tmp;
}
/*
 * PUBLIC =========================================================================================
 */
PIO* pioOpenLocal(const char *const program) {
	PIO *const pio = pioMalloc();

	pio->pioType = PIO_LOCAL;
	pio->pioStruct = piolOpen(program);
	pio->buffer = vbNew(Byte, 0);

	return pio;
}

PIO* pioOpenRemote(const char *const domainName, const uint16_t port) {
	PIO *const pio = pioMalloc();

	pio->pioType = PIO_REMOTE;
	pio->pioStruct = piorOpen(domainName, port);
	pio->buffer = vbNew(Byte, 0);

	return pio;
}

PIO* pioOpenTerminal(void) {
	PIO *const pio = pioMalloc();

	pio->pioType = PIO_TERMINAL;
	pio->pioStruct = piotOpen();
	pio->buffer = vbNew(Byte, 0);

	return pio;
}

void pioClose(PIO *const pio) {
	pioFunctionTable[pio->pioType].close(pio->pioStruct);
	vbFree(pio->buffer);
	free(pio);
}

int pioGetSendFD(const PIO *const pio) {
	return pioFunctionTable[pio->pioType].getSendFD(pio->pioStruct);
}

int pioGetRecvFD(const PIO *const pio) {
	return pioFunctionTable[pio->pioType].getRecvFD(pio->pioStruct);
}

void pioFlush(const PIO *const pio) {
	int64_t remainedSize = vbGetBufferSize(pio->buffer);

	if (remainedSize == 0) {
		return;
	} else {
		int64_t sentSize = 0, tmp = 0;
		while (remainedSize > 0) {
			tmp = pioFunctionTable[pio->pioType].send(
				pio->pioStruct, vbGetArray(pio->buffer, Byte) + sentSize, remainedSize
			);
			if (tmp < 0) {
				pwnStandardError("pioFlush()");
			}

			sentSize += tmp;
			remainedSize -= tmp;
		}

		vbClear(pio->buffer);
	}
}

void pioSend(const PIO *const pio, const void *const buffer, const uint64_t size) {
	const Byte *const ptr = buffer;
	for (uint64_t i = 0; i < size; ++i) {
		vbPush(pio->buffer, Byte, *(ptr + i));
	}
}

int64_t pioRecv(const PIO *const pio, void *const buffer, const uint64_t size) {
	pioFlush(pio);
	return pioFunctionTable[pio->pioType].recv(pio->pioStruct, buffer, size);
}