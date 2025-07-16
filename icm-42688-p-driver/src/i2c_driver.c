/*
* i2c_driver.c
* 
* Created by: July, 2025
*       Author: Yusuf Karaböcek
*/

#include "i2c_driver.h"
#include "stm32f1xx_hal.h"

extern I2C_HandleTypeDef hi2c1; // farkli i2c portlari kullanimina göre degistirme

#define ICM_42688_I2C_ADDRESS (0x68 << 1) // ICM-42688 I2C adresi

int i2c_read_wrapper(uint8_t reg, uint8_t *data, uint16_t len) {
    return HAL_I2C_Mem_Read(&hi2c1, ICM_42688_I2C_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, data, len, 1000);
}

int i2c_write_wrapper(uint8_t reg, uint8_t *data, uint16_t len) {
    return HAL_I2C_Mem_Write(&hi2c1, ICM_42688_I2C_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, data, len, 1000);
}
