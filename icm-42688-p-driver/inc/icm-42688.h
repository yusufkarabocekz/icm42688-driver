/*
* icm-42688.h
* 
* Created by: July, 2025
*       Author: Yusuf Karaböcek
*/

#ifndef ICM_42688_H
#define ICM_42688_H

#include <stdint.h>
#include <stdbool.h>

// ICM-42688 I2C Adresi (default: 0x68 veya 0x69)
#define ICM_42688_I2C_ADDRESS 0x68 

// Kimlik registerı (WHO_AM_I)
#define WHO_AM_I_REG 0x75

// Temel konfigürasyon ve güç yönetimi registerları
#define ICM42688_REG_DEVICE_CONFIG 0x11
#define ICM42688_PWR_MGMT0 0x4E

// Sıcaklık veri registerları
#define ICM42688_REG_TEMP_DATA1 0x1D
#define ICM42688_REG_TEMP_DATA2 0x1E

// İvmeölçer veri registerları
#define ICM42688_REG_ACCEL_DATA_X1 0x1F
#define ICM42688_REG_ACCEL_DATA_X0 0x20
#define ICM42688_REG_ACCEL_DATA_Y1 0x21
#define ICM42688_REG_ACCEL_DATA_Y0 0x22
#define ICM42688_REG_ACCEL_DATA_Z1 0x23
#define ICM42688_REG_ACCEL_DATA_Z0 0x24

// Jiroskop veri registerları
#define ICM42688_REG_GYRO_DATA_X1 0x25
#define ICM42688_REG_GYRO_DATA_X0 0x26
#define ICM42688_REG_GYRO_DATA_Y1 0x27
#define ICM42688_REG_GYRO_DATA_Y0 0x28
#define ICM42688_REG_GYRO_DATA_Z1 0x29
#define ICM42688_REG_GYRO_DATA_Z0 0x2A

// Konfigürasyon registerları
#define ICM42688_REG_ACCEL_CONFIG0 0x50
#define ICM42688_REG_GYRO_CONFIG0 0x4F

// Sensör verilerini tutan yapı
typedef struct {
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;
    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;
    int16_t temp;
} icm42688_data_t;

// Haberlesme soyutlaması: I2C veya SPI driverları buraya atanir
typedef struct {
    int (*read)(uint8_t reg, uint8_t *data, uint16_t len);
    int (*write)(uint8_t reg, uint8_t *data, uint16_t len);
} icm42688_bus_t;

// Sensör context yapısı -bus struct ı icerir
typedef struct {
    icm42688_bus_t bus;
}icm42688_t;

// ICM-42688 başlatma fonksiyonu
int icm42688_init(icm42688_t *dev);

// Tüm sensör verilerini okuyan fonksiyon
int icm42688_read_all(icm42688_t *dev, icm42688_data_t *data);

// Sıcaklık verisini okuyan fonksiyon
int icm42688_read_temp(icm42688_t *dev, int16_t *temp);

// Accel verisi okuyan fonksiyon
int icm42688_read_accel(icm42688_t *dev, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z);

// Gyro verisi okuyan fonksiyon
int icm42688_read_gyro(icm42688_t *dev, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z);

#endif // ICM_42688_H