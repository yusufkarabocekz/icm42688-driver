/**
 * @file i2c_driver.c
 * @brief I2C communication driver implementation for ICM-42688
 * @author Yusuf Karaböcek
 * @date July 2025
 */

#include "i2c_driver.h"
#include "stm32f1xx_hal.h"

extern I2C_HandleTypeDef hi2c1; /**< I2C1 handle - change for different ports */
extern I2C_HandleTypeDef hi2c2; /**< I2C2 handle (if available) */

/* Global I2C driver instance */
static i2c_driver_t g_i2c_driver = {0};

/* ICM-42688 I2C address */
#define ICM_42688_I2C_ADDRESS (0x68 << 1)

/* STM32 HAL callback functions */
static int stm32_i2c1_read_callback(uint8_t device_addr, uint8_t reg, uint8_t *data, uint16_t len) {
    return HAL_I2C_Mem_Read(&hi2c1, device_addr, reg, I2C_MEMADD_SIZE_8BIT, data, len, 1000);
}

static int stm32_i2c1_write_callback(uint8_t device_addr, uint8_t reg, uint8_t *data, uint16_t len) {
    return HAL_I2C_Mem_Write(&hi2c1, device_addr, reg, I2C_MEMADD_SIZE_8BIT, data, len, 1000);
}

static int stm32_i2c2_read_callback(uint8_t device_addr, uint8_t reg, uint8_t *data, uint16_t len) {
    return HAL_I2C_Mem_Read(&hi2c2, device_addr, reg, I2C_MEMADD_SIZE_8BIT, data, len, 1000);
}

static int stm32_i2c2_write_callback(uint8_t device_addr, uint8_t reg, uint8_t *data, uint16_t len) {
    return HAL_I2C_Mem_Write(&hi2c2, device_addr, reg, I2C_MEMADD_SIZE_8BIT, data, len, 1000);
}

int i2c_driver_init(i2c_driver_t *driver, uint8_t device_addr,
                   i2c_read_callback_t read_cb, i2c_write_callback_t write_cb) {
    if (!driver || !read_cb || !write_cb) {
        return -1; /* Error: invalid parameters */
    }

    driver->device_address = device_addr;
    driver->read_callback = read_cb;
    driver->write_callback = write_cb;

    /* Update global driver */
    g_i2c_driver = *driver;

    return 0; /* Success */
}

int i2c_driver_init_i2c1(uint8_t device_addr) {
    return i2c_driver_init(&g_i2c_driver, device_addr,
                          stm32_i2c1_read_callback, stm32_i2c1_write_callback);
}

int i2c_driver_init_i2c2(uint8_t device_addr) {
    return i2c_driver_init(&g_i2c_driver, device_addr,
                          stm32_i2c2_read_callback, stm32_i2c2_write_callback);
}

int i2c_read_wrapper(uint8_t reg, uint8_t *data, uint16_t len) {
    if (g_i2c_driver.read_callback) {
        return g_i2c_driver.read_callback(g_i2c_driver.device_address, reg, data, len);
    }
    /* Default to I2C1 */
    return (HAL_I2C_Mem_Read(&hi2c1, 0x68 << 1, reg, I2C_MEMADD_SIZE_8BIT, data, len, 1000) == HAL_OK) ? 0 : -1;
}

int i2c_write_wrapper(uint8_t reg, uint8_t *data, uint16_t len) {
    if (g_i2c_driver.write_callback) {
        return g_i2c_driver.write_callback(g_i2c_driver.device_address, reg, data, len);
    }
    /* Default to I2C1 */
    return stm32_i2c1_write_callback(ICM_42688_I2C_ADDRESS, reg, data, len);
}
