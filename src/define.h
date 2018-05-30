//#include"STC15F2K60S2.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h> 
#include "initT.h"
#include "RS485.h"

typedef unsigned char U8;
typedef unsigned int U16;
typedef unsigned long U32;
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

sbit key1=P3^4;
sbit key2=P3^5;
sbit key3=P3^6;
sbit key4=P3^7;

 void initall()
 {
    P1M0 = 0xff;
    P1M1 = 0x00;
    P2M0 = 0xff;
    P2M1 = 0x00;
    P3M0 = 0xfa;
    P3M1 = 0x05;	 
    P1=0xff;
    P2=0xff;
    P3=0xff; 
//while(1);     
    initT();
 
 
 }