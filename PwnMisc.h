#ifndef _PWN_MISC_
#define _PWN_MISC_

#include "PwnDef.h"
#include <stdint.h>
/*
 * some commons
 */
void pwnPrintByte(const uint64_t index, const Byte byte);

const char* pwnGetStringAfter(const char *const current, const char c);


#endif