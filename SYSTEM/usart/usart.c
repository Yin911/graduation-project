
//Ӳ������
#include "main.h"
#include "usart.h"
#include "delay.h"

//C��
#include <stdarg.h>
#include <string.h>
#include <stdio.h>


/*
************************************************************
*	�������ƣ�	Usart1_Init
*
*	�������ܣ�	����1��ʼ��
*
*	��ڲ�����	baud���趨�Ĳ�����
*
*	���ز�����	��
*
*	˵����		TX-PA9		RX-PA10
************************************************************
*/
void Usart1_Init(unsigned int baud)
{

	GPIO_InitTypeDef gpioInitStruct;                           //����GPIO�ṹ����� 
	USART_InitTypeDef usartInitStruct;                         //���崮�ڽṹ�����
	NVIC_InitTypeDef nvicInitStruct;                           //???????????????
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);      //ʹ��GPIOC��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);   //�����Ż�
	
	//PA9	TXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;                 //����PA9Ϊ�����������     ȫ˫��
	gpioInitStruct.GPIO_Pin = GPIO_Pin_9;                       //����TX����
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;               //����PA9����
	GPIO_Init(GPIOA, &gpioInitStruct);                          //GPIO��ʼ������
	
	//PA10	RXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;            //����PA10Ϊ��������       ȫ˫��
	gpioInitStruct.GPIO_Pin = GPIO_Pin_10;                       //����RX����
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;                //����PA10����
	GPIO_Init(GPIOA, &gpioInitStruct);                           //GPIO��ʼ������
	
	usartInitStruct.USART_BaudRate = baud;                       //������    �β�
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������������
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	 //���պͷ���ģʽ
	usartInitStruct.USART_Parity = USART_Parity_No;							 //��У��
	usartInitStruct.USART_StopBits = USART_StopBits_1;					 //1λֹͣλ
	usartInitStruct.USART_WordLength = USART_WordLength_8b;			 //8λ����λ
	USART_Init(USART1, &usartInitStruct);                        //���ڳ�ʼ������
	
	USART_Cmd(USART1, ENABLE);														       //ʹ�ܴ���
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);							 //ʹ�ܽ����ж�
	
	nvicInitStruct.NVIC_IRQChannel = USART1_IRQn;                //?????????????????
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicInitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&nvicInitStruct);

}

/*
************************************************************
*	�������ƣ�	Usart2_Init
*
*	�������ܣ�	����2��ʼ��
*
*	��ڲ�����	baud���趨�Ĳ�����
*
*	���ز�����	��
*
*	˵����		TX-PA2		RX-PA3
************************************************************
*/
void Usart2_Init(unsigned int baud)
{

	GPIO_InitTypeDef gpioInitStruct;
	USART_InitTypeDef usartInitStruct;
	NVIC_InitTypeDef nvicInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	//PA2	TXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_2;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStruct);
	
	//PA3	RXD
	gpioInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpioInitStruct.GPIO_Pin = GPIO_Pin_3;
	gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpioInitStruct);
	
	usartInitStruct.USART_BaudRate = baud;
	usartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//��Ӳ������
	usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//���պͷ���
	usartInitStruct.USART_Parity = USART_Parity_No;									//��У��
	usartInitStruct.USART_StopBits = USART_StopBits_1;								//1λֹͣλ
	usartInitStruct.USART_WordLength = USART_WordLength_8b;							//8λ����λ
	USART_Init(USART2, &usartInitStruct);
	
	USART_Cmd(USART2, ENABLE);														//ʹ�ܴ���
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);									//ʹ�ܽ����ж�
	
	nvicInitStruct.NVIC_IRQChannel = USART2_IRQn;
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicInitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicInitStruct);

}

/*
************************************************************
*	�������ƣ�	Usart3_Init
*
*	�������ܣ�	����3��ʼ��
*
*	��ڲ�����	baud���趨�Ĳ�����
*
*	���ز�����	��
*
*	˵����		TX-PB10		RX-PB11
************************************************************
*/
void Usart3_Init(unsigned int baud)
{
	GPIO_InitTypeDef GPIO_InitStruct;                         //����GPIO�ṹ�����   
	USART_InitTypeDef USART_InitStruct;                       //���崮�ڽṹ�����
	NVIC_InitTypeDef nvicInitStruct;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);      //ʹ��GPIOC��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); 
	
  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;                //����B10Ϊ�����������     ȫ˫��   
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;                     //����TX����
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;              //����B10����
	GPIO_Init(GPIOB,&GPIO_InitStruct);                        //GPIO��ʼ������
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;          //����B11Ϊ��������   
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_11;                     //����RX����
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;              //����B11����
	GPIO_Init(GPIOB,&GPIO_InitStruct);                        //GPIO��ʼ������
	 
	
	USART_InitStruct.USART_BaudRate=baud;                      //�����ʲ���
  USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;   //��Ӳ������������
	USART_InitStruct.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;   //���ͽ���ģʽ
	USART_InitStruct.USART_Parity=USART_Parity_No;             //����żУ��
	USART_InitStruct.USART_StopBits=USART_StopBits_1;          //ֹͣλ1λ
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;     //�ֳ�8λ
	USART_Init(USART3,&USART_InitStruct);                      //���ڳ�ʼ������
	
	USART_Cmd(USART3,ENABLE);                                  //ʹ��USART3
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);						 //ʹ�ܽ����ж�
	
	nvicInitStruct.NVIC_IRQChannel = USART3_IRQn;
	nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
	nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicInitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&nvicInitStruct);

	
	
}

/*
************************************************************
*	�������ƣ�	USART1_IRQHandler
*
*	�������ܣ�	����1�շ��ж�
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void USART1_IRQHandler(void)
{

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //�����жϣ�����������
	{
		USART_ClearFlag(USART1, USART_FLAG_RXNE);
	}
	if(USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)
	{
		USART_ClearFlag(USART1, USART_FLAG_ORE); //�������ж�
	}

}






#define Max_BUFF_Len 6
unsigned char Uart3_Buffer[Max_BUFF_Len];
unsigned int Uart3_Rx=0;

/*
************************************************************
*	�������ƣ�	USART3_IRQHandler
*
*	�������ܣ�	����3�շ��ж�
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void USART3_IRQHandler() 
{
      if(USART_GetITStatus(USART3,USART_IT_RXNE) != RESET)         //�жϲ���
       {       
				 
 
			 
	      }
}



/*
************************************************************
*	�������ƣ�	Usart_SendString
*
*	�������ܣ�	�������ݷ���
*
*	��ڲ�����	USARTx��������
*				str��Ҫ���͵�����
*				len�����ݳ���
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len)
{

	unsigned short count = 0;
	
	for(; count < len; count++)
	{
		USART_SendData(USARTx, *str++);									//��������
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);		//�ȴ��������
	}

}

/*
************************************************************
*	�������ƣ�	UsartPrintf
*
*	�������ܣ�	��ʽ����ӡ
*
*	��ڲ�����	USARTx��������
*				fmt����������
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...)
{

	unsigned char UsartPrintfBuf[296];
	va_list ap;
	unsigned char *pStr = UsartPrintfBuf;
	
	va_start(ap, fmt);
	vsnprintf((char *)UsartPrintfBuf, sizeof(UsartPrintfBuf), fmt, ap);							//��ʽ��
	va_end(ap);
	
	while(*pStr != 0)
	{
		USART_SendData(USARTx, *pStr++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	}

}


