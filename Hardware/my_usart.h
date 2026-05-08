#ifndef __MY_USART_H
#define __MY_USART_H
#include "stm32f10x.h"
#include <stdio.h> // 引入 stdio.h 以支持 printf

//   此默认使用pa9&pa10
void My_USART_Init(uint32_t baudrate);
#endif