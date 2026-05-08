#include "stm32f10x.h"                  // Device header

#include "stm32f10x.h"

#include "delay.h"

#include "my_gpio.h"

#include "delay.h"

#include "my_usart.h"


int main(void) {
    // 1. 系统及外设初始化
    My_USART_Init(115200); // 初始化串口
    
    Delay_ms(1000);        // 等待传感器稳定
    
    printf("\r\nSystem Ready!\r\n");
    
    // 2. 定义时间与地点变量 (使用英文或拼音避免乱码)
    char current_time[] = "2026-05-08 Fri"; // 对应：2026-05-08 星期五
    char location[] = "Guangdong - Guangzhou"; // 对应：广东省 广州市

    while (1) {
        // 3. 读取温湿度
       
        
       
            // 4. 打印组合信息
            printf("==================================\r\n");
            printf("Time: %s\r\n", current_time);
            printf("Loc : %s\r\n", location);
           
            printf("==================================\r\n");
        
        
        Delay_ms(2000); // DHT11 采样间隔至少 1 秒，这里设为 2 秒
    }
}