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

#ifndef _WIRING_TONE_
#define _WIRING_TONE_

#include <stdint.h>
#include "PinNames.h"

#ifdef __cplusplus
extern "C" {
#endif

	extern void tone(PinName _pin, uint32_t _frequency, uint32_t _duration = 0);

	extern void noTone(PinName _pin);

	extern void toneCallback(void);

#ifdef __cplusplus
}
#endif

#endif /* _WIRING_TONE_ */
