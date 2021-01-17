#include "TH02_dev.h"
#include <iostream>
#include <stdio.h>

int main (int argc, char *argv[])
{
    TH02_dev th02;

    std::cout << "Start to read TH02 Temperature and Humidity" << std::endl;

    for( int i = 0; i< 1000; i++)
    {
        std::cout << " Temp: " << th02.ReadTemperature();
        std::cout << " \t\t Humi: " << th02.ReadHumidity() << std::endl;
        usleep(10000);
    }

    return 0;
}
