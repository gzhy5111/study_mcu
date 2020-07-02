#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code ledChar[] = 
{
	0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 
	0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
};

unsigned char ledBuff[6] = 
{
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};



unsigned int cnt = 0;
unsigned char flag = 0;
unsigned long i = 0;

void main()
{
	
	unsigned long sec = 0;
	char j = 0; //！！主要不要写成 unsigned 类型
	unsigned char buf[6];

	//开启74HC138使能
	ADDR3 = 1;
	ENLED = 0;
	
	//定时1毫秒
	TMOD = 0x01;
	TH0 = (65536-1000)/256;
	TL0 = (65536-1000)%256;
	TR0 = 1;
	
	//开启中断
	EA = 1;
	ET0 = 1;
	
	while(1)
	{
		//定时一秒钟（一秒钟到了）
		if (flag == 1)
		{
			flag = 0;
			sec++; //单位秒
			buf[0] = sec%10;
			buf[1] = sec/10%10;
			buf[2] = sec/100%10;
			buf[3] = sec/1000%10;
			buf[4] = sec/10000%10;
			buf[5] = sec/100000%10;
			for (j=5; j >= 0; j--)
			{
				if (buf[j] == 0)		//==0
				{
					ledBuff[j] = 0xFF;		//高位是0则不显示
				}
				else
				{
					break;
				}
			}	
			for (; j >= 0; j--)
			{
				ledBuff[j] = ledChar[buf[j]];
			}
		}
	}
}

void InterruptTimer0() interrupt 1
{

	
	TH0 = (65536-1000)/256;
	TL0 = (65536-1000)%256;
	cnt++;
	if (cnt >= 1000)
	{
		cnt = 0;
		flag = 1;
	}
	
	//1ms刷新一次
	P0 = 0xFF;
	switch(i)
	{
		case 0: ADDR2 = 0; ADDR1 = 0; ADDR0 = 0; i++; P0 = ledBuff[0]; break;
		case 1: ADDR2 = 0; ADDR1 = 0; ADDR0 = 1; i++; P0 = ledBuff[1]; break;
		case 2: ADDR2 = 0; ADDR1 = 1; ADDR0 = 0; i++; P0 = ledBuff[2]; break;
		case 3: ADDR2 = 0; ADDR1 = 1; ADDR0 = 1; i++; P0 = ledBuff[3]; break;
		case 4: ADDR2 = 1; ADDR1 = 0; ADDR0 = 0; i++; P0 = ledBuff[4]; break;
		case 5: ADDR2 = 1; ADDR1 = 0; ADDR0 = 1; i=0; P0 = ledBuff[5]; break;
	}
}