#include "system.h"
#include "SysTick.h"
#include "usart.h"
#include "key.h"
#include "lcdshowinit.h" //基础显示频
#include "adc.h"
#include "water.h"
#include "waterflow.h"
#include "led.h"
#include "tftlcd.h"
#include "beep.h"
#include "string.h"
#include "led.h"
#include "waterpump.h"
extern float flow_rate; // 外引变量：水流量


int main()
{

    u8 key, i;			  // button用于记录按键下的次数，这里在rest时会清零。
    // u16 color = 0;
    u16 button, temp_z, temp_x = 0; // 计数器，整数部分，小数部分。
    float temp = 0;					// 液位
    u8 my_str[100];
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 中、断优先级分组 分2组

    //BEEP_Init();
    KEY_Init();
    SysTick_Init(72);
    pump_init(); // 关于水泵

    LED_Init(); // LED初始化
    USART1_Init(115200);//串口1，打印信息用
    Usart2_Init(115200);//串口2，驱动ESP8266用
    TFTLCD_Init();		 // LCD初始化
    New_Lcd_Show_Init(); // 变量初始化与布局
    Adc_Init();			 // ADC采集初始化，用于液位、烟雾、流量计。
    UsartPrintf(USART_DEBUG, " Hardware init OK\r\n");
    pump_stop_1();
    pump_stop_2();

    while (1)
    {

#if 1
        // Get_LiquidHeight(); // 输出液位深度
        key = KEY_Scan(0); // 扫描按键
        switch (key)
        {
        case KEY_UP_PRESS:
            break;
        case KEY1_PRESS://水泵1开，水泵2关
            LED2 = 0;
            pump_start_1();
            pump_stop_2();
            button--;
            u16_to_string(button_count(button), my_str);
            LCD_ShowString(60 + 60, 10 + 30, tftlcd_data.width, tftlcd_data.height, 24, my_str);
            break; // 熄灭D2指示灯,降下液位
        case KEY2_PRESS://水泵1关，水泵2开
            pump_start_2();
            pump_stop_1();
            button++;
            u16_to_string(button_count(button), my_str);
            LCD_ShowString(60 + 60, 10 + 30, tftlcd_data.width, tftlcd_data.height, 24, my_str);
            break; // 蜂鸣器开关---->改成计数器，用LCD显示动态数据，升液位
        case KEY0_PRESS://水泵1，2关
            pump_stop_1();
            pump_stop_2();
            if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 0)
            {
                printf("\r\n有水1");
                LED1 = 0; // D2指示灯亮
            }
            else
            {
                printf("\r\n无水1");
                LED1 = 1; // D2指示灯灭
            }
            temp = Get_LiquidHeight();			// 输出液位深度，float
            temp_z = temp;						// 取整数部分
            temp_x = (temp - temp_z) * 1000;	// 取小数部分,保留三位有效数字
            u16_to_string(temp_z, my_str);
            LCD_ShowString(60 + 60, 10 + 30, tftlcd_data.width, tftlcd_data.height, 24, my_str);
            LCD_ShowString(60 + 60 + 30, 10 + 30, tftlcd_data.width, tftlcd_data.height, 24, ".");

            u16_to_string(temp_x, my_str);
            LCD_ShowString(60 + 60 + 20 * 2.5, 10 + 30, tftlcd_data.width, tftlcd_data.height, 24, my_str);
            LCD_ShowString(60 + 60 + 20 * 4.5, 10 + 30, tftlcd_data.width, tftlcd_data.height, 24, "mm");

            break; // 蜂鸣器关闭
        }
#endif

        //Work_signal_lamp(i); // 信号工作灯显示
    }
}
