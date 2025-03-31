#ifndef __OLED_H
#define __OLED_H 

#include "main.h"

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

#define ZK_CS_Pin               GPIO_PIN_1
#define ZK_CS_GPIO_Port         GPIOA
#define OLED_CS_Pin             GPIO_PIN_2
#define OLED_CS_GPIO_Port       GPIOA
#define OLED_DC_Pin             GPIO_PIN_3
#define OLED_DC_GPIO_Port       GPIOA
#define OLED_RES_Pin            GPIO_PIN_4
#define OLED_RES_GPIO_Port      GPIOA

#define OLED_RES_Clr() HAL_GPIO_WritePin(OLED_RES_GPIO_Port, OLED_RES_Pin, GPIO_PIN_RESET)//RES
#define OLED_RES_Set() HAL_GPIO_WritePin(OLED_RES_GPIO_Port, OLED_RES_Pin, GPIO_PIN_SET)

#define OLED_DC_Clr()  HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_RESET)//DC
#define OLED_DC_Set()  HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_SET)

#define OLED_CS_Clr()  HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, GPIO_PIN_RESET)//CS
#define OLED_CS_Set()  HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, GPIO_PIN_SET)

#define ZK_CS_Clr()    HAL_GPIO_WritePin(ZK_CS_GPIO_Port,ZK_CS_Pin, GPIO_PIN_RESET)//CS2
#define ZK_CS_Set()    HAL_GPIO_WritePin(ZK_CS_GPIO_Port,ZK_CS_Pin, GPIO_PIN_SET)





#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

//OLED��ʾ����
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void OLED_WR_Byte(u8 dat,u8 cmd);
void OLED_Clear(void);
void OLED_address(u8 x,u8 y);
void OLED_Display_128x64(u8 *dp);
void OLED_Display_16x16(u8 x,u8 y,u8 *dp);
void OLED_Display_8x16(u8 x,u8 y,u8 *dp);
void OLED_Init(void);
void OLED_Init0(void);
void OLED_Display_Demo(void);
void OLED_SetPos(u8 page, u8 col);
void OLED_PutChar(int page, int col, char c);
void OLED_Print(int col, int  page, char *str);
void OLED_Refresh_Gram(void);
void OLED_DrawDot(unsigned char x,unsigned char y,unsigned char t);
void OLED_Plot(int *x, int *y);
void OLED_Axis(void);

//�ֿ���غ���
void Send_Command_to_ROM(u8 dat);
u8 Get_data_from_ROM(void);
void OLED_get_data_from_ROM(u8 addrHigh,u8 addrMid,u8 addrLow,u8 *pbuff,u8 DataLen);
void OLED_Display_GB2312_string(u8 x,u8 y,u8 *text);
void ZK_Display_16x16(u8 x,u8 y,u8 *dp);
void ZK_Display_8x16(u8 x,u8 y,u8 *dp);
void OLED_Display_string_5x7(u8 x,u8 y,u8 *text);
void ZK_Display_5x7(u8 x,u8 y,u8 *dp);
#endif

