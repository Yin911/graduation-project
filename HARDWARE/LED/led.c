#include "led.h"
#include "main.h"
    
		

		



//-------------------------------------------------------------------------------------------------------------------
//  @brief          LED灯初始化函数 
//  @since           v1.0
//  Date:           2022-1-12
//  Sample usage:   
//-------------------------------------------------------------------------------------------------------------------
void LED_Init(void)          //LED----B9
{
	GPIO_InitTypeDef    GPIO_InitStruct;                   //定义GPIO结构体变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //使能GPIOB的时钟
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;                   //配置PB9引脚
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;            //配置GPIO为通用推挽输出
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;           //配置GPIO速率
	GPIO_Init(GPIOB,&GPIO_InitStruct);                     //GPIO初始化函数
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);                      //PB9输出低电平
	
}

void led_control(void)
{
	 //LED_Init();
	 if(send_data.LED_FLAG==1) {GPIO_SetBits(GPIOB,GPIO_Pin_9);}   //PB9输出高电平	
	 else if(send_data.LED_FLAG==0){GPIO_ResetBits(GPIOB,GPIO_Pin_9);}                   //PB9输出低电平
}





//-------------------------------------------------------------------------------------------------------------------
//  @brief          风扇初始化函数 
//  @since           v1.0
//  Date:           2022-1-12
//  Sample usage:   
//-------------------------------------------------------------------------------------------------------------------
void FAN_Init(void)          //FAN----B13
{
	GPIO_InitTypeDef    GPIO_InitStruct;                   //定义GPIO结构体变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //使能GPIOB的时钟
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_13;                   //配置PB13引脚
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;            //配置GPIO为通用推挽输出
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;           //配置GPIO速率
	GPIO_Init(GPIOB,&GPIO_InitStruct);                     //GPIO初始化函数
	//GPIO_ResetBits(GPIOB,GPIO_Pin_13);                      //PB13输出低电平
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
	
}

void fan_control(void)
{
	 //FAN_Init();
	 if(send_data.FAN_FLAG==1) {GPIO_ResetBits(GPIOB,GPIO_Pin_13);}                 //PB13输出低电平
	 else if(send_data.FAN_FLAG==0) {GPIO_SetBits(GPIOB,GPIO_Pin_13);}              //PB13输出高电平	
	 
	 
}







//-------------------------------------------------------------------------------------------------------------------
//  @brief         蜂鸣器初始化
//  @since           v1.0
//  Date:           2022-1-12
//  Sample usage:   
//-------------------------------------------------------------------------------------------------------------------
void WARNING_Init(void)        //WARNING----C13
{
	GPIO_InitTypeDef GPIO_InitStruct;                      //定义GPIO结构体变量
	  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);   //使能GPIOC的时钟
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_13;                  //配置GPIO第13引脚
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;            //配置GPIO为通用推挽输出
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;           //配置GPIO速率
	GPIO_Init(GPIOC,&GPIO_InitStruct);                     //GPIO初始化函数

	GPIO_SetBits(GPIOC,GPIO_Pin_13);                       //PC13引脚置位低电平
}


void warning_control(void)
{
		//WARNING_Init();
	
	  if(send_data.temp>35 || send_data.humi>70 || send_data.CO2>20 )
		{
		    send_data.WARNING_FLAG = 1;
	
		    GPIO_ResetBits(GPIOC,GPIO_Pin_13);      //PC13输出高电平，蜂鸣器触发
			     
			  delay_ms(400);
        GPIO_SetBits(GPIOC,GPIO_Pin_13);       
       
	       
		}
	  else { send_data.WARNING_FLAG = 0;}
		
}





