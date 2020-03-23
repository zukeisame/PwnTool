#include "PwnShell.h"
#include "PwnFcntl.h"
#include "PwnError.h"
#include "PwnSleep.h"
#include "PwnDef.h"
#include "PwnVB.h"
#include <string.h>
#include <stdarg.h>
/*
 * PRIVATE ========================================================================================
 */
int pwnShellHasExitPattern(const VB *const vb) {
	const char *const line = vbGetArray(vb, Byte);

	if (strncmp(line, "exit", 4) == 0) {
		return 1;
	} else if (strstr(line, " exit") != NULL) {
		return 1;
	} else if (strstr(line, "exit ") != NULL) {
		return 1;
	} else {
		return 0;
	}
}

void pwnShellRecvAllVB(const PIO *const pio, VB *const vb) {
	Byte byte;
	while (pioRecv(pio, &byte, sizeof(byte)) == sizeof(byte)) {
		vbPush(vb, Byte, byte);
	}
}

void pwnShellRecvLineVB(const PIO *const pio, VB *const vb) {
	Byte byte;

	if (pioRecv(pio, &byte, sizeof(byte)) == sizeof(byte)) { // recv first byte
		while (byte != '\n') { // if is not end of line
			vbPush(vb, Byte, byte);

			if (pioRecv(pio, &byte, sizeof(byte)) != sizeof(byte)) {
				break;
			}
		}	
	}
}

void pwnShellSendVB(const PIO *const pio, const VB *const vb) {
	pioSend(pio, vbGetArray(vb, Byte), vbGetBufferSize(vb));
	pioFlush(pio);
}

void pwnShellSendString(const PIO *const pio, const char *const string) {
	const uint64_t length = strlen(string);

	pioSend(pio, string, length);
	pioFlush(pio);
}
/*
 * PUBLIC =========================================================================================
 */
#define POLLING_LIMIT 3
#define TEXT_RED "\x1b[31m"
#define TEXT_WHITE "\x1b[37m"
void pwnShell(const PIO *const pio) {
	uint64_t pollingCount;
	VB *const vb = vbNew(Byte, 0);
	PIO *const terminalPIO = pioOpenTerminal();

	pwnNonBlockFD(pioGetRecvFD(pio));
	pwnShellRecvAllVB(pio, vb); // discard existing data
	vbClear(vb);

	const char *const STDERR_TO_STDOUT = "exec 2>&1\n";
	pwnShellSendString(pio, STDERR_TO_STDOUT);

	for (;;) {
		pwnShellSendString(terminalPIO, TEXT_RED);
		pwnShellSendString(terminalPIO, "cheng$ ");
		pwnShellSendString(terminalPIO, TEXT_WHITE);

		pwnShellRecvLineVB(terminalPIO, vb);
		if (vbGetBufferSize(vb) > 0) {
			vbPush(vb, Byte, '\n');
			pwnShellSendVB(pio, vb);
			if (pwnShellHasExitPattern(vb)) {
				break;
			}
			vbClear(vb);
		}

		pollingCount = 0;
		do {
			pwnSleep(100);
			++pollingCount;
			pwnShellRecvAllVB(pio, vb);
		} while (pollingCount < POLLING_LIMIT && vbGetBufferSize(vb) == 0);

		if (vbGetBufferSize(vb) > 0) {
			pwnShellSendVB(terminalPIO, vb);
			vbClear(vb);
		}
	}

	pioClose(terminalPIO);
	vbFree(vb);
}
#undef POLLING_LIMIT
#undef TEXT_WHITE
#undef TEXT_RED