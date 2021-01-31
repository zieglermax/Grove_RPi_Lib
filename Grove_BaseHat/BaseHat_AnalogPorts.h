/*
    BaseHat_AnalogPorts.h
    Driver for reading analog voltage values of Grove BaseHat ports

    Copyright (c) 2021 Max Ziegler
    Website    : https://github.com/zieglermax/Grove_RPi_Lib
    Author     : Max Ziegler
    Create Time: Januar 2021
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

#ifndef _GROVE_BASEHAT_DEV_H
#define _GROVE_BASEHAT_DEV_H

/****************************************************************************/
/***        Including Files                                               ***/
/****************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <cstdint>
#include "I2C_Com.h"


/****************************************************************************/
/***        Class Definition                                              ***/
/****************************************************************************/
class BaseHat : protected I2C_Com {

    public:
        BaseHat(unsigned int dev = 1) : I2C_Com(dev, BASEHAT_I2C_DEV_ADR){};
        ~BaseHat(){};

        enum AnalogPort {
            A0 = 0,
            A1 = 1,
            A2 = 2,
            A3 = 3,
            A4 = 4,
            A5 = 5,
            A6 = 6,
            A7 = 7,
        };

        uint8_t version(void);
        double PowerSupplyVoltage(void);
        uint16_t ReadRaw(AnalogPort analogPort);
        double ReadVoltage(AnalogPort analogPort);

    private:

        static const uint8_t BASEHAT_I2C_DEV_ADR    = 0x04;
        static const uint8_t Reg_DeviceId           = 0x0;
        static const uint8_t Reg_Version            = 0x02;
        static const uint8_t Reg_PowerSupplyVoltage = 0x29;
        static const uint8_t Reg_RawBase            = 0x10;
        static const uint8_t Reg_VoltageBase        = 0x20;
        static const uint8_t Reg_ValueBase          = 0x30;

};

#endif  // _GROVE_BASEHAT_DEV_H
