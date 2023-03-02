#include "pwm.h"
#include "led.h"
#include "delay.h"


//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void sg90_TIM1_PWM_Init(u16 arr,u16 psc)
{  
	 GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);  //使能GPIO外设时钟使能
	                                                                     	

   //设置该引脚为复用输出功能,输出TIM1 CH1的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx

  TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE 主输出使能	

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1预装载使能	 
	
	TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	TIM_Cmd(TIM1, ENABLE);  //使能TIM1
 
   
}
#define ON 1
#define OFF 0
extern _Bool DOOR_FLAG; //门
void door_control(void)
{
		if(DOOR_FLAG)
		{
			  TIM_SetCompare1(TIM1, 195);       //0度位置，开门
		}
		else
		{ 
		    TIM_SetCompare1(TIM1, 185);      //90度位置，关门

		}
}


void WINDOW_TIM3_PWM_INIT(u16 arr,u16 psc)
{	
			GPIO_InitTypeDef GPIO_InitStructure;
			TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
			TIM_OCInitTypeDef  TIM_OCInitStructure;
   
	    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);// 
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO , ENABLE);  //使能GPIO外设时钟使能
      TIM_DeInit(TIM4);
	
	
	     //设置该引脚为复用输出功能,输出TIM1 CH1的PWM脉冲波形
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_0; //TIM3_CH3
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &GPIO_InitStructure);

			TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
			TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
			TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
			TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
			TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
			TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
			TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
			TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
			TIM_OC3Init(TIM3, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
			TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH1预装载使能
						
			TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
			TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
			TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
			TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH1预装载使能
											
			TIM_ARRPreloadConfig(TIM3, ENABLE); //使能TIMx在ARR上的预装载寄存器
			
			TIM_Cmd(TIM3, ENABLE);  //使能TIM1
			
		  TIM_SetCompare3(TIM3,800);
			TIM_SetCompare4(TIM3,800);

}
extern _Bool WINDOW_FLAG;//窗帘
extern _Bool WINDOW_STATE;//ON窗帘工作，off窗帘不工作

void WINDOW_control(void)
{
		if(WINDOW_FLAG==ON&&WINDOW_STATE==ON)
		 {
			    WINDOW_STATE=OFF;
  		    TIM_SetCompare3(TIM3,200);//拉开窗帘
			    TIM_SetCompare4(TIM3,800);
			    delay_ms(1000);
			    delay_ms(1000);
			    delay_ms(1000);
			    TIM_SetCompare3(TIM3,800);//窗帘不动
				  TIM_SetCompare4(TIM3,800);
      
		 }
		 else if(WINDOW_FLAG==OFF&&WINDOW_STATE==ON)
		 {
			    WINDOW_STATE=OFF;
				  TIM_SetCompare4(TIM3,200);//拉上窗帘
					TIM_SetCompare3(TIM3,800);
					delay_ms(1000);
			    delay_ms(1000);
			    delay_ms(1000);
			    TIM_SetCompare3(TIM3,800);//窗帘不动
				  TIM_SetCompare4(TIM3,800);
		 }




}
