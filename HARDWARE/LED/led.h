#ifndef __LED_H
#define __LED_H	 
#include "sys.h"




void FAN_Init(void);//初始化
void fan_control(void);			


void LED_Init(void);//初始化
void led_control(void);			

void WARNING_Init(void);
void warning_control(void);



#endif
