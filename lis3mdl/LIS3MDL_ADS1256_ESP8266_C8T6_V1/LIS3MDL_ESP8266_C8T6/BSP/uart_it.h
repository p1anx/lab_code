#ifndef UART_IT_H
#define UART_IT_H

#include "usart.h"
#include <string.h>

#define BUFFERSIZE 3


// uint8_t RxBuffer[BUFFERSIZE];
// uint8_t RxBufferUart1[BUFFERSIZE];







// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);//串口中断回调函数
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);//串口空闲中断回调函数
// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_UART_IdleCallback(UART_HandleTypeDef *huart);
void Clean_buff(void);
uint8_t WIFI_Init(void);
uint8_t WIFI_SendCMD(uint8_t *CMD,uint8_t *ACK,uint16_t timeout);
uint8_t WIFI_Init1(void);
uint8_t WIFI_SendCMD1(uint8_t *CMD,uint8_t *ACK,uint16_t timeout);
uint8_t WIFI_Init2(void);
void USART5_SendStrlen(uint8_t *data,uint16_t len);
void USART5_SendStr(uint8_t *data);
void ESP8266_SendCommand1(const char *command);

#endif