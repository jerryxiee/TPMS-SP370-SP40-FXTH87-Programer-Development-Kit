#include "SP37_ROMLibrary.h"
#include<SP37.h>
#include<RF.h>


//100Kpa~450Kpa
//压力值= 返回值*1.373 kPa + 100Kpa
//返回值0:错误
unsigned char Scale_Pressure_For_RF(signed int idata Measurement_Result)
{		
	return Scale_Pressure(&Measurement_Result);
}
//	1+  1+       1+          2+           2+      2+	1 = 10
//IDH+IDL+Pressure+Temperature+Acceleration+Voltage+CRC = 10
#define RF_DATA_BYTES 10
//DATA位于数组中的第6个
#define RF_DATA_HEAD  6
//返回值0:成功
//返回其他值 失败
//-1: StartXtalOscillator->error
//-2: VCO_Tuning->error
//-3: Send_RF_Telegram->error
//-4: StopXtalOscillator->error
char Send_RF(T_SP37_DATA idata t_sp37_data)
{	
	//原始数据
	unsigned char idata RF_Array[]={
		0x00,											//START of TABLE
		0x00,											//TYPE
		
		(2+1+RF_DATA_BYTES)*8,		//DATA_LANGTH
															//WAKE UP + SYNS + DATA

		0x00,
		0x00,		//WAKE UP
		
		0x15,		//SYNS

		0x00,		//DATA
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		0x00,
		
		0xF1,		//END
	};

	RF_Array[RF_DATA_HEAD + 0] = t_sp37_data.IDH;
	RF_Array[RF_DATA_HEAD + 1] = t_sp37_data.IDL;
	RF_Array[RF_DATA_HEAD + 2] = Scale_Pressure_For_RF(t_sp37_data.Pressure);
	RF_Array[RF_DATA_HEAD + 3] = t_sp37_data.Temperature>> 8;
	RF_Array[RF_DATA_HEAD + 4] = t_sp37_data.Temperature;
	RF_Array[RF_DATA_HEAD + 5] = t_sp37_data.Acceleration >> 8;
	RF_Array[RF_DATA_HEAD + 6] = t_sp37_data.Acceleration;
	RF_Array[RF_DATA_HEAD + 7] = t_sp37_data.Voltage>>8;
	RF_Array[RF_DATA_HEAD + 8] = t_sp37_data.Voltage;
	RF_Array[RF_DATA_HEAD + 9] = CRC_Baicheva_Calculate(&RF_Array[RF_DATA_HEAD + 0],9);

	return Send_RF_Data(RF_Array);
}

