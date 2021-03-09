#ifndef _LF_H
#define _LF_H


#define LF_GPIO_PORT  GPIOB
#define LF_GPIO_PIN   GPIO_Pin_9

#define LF_USE_TIME   TIM4


#define LF_GPIO_HIGH  {GPIO_SetBits(LF_GPIO_PORT,LF_GPIO_PIN);}
#define LF_GPIO_LOW   {GPIO_ResetBits(LF_GPIO_PORT,LF_GPIO_PIN);}

void LF_Init(void);
void LF_SendBits(u16 sendChar,u8 count);
void LF_SendATelegram(u16 ID,u8 *data,u8 Count);


#endif


