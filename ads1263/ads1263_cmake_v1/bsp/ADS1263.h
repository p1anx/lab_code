#ifndef  __ADS1263_H
#define  __ADS1263_H

#include "spi.h"
#include "gpio.h"
#include "usart.h"
#include "api.h"
#include "uart_printf.h"

#define ADS1263_SPI hspi1
#define ADS1263_UART huart1
/*********GPIO************/
#define ADS1263_GPIO_Port_CS    GPIOA
#define ADS1263_Pin_CS          GPIO_PIN_4

#define ADS1263_GPIO_Port_DRDY  GPIOA
#define ADS1263_Pin_DRDY        GPIO_PIN_2

#define ADS1263_GPIO_Port_RST   GPIOA
#define ADS1263_Pin_RST         GPIO_PIN_0

#define ADS1263_GPIO_Port_START GPIOA
#define ADS1263_Pin_START       GPIO_PIN_3

#define ADS1263_CS_LOW()        HAL_GPIO_WritePin(ADS1263_GPIO_Port_CS, ADS1263_Pin_CS, GPIO_PIN_RESET)
#define ADS1263_CS_HIGH()       HAL_GPIO_WritePin(ADS1263_GPIO_Port_CS, ADS1263_Pin_CS, GPIO_PIN_SET)

#define ADS1263_RESET_LOW()     HAL_GPIO_WritePin(ADS1263_GPIO_Port_RST, ADS1263_Pin_RST, GPIO_PIN_RESET)
#define ADS1263_RESET_HIGH()    HAL_GPIO_WritePin(ADS1263_GPIO_Port_RST, ADS1263_Pin_RST, GPIO_PIN_SET)

#define ADS1263_START()     HAL_GPIO_WritePin(ADS1263_GPIO_Port_START, ADS1263_Pin_START, GPIO_PIN_SET)
#define ADS1263_STOP()      HAL_GPIO_WritePin(ADS1263_GPIO_Port_START, ADS1263_Pin_START, GPIO_PIN_RESET)

#define ADS1263_DRDY()      HAL_GPIO_ReadPin(ADS1263_GPIO_Port_DRDY, ADS1263_Pin_DRDY)




/************************指令************************/
#define ADS1263_CMD_NOP         0x00
#define ADS1263_CMD_RESET       0x06
#define ADS1263_CMD_RDATA_ADC1  0x12
#define ADS1263_CMD_RDATA_ADC2  0x14
#define ADS1263_CMD_START_ADC1  0x08
#define ADS1263_CMD_START_ADC2  0x0C
#define ADS1263_CMD_STOP_ADC1   0x0A
#define ADS1263_CMD_STOP_ADC2   0x0E
#define ADS1263_CMD_SYOCAL_ADC1 0x16
#define ADS1263_CMD_SYGCAL_ADC1 0x17
#define ADS1263_CMD_SFOCAL_ADC1 0x19
#define ADS1263_CMD_SYOCAL_ADC2 0x1B
#define ADS1263_CMD_SYGCAL_ADC2 0x1C
#define ADS1263_CMD_SFOCAL_ADC2 0x1E


/*******寄存器地址列表************/
#define ADS1263_POWER           0x01
#define ADS1263_MUX_ADC1       0x06
#define ADS1263_MUX_ADC2       0x16
#define ADS1263_INTERFACE 0x02
#define ADS1263_Mode_0     0x03
#define ADS1263_Mode_1     0x04
#define ADS1263_Mode_2  0x05
#define ADS1263_INPMUX      0x06
#define ADS1263_OFCAL0  0x07
#define ADS1263_OFCAL1  0x08
#define ADS1263_OFCAL2  0x09

#define ADS1263_REFMUX  0x0F
#define ADS1263_GPIO_Connection 0x12
#define ADS1263_GPIO_Direction  0x13
#define ADS1263_GPIO_Data       0x14
#define ADS1263_TDACP_CONTROL 0x10
#define ADS1263_TDACN_CONTROL 0x11
#define ADS1263_ADC2_CONFIGURATION 0x15
#define ADS1263_IDACMUX    0x0D
#define ADS1263_IDACMAG    0x0E

/*******Mode0 Register************/
/*******Conversion Mode************/
#define ADS1263_CONTINUOUS_CONVERSION 0b0 << 6
#define ADS1263_SINGLE_SHOT_CONVERSION 0b1 << 6

/*******Digital Filter************/
#define ADS1263_SINC1_MODE 0b000 << 5
#define ADS1263_SINC2_MODE 0b001 << 5
#define ADS1263_SINC3_MODE 0b010 << 5
#define ADS1263_SINC4_MODE 0b011 << 5
#define ADS1263_FIR_MODE   0b100 << 5

/************************MOde2 Register******************************/

/*******PGA Gain************/
#define ADS1263_GAIN_1  0b000 << 4
#define ADS1263_GAIN_2  0b001 << 4
#define ADS1263_GAIN_4  0b010 << 4
#define ADS1263_GAIN_8  0b011 << 4
#define ADS1263_GAIN_16 0b100 << 4
#define ADS1263_GAIN_32 0b101 << 4


/*******Date Rate************/
#define ADS1263_DR_2_5  0b0000
#define ADS1263_DR_5    0b0001
#define ADS1263_DR_10   0b0010
#define ADS1263_DR_16_6 0b0011
#define ADS1263_DR_20   0b0100
#define ADS1263_DR_50   0b0101
#define ADS1263_DR_60   0b0110
#define ADS1263_DR_100  0b0111
#define ADS1263_DR_400  0b1000
#define ADS1263_DR_1200 0b1001
#define ADS1263_DR_2400 0b1010
#define ADS1263_DR_4800 0b1011
#define ADS1263_DR_7200 0b1100
#define ADS1263_DR_14400 0b1101
#define ADS1263_DR_19200 0b1110
#define ADS1263_DR_38400 0b1111

/*******INPMUX Register************/
#define ADS1263_MUXP_AIN0   0x00
#define ADS1263_MUXP_AIN1   0x10
#define ADS1263_MUXP_AIN2   0x20
#define ADS1263_MUXP_AIN3   0x30
#define ADS1263_MUXP_AIN4   0x40
#define ADS1263_MUXP_AIN5   0x50
#define ADS1263_MUXP_AIN6   0x60
#define ADS1263_MUXP_AIN7   0x70
#define ADS1263_MUXP_AIN8   0x80
#define ADS1263_MUXP_AIN9   0x90
#define ADS1263_MUXP_AINCOM 0xA0
#define ADS1263_TEMPERATURE_SENSOR_MONITOR_P 0xB0
#define ADS1263_ANALOG_POWER_SUPPLY_MONITOR_P 0xC0
#define ADS1263_DIGITAL_POWER_SUPPLY_MONITOR_P 0xD0
#define ADS1263_TDAC_TEST_SIGNAL_P     0xE0
#define ADS1263_FLOAT_P 0xF0
 
#define ADS1263_MUXN_AIN0   0x00
#define ADS1263_MUXN_AIN1   0x01
#define ADS1263_MUXN_AIN2   0x02
#define ADS1263_MUXN_AIN3   0x03
#define ADS1263_MUXN_AIN4   0x04
#define ADS1263_MUXN_AIN5   0x05
#define ADS1263_MUXN_AIN6   0x06
#define ADS1263_MUXN_AIN7   0x07
#define ADS1263_MUXN_AIN8   0x08
#define ADS1263_MUXN_AIN9   0x09
#define ADS1263_MUXN_AINCOM 0x0A
#define ADS1263_TEMPERATURE_SENSOR_MONITOR_N 0x0B
#define ADS1263_ANALOG_POWER_SUPPLY_MONITOR_N 0x0C
#define ADS1263_DIGITAL_POWER_SUPPLY_MONITOR_N 0x0D
#define ADS1263_TDAC_TEST_SIGNAL_N     0x0E
#define ADS1263_FLOAT_N 0x0F

typedef struct
{
    /* data */
    uint8_t port;
    uint8_t dataRate;
    uint8_t gain;
    uint8_t Power_Reg;
    uint8_t Interface_Reg;
    uint8_t Mode0_Reg;
    uint8_t Mode1_Reg;
    uint8_t Mode2_Reg;
    uint8_t INPMUX_Reg;
    uint8_t OFCAL0_Reg;
    uint8_t OFCAL1_Reg;
    uint8_t OFCAL2_Reg;
    uint8_t IDACMUX_Reg;
    uint8_t IDACMAG_Reg;
    uint8_t REFMUX_Reg;


    
}ADS1263_ConfigStruct;



void ADS1263_wreg(uint8_t reg_address, uint8_t n_data);
void ADS1263_rreg(uint8_t reg_address, uint8_t n_data);
void ADS1263_ReadID(void);
void ADS1263_GetReg(uint8_t reg_address);
void ADS1263_WriteReg(uint8_t reg_address, uint8_t reg_data);
void ADS1263_WriteRegN(uint8_t reg_address, uint8_t *reg_data, uint8_t n_data);
void ADS1263_ReadReg(uint8_t reg_address, uint8_t reg_data);
void ADS1263_ReadRegN(uint8_t reg_address, uint8_t *reg_data, uint8_t n_data);
// void ADS1263_Init(void);
void ADS1263_Init(uint8_t dataRate, uint8_t gain, uint8_t port);
void ADS1263_Config(void);
void ADS1263_ConfigFunc(ADS1263_ConfigStruct *ads);
// void ADS1263_Init0(void);
void ADS1263_Init0(uint8_t dataRate, uint8_t gain, uint8_t port);
void ADS1263_Init1(void);
void ADS1263_ReadData(void);
void ADS1263_ReadData0(void);
void ADS1263_Print(void);
void ADS1263_RegCheck(uint8_t reg_address, uint8_t reg_set);
void ADS1263_DataTrasmit(void);
void ADS1263_ToPython(void);
void ADS1263_RegSFOCAL(void);
uint32_t ADS1263_DataRx(void);
void ADS1263_DataTx(void);

#endif // ! __ADS1263_H
