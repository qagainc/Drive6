#ifndef __RS485_H__
#define __RS485_H__



#ifndef uchar
#define uchar unsigned char
#endif
#ifndef uint
#define uint unsigned int
#endif


extern bit flagBuzzOn;
extern unsigned char regGroup[10];


extern unsigned int GetCRC16(unsigned char *ptr,  unsigned char len);
extern void UartRxMonitor(unsigned char ms);  //串口接收监控函数
extern unsigned char UartRead(unsigned char *buf, unsigned char len); //串口数据读取函数，数据接收指针buf，读取数据长度len，返回值为实际读取到的数据长度
extern void DelayX10us(unsigned char t);  //软件延时函数，延时时间(t*10)us
extern void UartWrite(unsigned char *buf, unsigned char len); //串口数据写入函数，即串口发送函数，待发送数据指针buf，数据长度len
extern void UartDriver(); //串口驱动函数，检测接收到的命令并执行相应动作

#endif