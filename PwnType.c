#include "PwnType.h"
#include "PwnIO.h"
#include "PwnShell.h"
#include "PwnError.h"
#include "PwnRecvFormat.h"
#include "PwnSendFormat.h"
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/*
 * PRIVATE ========================================================================================
 */
struct PwnType {

	PIO *pio;
};

PT* ptMalloc(void) {
	PT *const pt = malloc(sizeof(PT));
	if (pt == NULL) {
		pwnStandardError("malloc()");
	}

	return pt;
}

void ptSIGPIPEHandler(const int signalNumber) {
	printf("Broken Pipe. Exiting ...\n");
	exit(1);
}

void ptHandleSIGPIPE(void) {
	if (signal(SIGPIPE, ptSIGPIPEHandler) == SIG_ERR) {
		pwnStandardError("signal()");
	}
}
/*
 * PUBLIC =========================================================================================
 */
PT* ptLocal(const char *const program) {
	PT *const pt = ptMalloc();
	pt->pio = pioOpenLocal(program);
	ptHandleSIGPIPE();
	return pt;
}

PT* ptRemote(const char *const domainName, const uint16_t port) {
	PT *const pt = ptMalloc();
	pt->pio = pioOpenRemote(domainName, port);
	ptHandleSIGPIPE();
	return pt;
}
/*
PT* ptTerminal(void) {
	PT *const pt = ptMalloc();
	pt->pio = pioOpenTerminal();
	return pt;
}
*/
void ptClose(PT *const pt) {
	pioClose(pt->pio);
	free(pt);
}

uint64_t ptSendf(const PT *const pt, const char *const formatString, ...) {
	va_list parameters;

	va_start(parameters, formatString);
	const uint64_t sendBytes = pwnSendFormat(pt->pio, formatString, parameters);
	va_end(parameters);

	return sendBytes;
}

uint64_t ptRecvf(const PT *const pt, const char *const formatString, ...) {
	va_list parameters;

	va_start(parameters, formatString);
	const uint64_t recvdBytes = pwnRecvFormat(pt->pio, formatString, parameters);
	va_end(parameters);

	return recvdBytes;
}

void ptFlush(const PT *const pt) {
	pioFlush(pt->pio);
}

void ptShell(const PT *const pt) {
	pwnShell(pt->pio);
}