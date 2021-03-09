#ifndef _OLEDFONT_H
#define _OLEDFONT_H

//����ASCII��
//ƫ����32
//ASCII�ַ���

#define ASCII_OFFSET	32

/************************************6*8�ĵ���(Terminal 11*11)************************************/
const unsigned char  F6x8[][6] =		
{
	{0x00,0x00,0x00,0x00,0x00,0x00},/*" ",0*/
	{0x00,0x00,0xBE,0x00,0x00,0x00},/*"!",1*/
	{0x00,0x06,0x00,0x06,0x00,0x00},/*""",2*/
	{0x14,0x7F,0x14,0x7F,0x14,0x00},/*"#",3*/
	{0x00,0x4C,0x7A,0x4F,0x32,0x00},/*"$",4*/
	{0x00,0x66,0x16,0x68,0x66,0x00},/*"%",5*/
	{0x00,0x38,0x4F,0x4D,0x32,0x00},/*"&",6*/
	{0x00,0x00,0x00,0x03,0x00,0x00},/*"'",7*/
	{0x00,0x00,0x3E,0x41,0x00,0x00},/*"(",8*/
	{0x00,0x00,0x41,0x3E,0x00,0x00},/*")",9*/
	{0x00,0x1C,0x3E,0x1C,0x00,0x00},/*"*",10*/
	{0x00,0x08,0x3E,0x08,0x00,0x00},/*"+",11*/
	{0x00,0x00,0x00,0x60,0x00,0x00},/*",",12*/
	{0x00,0x08,0x08,0x08,0x08,0x00},/*"-",13*/
	{0x00,0x00,0x40,0x00,0x00,0x00},/*".",14*/
	{0x00,0x40,0x30,0x0C,0x03,0x00},/*"/",15*/
	{0x00,0x3E,0x41,0x41,0x3E,0x00},/*"0",16*/
	{0x00,0x42,0x7F,0x40,0x00,0x00},/*"1",17*/
	{0x00,0x62,0x51,0x49,0x46,0x00},/*"2",18*/
	{0x00,0x22,0x49,0x49,0x36,0x00},/*"3",19*/
	{0x00,0x38,0x26,0x7F,0x20,0x00},/*"4",20*/
	{0x00,0x4F,0x49,0x49,0x31,0x00},/*"5",21*/
	{0x00,0x3E,0x49,0x49,0x32,0x00},/*"6",22*/
	{0x00,0x03,0x71,0x09,0x07,0x00},/*"7",23*/
	{0x00,0x36,0x49,0x49,0x36,0x00},/*"8",24*/
	{0x00,0x26,0x49,0x49,0x3E,0x00},/*"9",25*/
	{0x00,0x00,0x24,0x00,0x00,0x00},/*":",26*/
	{0x00,0x40,0x24,0x00,0x00,0x00},/*";",27*/
	{0x00,0x08,0x14,0x22,0x41,0x00},/*"<",28*/
	{0x00,0x14,0x14,0x14,0x14,0x00},/*"=",29*/
	{0x00,0x41,0x22,0x14,0x08,0x00},/*">",30*/
	{0x00,0x02,0x51,0x09,0x06,0x00},/*"?",31*/
	{0x00,0x0E,0x71,0x49,0x7E,0x00},/*"@",32*/
	{0x00,0x7E,0x11,0x11,0x7E,0x00},/*"A",33*/
	{0x00,0x7F,0x49,0x49,0x36,0x00},/*"B",34*/
	{0x00,0x3E,0x41,0x41,0x22,0x00},/*"C",35*/
	{0x00,0x7F,0x41,0x41,0x3E,0x00},/*"D",36*/
	{0x00,0x7F,0x49,0x49,0x41,0x00},/*"E",37*/
	{0x00,0x7F,0x09,0x09,0x01,0x00},/*"F",38*/
	{0x00,0x3E,0x41,0x49,0x3A,0x00},/*"G",39*/
	{0x00,0x7F,0x08,0x08,0x7F,0x00},/*"H",40*/
	{0x00,0x41,0x7F,0x41,0x00,0x00},/*"I",41*/
	{0x00,0x30,0x40,0x40,0x3F,0x00},/*"J",42*/
	{0x00,0x7F,0x08,0x14,0x63,0x00},/*"K",43*/
	{0x00,0x7F,0x40,0x40,0x40,0x00},/*"L",44*/
	{0x00,0x7F,0x06,0x06,0x7F,0x00},/*"M",45*/
	{0x00,0x7F,0x06,0x18,0x7F,0x00},/*"N",46*/
	{0x00,0x7F,0x41,0x41,0x7F,0x00},/*"O",47*/
	{0x00,0x7F,0x09,0x09,0x06,0x00},/*"P",48*/
	{0x00,0x3E,0x51,0x61,0x7E,0x00},/*"Q",49*/
	{0x00,0x7F,0x19,0x29,0x46,0x00},/*"R",50*/
	{0x00,0x26,0x49,0x49,0x32,0x00},/*"S",51*/
	{0x00,0x01,0x7F,0x01,0x01,0x00},/*"T",52*/
	{0x00,0x3F,0x40,0x40,0x3F,0x00},/*"U",53*/
	{0x00,0x0F,0x70,0x70,0x0F,0x00},/*"V",54*/
	{0x00,0x7F,0x30,0x30,0x7F,0x00},/*"W",55*/
	{0x00,0x63,0x1C,0x1C,0x63,0x00},/*"X",56*/
	{0x03,0x04,0x78,0x04,0x03,0x00},/*"Y",57*/
	{0x00,0x61,0x59,0x4D,0x43,0x00},/*"Z",58*/
	{0x00,0x00,0x7F,0x41,0x00,0x00},/*"[",59*/
	{0x03,0x0C,0x30,0x40,0x00,0x00},/*"\",60*/
	{0x00,0x00,0x41,0x7F,0x00,0x00},/*"]",61*/
	{0x00,0x02,0x01,0x02,0x00,0x00},/*"^",62*/
	{0x00,0x40,0x40,0x40,0x40,0x00},/*"_",63*/
	{0x00,0x00,0x03,0x00,0x00,0x00},/*"`",64*/
	{0x00,0x20,0x58,0x58,0x78,0x00},/*"a",65*/
	{0x00,0x7F,0x48,0x48,0x30,0x00},/*"b",66*/
	{0x00,0x30,0x48,0x48,0x48,0x00},/*"c",67*/
	{0x00,0x30,0x48,0x48,0x7F,0x00},/*"d",68*/
	{0x00,0x30,0x58,0x58,0x10,0x00},/*"e",69*/
	{0x00,0x08,0x7C,0x0A,0x08,0x00},/*"f",70*/
	{0x00,0x10,0xA8,0xA8,0x78,0x00},/*"g",71*/
	{0x00,0x7F,0x08,0x78,0x00,0x00},/*"h",72*/
	{0x00,0x00,0x74,0x00,0x00,0x00},/*"i",73*/
	{0x00,0x80,0x80,0x74,0x00,0x00},/*"j",74*/
	{0x00,0x7F,0x10,0x28,0x48,0x00},/*"k",75*/
	{0x00,0x40,0x7F,0x40,0x00,0x00},/*"l",76*/
	{0x00,0x78,0x08,0x78,0x78,0x00},/*"m",77*/
	{0x00,0x78,0x08,0x08,0x70,0x00},/*"n",78*/
	{0x00,0x30,0x48,0x48,0x30,0x00},/*"o",79*/
	{0x00,0xF8,0x48,0x48,0x30,0x00},/*"p",80*/
	{0x00,0x30,0x48,0x48,0xF8,0x00},/*"q",81*/
	{0x00,0x78,0x10,0x08,0x08,0x00},/*"r",82*/
	{0x00,0x50,0x58,0x68,0x28,0x00},/*"s",83*/
	{0x00,0x08,0x7C,0x48,0x00,0x00},/*"t",84*/
	{0x00,0x38,0x40,0x40,0x78,0x00},/*"u",85*/
	{0x00,0x18,0x60,0x60,0x18,0x00},/*"v",86*/
	{0x18,0x60,0x38,0x60,0x18,0x00},/*"w",87*/
	{0x00,0x48,0x30,0x30,0x48,0x00},/*"x",88*/
	{0x00,0x18,0xA0,0xA0,0x78,0x00},/*"y",89*/
	{0x00,0x48,0x68,0x58,0x48,0x00},/*"z",90*/
	{0x00,0x08,0x77,0x41,0x00,0x00},/*"{",91*/
	{0x00,0x00,0x7F,0x00,0x00,0x00},/*"|",92*/
	{0x00,0x41,0x77,0x08,0x00,0x00},/*"}",93*/
	{0x00,0x02,0x01,0x02,0x01,0x00},/*"~",94*/

	{0x01,0x3C,0x42,0x42,0x42,0x00}/*�����ַ� �� ,95*/	
};

const unsigned char  FBMP[][32]  = {
	{
		0xC0,0xE0,0x38,0x0C,0x04,0x26,0x22,0x02,0x02,0x02,0x06,0x04,0x18,0xF0,0x00,0x00,
		0x00,0x07,0x1C,0x30,0x20,0x20,0x60,0x40,0x40,0x40,0x60,0x20,0x20,0x11,0x0F,0x06
	},/*"xiaoji.bmp",0*/

	{
		0x00,0x00,0xF0,0x18,0x04,0x06,0x02,0x02,0x02,0x22,0x26,0x04,0x0C,0x38,0xE0,0xC0,
		0x06,0x0F,0x11,0x20,0x20,0x60,0x40,0x40,0x40,0x60,0x20,0x20,0x30,0x1C,0x07,0x00,
	}/*"xiaoji���Ҿ���.bmp",1*/

};

#endif


