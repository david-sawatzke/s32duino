/*
  Copyright (c) 2011-2012 Arduino.  All right reserved.

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

#include "WInterrupts.h"

void (*callbacks[16])(void);
void detachInterruptNum(uint8_t pin);

void attachInterrupt(uint32_t p, void (*callback)(void), uint32_t mode)
{
	uint32_t it_mode;
	uint8_t pin = STM_PIN(p);
	volatile GPIO_TypeDef* port = STM_PORT(p);
	// Just so there aren't any unforseen surprises
	detachInterrupt(p);
	callbacks[pin] = callback;
	switch(mode) {
	case CHANGE :
		EXTI->FTSR |= (1 << pin);
		EXTI->RTSR |= (1 << pin);
		break;
	case FALLING :
	case LOW :
		EXTI->FTSR |= (1 << pin);
		EXTI->RTSR &= ~(1 << pin);
		break;
	case RISING :
	case HIGH :
	default:
		EXTI->FTSR &= ~(1 << pin);
		EXTI->RTSR |= (1 << pin);
		break;
	}
	SYSCFG->EXTICR[pin >> 2] = (SYSCFG->EXTICR[pin >> 2] & ~(0xF << ((pin & 0b11) * 4)))
		| (getGPIOPortNumber(STM_PORT(p)) << ((pin & 0b11) * 4));
	EXTI->IMR |= (1 << pin);
}

void detachInterrupt(uint32_t p)
{
	detachInterruptNum(STM_PIN(p));
}

void detachInterruptNum(uint8_t pin)
{
	EXTI->IMR &= ~(1 << pin);
}

void handleInterrupt(uint8_t pin)
{
	if(EXTI->PR & (1 << pin)) {
		EXTI->PR = (1 << pin);
		callbacks[pin]();
	}
}

extern "C" {
	void EXTI0_1_IRQHandler(void)
	{
		handleInterrupt(0);
		handleInterrupt(1);
	}


	void EXTI2_3_IRQHandler(void)
	{
		handleInterrupt(2);
		handleInterrupt(3);
	}

	void EXTI4_15_IRQHandler(void)
	{
		for(uint8_t i = 4; i <= 15; i ++)
			handleInterrupt(i);
	}
}
