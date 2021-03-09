#include "sys.h"
#include "delay.h"
#include "lf.h"


//LF��ʼ��
//Ӳ���Ͽ���LF��ΪGPIOB 9
//ʹ��PWM���(TIM4_CH4) ����Ϊ125Khz
void LF_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  TIM_OCInitTypeDef TIM_OCInitStruct;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

  //GPIO����Ϊ�������
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStruct.GPIO_Pin  = LF_GPIO_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LF_GPIO_PORT,&GPIO_InitStruct);

  // ��λ��ʱ����
  TIM_DeInit(LF_USE_TIME);

  //ʱ������
  TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct.TIM_Period = 512-1;
  TIM_TimeBaseInitStruct.TIM_Prescaler = 1 - 1; //����Ƶ(CPU����Ƶ��64Mhz,TIM4����Ƶ��64M/2=32Mhz)
  TIM_TimeBaseInit(LF_USE_TIME,&TIM_TimeBaseInitStruct);
  TIM_ARRPreloadConfig(LF_USE_TIME,ENABLE);         //��ʱ��Ԥװ��ʹ��

  //PWM�������
  TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;              //���ϼ��� TIMx_CNT<TIMx_CCR1Ϊ��Ч��ƽ
  TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;      //��Ч��ƽ�� ���HIGH
  TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;  //ʹ�ܱȽ����
  TIM_OCInitStruct.TIM_Pulse = 0;                             //��ʼռ�ձ�Ϊ0

  TIM_OC4Init(LF_USE_TIME,&TIM_OCInitStruct);                 //ͨ��4

  TIM_OC4PreloadConfig(LF_USE_TIME,TIM_OCPreload_Enable);     //Ԥװ��ʹ��

  TIM_Cmd(LF_USE_TIME,ENABLE);                                //������ʱ��
}

static void PWM_Control(bool stasus)
{
  if(stasus==TRUE){
    TIM_SetCompare4(LF_USE_TIME,256);   //50%ռ�ձ�
  }else{
    TIM_SetCompare4(LF_USE_TIME,0);     //0%ռ�ձ�
  }
}


//3906bit/s
//ÿһ��Chipռ�õ�ʱ��Ϊ128us
//chipStatus: TRUE -->����125K����
//chipStatus: FALSE-->�ر�125K����
static LF_SendChip(bool chipStatus)
{
  if(chipStatus==TRUE){
    PWM_Control(TRUE);
    delay_us(128);
  }else{
    PWM_Control(FALSE);
    delay_us(128);
  }
  PWM_Control(FALSE);
}

static LF_SendBit(bool bitStatus)
{
  //����˹�ر���
  if(bitStatus==TRUE){
    LF_SendChip(FALSE);
    LF_SendChip(TRUE);
  }else{
    LF_SendChip(TRUE);
    LF_SendChip(FALSE);
  }
}

//����sendChar ΪҪ���������
//����count Ϊ���伸��Bit
void LF_SendBits(u16 sendChar,u8 count)
{
  u8 i;
  for(i=0;i<count;i++){
    if(sendChar & (1<<(count-1))){
      LF_SendBit(TRUE);
    }
    else{
      LF_SendBit(FALSE);
    }

    sendChar <<= 1;
  }
}

//�ȷ���16bits��PREAMBLE(����ͷ��)
static LF_SendTelegramPREAMBLE()
{
  LF_SendBits(0x0000,16);
}

//���ĸ�ʽ�����"FXTH870xD.pdf" 12.13 Telegram Verification�½�
//(9T) Pattern
static LF_SendTelegramSYNC(void)
{
  LF_SendChip(TRUE);
  LF_SendChip(TRUE);
  LF_SendChip(TRUE);
  LF_SendChip(FALSE);
  LF_SendChip(FALSE);
  LF_SendChip(FALSE);

  LF_SendChip(TRUE);
  LF_SendChip(FALSE);

  LF_SendChip(TRUE);
  LF_SendChip(TRUE);
  LF_SendChip(FALSE);
  LF_SendChip(FALSE);

  LF_SendChip(TRUE);
  LF_SendChip(TRUE);
  LF_SendChip(FALSE);
  LF_SendChip(FALSE);

  LF_SendChip(TRUE);
  LF_SendChip(FALSE);
}

//���ĸ�ʽ�����"SP37_Datasheet_V1.0.pdf" page:85
void LF_SendATelegram(u16 ID,u8 *data,u8 Count)
{
  u8 i;

  //�ȷ���PREAMBLE(����ͷ��)
  LF_SendTelegramPREAMBLE();

  //SYNC  9Bits
  LF_SendTelegramSYNC();

  LF_SendBits(ID,16);

  for(i=0;i<Count;i++){
    LF_SendBits(data[i],8);
  }
  PWM_Control(FALSE);
}

