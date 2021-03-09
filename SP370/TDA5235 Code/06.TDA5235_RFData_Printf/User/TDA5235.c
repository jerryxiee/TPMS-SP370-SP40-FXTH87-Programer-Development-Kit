#include "sys.h"
#include "delay.h"
#include "spi.h"

#include "TDA5235_SFR_INIT.h"
#include "TDA5235.h"

//NCS  -->	PA3
void TDA5235_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	//NSS管脚配置
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;		//上拉
	GPIO_InitStruct.GPIO_Pin  = TDA5235_NCS_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(TDA5235_NCS_PORT,&GPIO_InitStruct);

	//POWER_ON配置
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;		//上拉
	GPIO_InitStruct.GPIO_Pin  = TDA5235_POWER_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(TDA5235_POWER_PORT,&GPIO_InitStruct);
	
	SPI1_Init();
	//TDA5235 SPI_CLOCK = 2.2Mhz
	//STM32 SPI时钟是64Mhz/2 = 32Mhz
	//所以进行16分频
	SPI1_SetSpeed(SPI_BaudRatePrescaler_16);

	TDA5235_Power(ENABLE);
}

void TDA5235_SFR_Init(void)
{
	u8 i;
	for(i=0;i<init_length;i++)
	{
		TDA5235_Write_Register(init_data[i][0],init_data[i][1]);
	}
}


void TDA5235_Power(FunctionalState NewStatus)
{
	if(NewStatus==ENABLE){
		TDA5235_POWER_ON;
		//需要延时后，才能正常工作
		delay_ms(200);
	}else{
		TDA5235_POWER_OFF;
	}
}

//读寄存器
//addr:寄存器地址
//返回值:寄存器的值
u8 TDA5235_Read_Register(u8 addr)
{
	u8 res;
	TDA5235_SELECT;
	SPI1_ReadWriteByte(TDA5235_INS_RD);
	SPI1_ReadWriteByte(addr);
	res = SPI1_ReadWriteByte(0xFF);

	TDA5235_DISSELECT;
	return res;
}

//连续读寄存器
//addr:开始地址
//buffer:数据存储指针地址
//len:要读取的数据长度
void TDA5235_Read_Register_Burst(u8 start_addr,u8 *buffer,u8 len)
{
	u8 i;
	TDA5235_SELECT;
	SPI1_ReadWriteByte(TDA5235_INS_RDB);
	SPI1_ReadWriteByte(start_addr);

	for(i=0;i<len;i++)
	{
		*buffer = SPI1_ReadWriteByte(0xFF);
		buffer++;
	}
	
	TDA5235_DISSELECT;
}

//写寄存器
//addr:地址
//data:数据
void TDA5235_Write_Register(u8 addr,u8 data)
{
	TDA5235_SELECT;
	SPI1_ReadWriteByte(TDA5235_INS_WR);
	SPI1_ReadWriteByte(addr);
	SPI1_ReadWriteByte(data);
	TDA5235_DISSELECT;
}

//连续写寄存器
//start_addr:开始地址
//buffer:数据指针
//len:数据长度
void TDA5235_Write_Register_Burst(u8 start_addr,u8 *buffer,u8 len)
{
	u8 i;
	TDA5235_SELECT;
	SPI1_ReadWriteByte(TDA5235_INS_WRB);
	SPI1_ReadWriteByte(start_addr);

	for(i=0;i<len;i++)
	{
		SPI1_ReadWriteByte(*buffer);
		buffer++;
	}
	
	TDA5235_DISSELECT;
}

//读FIFO
//FIFO:数据指针
//返回值:收到的字节数
//返回值:0代表没有收到数据，或者数据溢出错误
u8 TDA5235_Read_FIFO(u8 * const FIFO)
{
	u8 i=0,j=0;
	u8 Status=0,Bits=0;
	TDA5235_SELECT;
	while(1)
	{
		SPI1_ReadWriteByte(TDA5235_INS_RDF);
		for(i=0;i<4;i++)
		{
			FIFO[i+j*4] = SPI1_ReadWriteByte(0xFF);
		}
		Status = SPI1_ReadWriteByte(0xFF);
		if(Status & (1<<7)) return 0;		//S7 代表数据出错，或者溢出
		else if(Status>0){ 
			Bits+=Status;
			j++;
		}

		if(Status != 0x20) break;
	}

	TDA5235_DISSELECT;
	return (Bits+7)/8;	//以8向上取整
}


