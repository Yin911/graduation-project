/*******************************************************************************
  * @file     main.c    
  * @attention
  * д��ÿ���ļ�һ��Ҫ��������һ�£�������¼��ȥ�ĵĳ�����Ϊδ�޸ĵ�
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
	unsigned short timeCount = 0;	//���ͼ������

	Hardware_Init();
	Net_Init();

	 while(1)
	 {  		
			if(++timeCount >= 200 || (cmd_rev_flag == 1))	    //���ͼ�������յ�����)	//���ͼ�������յ�����  16000 2min
			{	
				DHT11_Read_Data(&send_data.temp,&send_data.humi);																		//��ȡ��ʪ��ֵ	 
				send_data.CO2=(float)(Get_Adc_Average(ADC_Channel_9,10))*(3.3/4096)*10;		
				send_data.Light = LIght_Intensity();                                                //������ǿ��
				
				OneNet_SendData();	//��������
				timeCount = 0;
				cmd_rev_flag=0;
				ESP8266_Clear();
			  Show(); 
				warning_control();
			}

			data_ptr = ESP8266_GetIPD(0);		//����Ƿ����·�ָ��
			if(data_ptr != NULL)
			{
				OneNet_RevPro(data_ptr);
			}
	
	 }		 
	

}

void Hardware_Init(void)
{
	delay_init();	                	//��ʱ������ʼ��	
	
	//TIM2_Int_Init(4999,7199);  		//TIM��ʼ������ʱ��9999+1��*��7199+1��/72MHZ=1s  
	
	Usart1_Init(115200);						//���ڵ���
	Usart2_Init(115200);						//esp8266--stm32ͨ��        
	
	OLED_Init();			              //OLED��ʼ��
	OLED_CLS();                     //����
	
	KEY_Init();			              	//������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2��Ϊ�����ⲿ�ж�������   ��ռ���ȼ�Ϊ����������λ�������ȼ�Ҳ����λ
	EXTIX_Init();		              	//�жϼ�ִֵ�в���

	DHT11_Init();			              //��ʪ�ȴ�������ʼ��
  Adc_Init();				              //CO2����ʼ��
	BH1750_Init();			            //����

	FAN_Init();		  	              //���ȳ�ʼ��
	LED_Init();                    //ˮ�ó�ʼ��
	WARNING_Init();                 //��������ʼ��
	
}

void Net_Init(void)
{
	ESP8266_Init();					        //��ʼ��ESP8266
	while(OneNet_DevLink())			    //����OneNET
	delay_ms(500);                  //��ʱ
	
	OLED_CLS();                     //����

}


