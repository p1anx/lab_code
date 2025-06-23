#ifndef __API_H
#define __API_H

#include "spi.h"
#include "usart.h"

#define ADS1263_SPI hspi1
void ADS_SPI_tx(uint8_t *tx_data, uint16_t size);
void ADS_SPI_rx(uint8_t *rx_data, uint16_t size);

#endif // !__API_H#define __API_H
