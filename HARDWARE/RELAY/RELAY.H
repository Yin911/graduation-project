#ifndef __RELAY_H
#define __RELAY_H	
#include "sys.h"
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEKս��STM32������
//ADC ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

#define RELAY_ON PBout(13)=0;		// PB13
#define RELAY_OFF PBout(13)=1;	// PD2

void RELAY_Init(void);

 void realy_control(void);
#endif 