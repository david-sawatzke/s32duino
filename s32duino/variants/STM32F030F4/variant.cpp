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

#ifndef F_CPU
#define F_CPU_REPLACEMENT
#endif

#include "variant.h"
#include "Usart.h"


/*
 * UART objects
 */
Usart  Serial(USART1, PA3, PA2); //Connected to ST-Link

void serialEvent() __attribute__((weak));
void serialEvent() { }

void serialEventRun(void)
{
	if (Serial.available()) serialEvent();
}

// ----------------------------------------------------------------------------

extern "C" {

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSI/2)
 *            SYSCLK(Hz)                     = 48000000
 *            HCLK(Hz)                       = 48000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 1
 *            HSI Frequency(Hz)              = 8000000
 *            PREDIV                         = 1
 *            PLLMUL                         = 12
 *            Flash Latency(WS)              = 1
 * @param  None
 * @retval None
 */
	void initVariant(void)
	{
		RCC->CFGR = RCC->CFGR & (~RCC_CFGR_PLLMUL) | (RCC_CFGR_PLLMUL12); /* (6) */

		/* Enable PLL */
		RCC->CR |= RCC_CR_PLLON;

		/* Wait till PLL is ready */
		while((RCC->CR & RCC_CR_PLLRDY) == 0)
		{
		}

		/* Select PLL as system clock source */
		RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

		/* Wait till PLL is used as system clock source */
		while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)RCC_CFGR_SWS_PLL)
		{
		}
#ifdef F_CPU_REPLACEMENT
		SystemCoreClock = 48000000;
#endif
		RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOFEN;
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN | RCC_APB1ENR_TIM14EN;
		RCC->APB2ENR |= RCC_APB2ENR_ADCEN | RCC_APB2ENR_TIM1EN | RCC_APB2ENR_TIM16EN | RCC_APB2ENR_TIM17EN | RCC_APB2ENR_USART1EN | RCC_APB2ENR_SPI1EN;

		SysTick_Config(clockCyclesPerMicrosecond()* 1000);
		/* SysTick_IRQn interrupt configuration */
		NVIC_SetPriority(SysTick_IRQn, 0);
		NVIC_EnableIRQ(SysTick_IRQn);
		NVIC_SetPriority(USART1_IRQn, 0);
		NVIC_EnableIRQ(USART1_IRQn);
		NVIC_SetPriority(TIM16_IRQn, 0);
		NVIC_EnableIRQ(TIM16_IRQn);
		NVIC_SetPriority(EXTI0_1_IRQn, 0);
		NVIC_EnableIRQ(EXTI0_1_IRQn);
		NVIC_SetPriority(EXTI2_3_IRQn, 0);
		NVIC_EnableIRQ(EXTI2_3_IRQn);
		NVIC_SetPriority(EXTI4_15_IRQn, 0);
		NVIC_EnableIRQ(EXTI4_15_IRQn);
		__enable_irq();
	}

	void USART1_IRQHandler(void) {
		Serial.IrqHandler();
	}
	void TIM16_IRQHandler(void) {
		toneCallback();
	}
}
