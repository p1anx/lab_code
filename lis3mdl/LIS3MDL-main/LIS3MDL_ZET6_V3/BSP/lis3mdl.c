/*
 * bsp_spi.c
 *
 *  Created on: Oct 29, 2023
 *      Author: XWJ
 */


#include "lis3mdl.h"
#include "spi.h"
#include "usart.h"



//Write the data to a register
void LIS3MDL_WriteReg(uint8_t reg, uint8_t value){
	SPI_CS_LOW;
	uint8_t data[2];
	data[0] = reg | LIS3MDL_WRITE;
	data[1] = value;
	HAL_SPI_Transmit(&HSPI, data, 2, HAL_MAX_DELAY);
	SPI_CS_HIGH;
}

//Read the data of a register
uint8_t LIS3MDL_ReadReg(uint8_t reg){
	SPI_CS_LOW;
	uint8_t data[2] = {0x00, 0x00};
	uint8_t value;
	data[0] = reg | LIS3MDL_READ;
	HAL_SPI_TransmitReceive(&HSPI, data, data, 2, HAL_MAX_DELAY);
	value = data[1];
	SPI_CS_HIGH;
	return value;

}

uint8_t FullScale = FS_4GAUSS;
// uint8_t FullScale;
void LIS3MDL_Init(void){
	uint8_t data_reg1, data_reg2, data_reg3, data_reg4, data_reg5;
	data_reg1 = CTRL_REG1_OM_LP | CTRL_REG1_DO_80HZ | FAST_ODR_ENABLE | ST;
	data_reg2 =  FullScale | REBOOT_NORMAL | SOFT_RST_0; //Full scale selection
	data_reg3 =  LP | SIM | MD_CONTINUOUS;  //Read mode selection, single or continuous
	data_reg4 =  OMZ_LP | BLE;
	data_reg5 =  FAST_READ_DISABLE | BDU;

	// data_reg1 = 0x10|0x07;
	// data_reg2 = 0x00;
	// data_reg3 = 0x00;
	// data_reg4 = 0x00;
	// data_reg5 = 0x00;

	LIS3MDL_WriteReg(ADDR_CTRL_REG1, data_reg1);
	LIS3MDL_WriteReg(ADDR_CTRL_REG2, data_reg2);
	LIS3MDL_WriteReg(ADDR_CTRL_REG3, data_reg3);
	LIS3MDL_WriteReg(ADDR_CTRL_REG4, data_reg4);
	LIS3MDL_WriteReg(ADDR_CTRL_REG5, data_reg5);
	
}
//select 
int Sensitivity(void){
	int sensitivity;
	switch(FullScale){
		case FS_16GAUSS: sensitivity = 1711;break;
		case FS_12GAUSS: sensitivity = 2281;break;
		case FS_8GAUSS:  sensitivity = 3421;break;
		case FS_4GAUSS:  sensitivity = 6842;break;
		default: printf("sensitivity error!\n");
	}
	return sensitivity;
}



void LIS3MDL_DataRead(void){
	int datax, datay,dataz; // for showing negative number, the received data must be int type
	LIS3MDL_DATA data;
	int s = Sensitivity();
	printf("s=%d\n",s);
	float Bx, By, Bz;
	datax = LIS3MDL_ReadReg(ADDR_OUT_X_H) << 8 | LIS3MDL_ReadReg(ADDR_OUT_X_L);
	datay = LIS3MDL_ReadReg(ADDR_OUT_Y_H) << 8 | LIS3MDL_ReadReg(ADDR_OUT_Y_L);
	dataz = LIS3MDL_ReadReg(ADDR_OUT_Z_H) << 8 | LIS3MDL_ReadReg(ADDR_OUT_Z_L);

	printf("x:%d\n", datax);
	printf("y:%d\n", datay);
	printf("z:%d\n", dataz);
	if(datax > 0x7fff){
		datax = ~(uint16_t)datax + 1;
		datax &= 0xffff;
		datax = -datax;
	}
	if(datay > 0x7fff){
		datay = ~(uint16_t)datay + 1;
		datay &= 0xffff;
		datay = -datay;
	}
	if(dataz > 32767){
		dataz = ~(uint16_t)dataz + 1; //complement code conversion
		dataz &= 0xffff;
		dataz = -dataz;
	}
	Bx =(float)datax / s;
	By =(float)datay / s;
	Bz =(float)dataz / s;
	printf("Bx=%f gauss\n", Bx);
	printf("By=%f gauss\n", By);
	printf("Bz=%f gauss\n", Bz);

}

void LIS3MDL_DataRead_Transmisson(void){
	LIS3MDL_DATA data;
	uint8_t Bx_L[DATA_SIZE], Bx_H[DATA_SIZE], By_L[DATA_SIZE], By_H[DATA_SIZE], Bz_L[DATA_SIZE], Bz_H[DATA_SIZE];
	// uint16_t s = Sensitivity();
	uint8_t Bx_start = 0x10;
	uint8_t Bx_end   = 0x11;
	uint8_t By_start = 0x20;
	uint8_t By_end   = 0x21;
	uint8_t Bz_start = 0x30;
	uint8_t Bz_end   = 0x31;
	// printf("s=%d\n",s);

	for(int i = 0; i < DATA_SIZE; i++){
		Bx_L[i] = LIS3MDL_ReadReg(ADDR_OUT_X_L);
		Bx_H[i] = LIS3MDL_ReadReg(ADDR_OUT_X_H);
		By_L[i] = LIS3MDL_ReadReg(ADDR_OUT_Y_L);
		By_H[i] = LIS3MDL_ReadReg(ADDR_OUT_Y_H);
		Bz_L[i] = LIS3MDL_ReadReg(ADDR_OUT_Z_L);
		Bz_H[i] = LIS3MDL_ReadReg(ADDR_OUT_Z_H);
		HAL_UART_Transmit(&HUART, &Bx_start, 1, HAL_MAX_DELAY);
		HAL_UART_Transmit(&HUART, (uint8_t *)Bx_H, DATA_SIZE, HAL_MAX_DELAY);
		HAL_UART_Transmit(&HUART, (uint8_t *)Bx_L, DATA_SIZE, HAL_MAX_DELAY);
		HAL_UART_Transmit(&HUART, &Bx_end, 1, HAL_MAX_DELAY);
		// HAL_Delay(10);

		// HAL_UART_Transmit(&HUART, &By_start, 1, HAL_MAX_DELAY);
		// HAL_UART_Transmit(&HUART, (uint8_t *)By_H, DATA_SIZE, HAL_MAX_DELAY);
		// HAL_UART_Transmit(&HUART, (uint8_t *)By_L, DATA_SIZE, HAL_MAX_DELAY);
		// HAL_UART_Transmit(&HUART, &By_end, 1, HAL_MAX_DELAY);
		
		// HAL_UART_Transmit(&HUART, &Bz_start, 1, HAL_MAX_DELAY);
		// HAL_UART_Transmit(&HUART, (uint8_t *)Bz_H, DATA_SIZE, HAL_MAX_DELAY);
		// HAL_UART_Transmit(&HUART, (uint8_t *)Bz_L, DATA_SIZE, HAL_MAX_DELAY);
		// HAL_UART_Transmit(&HUART, &Bz_end, 1, HAL_MAX_DELAY);	
	}
	// HAL_UART_Transmit(&HUART, &start, 1, HAL_MAX_DELAY);
	// HAL_UART_Transmit(&HUART, Bx_H, 1, HAL_MAX_DELAY);
	// HAL_UART_Transmit(&HUART, Bx_L, DATA_SIZE, HAL_MAX_DELAY);


	
}
void LIS3MDL_TransmitToPython(void){
	LIS3MDL_DATA data;
	uint8_t Bx_L[DATA_SIZE], Bx_H[DATA_SIZE], By_L[DATA_SIZE], By_H[DATA_SIZE], Bz_L[DATA_SIZE], Bz_H[DATA_SIZE];
	uint16_t s = Sensitivity();
	uint8_t  s_arr[2] = {(s & 0xff00) >> 8, s & 0xff};
	uint8_t s_start  = 0x00;
	uint8_t s_end    = 0x01;
	uint8_t Bx_start = 0x10;
	uint8_t Bx_end   = 0x11;
	uint8_t By_start = 0x20;
	uint8_t By_end   = 0x21;
	uint8_t Bz_start = 0x30;
	uint8_t Bz_end   = 0x31;

	for(int i = 0; i < DATA_SIZE; i++){
		Bx_L[i] = LIS3MDL_ReadReg(ADDR_OUT_X_L);
		Bx_H[i] = LIS3MDL_ReadReg(ADDR_OUT_X_H);
		By_L[i] = LIS3MDL_ReadReg(ADDR_OUT_Y_L);
		By_H[i] = LIS3MDL_ReadReg(ADDR_OUT_Y_H);
		Bz_L[i] = LIS3MDL_ReadReg(ADDR_OUT_Z_L);
		Bz_H[i] = LIS3MDL_ReadReg(ADDR_OUT_Z_H);
		HAL_UART_Transmit(&HUART, (uint8_t *)&s_start,1    , HAL_MAX_DELAY);
		HAL_UART_Transmit(&HUART, (uint8_t *)s_arr, 2       , HAL_MAX_DELAY);

		HAL_UART_Transmit(&HUART, (uint8_t *)Bx_H, DATA_SIZE, HAL_MAX_DELAY);
		HAL_UART_Transmit(&HUART, (uint8_t *)Bx_L, DATA_SIZE, HAL_MAX_DELAY);

		HAL_UART_Transmit(&HUART, (uint8_t *)By_H, DATA_SIZE, HAL_MAX_DELAY);
		HAL_UART_Transmit(&HUART, (uint8_t *)By_L, DATA_SIZE, HAL_MAX_DELAY);
		
		HAL_UART_Transmit(&HUART, (uint8_t *)Bz_H, DATA_SIZE, HAL_MAX_DELAY);
		HAL_UART_Transmit(&HUART, (uint8_t *)Bz_L, DATA_SIZE, HAL_MAX_DELAY);
	}
}


LIS3MDL_DATA LIS3MDL_DataRead_Continue(void){
	int datax, datay,dataz; // for showing negative number, the received data must be int type
	LIS3MDL_DATA data;
	char *Buffer[3];
	char *str;
	int s = Sensitivity();
	printf("s=%d\n",s);
	float Bx, By, Bz;
	datax = LIS3MDL_ReadReg(ADDR_OUT_X_H) << 8 | LIS3MDL_ReadReg(ADDR_OUT_X_L);
	datay = LIS3MDL_ReadReg(ADDR_OUT_Y_H) << 8 | LIS3MDL_ReadReg(ADDR_OUT_Y_L);
	dataz = LIS3MDL_ReadReg(ADDR_OUT_Z_H) << 8 | LIS3MDL_ReadReg(ADDR_OUT_Z_L);

	printf("x:%d\n", datax);
	printf("y:%d\n", datay);
	printf("z:%d\n", dataz);
	if(datax > 0x7fff){
		datax = ~(uint16_t)datax + 1;
		datax &= 0xffff;
		datax = -datax;
	}
	if(datay > 0x7fff){
		datay = ~(uint16_t)datay + 1;
		datay &= 0xffff;
		datay = -datay;
	}
	if(dataz > 32767){
		dataz = ~(uint16_t)dataz + 1; //complement code conversion
		dataz &= 0xffff;
		dataz = -dataz;
	}
	
	Bx =(float)datax / s;
	By =(float)datay / s;
	Bz =(float)dataz / s;
	// sprintf(str, "str = %f", Bx);
	// printf("Bx:%s\n", str);
	// sprintf(Buffer[0], "%f", Bx);
	// sprintf(Buffer[1], "%f", By);
	// sprintf(Buffer[2], "%f", Bz);
	// printf("Bx:%s\n", Buffer[0]);
	// printf("By:%s\n", Buffer[1]);
	// printf("Bz:%s\n", Buffer[2]);

	// sprintf(data.x, "%f", Bx);
	// sprintf(data.y, "%f", By);
	// sprintf(data.z, "%f", Bz);
	// printf("Bx:%s\n", data.x);
	// printf("By:%s\n", data.y);
	// printf("Bz:%s\n", data.z);
	return data;
	
}

void LIS3MDL_DataRead_Continue_Transmission(void){
	// char *BxBuffer[DATA_SIZE], *ByBuffer[DATA_SIZE], *BzBuffer[DATA_SIZE];

	// for(int i = 0; i < DATA_SIZE; i++){
	// 	LIS3MDL_DATA data = LIS3MDL_DataRead_Continue();
	// 	BxBuffer[i] = data.x;
	// 	ByBuffer[i] = data.y;
	// 	BzBuffer[i] = data.z;
	// 	printf("Bx:%s\n", BxBuffer[i]);
	// 	printf("By:%s\n", ByBuffer[i]);
	// 	printf("Bz:%s\n", BzBuffer[i]);
	// }
}












