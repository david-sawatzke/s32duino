#ifndef __USART_H
#define __USART_H
#include "HardwareSerial.h"
#include "RingBuffer.h"
#include "stm32_def.h"
#include "PortNames.h"
#include "PeripheralPins.h"
#include "register_helpers.h"

#include <stdint.h>

class Usart : public HardwareSerial
{
public:
	Usart(USART_TypeDef *_s, PinName _pinRX, PinName _pinTX);
	void begin(uint32_t baudRate);
	void begin(uint32_t baudrate, uint16_t config);
	void end();
	int available();
	int availableForWrite();
	int peek();
	int read();
	void flush();
	size_t write(const uint8_t data);
	using Print::write; // pull in write(str) and write(buf, size) from Print

	void IrqHandler();

	operator bool() { return true; }

private:
	PinName rxPin;
	PinName txPin;
	USART_TypeDef *usart;
	RingBuffer rxBuffer;
	RingBuffer txBuffer;
};

#endif // __USART_H
