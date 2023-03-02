#include "key.h"
#include "delay.h"
#include "OLED_I2C.h"
#include "led.h"
#include "fan.h"
#include "led.h"
#include "door_bsp.h"
#include "main.h"


//-------------------------------------------------------------------------------------------------------------------
//  @brief          按键初始化函数 
//  @since           v1.0
//  Date:           2022-1-9
//  Sample usage:   
//PB4 PB3 PA15 PA12 --------A8,A9,A10,A11
//-------------------------------------------------------------------------------------------------------------------
void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;                //定义GPIO结构体变量

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTC时钟    
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);//使能PORTA,PORTC时钟    |RCC_APB2Periph_AFIO  复用  1 10 1733
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PORTB,PORTC时钟                  //没有B端口，用不到了  1.9.2216


	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
		
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;         //配置GPIO第10引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);              //GPIO初始化A10
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
 	GPIO_Init(GPIOA, &GPIO_InitStructure);

}

