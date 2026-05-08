#ifndef __DHT11_H
#define __DHT11_H
#include "stm32f10x.h"

// DHT11 读取状态码
#define DHT11_OK 0
#define DHT11_ERROR 1

// 假设 DHT11 接在 PA1 引脚，你可以根据实际接线修改
#define DHT11_PORT GPIOA
#define DHT11_PIN  GPIO_Pin_1

void DHT11_Init(void);
uint8_t DHT11_ReadData(uint8_t *temp, uint8_t *humi);

#endif
