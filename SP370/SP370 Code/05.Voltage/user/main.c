/* ************************************************************************************************** */
/* ************************************************************************************************** */
/* ************************************************************************************************** */
/* ************************************************************************************************** */
/*   ----------------------------------------------------------------------------------------------   */
/*                                          С��ߴߴ�Ƽ���Ʒ		                                  		*/
/*                                         www.xiaojijiji.com		                                  		*/
/*   ----------------------------------------------------------------------------------------------   */
/* ************************************************************************************************** */
/* ************************************************************************************************** */
/* ************************************************************************************************** */
/* ************************************************************************************************** */
/*   -----------------------------------------------------------------------------------------------  */
/*	                     ��л��֧��С��ߴߴ�Ƽ��������ر���Э�飬�������ߵ��Ͷ��ɹ���                 */
/*                                  δ�������벻Ҫ�����ϡ����봫�����˻�������	                      */
/*																		         �����ڲ�ʹ��                                           */
/* ************************************************************************************************** */





#include "Reg_SP37.h"
#include "SP37_ROMLibrary.h"
#include <uart.h>
#include <stdio.h>
#include <ctype.h>

idata ID_Struct ID_Result;

void MAIN(void)
{
	unsigned char StatusByte;

	struct{
		signed int Voltage;
		signed int Raw_voltage;
	}idata Volt_Result;

	Uart_Init();

	
	while(1){
		
		WDRES = 1;

		Start_Supply_Voltage();

		Trig_Supply_Voltage();
		
		StatusByte = Get_Supply_Voltage(&Volt_Result.Voltage);

		if(!StatusByte)
		{
			printf("Get_Supply_Voltage OK\r\n");
			printf("The Raw Val is %d,%d\r\n",Volt_Result.Voltage,Volt_Result.Raw_voltage);
			printf("The Voltage is %f v\r\n",Volt_Result.Voltage/8.0/1000);
		}
		else
		{
			printf("Get_Supply_Voltage Error!\r\n");
		}

		//��ʱ1S
		
		Wait100usMultiples(10000);
	}
}



