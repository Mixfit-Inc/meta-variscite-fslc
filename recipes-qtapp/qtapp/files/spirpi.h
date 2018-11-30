// Author: Roberto Bellinato roberto.bellinato@egicon.com

#ifndef SPIRPI_H
#define SPIRPI_H

#include <qdebug.h>
//#include <bcm2835.h>
#include <fcntl.h>				//Needed for SPI port
//#include <sys/ioctl.h>			//Needed for SPI port
//#include <linux/spi/spidev.h>	//Needed for SPI port
#include <unistd.h>			//Needed for SPI port
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <cstring>

class SpiRpi
{
public:
    SpiRpi();
    int SpiOpenPort(int spi_device);
    int SpiClosePort(int spi_device);
    int GpioReadPin(uint8_t PIN);
    int SpiWriteAndRead(int spi_device, unsigned char *dataToWrite, unsigned char *datatoRead, int length);
    void usingBcm();
    int GpioWritePin(uint8_t PIN, bool val);
};

#endif // SPIRPI_H
