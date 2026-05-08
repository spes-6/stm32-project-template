#include "delay.h"

// 基础软件延时
void Delay_Soft(uint32_t nCount)
{
    for (; nCount != 0; nCount--)
    {
        __nop(); 
    }
}

// 粗略的微秒级延时
void Delay_us(uint32_t nUs)
{
    uint32_t i;
    while(nUs--)
    {
        for(i = 0; i < 10; i++); 
    }
}

// 粗略的毫秒级延时
void Delay_ms(uint32_t nMs)
{
    while(nMs--)
    {
        Delay_us(1000);
    }
}

// 粗略的秒级延时
void Delay_s(uint32_t nS)
{
    while(nS--)
    {
        Delay_ms(1000);
    }
}