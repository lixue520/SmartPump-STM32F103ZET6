#include "led.h"
#include "SysTick.h"

/*******************************************************************************
 * 函 数 名         : LED_Init
 * 函数功能		   : LED初始化函数
 * 输    入         : 无
 * 输    出         : 无
 *******************************************************************************/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; // 定义结构体变量
	RCC_APB2PeriphClockCmd(LED1_PORT_RCC | LED2_PORT_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = LED1_PIN; // 选择你要设置的IO口
	/**
	 * GPIO_Mode_Out_PP 是指将 GPIO 端口设置为推挽输出模式，其中输出电平只有高低两种。
	 * 它的特点是：当一个电平时间超过一定的阈值后，会驱动上拉或下拉电阻，从而将端口对应
	 * 电平保持较长时间。
	 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 设置传输速率
	GPIO_Init(LED1_PORT, &GPIO_InitStructure);		  /* 初始化GPIO */
	GPIO_SetBits(LED1_PORT, LED1_PIN);				  // 将LED端口拉高，熄灭所有LED
	GPIO_InitStructure.GPIO_Pin = LED2_PIN;			  // 选择你要设置的IO口
	GPIO_Init(LED2_PORT, &GPIO_InitStructure);		  /* 初始化GPIO */
	GPIO_SetBits(LED2_PORT, LED2_PIN);				  // 将LED端口拉高，熄灭所有LED
	init_GPIO_PA11(); // 初始化PA11引脚
}

// 初始化PA11引脚
void init_GPIO_PA11(void)
{ // 配置GPIOA口
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA, GPIO_Pin_11);//IN+
	// GPIO_ResetBits(GPIOA, GPIO_Pin_15);//IN-,当两者都是低电平时电机动，两者相异则不动
}



// 设置PA11端口输出高电平
void set_GPIO_PA11_high(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_11);
}

// 设置PA11端口输出低电平
void set_GPIO_PA11_low(void)
{
	GPIO_ResetBits(GPIOA, GPIO_Pin_11);
}

void Work_signal_lamp(u8 i)
{
	i++;
	if (i % 20 == 0)
	{
		LED1 = !LED1;
	}

	delay_ms(10);
}
