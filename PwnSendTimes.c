#include "PwnSendTimes.h"
#include "PwnDef.h"
/*
 * PRIVATE ========================================================================================
 */
/*
 * PUBLIC =========================================================================================
 */
uint64_t pwnSendByteTimes(const PIO *const pio, va_list parameters, const uint64_t times) {
	const Byte byte = (Byte) va_arg(parameters, int);

	for (uint64_t i = 0; i < times; ++i) {
		pioSend(pio, &byte, sizeof(byte));
	}

	return times * sizeof(byte);
}

uint64_t pwnSendFourBytesTimes(const PIO *const pio, va_list parameters, const uint64_t times) {
	const FourBytes fourBytes = va_arg(parameters, FourBytes);

	for (uint64_t i = 0; i < times; ++i) {
		pioSend(pio, &fourBytes, sizeof(fourBytes));
	}

	return times * sizeof(fourBytes);
}

uint64_t pwnSendEightBytesTimes(const PIO *const pio, va_list parameters, const uint64_t times) {
	const EightBytes eightBytes = va_arg(parameters, EightBytes);

	for (uint64_t i = 0; i < times; ++i) {
		pioSend(pio, &eightBytes, sizeof(eightBytes));
	}

	return times * sizeof(eightBytes);
}