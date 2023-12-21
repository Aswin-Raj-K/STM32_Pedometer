#include "I3G4250D.h"


I3G4250D::I3G4250D(PinName mosi, PinName miso, PinName sclk, PinName cs) : spi(mosi, miso, sclk, cs, use_gpio_ssel) {
}



void I3G4250D::initialize() {
    // Setup the SPI for 8-bit data, high steady state clock,
    // second edge capture, with a 1MHz clock rate
    spi.format(8, 3);
    spi.frequency(1'000'000);

    writeRegister(CTRL_REG1, CTRL_REG1_CONFIG);
    writeRegister(CTRL_REG4, CTRL_REG4_CONFIG);

}



void I3G4250D::writeRegister(I3G4250D_Reg regAddr, uint8_t data){
    writeBuf[0] = regAddr;
    writeBuf[1] = data;
    spi.transfer(writeBuf, 2, readBuf, 2, callback(this, &I3G4250D::spiCallback), SPI_EVENT_COMPLETE);
    flags.wait_all(SPI_FLAG);
}

int I3G4250D::readRegister(I3G4250D_Reg regAddr){
    writeBuf[0] = 0x80 | regAddr;

    spi.transfer(writeBuf, 2, readBuf, 2, callback(this, &I3G4250D::spiCallback), SPI_EVENT_COMPLETE);
    flags.wait_all(SPI_FLAG);
    return readBuf[1];
}

void I3G4250D::readGyroscopeData(float& gx, float& gy, float& gz){
    int16_t raw_gx,raw_gy,raw_gz;

    //prepare the write buffer to trigger a sequential read
    writeBuf[0]=OUT_X_L|READ_MASK|MS_MASK;

    //start sequential sample reading
    spi.transfer(writeBuf,7,readBuf,7,callback(this, &I3G4250D::spiCallback),SPI_EVENT_COMPLETE );
    flags.wait_all(SPI_FLAG);

    //read_buf after transfer: garbage byte, gx_low,gx_high,gy_low,gy_high,gz_low,gz_high
    //Put the high and low bytes in the correct order lowB,HighB -> HighB,LowB
    raw_gx=( ( (uint16_t)readBuf[2] ) <<8 ) | ( (uint16_t)readBuf[1] );
    raw_gy=( ( (uint16_t)readBuf[4] ) <<8 ) | ( (uint16_t)readBuf[3] );
    raw_gz=( ( (uint16_t)readBuf[6] ) <<8 ) | ( (uint16_t)readBuf[5] );

    gx=((float)raw_gx)*raw2dps;
    gy=((float)raw_gy)*raw2dps;
    gz=((float)raw_gz)*raw2dps;
}

void I3G4250D::spiCallback(int event)
{
    flags.set(SPI_FLAG);
}


bool I3G4250D::setConfig1(I3G4250D_DataRate dataRate, I3G4250D_CutOff cutOff){
    this->dataRate = dataRate;
    CTRL_REG1_CONFIG = static_cast<uint8_t>(dataRate) << 6 | (CTRL_REG1_CONFIG & DR_MASK);


    uint8_t cf = 0x00;

    if(dataRate == DR100HZ){
        if(cutOff == CO_12_5HZ)
            cf = 0x00;
        else if(cutOff == CO_25HZ)
            cf = 0b00010000;
        else
            return false;
    }else if(dataRate == DR200HZ){
        if(cutOff == CO_12_5HZ)
            cf = 0x00;
        else if(cutOff == CO_25HZ)
            cf = 0b00010000;
        else if(cutOff == CO_50HZ)
            cf = 0b00100000;
        else if(cutOff == CO_70HZ)
            cf = 0b00110000;
        else
            return false;
    }else if(dataRate == DR400HZ){
        if(cutOff == CO_20HZ)
            cf = 0x00;
        else if(cutOff == CO_25HZ)
            cf = 0b00010000;
        else if(cutOff == CO_50HZ)
            cf = 0b00100000;
        else if(cutOff == CO_110HZ)
            cf = 0b00110000;
        else
            return false;
    }else{
        if(cutOff == CO_30HZ)
            cf = 0x00;
        else if(cutOff == CO_35HZ)
            cf = 0b00010000;
        else if(cutOff == CO_50HZ)
            cf = 0b00100000;
        else if(cutOff == CO_110HZ)
            cf = 0b00110000;
        else
            return false;
    }


    CTRL_REG1_CONFIG = cf | (CTRL_REG1_CONFIG & CO_MASK);
    return true;
}



void I3G4250D::setConfig4(I3G4250D_FS fullScale){
    CTRL_REG4_CONFIG = 0b01000000; //Setting little endian
    CTRL_REG4_CONFIG = fullScale | (CTRL_REG4_CONFIG & FS_MASK);
}

