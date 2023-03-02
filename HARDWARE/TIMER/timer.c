#include "timer.h"
#include "led.h"
#include "OLED_I2C.h"
#include "delay.h"
#include "main.h"

//extern u8 LED_FLAG;     //��
//extern u8 DOOR_FLAG;    //��
//extern u8 FAN_FLAG;     //����
//extern u8 CURTAINS_FLAG;//����

u8 oled_buffer[50];	//oled����
 
//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM2_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;               //���嶨ʱ���ṹ�����
	NVIC_InitTypeDef NVIC_InitStructure;                          //�����ж����ȼ��ṹ�����

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);          //ʹ������ʱ��2  ������APB1��

	TIM_TimeBaseStructure.TIM_Period = arr;                       //�β�  ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc;                     //�β�  ����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                  //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);               //��ʱ����ʼ��  ����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
  //��ʱ���ж�����
	TIM_ITConfig(     //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM2,           //TIM2
		TIM_IT_Update , //�жϸ���
		ENABLE          //ʹ��
		);
	//�ж����ȼ�����
	//���Ǽ�ס��ֻҪ���жϣ���Ҫ�������ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;            //TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;         //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);                            //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM2, ENABLE);    //ʹ��TIMx���裬���ƴ���ʹ�ܣ�����һ����ԭ��
							 
}



////////////////////////////////////////////////////////
//��ʱ���жϷ�����
////////////////////////////////////////////////////////
void TIM2_IRQHandler(void)   //TIM2�ж�
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		  TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 	
		}
}






void Show(void)
{
	    int i;
			//OLED_CLS();                                     //OLED����
			for(i=0;i<6;i++){OLED_ShowCN(16+i*16,0,i);}   
			
		
			/////////////////////////////////////////////////////////////////////////////////////////////////
			 sprintf((char*)oled_buffer,"Temp:%d C",send_data.temp);             //�¶�	
			 OLED_ShowStr(0,2,oled_buffer,1);	//�ַ�����ʾ
			
			 sprintf((char*)oled_buffer,"Humi:%d%%",send_data.humi);             //ʪ��
			 OLED_ShowStr(0,3,oled_buffer,1);

			 sprintf((char*)oled_buffer,"CO2:%.2f",send_data.CO2);               //co2
			 OLED_ShowStr(0,4,oled_buffer,1); 
			
			 sprintf((char*)oled_buffer,"Light:%d lux",send_data.Light);         //����
			 OLED_ShowStr(0,5,oled_buffer,1); 


			/////////////////////////////////////////////////////////////////////////////////////////////////
			 if(send_data.FAN_FLAG)sprintf((char*)oled_buffer,"Fan:ON ");        //����
			 else sprintf((char*)oled_buffer,"Fan:OFF");
			 OLED_ShowStr(0,6,oled_buffer,1);
			
			 if(send_data.LED_FLAG)sprintf((char*)oled_buffer,"Led:ON ");       
			 else sprintf((char*)oled_buffer,"Led:OFF");
			 OLED_ShowStr(50,6,oled_buffer,1);
		
			 if(send_data.WARNING_FLAG)sprintf((char*)oled_buffer,"WARNING:ON ");//����
			 else sprintf((char*)oled_buffer,"WARNING:OFF");
			 OLED_ShowStr(0,7,oled_buffer,1);

			
			 
			 
			 
		
			 
			 
}







//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM3, //TIM2
		TIM_IT_Update ,
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����
							 
}


void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
		  TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ   
		}
}







