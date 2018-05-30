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
extern void UartRxMonitor(unsigned char ms);  //���ڽ��ռ�غ���
extern unsigned char UartRead(unsigned char *buf, unsigned char len); //�������ݶ�ȡ���������ݽ���ָ��buf����ȡ���ݳ���len������ֵΪʵ�ʶ�ȡ�������ݳ���
extern void DelayX10us(unsigned char t);  //�����ʱ��������ʱʱ��(t*10)us
extern void UartWrite(unsigned char *buf, unsigned char len); //��������д�뺯���������ڷ��ͺ���������������ָ��buf�����ݳ���len
extern void UartDriver(); //�������������������յ������ִ����Ӧ����

#endif