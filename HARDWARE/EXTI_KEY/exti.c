#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "door_bsp.h"
#include "fan.h"
#include "led.h"
#include "main.h"

#include "esp8266.h"

//PB5 PB4 PA15 PA12
// A8  A9  A10  A11
//�ⲿ�жϳ�ʼ������
void EXTIX_Init(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

  	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��

	  KEY_Init();//��ʼ��������Ӧioģʽ

		
    //GPIOA.10	  �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource10);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line10;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	                            //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    //GPIOA.11	  �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource11);
   	EXTI_InitStructure.EXTI_Line=EXTI_Line11;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		                              //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
		
		//ע��һ�㣺��STM32������һ���õ����жϣ���������ж����ȼ���������--NVIC   ����ͬѧ��Ҫʱ���뵽����LPC��һ����biubiubiu
		
		//�ж����ȼ���������
		NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			           //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	       //��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					     //  �����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							     //ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
	
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			         //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��    EXTI9_5_IRQn  ��stm32f10x.h��  ��5��9
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	       //��ռ���ȼ�2 ��0-3��
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					     //  �����ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								   //ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	                               //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
	
		NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			       //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	       //��ռ���ȼ�2��  ��ԽСԽ�ȷ��� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					     //  �����ȼ�0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								   //ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
		
		

}

/////////////////////////////////////////////////
//�����жϷ�����
/////////////////////////////////////////////////
void EXTI4_IRQHandler(void)                         //�ⲿ�ж���0��4���жϷ�����
{
}



/////////////////////////////////////////////////////////
//A10 A11
//����һ����������LED��
//���ڶ���������������
/////////////////////////////////////////////////////////
void EXTI9_5_IRQHandler(void)                       //�ⲿ�ж���5��9���жϷ�����  ���� A8 A9 ������
{

}

 void EXTI15_10_IRQHandler(void)
{			

}


		




		
		  




