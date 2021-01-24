/*
    I2C_Com.h
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

#ifndef _I2C_COM_H
#define _I2C_COM_H

/****************************************************************************/
/***        Including Files                                               ***/
/****************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <cstdint>


/****************************************************************************/
/***        Class Definition                                              ***/
/****************************************************************************/
class I2C_Com {
    public:
        I2C_Com(const unsigned int dev = 1, const uint8_t DevID = 0x04);
        ~I2C_Com();

        uint8_t isAvailable();

    protected:
        void        I2C_WriteCmd(const uint8_t Cmd);
        uint8_t     I2C_ReadReg(const uint8_t Reg);
        void        I2C_WriteReg(const uint8_t Reg, const uint8_t Data);
        uint8_t     I2C_ReadData(const uint8_t reg);
        uint16_t    I2C_ReadData2byte(const uint8_t regL, const uint8_t regH);
        uint16_t    I2C_ReadData2byte(const uint8_t reg);



    private:
        int I2C_Device;
        uint8_t I2C_DEV_ADR;
        static constexpr uint8_t I2C_REG_STATUS        = 0x00;
        static constexpr uint8_t I2C_STATUS_RDY_MASK   = 0x01;

#ifdef CROSS_COMPILE
        int open(const char* dev, int mode) {return 0;};
        int ioctl(int dev, int mode, int adr){return 0;};
        int close(int dev){return 0;};
        int i2c_smbus_write_byte( int dev, uint8_t byte) { return 0;};
        int i2c_smbus_read_byte_data( int dev, uint8_t reg) { return 1234;};
        int i2c_smbus_write_byte_data( int dev, uint8_t Reg, uint8_t Data) {return 0;};
        int i2c_smbus_read_word_data( int dev, uint8_t Reg){return 0;};

        static constexpr uint8_t I2C_SLAVE = 0x00;
#endif // CROSS_COMPILE
};

#endif  // _I2C_COM_H
