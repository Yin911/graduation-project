#include "airfan.h"



//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void AIRFAN_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PA,PD�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 //LED0-->PA.8 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
 GPIO_ResetBits(GPIOC,GPIO_Pin_9);						 //PA.8 �����
	
}
extern _Bool AIRFAN_FLAG;  //����
#define ON 1
#define OFF 0
void AIRFAN_control(void)
{
		 if(AIRFAN_FLAG)
		 {
				AIRFAN=ON;		 
		 }
		 else
		 {
				AIRFAN=OFF;	
		 }	
}

