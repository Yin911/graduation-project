#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f10x.h"
#include "stdio.h"
#include "math.h"
#include "delay.h"
#include "string.h"	

#include "dht11.h"
#include "BH1750.h"
#include "adc.h"
#include "led.h"
#include "OLED_I2C.h"
#include "usart.h"
#include "timer.h"
#include "exti.h"
#include "key.h"

#include "door_bsp.h"
#include "fan.h"

#include "esp8266.h"
#include "MqttKit.h"
#include "onenet.h"
/*
typedef struct{
	uint8_t temp;				//�¶�
	uint8_t humi;				//ʪ��
	float mq;					//MQ135������
	float sun;				//����ǿ�ȴ�����
	uint8_t LED_FLAG;			//LED
	uint8_t FAN_FLAG;			//����
	uint8_t DOOR_FLAG;		//�������
	uint8_t WARNING_FLAG;		//�������
	uint16_t max_temp;//�¶���ֵ
	uint16_t max_mq;	//MQ��������ֵ
}SendData;

*/

typedef struct{
	uint8_t temp;				//�¶�                      
	uint8_t humi;				//ʪ��                      
	uint8_t Light;     //����                  
	float CO2;				 //                             
	
 
	uint8_t FAN_FLAG;			  //����                    

  uint8_t LED_FLAG;      //ˮ��              
	

	uint8_t WARNING_FLAG;	  //����                    

	
	
}SendData;






extern SendData send_data;
extern uint8_t cmd_rev_flag;



void Hardware_Init(void);	
void Net_Init(void);

#endif



















