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
/*                                          С��ߴߴ�Ƽ���Ʒ                                          */
/*                                         www.xiaojijiji.com                                         */
/*   ----------------------------------------------------------------------------------------------   */
/* ************************************************************************************************** */
/* ************************************************************************************************** */
/* ************************************************************************************************** */
/* ************************************************************************************************** */
/*   -----------------------------------------------------------------------------------------------  */
/*	                     ��л��֧��С��ߴߴ�Ƽ��������ر���Э�飬�������ߵ��Ͷ��ɹ���                 */
/*                                  δ�������벻Ҫ�����ϡ����봫�����˻�������	                      */
/*                                             �����ڲ�ʹ��                                           */
/* ************************************************************************************************** */


int main(void)
{

	Clock_Init();
	NVIC_Configuration();		//�ж�����
	delay_init();
	USART1_Init(115200);		//USART1��ʼ��,������115200

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


/*	ͷ�ļ�·��
.\CORE;..\FWLib\inc;.\INCLUDE
*/
