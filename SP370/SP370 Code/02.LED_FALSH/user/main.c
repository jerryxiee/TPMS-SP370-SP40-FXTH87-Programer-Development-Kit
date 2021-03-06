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

//程序在PP0,PP1,PP2管教出产生方波
void MAIN(void)
{
	P1DIR = 0x00;			//PP0,PP1,PP2配置为输出
	P1OUT &= ~((1<<0) | (1<<1) | (1<<2));			//管脚配置为低电平
	P1SENS &= ~0xFF;	//上拉电阻
	
	while(1)
	{
		P1OUT &= ~((7<<0));
		Wait100usMultiples(5000);		//调用库函数 延时5000*100us = 500ms
																//此延时函数，最大延时时间为watchdog timer
																//也就是最大1.7秒

		P1OUT |= (7<<0);
		Wait100usMultiples(5000);
	}
}



