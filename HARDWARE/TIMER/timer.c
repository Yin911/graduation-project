#include "timer.h"
#include "led.h"
#include "OLED_I2C.h"
#include "delay.h"
#include "main.h"

//extern u8 LED_FLAG;     //灯
//extern u8 DOOR_FLAG;    //门
//extern u8 FAN_FLAG;     //风扇
//extern u8 CURTAINS_FLAG;//窗帘

u8 oled_buffer[50];	//oled送字
 
//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM2_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;               //定义定时器结构体变量
	NVIC_InitTypeDef NVIC_InitStructure;                          //定义中断优先级结构体变量

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);          //使能外设时钟2  挂载在APB1下

	TIM_TimeBaseStructure.TIM_Period = arr;                       //形参  设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc;                     //形参  设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                  //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);               //定时器初始化  根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
  //定时器中断配置
	TIM_ITConfig(     //使能或者失能指定的TIM中断
		TIM2,           //TIM2
		TIM_IT_Update , //中断更新
		ENABLE          //使能
		);
	//中断优先级配置
	//还是记住，只要用中断，就要配置优先级
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;            //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;         //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);                            //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM2, ENABLE);    //使能TIMx外设，类似串口使能，都是一样的原理
							 
}



////////////////////////////////////////////////////////
//定时器中断服务函数
////////////////////////////////////////////////////////
void TIM2_IRQHandler(void)   //TIM2中断
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		  TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 	
		}
}






void Show(void)
{
	    int i;
			//OLED_CLS();                                     //OLED清屏
			for(i=0;i<6;i++){OLED_ShowCN(16+i*16,0,i);}   
			
		
			/////////////////////////////////////////////////////////////////////////////////////////////////
			 sprintf((char*)oled_buffer,"Temp:%d C",send_data.temp);             //温度	
			 OLED_ShowStr(0,2,oled_buffer,1);	//字符串显示
			
			 sprintf((char*)oled_buffer,"Humi:%d%%",send_data.humi);             //湿度
			 OLED_ShowStr(0,3,oled_buffer,1);

			 sprintf((char*)oled_buffer,"CO2:%.2f",send_data.CO2);               //co2
			 OLED_ShowStr(0,4,oled_buffer,1); 
			
			 sprintf((char*)oled_buffer,"Light:%d lux",send_data.Light);         //光照
			 OLED_ShowStr(0,5,oled_buffer,1); 


			/////////////////////////////////////////////////////////////////////////////////////////////////
			 if(send_data.FAN_FLAG)sprintf((char*)oled_buffer,"Fan:ON ");        //风扇
			 else sprintf((char*)oled_buffer,"Fan:OFF");
			 OLED_ShowStr(0,6,oled_buffer,1);
			
			 if(send_data.LED_FLAG)sprintf((char*)oled_buffer,"Led:ON ");       
			 else sprintf((char*)oled_buffer,"Led:OFF");
			 OLED_ShowStr(50,6,oled_buffer,1);
		
			 if(send_data.WARNING_FLAG)sprintf((char*)oled_buffer,"WARNING:ON ");//警报
			 else sprintf((char*)oled_buffer,"WARNING:OFF");
			 OLED_ShowStr(0,7,oled_buffer,1);

			
			 
			 
			 
		
			 
			 
}







//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(  //使能或者失能指定的TIM中断
		TIM3, //TIM2
		TIM_IT_Update ,
		ENABLE  //使能
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设
							 
}


void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		  TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源   
		}
}







