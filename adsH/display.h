void display(float adv)  //��ʾ�Ӻ���
{
	uchar bai,shi,ge;
	bai=adv/100;		//�ֳ��٣�ʮ���͸�λ
	shi=adv/10-10*bai;
	ge=adv/1-100*bai-10*shi;
	dula=1;
	P0=table[bai];    //�Ͷ�ѡ����
	dula=0;
	P0=0xff;		//��λѡ����ǰ�ر�������ʾ����ֹ��λѡ����ʱ
	wela=1;			//ԭ����ѡ����ͨ��λѡ��������ɻ���
	P0=0xdf;		//��λѡ����
	wela=0;
	delayms(5);	    //��ʱ
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