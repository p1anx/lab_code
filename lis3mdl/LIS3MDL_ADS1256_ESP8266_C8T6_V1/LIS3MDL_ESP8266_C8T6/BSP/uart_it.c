#include "uart_it.h"
#include "ESP8266.h"
#include <string.h>

#define MAX 1024
#define MAX_LEN 1024

uint8_t RxBuffer[BUFFERSIZE];
uint8_t RxBufferUart1[BUFFERSIZE];
uint8_t revCount = 0;



uint8_t USART1Rev=0;
uint8_t USART3Rev=0;
uint8_t USART3Rev_Flag=0;
uint8_t USART1Rev_Flag=0;

uint8_t revBuff[MAX];
typedef struct{
	uint8_t Txdata[MAX];
	uint8_t Txcnt;
	uint8_t Rxdata[MAX];
	uint16_t Rxcnt;
	uint8_t Rxflag;
}WIFI_DATA;


WIFI_DATA wifi={0};

// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
//   UNUSED(huart);
//   if(huart->Instance == USART1){

//         HAL_UART_Transmit(&huart1, RxBufferUart1, BUFFERSIZE, HAL_MAX_DELAY);   

//   }
//   HAL_UART_Receive_IT(&huart1, RxBufferUart1, 1);
// }

//串口空闲中断
// void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
// {
// 	if(huart->Instance==USART1)
// 	{
// 		//把收到的一包数据通过串口回传
// 		// HAL_UART_Transmit(&huart1,RxBuffer,Size,0xff);
//         printf("rx:%s\n", RxBuffer);
// 		//再次开启空闲中断接收，不然只会接收一次数据
// 		HAL_UARTEx_ReceiveToIdle_IT(&huart1,RxBuffer,BUFFERSIZE);
// 	}
// }

//空闲中断回调函数
// void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
//     if(huart->Instance==USART3)
// 	{
// 		wifi.Rxflag=1;
// 		revCount=0;
//         HAL_UARTEx_ReceiveToIdle_IT(&huart3,&USART3Rev,1);
// 	}
// }
// void HAL_UART_IdleCallback(UART_HandleTypeDef *huart)
// {
// 	if(huart->Instance==USART3)
// 	{
// 		wifi.Rxflag=1;
// 		revCount=0;
// 	}
// }
//串口接收回调函数
// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
// {
// 	if(huart->Instance==USART1)
// 	{
		
// 		revBuff[revCount++]=USART1Rev;
// //		UART5->DR=USART5Rev;
// 		HAL_UART_Receive_IT(&huart1,&USART1Rev,1);
// 	}
	
// 	if(huart->Instance==USART3)
// 	{
// 		wifi.Rxdata[wifi.Rxcnt++]=USART3Rev;
// 		USART1->DR=USART3Rev;
// 		HAL_UART_Receive_IT(&huart3,&USART3Rev,1);
// 	}
// }

void Clean_buff(void)
{
	memset(wifi.Rxdata,0,sizeof(wifi.Rxdata));
	wifi.Rxcnt=0;
	wifi.Rxflag=0;
	wifi.Txcnt=0;
}
//串口发送字符串
void USART5_SendStr(uint8_t *data)
{
	while(*data)
	{
		HAL_UART_Transmit(&huart3,(uint8_t *)data,1,100);
		data++;
	}
	//HAL_UART_Transmit(&huart5,data,sizeof(data),HAL_MAX_DELAY);    //错误，直接发一串数据过去不行
}

void USART5_SendStrlen(uint8_t *data,uint16_t len)
{
	int i=0;
	for(i=0;i<len;i++)
	{
		HAL_UART_Transmit(&huart3,(uint8_t *)data,1,100);
		data++;
	}
}


uint8_t WIFI_SendCMD(uint8_t *CMD,uint8_t *ACK,uint16_t timeout)
{
//	printf("%s\r\n",CMD);
	Clean_buff();
	USART5_SendStr(CMD);
	
	while(timeout--)
	{
		if(wifi.Rxflag==1)
		{
			if(strstr((char *)wifi.Rxdata,(char *)ACK)!=NULL)
			{
                printf("OK\n");
				return 1;
			}
		}
		HAL_Delay(1);
	}
	return 0;
}	
uint8_t WIFI_SendCMD1(uint8_t *CMD,uint8_t *ACK,uint16_t timeout)
{
//	printf("%s\r\n",CMD);
	Clean_buff();
	USART5_SendStr(CMD);
	while(timeout--)
	{
		if(wifi.Rxflag==1)
		{
			if(strstr((char *)wifi.Rxdata,(char *)ACK)!=NULL)
			{
                printf("OK\n");
				return 1;
			}
		}
		HAL_Delay(1);
	}
 

	return 0;
}	

uint8_t WIFI_Init(void)
{
	if(WIFI_SendCMD((uint8_t *)"AT\r\n",(uint8_t *)"OK",500)==0) return 1;
    
	if(WIFI_SendCMD((uint8_t *)"AT+CWMODE=2\r\n",(uint8_t *)"OK",2000)==0) return 2;
    if(WIFI_SendCMD((uint8_t *)"AT+RST\r\n",(uint8_t *)"ready",500)==0) return 1;
    if(WIFI_SendCMD((uint8_t *)"AT+CWSAP=\"esp8266\",\"12345678\"\r\n",(uint8_t *)"OK",12000)==0) return 3;
    
	// if(WIFI_SendCMD((uint8_t *)"AT+CWJAP=\"PC-20220213UNDT 2427\",\"12345678\"\r\n",(uint8_t *)"OK",12000)==0) return 3;
	// if(WIFI_SendCMD((uint8_t *)"AT+CIPSTART=\"TCP\",\"iot-06z00d6p8f3ii1c.mqtt.iothub.aliyuncs.com\",1883\r\n",(uint8_t *)"OK",12000)==0) return 4;
	if(WIFI_SendCMD((uint8_t *)"AT+CIPMODE=1\r\n",(uint8_t *)"OK",5000)==0) return 5;
	// if(WIFI_SendCMD((uint8_t *)"AT+CIPSEND\r\n",(uint8_t *)">",5000)==0) return 6;
	return 0;
}

uint8_t WIFI_Init1(void)
{
	WIFI_SendCMD1((uint8_t *)"AT\r\n",(uint8_t *)"OK",500);
    WIFI_SendCMD1((uint8_t *)"AT+RST\r\n",(uint8_t *)"OK",500);
	WIFI_SendCMD1((uint8_t *)"AT+CWMODE=2\r\n",(uint8_t *)"OK",2000);
    WIFI_SendCMD1((uint8_t *)"AT+CWSAP=\"esp8266\",\"12345678\",1,3\r\n",(uint8_t *)"OK",12000);
    WIFI_SendCMD1((uint8_t *)"AT+CIPMUX=0\r\n",(uint8_t *)"OK",2000);
	// if(WIFI_SendCMD((uint8_t *)"AT+CWJAP=\"PC-20220213UNDT 2427\",\"12345678\"\r\n",(uint8_t *)"OK",12000)==0) return 3;
	// if(WIFI_SendCMD((uint8_t *)"AT+CIPSTART=\"TCP\",\"iot-06z00d6p8f3ii1c.mqtt.iothub.aliyuncs.com\",1883\r\n",(uint8_t *)"OK",12000)==0) return 4;
	WIFI_SendCMD1((uint8_t *)"AT+CIPMODE=1\r\n",(uint8_t *)"OK",5000);
	WIFI_SendCMD1((uint8_t *)"AT+CIPSEND\r\n",(uint8_t *)">",5000);
	return 0;
}
uint8_t counter = 0;
void ESP8266_SendCommand1(const char *command) {

  HAL_UART_Transmit(&huart3, (uint8_t *)command, strlen(command), HAL_MAX_DELAY);
  HAL_Delay(1000);
  printf("ok%d\n", counter);
  counter++;
}

// uint8_t WIFI_Init2(void)
// {
//     char cmd1[] = "AT\r\n";
//     char cmd2[] = "AT+RST\r\n";
//     char cmd3[] = "AT+CWMODE=2\r\n";
//     char cmd4[] = "AT+CWSAP==\"esp8266\",\"12345678\",1,3\r\n";
//     char cmd5[] = "AT+CIPMUX=0\r\n";
//     char cmd6[] = "AT+CIPMODE=1\r\n";
//     char cmd7[] = "AT+CIPSEND\r\n";

//     ESP8266_SendCommand(cmd1);
//     ESP8266_SendCommand(cmd2);
//     ESP8266_SendCommand(cmd2);
//     ESP8266_SendCommand(cmd2);
//     ESP8266_SendCommand(cmd2);
//     ESP8266_SendCommand(cmd2);
//     ESP8266_SendCommand(cmd2);


// 	return 0;
// }

