#include<CRC.h>

#define POLYNOMIAL 0x2F
#define CRC8_INIT  0xAA
//最大长度0xFF  BlockLength<=0xFF
unsigned char CRC8_Calc(unsigned char *BlockStart,unsigned char BlockLength)
{
	unsigned char i,j;
	unsigned char CRC_VAL = CRC8_INIT;	
	
	for(j=0;j<BlockLength;j++){
		CRC_VAL = *(BlockStart+j) ^ CRC_VAL;
		for(i=0;i<8;i++){
			if(CRC_VAL & 0x80){
				CRC_VAL <<= 1;
				CRC_VAL ^= POLYNOMIAL;
			}
			else{
				CRC_VAL <<= 1;
			}
		}
	}
	return CRC_VAL;
}


