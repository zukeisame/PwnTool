#include "PwnIOLocal.h"
#include "PwnError.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
/*
 * PRIVATE ========================================================================================
 */
struct PwnIOLocal {

	int pid;

	int sendFD;

	int recvFD;
};

PIOLocal* piolMalloc(void) {
	PIOLocal *const tmp = malloc(sizeof(PIOLocal));
	if (tmp == NULL) {
		pwnStandardError("malloc()");
	}
	return tmp;
}
/*
 * PUBLIC =========================================================================================
 */
void* piolOpen(const char *const program) {
	int sendPipe[2], recvPipe[2]; // [0] for read end, [1] for write end
	if (pipe(sendPipe) < 0) pwnStandardError("pipe()");
	if (pipe(recvPipe) < 0) pwnStandardError("pipe()");

	const int childPID = fork();
	if (childPID == 0) {
		if (close(sendPipe[1]) < 0) pwnStandardError("close()");
		if (dup2(sendPipe[0], STDIN_FILENO) < 0) pwnStandardError("dup2()");
		if (close(sendPipe[0]) < 0) pwnStandardError("close()");

		if (close(recvPipe[0]) < 0) pwnStandardError("close()");
		if (dup2(recvPipe[1], STDOUT_FILENO) < 0) pwnStandardError("dup2()");
		if (dup2(recvPipe[1], STDERR_FILENO) < 0) pwnStandardError("dup2()");
		if (close(recvPipe[1]) < 0) pwnStandardError("close()");

		if (execl(program, program, NULL) < 0) pwnStandardError("execve()");
	} else if (childPID > 0) {
		printf("[#] forking new process %d\n", childPID);

		if (close(sendPipe[0]) < 0) pwnStandardError("close()");

		if (close(recvPipe[1]) < 0) pwnStandardError("close()");

		PIOLocal *const piol = piolMalloc();
		piol->pid = childPID;
		piol->sendFD = sendPipe[1];
		piol->recvFD = recvPipe[0];
		return piol;
	} else {
		pwnStandardError("fork()");
	}
}

void piolClose(void *const ptr) {
	PIOLocal *const piol = (PIOLocal*) ptr;

	if (close(piol->sendFD) < 0) {
		pwnStandardError("close()");
	}
	if (close(piol->recvFD) < 0) {
		pwnStandardError("close()");
	}
	if (waitpid(piol->pid, NULL, 0) < 0) {
		pwnStandardError("waitpid()");
	}

	free(piol);
}

int piolGetSendFD(const void *const ptr) {
	const PIOLocal *const piol = (PIOLocal*) ptr;
	return piol->sendFD;
}

int piolGetRecvFD(const void *const ptr) {
	const PIOLocal *const piol = (PIOLocal*) ptr;
	return piol->recvFD;
}

int64_t piolSend(const void *const ptr, const void *const buffer, const uint64_t size) {
	const PIOLocal *const piol = (PIOLocal*) ptr;
	return write(piol->sendFD, buffer, size);
}

int64_t piolRecv(const void *const ptr, void *const buffer, const uint64_t size) {
	const PIOLocal *const piol = (PIOLocal*) ptr;
	return read(piol->recvFD, buffer, size);
}