#include <reg52.h>

unsigned long beats = 0;

void StartMotor(unsigned long angle);

void main()
{
	//中断
	EA = 1;									//开放总中断
	ET0 = 1;								//允许T0中断
	
	//定时器（因为点击启动刷新节拍要求时间>1.8ms，所以用定时器每2ms刷新一次节拍）
	TR0 = 1;								//允许TR0计时
	TMOD = 0x01;						
	TH0 = (65536-2000)/256;	//2ms
	TL0 = (65536-2000)%256;	
	
	StartMotor(360*2+180);	//转两圈半
	while(1);
}

void StartMotor(unsigned long angle)	//angle：角度
{
	//重要！因为angle类型，所以要在操作angle的时候开放/关闭中断
	EA = 0;
	beats = (angle*4076)/360;					//角度转为拍数
	EA = 1;
}

void interruptTimer0()	interrupt 1
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
		index = index & 0x07;
		beats--;
	}
	else	//beats为0，关闭
	{
		P1 = P1 | 0x0F;
	}
}