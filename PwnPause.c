#include "PwnPause.h"
#include <stdio.h>


void pwnPause() {
	printf("[#] pausing! press enter to continue ...");
	getchar();
	printf("[#] continuing ...\n");
}