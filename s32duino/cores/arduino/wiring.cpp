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

volatile uint32_t uwTick;
uint32_t millis( void )
{
	return uwTick;
}

// Interrupt-compatible version of micros
uint32_t micros( void )
{
	uint32_t m0 = millis();
	uint32_t u0 = SysTick->LOAD - SysTick->VAL;
	uint32_t m1 = millis();
	uint32_t u1 = SysTick->LOAD - SysTick->VAL;

	if (m1 > m0) {
		return ( m1 * 1000 + (u1 * 1000) / SysTick->LOAD);
	} else {
		return ( m0 * 1000 + (u0 * 1000) / SysTick->LOAD);
	}
}

void delay( uint32_t ms )
{
	if (ms == 0)
		return;
	uint32_t start = millis();
	do {
		yield();
	} while (millis() - start < ms);
}
extern "C" {
	void SysTick_Handler(void)
	{
		uwTick++;
	}

#if defined ( __ICCARM__ ) /* IAR Ewarm 5.41+ */
	extern signed int putchar( signed int c ) ;
/**
 * \brief
 *
 * \param c  Character to output.
 *
 * \return The character that was output.
 */
	extern WEAK signed int putchar( signed int c )

		return c ;
}
#endif /* __ICCARM__ */
}
