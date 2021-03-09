#ifndef _SP37_H
#define _SP37_H

unsigned char Measure_Pressure(int *Pressure_VAL);
unsigned char Measure_Acceleration(int *Acceleration_VAL);
unsigned char Measure_Temperature(int *Temperature_VAL);
unsigned char Measure_Supply_Voltage(int *Voltage_VAL);
char StartXtalOscillator(void);
char StopXtalOscillator(void);
unsigned char CRC8_Calculate(unsigned char idata *BlockStart, unsigned char BlockLength);
unsigned char CRC_Baicheva_Calculate(unsigned char idata *BlockStart, unsigned char BlockLength);
void Read_SP37_ID(unsigned char idata *IDH,unsigned char idata *IDL);
void Send_RF_Init(void);
char Send_RF_Data(unsigned char idata * descriptorPtr);

#endif
		

