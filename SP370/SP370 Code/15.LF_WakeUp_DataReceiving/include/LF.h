#ifndef _LF_H
#define _LF_H

typedef enum{
	FALSE = 0,
	TRUE  = 1
}bool;

//����LF���ݰ���󳤶� ������һ��,��ֹ�����������Խ��
#define MAX_LF_DATA	32
//LF ���ݰ���������
extern unsigned char LFData[MAX_LF_DATA];

void LF_Configure_Carrier_Detect(void);
void LF_Configure_Telegram(void);

unsigned char LF_DataReceive(void);

#endif


