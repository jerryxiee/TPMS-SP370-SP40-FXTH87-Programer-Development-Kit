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


void MAIN(void)
{
	signed char StatusByte;
	unsigned char idata descriptorPtr[] = {
		0x00,												//START of TABLE
		0x00,												//TYPE
		
		8*13+8*1+8*8,								//WAKE UP + SYNS + DATA

		0x00,0x00,0x00,0x00,0x00,		//WAKE UP
		0x00,0x00,0x00,0x00,0x00,		
		0x00,0x00,0x00,	
		
		0x15,		//SYNS

		0x12,		//DATA
		0x34,
		0x56,
		0x78,
		0xAA,
		0xBB,
		0xCC,
		0xDD,
		
		0xF1,
	};

	//���ڳ�ʼ��
	Uart_Init();

	//����RF
	//Data not inverted | ASK modulation | 433MHz | 3 PA output stages
	//RFTX = (1<<7) | (1<<5) | (1<<2) | (3<<0);
	// FSK switch open, FSK with internal pulling capacitors, data inv., 433.92 MHz, 1PA stages
	RFTX = (0<<7) | (1<<6) | (0<<5) | (1<<2) | (0<<0);

	//XTAL1 = 0x7F;				// +/- 35kHz Deviation
	//XTAL0 = 0x17;	;	

	XTAL1 = 0xFF;				// +/- 35kHz Deviation
	XTAL0 = 0x0;	;	

	StopXtalOsc();		//�رվ����������´�
	//signed char StartXtalOsc(unsigned char Delay)
	StatusByte = StartXtalOsc(33);
	if(!StatusByte)
		printf("XTAL started and delay passed\r\n");
	else
	{
		printf("XTAL already on (no action)\r\n");
	}

	//signed char VCO_Tuning(void)
	StatusByte = VCO_Tuning();
	if(!StatusByte)
		printf("Success of VCO Tuning\r\n");
	else
	{
		printf("VCO Tuning ERROR\r\n");
		return;
	}	

	while(1)
	{
		WDRES = 1;
		StatusByte = Send_RF_Telegram(2000,descriptorPtr);
		
		if(!StatusByte)
			printf("Success to Send_RF_Telegram\r\n");
		else
			printf("Sorry Send_RF_Telegram ERROR\r\n");
	
		Wait100usMultiples(100);
		WDRES = 1;
	}
}




