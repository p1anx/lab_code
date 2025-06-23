#include "ADS1263.h"
#include <stdio.h>

void ADS1263_Config(void){

}

void ADS1263_wreg(uint8_t reg_address, uint8_t n_data)
{
    uint8_t data[2];
    data[0] = reg_address | 0x40;
    data[1] = n_data-1;
    ADS_SPI_tx(data, 2);
}

void ADS1263_rreg(uint8_t reg_address, uint8_t n_data)
{
    uint8_t data[2];
    data[0] = reg_address | 0x20;
    data[1] = n_data-1;
    ADS_SPI_tx(data, 2);
}

void ADS1263_ReadID(void){ //ID = 0010 0011 (ascii: #, 0x23)

    uint8_t recvData;
    ADS1263_RESET_LOW();
    HAL_Delay(1);
    ADS1263_RESET_HIGH();
    HAL_Delay(1);
    ADS1263_CS_LOW();
    HAL_Delay(1);
    ADS1263_rreg(0x02, 1);
    ADS_SPI_rx(&recvData, 1);
    ADS1263_CS_HIGH();

    // HAL_UART_Transmit(&huart1, &recvData, 1, 1000);
    printf("ID:0x%x\n", recvData);

}
void ADS1263_GetReg(uint8_t reg_address){
    uint8_t recvData;
    // ADS1263_RESET_LOW();
    // HAL_Delay(1);
    // ADS1263_RESET_HIGH();
    // HAL_Delay(1);
    ADS1263_CS_LOW();
    HAL_Delay(1);
    ADS1263_rreg(reg_address, 1);
    ADS_SPI_rx(&recvData, 1);
    ADS1263_CS_HIGH();

    // HAL_UART_Transmit(&huart1, &recvData, 1, 1000);
    printf("reg:0x%x\n", recvData);

}

void ADS1263_WriteReg(uint8_t reg_address, uint8_t reg_data){
    uint8_t cmd_nop = ADS1263_CMD_NOP;
    ADS1263_CS_LOW();
    ADS1263_wreg(reg_address, 1);
    ADS_SPI_tx(&reg_data, 1);
    // ADS_SPI_tx(&cmd_nop, 0);
    ADS1263_CS_HIGH();
}

void ADS1263_WriteRegN(uint8_t reg_address, uint8_t *reg_data, uint8_t n_data){
    ADS1263_CS_LOW();
    ADS1263_wreg(reg_address, n_data-1);
    ADS_SPI_tx(reg_data, n_data-1);
    ADS1263_CS_HIGH();
}

void ADS1263_ReadReg(uint8_t reg_address, uint8_t reg_data){
    ADS1263_CS_LOW();
    ADS1263_rreg(reg_address, 1);
    ADS_SPI_rx(&reg_data, 1);
    ADS1263_CS_HIGH();
}

void ADS1263_ReadRegN(uint8_t reg_address, uint8_t *reg_data, uint8_t n_data){
    ADS1263_CS_LOW();
    ADS1263_rreg(reg_address, n_data);
    ADS_SPI_rx(reg_data, n_data);
    ADS1263_CS_HIGH();
}

void ADS1263_ConfigFunc(ADS1263_ConfigStruct *ads){
    ADS1263_WriteReg(ADS1263_POWER, ads->Power_Reg);
    ADS1263_WriteReg(ADS1263_INTERFACE, ads->Interface_Reg);
    ADS1263_WriteReg(ADS1263_Mode_0, ads->Mode0_Reg);
    ADS1263_WriteReg(ADS1263_Mode_1, ads->Mode1_Reg);
    ADS1263_WriteReg(ADS1263_Mode_2, ads->Mode2_Reg);
    ADS1263_WriteReg(ADS1263_INPMUX, ads->INPMUX_Reg);
    ADS1263_WriteReg(ADS1263_OFCAL0, ads->OFCAL0_Reg);
    ADS1263_WriteReg(ADS1263_OFCAL1, ads->OFCAL1_Reg);
    ADS1263_WriteReg(ADS1263_OFCAL2, ads->OFCAL2_Reg);

    ADS1263_WriteReg(ADS1263_IDACMUX, ads->IDACMUX_Reg);
    ADS1263_WriteReg(ADS1263_IDACMAG, ads->IDACMUX_Reg);
    ADS1263_WriteReg(ADS1263_REFMUX, ads->REFMUX_Reg);
}

void ADS1263_Init(uint8_t dataRate, uint8_t gain, uint8_t port){

    int delayms = 1000;
    uint8_t cmd_stop1 = ADS1263_CMD_STOP_ADC1;
    uint8_t cmd_stop2 = ADS1263_CMD_STOP_ADC2;   

    ADS1263_ConfigStruct ads;
    ads.Power_Reg = 0x11;
    ads.Interface_Reg = 0x04;
    ads.Mode0_Reg = ADS1263_CONTINUOUS_CONVERSION;
    ads.Mode1_Reg = ADS1263_SINC1_MODE;
    ads.Mode2_Reg = gain | dataRate;
    ads.INPMUX_Reg = port;
    ads.OFCAL0_Reg = 0x00;
    ads.OFCAL1_Reg = 0x00;
    ads.OFCAL2_Reg = 0x00;

    ads.IDACMUX_Reg = 0xbb;
    ads.IDACMAG_Reg = 0x00;
    ads.REFMUX_Reg = 0x00;

    ADS1263_STOP();
    // HAL_SPI_Transmit(&hspi1, cmd_stop1, 1, 1000);
    HAL_SPI_Transmit(&hspi1, &cmd_stop2, 1, 1000);
    ADS1263_RESET_LOW();
    HAL_Delay(1);
    ADS1263_RESET_HIGH();
    ADS1263_ConfigFunc(&ads);

    HAL_Delay(delayms);
    ADS1263_START();
}

void ADS1263_Init0(uint8_t dataRate, uint8_t gain, uint8_t port){
    
    int delayms = 1000;
    uint8_t ready_status;
    uint8_t cmd_stop1 = ADS1263_CMD_STOP_ADC1;
    uint8_t cmd_stop2 = ADS1263_CMD_STOP_ADC2;   
    uint8_t power_setting = 0x11;
    uint8_t Interface = 0x04;
    uint8_t Mode0_Setting = ADS1263_CONTINUOUS_CONVERSION ;
    //ADC1
    // uint8_t Mode0_Setting = ADS1263_SINGLE_SHOT_CONVERSION ;
    uint8_t Mode1_Setting = ADS1263_SINC1_MODE;
    uint8_t Mode2_Setting = gain | dataRate;
    // uint8_t INPMUX_Setting = ADS1263_MUXP_AIN0 | ADS1263_MUXN_AIN1;
    uint8_t INPMUX_Setting = port;
    uint8_t IDACMUX_setting = 0xbb;
    uint8_t IDACMAG_setting = 0x00;
    uint8_t REFMUX_setting = 0x00;

    //ADC2
    uint8_t ADC2CFG_setting = 0x00; 
    uint8_t ADC2MUX_setting = 0x01;
    
    uint8_t sfocal_cmd = ADS1263_CMD_SFOCAL_ADC1;
    uint8_t cmd_group1[13], cmd1_group1[3];
    uint8_t cmd_group2[2];

    cmd_group1[0] = Mode0_Setting;
    cmd_group1[1] = Mode1_Setting;
    cmd_group1[2] = Mode2_Setting;
    cmd_group1[3] = INPMUX_Setting;
    cmd_group1[4] = 0x00;
    cmd_group1[5] = 0x00;
    cmd_group1[6] = 0x00;
    cmd_group1[7] = 0x00;
    cmd_group1[8] = 0x00;
    cmd_group1[9] = 0x40;

    cmd_group1[10] = IDACMUX_setting; 
    cmd_group1[11] = IDACMAG_setting;
    cmd_group1[12] = REFMUX_setting;

    ADS1263_STOP();
    // HAL_SPI_Transmit(&hspi1, cmd_stop1, 1, 1000);
    HAL_SPI_Transmit(&hspi1, &cmd_stop2, 1, 1000);

    ADS1263_RESET_LOW();
    HAL_Delay(1);
    ADS1263_RESET_HIGH();
    // HAL_Delay(1000);
    // ADS1263_WriteReg(0x01, 0x01);
    ADS1263_WriteReg(ADS1263_INTERFACE ,Interface);
    // ADS1263_WriteRegN(0x03, cmd_group1, sizeof(cmd_group1)/cmd_group1[0]);

    //adc1
    ADS1263_WriteRegN(0x03, cmd_group1, 13);

    //adc2

    HAL_Delay(delayms);
    ADS1263_START();


}


void ADS1263_RegCheck(uint8_t reg_address, uint8_t reg_set){
    uint8_t reg_read;
    ADS1263_CS_LOW();
    HAL_Delay(1);
    ADS1263_rreg(reg_address, 1);
    ADS_SPI_rx(&reg_read, 1);
    ADS1263_CS_HIGH();

    if(reg_set == reg_read){
        printf("setting good for addr:0x%x \n", reg_address);
    }
    else{
        printf("setting bad for addr:0x%x \n", reg_address);
    }


}

void ADS1263_RegSFOCAL(void){
    uint8_t cmd_sfocal = ADS1263_CMD_SFOCAL_ADC1;
    ADS1263_Config();
    ADS1263_WriteReg(ADS1263_INPMUX, 0xff);

    // HAL_Delay(1000);
    ADS1263_START();
    ADS_SPI_tx(&cmd_sfocal, 1);
    // ADS1263_Init();
    while(1){
        HAL_Delay(1000);
        printf("interface:");
        ADS1263_GetReg(0x02);
        ADS1263_GetReg(0x03);
        ADS1263_GetReg(0x04);
        
        printf("inpmux:");
        ADS1263_GetReg(0x06);

        printf("sfocal:\n");
        printf("of1");
        ADS1263_GetReg(0x07);
        printf("of2");
        ADS1263_GetReg(0x08);
        printf("of3");
        ADS1263_GetReg(0x09);

    }
}

void ADS1263_ReadData(void){
    uint8_t Data[5];
    uint32_t rxBuffer;
    double voltage;
    while(1 == ADS1263_DRDY());
    ADS1263_CS_LOW();
    uint8_t read_cmd = ADS1263_CMD_RDATA_ADC1;//发送ADC1读取转换数据命令
    HAL_SPI_Transmit(&hspi1, &read_cmd, 1, 1000);
    HAL_SPI_Receive(&hspi1, Data, 4, 1000);

    rxBuffer = Data[0] <<24 | Data[1] << 16 | Data[2] << 8 | Data[3];
    voltage = (double)rxBuffer * 2.5/ 2147483648;
    

    printf("data[0]:0x%x\n", Data[0]);
    printf("data[1]:0x%x\n", Data[1]);
    printf("data[2]:0x%x\n", Data[2]);
    printf("data[3]:0x%x\n", Data[3]);
    ADS1263_CS_HIGH();
}

void ADS1263_Print(void){
    uint8_t rxData;
    float v;

    ADS1263_Init(ADS1263_DR_400, ADS1263_GAIN_1, ADS1263_MUXP_AIN0 | ADS1263_MUXN_AINCOM);
    while(1){
        // ADS1263_ReadData();
        rxData = ADS1263_DataRx();
        printf("rxData:%d\n", rxData);

        HAL_Delay(1000);
    }
}


void ADS1263_DataTrasmit(void){
    uint8_t txflag = 0x11;
    uint8_t Data[5];
    uint8_t read_cmd = ADS1263_CMD_RDATA_ADC1;//发送ADC1读取转换数据命令

    while(1 == ADS1263_DRDY());
    ADS1263_CS_LOW();
    HAL_SPI_Transmit(&hspi1, &read_cmd, 1, 1000);
    HAL_SPI_Receive(&hspi1, Data,sizeof(Data)/sizeof(Data[0]), 1000);

    ADS1263_CS_HIGH();
    if(0x40 == (Data[0] & 0x40) ){
        HAL_UART_Transmit(&huart1, &txflag, 1, 1000);
        HAL_UART_Transmit(&huart1, Data+1, 4, 1000);

    }
}
uint32_t ADS1263_DataRx(void){
    uint32_t recvData;
    uint8_t txflag = 0x11;
    uint8_t Data[5];
    uint8_t read_cmd = ADS1263_CMD_RDATA_ADC1;//发送ADC1读取转换数据命令

    while(1 == ADS1263_DRDY());
    ADS1263_CS_LOW();
    HAL_SPI_Transmit(&hspi1, &read_cmd, 1, 1000);
    HAL_SPI_Receive(&hspi1, Data,sizeof(Data)/sizeof(Data[0]), 1000);

    if(0x40 == (Data[0] & 0x40) ){
        recvData = Data[1] << 24 | Data[2] << 16 | Data[3] << 8 | Data[4];
    }
    ADS1263_CS_HIGH();
    return recvData;
}

void ADS1263_DataTx(void){
    uint32_t rxData = ADS1263_DataRx();
    uint8_t data[4];
    uint8_t txFlag = 0x11;
    data[0] = (rxData & 0xff000000) >> 24; 
    data[1] = (rxData & 0x00ff0000) >> 16; 
    data[2] = (rxData & 0x0000ff00) >> 8; 
    data[3] = (rxData & 0x000000ff) >> 0; 
    HAL_UART_Transmit(&ADS1263_UART, &txFlag, 1, 1000);
    HAL_UART_Transmit(&ADS1263_UART, &data, 4, 1000);

}
void ADS1263_ToPython(void){
    ADS1263_Init(ADS1263_DR_1200, ADS1263_GAIN_1, ADS1263_MUXP_AIN0 | ADS1263_MUXN_AINCOM);
    // ADS1263_Config();
    while(1){
        // HAL_Delay(10);
        // ADS1263_DataTrasmit();
        ADS1263_DataTx();
    }
}
