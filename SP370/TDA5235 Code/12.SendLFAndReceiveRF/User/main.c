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
/*   ----------------------------------------------------------------------------------------------   */
/*                       感谢您支持小鸡叽叽科技，请遵守保密协议，保护作者的劳动成果                   */
/*                                  未经允许请不要将资料、代码传送他人或者网络                        */
/*                                           仅供内部使用                                             */
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
/* 此例程验证SP370的LF与RF功能                                                   */
/* 上电后不断发射"符合SP370"的报文(10Hz)                                         */
/* Wakeup ID为0x1234                                                             */
/* 每一个报文发送8Byte数据0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77                */
/* 如果有接收到来自SP370的RF数据，将在屏幕上显示,并且Printf接收到的数据          */
/* ***************************************************************************** */

int main(void)
{
	Clock_Init();
	NVIC_Configuration();		//中断配置
	delay_init();
	LED_Init();
	USART1_Init(115200);		//USART1初始化,波特率115200	

	Tim3_Init(1000,64); 		//1ms的溢出中断 //系统灯闪烁
	TIM3_Cmd(ENABLE);

	LF_Init();

	OLED_Init(); 
 
	Display_Logo();  
	Display_Http();
	Display_Version();  

	//Display_User_ID_NULL();
	Display_Unique_ID_NULL();
	Display_RF_Receive_Mark();

	Display_Pressure(0); 
	Display_Temperature(0);
	Display_Acceleration(0);
	Display_Voltage(0);

	TDA5235_Init();
	TDA5235_SFR_Init();
	
	while(1)
	{
		u16 ID = 0x1234;
		u8 data[] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77};

		//LF数据
		//这里200ms进行LF一包数据
		if(time_1ms%200){
			LF_SendATelegram(ID,data,sizeof(data)/sizeof(data[0]));
		}
		
		//如果有接收到数据,进行处理
		if(TDA5235_FIFO_NUM){
			PT_SP37_RF_DATA pt_SP37Data = (PT_SP37_RF_DATA)TDA5235_FIFO;

			LED_ReceiveReverse();		//STATUS灯闪烁
			Display_RF_Receive_Count_Plus();
			Display_Logo_Move();

			//Display_User_ID(pt_SP37Data->IDH,pt_SP37Data->IDL);
			Display_Unique_ID(pt_SP37Data->UniqueID);
			Display_Tyre_Position(pt_SP37Data->TyrePosition);
			Display_Pressure(SP37_Cal_Pressure_V2(pt_SP37Data->Pressure));
			Display_Temperature(SP37_Cal_Temperature(pt_SP37Data->Temperature));
			Display_Acceleration(SP37_Cal_Acceleration(pt_SP37Data->Acceleration));
			Display_Voltage(SP37_Cal_Voltage(pt_SP37Data->Voltage));

			printf("*****************************\r\n");
			printf("Get a message from SP370:\r\n");
			printf("UniqueID:    %02X%02X%02X%02X\r\n",	pt_SP37Data->UniqueID[0],
														pt_SP37Data->UniqueID[1],
														pt_SP37Data->UniqueID[2],
														pt_SP37Data->UniqueID[3]);
			printf("TyrePosition:%d\r\n",pt_SP37Data->TyrePosition);
			printf("Pressure:    %f\r\n",SP37_Cal_Pressure_V2(pt_SP37Data->Pressure));
			printf("Temperature: %f\r\n",SP37_Cal_Temperature(pt_SP37Data->Temperature));
			printf("Acceleration:%f\r\n",SP37_Cal_Acceleration(pt_SP37Data->Acceleration));
			printf("Voltage:     %f\r\n",SP37_Cal_Voltage(pt_SP37Data->Voltage));
			printf("*****************************\r\n");
			TDA5235_FIFO_NUM = 0;	//清零
		}
	}


}


/*	头文件路径
.\CORE;..\FWLib\inc;.\INCLUDE
*/

