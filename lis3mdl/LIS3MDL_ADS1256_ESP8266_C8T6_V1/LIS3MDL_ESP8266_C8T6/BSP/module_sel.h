#ifndef _MODULE_SEL_H_
#define _MODULE_SEL_H_

#include "stm32f1xx.h"
#include "gpio.h"
#include "lis3mdl.h"
#include "ads1256.h"
#include "ESP8266.h"


#define LED1_PIN GPIO_PIN_14
#define LED1_PORT GPIOC

#define LED2_PIN GPIO_PIN_15
#define LED2_PORT GPIOC

#define KEY1_PIN GPIO_PIN_12
#define KEY1_PORT GPIOB

#define KEY2_PIN GPIO_PIN_15
#define KEY2_PORT GPIOA

void  Led1_sel(void);
void  Led2_sel(void);

#endif