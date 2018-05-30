#define DataPort P2 //定义数据端口 程序中遇到DataPort 则用P0 替换
#define DataPort2 P3
unsigned char TempData[8]; //存储显示值的全局变量

unsigned char code dofly_DuanMa[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};// 显示段码值0~9
unsigned char code dofly_WeiMa[]={0x80,0x40,0x20,0x10,0x08};//分别对应相应的数码管点亮,即位码

void Display2()
{
	
	DataPort2 &=~0xf8;
	DataPort2 |= dofly_WeiMa[3];
	DataPort=0x48; 
	delay_ms(5);	
	
  DataPort2 &=~0xf8;
	DataPort2 |= dofly_WeiMa[2];
	DataPort=TempData[2]; 
	delay_ms(5);

	DataPort2 &=~0xf8;
	DataPort2 |= dofly_WeiMa[1];
	DataPort=TempData[1]; 
	delay_ms(5);
 
	DataPort2 &=~0xf8;
	DataPort2 |= dofly_WeiMa[0];
	DataPort=TempData[0]; 
	delay_ms(5);
	
	DataPort2 &=~0xf8;
	DataPort2 |= dofly_WeiMa[4];
	DataPort=0x3E; 
	delay_ms(5);
}
/*-------------------------------------------
  bai=adv/100;		//分出百，十，和个位
	shi=adv/10-10*bai;
	ge=adv/1-100*bai-10*shi;
  TempData[2]=dofly_DuanMa[bai]; //十位温度
  TempData[3]=dofly_DuanMa[shi]|0x80; //个位温度,带小数点
  TempData[4]=dofly_DuanMa[ge];
--------------------------------------------------*/
/*------------------------------------------------
 显示函数，用于动态扫描数码管
 输入参数 FirstBit 表示需要显示的第一位，如赋值2表示从第三个数码管开始显示
 如输入0表示从第一个显示。
 Num表示需要显示的位数，如需要显示99两位数值则该值输入2
------------------------------------------------*/
//   bai=adv/100;
//	shi=adv/10-10*bai;
//	ge=adv/1-100*bai-10*shi;
//	TempData[0]=0x3E;
//   TempData[2]=dofly_DuanMa[bai]|0x80; //十位温度
//   TempData[3]=dofly_DuanMa[shi]; //个位温度,带小数点
//   TempData[4]=dofly_DuanMa[ge];
//	Display(0,3);