/**
	************************************************************
	************************************************************
	************************************************************
	*	文件名： 	onenet.c
	*
	*	日期： 		2017-05-08
	*
	*	版本： 		V1.1
	*
	*	说明： 		与onenet平台的数据交互接口层
	*
	*	修改记录：	V1.0：协议封装、返回判断都在同一个文件，并且不同协议接口不同。
	*				V1.1：提供统一接口供应用层使用，根据不同协议文件来封装协议相关的内容。
	************************************************************
	************************************************************
	************************************************************
**/

//单片机头文件
#include "stm32f10x.h"

//网络设备
#include "esp8266.h"

//协议文件
#include "onenet.h"
#include "mqttkit.h"

//硬件驱动
#include "usart.h"
#include "delay.h"
#include "main.h"

//C库
#include <string.h>
#include <stdio.h>


#include "led.h"
#include "door_bsp.h"
#include "fan.h"

#define PROID		"571810"   //产品ID

#define AUTH_INFO	"abc123"  //鉴权信息

#define DEVID		"1046057804"//设备ID


extern unsigned char esp8266_buf[128];


//==========================================================
//	函数名称：	OneNet_DevLink
//
//	函数功能：	与onenet创建连接
//
//	入口参数：	无
//
//	返回参数：	1-成功	0-失败
//
//	说明：		与onenet平台建立连接
//==========================================================
_Bool OneNet_DevLink(void)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};					//协议包

	unsigned char *dataPtr;
	
	_Bool status = 1;
	OLED_CLS();//OLED清屏
  OLED_ShowCN(15,2,15);OLED_ShowCN(31,2,16);OLED_ShowCN(47,2,17);OLED_ShowCN(63,2,13);OLED_ShowCN(79,2,14);OLED_ShowCN(95,2,10);//oled显示“服务器连接中”
	//UsartPrintf(USART_DEBUG, "OneNet_DevLink\r\n"
	//						"PROID: %s,	AUIF: %s,	DEVID:%s\r\n"
   //                     , PROID, AUTH_INFO, DEVID);
	
	if(MQTT_PacketConnect(PROID, AUTH_INFO, DEVID, 256, 0, MQTT_QOS_LEVEL0, NULL, NULL, 0, &mqttPacket) == 0)
	{
		ESP8266_SendData(mqttPacket._data, mqttPacket._len);			//上传平台
		
		dataPtr = ESP8266_GetIPD(250);									//等待平台响应
		if(dataPtr != NULL)
		{
			if(MQTT_UnPacketRecv(dataPtr) == MQTT_PKT_CONNACK)
			{
				switch(MQTT_UnPacketConnectAck(dataPtr))
				{
					case 0:UsartPrintf(USART_DEBUG, "Tips:	连接成功\r\n");status = 0;
					       OLED_CLS();//OLED清屏
					       OLED_ShowCN(31,4,13);OLED_ShowCN(47,4,14);OLED_ShowCN(63,4,12);OLED_ShowCN(79,4,18);//oled显示“连接成功”	
                 delay_ms(500);					
					       break;
					case 1:UsartPrintf(USART_DEBUG, "WARN:	连接失败：协议错误\r\n");break;
					case 2:UsartPrintf(USART_DEBUG, "WARN:	连接失败：非法的clientid\r\n");break;
					case 3:UsartPrintf(USART_DEBUG, "WARN:	连接失败：服务器失败\r\n");break;
					case 4:UsartPrintf(USART_DEBUG, "WARN:	连接失败：用户名或密码错误\r\n");break;
					case 5:UsartPrintf(USART_DEBUG, "WARN:	连接失败：非法链接(比如token非法)\r\n");break;
					
					default:UsartPrintf(USART_DEBUG, "ERR:	连接失败：未知错误\r\n");break;
				}
			}
		}
		
		MQTT_DeleteBuffer(&mqttPacket);								//删包
	}
	else
	{	UsartPrintf(USART_DEBUG, "WARN:	MQTT_PacketConnect Failed\r\n");
	  OLED_ShowCN(47,4,26);OLED_ShowCN(63,4,27);OLED_ShowCN(47,6,28);OLED_ShowCN(63,6,29);//链接失败，重连
	}
	return status;
	
}





unsigned char OneNet_FillBuf(char *buf)
{
	
	char text[32];
	memset(text, 0, sizeof(text));
	strcpy(buf, ",;");
	
	//温度
	memset(text, 0, sizeof(text));
	sprintf(text, "Temperature,%d;", send_data.temp);
	strcat(buf, text);
	
	//湿度
	memset(text, 0, sizeof(text));
	sprintf(text, "Humidity,%d;", send_data.humi);
	strcat(buf, text);
	
	//CO2
	memset(text, 0, sizeof(text));
  sprintf(text, "CO2,%.1f;", send_data.CO2);
	strcat(buf, text);
	
	//光照
	memset(text, 0, sizeof(text));
	sprintf(text, "Light,%d;", send_data.Light);
	strcat(buf, text);
	
	//风扇
	memset(text, 0, sizeof(text));
	sprintf(text, "Fan,%d;", send_data.FAN_FLAG);
	strcat(buf, text);

  //水泵
  memset(text, 0, sizeof(text));
	sprintf(text, "Led,%d;", send_data.LED_FLAG);
	strcat(buf, text);
	
	//警报
	memset(text, 0, sizeof(text));
	sprintf(text, "Warning,%d;", send_data.WARNING_FLAG);
	strcat(buf, text);
	
	
	return strlen(buf);

}



//==========================================================
//	函数名称：	OneNet_SendData
//
//	函数功能：	上传数据到平台
//
//	入口参数：	type：发送数据的格式
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void OneNet_SendData(void)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};												//协议包
	
	char buf[128];
	
	short body_len = 0, i = 0;
	
	//UsartPrintf(USART_DEBUG, "Tips:	OneNet_SendData-MQTT\r\n");
	
	memset(buf, 0, sizeof(buf));
	
	body_len = OneNet_FillBuf(buf);																	//获取当前需要发送的数据流的总长度
	
	if(body_len)
	{
		if(MQTT_PacketSaveData(DEVID, body_len, NULL, 5, &mqttPacket) == 0)							//封包
		{
			for(; i < body_len; i++)
				mqttPacket._data[mqttPacket._len++] = buf[i];
			
			ESP8266_SendData(mqttPacket._data, mqttPacket._len);									//上传数据到平台
			//UsartPrintf(USART_DEBUG, "Send %d Bytes\r\n", mqttPacket._len);
			
			MQTT_DeleteBuffer(&mqttPacket);															//删包
		}
		else  {;}
			//UsartPrintf(USART_DEBUG, "WARN:	EDP_NewBuffer Failed\r\n");
	}
	
}

//==========================================================
//	函数名称：	OneNet_RevPro
//
//	函数功能：	平台返回数据检测
//
//	入口参数：	dataPtr：平台返回的数据
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void OneNet_RevPro(unsigned char *cmd)
{
	
	MQTT_PACKET_STRUCTURE mqttPacket = {NULL, 0, 0, 0};								//协议包
	
	char *req_payload = NULL;
	char *cmdid_topic = NULL;
	
	unsigned short req_len = 0;
	
	unsigned char type = 0;
	
	short result = 0;

	char *dataPtr = NULL;
	char numBuf[10];
	int num = 0;
	
	type = MQTT_UnPacketRecv(cmd);
	switch(type)
	{
		case MQTT_PKT_CMD:															//命令下发
			
			result = MQTT_UnPacketCmd(cmd, &cmdid_topic, &req_payload, &req_len);	//解出topic和消息体
			if(result == 0)
			{
				UsartPrintf(USART_DEBUG, "cmdid: %s, req: %s, req_len: %d\r\n", cmdid_topic, req_payload, req_len);
				
				if(MQTT_PacketCmdResp(cmdid_topic, req_payload, &mqttPacket) == 0)	//命令回复组包
				{
					UsartPrintf(USART_DEBUG, "Tips:	Send CmdResp\r\n");
					
					ESP8266_SendData(mqttPacket._data, mqttPacket._len);			//回复命令
					MQTT_DeleteBuffer(&mqttPacket);									          //删包
				}
			}
		
		break;
			
		case MQTT_PKT_PUBACK:														                //发送Publish消息，平台回复的Ack
		
			if(MQTT_UnPacketPublishAck(cmd) == 0)
				UsartPrintf(USART_DEBUG, "Tips:	MQTT Publish Send OK\r\n");
			
		break;
		
		default:
			result = -1;
		break;
	}
	
	ESP8266_Clear();									          //清空缓存
	
	if(result == -1)
		return;
	
	dataPtr = strchr(req_payload, ':');					//搜索'}'

	if(dataPtr != NULL && result != -1)					//如果找到了
	{
		dataPtr++;
		
		while(*dataPtr >= '0' && *dataPtr <= '9')	//判断是否是下发的命令控制数据
		{
			numBuf[num++] = *dataPtr++;
		}
		numBuf[num] = 0;
		
		num = atoi((const char *)numBuf);				  //转为数值形式
		
//===========================================接受onenet发来的数据==================================================	
		if(strstr((char *)req_payload, "FAN_FLAG"))		           
		{
			send_data.FAN_FLAG = num;
			fan_control();
		}
		if(strstr((char *)req_payload, "LED_FLAG"))		           
		{
			send_data.LED_FLAG = num;
			led_control();
		}
	
		cmd_rev_flag = 1;
		
	}
//===================================================================================================================
	if(type == MQTT_PKT_CMD || type == MQTT_PKT_PUBLISH)
	{
		MQTT_FreeBuffer(cmdid_topic);
		MQTT_FreeBuffer(req_payload);
	}

}
