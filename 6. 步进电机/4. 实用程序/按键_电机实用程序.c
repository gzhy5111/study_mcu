#include <reg52.h>

unsigned long beats = 0;
void StartMotor(unsigned long angle);
void main()
{
	//�ж�
	EA = 1;
	ET0 = 1;
	
	//��ʱ������ʱ��2ms����ˢ�½��ģ���������ԣ�>1.8ms����������
	TH0 = (65536-2000)/256;
	TL0 = (65536-2000)%256;
	TMOD = 0x01;
	TR0 = 1;
	
	StartMotor(90);
	while(1);
}

void StartMotor(unsigned long angle)
{
	EA = 0;		//��Ϊangle��long�ͣ����Բ���֮ǰ�ر��ж�
	beats = (angle*4076)/360;
	EA = 1;
}

void InterruptTimer0() interrupt 1
{
	unsigned char tmp;
	static unsigned char index = 0;
	unsigned char code BeatCode[8] = {
		0x0E, 0x0C, 0x0D, 0x09, 0x0B, 0x03, 0x07, 0x06
	};
	TH0 = (65536-2000)/256;
	TL0 = (65536-2000)%256;	
	if (beats != 0)
	{
		tmp = P1;
		tmp = tmp & 0xF0;
		tmp = tmp | BeatCode[index];
		P1 = tmp;
		index++;
		index = index &0x07;
		beats--;
	}
	else
	{
		P1 = P1 |0x0F;
	}
}