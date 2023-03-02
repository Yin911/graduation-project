#include "HCSR501.h"
#include "BEEP.h"
#include "delay.h"

void HCSR501_Init(void)
{
 
		 GPIO_InitTypeDef  GPIO_InitStructure;
		
		 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PC�˿�ʱ�� 
			
		 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;				 //LED0-->PA.8 �˿�����
		 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //��������
		 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
		 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
	
	
}
extern _Bool warning_mode;//0������ 1 ����
extern _Bool people_mode;////0û�� 1 ����
void HCSR501_control(void)
{
	   u8 t;
		 t=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6); 	
		 if(t==0)
		 {
		    people_mode=0;			  
		 }
		 if(t==1)
		 {
		    people_mode=1;
			  if(warning_mode)//���˴���
				{
				   BEEP_ON;
				}
				else
				{
				   BEEP_OFF;
				}
		 } 
}
