#include <string.h>
#include "initT.h"
//#include "RS485.h"

sbit INT0 = 0xB2;

unsigned char i2;
#define FOSC 11059200L          //ϵͳƵ��
#define BAUD 9600             //���ڲ�����

//#define NONE_PARITY     0       //��У��
//#define ODD_PARITY      1       //��У��
//#define EVEN_PARITY     2       //żУ��
//#define MARK_PARITY     3       //���У��
//#define SPACE_PARITY    4       //�հ�У��

//#define PARITYBIT EVEN_PARITY   //����У��λ
//#define S1_S0 0x40              //P_SW1.6
//#define S1_S1 0x80              //P_SW1.7

bit busy;
/*
T0λ1s T1Ϊ����ͨѶ
TI=0;	//���������ݺ�Ӳ����1�������0
��������ʱҪ�Ȱ�ES=0�����ݴ���ú���ES=1�������ͳ�ȥ
RI=0;	//���������ݺ�Ӳ����1�������0
*/
unsigned int t0_num=0;
unsigned char  flag_time;
unsigned char EnLed = 0; 

unsigned char TempData[8]; //�洢��ʾֵ��ȫ�ֱ���
unsigned char code dofly_WeiMa[]={0x10,0x08,0x04,0x02,0x01};//�ֱ��Ӧ��Ӧ������ܵ���,��λ��
unsigned char code dofly_DuanMa[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};// ��ʾ����ֵ0~9


//RS485 
unsigned char cntRxd = 0;
bit flagOnceTxd = 0;  //���η�����ɱ�־����������һ���ֽ�
unsigned char pdata bufRxd[40]; //���ڽ��ջ�����

//void Enable_NVIC(void)
//{    
//	EA=1;	//�������ж�
//	ES=1;	//�򿪴��п��жϡ�
//}

//void Disable_NVIC(void)
//{
//	 EA=0;	//�������ж�
//     ES=0;	//�򿪴��п��жϡ�
//}

//void delay_50us()
//{
//	uchar i;
//	for (i=0; i<30; i++);
//}

/*===========================================================================================*/	 
void delay_ms(unsigned int x)
{
	unsigned int a, b;
	for (a=0; a<x; a++)
	{
  	    for (b=0; b<300;b++);
			
	}
}

void initT()
{

//    ACC = P_SW1;
//    ACC &= ~(S1_S0 | S1_S1);    //S1_S0=0 S1_S1=0
//    P_SW1 = ACC;                //(P3.0/RxD, P3.1/TxD)

//#if (PARITYBIT == NONE_PARITY)
//    SCON = 0x50;                //8λ�ɱ䲨����
//#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
//    SCON = 0xda;                //9λ�ɱ䲨����,У��λ��ʼΪ1
//#elif (PARITYBIT == SPACE_PARITY)
//    SCON = 0xd2;                //9λ�ɱ䲨����,У��λ��ʼΪ0
//#endif

//    AUXR = 0x40;                //��ʱ��1Ϊ1Tģʽ
//    TMOD = 0x00;                //��ʱ��1Ϊģʽ0(16λ�Զ�����)
//    TL1 = (65536 - (FOSC/4/BAUD));   //���ò�������װֵ
//    TH1 = (65536 - (FOSC/4/BAUD))>>8;
//	TR1=1; //T1�������������жϵ�������
    
    SCON = 0x50;                //8λ�ɱ䲨����
	AUXR |= 0x01;		//����1ѡ��ʱ��2Ϊ�����ʷ�����
	AUXR |= 0x04;		//��ʱ��2ʱ��ΪFosc,��1T
	//T2L = 0xE0;		//�趨��ʱ��ֵ
	//T2H = 0xFE;		//�趨��ʱ��ֵ
    T2L = (65536-(FOSC/4/BAUD));		//���ò�������װֵ
	T2H = (65536-(FOSC/4/BAUD))>>8;
	AUXR |= 0x10;		//������ʱ��2

	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0xCD;		//���ö�ʱ��ֵ
	TH0 = 0xD4;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־

    ES=1;	//�򿪴��п��жϡ�
  	EA=1;	//�������ж�

    ET0 = 1;   //ʹ�ܶ�ʱ��0�ж�
	TR0 = 1;   //��ʱ��0��ʼ��ʱ

//	INT0 = 1;
 //   IT0 = 1;                    //����INT0���ж����� (1:���½��� 0:�����غ��½���)
 //   EX0 = 1; 			       //ʹ��INT0�ж�

}
void timer0() interrupt 1
{
	t0_num++;
	if(t0_num==1000)
	{
		t0_num=0;
		flag_time=1;
	}

    P1=0x00;
    P2&=~0x1f;
   switch(EnLed)
	{
		case 0: P2|=dofly_WeiMa[0]; EnLed++; P1=TempData[0];break;
		case 1: P2|=dofly_WeiMa[1]; EnLed++; P1=TempData[1];break;
		case 2: P2|=dofly_WeiMa[2]; EnLed++; P1=TempData[2];break;
		case 3: P2|=dofly_WeiMa[3]; EnLed++; P1=TempData[3];break;
		case 4: P2|=dofly_WeiMa[4]; EnLed=0; P1=TempData[4];break;
		default:break;
	}
   UartRxMonitor(1);  //���ڽ��ռ��
}

void ser() interrupt 4	
{
    if (RI)
    {
        RI = 0;                 //���RIλ
     if (cntRxd < sizeof(bufRxd)) //���ջ�������δ����ʱ��
        {
            bufRxd[cntRxd++] = SBUF; //��������ֽڣ�������������
        }   
    }
    if (TI)
    {
        TI = 0;                 //���TIλ
        busy = 0;               //��æ��־
        flagOnceTxd = 1;  //���õ��η�����ɱ�־
    }


}

/*----------------------------
���ʹ�������
----------------------------*/
void SendData(unsigned char dat)
{
    while (busy);               //�ȴ�ǰ������ݷ������
//    ACC = dat;                  //��ȡУ��λP (PSW.0)
//    if (P)                      //����P������У��λ
//    {
//#if (PARITYBIT == ODD_PARITY)
//        TB8 = 0;                //����У��λΪ0
//#elif (PARITYBIT == EVEN_PARITY)
//        TB8 = 1;                //����У��λΪ1
//#endif
//    }
//    else
//    {
//#if (PARITYBIT == ODD_PARITY)
//        TB8 = 1;                //����У��λΪ1
//#elif (PARITYBIT == EVEN_PARITY)
//        TB8 = 0;                //����У��λΪ0
//#endif
//    }
    busy = 1;
    SBUF=dat;
//    SBUF = ACC;                 //д���ݵ�UART���ݼĴ���
}

/*----------------------------
�����ַ���
----------------------------*/
void SendString(char *s)
{
    while (*s)                  //����ַ���������־
    {
        SendData(*s++);         //���͵�ǰ�ַ�
    }
}



