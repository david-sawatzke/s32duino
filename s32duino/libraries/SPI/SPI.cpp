/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@arduino.cc>
 * Copyright (c) 2014 by Paul Stoffregen <paul@pjrc.com> (Transaction API)
 * Copyright (c) 2017 by David Sawatzke <david@sawatzke.de> (Port to STM32F0)
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#include "SPI.h"

/* The following contructors are available:
   - SPIClass SPI
   - SPIClass SPI(mosi,miso,sck)
*/
SPIClass SPI;

SPIClass::SPIClass()
{
	spi = SPI1;
	pin_miso = MISO;
	pin_mosi = MOSI;
	pin_sck = SCK;
}

SPIClass::SPIClass(SPI_TypeDef *spi, uint8_t mosi, uint8_t miso, uint8_t sck)
{
	this->spi = spi;
	pin_miso = miso;
	pin_mosi = mosi;
	pin_sck = sck;
}

uint8_t SPIClass::transfer(uint8_t data)
{
	*((uint8_t *)&(spi->DR)) = data;
	while(!(spi->SR & SPI_SR_RXNE));
	return *((uint8_t *)&(spi->DR));
}

uint16_t SPIClass::transfer16(uint16_t data)
{
	union { uint16_t val; struct { uint8_t lsb; uint8_t msb; }; } in, out;
	in.val = data;


	if (spi->CR1 & SPI_CR1_LSBFIRST) {
		out.lsb = transfer(in.lsb);
		out.msb = transfer(in.msb);
	} else {
		out.msb = transfer(in.msb);
		out.lsb = transfer(in.lsb);
	}
	return out.val;
}

void SPIClass::transfer(void *buf, size_t count) 
{
	if (count == 0) return;
	uint8_t *p = (uint8_t *)buf;
	*((uint8_t *)&(spi->DR)) = *p;
	while (--count > 0) {
		uint8_t out = *(p + 1);
		while(!(spi->SR & SPI_SR_RXNE));
		uint8_t in = *((uint8_t *)&(spi->DR));
		*((uint8_t *)&(spi->DR)) = out;
		*p++ = in;
	}
	while(!(spi->SR & SPI_SR_RXNE));
	*p = *((uint8_t *)&(spi->DR));
}

void SPIClass::beginTransaction(SPISettings settings)
{
	spi->CR1 = settings.CR1;
	spi->CR1 |= SPI_CR1_SPE | SPI_CR1_MSTR;
}

void SPIClass::endTransaction(void)
{
}

void SPIClass::begin()
{
	uint32_t pinDataMOSI = pinmap_find_data(pin_mosi, PinMap_SPI_MOSI);
	uint32_t pinDataMISO = pinmap_find_data(pin_miso, PinMap_SPI_MISO);
	uint32_t pinDataSCK = pinmap_find_data(pin_sck, PinMap_SPI_SCK);

	if ((STM_PIN_PERIPHERAL(pinDataMOSI) != STM_PIN_PERIPHERAL(pinDataMISO)) || (STM_PIN_PERIPHERAL(pinDataSCK) != spi)) {
		// Error handling
		__BKPT(1);
	}
        spi->CR2 = SPI_CR2_DS_0 | SPI_CR2_DS_1 | SPI_CR2_DS_2 | SPI_CR2_FRXTH;
	setGPIOAFR(pin_mosi, STM_PIN_AFNUM(pinDataMOSI));
	setGPIOAFR(pin_miso, STM_PIN_AFNUM(pinDataMISO));
	setGPIOAFR(pin_sck, STM_PIN_AFNUM(pinDataSCK));
	setGPIOMODER(pin_mosi, 0b10);
	setGPIOMODER(pin_miso, 0b10);
	setGPIOMODER(pin_sck, 0b10);
	beginTransaction(SPISettings());
}

void SPIClass::end()
{
	//Disable SPI
	spi->CR1 &= ~SPI_CR1_SPE;
}

void SPIClass::setBitOrder(uint8_t bitOrder)
{
	if(bitOrder == LSBFIRST) {
		spi->CR1 |= SPI_CR1_LSBFIRST;
	} else {
		spi->CR1 &= ~SPI_CR1_LSBFIRST;
	}
}

void SPIClass::setDataMode(uint8_t dataMode)
{
	if((dataMode == SPI_MODE1)||(dataMode == SPI_MODE3)) {
		spi->CR1 |= SPI_CR1_CPHA;
	} else {
		spi->CR1 &= ~SPI_CR1_CPHA;
	}

	if((dataMode == SPI_MODE2)||(dataMode == SPI_MODE3)) {
		spi->CR1 |= SPI_CR1_CPOL;
	} else {
		spi->CR1 &= ~SPI_CR1_CPOL;
	}
}

/*
 * This function should not be used in new projects.
 * Use SPISettings with SPI.beginTransaction() to configure SPI parameters.
 */
void SPIClass::setClockDivider(uint8_t clockDiv)
{
	switch(clockDiv) {
	case SPI_CLOCK_DIV2:
	case SPI_CLOCK_DIV4:
	case SPI_CLOCK_DIV8:
	case SPI_CLOCK_DIV16:
	case SPI_CLOCK_DIV32:
	case SPI_CLOCK_DIV64:
	case SPI_CLOCK_DIV128:
	case SPI_CLOCK_DIV256:
		spi->CR1 = (spi->CR1 & ~(7 << 3)) | (clockDiv << 3);
		break;
	}
}
