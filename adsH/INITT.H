#ifndef __initT_H__
#define __initT_H__

#include"STC15F2K60S2.h"

#ifndef  ADS1262_START
#define  ADS1262_START  P54
#endif 
#ifndef uchar
#define uchar unsigned char
#endif
#ifndef uint
#define uint unsigned int
#endif

//extern void Enable_NVIC(void);
//extern void Disable_NVIC(void);
//extern void delay_50us();
extern void delay_ms(unsigned int x);

//UART 相关函数------------------------

void initT();
void SendData(unsigned char dat);
void SendString(char *s);

extern unsigned int t0_num;
extern unsigned char flag_time;
extern unsigned char b_ad_finish;
extern unsigned char i2;
extern unsigned char TempData[8];
extern unsigned char code dofly_DuanMa[16];
//UART----END-------------------------------
//RS485
extern unsigned char cntRxd ;
extern bit flagOnceTxd;  //单次发送完成标志，即发送完一个字节
extern unsigned char pdata bufRxd[40]; //串口接收缓冲区

extern void UartRxMonitor(unsigned char ms);

#endif