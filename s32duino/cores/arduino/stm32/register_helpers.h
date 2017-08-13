#ifndef __GPIO_H
#define __GPIO_H
#include <stdint.h>
#include "PinNamesTypes.h"
#include "stm32_def.h"
void setGPIOMODER(uint32_t p, uint8_t mode);
void setGPIOAFR(uint32_t p, uint8_t af);
void setGPIOPUPDR(uint32_t p, uint8_t mode);
uint8_t getGPIOMODER(uint32_t p);
#endif // __GPIO_H
