/*
* spi_driver.c
* 
* Created by: July, 2025
*       Author: Yusuf Karaböcek
*/

#include "spi_driver.h"
#include "stm32f1xx_hal.h"

extern SPI_HandleTypeDef hspi1;

#define READ_FLAG 0x80 // SPI icin okuma biti

void spi_cs_enable(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // pin secimi de main.c de yapilabilir
}

void spi_cs_disable(void) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

int spi_read_wrapper(uint8_t reg, uint8_t *data, uint16_t len) {
    uint8_t tx_data = reg | READ_FLAG;
    spi_cs_enable();

    if(HAL_SPI_Transmit(&hspi1, &tx_data, 1, 1000) != HAL_OK) {
        spi_cs_disable();
        return -1;
    }   

    if(HAL_SPI_Receive(&hspi1, data, len, 1000) != HAL_OK) {
        spi_cs_disable();
        return -2;
    }

    spi_cs_disable();
    return 0;
}

int spi_write_wrapper(uint8_t reg, uint8_t *data, uint16_t len) {
    uint8_t tx_data = reg & 0x7F;
    spi_cs_enable();

    if(HAL_SPI_Transmit(&hspi1, &tx_data, 1, 1000) != HAL_OK) {
        spi_cs_disable();
        return -1;
    }

    if(HAL_SPI_Transmit(&hspi1, data, len, 1000) != HAL_OK) {
        spi_cs_disable();
        return -2;
    }

    spi_cs_disable();
    return 0;
}
