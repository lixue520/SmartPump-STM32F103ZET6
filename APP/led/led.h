#ifndef _led_H
#define _led_H

#include "system.h"

/*  LEDʱ�Ӷ˿ڡ����Ŷ��� */
#define LED1_PORT 			GPIOB   
#define LED1_PIN 			GPIO_Pin_5
#define LED1_PORT_RCC		RCC_APB2Periph_GPIOB

#define LED2_PORT 			GPIOE   
#define LED2_PIN 			GPIO_Pin_5
#define LED2_PORT_RCC		RCC_APB2Periph_GPIOE


#define LED1 PBout(5)  	
#define LED2 PEout(5)  	


void LED_Init(void);
void Work_signal_lamp(u8 i);
void init_GPIO_PA11(void);
// 设置PA11端口输出高电平
void set_GPIO_PA11_high(void);

// 设置PA11端口输出低电平
void set_GPIO_PA11_low(void);

#endif
