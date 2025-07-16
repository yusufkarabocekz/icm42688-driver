# ICM-42688 Driver for STM32 (I2C & SPI)

A lightweight and flexible C driver library for the ICM-42688 6-axis IMU sensor.  
Supports both **I2C** and **SPI** communication protocols with hardware abstraction,  
designed to work easily with STM32 microcontrollers using HAL or other platforms.

---

## Features

- Read temperature, accelerometer, and gyroscope data  
- Supports both I2C and SPI via function pointer abstraction  
- Simple API with separate functions for temperature, accel, gyro, and combined read  
- Easily extendable and portable to different MCUs  
- Example usage planned (coming soon)

---

## File Structure

```c

icm42688-driver/
├── inc/ # Header files (.h)
│ ├── icm42688.h
│ ├── i2c_driver.h
│ └── spi_driver.h
├── src/ # Source files (.c)
│ ├── icm42688.c
│ ├── i2c_driver.c
│ └── spi_driver.c
├── example/ # Example application (planned)
│ └── main.c # (coming soon)
├── README.md # This file

```

---

## Usage

1. Initialize the driver struct and assign bus read/write functions.  
2. Call `icm42688_init()` to initialize the sensor.  
3. Use read functions to get sensor data.

```c
#include "icm42688.h"
#include "i2c_driver.h"

icm42688_t imu;

void app_init(void) {
    imu.bus.read = i2c_read_wrapper;
    imu.bus.write = i2c_write_wrapper;

    if (icm42688_init(&imu) == 0) {
        // Initialization success
    }
}

void app_loop(void) {
    int16_t temp;
    if (icm42688_read_temp(&imu, &temp) == 0) {
        // Use temperature value
    }
}

```

---

## Author

Yusuf Karaböcek
Electrical and Electronics Engineering
yusufkarabocekz@gmail.com
