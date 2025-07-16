/*
* i2c_driver.h
* 
* Created by: July, 2025
*       Author: Yusuf Karaböcek
*/

#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include <stdint.h>

int i2c_read_wrapper(uint8_t reg, uint8_t *data, uint16_t len);
int i2c_write_wrapper(uint8_t reg, uint8_t *data, uint16_t len);

#endif // I2C_DRIVER_H