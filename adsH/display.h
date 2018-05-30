void display(float adv)  //显示子函数
{
	uchar bai,shi,ge;
	bai=adv/100;		//分出百，十，和个位
	shi=adv/10-10*bai;
	ge=adv/1-100*bai-10*shi;
	dula=1;
	P0=table[bai];    //送段选数据
	dula=0;
	P0=0xff;		//送位选数据前关闭所有显示，防止打开位选锁存时
	wela=1;			//原来段选数据通过位选锁存器造成混乱
	P0=0xdf;		//送位选数据
	wela=0;
	delayms(5);	    //延时
	dula=1;
	P0=seg[shi];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xbf;
	wela=0;
	delayms(5);
	dula=1;
	P0=table[ge];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0x7f;
	wela=0;
	delayms(5);
}