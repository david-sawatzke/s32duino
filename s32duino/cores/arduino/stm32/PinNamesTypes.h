/*  *******************************************************************************
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
#ifndef _PINNAMESTYPES_H
#define _PINNAMESTYPES_H

#ifdef __cplusplus
extern "C" {

#endif

/*  STM PIN data as used in pin_function is coded on 32 bits as below
 *   [2:0]  Alternate Num
 *     [3]  Inverted (for Timer)
 *   [4:7]  Channel (Analog/Timer
 *  [32:8]  Peripheral (as every Peripheral is at least 1 KB big, we can use the lower 8 bits
 */

#define STM_PIN_PERIPHERAL_MASK 0x00FFFFFF
#define STM_PIN_PERIPHERAL_SHIFT 8
#define STM_PIN_PERIPHERAL_BITS (STM_PIN_FUNCTION_MASK << STM_PIN_FUNCTION_SHIFT)

#define STM_PIN_CHAN_MASK 0x0F
#define STM_PIN_CHAN_SHIFT 4
#define STM_PIN_CHANNEL_BIT (STM_PIN_CHAN_MASK << STM_PIN_CHAN_SHIFT)

#define STM_PIN_INV_MASK 0x01
#define STM_PIN_INV_SHIFT 3
#define STM_PIN_INV_BIT (STM_PIN_INV_MASK << STM_PIN_INV_SHIFT)

#define STM_PIN_AFNUM_MASK 0b00000111
#define STM_PIN_AFNUM_SHIFT 0
#define STM_PIN_AFNUM_BITS (STM_PIN_AFNUM_MASK << STM_PIN_AFNUM_SHIFT)

#define STM_PIN_PERIPHERAL(X)         ((volatile void*)((((X) >> STM_PIN_PERIPHERAL_SHIFT) & STM_PIN_PERIPHERAL_MASK) << STM_PIN_PERIPHERAL_SHIFT))
#define STM_PIN_CHANNEL(X)          (((X) >> STM_PIN_CHAN_SHIFT) & STM_PIN_CHAN_MASK)
#define STM_PIN_INVERTED(X)         (((X) >> STM_PIN_INV_SHIFT) & STM_PIN_INV_MASK)
#define STM_PIN_AFNUM(X)            (((X) >> STM_PIN_AFNUM_SHIFT) & STM_PIN_AFNUM_MASK)

#define STM_PIN_DEFINE(PERIPHERAL, AFNUM)  STM_PIN_DEFINE_EXT(PERIPHERAL, 0, 0, AFNUM)

#define STM_PIN_DEFINE_EXT(PERIPHERAL, CHAN, INV, AFNUM)	\
	((uint32_t)(PERIPHERAL) |					\
	 ((CHAN   & STM_PIN_CHAN_MASK) << STM_PIN_CHAN_SHIFT) |		\
	 ((INV    & STM_PIN_INV_MASK) << STM_PIN_INV_SHIFT) |		\
	 ((AFNUM  & STM_PIN_AFNUM_MASK) << STM_PIN_AFNUM_SHIFT))

// High nibble = port number (FirstPort <= PortName <= LastPort)
// Low nibble  = pin number
#define STM_PORT(X) ((volatile GPIO_TypeDef *)(((uint32_t)(X)) & 0xFFFFFFF0))
#define STM_PIN(X)  ((uint8_t)(X) & 0xF)
// Check PinName is valid: FirstPort <= PortName <= LastPort
// As FirstPort is equal to 0 and STM_PORT cast as an unsigned
// (STM_PORT(X) >= FirstPort)  is always true

#define STM_GPIO_PIN(X) ((uint16_t)(1<<STM_PIN(X)))

#ifdef __cplusplus
}
#endif

#endif

