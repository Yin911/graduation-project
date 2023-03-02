#include "key.h"
#include "delay.h"
#include "OLED_I2C.h"
#include "led.h"
#include "fan.h"
#include "led.h"
#include "door_bsp.h"
#include "main.h"


//-------------------------------------------------------------------------------------------------------------------
//  @brief          ������ʼ������ 
//  @since           v1.0
//  Date:           2022-1-9
//  Sample usage:   
//PB4 PB3 PA15 PA12 --------A8,A9,A10,A11
//-------------------------------------------------------------------------------------------------------------------
void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;                //����GPIO�ṹ�����

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTA,PORTCʱ��    
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);//ʹ��PORTA,PORTCʱ��    |RCC_APB2Periph_AFIO  ����  1 10 1733
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PORTB,PORTCʱ��                  //û��B�˿ڣ��ò�����  1.9.2216


	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����
		
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10;         //����GPIO��10����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       //���ó���������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);              //GPIO��ʼ��A10
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_11;         
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
 	GPIO_Init(GPIOA, &GPIO_InitStructure);

}

