#ifndef _RF_H
#define _RF_H

typedef struct SP37_DATA {
	unsigned char IDH;
	unsigned char IDL;
	int Pressure;
	int Temperature;
	int Acceleration;
	int Voltage;
	unsigned char CRC;
}T_SP37_DATA;

char Send_RF(T_SP37_DATA idata t_sp37_data);

#endif


