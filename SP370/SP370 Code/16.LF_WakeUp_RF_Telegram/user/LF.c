#include "Reg_SP37.h"
#include "SP37_ROMLibrary.h"
#include <SP37.h>
#include <LF.h>

#include <absacc.h>		//绝对地址访问包含头文件

#include "Reg_SP37.h"
#include "SP37_ROMLibrary.h"
#include <SP37.h>
#include <LF.h>

#include <absacc.h>		//绝对地址访问包含头文件

void LF_Configure_Carrier_Detect(void)
{
	LFCDM0 = 0x1C;            //Enable auto-calibration & freeze threshold
	
	LFRX0  = CBYTE[0x580F]; 	//这里选择唤醒灵敏度,即感应电压大小灵敏度
                            //务必从地址0x5810,0X580F,0X580E读入参数值(因为芯片出厂时,原厂保存了矫正值)
                            //0x5810: LF-sensitivity = 0.33 ... 3.35 mVpp(最高灵敏度)
                            //0x580F: LF-sensitivity = 2 ... 11 mVpp
                            //0x580E: LF-sensitivity = 10 ... 50 mVpp(最低灵敏度)
                            //此处我选择0x580F,
                            //灵敏度过高可能会导致，可能会造成误触发。比如还没使用LF激励，就被唤醒了
                            //灵敏度过低,需要较强的激励源，或者激励源需要 很靠近
	
	LFRX1  = 0x10;            //配置auto-calibration为侦测 载波的模式
	LFCDFLT = 0x00;           //过滤器配置
                            //关闭载波过滤功能，可以降低Powerdown时的 功耗
                            //此处的值也需要从地址0x580D,0x580C,0x580B读取
                            //0x580D: Detector Filter Time = 62...240s
                            //0x580C: Detector Filter Time = 500 ... 800s
                            //0x580B: Detector Filter Time = 800 ... 1150 s
                            //此处配置为0x00,关闭滤波功能
	
	WUM &= ~(0x20);           //开启LF 唤醒中断(载波侦测)
	LFRXC = 0x04;             //LF Baseband disabled, LF-Receiver enabled
	ITPR  = 0x00;							//由于内部定时器唤醒，无法关闭。若使用默认值，0.5秒就会被唤醒一次
                            //即默认值将会干扰我们观测LF唤醒的状态
                            //此处修改为0x00,变成大约2min会被定时器唤醒一次
														
}


void LF_Configure_Telegram(void)
{
	LFPCFG = 0x02;            //Use 16Bit pattern P0 for wakeup(16Bit ID匹配)
	LFP0H = 0x12;LFP0L = 0x34;//ID的高地位
	
	LFRX1  = 0x30;            //配置auto-calibration为侦测 报文的模式
	
	WUM &= ~(0x04);           //开启LF 唤醒中断 Pattern Match Wakeup
	LFRXC = 0x14;             //LF Baseband enabled, LF-Receiver enabled
	ITPR  = 0x00;             //由于内部定时器唤醒，无法关闭。若使用默认值，0.5秒就会被唤醒一次
                            //即默认值将会干扰我们观测LF唤醒的状态
                            //此处修改为0x00,变成大约2min会被定时器唤醒一次
	
	StartXtalOsc(40);         //Start RF quartz oscillator and wait 40x42.67μs
                            //开启外部晶振，实际目的是为了校准LF的波特率(为LFBaudrateCalibration函数服务)
	LFBaudrateCalibration(3906);//数据传输波特率3906Bit/s
	StopXtalOsc();            //关闭外部晶振
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



