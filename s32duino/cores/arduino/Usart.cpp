/*
  Copyright (c) 2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Usart.h"

Usart::Usart(USART_TypeDef *_s, PinName _pinRX, PinName _pinTX)
{
	usart = _s;
	rxPin = _pinRX;
	txPin = _pinTX;
}

void Usart::begin(unsigned long baudrate)
{
	begin(baudrate, SERIAL_8N1);
}

void Usart::begin(unsigned long baudrate, uint16_t config)
{
	uint32_t pinDataTx = pinmap_find_data(txPin, PinMap_UART_TX);
	uint32_t pinDataRx = pinmap_find_data(rxPin, PinMap_UART_RX);
	if ((STM_PIN_PERIPHERAL(pinDataTx) != STM_PIN_PERIPHERAL(pinDataRx)) || (STM_PIN_PERIPHERAL(pinDataRx) != usart)) {
		// Error handling
		__BKPT(1);
	}

        usart->BRR = F_CPU/baudrate;
        usart->CR3 = 0;

	switch (config & HARDSER_STOP_BIT_MASK) {
	case HARDSER_STOP_BIT_1_5:
		usart->CR2 = USART_CR2_STOP_0 | USART_CR2_STOP_1;
	case HARDSER_STOP_BIT_2:
		usart->CR2 = USART_CR2_STOP_1;
	default:
		usart->CR2 = 0;
	}

	switch (config & HARDSER_PARITY_MASK) {
	case HARDSER_PARITY_EVEN:
		usart->CR1 = USART_CR1_PCE;
	case HARDSER_PARITY_ODD:
		usart->CR1 = USART_CR1_PCE | USART_CR1_PS;
	default:
		usart->CR1 = 0;
	}

	usart->CR1 |= USART_CR1_RXNEIE | USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;

	setGPIOAFR(txPin, STM_PIN_AFNUM(pinDataTx));
	setGPIOAFR(rxPin, STM_PIN_AFNUM(pinDataRx));
	setGPIOMODER(txPin, 0b10);
	setGPIOMODER(rxPin, 0b10);

}

void Usart::end()
{
	usart->CR1 &= ~(USART_CR1_TXEIE | USART_CR1_RXNEIE);
	rxBuffer.clear();
	txBuffer.clear();
	usart->CR1 &= ~USART_CR1_UE;
}

void Usart::flush()
{
	while(txBuffer.available());
}

void Usart::IrqHandler()
{
	if (usart->ISR & USART_ISR_TXE) {
		int16_t c = txBuffer.read_char();
		if (c >= 0)
			usart->TDR = c;
		else
			usart->CR1 &= ~USART_CR1_TXEIE;
	}
	if (usart->ISR & USART_ISR_RXNE)
		rxBuffer.store_char(usart->RDR);
	if (usart->ISR & USART_ISR_ORE)
		// An overrung error has happened
		// Just ignore it for now
		usart->ICR = USART_ICR_ORECF;

	if (usart->ISR & USART_ISR_FE)
		// A framing error happened
	        // Just ignore it for now
		usart->ICR = USART_ICR_FECF;
}

int Usart::available()
{
	return rxBuffer.available();
}

int Usart::availableForWrite()
{
	return !txBuffer.isFull();
}

int Usart::peek()
{
	return rxBuffer.peek();
}

int Usart::read()
{
	return rxBuffer.read_char();
}

size_t Usart::write(const uint8_t data)
{
	while(txBuffer.isFull());
	txBuffer.store_char(data);
	usart->CR1 |= USART_CR1_TXEIE;
    return 1;
}
