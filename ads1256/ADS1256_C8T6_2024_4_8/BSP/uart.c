/*
 * uart.c
 *
 *  Created on: Dec 16, 2022
 *      Author: XWJ
 */

#include "uart.h"

#ifdef __GNUC__
#define PUTCHAR int __io_putchar(int ch)
#else
#define PUTCHAR int	fputc(int ch, FILE* f)
#endif


PUTCHAR
{
	HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, 1000);
	return ch;
}

int fgetc(FILE* f){
	uint8_t ch = 0;
	HAL_UART_Receive(&huart2, &ch, 1, 1000);
	return ch;
}
