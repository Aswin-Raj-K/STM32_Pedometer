#ifndef GYROMETER_DATA_H_
#define GYROMETER_DATA_H_

#include <mbed.h>

// Register Addresses
#define WHO_AM_I 0x0F   // WHOAMI Register

#define CTRL_REG_1 0x20 // Control Register 1
#define CTRL_REG_2 0x21 // Control Register 2
#define CTRL_REG_3 0x22 // Control Register 3
#define CTRL_REG_4 0x23 // Control Register 4
#define CTRL_REG_5 0x24 // Control Register 5

// Angular Register Addresses
#define OUT_X_L 0x28    // X-axis angular rate data Low
#define OUT_X_H 0x29    // X-axis angular rate data high
#define OUT_Y_L 0x2A    // Y-axis angular rate data low
#define OUT_Y_H 0x2B    // Y-axis angular rate data high
#define OUT_Z_L 0x2C    // Z-axis angular rate data low
#define OUT_Z_H 0x2D    // Z-axis angular rate data high

#define STATUS_REG 0x27 // Status Register

// Fullscale selections
#define FULL_SCALE_245 0x00      // full scale 245 dps
#define FULL_SCALE_500 0x10      // full scale 500 dps
#define FULL_SCALE_2000 0x20     // full scale 2000 dps

// Sensitivities in dps/digit
#define SENSITIVITY_245 0.00875f // 245 dps typical sensitivity
#define SENSITIVITY_500 0.0175f  // 500 dps typical sensitivity
#define SENSITIVITY_2000 0.07f   // 2000 dps typical sensitivity

// Data rate and bandwidth
#define ODR_800_CUTOFF_110 0xf0
#define ODR_800_HIGH_PASS_56 0x00

// Convert constants
#define Distance_from_the_axis_of_rotation 1    // actual distance from the axis of rotation to the gyroscope sensor
#define DEGREE_TO_RAD 0.01745329252f            // pi / 180

#define POWERON 0x0f  // turn on gyroscope

// Raw data
typedef struct {
    int16_t x_raw; // X-axis raw data
    int16_t y_raw; // Y-axis raw data
    int16_t z_raw; // Z-axis raw data
} Gyroscope_RawData;


// Write IO
void WriteByte(uint8_t address, uint8_t data);

// Read IO
void GetGyroValue(Gyroscope_RawData *rawdata);

// Gyroscope initialization
void InitiateGyroscope(Gyroscope_RawData *init_raw_data, uint8_t odr, uint8_t hpf, uint8_t fs, float* sensitivity);

// Calculate distance from raw data array;
float GetDistance(int16_t arr[]);

#endif // GYROMETER_DATA_H_
