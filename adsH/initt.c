#include <string.h>
#include "initT.h"
//#include "RS485.h"

sbit INT0 = 0xB2;

unsigned char i2;
#define FOSC 11059200L          //系统频率
#define BAUD 9600             //串口波特率

//#define NONE_PARITY     0       //无校验
//#define ODD_PARITY      1       //奇校验
//#define EVEN_PARITY     2       //偶校验
//#define MARK_PARITY     3       //标记校验
//#define SPACE_PARITY    4       //空白校验

//#define PARITYBIT EVEN_PARITY   //定义校验位
//#define S1_S0 0x40              //P_SW1.6
//#define S1_S1 0x80              //P_SW1.7

bit busy;
/*
T0位1s T1为串口通讯
TI=0;	//发送完数据后，硬件置1，软件清0
发送数据时要先把ES=0，数据处理好后再ES=1；即发送出去
RI=0;	//发送完数据后，硬件置1，软件清0
*/
unsigned int t0_num=0;
unsigned char  flag_time;
unsigned char EnLed = 0; 

unsigned char TempData[8]; //存储显示值的全局变量
unsigned char code dofly_WeiMa[]={0x10,0x08,0x04,0x02,0x01};//分别对应相应的数码管点亮,即位码
unsigned char code dofly_DuanMa[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};// 显示段码值0~9


//RS485 
unsigned char cntRxd = 0;
bit flagOnceTxd = 0;  //单次发送完成标志，即发送完一个字节
unsigned char pdata bufRxd[40]; //串口接收缓冲区

//void Enable_NVIC(void)
//{    
//	EA=1;	//串口总中断
//	ES=1;	//打开串行口中断。
//}

//void Disable_NVIC(void)
//{
//	 EA=0;	//串口总中断
//     ES=0;	//打开串行口中断。
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
//    SCON = 0x50;                //8位可变波特率
//#elif (PARITYBIT == ODD_PARITY) || (PARITYBIT == EVEN_PARITY) || (PARITYBIT == MARK_PARITY)
//    SCON = 0xda;                //9位可变波特率,校验位初始为1
//#elif (PARITYBIT == SPACE_PARITY)
//    SCON = 0xd2;                //9位可变波特率,校验位初始为0
//#endif

//    AUXR = 0x40;                //定时器1为1T模式
//    TMOD = 0x00;                //定时器1为模式0(16位自动重载)
//    TL1 = (65536 - (FOSC/4/BAUD));   //设置波特率重装值
//    TH1 = (65536 - (FOSC/4/BAUD))>>8;
//	TR1=1; //T1的启动，就是中断的软启动
    
    SCON = 0x50;                //8位可变波特率
	AUXR |= 0x01;		//串口1选择定时器2为波特率发生器
	AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
	//T2L = 0xE0;		//设定定时初值
	//T2H = 0xFE;		//设定定时初值
    T2L = (65536-(FOSC/4/BAUD));		//设置波特率重装值
	T2H = (65536-(FOSC/4/BAUD))>>8;
	AUXR |= 0x10;		//启动定时器2

	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xCD;		//设置定时初值
	TH0 = 0xD4;		//设置定时初值
	TF0 = 0;		//清除TF0标志

    ES=1;	//打开串行口中断。
  	EA=1;	//串口总中断

    ET0 = 1;   //使能定时器0中断
	TR0 = 1;   //定时器0开始计时

//	INT0 = 1;
 //   IT0 = 1;                    //设置INT0的中断类型 (1:仅下降沿 0:上升沿和下降沿)
 //   EX0 = 1; 			       //使能INT0中断

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
   UartRxMonitor(1);  //串口接收监控
}

void ser() interrupt 4	
{
    if (RI)
    {
        RI = 0;                 //清除RI位
     if (cntRxd < sizeof(bufRxd)) //接收缓冲区尚未用完时，
        {
            bufRxd[cntRxd++] = SBUF; //保存接收字节，并递增计数器
        }   
    }
    if (TI)
    {
        TI = 0;                 //清除TI位
        busy = 0;               //清忙标志
        flagOnceTxd = 1;  //设置单次发送完成标志
    }


}

/*----------------------------
发送串口数据
----------------------------*/
void SendData(unsigned char dat)
{
    while (busy);               //等待前面的数据发送完成
//    ACC = dat;                  //获取校验位P (PSW.0)
//    if (P)                      //根据P来设置校验位
//    {
//#if (PARITYBIT == ODD_PARITY)
//        TB8 = 0;                //设置校验位为0
//#elif (PARITYBIT == EVEN_PARITY)
//        TB8 = 1;                //设置校验位为1
//#endif
//    }
//    else
//    {
//#if (PARITYBIT == ODD_PARITY)
//        TB8 = 1;                //设置校验位为1
//#elif (PARITYBIT == EVEN_PARITY)
//        TB8 = 0;                //设置校验位为0
//#endif
//    }
    busy = 1;
    SBUF=dat;
//    SBUF = ACC;                 //写数据到UART数据寄存器
}

/*----------------------------
发送字符串
----------------------------*/
void SendString(char *s)
{
    while (*s)                  //检测字符串结束标志
    {
        SendData(*s++);         //发送当前字符
    }
}



