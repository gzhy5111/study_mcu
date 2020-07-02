#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code image[] = 
{
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xC3,0xE7,0xE7,0xE7,0xE7,0xE7,0xC3,0xFF,
	0x99,0x00,0x00,0x00,0x81,0xC3,0xE7,0xFF,
	0x99,0x99,0x99,0x99,0x99,0x81,0xC3,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
};

void main()
{
	//开启U4使能
	ADDR3 = 0;
	ENLED = 0;
	
	//开启中断
	EA = 1;
	ET0 = 1;
	
	//计时器
	TR0 = 1;
	TMOD = 0x01;
	TH0 = (65536-1000)/256;
	TL0 = (65536-1000)%256;
	
	while(1);
}

static unsigned char index = 0;
static unsigned char tmr = 0;

void InterruptTimer0() interrupt 1
{
	static unsigned char i = 0;			//!!不要忘记 static修饰i 为全局变量。
	TH0 = (65536-1000)/256;
	TL0 = (65536-1000)%256;
	

	
	P0 = 0xFF;
	switch(i)
	{
		case 0: ADDR2=0; ADDR1=0; ADDR0=0; P0=image[index+0]; i++; break;
		case 1: ADDR2=0; ADDR1=0; ADDR0=1; P0=image[index+1]; i++; break;
		case 2: ADDR2=0; ADDR1=1; ADDR0=0; P0=image[index+2]; i++; break;
		case 3: ADDR2=0; ADDR1=1; ADDR0=1; P0=image[index+3]; i++; break;
		case 4: ADDR2=1; ADDR1=0; ADDR0=0; P0=image[index+4]; i++; break;
		case 5: ADDR2=1; ADDR1=0; ADDR0=1; P0=image[index+5]; i++; break;
		case 6: ADDR2=1; ADDR1=1; ADDR0=0; P0=image[index+6]; i++; break;
		case 7: ADDR2=1; ADDR1=1; ADDR0=1; P0=image[index+7]; i=0; break;
		default: break;
	}
	
	tmr++;
	if (tmr >= 250)
	{
		index++;
		tmr = 0;
		if (index >= 32)
		{
			index = 0;
		}
	}
	
}