#include "sys.h"
#include "delay.h"
#include "lf.h"


//LF初始化
//硬件上控制LF的为GPIOB 9
//使用PWM输出(TIM4_CH4) 配置为125Khz
void LF_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  TIM_OCInitTypeDef TIM_OCInitStruct;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

  //GPIO配置为复用输出
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStruct.GPIO_Pin  = LF_GPIO_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LF_GPIO_PORT,&GPIO_InitStruct);

  // 复位定时器。
  TIM_DeInit(LF_USE_TIME);

  //时间配置
  TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStruct.TIM_Period = 512-1;
  TIM_TimeBaseInitStruct.TIM_Prescaler = 1 - 1; //不分频(CPU总线频率64Mhz,TIM4计数频率64M/2=32Mhz)
  TIM_TimeBaseInit(LF_USE_TIME,&TIM_TimeBaseInitStruct);
  TIM_ARRPreloadConfig(LF_USE_TIME,ENABLE);         //定时器预装载使能

  //PWM输出配置
  TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;              //向上计数 TIMx_CNT<TIMx_CCR1为有效电平
  TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;      //有效电平是 输出HIGH
  TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;  //使能比较输出
  TIM_OCInitStruct.TIM_Pulse = 0;                             //初始占空比为0

  TIM_OC4Init(LF_USE_TIME,&TIM_OCInitStruct);                 //通道4

  TIM_OC4PreloadConfig(LF_USE_TIME,TIM_OCPreload_Enable);     //预装载使能

  TIM_Cmd(LF_USE_TIME,ENABLE);                                //开启定时器
}

static void PWM_Control(bool stasus)
{
  if(stasus==TRUE){
    TIM_SetCompare4(LF_USE_TIME,256);   //50%占空比
  }else{
    TIM_SetCompare4(LF_USE_TIME,0);     //0%占空比
  }
}


//3906bit/s
//每一个Chip占用的时间为128us
//chipStatus: TRUE -->开启125K振荡器
//chipStatus: FALSE-->关闭125K振荡器
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
  //曼切斯特编码
  if(bitStatus==TRUE){
    LF_SendChip(FALSE);
    LF_SendChip(TRUE);
  }else{
    LF_SendChip(TRUE);
    LF_SendChip(FALSE);
  }
}

//参数sendChar 为要发射的数据
//参数count 为发射几个Bit
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

//先发送16bits的PREAMBLE(报文头部)
static LF_SendTelegramPREAMBLE()
{
  LF_SendBits(0x0000,16);
}

//报文格式，详见"FXTH870xD.pdf" 12.13 Telegram Verification章节
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

//报文格式，详见"SP37_Datasheet_V1.0.pdf" page:85
void LF_SendATelegram(u16 ID,u8 *data,u8 Count)
{
  u8 i;

  //先发送PREAMBLE(报文头部)
  LF_SendTelegramPREAMBLE();

  //SYNC  9Bits
  LF_SendTelegramSYNC();

  LF_SendBits(ID,16);

  for(i=0;i<Count;i++){
    LF_SendBits(data[i],8);
  }
  PWM_Control(FALSE);
}

