#include "ESP8266.h"
#include <string.h>


#define ESP8266_RxCounter 
uint16_t wifi_count = 1;
uint8_t wifi_RxBuffer[ESP8266_MAX];   
uint8_t wifi_Uart_Flag;


//esp8266 sends commond.
uint8_t ESP8266_SendCommand(uint8_t cmd[], uint8_t ack[], int timeout){
    // for(wifi_count=0; wifi_count < timeout; wifi_count++){
        memset(wifi_RxBuffer, 0, ESP8266_MAX);

        HAL_UART_Transmit(&ESP8266_UART, cmd, strlen(cmd), HAL_MAX_DELAY);

        while(timeout--){ 
            HAL_Delay(1);
            if(strstr(wifi_RxBuffer, ack)){
                // printf("%s ok!\n", cmd);
                // printf("%s \n", wifi_RxBuffer);
                
                return 1;
            }    
        }
        // if(timeout < 0){
        //     printf("%s failed\n", cmd);
        // }
        // HAL_Delay(1);
    return 0;
    
}
void PC_To_Esp8266_Message(void){
    memset(wifi_RxBuffer, 0, ESP8266_MAX);
    // HAL_UART_Transmit(&ESP8266_UART, )
    if(wifi_Uart_Flag==1){
        HAL_Delay(10);
        HAL_UART_Transmit(&PC_UART, wifi_RxBuffer, strlen(wifi_RxBuffer), HAL_MAX_DELAY);
        wifi_Uart_Flag = 0;
    }

}
extern uint8_t B1[B_DATA_SIZE*6], B2[B_DATA_SIZE*6], B3[B_DATA_SIZE*6];
void ESP8266_To_PC_Message(void){
    uint8_t txFlag = 0x19;
    uint8_t arr[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x11, 0x12, 0x13, 0x14};
    int Bx[B_DATA_SIZE], By[B_DATA_SIZE], Bz[B_DATA_SIZE];
    float datax, datay, dataz;
    int size = B_DATA_SIZE*6;
    char cmd[30] = "AT+CIPSEND=0,";
    sprintf(cmd, "%s%d\r\n", cmd, size);

    char str[]="I am esp8266\n";
    // char cmd[] = "AT+CIPSEND=0,1500\r\n";
    char cmd1[] = "AT+CIPSEND=0,10\r\n";
    char cmd2[] = "AT+CIPSEND=0,1\r\n";
    char ok[] = "OK";
    // while(ESP8266_SendCommand("AT+RST\r\n", "OK", 1000)!=1);
//*****************************************************************************
    // memset(wifi_RxBuffer, 0, ESP8266_MAX);
    // while(!ESP8266_SendCommand(cmd, ok, 1000));
    // HAL_UART_Transmit(&ESP8266_UART, str, strlen(str), HAL_MAX_DELAY);
    // LIS3MDL_DataRead_DMA();
    // for(int i = 0; i <6; i++){
    //     memset(wifi_RxBuffer, 0, ESP8266_MAX);
    //     while(!ESP8266_SendCommand(cmd, ok, 1000));
    //     HAL_UART_Transmit(&ESP8266_UART, B+i, 1, HAL_MAX_DELAY);
    // }
//*****************************************************************************
    LIS3MDL_DataRead_DMA();
    // for(int i = 0; i < B_DATA_SIZE; i++){
    //     Bx[i] = B1[i*6 + 0] << 8 | B1[i*6 + 1];
    //     By[i] = B1[i*6 + 2] << 8 | B1[i*6 + 3];
    //     Bz[i] = B1[i*6 + 4] << 8 | B1[i*6 + 5];

    //     Bx[i] = Bx[i] > 0x7fff ? Bx[i] - 0xffff : Bx[i];
    //     By[i] = By[i] > 0x7fff ? By[i] - 0xffff : By[i];
    //     Bz[i] = Bz[i] > 0x7fff ? Bz[i] - 0xffff : Bz[i];
    //     datax = (float)Bx[i] * 0.000146;
    //     datay = (float)By[i] * 0.000146;
    //     dataz = (float)Bz[i] * 0.000146;
    //     printf("Bx = %f, By = %f, Bz = %f\n", datax, datay, dataz);

    // }
    

    // memset(wifi_RxBuffer, 0, ESP8266_MAX);
    // while(!ESP8266_SendCommand(cmd, ok, 1000));
    // HAL_UART_Transmit(&ESP8266_UART, B1, size, HAL_MAX_DELAY);

// *****************************************************************
    // memset(wifi_RxBuffer, 0, ESP8266_MAX);
    // while(!ESP8266_SendCommand(cmd2, ok, 1000));
    // HAL_UART_Transmit(&ESP8266_UART, &txFlag, 1, HAL_MAX_DELAY);
    // HAL_Delay(50);
    // memset(wifi_RxBuffer, 0, ESP8266_MAX);
    // while(!ESP8266_SendCommand(cmd1, ok, 1000));
    // HAL_UART_Transmit(&ESP8266_UART, arr, 10, HAL_MAX_DELAY);
// *****************************************************************

    memset(wifi_RxBuffer, 0, ESP8266_MAX);
    while(!ESP8266_SendCommand(cmd, ok, 1000));
    HAL_UART_Transmit(&ESP8266_UART, B1, size, HAL_MAX_DELAY);


    HAL_Delay(200);
    memset(wifi_RxBuffer, 0, ESP8266_MAX);
    while(!ESP8266_SendCommand(cmd, ok, 1000));
    HAL_UART_Transmit(&ESP8266_UART, B2, size, HAL_MAX_DELAY);

    HAL_Delay(200);
    memset(wifi_RxBuffer, 0, ESP8266_MAX);
    while(!ESP8266_SendCommand(cmd, ok, 1000));
    HAL_UART_Transmit(&ESP8266_UART, B3, size, HAL_MAX_DELAY);


    // while(!ESP8266_SendCommand(cmd1, ok, 1000));
    // HAL_UART_Transmit(&ESP8266_UART, str, strlen(str), HAL_MAX_DELAY);
    // HAL_UART_Transmit(&ESP8266_UART, arr, sizeof(arr), HAL_MAX_DELAY);
    // HAL_UART_Transmit_DMA(&ESP8266_UART, str, strlen(str));
    // HAL_UART_Transmit(&ESP8266_UART, arr, sizeof(arr), HAL_MAX_DELAY);
    // printf("send success\n");
}


//初始化WIFI，进入透传模式

uint8_t ESP8266_Init(void)
{
    //initiatiohn of commond and ack 
    char wifiAck_ok[] = "OK";
    char wifiAck_ready[] = "ready";
    char cmd1[] = "AT\r\n";
    char cmd2[] = "AT+CWMODE=3\r\n";
    char cmd3[] = "AT+RST\r\n";
 
    char cmd4[] = "AT+CWSAP=\"ESP8266_AP\",\"12345678\",1,3\r\n";
    // char cmd4[] = "AT+CWJAP=\"ESP8266_AP\",\"12345678\",1,3\r\n";
    char cmd5[] = "AT+CIPMUX=1\r\n";
    char cmd6[] = "AT+CIPSERVER=1,333\r\n";
    // char cmd7[] = "AT+CIPMODE=1\r\n";
    // char cmd7[] = "AT+CIPSTART=\"TCP\",\"192.168.4.1\",333";
    // char cmd7[] = "AT+CIFSR\r\n"; //check local ip
    char cmd7[] = "AT+CWLIF\r\n";  //view the message of linking to pc
    char cmd8[] = "AT+CIPSEND=0,8\r\n";//send Byte
 
    uint8_t init_timeout = 1000;

    // HAL_UART_Receive_IT(&ESP8266_UART, wifi_RxBuffer, ESP8266_MAX);
    HAL_UARTEx_ReceiveToIdle_IT(&ESP8266_UART, wifi_RxBuffer, ESP8266_MAX);// IT() must be set firstly, than set init();
   
    WIFI_RST_HIGH();            // cancel reset
    WIFI_CH_EN();               // enable wifi chip
    while(ESP8266_SendCommand(cmd1, wifiAck_ok, init_timeout)!=1);//AT command must keep loop, waiting for completion of writing;
    printf("cmd1 pass\n");
    while(ESP8266_SendCommand(cmd2, wifiAck_ok, init_timeout)!=1);
    printf("cmd2 pass\n");
    // while(ESP8266_SendCommand(cmd3, wifiAck_ok, init_timeout)!=1);
    while(ESP8266_SendCommand(cmd3, wifiAck_ready, init_timeout)!=1);
    printf("cmd3 pass\n");
    while(ESP8266_SendCommand(cmd4, wifiAck_ok, init_timeout)!=1);
    printf("cmd4 pass\n");
    while(ESP8266_SendCommand(cmd5, wifiAck_ok, init_timeout)!=1);
    printf("cmd5 pass\n");
    while(ESP8266_SendCommand(cmd6, wifiAck_ok, init_timeout)!=1);
    printf("cmd6 pass\n");
    while(ESP8266_SendCommand(cmd7, wifiAck_ok, init_timeout)!=1);
    printf("cmd7 pass\n");
    // while(ESP8266_SendCommand(cmd8, wifiAck_ok, init_timeout)!=1);
    // printf("cmd8 pass\n");

    // ESP8266_SendCommand(cmd1, wifiAck_ok, init_timeout);

    // ESP8266_SendCommand(cmd2, wifiAck_ok, init_timeout);

    
    // ESP8266_SendCommand(cmd3, wifiAck_ready, init_timeout);
    // ESP8266_SendCommand(cmd4, wifiAck_ok, init_timeout);
    // ESP8266_SendCommand(cmd5, wifiAck_ok, init_timeout);
    // ESP8266_SendCommand(cmd6, wifiAck_ok, init_timeout);
    // ESP8266_SendCommand(cmd7, wifiAck_ok, init_timeout);
    // HAL_UART_Receive_IT(&ESP8266_UART, wifi_RxBuffer, ESP8266_MAX);

	return 0;
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    if(huart->Instance == USART2){
        printf("rx = %s\n", wifi_RxBuffer);
        HAL_UART_Receive_IT(&ESP8266_UART, wifi_RxBuffer, ESP8266_MAX);
    }
}


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
    if(huart->Instance==USART2)
	{
        // printf("receive over\n");
        // char str[] = "receive over\n";
        // HAL_UART_Transmit(&huart3, str, strlen(str), 1000);
        wifi_Uart_Flag = 1;
        printf("%s\n", wifi_RxBuffer);
        HAL_UARTEx_ReceiveToIdle_IT(&ESP8266_UART, wifi_RxBuffer, ESP8266_MAX);
        // HAL_UARTEx_ReceiveToIdle_IT(&huart1, wifi_RxBuffer, ESP8266_MAX);
	}
}

int fputc(int ch, FILE* f){
    HAL_UART_Transmit(&HUART, (uint8_t *)&ch, 1, 1000);
    return ch;
}

