#include "led.h"
#include "delay.h"
#include "door_bsp.h"
#include "main.h"

//IN1-PA4
#define IN1_GPIO_PORT     GPIOA
#define IN1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define IN1_GPIO_PIN      GPIO_Pin_4

//IN2-PA5
#define IN2_GPIO_PORT     GPIOA
#define IN2_GPIO_CLK      RCC_APB2Periph_GPIOA
#define IN2_GPIO_PIN      GPIO_Pin_5

//IN3-PA6
#define IN3_GPIO_PORT     GPIOA
#define IN3_GPIO_CLK      RCC_APB2Periph_GPIOA
#define IN3_GPIO_PIN      GPIO_Pin_6

//IN1-PA7
#define IN4_GPIO_PORT     GPIOA
#define IN4_GPIO_CLK      RCC_APB2Periph_GPIOA
#define IN4_GPIO_PIN      GPIO_Pin_7

/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //输出为高电平		
#define digitalLo(p,i)		 {p->BRR=i;}	 //输出低电平

/* 定义控制IO的宏 */
#define IN1_HIGH        digitalHi(IN1_GPIO_PORT,IN1_GPIO_PIN)
#define IN1_LOW         digitalLo(IN1_GPIO_PORT,IN1_GPIO_PIN)

#define IN2_HIGH        digitalHi(IN2_GPIO_PORT,IN2_GPIO_PIN)
#define IN2_LOW         digitalLo(IN2_GPIO_PORT,IN2_GPIO_PIN)

#define IN3_HIGH        digitalHi(IN3_GPIO_PORT,IN3_GPIO_PIN)
#define IN3_LOW         digitalLo(IN3_GPIO_PORT,IN3_GPIO_PIN)

#define IN4_HIGH        digitalHi(IN4_GPIO_PORT,IN4_GPIO_PIN)
#define IN4_LOW         digitalLo(IN4_GPIO_PORT,IN4_GPIO_PIN)

//==========================================================
//	函数名称：	
//
//	函数功能：	
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void Curtains_Init(void)  //CURTAINS  Curtains
{		
		GPIO_InitTypeDef GPIO_InitStructure;              //定义一个GPIO_InitTypeDef类型的结构体
		RCC_APB2PeriphClockCmd( IN1_GPIO_CLK | IN2_GPIO_CLK | IN3_GPIO_CLK | IN4_GPIO_CLK , ENABLE);  //开启引脚相关的GPIO外设时钟
	
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //设置引脚模式为通用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //设置引脚速率为50MHz 
	  GPIO_InitStructure.GPIO_Pin = IN1_GPIO_PIN;	      //选择要控制的GPIO引脚   宏定义
		GPIO_Init(IN1_GPIO_PORT, &GPIO_InitStructure);	  //初始化GPIO
		GPIO_InitStructure.GPIO_Pin = IN2_GPIO_PIN;       //选择要控制的GPIO引脚
		GPIO_Init(IN2_GPIO_PORT, &GPIO_InitStructure);    //初始化GPIO
		GPIO_InitStructure.GPIO_Pin = IN3_GPIO_PIN;       //选择要控制的GPIO引脚
		GPIO_Init(IN3_GPIO_PORT, &GPIO_InitStructure);    //初始化GPIO
		GPIO_InitStructure.GPIO_Pin = IN4_GPIO_PIN;       //选择要控制的GPIO引脚
		GPIO_Init(IN4_GPIO_PORT, &GPIO_InitStructure);    //初始化GPIO
		
		IN1_LOW;//所有引脚初始化为低电平
    IN2_LOW;
    IN3_LOW;
    IN4_LOW;		
}

void SysTick_Delay_Ms(__IO uint32_t ms)
{
	uint32_t i;
	SysTick_Config(72000);
	
	for(i=0; i<ms ; i++)
	{
		while(!(SysTick->CTRL)&(1<<16))
			;
	}
	SysTick->CTRL &= SysTick_CTRL_ENABLE_Msk;
}


enum dir{Pos,Neg};
void stepper(uint8_t dir,int speed)
{
	if(dir == Pos)
	{
		IN1_HIGH;
		SysTick_Delay_Ms(speed);
		IN1_LOW;
		IN2_HIGH;
		SysTick_Delay_Ms(speed);
		IN2_LOW;
		IN3_HIGH;
		SysTick_Delay_Ms(speed);
		IN3_LOW;
		IN4_HIGH;
		SysTick_Delay_Ms(speed);
		IN4_LOW;
	}
	else
	{
		IN1_HIGH;
		SysTick_Delay_Ms(speed);
		IN1_LOW;
		IN4_HIGH;
		SysTick_Delay_Ms(speed);
		IN4_LOW;
		IN3_HIGH;
		SysTick_Delay_Ms(speed);
		IN3_LOW;
		IN2_HIGH;
		SysTick_Delay_Ms(speed);
		IN2_LOW;
	}
}


void Open_Curtains(void)			  	//开门
{
	int i;
	enum dir{Pos,Neg};
	Curtains_Init();
  for(i = 0;i < 300;i++)      //电机正转
		stepper(Neg,7200); 

}

void Close_Curtains(void)				  //关门
{
	int i;
	enum dir{Pos,Neg};
	Curtains_Init();
	for(i = 0;i < 300;i++)      //电机反转
		stepper(Pos,7200);   

}
//i控制转动时间
//speed控制速度，要能带动
//DelayTime的最小值为6500左右，如果数值过小，由于转换过快，步进电机只会抖动而不会转动。



#define ON 1
#define OFF 0


