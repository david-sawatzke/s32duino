/*
 * <Description>
 *
 * Copyright (C) 2017, STMicroelectronics - All Rights Reserved
 *
 * License type: GPLv2
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef _PINNAMES_H
#define _PINNAMES_H

#include "PinNamesTypes.h"
#include "PortNames.h"

#ifdef __cplusplus
extern "C" {
#endif

#define GPIO_PIN(port, pin) (((uint32_t)port & 0xFFFFFFF0) | (pin & 0xF))

	typedef enum {

		PA0  = GPIO_PIN(GPIOA, 0x00),
		PA1  = GPIO_PIN(GPIOA, 0x01),
		PA2  = GPIO_PIN(GPIOA, 0x02),
		PA3  = GPIO_PIN(GPIOA, 0x03),
		PA4  = GPIO_PIN(GPIOA, 0x04),
		PA5  = GPIO_PIN(GPIOA, 0x05),
		PA6  = GPIO_PIN(GPIOA, 0x06),
		PA7  = GPIO_PIN(GPIOA, 0x07),
		PA8  = GPIO_PIN(GPIOA, 0x08),
		PA9  = GPIO_PIN(GPIOA, 0x09),
		PA10 = GPIO_PIN(GPIOA, 0x0A),
		PA11 = GPIO_PIN(GPIOA, 0x0B),
		PA12 = GPIO_PIN(GPIOA, 0x0C),
		PA13 = GPIO_PIN(GPIOA, 0x0D),
		PA14 = GPIO_PIN(GPIOA, 0x0E),
		PA15 = GPIO_PIN(GPIOA, 0x0F),

		PB0  = GPIO_PIN(GPIOB, 0x00),
		PB1  = GPIO_PIN(GPIOB, 0x01),
		PB2  = GPIO_PIN(GPIOB, 0x02),
		PB3  = GPIO_PIN(GPIOB, 0x03),
		PB4  = GPIO_PIN(GPIOB, 0x04),
		PB5  = GPIO_PIN(GPIOB, 0x05),
		PB6  = GPIO_PIN(GPIOB, 0x06),
		PB7  = GPIO_PIN(GPIOB, 0x07),
		PB8  = GPIO_PIN(GPIOB, 0x08),
		PB9  = GPIO_PIN(GPIOB, 0x09),
		PB10 = GPIO_PIN(GPIOB, 0x0A),
		PB11 = GPIO_PIN(GPIOB, 0x0B),
		PB12 = GPIO_PIN(GPIOB, 0x0C),
		PB13 = GPIO_PIN(GPIOB, 0x0D),
		PB14 = GPIO_PIN(GPIOB, 0x0E),
		PB15 = GPIO_PIN(GPIOB, 0x0F),
#if defined GPIOC_BASE
		PC0  = GPIO_PIN(GPIOC, 0x00),
		PC1  = GPIO_PIN(GPIOC, 0x01),
		PC2  = GPIO_PIN(GPIOC, 0x02),
		PC3  = GPIO_PIN(GPIOC, 0x03),
		PC4  = GPIO_PIN(GPIOC, 0x04),
		PC5  = GPIO_PIN(GPIOC, 0x05),
		PC6  = GPIO_PIN(GPIOC, 0x06),
		PC7  = GPIO_PIN(GPIOC, 0x07),
		PC8  = GPIO_PIN(GPIOC, 0x08),
		PC9  = GPIO_PIN(GPIOC, 0x09),
		PC10 = GPIO_PIN(GPIOC, 0x0A),
		PC11 = GPIO_PIN(GPIOC, 0x0B),
		PC12 = GPIO_PIN(GPIOC, 0x0C),
		PC13 = GPIO_PIN(GPIOC, 0x0D),
		PC14 = GPIO_PIN(GPIOC, 0x0E),
		PC15 = GPIO_PIN(GPIOC, 0x0F),
#endif
#if defined GPIOD_BASE
		PD0  = GPIO_PIN(GPIOD, 0x00),
		PD1  = GPIO_PIN(GPIOD, 0x01),
		PD2  = GPIO_PIN(GPIOD, 0x02),
		PD3  = GPIO_PIN(GPIOD, 0x03),
		PD4  = GPIO_PIN(GPIOD, 0x04),
		PD5  = GPIO_PIN(GPIOD, 0x05),
		PD6  = GPIO_PIN(GPIOD, 0x06),
		PD7  = GPIO_PIN(GPIOD, 0x07),
		PD8  = GPIO_PIN(GPIOD, 0x08),
		PD9  = GPIO_PIN(GPIOD, 0x09),
		PD10 = GPIO_PIN(GPIOD, 0x0A),
		PD11 = GPIO_PIN(GPIOD, 0x0B),
		PD12 = GPIO_PIN(GPIOD, 0x0C),
		PD13 = GPIO_PIN(GPIOD, 0x0D),
		PD14 = GPIO_PIN(GPIOD, 0x0E),
		PD15 = GPIO_PIN(GPIOD, 0x0F),
#endif
#if defined GPIOE_BASE
		PE0  = GPIO_PIN(GPIOE, 0x00),
		PE1  = GPIO_PIN(GPIOE, 0x01),
		PE2  = GPIO_PIN(GPIOE, 0x02),
		PE3  = GPIO_PIN(GPIOE, 0x03),
		PE4  = GPIO_PIN(GPIOE, 0x04),
		PE5  = GPIO_PIN(GPIOE, 0x05),
		PE6  = GPIO_PIN(GPIOE, 0x06),
		PE7  = GPIO_PIN(GPIOE, 0x07),
		PE8  = GPIO_PIN(GPIOE, 0x08),
		PE9  = GPIO_PIN(GPIOE, 0x09),
		PE10 = GPIO_PIN(GPIOE, 0x0A),
		PE11 = GPIO_PIN(GPIOE, 0x0B),
		PE12 = GPIO_PIN(GPIOE, 0x0C),
		PE13 = GPIO_PIN(GPIOE, 0x0D),
		PE14 = GPIO_PIN(GPIOE, 0x0E),
		PE15 = GPIO_PIN(GPIOE, 0x0F),
#endif
#if defined GPIOF_BASE
		PF0  = GPIO_PIN(GPIOF, 0x00),
		PF1  = GPIO_PIN(GPIOF, 0x01),
		PF2  = GPIO_PIN(GPIOF, 0x02),
		PF3  = GPIO_PIN(GPIOF, 0x03),
		PF4  = GPIO_PIN(GPIOF, 0x04),
		PF5  = GPIO_PIN(GPIOF, 0x05),
		PF6  = GPIO_PIN(GPIOF, 0x06),
		PF7  = GPIO_PIN(GPIOF, 0x07),
		PF8  = GPIO_PIN(GPIOF, 0x08),
		PF9  = GPIO_PIN(GPIOF, 0x09),
		PF10 = GPIO_PIN(GPIOF, 0x0A),
		PF11 = GPIO_PIN(GPIOF, 0x0B),
		PF12 = GPIO_PIN(GPIOF, 0x0C),
		PF13 = GPIO_PIN(GPIOF, 0x0D),
		PF14 = GPIO_PIN(GPIOF, 0x0E),
		PF15 = GPIO_PIN(GPIOF, 0x0F),
#endif
#if defined GPIOG_BASE
		PG0  = GPIO_PIN(GPIOG, 0x00),
		PG1  = GPIO_PIN(GPIOG, 0x01),
		PG2  = GPIO_PIN(GPIOG, 0x02),
		PG3  = GPIO_PIN(GPIOG, 0x03),
		PG4  = GPIO_PIN(GPIOG, 0x04),
		PG5  = GPIO_PIN(GPIOG, 0x05),
		PG6  = GPIO_PIN(GPIOG, 0x06),
		PG7  = GPIO_PIN(GPIOG, 0x07),
		PG8  = GPIO_PIN(GPIOG, 0x08),
		PG9  = GPIO_PIN(GPIOG, 0x09),
		PG10 = GPIO_PIN(GPIOG, 0x0A),
		PG11 = GPIO_PIN(GPIOG, 0x0B),
		PG12 = GPIO_PIN(GPIOG, 0x0C),
		PG13 = GPIO_PIN(GPIOG, 0x0D),
		PG14 = GPIO_PIN(GPIOG, 0x0E),
		PG15 = GPIO_PIN(GPIOG, 0x0F),
#endif
#if defined GPIOH_BASE
		PH0  = GPIO_PIN(GPIOH, 0x00),
		PH1  = GPIO_PIN(GPIOH, 0x01),
		PH2  = GPIO_PIN(GPIOH, 0x02),
		PH3  = GPIO_PIN(GPIOH, 0x03),
		PH4  = GPIO_PIN(GPIOH, 0x04),
		PH5  = GPIO_PIN(GPIOH, 0x05),
		PH6  = GPIO_PIN(GPIOH, 0x06),
		PH7  = GPIO_PIN(GPIOH, 0x07),
		PH8  = GPIO_PIN(GPIOH, 0x08),
		PH9  = GPIO_PIN(GPIOH, 0x09),
		PH10 = GPIO_PIN(GPIOH, 0x0A),
		PH11 = GPIO_PIN(GPIOH, 0x0B),
		PH12 = GPIO_PIN(GPIOH, 0x0C),
		PH13 = GPIO_PIN(GPIOH, 0x0D),
		PH14 = GPIO_PIN(GPIOH, 0x0E),
		PH15 = GPIO_PIN(GPIOH, 0x0F),
#endif
#if defined GPIOI_BASE
		PI0  = GPIO_PIN(GPIOI, 0x00),
		PI1  = GPIO_PIN(GPIOI, 0x01),
		PI2  = GPIO_PIN(GPIOI, 0x02),
		PI3  = GPIO_PIN(GPIOI, 0x03),
		PI4  = GPIO_PIN(GPIOI, 0x04),
		PI5  = GPIO_PIN(GPIOI, 0x05),
		PI6  = GPIO_PIN(GPIOI, 0x06),
		PI7  = GPIO_PIN(GPIOI, 0x07),
		PI8  = GPIO_PIN(GPIOI, 0x08),
		PI9  = GPIO_PIN(GPIOI, 0x09),
		PI10 = GPIO_PIN(GPIOI, 0x0A),
		PI11 = GPIO_PIN(GPIOI, 0x0B),
		PI12 = GPIO_PIN(GPIOI, 0x0C),
		PI13 = GPIO_PIN(GPIOI, 0x0D),
		PI14 = GPIO_PIN(GPIOI, 0x0E),
		PI15 = GPIO_PIN(GPIOI, 0x0F),
#endif

		// Not connected
		NC = (int)0xFFFFFFFF
	} PinName;

#ifdef __cplusplus
		}
#endif

#endif
