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

/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //���Ϊ�ߵ�ƽ		
#define digitalLo(p,i)		 {p->BRR=i;}	 //����͵�ƽ

/* �������IO�ĺ� */
#define IN1_HIGH        digitalHi(IN1_GPIO_PORT,IN1_GPIO_PIN)
#define IN1_LOW         digitalLo(IN1_GPIO_PORT,IN1_GPIO_PIN)

#define IN2_HIGH        digitalHi(IN2_GPIO_PORT,IN2_GPIO_PIN)
#define IN2_LOW         digitalLo(IN2_GPIO_PORT,IN2_GPIO_PIN)

#define IN3_HIGH        digitalHi(IN3_GPIO_PORT,IN3_GPIO_PIN)
#define IN3_LOW         digitalLo(IN3_GPIO_PORT,IN3_GPIO_PIN)

#define IN4_HIGH        digitalHi(IN4_GPIO_PORT,IN4_GPIO_PIN)
#define IN4_LOW         digitalLo(IN4_GPIO_PORT,IN4_GPIO_PIN)

//==========================================================
//	�������ƣ�	
//
//	�������ܣ�	
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void Curtains_Init(void)  //CURTAINS  Curtains
{		
		GPIO_InitTypeDef GPIO_InitStructure;              //����һ��GPIO_InitTypeDef���͵Ľṹ��
		RCC_APB2PeriphClockCmd( IN1_GPIO_CLK | IN2_GPIO_CLK | IN3_GPIO_CLK | IN4_GPIO_CLK , ENABLE);  //����������ص�GPIO����ʱ��
	
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //��������ģʽΪͨ���������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //������������Ϊ50MHz 
	  GPIO_InitStructure.GPIO_Pin = IN1_GPIO_PIN;	      //ѡ��Ҫ���Ƶ�GPIO����   �궨��
		GPIO_Init(IN1_GPIO_PORT, &GPIO_InitStructure);	  //��ʼ��GPIO
		GPIO_InitStructure.GPIO_Pin = IN2_GPIO_PIN;       //ѡ��Ҫ���Ƶ�GPIO����
		GPIO_Init(IN2_GPIO_PORT, &GPIO_InitStructure);    //��ʼ��GPIO
		GPIO_InitStructure.GPIO_Pin = IN3_GPIO_PIN;       //ѡ��Ҫ���Ƶ�GPIO����
		GPIO_Init(IN3_GPIO_PORT, &GPIO_InitStructure);    //��ʼ��GPIO
		GPIO_InitStructure.GPIO_Pin = IN4_GPIO_PIN;       //ѡ��Ҫ���Ƶ�GPIO����
		GPIO_Init(IN4_GPIO_PORT, &GPIO_InitStructure);    //��ʼ��GPIO
		
		IN1_LOW;//�������ų�ʼ��Ϊ�͵�ƽ
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


void Open_Curtains(void)			  	//����
{
	int i;
	enum dir{Pos,Neg};
	Curtains_Init();
  for(i = 0;i < 300;i++)      //�����ת
		stepper(Neg,7200); 

}

void Close_Curtains(void)				  //����
{
	int i;
	enum dir{Pos,Neg};
	Curtains_Init();
	for(i = 0;i < 300;i++)      //�����ת
		stepper(Pos,7200);   

}
//i����ת��ʱ��
//speed�����ٶȣ�Ҫ�ܴ���
//DelayTime����СֵΪ6500���ң������ֵ��С������ת�����죬�������ֻ�ᶶ��������ת����



#define ON 1
#define OFF 0


