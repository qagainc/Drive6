#include"define.h"	

unsigned int adv2;
struct 
{
 int x;
 int y;

}test1;

void main()
{


   test1.x=0;
   test1.y=0;
   
 	uchar bai,shi,ge,qian,wan;   
    char JK=0;
    initall();  
   SendString("STC15W413AS 05\r\n");
 while(1)
 {
     
    UartDriver(); 
  if(flag_time==1)
	{
	 flag_time=0;	
     // SendString("STC15W413AS 03\r\n");
		 
//    ES=0;
//	  TI=1;
//	 printf("The voltage is %fV\n",ad_v0);
// 
//	  while(!TI);
//	  TI=0;
//	  ES=1;		 
	}
 switch(JK)
 {
    case 0:
   adv2=12345;
   wan=adv2/10000%10;
   qian=adv2/1000%10;    
   bai=adv2/100%10;
   shi=adv2/10%10;
   ge=adv2%10;
   TempData[4]=dofly_DuanMa[wan]|0x80; //十位温度
   TempData[3]=dofly_DuanMa[qian]; //十位温度    
   TempData[2]=dofly_DuanMa[bai]; //十位温度
   TempData[1]=dofly_DuanMa[shi]; //个位温度,带小数点
   TempData[0]=dofly_DuanMa[ge];
    break;
   case 1:
   TempData[4]=0xF6; //十位温度
   TempData[3]=dofly_DuanMa[regGroup[0]/16]; //十位温度    
   TempData[2]=dofly_DuanMa[regGroup[0]%16]; //十位温度
   TempData[1]=dofly_DuanMa[regGroup[1]/16]; //个位温度,带小数点
   TempData[0]=dofly_DuanMa[regGroup[1]%16]; 
   break;
   case 2:
   TempData[4]=0xB8; //十位温度
   TempData[3]=dofly_DuanMa[regGroup[2]/16]; //十位温度    
   TempData[2]=dofly_DuanMa[regGroup[2]%16]; //十位温度
   TempData[1]=dofly_DuanMa[regGroup[3]/16]; //个位温度,带小数点
   TempData[0]=dofly_DuanMa[regGroup[3]%16]; 
   break; 
   case 3:
   TempData[4]=0x2D; //十位温度
   TempData[3]=dofly_DuanMa[regGroup[4]/16]; //十位温度    
   TempData[2]=dofly_DuanMa[regGroup[4]%16]; //十位温度
   TempData[1]=dofly_DuanMa[regGroup[5]/16]; //个位温度,带小数点
   TempData[0]=dofly_DuanMa[regGroup[5]%16]; 
   break; 
   default:JK=0;break;
   
 }
	if(key2==0)
	{
	 delay_ms(2);
	 if(key2==0)
	 {                 
     JK--;         
     if(JK<0)
     JK=3;         
     
     while(!key2);		 
	 }	
	}
	if(key3==0)
	{
	 delay_ms(2);
	 if(key3==0)
	 { 
     JK++;
     if(JK>3)
     JK=0;         
    
     while(!key3);         
	 
	 }	
	}
    
    
 }
 
}
// if(TR0==0)
//  {
//  Display2();
//  }
 // SendString("STC15F2K61S2\r\nUart Test !\r\n");
// SendString("ADS1232 Tr0=18\r\n");
	 
//	 ADS1262_START=1;
//     WaitForDRDY();
//     ADS1262_START=0;
//     ad_sample_dat = ADS126xReadData(6, 1);
//
////	  ad_val=get_ad();
//	  adv=(ad_sample_dat/(256.0*256*256*256))*5.0*100.0;
//	  ad_v0=ad_sample_dat/(256.0*256*256*256)*5.0;
	//  ES=0;
	//  TI=1;
	 // printf("The voltage is %fV\n",ad_sample_dat);
	  //UART_Send_Str("ADS1262 test!\r\n");
	 // printf("The voltage is");
	 // while(!TI);
	 // TI=0;
	 // ES=1;
	 // SendData(miao+0x30);
	 // SendData('\r'); 
	 // SendData('\n');
	 
// void LoadInitRegSettings(void)
//{
//	uchar AdcRegData[ADS126x_NUM_REG];							//Stores the register read values
//	uchar WriteRegData[ADS126x_NUM_REG];							//Stores the register write values
//
//	ADS126x_Read_Register(ID, ADS126x_NUM_REG, AdcRegData);			//Read ALL registers
//
//	/* Configure Register Settings */
//	WriteRegData[ID] = AdcRegData[ID];								//ID
//	WriteRegData[POWER] = INTREF;									//POWER (RESET = 0, INTREF = 1)
//	WriteRegData[INTERFACE] = STATUS | CRC_ON;						//INTERFACE
//	WriteRegData[MODE0] = DELAY_278us;								//MODE0 (Set DELAY)
//	WriteRegData[MODE1] = (AdcRegData[MODE1] & FILTER_MASK);		//MODE1
//	WriteRegData[MODE2] = (AdcRegData[MODE2] & ~BYPASS) | GAIN_32;	//MODE2 (BYPASS = 0, GAIN = 32 V/V)
//	WriteRegData[INPMUX] = MUXP_AIN2 | MUXN_AIN3;					//INPMUX (AINP = AIN1, AINN = AIN2)
//
//	WriteRegData[OFCAL0] = OFCAL0_DEFAULT_VALUE;					//OFCAL0 (reset to default)
//	WriteRegData[OFCAL1] = OFCAL1_DEFAULT_VALUE;					//OFCAL1 (reset to default)
//	WriteRegData[OFCAL2] = OFCAL2_DEFAULT_VALUE;					//OFCAL2 (reset to default)
//	WriteRegData[FSCAL0] = FSCAL0_DEFAULT_VALUE;					//FSCAL0 (reset to default)
//	WriteRegData[FSCAL1] = FSCAL1_DEFAULT_VALUE;					//FSCAL1 (reset to default)
//	WriteRegData[FSCAL2] = FSCAL2_DEFAULT_VALUE;					//FSCAL2 (reset to default)
//
//	WriteRegData[IDACMUX] = MUX2_NO_CONM | MUX1_AINCOM;				//IDACMUX (IDAC1MUX = AINCOM)
//	WriteRegData[IDACMAG] = MAG2_OFF | MAG1_500uA;					//IDACMAG (IDAC1MAG = 500 uA)
//	WriteRegData[REFMUX] = RMUXP_AIN0 | RMUXN_AIN3;					//REFMUX (REFP = AIN0, REFN = AIN3)
//
//	WriteRegData[TDACP] = TDACP_DEFAULT_VALUE;						//TDACP (reset to default)
//	WriteRegData[TDACN] = TDACN_DEFAULT_VALUE;						//TDACN (reset to default)
//
//	WriteRegData[GPIOCON] = CON6_AIN09 | CON5_AIN08;				//GPIOCON (Enable GPIOs on AIN8 & AIN9)
//
//	WriteRegData[GPIODIR] = GPIOCON_DEFAULT_VALUE;					//GPIODIR (reset to default)
//
//	WriteRegData[GPIODAT] = DAT5_AIN08;								//GPIODAT (Biases bridge with + polarity)
//
//	ADS126x_Write_Register(ID, ADS126x_NUM_REG, &WriteRegData[0]);	//Write ALL registers
//
//}
//		 SendData(ADC_Bytes[0]);
//		SendData(ADC_Bytes[1]);
//		SendData(ADC_Bytes[2]);
//		SendData(ADC_Bytes[3]);
//		SendData(ADC_Bytes[4]);	
//     SendData(ADC_Bytes[5]);

//	if(key1==0)
//	{
//	 delay_ms(2);
//	 if(key1==0)
//	 {
//      TR0=0;
//	  if(i2>20)
//	  i2=0;
//	  i2++;
//	  while(!key1);
//	 
//	 }
//	 }

//	if(key2==0)
//	{
//	 delay_ms(2);
//	 if(key2==0)
//	 {
//	  TR0=0;
//	  if(i2==0)
//	  i2=20;
//	  i2--;
//	  while(!key2); 
//	 }
//	}
//	   SendData(read_reg_buffer[0]);
//	   SendData(read_reg_buffer[1]);
//	   SendData(read_reg_buffer[2]);
//	   SendData(read_reg_buffer[3]);
//	   SendData(read_reg_buffer[4]);	
//     SendData(read_reg_buffer[5]);
//	 adcdata32= ((unsigned long)ADC_Bytes[1] << 24) |
//				((unsigned long)ADC_Bytes[2]<<16)|
//                ((unsigned long)ADC_Bytes[3]<<8)|
//                ((unsigned long)ADC_Bytes[4]<<0);	
