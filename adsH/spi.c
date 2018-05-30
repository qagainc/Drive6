#include"spi.h"

#define SPIF        0x80        //SPSTAT.7                                
#define WCOL        0x40        //SPSTAT.6                                                        
#define SSIG        0x80        //SPCTL.7                                 
#define SPEN        0x40        //SPCTL.6                                 
#define DORD        0x20        //SPCTL.5                                 
#define MSTR        0x10        //SPCTL.4                                 
#define CPOL        0x08        //SPCTL.3                                 
#define CPHA        0x04        //SPCTL.2                                 
#define SPDHH       0x00        //CPU_CLK/4                               
#define SPDH        0x01        //CPU_CLK/16                              
#define SPDL        0x02        //CPU_CLK/64                              
#define SPDLL       0x03        //CPU_CLK/128                                                    
sbit SPISS      =   P1^2;       //SPI从机选择口, 连接到其它MCU的SS口
                                //当SPI为一主多从模式时,请使用主机的普通IO口连接到从机的SS口
unsigned char SPIBuf=0xff;

//SPCTL = SPEN | MSTR | SSIG | SPDLL;        //主机模式
void InitSPI()
{   
    //SPCTL = 0xD4 | 0x03; //01
    SPCTL = 0xD4 | 0x03; //01
    SPDAT = 0;                  //初始化SPI数据
    SPSTAT = SPIF | WCOL;       //清除SPI状态位

}
///////////////////////////////////////////////////////////
void hardware_spi_write(unsigned char senddata)
{
 SPDAT=senddata;
 while((SPSTAT&0x80)==0);
 SPSTAT=0xC0;
}

//--------------------------------------------------------------------------//
//硬件SPI读数据//
//参数：无
//返回值类型：unsigned char//
unsigned char hardware_spi_read()
{
	SPDAT = 0x00;
while((SPSTAT&0x80)==0);
	//while((SPSTAT&0x80));
	SPSTAT=0xC0;  //  SPIF写1清0 
	return SPDAT;
} 

