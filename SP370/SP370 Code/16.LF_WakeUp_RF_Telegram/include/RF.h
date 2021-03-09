#ifndef _RF_H
#define _RF_H

typedef struct SP37_DATA {
	ID_Struct ID_Result;	//用于存储芯片唯一序列号(UniqueId)
	unsigned char IDH;
	unsigned char IDL;
	E_Tyre_Position Tyre_Position;
	int Pressure;
	int Temperature;
	int Acceleration;
	int Voltage;
	unsigned char CRC;
}T_SP37_DATA;

char Send_RF(T_SP37_DATA idata t_sp37_data);

#endif


