#include "PwnFcntl.h"
#include "PwnError.h"
#include <unistd.h>
#include <fcntl.h>


void pwnBlockFD(const int fd) {
	if (fd < 0) return;

	int flags;
	if ((flags = fcntl(fd, F_GETFL)) < 0) {
		pwnStandardError("fcntl()");
	}

	flags &= (~O_NONBLOCK);
	if (fcntl(fd, F_SETFL, flags) < 0) {
		pwnStandardError("fcntl()");
	}
}


void pwnNonBlockFD(const int fd) {
	if (fd < 0) return;

	int flags;
	if ((flags = fcntl(fd, F_GETFL)) < 0) {
		pwnStandardError("fcntl()");
	}

	flags |= O_NONBLOCK;
	if (fcntl(fd, F_SETFL, flags) < 0) {
		pwnStandardError("fcntl()");
	}
}