#ifndef __BEEP_H
#define __BEEP_H	
#include "sys.h"


#define BEEP_ON PCout(12)=0;	// PA8
#define BEEP_OFF PCout(12)=1;	// PD2
#define GET_BEEP_STATE GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12)//»ñÈ¡pc12×´Ì¬
void Beep_Init(void);

 
#endif 
