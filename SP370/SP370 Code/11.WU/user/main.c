/* ************************************************************************************************** */
/* ************************************************************************************************** */
/* ************************************************************************************************** */
/* ************************************************************************************************** */
/*   ----------------------------------------------------------------------------------------------   */
/*                                          小鸡叽叽科技出品		                                  		*/
/*                                         www.xiaojijiji.com		                                  		*/
/*   ----------------------------------------------------------------------------------------------   */
/* ************************************************************************************************** */
/* ************************************************************************************************** */
/* ************************************************************************************************** */
/* ************************************************************************************************** */
/*   -----------------------------------------------------------------------------------------------  */
/*	                     感谢您支持小鸡叽叽科技，请遵守保密协议，保护作者的劳动成果，                 */
/*                                  未经允许请不要将资料、代码传送他人或者网络	                      */
/*																		         仅供内部使用                                           */
/* ************************************************************************************************** */




#include "Reg_SP37.h"
#include "SP37_ROMLibrary.h"
#include <uart.h>
#include <stdio.h>
#include <ctype.h>

void MAIN(void)
{
	if(WUF == 0x00){		//第一次上电的时候,进行配置
											//第一次上电的时候WUF = 0x00
		
		GPR6 = 100;				//此处寄存器GPR6初始化为100
		Uart_Init();
	}

	
	GPR6++;							//通用寄存器用于存储数据，数据在Powerdown期间不丢失
											//所以通用寄存器可以用来保存一些值,用于前后比较等作用
											//此处的通用寄存器GPR6 每唤醒一次进行+1操作
											//备注通用寄存器GPR1、GPR2、GPR3可以通过bit的方式来操作
											//即GPR1、GPR2、GPR3可以利用sbit来定义某一个bit
	
	printf("GPR6 = %d\r\n",(int)GPR6);

	//2kHz RC LP Oscillator
	//Interval Wakeup 时间到产生Wakeup信号
	//SP37_Datasheet_V1.0		Page:43
	//Intervaltimerperiod[s] = timebase[s] * postcounter[ITPR]
	ITPR = 100;																//这里是对2Khz进行100分频(SP370内部LC震荡频率为2Khz)
	ITPH = 0;
	ITPL = 100;																//TIPH ITPL是计数器的高地址与低地址
																						//这里设置为100  -->  即5秒
																						//  100 / (2000 / 100) = 5

	Powerdown();		//进入休眠,等待ITP时间到唤醒(Powerdown期间功耗最低)
}




