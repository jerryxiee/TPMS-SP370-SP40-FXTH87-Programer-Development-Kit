#ifndef _LF_H
#define _LF_H

typedef enum{
	FALSE = 0,
	TRUE  = 1
}bool;

//定义LF数据包最大长度 尽量大一点,防止意外情况数组越界
#define MAX_LF_DATA	32
//LF 数据包缓存数组
extern unsigned char LFData[MAX_LF_DATA];

void LF_Configure_Carrier_Detect(void);
void LF_Configure_Telegram(void);

unsigned char LF_DataReceive(void);

#endif


