/*
*******************************************************************************
* Copyright (c) 2016, STMicroelectronics
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
* 3. Neither the name of STMicroelectronics nor the names of its contributors
*    may be used to endorse or promote products derived from this software
*    without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************
*/
#include "Arduino.h"
#include "PeripheralPins.h"

// =====
// Note: Commented lines are alternative possibilities which are not used per default.
//       If you change them, you will have to know what you do
// =====

//*** ADC ***

const PinMap PinMap_ADC[] = {
	{PA0, STM_PIN_DEFINE_EXT(ADC1, 0, 0, 0)}, // ADC_IN0
	{PA1, STM_PIN_DEFINE_EXT(ADC1, 1, 0, 0)}, // ADC_IN1
	{PA2, STM_PIN_DEFINE_EXT(ADC1, 2, 0, 0)}, // ADC_IN2
	{PA3, STM_PIN_DEFINE_EXT(ADC1, 3, 0, 0)}, // ADC_IN3
	{PA4, STM_PIN_DEFINE_EXT(ADC1, 4, 0, 0)}, // ADC_IN4
	{PA5, STM_PIN_DEFINE_EXT(ADC1, 5, 0, 0)}, // ADC_IN4
	{PA6, STM_PIN_DEFINE_EXT(ADC1, 6, 0, 0)}, // ADC_IN6
	{PA7, STM_PIN_DEFINE_EXT(ADC1, 7, 0, 0)}, // ADC_IN7
	{PB1, STM_PIN_DEFINE_EXT(ADC1, 9, 0, 0)}, // ADC_IN9
	{NC, 0}
};

//*** I2C ***

const PinMap PinMap_I2C_SDA[] = {
	//{PB7,   I2C1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF1)},
	{NC,    0}
};

const PinMap PinMap_I2C_SCL[] = {
	//{PB6,   I2C1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF1)},
	{NC,    0}
};

//*** PWM ***

const PinMap PinMap_PWM[] = {
	{PA4,   STM_PIN_DEFINE_EXT(TIM14,  1, 0, GPIO_AF4)},  // TIM14_CH1
	{PA6,   STM_PIN_DEFINE_EXT(TIM3,   1, 0, GPIO_AF1)},  // TIM3_CH1
	{PA7,   STM_PIN_DEFINE_EXT(TIM3,   2, 0, GPIO_AF1)},  // TIM3_CH2
	{PA8,   STM_PIN_DEFINE_EXT(TIM1,   1, 0, GPIO_AF2)},  // TIM1_CH1
	{PA9,   STM_PIN_DEFINE_EXT(TIM1,   2, 0, GPIO_AF2)},  // TIM1_CH2
	{PA10,  STM_PIN_DEFINE_EXT(TIM1,   3, 0, GPIO_AF2)},  // TIM1_CH3
	{PB1,   STM_PIN_DEFINE_EXT(TIM3,   4, 0, GPIO_AF1)},  // TIM3_CH4
	{NC,    0}
};

//*** SERIAL ***

const PinMap PinMap_UART_TX[] = {
	{PA2, STM_PIN_DEFINE(USART1, GPIO_AF1)},
	{PA9, STM_PIN_DEFINE(USART1, GPIO_AF1)},
	{NC,  0}
};

const PinMap PinMap_UART_RX[] = {
	{PA3, STM_PIN_DEFINE(USART1, GPIO_AF1)},
	{PA10, STM_PIN_DEFINE(USART1, GPIO_AF1)},
	{NC,   0}
};

//*** SPI ***

const PinMap PinMap_SPI_MOSI[] = {
	{PA7,  STM_PIN_DEFINE(SPI1, GPIO_AF0)},
	{NC,   0}
};

const PinMap PinMap_SPI_MISO[] = {
	{PA6,  STM_PIN_DEFINE(SPI1, GPIO_AF0)},
	{NC,   0}
};

const PinMap PinMap_SPI_SCK[] = {
	{PA5,  STM_PIN_DEFINE(SPI1, GPIO_AF0)},
	{NC,   0}
};
