#include "spirpi.h"


SpiRpi::SpiRpi()
{

}



int spi_cs0_fd;				//file descriptor for the SPI device
int spi_cs1_fd;				//file descriptor for the SPI device
unsigned char spi_mode;
unsigned char spi_bitsPerWord;
unsigned int spi_speed;




//***********************************
//***********************************
//********** SPI OPEN PORT **********
//***********************************
//***********************************
//spi_device	0=CS0, 1=CS1
int SpiRpi::SpiOpenPort (int spi_device)
{
    int status_value = -1;
    int *spi_cs_fd;


    //----- SET SPI MODE -----
    //SPI_MODE_0 (0,0) 	CPOL = 0, CPHA = 0, Clock idle low, data is clocked in on rising edge, output data (change) on falling edge
    //SPI_MODE_1 (0,1) 	CPOL = 0, CPHA = 1, Clock idle low, data is clocked in on falling edge, output data (change) on rising edge
    //SPI_MODE_2 (1,0) 	CPOL = 1, CPHA = 0, Clock idle high, data is clocked in on falling edge, output data (change) on rising edge
    //SPI_MODE_3 (1,1) 	CPOL = 1, CPHA = 1, Clock idle high, data is clocked in on rising, edge output data (change) on falling edge
//    spi_mode = SPI_MODE_0;

    //----- SET BITS PER WORD -----
    spi_bitsPerWord = 8;

    //----- SET SPI BUS SPEED -----
    spi_speed = 1000000;		//1000000 = 1MHz (1uS per bit)


    if (spi_device)
        spi_cs_fd = &spi_cs1_fd;
    else
        spi_cs_fd = &spi_cs0_fd;


//    if (spi_device)
//        *spi_cs_fd = open(std::string("/dev/spidev0.1").c_str(), O_RDWR);
//    else
//        *spi_cs_fd = open(std::string("/dev/spidev0.0").c_str(), O_RDWR);

//    if (*spi_cs_fd < 0)
//    {
//        perror("Error - Could not open SPI device");
//        return -1;
//    }

//    status_value = ioctl(*spi_cs_fd, SPI_IOC_WR_MODE, &spi_mode);
//    if(status_value < 0)
//    {
//        perror("Could not set SPIMode (WR)...ioctl fail");
//        return -1;
//    }

//    status_value = ioctl(*spi_cs_fd, SPI_IOC_RD_MODE, &spi_mode);
//    if(status_value < 0)
//    {
//        perror("Could not set SPIMode (RD)...ioctl fail");
//        return -1;
//    }

//    status_value = ioctl(*spi_cs_fd, SPI_IOC_WR_BITS_PER_WORD, &spi_bitsPerWord);
//    if(status_value < 0)
//    {
//        perror("Could not set SPI bitsPerWord (WR)...ioctl fail");
//        return -1;
//    }

//    status_value = ioctl(*spi_cs_fd, SPI_IOC_RD_BITS_PER_WORD, &spi_bitsPerWord);
//    if(status_value < 0)
//    {
//        perror("Could not set SPI bitsPerWord(RD)...ioctl fail");
//        return -1;
//    }

//    status_value = ioctl(*spi_cs_fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed);
//    if(status_value < 0)
//    {
//        perror("Could not set SPI speed (WR)...ioctl fail");
//        return -1;
//    }

//    status_value = ioctl(*spi_cs_fd, SPI_IOC_RD_MAX_SPEED_HZ, &spi_speed);
//    if(status_value < 0)
//    {
//        perror("Could not set SPI speed (RD)...ioctl fail");
//        return -1;
//    }
    return(status_value);
}



//************************************
//************************************
//********** SPI CLOSE PORT **********
//************************************
//************************************
int SpiRpi::SpiClosePort (int spi_device)
{
    int status_value = -1;
    int *spi_cs_fd;

    if (spi_device)
        spi_cs_fd = &spi_cs1_fd;
    else
        spi_cs_fd = &spi_cs0_fd;


    status_value = close(*spi_cs_fd);
    if(status_value < 0)
    {
        perror("Error - Could not close SPI device");
        return -1;
    }
    return(status_value);
}



//*******************************************
//*******************************************
//********** SPI WRITE & READ DATA **********
//*******************************************
//*******************************************
//data		Bytes to write.  Contents is overwritten with bytes read.
int SpiRpi::SpiWriteAndRead (int spi_device, unsigned char *dataToWrite, unsigned char *datatoRead, int length)
{
    //struct spi_ioc_transfer spi[length];
    int i = 0;
    int retVal = -1;
    int *spi_cs_fd;

    if (spi_device)
        spi_cs_fd = &spi_cs1_fd;
    else
        spi_cs_fd = &spi_cs0_fd;

    //one spi transfer for each byte

//    for (i = 0 ; i < length ; i++)
//    {
//        memset(&spi[i], 0, sizeof (spi[i]));
//        spi[i].tx_buf        = (unsigned long)(dataToWrite + i); // transmit from "data"
//        spi[i].rx_buf        = (unsigned long)(datatoRead + i) ; // receive into "data"
//        spi[i].len           = sizeof(*(dataToWrite + i)) ;
//        spi[i].delay_usecs   = 0 ;
//        spi[i].speed_hz      = spi_speed ;
//        spi[i].bits_per_word = spi_bitsPerWord ;
//        spi[i].cs_change = 0;

//    }

//    ioctl(*spi_cs_fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed) ;
//    ioctl(*spi_cs_fd, SPI_IOC_RD_MAX_SPEED_HZ, &spi_speed) ;

//    //qDebug() << "speed " << spi_speed;

//    retVal = ioctl(*spi_cs_fd, SPI_IOC_MESSAGE(length), &spi) ;

//    if(retVal < 0)
//    {
//        perror("Error - Problem transmitting spi data..ioctl");
//        return -1;
//    }

    return retVal;
}


// NON FUNZIONA!!!!
void SpiRpi::usingBcm()
{

//    //Setup SPI pins
//    bcm2835_spi_begin();

//    //Set CS pins polarity to low
//    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, 0);
//    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, 0);

//    //Set SPI clock speed
//    //	BCM2835_SPI_CLOCK_DIVIDER_65536 = 0,       ///< 65536 = 262.144us = 3.814697260kHz (total H+L clock period)
//    //	BCM2835_SPI_CLOCK_DIVIDER_32768 = 32768,   ///< 32768 = 131.072us = 7.629394531kHz
//    //	BCM2835_SPI_CLOCK_DIVIDER_16384 = 16384,   ///< 16384 = 65.536us = 15.25878906kHz
//    //	BCM2835_SPI_CLOCK_DIVIDER_8192  = 8192,    ///< 8192 = 32.768us = 30/51757813kHz
//    //	BCM2835_SPI_CLOCK_DIVIDER_4096  = 4096,    ///< 4096 = 16.384us = 61.03515625kHz
//    //	BCM2835_SPI_CLOCK_DIVIDER_2048  = 2048,    ///< 2048 = 8.192us = 122.0703125kHz
//    //	BCM2835_SPI_CLOCK_DIVIDER_1024  = 1024,    ///< 1024 = 4.096us = 244.140625kHz
//    //	BCM2835_SPI_CLOCK_DIVIDER_512   = 512,     ///< 512 = 2.048us = 488.28125kHz
//    //	BCM2835_SPI_CLOCK_DIVIDER_256   = 256,     ///< 256 = 1.024us = 976.5625MHz
//    //	BCM2835_SPI_CLOCK_DIVIDER_128   = 128,     ///< 128 = 512ns = = 1.953125MHz
//    //	BCM2835_SPI_CLOCK_DIVIDER_64    = 64,      ///< 64 = 256ns = 3.90625MHz
//    //	BCM2835_SPI_CLOCK_DIVIDER_32    = 32,      ///< 32 = 128ns = 7.8125MHz
//    //	BCM2835_SPI_CLOCK_DIVIDER_16    = 16,      ///< 16 = 64ns = 15.625MHz
//    //	BCM2835_SPI_CLOCK_DIVIDER_8     = 8,       ///< 8 = 32ns = 31.25MHz
//    //	BCM2835_SPI_CLOCK_DIVIDER_4     = 4,       ///< 4 = 16ns = 62.5MHz
//    //	BCM2835_SPI_CLOCK_DIVIDER_2     = 2,       ///< 2 = 8ns = 125MHz, fastest you can get
//    //	BCM2835_SPI_CLOCK_DIVIDER_1     = 1,       ///< 1 = 262.144us = 3.814697260kHz, same as 0/65536
//    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_256);

//    //Set SPI data mode
//    //	BCM2835_SPI_MODE0 = 0,  // CPOL = 0, CPHA = 0, Clock idle low, data is clocked in on rising edge, output data (change) on falling edge
//    //	BCM2835_SPI_MODE1 = 1,  // CPOL = 0, CPHA = 1, Clock idle low, data is clocked in on falling edge, output data (change) on rising edge
//    //	BCM2835_SPI_MODE2 = 2,  // CPOL = 1, CPHA = 0, Clock idle high, data is clocked in on falling edge, output data (change) on rising edge
//    //	BCM2835_SPI_MODE3 = 3,  // CPOL = 1, CPHA = 1, Clock idle high, data is clocked in on rising, edge output data (change) on falling edge
//    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);		//(SPI_MODE_# | SPI_CS_HIGH)=Chip Select active high, (SPI_MODE_# | SPI_NO_CS)=1 device per bus no Chip Select

//    //Set with CS pin to use for next transfers
//    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);

//    //Transfer 1 byte
//    //uint8_t data;
//    //data = bcm2835_spi_transfer((uint8_t)0x55);

//    //Transfer many bytes
//    char data_buffer[10];
//    int Count;
//    for (Count = 0; Count < 10; Count++)
//        data_buffer[Count] = 0x80 + Count;
//    bcm2835_spi_transfern(&data_buffer[0], 10);			//data_buffer used for tx and rx

//    //Return SPI pins to default inputs state
//    bcm2835_spi_end();
}

int SpiRpi::GpioReadPin(uint8_t PIN)
{
//    if (!bcm2835_init())
//        return -1;
//    // Set RPI pin to be an input
//    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_INPT);
//    //  with a pullup
//    bcm2835_gpio_set_pud(PIN, BCM2835_GPIO_PUD_OFF);
//    // Read some data
//    uint8_t value = bcm2835_gpio_lev(PIN);
//    //printf("read from GPIO: %d\n", value);

//    bcm2835_close();
    return 0;
}

int SpiRpi::GpioWritePin(uint8_t PIN, bool val)
{
//    if (!bcm2835_init())
//        return -1;
//    //  with a pullup
//    bcm2835_gpio_set_pud(PIN, BCM2835_GPIO_PUD_OFF);
//    // Set RPI pin to be an input
//    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);

//    if(val)
//        bcm2835_gpio_set(PIN);
//    else
//        bcm2835_gpio_clr(PIN);
//    //printf("write GPIO: %d\n", val);

//    bcm2835_close();
    return val;
}

