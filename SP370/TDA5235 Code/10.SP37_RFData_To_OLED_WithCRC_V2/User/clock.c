#include "sys.h"
#include "clock.h"


//配置为内部时钟
//倍频到64Mhz

//********************//
//使用内部时钟修改的地方
//1.最大到64M
//2.flash配置
//3.屏蔽掉startup_stm32f10x_md.s --> SystemInit(屏蔽其时钟配置)
//4.修改system_stm32f10x.c       --> define SYSCLK_FREQ_72MHz  64000000
//	以适应Delay等函数
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



	RCC_DeInit();//将外设 RCC寄存器重设为缺省值
	
	RCC_HSICmd(ENABLE);//使能HSI  
	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);		//等待HSI使能成功

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

