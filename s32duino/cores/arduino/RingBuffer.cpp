/*
  Copyright (c) 2014 Arduino.  All right reserved.

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

#include "RingBuffer.h"
#include <string.h>

RingBuffer::RingBuffer( void )
{
	memset( (void *)_aucBuffer, 0, SERIAL_BUFFER_SIZE ) ;
	_iHead=0 ;
	_iTail=0 ;
}

void RingBuffer::store_char( uint8_t c )
{
	uint8_t i = nextIndex(_iHead);

	// if we should be storing the received character into the location
	// just before the tail (meaning that the head would advance to the
	// current location of the tail), we're about to overflow the buffer
	// and so we don't write the character or advance the head.
	if ( i != _iTail )
	{
		_aucBuffer[_iHead] = c ;
		_iHead = i ;
	}
}

void RingBuffer::clear(void)
{
	_iHead = 0;
	_iTail = 0;
}

bool RingBuffer::available(){
	int16_t delta = _iHead - _iTail;

	if(delta < 0)
		return SERIAL_BUFFER_SIZE + delta;
	else
		return delta;
}


int16_t RingBuffer::peek()
{
	if(_iTail == _iHead)
		return -1;

	return _aucBuffer[_iTail];
}

uint8_t RingBuffer::nextIndex(uint8_t index)
{
	return (uint32_t)(index + 1) % SERIAL_BUFFER_SIZE;
}


int16_t RingBuffer::read_char()
{
	if(_iTail == _iHead)
		return -1;

	uint8_t value = _aucBuffer[_iTail];
	_iTail = nextIndex(_iTail);

	return value;
}


bool RingBuffer::isFull()
{
	return (nextIndex(_iHead) == _iTail);
}
