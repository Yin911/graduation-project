#ifndef __door_bsp_H
#define __door_bsp_H	 
#include "sys.h"

//IN1-PA4
#define IN1_GPIO_PORT     GPIOA
#define IN1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define IN1_GPIO_PIN      GPIO_Pin_4

//IN2-PA5
#define IN2_GPIO_PORT     GPIOA
#define IN2_GPIO_CLK      RCC_APB2Periph_GPIOA
#define IN2_GPIO_PIN      GPIO_Pin_5

//IN3-PA6
#define IN3_GPIO_PORT     GPIOA
#define IN3_GPIO_CLK      RCC_APB2Periph_GPIOA
#define IN3_GPIO_PIN      GPIO_Pin_6

//IN1-PA7
#define IN4_GPIO_PORT     GPIOA
#define IN4_GPIO_CLK      RCC_APB2Periph_GPIOA
#define IN4_GPIO_PIN      GPIO_Pin_7

/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)		 {p->BSRR=i;}	 //���Ϊ�ߵ�ƽ		
#define digitalLo(p,i)		 {p->BRR=i;}	 //����͵�ƽ

/* �������IO�ĺ� */
#define IN1_HIGH        digitalHi(IN1_GPIO_PORT,IN1_GPIO_PIN)
#define IN1_LOW         digitalLo(IN1_GPIO_PORT,IN1_GPIO_PIN)

#define IN2_HIGH        digitalHi(IN2_GPIO_PORT,IN2_GPIO_PIN)
#define IN2_LOW         digitalLo(IN2_GPIO_PORT,IN2_GPIO_PIN)

#define IN3_HIGH        digitalHi(IN3_GPIO_PORT,IN3_GPIO_PIN)
#define IN3_LOW         digitalLo(IN3_GPIO_PORT,IN3_GPIO_PIN)

#define IN4_HIGH        digitalHi(IN4_GPIO_PORT,IN4_GPIO_PIN)
#define IN4_LOW         digitalLo(IN4_GPIO_PORT,IN4_GPIO_PIN)


void Curtains_Init(void);
void SysTick_Delay_Ms(__IO uint32_t ms);	//�δ���ʱ
void stepper(uint8_t dir,int speed);
void Open_Curtains(void);				//����
void Close_Curtains(void);			//�ش�
void Curtains_Control(void);
#endif
