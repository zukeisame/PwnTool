#include "PwnIOTerminal.h"
#include "PwnError.h"
#include <stdlib.h>
#include <unistd.h>
/*
 * PRIVATE ========================================================================================
 */
struct PwnIOTerminal {

	int pid;
};
/*
 * PUBLIC =========================================================================================
 */
void* piotOpen(void) {
	PIOTerminal *const piot = malloc(sizeof(PIOTerminal));
	if (piot == NULL) {
		pwnStandardError("malloc()");
	}

	piot->pid = getpid();

	return piot;
}

void piotClose(void *const piot) {
	free(piot);
}

int piotGetSendFD(const void *const piot) {
	return STDOUT_FILENO;
}

int piotGetRecvFD(const void *const piot) {
	return STDIN_FILENO;
}

int64_t piotSend(const void *const piot, const void *const buffer, const uint64_t size) {
	return write(STDOUT_FILENO, buffer, size);
}

int64_t piotRecv(const void *const piot, void *const buffer, const uint64_t size) {
	return read(STDIN_FILENO, buffer, size);
}