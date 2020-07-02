#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;
sbit KEY4 = P2^7;

unsigned char code ledChar[] = {
	0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 
	0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
};

bit KeySta = 1;

void main()
{
	bit backup = 1;
	unsigned char cnt = 0;
	
	//开启U3使能
	ENLED = 0;
	ADDR3 = 1;
	
	//LEDS0低电平
	ADDR2 = 0;
	ADDR1 = 0;
	ADDR0 = 0;
	
	//定时器
	TH0 = (65536-2000)/256;
	TL0 = (65536-2000)%256;
	TR0 = 1;
	TMOD = 0x01;
	
	//中断
	EA = 1;
	ET0 = 1;
	
	#pragma ASM
		CLR	0xA0.3
	#pragma ENDASM
	
	P0 = ledChar[cnt];

	
	while(1)
	{
		if (KeySta != backup)
		{
			if (backup == 0)
			{
				cnt++;
				if (cnt >= 10)
				{
					cnt = 0;
				}
				P0 = ledChar[cnt];
			}
			backup = KeySta;
		}
	}
}

//中断的目的：检测按键状态（是否被按下）
void InterruptTimer0()	interrupt 1
{
	static unsigned char keybuf = 0xFF;
	
	TH0 = (65536-2000)/256;
	TL0 = (65536-2000)%256;
	
	//进入一次中断就移位一次
	keybuf = (keybuf << 1)|KEY4;
	
	if (keybuf == 0x00)		//连续八次都是0
	{
		KeySta = 0;
	}
	else if (keybuf == 0xFF)
	{
		KeySta = 1;
	}
	else
	{
	}
}