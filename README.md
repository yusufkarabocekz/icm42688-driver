# ICM-42688 Driver for STM32 (I2C & SPI)

A lightweight and flexible C driver library for the ICM-42688 6-axis IMU sensor.  
Supports both **I2C** and **SPI** communication protocols with hardware abstraction,  
designed to work easily with STM32 microcontrollers using HAL or other platforms.

---

## Features

- ✅ Read temperature, accelerometer, and gyroscope data  
- ✅ Supports both I2C and SPI via function pointer abstraction  
- ✅ Simple API with separate functions for temperature, accel, gyro, and combined read  
- ✅ Easily extendable and portable to different MCUs  
- ✅ Professional documentation with Doxygen support
- ✅ Live debugging support with global variables

---

## File Structure

```
icm-42688-p-driver/
├── inc/                    # Header files (.h)
│   ├── icm-42688.h        # Main sensor API
│   ├── i2c_driver.h       # I2C communication interface
│   └── spi_driver.h       # SPI communication interface
├── src/                    # Source files (.c)
│   ├── icm-42688.c        # Main sensor implementation
│   ├── i2c_driver.c       # I2C driver implementation
│   └── spi_driver.c       # SPI driver implementation
├── example/                # Example application
│   └── main.c             # Complete usage example
└── README.md              # This file
```

---

## Quick Start

### 1. Include Headers
```c
#include "icm-42688.h"
#include "i2c_driver.h"    // For I2C communication
// OR
#include "spi_driver.h"    // For SPI communication
```

### 2. Initialize Sensor
```c
icm42688_t imu_sensor;

// For I2C
i2c_driver_init_i2c1(0x68 << 1);  // Initialize I2C1 with device address
imu_sensor.bus.read = i2c_read_wrapper;
imu_sensor.bus.write = i2c_write_wrapper;

// For SPI
imu_sensor.bus.read = spi_read_wrapper;
imu_sensor.bus.write = spi_write_wrapper;

// Initialize sensor
int result = icm42688_init(&imu_sensor);
if (result == 0) {
    // Initialization successful
}
```

### 3. Read Sensor Data
```c
icm42688_data_t sensor_data;

// Read all data at once
if (icm42688_read_all(&imu_sensor, &sensor_data) == 0) {
    // Access data:
    int16_t temp = sensor_data.temp;
    int16_t accel_x = sensor_data.accel_x;
    int16_t accel_y = sensor_data.accel_y;
    int16_t accel_z = sensor_data.accel_z;
    int16_t gyro_x = sensor_data.gyro_x;
    int16_t gyro_y = sensor_data.gyro_y;
    int16_t gyro_z = sensor_data.gyro_z;
}
```

---

## API Reference

### Data Structures

#### `icm42688_data_t`
```c
typedef struct {
    int16_t accel_x;    /**< Accelerometer X-axis data */
    int16_t accel_y;    /**< Accelerometer Y-axis data */
    int16_t accel_z;    /**< Accelerometer Z-axis data */
    int16_t gyro_x;     /**< Gyroscope X-axis data */
    int16_t gyro_y;     /**< Gyroscope Y-axis data */
    int16_t gyro_z;     /**< Gyroscope Z-axis data */
    int16_t temp;       /**< Temperature data */
} icm42688_data_t;
```

#### `icm42688_t`
```c
typedef struct {
    icm42688_bus_t bus; /**< Communication bus interface */
} icm42688_t;
```

### Core Functions

#### `icm42688_init(icm42688_t *dev)`
- **Purpose**: Initialize the ICM-42688 sensor
- **Parameters**: `dev` - Pointer to sensor context
- **Returns**: `0` on success, negative value on error
- **Error Codes**:
  - `-1`: Null pointer
  - `-2`: WHO_AM_I read error
  - `-3`: Wrong device ID (expected 0x47)
  - `-4`: Power management error

#### `icm42688_read_all(icm42688_t *dev, icm42688_data_t *data)`
- **Purpose**: Read all sensor data (temperature, accelerometer, gyroscope)
- **Parameters**: 
  - `dev` - Pointer to sensor context
  - `data` - Pointer to data structure
- **Returns**: `0` on success, negative value on error

#### `icm42688_read_temp(icm42688_t *dev, int16_t *temp)`
- **Purpose**: Read temperature data only
- **Parameters**: 
  - `dev` - Pointer to sensor context
  - `temp` - Pointer to temperature value
- **Returns**: `0` on success, negative value on error

#### `icm42688_read_accel(icm42688_t *dev, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z)`
- **Purpose**: Read accelerometer data only
- **Parameters**: 
  - `dev` - Pointer to sensor context
  - `accel_x, accel_y, accel_z` - Pointers to acceleration values
- **Returns**: `0` on success, negative value on error

#### `icm42688_read_gyro(icm42688_t *dev, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z)`
- **Purpose**: Read gyroscope data only
- **Parameters**: 
  - `dev` - Pointer to sensor context
  - `gyro_x, gyro_y, gyro_z` - Pointers to angular velocity values
- **Returns**: `0` on success, negative value on error

---

## Complete Example (main.c)

### I2C Example
```c
#include "main.h"
#include "icm-42688.h"
#include "i2c_driver.h"

/* Global variables for debugging */
icm42688_t imu_sensor;
icm42688_data_t sensor_data;
int debug_init_result = -1;
int debug_read_result = -1;

int main(void) {
    /* Initialize HAL and peripherals */
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();
    
    /* Initialize I2C driver */
    i2c_driver_init_i2c1(0x68 << 1);
    
    /* Configure sensor */
    imu_sensor.bus.read = i2c_read_wrapper;
    imu_sensor.bus.write = i2c_write_wrapper;
    
    /* Initialize sensor */
    debug_init_result = icm42688_init(&imu_sensor);
    
    while (1) {
        if (debug_init_result == 0) {
            debug_read_result = icm42688_read_all(&imu_sensor, &sensor_data);
            
            if (debug_read_result == 0) {
                /* Data is available in sensor_data structure */
                /* Use sensor_data.temp, sensor_data.accel_x, etc. */
            }
        }
        HAL_Delay(100);
    }
}
```

### SPI Example
```c
#include "main.h"
#include "icm-42688.h"
#include "spi_driver.h"

/* Global variables for debugging */
icm42688_t imu_sensor;
icm42688_data_t sensor_data;
int debug_init_result = -1;
int debug_read_result = -1;

int main(void) {
    /* Initialize HAL and peripherals */
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_SPI1_Init();
    
    /* Configure sensor for SPI */
    imu_sensor.bus.read = spi_read_wrapper;
    imu_sensor.bus.write = spi_write_wrapper;
    
    /* Initialize sensor */
    debug_init_result = icm42688_init(&imu_sensor);
    
    while (1) {
        if (debug_init_result == 0) {
            debug_read_result = icm42688_read_all(&imu_sensor, &sensor_data);
            
            if (debug_read_result == 0) {
                /* Data is available in sensor_data structure */
                /* Use sensor_data.temp, sensor_data.accel_x, etc. */
            }
        }
        HAL_Delay(100);
    }
}
```

---

## Hardware Connections

### I2C Connection
```
STM32          ICM-42688
I2C1_SDA  -->  SDA
I2C1_SCL  -->  SCL
3.3V      -->  VDD
GND       -->  GND
```

### SPI Connection
```
STM32          ICM-42688
SPI1_MOSI -->  SDI
SPI1_MISO <--  SDO
SPI1_SCK  -->  SCK
PA4       -->  CS (Chip Select)
3.3V      -->  VDD
GND       -->  GND
```

---

## Debugging with Live Expressions

Add these global variables to your main.c for real-time debugging:

```c
/* Debug variables for Live Expressions */
int16_t debug_accel_x = 0;
int16_t debug_accel_y = 0;
int16_t debug_accel_z = 0;
int16_t debug_gyro_x = 0;
int16_t debug_gyro_y = 0;
int16_t debug_gyro_z = 0;
int16_t debug_temp = 0;
int debug_init_result = -1;
int debug_read_result = -1;
```

Then update them in your main loop:
```c
if (debug_read_result == 0) {
    debug_accel_x = sensor_data.accel_x;
    debug_accel_y = sensor_data.accel_y;
    debug_accel_z = sensor_data.accel_z;
    debug_gyro_x = sensor_data.gyro_x;
    debug_gyro_y = sensor_data.gyro_y;
    debug_gyro_z = sensor_data.gyro_z;
    debug_temp = sensor_data.temp;
}
```

Add these variables to your IDE's Live Expressions window to monitor sensor data in real-time.

---

## Error Handling

### Common Error Codes
- `0`: Success
- `-1`: Null pointer or invalid parameters
- `-2`: Communication error (read/write failed)
- `-3`: Wrong device ID (check connections)
- `-4`: Configuration error

### Troubleshooting
1. **Wrong device ID (-3)**: Check I2C/SPI connections and device address
2. **Communication errors (-2)**: Verify bus configuration and timing
3. **Null pointer (-1)**: Ensure all pointers are properly initialized

---

## Author

**Yusuf Karaböcek**  
Electrical and Electronics Engineering  
📧 yusufkarabocekz@gmail.com

---

## License

This project is provided as-is for educational and development purposes.
