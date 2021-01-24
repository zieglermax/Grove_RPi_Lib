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

#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <cstdint>
#include <iostream>


/****************************************************************************/
/***       Class member Functions                                         ***/
/****************************************************************************/

float TH02_dev::ReadTemperature(void) {
    /* Start a new temperature conversion */
    I2C_WriteReg(REG_CONFIG, CMD_MEASURE_TEMP);
    //delay(100);
    /* Wait until conversion is done */
    while (!isAvailable());
    uint16_t value = I2C_ReadData2byte(REG_DATA_L, REG_DATA_H);

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
    I2C_WriteReg(REG_CONFIG, CMD_MEASURE_HUMI);

    /* Wait until conversion is done */
    //delay(100);
    while (!isAvailable());
    uint16_t value = I2C_ReadData2byte(REG_DATA_L, REG_DATA_H);

    value = value >> 4;

    /*
        Formula:
        Humidity(%) = (Value/16) - 24
    */
    //std::cout << "RawHumidityVal: " << value << std::endl;
    float humility = (value / 16.0) - 24.0;

    return humility;
}
