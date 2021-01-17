/*
    TH02_dev.cpp
    Driver for DIGITAL I2C HUMIDITY AND TEMPERATURE SENSOR

    Copyright (c) 2014 seeed technology inc.
    Website    : www.seeed.cc
    Author     : Orig. Oliver Wang - Modified by Max Ziegler
    Create Time: April 2014
    Change Log : January 2021 - converted to RPi usage

    The MIT License (MIT)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include "TH02_dev.h"
#include <unistd.h>
#include <stdlib.h>
extern "C" {
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
}
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <cstdint>
#include <iostream>

/* Use Serial IIC */
#ifdef SERIAL_IIC
#endif

/****************************************************************************/
/***       Local Variable                                                 ***/
/****************************************************************************/


/****************************************************************************/
/***       Class member Functions                                         ***/
/****************************************************************************/

TH02_dev::TH02_dev() {
    /* Init IIC Interface */
	std::cout << "Initalizing I²C Interface" << std::endl;
    /* open i2c_device */
    //if ((TH02_dev::i2c_device = open(strcat("/dev/i2c-", (char) (48+iic_i2c_device)), O_RDWR)) < 0)
    if ((TH02_dev::i2c_device = open("/dev/i2c-1", O_RDWR)) < 0)
    {
        perror("open() failed");
    }
    printf(" OK\n");

    /* Specify Address of slave i2c_device */
    if (ioctl(TH02_dev::i2c_device, I2C_SLAVE, TH02_I2C_DEV_ID) < 0)
    {
        printf("Failed to acquire bus access and/or talk to slave\n");
    }

    /* TH02 don't need to software reset */
}

TH02_dev::~TH02_dev() {
    /* Init IIC Interface */
	std::cout << "Deinitalizing I²C Interface" << std::endl;
    /* open i2c_device */
    if (0 < close(TH02_dev::i2c_device) )
    {
        perror("close() failed");
    }
    std::cout << "I²C i2c_device Deinitialized succesfully." << std::endl;

}

float TH02_dev::ReadTemperature(void) {
    /* Start a new temperature conversion */
    TH02_dev::TH02_IIC_WriteReg(REG_CONFIG, CMD_MEASURE_TEMP);
    //delay(100);
    /* Wait until conversion is done */
    while (!TH02_dev::isAvailable());
    uint16_t value = TH02_dev::TH02_IIC_ReadData();

    value = value >> 2;
    /*
        Formula:
        Temperature(C) = (Value/32) - 50
    */
    //std::cout << "RawTempValue: " << value << std::endl;
    float temper = (value / 32.0) - 50.0;

    return temper;
}

float TH02_dev::ReadHumidity(void) {
    /* Start a new humility conversion */
    TH02_dev::TH02_IIC_WriteReg(REG_CONFIG, CMD_MEASURE_HUMI);

    /* Wait until conversion is done */
    //delay(100);
    while (!TH02_dev::isAvailable());
    uint16_t value = TH02_dev::TH02_IIC_ReadData();

    value = value >> 4;

    /*
        Formula:
        Humidity(%) = (Value/16) - 24
    */
    //std::cout << "RawHumidityVal: " << value << std::endl;
    float humility = (value / 16.0) - 24.0;

    return humility;
}

/****************************************************************************/
/***       Local Functions                                                ***/
/****************************************************************************/
uint8_t TH02_dev::isAvailable() {
    uint8_t status =  TH02_dev::TH02_IIC_ReadReg(REG_STATUS);
    if (status & STATUS_RDY_MASK) {
        return 0;    //ready
    } else {
        return 1;    //not ready yet
    }
}

void TH02_dev::TH02_IIC_WriteCmd(uint8_t u8Cmd) {
    i2c_smbus_write_byte(TH02_dev::i2c_device, u8Cmd);
}

uint8_t TH02_dev::TH02_IIC_ReadReg(uint8_t u8Reg) {
    uint8_t TempReg = 0;
    TempReg = (uint8_t) i2c_smbus_read_byte_data(TH02_dev::i2c_device, u8Reg);
    return TempReg;
}

void TH02_dev::TH02_IIC_WriteReg(uint8_t u8Reg, uint8_t u8Data) {
   i2c_smbus_write_byte_data( TH02_dev::i2c_device, u8Reg, u8Data);
   //i2c_smbus_write_byte( TH02_dev::i2c_device, u8Reg);
   //i2c_smbus_write_byte( TH02_dev::i2c_device, u8Data
}

uint16_t TH02_dev::TH02_IIC_ReadData(void) {
    uint16_t Temp = TH02_IIC_ReadData2byte();
    return Temp;
}

uint16_t TH02_dev::TH02_IIC_ReadData2byte() {
    uint16_t TempData = 0;
    uint8_t datah=0, datal=0;

    datah = i2c_smbus_read_byte_data( TH02_dev::i2c_device, REG_DATA_H );
    datal = i2c_smbus_read_byte_data( TH02_dev::i2c_device, REG_DATA_L );
    TempData = (datah << 8) | datal;

    //std::cout << "RawTemp Value: " << TempData << std::endl;
    return TempData;
}
