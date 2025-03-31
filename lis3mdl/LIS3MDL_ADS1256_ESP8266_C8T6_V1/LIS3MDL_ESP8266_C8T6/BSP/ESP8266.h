#ifndef ESP8266_H
#define ESP8266_H

#include <stdint.h>
#include "usart.h"
#include <stdio.h>
#include <string.h> 
#include "lis3mdl.h"

#define HUART        huart1
#define ESP8266_UART huart2
#define PC_UART      huart1

#define ESP8266_MAX     2048
#define WIFI_EN_PORT    GPIOA
#define WIFI_EN_PIN     GPIO_PIN_1
#define WIFI_RST_PORT   GPIOA
#define WIFI_RST_PIN    GPIO_PIN_0

#define WIFI_CH_EN()           HAL_GPIO_WritePin(WIFI_EN_PORT, WIFI_EN_PIN, GPIO_PIN_SET)
#define WIFI_RST_HIGH()        HAL_GPIO_WritePin(WIFI_RST_PORT, WIFI_RST_PIN, GPIO_PIN_SET)
#define WIFI_RST_LOW()         HAL_GPIO_WritePin(WIFI_RST_PORT, WIFI_RST_PIN, GPIO_PIN_RESET)



//声明要使用的变量


uint8_t ESP8266_SendCommand(uint8_t cmd[], uint8_t ack[], int timeout);
uint8_t ESP8266_Init(void);
void PC_To_Esp8266_Message(void);
void ESP8266_To_PC_Message(void);

#endif