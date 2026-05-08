#include "dht11.h"
#include "my_gpio.h"
#include "delay.h"

// DHT11 初始化：拉高总线，进入空闲状态
void DHT11_Init(void) {
    My_GPIO_Init(DHT11_PORT, DHT11_PIN, GPIO_MODE_OUT_PP, GPIO_Speed_50MHz);
    My_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_STATE_SET);
}

// 从 DHT11 读取 1 个字节
static uint8_t DHT11_ReadByte(void) {
    uint8_t i, byte = 0;
    for (i = 0; i < 8; i++) {
        // 等待 50us 低电平过去 (DHT11 拉低 50us 表示数据开始)
        while (My_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == 0);
        
        // 延时 40us 后判断电平：
        // 如果此时还是高电平，说明是 '1' (高电平持续 70us)
        // 如果此时变为低电平，说明是 '0' (高电平持续 26-28us)
        Delay_us(40); 
        
        byte <<= 1;
        if (My_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == 1) {
            byte |= 1;
        }
        
        // 等待剩余的高电平结束，为下一位数据读取做准备
        while (My_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == 1);
    }
    return byte;
}

// 读取温湿度数据 (temp: 温度整数, humi: 湿度整数)
// 返回值: DHT11_OK (0) 表示成功, DHT11_ERROR (1) 表示失败
uint8_t DHT11_ReadData(uint8_t *temp, uint8_t *humi) {
    uint8_t buf[5]; // 修正：这里必须定义为数组才能存储 5 个字节的数据
    uint8_t i;
    
    // 1. 主机发送起始信号
    My_GPIO_Init(DHT11_PORT, DHT11_PIN, GPIO_MODE_OUT_PP, GPIO_Speed_50MHz);
    My_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_STATE_RESET); // 拉低总线
    Delay_ms(20); // 拉低至少 18ms
    My_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_STATE_SET);  // 拉高总线
    Delay_us(30); // 拉高 20-40us
    
    // 2. 切换为输入模式，准备接收响应
    My_GPIO_Init(DHT11_PORT, DHT11_PIN, GPIO_MODE_IPU, GPIO_Speed_50MHz); 
    
    // 3. 等待 DHT11 响应 (80us 低电平 + 80us 高电平)
    // 检查 DHT11 是否拉低了总线 (如果没拉低，说明没有响应)
    if (My_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == 1) {
        return DHT11_ERROR;
    }
    
    // 等待 80us 低电平过去
    while (My_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == 0);
    
    // 等待 80us 高电平过去
    if (My_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == 1) {
        while (My_GPIO_ReadPin(DHT11_PORT, DHT11_PIN) == 1);
    } else {
        return DHT11_ERROR; // 响应信号异常
    }

    // 4. 循环读取 40 位数据 (5 字节)
    for (i = 0; i < 5; i++) {
        buf[i] = DHT11_ReadByte();
    }

    // 5. 校验数据 (湿度整数+湿度小数+温度整数+温度小数 = 校验和)
    // DHT11 的小数部分通常为 0，所以这里只返回整数部分
    if (buf[0] + buf[1] + buf[2] + buf[3] == buf[4]) {
        *humi = buf[0]; // 湿度整数
        *temp = buf[2]; // 温度整数
        return DHT11_OK;
    }
    
    return DHT11_ERROR;
}