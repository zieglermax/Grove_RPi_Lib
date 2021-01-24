/*
    TH02_dev.h
    Driver for DIGITAL I2C HUMIDITY AND TEMPERATURE SENSOR

    Copyright (c) 2014 seeed technology inc.
    Website    : www.seeed.cc
    Author     : Original Oliver Wang, Modified to RPi Lib by Max Ziegler
    Create Time: April 2014
    Change Log : January 2021

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

#ifndef _TH02_DEV_H
#define _TH02_DEV_H

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
class TH02_dev : protected I2C_Com {

    private:
        static constexpr uint8_t TH2_I2C_DEV_ADR = 0x40;

        static constexpr uint8_t REG_DATA_H = 0x01;
        static constexpr uint8_t REG_DATA_L = 0x02;
        static constexpr uint8_t REG_CONFIG = 0x03;
        static constexpr uint8_t CMD_MEASURE_HUMI = 0x01;
        static constexpr uint8_t CMD_MEASURE_TEMP = 0x11;

    public:
        TH02_dev(unsigned int device = 1) : I2C_Com(device,TH2_I2C_DEV_ADR){};
        ~TH02_dev(){};

        float ReadTemperature(void);
        float ReadHumidity(void);
};

#endif  // _TH02_DEV_H
