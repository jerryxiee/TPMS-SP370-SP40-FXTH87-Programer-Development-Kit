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



#include "Reg_SP37.h"
#include "SP37_ROMLibrary.h"
#include <uart.h>
#include <SP37.h>
#include <RF.h>
#include <LF.h>

#include <absacc.h>		//���Ե�ַ���ʰ���ͷ�ļ�


/* ***************************************************************************** */
/* ������ΪLF�������ģʽ��ֻ��Wakeup IDƥ���ʱ��Żỽ��                       */
/* Wakeup IDȡ����"LF����Դ�����ID"                                             */
/* LF ����ĵ���ο�"SP37_LF_v1.0.pdf","SP37_Datasheet_V1.0.pdf"                 */
/* �ĵ�λ��"SP37 �������"����"SP37 оƬ�����ֲ�"                                */
/* ***************************************************************************** */

void MAIN(void)
{
	unsigned char store_wuf;
	
	Uart_Init();

	store_wuf = WUF;						//��¼����Դ
	printf("Power On,WUF = %02X\r\n",(int)store_wuf);	//ÿ��PowerOnʱprintf WUF��ֵ

	if(store_wuf == 0x00){			//��һ���ϵ��ʱ��,��������
															//��һ���ϵ��ʱ��WUF = 0x00
		LF_Configure_Telegram();	
	}
	if(store_wuf & 0x04){
		printf("LF Wake Up For Pattern 0...\r\n");	//���Ļ���
	}

	Powerdown();
}
