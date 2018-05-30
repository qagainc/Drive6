#ifndef _SPI_H__
#define _SPI_H__ 
 
#include"STC15F2K60S2.h"

#define USE_HARDWARE_SPI //使用SPI硬件
/* STC硬件SPI硬件接口 -----------------------------------------------------------*/
// SD_MOSI P1^5
// SD_MISO P1^6 
// SD_SCLK P1^7   
//======================================================================================================================//
//硬件SPI
extern void HARDWARE_SPI_INT(unsigned char speed);	//spi硬件初始  speed=0/1/2/3 分别对应4分频，16分频，64分频，128分频
extern void InitSPI();
extern void hardware_spi_write(unsigned char n);
extern unsigned char hardware_spi_read();


#endif




