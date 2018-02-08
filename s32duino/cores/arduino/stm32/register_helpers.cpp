#include "register_helpers.h"

void setGPIOMODER(uint32_t p, uint8_t mode)
{
	STM_PORT(p)->MODER = (STM_PORT(p)->MODER & ~(0b11 << (STM_PIN(p) * 2))) | (mode << (STM_PIN(p) * 2));
}

void setGPIOAFR(uint32_t p, uint8_t af)
{
	STM_PORT(p)->AFR[STM_PIN(p) >> 3] = (STM_PORT(p)->AFR[STM_PIN(p) >> 3] & ~(0xF << ((STM_PIN(p) & 0b111) * 4)))
		| (af << ((STM_PIN(p) & 0b111) * 4));
}

uint8_t getGPIOMODER(uint32_t p)
{
	return (STM_PORT(p)->MODER >> (STM_PIN(p) * 2)) & 0b11;
}

void setGPIOPUPDR(uint32_t p, uint8_t mode)
{
	STM_PORT(p)->PUPDR = (STM_PORT(p)->PUPDR & (0b11 << (STM_PIN(p) * 2))) | (mode << (STM_PIN(p) * 2));
}
