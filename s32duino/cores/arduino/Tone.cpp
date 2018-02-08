/* Tone.cpp

  A Tone Generator Library

  Written by Brett Hagman

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"

volatile GPIO_TypeDef * port;
uint16_t pin;
uint32_t start;
uint32_t duration;


// frequency (in hertz) and duration (in milliseconds).

void tone(PinName _pin, uint32_t _frequency, uint32_t _duration)
{
	uint8_t end = 0;
	uint32_t prescaler = 1;
	uint32_t period = 0;
	while(end == 0) {
		period = ((uint32_t)(F_CPU / (_frequency * 2) / prescaler)) - 1;

		if((period >= 0xFFFF) && (prescaler < 0xFFFF))
			prescaler++; //prescaler *= 2;

		else
			end = 1;
	}
	if (prescaler > 0xFFFF)
		return;
	TIMER_TONE->CR1 = 0;
	duration = _duration;
	port = STM_PORT(_pin);
	pin = STM_GPIO_PIN(_pin);
	pinMode(_pin, OUTPUT);
	TIMER_TONE->DIER = TIM_DIER_UIE;
	TIMER_TONE->PSC = prescaler-1;
	TIMER_TONE->ARR = period;
	start = millis();
	TIMER_TONE->CR1 = TIM_CR1_ARPE | TIM_CR1_URS | TIM_CR1_CEN;
}


void noTone(PinName _pin)
{
	TIMER_TONE->DIER &= TIM_DIER_UIE;
	digitalWrite(_pin, LOW);
}

void toneCallback(void)
{
	if (TIMER_TONE->SR & TIM_SR_UIF) {
		TIMER_TONE->SR = ~TIM_SR_UIF;
		port->ODR ^= pin;
		if (duration && (millis() - start >= duration))
			TIMER_TONE->DIER &= TIM_DIER_UIE;
	}
}
