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
//外部中断初始化函数
void EXTIX_Init(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

  	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//外部中断，需要使能AFIO时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟

	  KEY_Init();//初始化按键对应io模式

		
    //GPIOA.10	  中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource10);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line10;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	                            //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    //GPIOA.11	  中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource11);
   	EXTI_InitStructure.EXTI_Line=EXTI_Line11;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		                              //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		
		//注意一点：在STM32中我们一但用到了中断，必须进行中断优先级管理配置--NVIC   阿峰同学，要时常想到，和LPC不一样。biubiubiu
		
		//中断优先级管理配置
		NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			           //使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	       //抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					     //  子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;							     //使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
	
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			         //使能按键所在的外部中断通道    EXTI9_5_IRQn  在stm32f10x.h中  从5到9
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	       //抢占优先级2 （0-3）
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					     //  子优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								   //使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	                               //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
	
		NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			       //使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	       //抢占优先级2，  数越小越先发生 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					     //  子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								   //使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
		
		

}

/////////////////////////////////////////////////
//按键中断服务函数
/////////////////////////////////////////////////
void EXTI4_IRQHandler(void)                         //外部中断线0到4的中断服务函数
{
}



/////////////////////////////////////////////////////////
//A10 A11
//按第一个按键开启LED灯
//按第二个按键开启窗帘
/////////////////////////////////////////////////////////
void EXTI9_5_IRQHandler(void)                       //外部中断线5到9的中断服务函数  按键 A8 A9 在其中
{

}

 void EXTI15_10_IRQHandler(void)
{			

}


		




		
		  




