#include "led.h"
#include "main.h"
    
		

		



//-------------------------------------------------------------------------------------------------------------------
//  @brief          LED�Ƴ�ʼ������ 
//  @since           v1.0
//  Date:           2022-1-12
//  Sample usage:   
//-------------------------------------------------------------------------------------------------------------------
void LED_Init(void)          //LED----B9
{
	GPIO_InitTypeDef    GPIO_InitStruct;                   //����GPIO�ṹ�����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //ʹ��GPIOB��ʱ��
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;                   //����PB9����
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;            //����GPIOΪͨ���������
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;           //����GPIO����
	GPIO_Init(GPIOB,&GPIO_InitStruct);                     //GPIO��ʼ������
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);                      //PB9����͵�ƽ
	
}

void led_control(void)
{
	 //LED_Init();
	 if(send_data.LED_FLAG==1) {GPIO_SetBits(GPIOB,GPIO_Pin_9);}   //PB9����ߵ�ƽ	
	 else if(send_data.LED_FLAG==0){GPIO_ResetBits(GPIOB,GPIO_Pin_9);}                   //PB9����͵�ƽ
}





//-------------------------------------------------------------------------------------------------------------------
//  @brief          ���ȳ�ʼ������ 
//  @since           v1.0
//  Date:           2022-1-12
//  Sample usage:   
//-------------------------------------------------------------------------------------------------------------------
void FAN_Init(void)          //FAN----B13
{
	GPIO_InitTypeDef    GPIO_InitStruct;                   //����GPIO�ṹ�����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //ʹ��GPIOB��ʱ��
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_13;                   //����PB13����
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;            //����GPIOΪͨ���������
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;           //����GPIO����
	GPIO_Init(GPIOB,&GPIO_InitStruct);                     //GPIO��ʼ������
	//GPIO_ResetBits(GPIOB,GPIO_Pin_13);                      //PB13����͵�ƽ
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
	
}

void fan_control(void)
{
	 //FAN_Init();
	 if(send_data.FAN_FLAG==1) {GPIO_ResetBits(GPIOB,GPIO_Pin_13);}                 //PB13����͵�ƽ
	 else if(send_data.FAN_FLAG==0) {GPIO_SetBits(GPIOB,GPIO_Pin_13);}              //PB13����ߵ�ƽ	
	 
	 
}







//-------------------------------------------------------------------------------------------------------------------
//  @brief         ��������ʼ��
//  @since           v1.0
//  Date:           2022-1-12
//  Sample usage:   
//-------------------------------------------------------------------------------------------------------------------
void WARNING_Init(void)        //WARNING----C13
{
	GPIO_InitTypeDef GPIO_InitStruct;                      //����GPIO�ṹ�����
	  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);   //ʹ��GPIOC��ʱ��
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_13;                  //����GPIO��13����
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;            //����GPIOΪͨ���������
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;           //����GPIO����
	GPIO_Init(GPIOC,&GPIO_InitStruct);                     //GPIO��ʼ������

	GPIO_SetBits(GPIOC,GPIO_Pin_13);                       //PC13������λ�͵�ƽ
}


void warning_control(void)
{
		//WARNING_Init();
	
	  if(send_data.temp>35 || send_data.humi>70 || send_data.CO2>20 )
		{
		    send_data.WARNING_FLAG = 1;
	
		    GPIO_ResetBits(GPIOC,GPIO_Pin_13);      //PC13����ߵ�ƽ������������
			     
			  delay_ms(400);
        GPIO_SetBits(GPIOC,GPIO_Pin_13);       
       
	       
		}
	  else { send_data.WARNING_FLAG = 0;}
		
}





