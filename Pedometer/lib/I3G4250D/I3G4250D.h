#ifndef I3G4250D_H
#define I3G4250D_H

#include "mbed.h"

class I3G4250D {

public:
    // Constants for device identification and SPI flag
    static const int DEVICE_ID = 0xD3;
    static const int SPI_FLAG = 1;

    // Register addresses for the gyroscope sensor
    typedef enum {
        WHO_AM_I = 0x0f,
        CTRL_REG1 = 0x20,
        CTRL_REG2 = 0x21,
        CTRL_REG3 = 0x22,
        CTRL_REG4 = 0x23,
        CTRL_REG5 = 0x24,
        OUT_X_L = 0x28,
        OUT_X_H = 0x29,
        OUT_Y_L = 0x2A,
        OUT_Y_H = 0x2B,
        OUT_Z_L = 0x2C,
        OUT_Z_H = 0x2D
    } I3G4250D_Reg;

    // Enums for data rate, full scale, and cut-off frequency settings
    typedef enum {
        DR100HZ = 0b00,
        DR200HZ = 0b01,
        DR400HZ = 0b10,
        DR800HZ = 0b11
    } I3G4250D_DataRate;

    typedef enum {
        FS245DPS = 0b00,
        FS500DPS = 0b01,
        FS2000DPS = 0b10,
    } I3G4250D_FS;

    typedef enum {
        CO_12_5HZ = 1,
        CO_20HZ = 2,
        CO_25HZ = 3,
        CO_30HZ = 4,
        CO_35HZ = 5,
        CO_50HZ = 6,
        CO_70HZ = 7,
        CO_110HZ = 8
    } I3G4250D_CutOff;

    // Constructor
    I3G4250D(PinName mosi, PinName miso, PinName sclk, PinName cs);

    // Methods for configuring the gyroscope sensor
    bool setConfig1(I3G4250D_DataRate dataRate = DR200HZ, I3G4250D_CutOff cutOff = CO_50HZ);
    void setConfig4(I3G4250D_FS fullScale = FS245DPS);
    void initialize();
    void readGyroscopeData(float& gx, float& gy, float& gz);
    int readRegister(I3G4250D_Reg reg);
    void writeRegister(I3G4250D_Reg reg, u_int8_t data);

private:
    // Bit masks and constants
    const u_int8_t DR_MASK = 0b00111111;
    const u_int8_t CO_MASK = 0b11001111;
    const u_int8_t FS_MASK = 0b11001111;
    const u_int8_t MS_MASK = 0x40;
    const u_int8_t READ_MASK = 0x80;
    float raw2rps = 17.5f * 0.017453292519943295769236907684886f / 1000.0f; //for 500dps
    I3G4250D_DataRate dataRate;

    // SPI communication and event flags
    SPI spi;
    EventFlags flags;
    uint8_t writeBuf[32];
    uint8_t readBuf[32];

    // Private methods
    void spiCallback(int event);
    //Dedault configuration for the gyroscope
    //configuration: 200Hz ODR,50Hz cutoff, Power on, Z on, Y on, X on
    u_int8_t CTRL_REG1_CONFIG = 0b01'10'1'1'1'1;
    //register fields(bits): reserved(1), endian-ness(1),Full scale sel(2), reserved(1),self-test(2), SPI mode(1)
    u_int8_t CTRL_REG4_CONFIG = 0b0'0'01'0'00'0;
};

#endif
