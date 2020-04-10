#include "PwnShell.h"
#include "PwnFcntl.h"
#include "PwnError.h"
#include "PwnDef.h"
#include "PwnVB.h"
#include <string.h>
#include <stdarg.h>
#include <ctype.h>
#include <poll.h>
/*
 * PRIVATE ========================================================================================
 */
int pwnShellHasExitPattern(const VB *const vb) {
	const char *const line = vbGetArray(vb, Byte);
	
	for (long i = 0; i < vbGetBufferSize(vb); ++i) {
		if (isspace(line[i])) {
			continue;
		}

		if (isspace(*(line + i + 4)) && (strncmp(line + i, "exit", 4) == 0)) {
			return 1;
		} else {
			return 0;
		}
	}

	return 0;
}

void pwnShellRecvAllVB(const PIO *const pio, VB *const vb) {
	Byte byte;

	if (pioRecv(pio, &byte, sizeof(byte)) == sizeof(byte)) { // first byte
		vbPush(vb, Byte, byte);
		// read remainders
		pwnNonBlockFD(pioGetRecvFD(pio));
		while (pioRecv(pio, &byte, sizeof(byte)) == sizeof(byte)) {
			vbPush(vb, Byte, byte);
		}
		pwnBlockFD(pioGetRecvFD(pio));
	}
}

void pwnShellSendVB(const PIO *const pio, const VB *const vb) {
	pioSend(pio, vbGetArray(vb, Byte), vbGetBufferSize(vb));
	pioFlush(pio);
}

int pwnShellPoll(const PIO *const pio, struct pollfd *const poller) {
	poller->fd = pioGetRecvFD(pio);
	poller->events = POLLIN;
	poller->revents = 0;

	return poll(poller, 1, 300);
}
/*
 * PUBLIC =========================================================================================
 */
#define PROMOPT "cheng$ "
#define TEXT_RED "\x1b[31m"
#define TEXT_WHITE "\x1b[37m"
#define STDERR_TO_STDOUT "exec 2>&1\n"
void pwnShell(const PIO *const pio) {
	Byte byte;
	int pollRet;
	struct pollfd poller;
	uint64_t pollingCount;
	VB *const vb = vbNew(Byte, 0);
	PIO *const terminalPIO = pioOpenTerminal();

	pioSend(pio, STDERR_TO_STDOUT, strlen(STDERR_TO_STDOUT));
	pioFlush(pio);

	pwnNonBlockFD(pioGetRecvFD(pio)); // discard existing data
	while (pioRecv(pio, &byte, sizeof(byte)) == sizeof(byte));
	pwnBlockFD(pioGetRecvFD(pio));

	for (;;) {
		pioSend(terminalPIO, TEXT_RED, strlen(TEXT_RED));
		pioSend(terminalPIO, PROMOPT, strlen(PROMOPT));
		pioSend(terminalPIO, TEXT_WHITE, strlen(TEXT_WHITE));
		pioFlush(pio);

		pwnShellRecvAllVB(terminalPIO, vb);
		if (vbGet(vb, Byte, 0) != '\n') {
			pwnShellSendVB(pio, vb);
			if (pwnShellHasExitPattern(vb)) {
				break;
			}
		}
		vbClear(vb);

		pollRet = pwnShellPoll(pio, &poller);
		if (pollRet < 0) {
			pwnStandardError("poll()");
		} else if (pollRet == 1) {
			if (poller.revents & POLLIN) {
				pwnShellRecvAllVB(pio, vb);
				pwnShellSendVB(terminalPIO, vb);
				vbClear(vb);
			} else {
				break;
			}
		}
	}

	pioClose(terminalPIO);
	vbFree(vb);
}
#undef STDERR_TO_STDOUT
#undef TEXT_WHITE
#undef TEXT_RED
#undef PROMOPT