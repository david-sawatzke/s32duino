/*
  Copyright (c) 2011 Arduino.  All right reserved.

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

#include "Arduino.h"




static int _readResolution = 10;
static int _writeResolution = 8;

void analogReadResolution(int res) {
	_readResolution = res;
}

void analogWriteResolution(int res) {
	_writeResolution = res;
}

static inline uint32_t mapResolution(uint32_t value, uint32_t from, uint32_t to) {
	if (from == to)
		return value;
	if (from > to)
		return value >> (from-to);
	else
		return value << (to-from);
}


//perform the read operation on the selected analog pin.
//the initialization of the analog PIN is done through this function
uint16_t analogRead(PinName ulPin)
{
	// See if the Pin is an analog pin
	uint32_t pinData = pinmap_find_data(ulPin, PinMap_ADC);
	if (pinData == NP) {
		return 0;
	}
	// Save the current pin mode
	uint8_t pinMode = getGPIOMODER(ulPin);
	ADC_TypeDef * adc = (ADC_TypeDef *)STM_PIN_PERIPHERAL(pinData);
	// Set ADC Pin Mode
	setGPIOMODER(ulPin, 0b11);
	// Setup ADC if it isn't enabled
	if ((adc->CR & ADC_CR_ADEN) == 0) {
		//Calibrate ADC
		adc->CR |= ADC_CR_ADCAL;
		//Wait until calibration is done
		while ((adc->CR & ADC_CR_ADCAL) != 0);
		//Enable the ADC
		adc->CR |= ADC_CR_ADEN;
		//Wait until it's ready
		while ((adc->ISR & ADC_ISR_ADRDY) == 0);
		//Keep 8 bits
		//Enable maxmium sample time
		adc->SMPR = ADC_SMPR_SMP;
		// Use 12 Bits, right aligned
		adc->CFGR1 = 0;
	}
	//Enable the channel
	adc->CHSELR = 1 << STM_PIN_CHANNEL(pinData);
	adc->CR |= ADC_CR_ADSTART;
	while ((adc->ISR & ADC_ISR_EOC) == 0);
	uint16_t value = adc->DR;
	value = mapResolution(value, 12, _readResolution);
	setGPIOMODER(ulPin, pinMode);
	return value;
}


// Right now, PWM output only works on the pins with
// hardware support.  These are defined in the appropriate
// variant.cpp file.  For the rest of the pins, we default
// to digital output.
void analogWrite(PinName ulPin, uint32_t ulValue) {
	// See if the Pin is an analog pin
	uint32_t pinData = pinmap_find_data(ulPin, PinMap_PWM);
	if (pinData != NP) {
		TIM_TypeDef * tim = (TIM_TypeDef *)STM_PIN_PERIPHERAL(pinData);
		if ((tim->CR1 & TIM_CR1_CEN) == 0) {
			tim->ARR = (1 << _writeResolution) - 1;
			// PSC is implicity 0, go as fast as possible
			tim->CR1 = TIM_CR1_ARPE | TIM_CR1_CEN;
		}
		ulValue = (ulValue * tim->ARR) / ((1 << _writeResolution) - 1);

		switch (STM_PIN_CHANNEL(pinData)) {
			// TODO handle inverted
		case 1:
			tim->CCER |= TIM_CCER_CC1E;
			tim->CCMR1 |= TIM_CCMR1_OC1PE | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
			tim->CCR1 = ulValue;
			break;
		case 2:
			tim->CCER |= TIM_CCER_CC2E;
			tim->CCMR1 |= TIM_CCMR1_OC2PE | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;
			tim->CCR2 = ulValue;
			break;
		case 3:
			tim->CCER |= TIM_CCER_CC3E;
			tim->CCMR2 |= TIM_CCMR2_OC3PE | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2;
			tim->CCR3 = ulValue;
			break;
		case 4:
			tim->CCER |= TIM_CCER_CC4E;
			tim->CCMR2 |= TIM_CCMR2_OC4PE | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;
			tim->CCR4 = ulValue;
			break;
		default:
			break;
		}
		setGPIOAFR(ulPin, STM_PIN_AFNUM(pinData));
		setGPIOMODER(ulPin, 0b10);
	} else {
		ulValue = mapResolution(ulValue, _writeResolution, 8);
		if (ulValue < 128) {
			digitalWrite(ulPin, LOW);
		}
		else {
			digitalWrite(ulPin, HIGH);
		}
	}
}
