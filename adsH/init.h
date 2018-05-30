void init()
{
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	TR0=1;
	ET0=1;
	EA=1;
	sda=1;
	delay();
	scl=1;
	delay();
}