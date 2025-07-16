/*
* spi_driver.h
* 
* Created by: July, 2025
*       Author: Yusuf Karaböcek
*/

#ifndef SPI_DRIVER_H
#define SPI_DRIVER_H

#include <stdint.h>

int spi_read_wrapper(uint8_t reg, uint8_t *data, uint16_t len);
int spi_write_wrapper(uint8_t reg, uint8_t *data, uint16_t len);

void spi_cs_enable(void);
void spi_cs_disable(void);

#endif // SPI_DRIVER_H