//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

//		�ļ����� 	esp8266.c
//		���ڣ� 		2022-01-08
//		˵���� 		ESP8266�ļ�����
//---------------------------------------------------------------------------------


//��Ƭ��ͷ�ļ�
#include "stm32f10x.h"

//�����豸����
#include "esp8266.h"

//Ӳ������
#include "delay.h"
#include "usart.h"

//C��
#include <string.h>
#include <stdio.h>
#include "OLED_I2C.h"

#define ESP8266_WIFI_INFO			"AT+CWJAP=\"OPPO\",\"My20000911\"\r\n"           //WIFI����������

#define ESP8266_ONENET_INFO		"AT+CIPSTART=\"TCP\",\"183.230.40.39\",6002\r\n"


unsigned char esp8266_buf[128];
unsigned short esp8266_cnt = 0, esp8266_cntPre = 0;


//==========================================================
//	�������ƣ�	ESP8266_Clear
//
//	�������ܣ�	��ջ���
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void ESP8266_Clear(void)
{

	memset(esp8266_buf, 0, sizeof(esp8266_buf));
	esp8266_cnt = 0;

}

//==========================================================
//	�������ƣ�	ESP8266_WaitRecive
//
//	�������ܣ�	�ȴ��������
//
//	��ڲ�����	��
//
//	���ز�����	REV_OK-�������		REV_WAIT-���ճ�ʱδ���
//
//	˵����		ѭ�����ü���Ƿ�������
//==========================================================
_Bool ESP8266_WaitRecive(void)
{

	if(esp8266_cnt == 0) 							//������ռ���Ϊ0 ��˵��û�д��ڽ��������У�����ֱ����������������
		return REV_WAIT;
		
	if(esp8266_cnt == esp8266_cntPre)				//�����һ�ε�ֵ�������ͬ����˵���������
	{
		esp8266_cnt = 0;							//��0���ռ���
			
		return REV_OK;								//���ؽ�����ɱ�־
	}
		
	esp8266_cntPre = esp8266_cnt;					//��Ϊ��ͬ
	
	return REV_WAIT;								//���ؽ���δ��ɱ�־

}

//==========================================================
//	�������ƣ�	ESP8266_SendCmd
//
//	�������ܣ�	��������
//
//	��ڲ�����	cmd������
//				res����Ҫ���ķ���ָ��
//
//	���ز�����	0-�ɹ�	1-ʧ��
//
//	˵����		
//==========================================================
_Bool ESP8266_SendCmd(char *cmd, char *res)
{
	
	unsigned char timeOut = 200;

	Usart_SendString(USART2, (unsigned char *)cmd, strlen((const char *)cmd));
	
	while(timeOut--)
	{
		if(ESP8266_WaitRecive() == REV_OK)							//����յ�����
		{
			if(strstr((const char *)esp8266_buf, res) != NULL)		//����������ؼ���
			{
				ESP8266_Clear();									//��ջ���
				
				return 0;
			}
		}
		
		delay_ms(10);
	}
	
	return 1;

}

//==========================================================
//	�������ƣ�	ESP8266_SendData
//
//	�������ܣ�	��������
//
//	��ڲ�����	data������
//				len������
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void ESP8266_SendData(unsigned char *data, unsigned short len)
{

	char cmdBuf[32];
	
	ESP8266_Clear();								//��ս��ջ���
	sprintf(cmdBuf, "AT+CIPSEND=%d\r\n", len);		//��������
	if(!ESP8266_SendCmd(cmdBuf, ">"))				//�յ���>��ʱ���Է�������
	{
		Usart_SendString(USART2, data, len);		//�����豸������������
	}

}

//==========================================================
//	�������ƣ�	ESP8266_GetIPD
//
//	�������ܣ�	��ȡƽ̨���ص�����
//
//	��ڲ�����	�ȴ���ʱ��(����10ms)
//
//	���ز�����	ƽ̨���ص�ԭʼ����
//
//	˵����		��ͬ�����豸���صĸ�ʽ��ͬ����Ҫȥ����
//				��ESP8266�ķ��ظ�ʽΪ	"+IPD,x:yyy"	x�������ݳ��ȣ�yyy����������
//==========================================================
unsigned char *ESP8266_GetIPD(unsigned short timeOut)
{

	char *ptrIPD = NULL;
	
	do
	{
		if(ESP8266_WaitRecive() == REV_OK)								//����������
		{
			ptrIPD = strstr((char *)esp8266_buf, "IPD,");				//������IPD��ͷ
			if(ptrIPD == NULL)											//���û�ҵ���������IPDͷ���ӳ٣�������Ҫ�ȴ�һ�ᣬ�����ᳬ���趨��ʱ��
			{
				//UsartPrintf(USART_DEBUG, "\"IPD\" not found\r\n");
			}
			else
			{
				ptrIPD = strchr(ptrIPD, ':');							//�ҵ�':'
				if(ptrIPD != NULL)
				{
					ptrIPD++;
					return (unsigned char *)(ptrIPD);
				}
				else
					return NULL;
				
			}
		}
		
		delay_ms(5);													//��ʱ�ȴ�
	} while(timeOut--);
	
	return NULL;														//��ʱ��δ�ҵ������ؿ�ָ��

}

//==========================================================
//	�������ƣ�	ESP8266_Init
//
//	�������ܣ�	��ʼ��ESP8266
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
int i;
void ESP8266_Init(void)
{
	
	GPIO_InitTypeDef GPIO_Initure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	//ESP8266��λ����
	GPIO_Initure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Initure.GPIO_Pin = GPIO_Pin_14;					//GPIOC14-��λ
	GPIO_Initure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_Initure);
	
	GPIO_WriteBit(GPIOC, GPIO_Pin_14, Bit_RESET);
	delay_ms(250);
	GPIO_WriteBit(GPIOC, GPIO_Pin_14, Bit_SET);
	delay_ms(500);
	
	ESP8266_Clear();
	
	OLED_ShowStr(35,1,(uint8_t *)"ESP8266",2);
	OLED_ShowCN(33,3,7);OLED_ShowCN(49,3,8);OLED_ShowCN(65,3,9);OLED_ShowCN(81,3,10);//oled��ʾ��ESP8266��ʼ���С�
	for(i=0;i<10;i++){OLED_progress_bar(6,i);}//��ʾ������
	
	//UsartPrintf(USART_DEBUG, "1. AT\r\n");
	while(ESP8266_SendCmd("AT\r\n", "OK"))
	delay_ms(500);
	//UsartPrintf(USART_DEBUG, "2. CWMODE\r\n");
	while(ESP8266_SendCmd("AT+CWMODE=1\r\n", "OK"))
	delay_ms(500);
	for(i=10;i<20;i++){OLED_progress_bar(6,i);}//��ʾ������    
	//UsartPrintf(USART_DEBUG, "3. AT+CWDHCP\r\n");
	while(ESP8266_SendCmd("AT+CWDHCP=1,1\r\n", "OK"))
	delay_ms(500);
	//UsartPrintf(USART_DEBUG, "4. CWJAP\r\n");
	while(ESP8266_SendCmd(ESP8266_WIFI_INFO, "GOT IP"))
	delay_ms(500);
	for(i=20;i<30;i++){OLED_progress_bar(6,i);}//��ʾ������
	//UsartPrintf(USART_DEBUG, "5. CIPSTART\r\n");
	while(ESP8266_SendCmd(ESP8266_ONENET_INFO, "CONNECT"))
	delay_ms(500);
	for(i=30;i<51;i++){OLED_progress_bar(6,i);}//��ʾ������
	//UsartPrintf(USART_DEBUG, "6. ESP8266 Init OK\r\n");
  OLED_ShowCN(24,3,7);OLED_ShowCN(40,3,8);OLED_ShowCN(56,3,9);OLED_ShowCN(72,3,11);OLED_ShowCN(88,3,12);//oled��ʾ��ESP8266��ʼ����ɡ�
}

//==========================================================
//	�������ƣ�	USART2_IRQHandler
//
//	�������ܣ�	����2�շ��ж�
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void USART2_IRQHandler(void)
{

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //�����ж�
	{
		if(esp8266_cnt >= sizeof(esp8266_buf))	esp8266_cnt = 0; //��ֹ���ڱ�ˢ��
		esp8266_buf[esp8266_cnt++] = USART2->DR;
		
		USART_ClearFlag(USART2, USART_FLAG_RXNE);
	}

}





