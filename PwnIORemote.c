#include "PwnIORemote.h"
#include "PwnError.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
/*
 * PRIVATE ========================================================================================
 */
struct PwnIORemote {

	int socketFD;

	struct sockaddr_in address;
};

PIORemote* piorMalloc(void) {
	PIORemote *const tmp = malloc(sizeof(PIORemote));
	if (tmp == NULL) {
		pwnStandardError("malloc()");
	}
	return tmp;
}

void piorTranslateAddress(struct sockaddr_in *const address, const char *const name, const uint16_t port) {
	struct hostent *const hostInfo = gethostbyname(name);
	if (hostInfo == NULL) {
		pwnStandardError("gethostbyname()");
	}
	
	address->sin_family = AF_INET;
	address->sin_addr = *((struct in_addr*) (hostInfo->h_addr_list[0]));
	address->sin_port = htons(port);
	memset(address->sin_zero, 0, sizeof(address->sin_zero));
}

void piorSetSocketTimeout(const int socketFD, const unsigned long seconds, const unsigned long microseonds) {
	struct timeval interval;
	interval.tv_sec = seconds;
	interval.tv_usec = microseonds * 1000lu;

	if (setsockopt(socketFD, SOL_SOCKET, SO_RCVTIMEO, &interval, sizeof(interval)) < 0) {
		pwnStandardError("setsockopt()");
	}
}
/*
 * PUBLIC =========================================================================================
 */
void* piorOpen(const char *const domainName, const uint16_t port) {
	PIORemote *const pior = piorMalloc();

	pior->socketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (pior->socketFD < 0) {
		pwnStandardError("socket()");
	}

	piorTranslateAddress(&(pior->address), domainName, port);
	if (connect(pior->socketFD, (struct sockaddr*) &(pior->address), sizeof(pior->address)) < 0) {
		pwnStandardError("connect()");
	}
	printf("[#] connection with %s:%hd established\n", domainName, port);

	return pior;
}

void piorClose(void *const ptr) {
	PIORemote *const pior = (PIORemote*) ptr;

	if (close(pior->socketFD) < 0) {
		pwnStandardError("close()");
	}
	free(pior);
}

int piorGetSocketFD(const void *const ptr) {
	const PIORemote *const pior = (PIORemote*) ptr;
	return pior->socketFD;
}

int64_t piorSend(const void *const ptr, const void *const buffer, const uint64_t size) {
	const PIORemote *const pior = (PIORemote*) ptr;
	return send(pior->socketFD, buffer, size, 0);
}

int64_t piorRecv(const void *const ptr, void *const buffer, const uint64_t size) {
	const PIORemote *const pior = (PIORemote*) ptr;
	return recv(pior->socketFD, buffer, size, 0);
}