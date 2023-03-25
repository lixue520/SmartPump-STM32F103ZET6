#include "led.h"
#include "SysTick.h"

/*******************************************************************************
 * �� �� ��         : LED_Init
 * ��������		   : LED��ʼ������
 * ��    ��         : ��
 * ��    ��         : ��
 *******************************************************************************/
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; // ����ṹ�����
	RCC_APB2PeriphClockCmd(LED1_PORT_RCC | LED2_PORT_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = LED1_PIN; // ѡ����Ҫ���õ�IO��
	/**
	 * GPIO_Mode_Out_PP ��ָ�� GPIO �˿�����Ϊ�������ģʽ�����������ƽֻ�иߵ����֡�
	 * �����ص��ǣ���һ����ƽʱ�䳬��һ������ֵ�󣬻������������������裬�Ӷ����˿ڶ�Ӧ
	 * ��ƽ���ֽϳ�ʱ�䡣
	 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // �����������ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // ���ô�������
	GPIO_Init(LED1_PORT, &GPIO_InitStructure);		  /* ��ʼ��GPIO */
	GPIO_SetBits(LED1_PORT, LED1_PIN);				  // ��LED�˿����ߣ�Ϩ������LED
	GPIO_InitStructure.GPIO_Pin = LED2_PIN;			  // ѡ����Ҫ���õ�IO��
	GPIO_Init(LED2_PORT, &GPIO_InitStructure);		  /* ��ʼ��GPIO */
	GPIO_SetBits(LED2_PORT, LED2_PIN);				  // ��LED�˿����ߣ�Ϩ������LED
	init_GPIO_PA11(); // ��ʼ��PA11����
}

// ��ʼ��PA11����
void init_GPIO_PA11(void)
{ // ����GPIOA��
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA, GPIO_Pin_11);//IN+
	// GPIO_ResetBits(GPIOA, GPIO_Pin_15);//IN-,�����߶��ǵ͵�ƽʱ����������������򲻶�
}



// ����PA11�˿�����ߵ�ƽ
void set_GPIO_PA11_high(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_11);
}

// ����PA11�˿�����͵�ƽ
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
