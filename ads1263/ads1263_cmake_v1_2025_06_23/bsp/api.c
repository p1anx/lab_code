#include "api.h"

void ADS_SPI_tx(uint8_t *tx_data, uint16_t size)
{
    HAL_SPI_Transmit(&ADS1263_SPI, tx_data, size, 1000);
}

void ADS_SPI_rx(uint8_t *rx_data, uint16_t size)
{
    HAL_SPI_Receive(&ADS1263_SPI, rx_data, size, 1000);
}