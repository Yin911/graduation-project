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
	uint8_t temp;				//温度
	uint8_t humi;				//湿度
	float mq;					//MQ135传感器
	float sun;				//光照强度传感器
	uint8_t LED_FLAG;			//LED
	uint8_t FAN_FLAG;			//风扇
	uint8_t DOOR_FLAG;		//步进电机
	uint8_t WARNING_FLAG;		//步进电机
	uint16_t max_temp;//温度阈值
	uint16_t max_mq;	//MQ传感器阈值
}SendData;

*/

typedef struct{
	uint8_t temp;				//温度                      
	uint8_t humi;				//湿度                      
	uint8_t Light;     //光照                  
	float CO2;				 //                             
	
 
	uint8_t FAN_FLAG;			  //风扇                    

  uint8_t LED_FLAG;      //水泵              
	

	uint8_t WARNING_FLAG;	  //警报                    

	
	
}SendData;






extern SendData send_data;
extern uint8_t cmd_rev_flag;



void Hardware_Init(void);	
void Net_Init(void);

#endif



















