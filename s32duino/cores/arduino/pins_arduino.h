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
#ifndef _PINS_ARDUINO_H_
#define _PINS_ARDUINO_H_

// API compatibility
#include "variant.h"
#include "PinNames.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Libc porting layers
 */
#if defined (  __GNUC__  ) /* GCC CS3 */
#    include <syscalls.h> /** RedHat Newlib minimal stub */
#endif

#define NOT_AN_INTERRUPT            NC // -1

#define NUM_DIGITAL_PINS            DEND
#define NUM_ANALOG_INPUTS           (AEND-A0)

// Convert an analog pin number to a digital pin number
// Used by analogRead api to have A0 == 0
#define analogInputToDigitalPin(p)  ((p < NUM_ANALOG_INPUTS) ? (p+A0) : p)
// All pins could manage EXTI
#define digitalPinToInterrupt(p)    ((uint32_t) p)

#define digitalPinHasI2C(p)         (pin_in_pinmap(p, PinMap_I2C_SDA) ||\
                                     pin_in_pinmap(p, PinMap_I2C_SCL))
#define digitalPinHasPWM(p)         (pin_in_pinmap(p, PinMap_PWM))
#define digitalPinHasSerial(p)      (pin_in_pinmap(p, PinMap_UART_RX) ||\
                                     pin_in_pinmap(p, PinMap_UART_TX))
#define digitalPinHasSPI(p)         (pin_in_pinmap(p, PinMap_SPI_MOSI) ||\
                                     pin_in_pinmap(p, PinMap_SPI_MISO) ||\
                                     pin_in_pinmap(p, PinMap_SPI_SCK))


#define digitalPinToPort(p)         (STM_GPI_PORT(p)->ODR)
#define digitalPinToBitMask(p)      (STM_GPIO_PIN(p))

#define digitalPinIsValid(p)        (TRUE)

#ifdef __cplusplus
}
#endif

#endif /*_PINS_ARDUINO_H_*/
