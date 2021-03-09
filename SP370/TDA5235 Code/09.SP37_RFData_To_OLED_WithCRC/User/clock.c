#include "sys.h"
#include "clock.h"


//����Ϊ�ڲ�ʱ��
//��Ƶ��64Mhz

//********************//
//ʹ���ڲ�ʱ���޸ĵĵط�
//1.���64M
//2.flash����
//3.���ε�startup_stm32f10x_md.s --> SystemInit(������ʱ������)
//4.�޸�system_stm32f10x.c       --> define SYSCLK_FREQ_72MHz  64000000
//	����ӦDelay�Ⱥ���
//********************//

void Clock_Init(void)
{
	/*
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);
	while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) != SET);

	RCC_PLLConfig(RCC_PLLSource_HSE_Div2,RCC_PLLMul_9);
	RCC_PLLCmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET);

	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	while(RCC_GetSYSCLKSource() != 0x08);

	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div2);
	RCC_PCLK2Config(RCC_HCLK_Div1);
	RCC_ADCCLKConfig(RCC_PCLK2_Div2);
	*/



	RCC_DeInit();//������ RCC�Ĵ�������Ϊȱʡֵ
	
	RCC_HSICmd(ENABLE);//ʹ��HSI  
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);		//�ȴ�HSIʹ�ܳɹ�

	FLASH_SetLatency(FLASH_Latency_2);
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

	RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_16);
	RCC_PLLCmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET);

	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	while(RCC_GetSYSCLKSource() != 0x08);

	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div2);
	RCC_PCLK2Config(RCC_HCLK_Div1);
	RCC_ADCCLKConfig(RCC_PCLK2_Div2);
}

