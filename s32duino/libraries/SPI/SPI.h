/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@arduino.cc>
 * Copyright (c) 2014 by Paul Stoffregen <paul@pjrc.com> (Transaction API)
 * Copyright (c) 2017 by David Sawatzke <david@sawatzke.de> (Adjustments for stm32f030)
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include "variant.h"
#include <stdio.h>

// SPI_HAS_TRANSACTION means SPI has
//   - beginTransaction()
//   - endTransaction()
//   - usingInterrupt()
//   - SPISetting(clock, bitOrder, dataMode)
#define SPI_HAS_TRANSACTION 1

// SPI_ATOMIC_VERSION means that SPI has atomicity fixes and what version.
// This way when there is a bug fix you can check this define to alert users
// of your code if it uses better version of this library.
// This also implies everything that SPI_HAS_TRANSACTION as documented above is
// available too.
#define SPI_ATOMIC_VERSION 1

// For compatibility with sketches designed for AVR @ 16 MHz
// need to go from 64MHz to 16 (/4)
// This function should not be used in new projects.
// Use SPISettings with SPI.beginTransaction() to configure SPI parameters.
#define SPI_CLOCK_DIV2	 2
#define SPI_CLOCK_DIV4	 4
#define SPI_CLOCK_DIV8	 8
#define SPI_CLOCK_DIV16	 16
#define SPI_CLOCK_DIV32	 32
#define SPI_CLOCK_DIV64	 64
#define SPI_CLOCK_DIV128 128
#define SPI_CLOCK_DIV256 256

#define SPI_MODE0 0x00
#define SPI_MODE1 0x01
#define SPI_MODE2 0x02
#define SPI_MODE3 0x03

enum SPITransferMode {
	SPI_CONTINUE,
	SPI_LAST
};

class SPISettings {
public:
	SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) {
		uint32_t clockSetting = F_CPU / 2;
		uint8_t clockDiv = 0;
		while (clockDiv < 7 && clock < clockSetting) {
			clockSetting /= 2;
			clockDiv++;
		}
		CR1 = clockDiv << 3;


		if(bitOrder == LSBFIRST) {
			CR1 |= SPI_CR1_LSBFIRST;
		}

		if((dataMode == SPI_MODE1)||(dataMode == SPI_MODE3)) {
			CR1 |= SPI_CR1_CPHA;
		}

		if((dataMode == SPI_MODE2)||(dataMode == SPI_MODE3)) {
			CR1 |= SPI_CR1_CPOL;
		}

	}
	SPISettings() {
		// Slowest speed
		CR1 = (7 << 3);
	}
private:
	uint32_t CR1;
	friend class SPIClass;
};



class SPIClass {
public:
	SPIClass();
	SPIClass(SPI_TypeDef *spi, uint8_t mosi, uint8_t miso, uint8_t sck);

	// Transfer functions
	// Write to the SPI bus (MOSI pin) and also receive (MISO pin)
	uint8_t transfer(uint8_t data);

	uint16_t transfer16(uint16_t data);

	void transfer(void *buf, size_t count);

	void beginTransaction(SPISettings settings);

	// After performing a group of transfers and releasing the chip select
	// signal, this function allows others to access the SPI bus
	void endTransaction(void);

	// SPI Configuration methods
	void attachInterrupt(void);
	void detachInterrupt(void);

	void begin(void);
	void end(void);

	// Attach/Detach pin to/from SPI controller
	void begin(uint8_t _pin);
	void end(uint8_t _pin);


	// This function is deprecated.  New applications should use
	// beginTransaction() to configure SPI settings.
	void setBitOrder(uint8_t bitOrder);

	// This function is deprecated.  New applications should use
	// beginTransaction() to configure SPI settings.
	void setDataMode(uint8_t dataMode);
	// This function is deprecated.  New applications should use
	// beginTransaction() to configure SPI settings.
	void setClockDivider(uint8_t clockDiv);
private:
	SPI_TypeDef *spi;
	uint32_t pin_miso;
	uint32_t pin_mosi;
	uint32_t pin_sck;
};

extern SPIClass SPI;

#endif
