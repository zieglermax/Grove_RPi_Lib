/*
    BaseHat_AnalogPorts.cpp
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

/****************************************************************************/
/***        Include files                                                 ***/
/****************************************************************************/
#include "I2C_Com.h"
#include "BaseHat_AnalogPorts.h"

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

uint8_t BaseHat::version(void)
{
    return I2C_ReadData(Reg_Version);
}

double BaseHat::PowerSupplyVoltage(void)
{
    return I2C_ReadData2byte(Reg_PowerSupplyVoltage) / 1000.0;
}

uint16_t BaseHat::ReadRaw(AnalogPort analogPort)
{
    return I2C_ReadData2byte(Reg_RawBase + analogPort);
}

double BaseHat::ReadVoltage(AnalogPort analogPort)
{
    return I2C_ReadData2byte(Reg_RawBase + analogPort) / 1000.0 ;
}
