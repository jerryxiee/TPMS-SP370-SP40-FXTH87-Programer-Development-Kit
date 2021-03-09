#ifndef _SP37DATA_H
#define _SP37DATA_H

//²»°üÀ¨CRC
#define SP37_RF_DATA_LENGTH 	9

typedef struct SP37_RF_DATA {
	u8 IDH;
	u8 IDL;
	u8 Pressure;
	u8 Temperature[2];
	u8 Acceleration[2];
	u8 Voltage[2];
	u8 CRC8;
	u8 RESERVED[16];
}T_SP37_RF_DATA,*PT_SP37_RF_DATA;

float SP37_Cal_Pressure(u8 rawVal);
float SP37_Cal_Temperature(u8 *rawVal);
float SP37_Cal_Acceleration(u8 *rawVal);
float SP37_Cal_Voltage(u8 *rawVal);


#endif


