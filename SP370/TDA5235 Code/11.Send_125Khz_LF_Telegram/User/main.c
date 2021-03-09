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
/*   ----------------------------------------------------------------------------------------------   */
/*                       ��л��֧��С��ߴߴ�Ƽ��������ر���Э�飬�������ߵ��Ͷ��ɹ�                   */
/*                                  δ�������벻Ҫ�����ϡ����봫�����˻�������                        */
/*                                           �����ڲ�ʹ��                                             */
/* ************************************************************************************************** */


#include "sys.h"
#include "clock.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "tim.h"

#include "oled.h"
#include "display.h"

#include "TDA5235.h"
#include "TDA5235_SFR.h"

#include "SP37Data.h"

#include "lf.h"

/* ***************************************************************************** */
/* ��������֤SP370��LF����                                                       */
/* �ϵ�󲻶Ϸ���"����SP370"�ı���(10Hz)                                         */
/* Wakeup IDΪ0x1234                                                             */
/* ÿһ�����ķ���8Byte����0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77                */
/* ***************************************************************************** */

int main(void)
{

	Clock_Init();
	NVIC_Configuration();		//�ж�����
	delay_init();
	LED_Init();
	USART1_Init(115200);		//USART1��ʼ��,������115200	

	Tim3_Init(1000,64); 		//1ms������ж� //ϵͳ����˸
	TIM3_Cmd(ENABLE);

	LF_Init();


	OLED_Init(); 
 
	Display_Logo();  
	Display_Http();
	Display_Version();

	OLED_ShowBMP(0,2,1);	//���Ͻ� Logo
	OLED_ShowBMP(110,2,0);	//���Ͻ� Logo
	OLED_ShowBMP(0,6,1);	//���½� Logo
	OLED_ShowBMP(110,6,0);	//���½� Logo

	//OLED_ShowStr(VERSION_START_X,VERSION_START_PAGE," .Send 125Khz LF. ");
	OLED_ShowStr(6,4,"Send 125Khz LF TEST");
	OLED_ShowStr(6,5,"     ID:0x1234    ");
	
	while(1)
	{
		u16 ID = 0x1234;
		u8 data[] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77};
		
		LF_SendATelegram(ID,data,sizeof(data)/sizeof(data[0]));
		delay_ms(100);
	}
}


/*	ͷ�ļ�·��
.\CORE;..\FWLib\inc;.\INCLUDE
*/
