/*
    I2C_Com.cpp
    Driver for DIGITAL I2C Communication

    Copyright (c) 2021 Maximilian Ziegler
    Website    : https://github.com/zieglermax/Grove_RPi_Lib
    Author     : Max Ziegler
    Create Time: January 2021
    Change Log :

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

#include <unistd.h>
#include <stdlib.h>
#include "I2C_Com.h"

#ifndef CROSS_COMPILE
extern "C" {
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
}
#include <sys/ioctl.h>
#endif // CROSS_COMPILE


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <cstdint>
#include <iostream>



/****************************************************************************/
/***       Class member Functions                                         ***/
/****************************************************************************/

I2C_Com::I2C_Com(const unsigned int dev, const uint8_t DevId) {

    /* Init IIC Interface */
	std::cout << "Initalizing I²C Interface" << std::endl;

	I2C_DEV_ADR = DevId;
    std::string dev_name = "/dev/i2c-" + std::to_string(dev);
    //dev_name += std::to_string(dev);
    if ( (I2C_Device = open( dev_name.c_str(), O_RDWR)) < 0)
    {
        perror("open() failed");
    }
    printf(" OK\n");

    /* Specify Address of slave i2c_device */
    if (ioctl( I2C_Device, I2C_SLAVE, I2C_DEV_ADR) < 0)
    {
        printf("Failed to acquire bus access and/or talk to slave\n");
    }

}

I2C_Com::~I2C_Com() {
    /* Init IIC Interface */
	std::cout << "Deinitalizing I²C Interface" << std::endl;

    if (0 < close(I2C_Device) )
    {
        perror("close() failed");
    }
    std::cout << "I²C i2c_device Deinitialized succesfully." << std::endl;

}

/****************************************************************************/
/***       Local Functions                                                ***/
/****************************************************************************/
uint8_t I2C_Com::isAvailable() {
    uint8_t status =  I2C_ReadReg(I2C_REG_STATUS);
    if (status & I2C_STATUS_RDY_MASK) {
        return 0;    //ready
    } else {
        return 1;    //not ready yet
    }
}

void I2C_Com::I2C_WriteCmd(const uint8_t Cmd) {
    i2c_smbus_write_byte(I2C_Device, Cmd);
}

uint8_t I2C_Com::I2C_ReadReg(const uint8_t Reg) {
    uint8_t TempReg = 0;
    TempReg = (uint8_t) i2c_smbus_read_byte_data(I2C_Device, Reg);
    return TempReg;
}

void I2C_Com::I2C_WriteReg(const uint8_t Reg, const uint8_t Data) {
   i2c_smbus_write_byte_data( I2C_Device, Reg, Data);
}

uint8_t I2C_Com::I2C_ReadData(const uint8_t reg) {
    uint8_t Temp = i2c_smbus_read_byte_data( I2C_Device, reg );
    return Temp;
}

uint16_t I2C_Com::I2C_ReadData2byte(const uint8_t regL, const uint8_t regH ) {
    uint16_t TempData = 0;
    uint8_t datah=0, datal=0;

    datah = i2c_smbus_read_byte_data( I2C_Device, regH );
    datal = i2c_smbus_read_byte_data( I2C_Device, regL );
    TempData = (datah << 8) | datal;

    //std::cout << "RawTemp Value: " << TempData << std::endl;
    return TempData;
}

uint16_t I2C_Com::I2C_ReadData2byte(const uint8_t reg) {
    uint16_t TempData = 0;

    TempData = i2c_smbus_read_word_data( I2C_Device, reg );

    //std::cout << "RawTemp Value: " << TempData << std::endl;
    return TempData;
}
