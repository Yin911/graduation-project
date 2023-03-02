#include "pwm.h"
#include "led.h"
#include "delay.h"


//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void sg90_TIM1_PWM_Init(u16 arr,u16 psc)
{  
	 GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //ʹ��GPIO����ʱ��ʹ��
	                                                                     	

   //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM������ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

  TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE �����ʹ��	

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	 
	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
 
   
}
#define ON 1
#define OFF 0
extern _Bool DOOR_FLAG; //��
void door_control(void)
{
		if(DOOR_FLAG)
		{
			  TIM_SetCompare1(TIM1, 195);       //0��λ�ã�����
		}
		else
		{ 
		    TIM_SetCompare1(TIM1, 185);      //90��λ�ã�����

		}
}


void WINDOW_TIM3_PWM_INIT(u16 arr,u16 psc)
{	
			GPIO_InitTypeDef GPIO_InitStructure;
			TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
			TIM_OCInitTypeDef  TIM_OCInitStructure;
   
	    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);// 
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO , ENABLE);  //ʹ��GPIO����ʱ��ʹ��
      TIM_DeInit(TIM4);
	
	
	     //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0; //TIM3_CH3
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &GPIO_InitStructure);

			TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
			TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
			TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
			TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
			TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM������ȵ���ģʽ2
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
			TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
			TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
			TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��
						
			TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
			TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
			TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��
											
			TIM_ARRPreloadConfig(TIM3, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
			
			TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM1
			
		  TIM_SetCompare3(TIM3,800);
			TIM_SetCompare4(TIM3,800);

}
extern _Bool WINDOW_FLAG;//����
extern _Bool WINDOW_STATE;//ON����������off����������

void WINDOW_control(void)
{
		if(WINDOW_FLAG==ON&&WINDOW_STATE==ON)
		 {
			    WINDOW_STATE=OFF;
  		    TIM_SetCompare3(TIM3,200);//��������
			    TIM_SetCompare4(TIM3,800);
			    delay_ms(1000);
			    delay_ms(1000);
			    delay_ms(1000);
			    TIM_SetCompare3(TIM3,800);//��������
				  TIM_SetCompare4(TIM3,800);
      
		 }
		 else if(WINDOW_FLAG==OFF&&WINDOW_STATE==ON)
		 {
			    WINDOW_STATE=OFF;
				  TIM_SetCompare4(TIM3,200);//���ϴ���
					TIM_SetCompare3(TIM3,800);
					delay_ms(1000);
			    delay_ms(1000);
			    delay_ms(1000);
			    TIM_SetCompare3(TIM3,800);//��������
				  TIM_SetCompare4(TIM3,800);
		 }




}