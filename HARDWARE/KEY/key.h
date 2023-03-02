#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
	 


  
#define KEY1  PBin(8)   
#define KEY2  PBin(9)  	
#define KEY3  PAin(10)
#define KEY4  PAin(11)

//#define KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15) //��ȡ����1
//#define KEY2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12) //��ȡ����2
//#define KEY3  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) //��ȡ����3
//#define KEY4  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)  //��ȡ����4

 

#define KEY1_PRES	1		//KEY1  
#define KEY2_PRES	2		//KEY2
#define KEY3_PRES	3		//KEY3  
#define KEY4_PRES	4		//KEY4 


void KEY_Init(void);//IO��ʼ��
void Key_Control(void);

#endif
