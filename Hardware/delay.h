#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"

void Delay_Soft(uint32_t nCount);
void Delay_us(uint32_t nUs);
void Delay_ms(uint32_t nMs);
void Delay_s(uint32_t nS);

#endif