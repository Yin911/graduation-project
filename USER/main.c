/*******************************************************************************
  * @file     main.c    
  * @attention
  * 写完每个文件一定要单独编译一下，否则烧录进去的的程序仍为未修改的
  * 
  ******************************************************************************
/-----------------------------------------------------------------------------**/



#include "main.h"

//                    1   2   3    4   5    6   7 
SendData send_data = {0,  0,  0, 0.0, 0.0,  0,  0};
uint8_t cmd_rev_flag = 0;

	
int main(void)
{  
  
	unsigned char *data_ptr = NULL;
	unsigned short timeCount = 0;	//发送间隔变量

	Hardware_Init();
	Net_Init();

	 while(1)
	 {  		
			if(++timeCount >= 200 || (cmd_rev_flag == 1))	    //发送间隔或者收到命令)	//发送间隔或者收到命令  16000 2min
			{	
				DHT11_Read_Data(&send_data.temp,&send_data.humi);																		//读取温湿度值	 
				send_data.CO2=(float)(Get_Adc_Average(ADC_Channel_9,10))*(3.3/4096)*10;		
				send_data.Light = LIght_Intensity();                                                //读光照强度
				
				OneNet_SendData();	//发送数据
				timeCount = 0;
				cmd_rev_flag=0;
				ESP8266_Clear();
			  Show(); 
				warning_control();
			}

			data_ptr = ESP8266_GetIPD(0);		//检查是否有下发指定
			if(data_ptr != NULL)
			{
				OneNet_RevPro(data_ptr);
			}
	
	 }		 
	

}

void Hardware_Init(void)
{
	delay_init();	                	//延时函数初始化	
	
	//TIM2_Int_Init(4999,7199);  		//TIM初始化，定时（9999+1）*（7199+1）/72MHZ=1s  
	
	Usart1_Init(115200);						//串口调试
	Usart2_Init(115200);						//esp8266--stm32通信        
	
	OLED_Init();			              //OLED初始化
	OLED_CLS();                     //清屏
	
	KEY_Init();			              	//按键初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2，为后面外部中断做基础   抢占优先级为两个二进制位，子优先级也是两位
	EXTIX_Init();		              	//判断键值执行操作

	DHT11_Init();			              //温湿度传感器初始化
  Adc_Init();				              //CO2检测初始化
	BH1750_Init();			            //光照

	FAN_Init();		  	              //风扇初始化
	LED_Init();                    //水泵初始化
	WARNING_Init();                 //蜂鸣器初始化
	
}

void Net_Init(void)
{
	ESP8266_Init();					        //初始化ESP8266
	while(OneNet_DevLink())			    //接入OneNET
	delay_ms(500);                  //延时
	
	OLED_CLS();                     //清屏

}


