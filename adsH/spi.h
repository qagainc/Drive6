#ifndef _SPI_H__
#define _SPI_H__ 
 
#include"STC15F2K60S2.h"

#define USE_HARDWARE_SPI //ʹ��SPIӲ��
/* STCӲ��SPIӲ���ӿ� -----------------------------------------------------------*/
// SD_MOSI P1^5
// SD_MISO P1^6 
// SD_SCLK P1^7   
//======================================================================================================================//
//Ӳ��SPI
extern void HARDWARE_SPI_INT(unsigned char speed);	//spiӲ����ʼ  speed=0/1/2/3 �ֱ��Ӧ4��Ƶ��16��Ƶ��64��Ƶ��128��Ƶ
extern void InitSPI();
extern void hardware_spi_write(unsigned char n);
extern unsigned char hardware_spi_read();


#endif




