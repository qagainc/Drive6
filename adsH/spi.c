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
sbit SPISS      =   P1^2;       //SPI�ӻ�ѡ���, ���ӵ�����MCU��SS��
                                //��SPIΪһ�����ģʽʱ,��ʹ����������ͨIO�����ӵ��ӻ���SS��
unsigned char SPIBuf=0xff;

//SPCTL = SPEN | MSTR | SSIG | SPDLL;        //����ģʽ
void InitSPI()
{   
    //SPCTL = 0xD4 | 0x03; //01
    SPCTL = 0xD4 | 0x03; //01
    SPDAT = 0;                  //��ʼ��SPI����
    SPSTAT = SPIF | WCOL;       //���SPI״̬λ

}
///////////////////////////////////////////////////////////
void hardware_spi_write(unsigned char senddata)
{
 SPDAT=senddata;
 while((SPSTAT&0x80)==0);
 SPSTAT=0xC0;
}

//--------------------------------------------------------------------------//
//Ӳ��SPI������//
//��������
//����ֵ���ͣ�unsigned char//
unsigned char hardware_spi_read()
{
	SPDAT = 0x00;
while((SPSTAT&0x80)==0);
	//while((SPSTAT&0x80));
	SPSTAT=0xC0;  //  SPIFд1��0 
	return SPDAT;
} 

