#define DataPort P2 //�������ݶ˿� ����������DataPort ����P0 �滻
#define DataPort2 P3
unsigned char TempData[8]; //�洢��ʾֵ��ȫ�ֱ���

unsigned char code dofly_DuanMa[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};// ��ʾ����ֵ0~9
unsigned char code dofly_WeiMa[]={0x80,0x40,0x20,0x10,0x08};//�ֱ��Ӧ��Ӧ������ܵ���,��λ��

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
  bai=adv/100;		//�ֳ��٣�ʮ���͸�λ
	shi=adv/10-10*bai;
	ge=adv/1-100*bai-10*shi;
  TempData[2]=dofly_DuanMa[bai]; //ʮλ�¶�
  TempData[3]=dofly_DuanMa[shi]|0x80; //��λ�¶�,��С����
  TempData[4]=dofly_DuanMa[ge];
--------------------------------------------------*/
/*------------------------------------------------
 ��ʾ���������ڶ�̬ɨ�������
 ������� FirstBit ��ʾ��Ҫ��ʾ�ĵ�һλ���縳ֵ2��ʾ�ӵ���������ܿ�ʼ��ʾ
 ������0��ʾ�ӵ�һ����ʾ��
 Num��ʾ��Ҫ��ʾ��λ��������Ҫ��ʾ99��λ��ֵ���ֵ����2
------------------------------------------------*/
//   bai=adv/100;
//	shi=adv/10-10*bai;
//	ge=adv/1-100*bai-10*shi;
//	TempData[0]=0x3E;
//   TempData[2]=dofly_DuanMa[bai]|0x80; //ʮλ�¶�
//   TempData[3]=dofly_DuanMa[shi]; //��λ�¶�,��С����
//   TempData[4]=dofly_DuanMa[ge];
//	Display(0,3);