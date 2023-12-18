#include "gyrometer_data.h"
#include <mbed.h>

SPI spi(PF_9, PF_8, PF_7); // mosi, miso, sclk
DigitalOut cs(PC_1);

Gyroscope_RawData *gyro_raw;

// Write I/O
void WriteByte(uint8_t address, uint8_t data) {
  cs = 0;
  spi.write(address);
  spi.write(data);
  cs = 1;
}

// Get raw data from spi
void GetGyroValue(Gyroscope_RawData *rawdata) {
  cs = 0;
  spi.write(OUT_X_L | 0x80 | 0x40); // auto-incremented read
  rawdata->x_raw = spi.write(0xff) | spi.write(0xff) << 8;
  rawdata->y_raw = spi.write(0xff) | spi.write(0xff) << 8;
  rawdata->z_raw = spi.write(0xff) | spi.write(0xff) << 8;
  cs = 1;
}

// Initiate spi, set up control registers
void InitiateGyroscope(Gyroscope_RawData *init_raw_data, uint8_t odr, uint8_t hpf, uint8_t fs, float* sensitivity) {
  gyro_raw = init_raw_data;
  cs = 1;
  // set up spi
  spi.format(8, 3);       // 8 bits per SPI frame; polarity 1, phase 0
  spi.frequency(1000000); // clock frequency deafult 1 MHz max:10MHz

  WriteByte(CTRL_REG_1, odr | POWERON); // set ODR Bandwidth and enable all 3 axises
  WriteByte(CTRL_REG_2, hpf);           // no high pass filter
  WriteByte(CTRL_REG_4, fs);            // LSB, full sacle selection: 500dps

  switch (fs) {
  case FULL_SCALE_245:
    *sensitivity = SENSITIVITY_245;
    break;

  case FULL_SCALE_500:
    *sensitivity = SENSITIVITY_500;
    break;

  case FULL_SCALE_2000:
    *sensitivity = SENSITIVITY_2000;
    break;

  }
}