#include "Reg_SP37.h"
#include "SP37_ROMLibrary.h"
#include <SP37.h>
#include <LF.h>

#include <absacc.h>		//���Ե�ַ���ʰ���ͷ�ļ�

#include "Reg_SP37.h"
#include "SP37_ROMLibrary.h"
#include <SP37.h>
#include <LF.h>

#include <absacc.h>		//���Ե�ַ���ʰ���ͷ�ļ�

void LF_Configure_Carrier_Detect(void)
{
	LFCDM0 = 0x1C;            //Enable auto-calibration & freeze threshold
	
	LFRX0  = CBYTE[0x580F]; 	//����ѡ����������,����Ӧ��ѹ��С������
                            //��شӵ�ַ0x5810,0X580F,0X580E�������ֵ(��ΪоƬ����ʱ,ԭ�������˽���ֵ)
                            //0x5810: LF-sensitivity = 0.33 ... 3.35 mVpp(���������)
                            //0x580F: LF-sensitivity = 2 ... 11 mVpp
                            //0x580E: LF-sensitivity = 10 ... 50 mVpp(���������)
                            //�˴���ѡ��0x580F,
                            //�����ȹ��߿��ܻᵼ�£����ܻ�����󴥷������绹ûʹ��LF�������ͱ�������
                            //�����ȹ���,��Ҫ��ǿ�ļ���Դ�����߼���Դ��Ҫ �ܿ���
	
	LFRX1  = 0x10;            //����auto-calibrationΪ��� �ز���ģʽ
	LFCDFLT = 0x00;           //����������
                            //�ر��ز����˹��ܣ����Խ���Powerdownʱ�� ����
                            //�˴���ֵҲ��Ҫ�ӵ�ַ0x580D,0x580C,0x580B��ȡ
                            //0x580D: Detector Filter Time = 62...240�gs
                            //0x580C: Detector Filter Time = 500 ... 800�gs
                            //0x580B: Detector Filter Time = 800 ... 1150 �gs
                            //�˴�����Ϊ0x00,�ر��˲�����
	
	WUM &= ~(0x20);           //����LF �����ж�(�ز����)
	LFRXC = 0x04;             //LF Baseband disabled, LF-Receiver enabled
	ITPR  = 0x00;							//�����ڲ���ʱ�����ѣ��޷��رա���ʹ��Ĭ��ֵ��0.5��ͻᱻ����һ��
                            //��Ĭ��ֵ����������ǹ۲�LF���ѵ�״̬
                            //�˴��޸�Ϊ0x00,��ɴ�Լ2min�ᱻ��ʱ������һ��
														
}


void LF_Configure_Telegram(void)
{
	LFPCFG = 0x02;            //Use 16Bit pattern P0 for wakeup(16Bit IDƥ��)
	LFP0H = 0x12;LFP0L = 0x34;//ID�ĸߵ�λ
	
	LFRX1  = 0x30;            //����auto-calibrationΪ��� ���ĵ�ģʽ
	
	WUM &= ~(0x04);           //����LF �����ж� Pattern Match Wakeup
	LFRXC = 0x14;             //LF Baseband enabled, LF-Receiver enabled
	ITPR  = 0x00;             //�����ڲ���ʱ�����ѣ��޷��رա���ʹ��Ĭ��ֵ��0.5��ͻᱻ����һ��
                            //��Ĭ��ֵ����������ǹ۲�LF���ѵ�״̬
                            //�˴��޸�Ϊ0x00,��ɴ�Լ2min�ᱻ��ʱ������һ��
	
	StartXtalOsc(40);         //Start RF quartz oscillator and wait 40x42.67��s
                            //�����ⲿ����ʵ��Ŀ����Ϊ��У׼LF�Ĳ�����(ΪLFBaudrateCalibration��������)
	LFBaudrateCalibration(3906);//���ݴ��䲨����3906Bit/s
	StopXtalOsc();            //�ر��ⲿ����
}

unsigned char LFData[MAX_LF_DATA];

unsigned char LF_DataReceive(void)
{
	unsigned char RECEIVING;
	unsigned char i, index;
	unsigned char store;

	//Clear LF Data Buffer
	for (i = 0; i<MAX_LF_DATA;i++)
		LFData[i] = 0;

	// Now Receive LF Data...
	if (LFRXS & 0x08)         // If Databyte already pending in LFRXD then store it.
		LFData[index++] = LFRXD;

	RECEIVING = TRUE;         // Assume that Bytes will follow
	index = 0;
	while (RECEIVING)         // Loop to receive LF Data
	{
		CFG2 |= 0x02;           // Reset Watchdog
		T0RUN = 0;              // Stop Timer 0
		TMOD = 0x51;            // Set Timermode 1, Systemclock devided by 8, T0 source, T1 source
		TH0  = 0x0C;            // Configure Timer 0 for 2ms period timeout (max time between bytes)
		TL0  = 0xC4;			
		T0RUN = 1;              // Start Timer to wait for incoming LF Bytes...
		IDLE = 1;               // Enter IDLE Mode since either Timer0 or LF will generate RESUME
		store = REF;            // store REF in a variable since it is cleared on read access

		if (store & 0x10)       // RESUME : LF Data Buffer Full thus LF Databyte received
		{
			LFData[index++] = LFRXD; // Readout LF data
			RECEIVING = TRUE;     // Byte received so stay in the Loop

		}
		if (store & 0x01)       // RESUME : Timer0 Timeout thus no LF Data received
		{
			RECEIVING = FALSE;    // No Byte received so leave Loop
		}
	}

	return index;
}



