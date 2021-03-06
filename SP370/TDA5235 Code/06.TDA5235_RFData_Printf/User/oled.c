#include "sys.h"
#include "iic1.h"
#include "oled.h"

#include "oledfont.h"

static bool OLED_Send_Command(u8 IIC_Command);
static bool OLED_Send_Data(u8 data);


void OLED_Init(void)
{
	IIC1_Init();

	OLED_Send_Command(0xAE);//--turn off OLED panel
	OLED_Send_Command(0x00);//---set low column address
	OLED_Send_Command(0x10);//---set high column address
	OLED_Send_Command(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_Send_Command(0x81);//--set contrast control register
	OLED_Send_Command(0xCF); // Set SEG Output Current Brightness
	OLED_Send_Command(0xA1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OLED_Send_Command(0xC8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OLED_Send_Command(0xA6);//--set normal display
	OLED_Send_Command(0xA8);//--set multiplex ratio(1 to 64)
	OLED_Send_Command(0x3f);//--1/64 duty
	OLED_Send_Command(0xD3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_Send_Command(0x00);//-not offset
	OLED_Send_Command(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_Send_Command(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_Send_Command(0xD9);//--set pre-charge period
	OLED_Send_Command(0xF1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_Send_Command(0xDA);//--set com pins hardware configuration
	OLED_Send_Command(0x12);
	OLED_Send_Command(0xDB);//--set vcomh
	OLED_Send_Command(0x40);//Set VCOM Deselect Level
	OLED_Send_Command(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_Send_Command(0x02);//
	OLED_Send_Command(0x8D);//--set Charge Pump enable/disable
	OLED_Send_Command(0x14);//--set(0x10) disable
	OLED_Send_Command(0xA4);// Disable Entire Display On (0xa4/0xa5)
	OLED_Send_Command(0xA6);// Disable Inverse Display On (0xa6/a7) 


	OLED_Clear();	//清屏幕数据
	OLED_Send_Command(0xAF);//--turn on OLED panel
	
}


static bool OLED_Send_Command(u8 IIC_Command)
{
	u8 res = 0;
	
	IIC1_Start();
	IIC1_Send_Byte(0x78);            //Slave address,SA0=0
	res |= IIC1_Wait_Ack();	
	IIC1_Send_Byte(0x00);			//write command
	res |= IIC1_Wait_Ack();	
	IIC1_Send_Byte(IIC_Command); 
	res |= IIC1_Wait_Ack();	
	IIC1_Stop();

	if(res)
		return FALSE;
	else
		return TRUE;
}

static bool OLED_Send_Data(u8 data)
{
	u8 res = 0;

	IIC1_Start();
	
	IIC1_Send_Byte(0x78);			//D/C#=0; R/W#=0
	res |= IIC1_Wait_Ack();	
	
	IIC1_Send_Byte(0x40);			//write data
	res |= IIC1_Wait_Ack();	
	
	IIC1_Send_Byte(data);
	res |= IIC1_Wait_Ack();	
	
	IIC1_Stop();	

	if(res)
		return FALSE;
	else
		return TRUE;

}

//开启OLED显示    
void OLED_Display_On(void)
{
	OLED_Send_Command(0X8D);  //SET DCDC命令
	OLED_Send_Command(0X14);  //DCDC ON
	OLED_Send_Command(0XAF);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
	OLED_Send_Command(0X8D);  //SET DCDC命令
	OLED_Send_Command(0X10);  //DCDC OFF
	OLED_Send_Command(0XAE);  //DISPLAY OFF
}

//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
	u8 page,n;		    
	for(page=0;page<8;page++)  
	{  
		u8 addr = 0;
		OLED_Send_Command(0xb0 	| (page&0x07));    //设置页地址（0~7）
		OLED_Send_Command(0x00 	| addr);      //设置显示位置—列低地址
		OLED_Send_Command(0x10	| addr);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_Send_Data(0x0); 
	} //更新显示
}


static void OLED_Set_Pos(u8 x, u8 y) 
{ 
	OLED_Send_Command(0xb0+y);
	OLED_Send_Command(((x&0xf0)>>4)|0x10);
	OLED_Send_Command((x&0x0f)); 
}   	  

void OLED_ShowChr(u8 x,u8 page,char chr)
{
	u8 i;

	OLED_Set_Pos(x,page);

	for(i=0;i<6;i++){
		OLED_Send_Data(F6x8[chr-ASCII_OFFSET][i]);
	}
}

void OLED_ShowStr(u8 x,u8 page,char *str)
{
	u8 i=0;
	while(str[i] != '\0'){
		OLED_ShowChr(x,page,str[i]);
		x += 6;
		if(x + 6 > OLED_MAX_X){x=0;page+=1;}
			i++;
	}
}

/*
void OLED_ShowChinese(u8 x,u8 page,u8 num)
{
	u8 i;

	OLED_Set_Pos(x,page);

	for(i=0;i<16;i++){
		OLED_Send_Data(FChinese[num][i]);
	}

	OLED_Set_Pos(x,page+1);
	for(i=0;i<16;i++){
		OLED_Send_Data(FChinese[num][i+16]);
	}
}*/

void OLED_ShowBMP(u8 x,u8 page,u8 num)
{
	u8 i;

	OLED_Set_Pos(x,page);

	for(i=0;i<16;i++){
		OLED_Send_Data(FBMP[num][i]);
	}

	OLED_Set_Pos(x,page+1);
	for(i=0;i<16;i++){
		OLED_Send_Data(FBMP[num][i+16]);
	}
}


void OLED_CleanBMP(u8 x,u8 page)
{
	u8 i;

	OLED_Set_Pos(x,page);

	for(i=0;i<16;i++){
		OLED_Send_Data(0);
	}

	OLED_Set_Pos(x,page+1);
	for(i=0;i<16;i++){
		OLED_Send_Data(0);
	}
}


