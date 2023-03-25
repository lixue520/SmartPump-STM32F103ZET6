#include "waterpump.h"
/*
* PE口和PA13口永远动不了电平
*/
void pump_init()
{
    
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_11; // PA12和PA13口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
    GPIO_ResetBits(GPIOA, GPIO_Pin_12); 
    GPIO_ResetBits(GPIOA, GPIO_Pin_11); 
	
}

void pump_start_1()
{
    GPIO_SetBits(GPIOA, GPIO_Pin_11);	// IN+:1
}

void pump_stop_1()
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_11); // IN-:0
}

void pump_start_2() {
    GPIO_SetBits(GPIOA, GPIO_Pin_12);	// IN+:1
   
}
void pump_stop_2() {
    GPIO_ResetBits(GPIOA, GPIO_Pin_12); // IN-:0
}