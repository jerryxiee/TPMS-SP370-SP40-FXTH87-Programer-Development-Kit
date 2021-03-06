#include "sys.h"
#include "clock.h"
#include "delay.h"
#include "usart.h"

#include "led.h"

#include "oled.h"
#include "display.h"


/* ************************************************************************************************** */
/* ************************************************************************************************** */
/* ************************************************************************************************** */
/* ************************************************************************************************** */
/*   ----------------------------------------------------------------------------------------------   */
/*                                          小鸡叽叽科技出品                                          */
/*                                         www.xiaojijiji.com                                         */
/*   ----------------------------------------------------------------------------------------------   */
/* ************************************************************************************************** */
/* ************************************************************************************************** */
/* ************************************************************************************************** */
/* ************************************************************************************************** */
/*   -----------------------------------------------------------------------------------------------  */
/*	                     感谢您支持小鸡叽叽科技，请遵守保密协议，保护作者的劳动成果，                 */
/*                                  未经允许请不要将资料、代码传送他人或者网络	                      */
/*                                             仅供内部使用                                           */
/* ************************************************************************************************** */


int main(void)
{

	Clock_Init();
	NVIC_Configuration();		//中断配置
	delay_init();
	USART1_Init(115200);		//USART1初始化,波特率115200

	LED_Init();

	OLED_Init(); 
 
	Display_Logo();  
	Display_Http();
	Display_Version();

	
	while(1)
	{
		
		delay_ms(500);		
	}


}


/*	头文件路径
.\CORE;..\FWLib\inc;.\INCLUDE
*/

