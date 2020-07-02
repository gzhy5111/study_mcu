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

void delay()
{
	unsigned int i = 1000;
	while (i--);
}

void main()
{
	bit backup = 1;
	unsigned char cnt = 0;
	bit keybuf = 1;
	
	ENLED = 0;
	ADDR3 = 1;
	
	ADDR2 = 0;
	ADDR1 = 0;
	ADDR0 = 0;
	
	//先给高电平
	P2 = 0xF7;	//1111 0111 , KeyIn1为1
	
	P0 = ledChar[0];
	
	while(1)
	{
		keybuf = KEY4;
		if (keybuf != backup)
		{
			// 最简单的消抖原理，给一个10ms左右的延时时间
			delay();
			if (keybuf == KEY4)
			{
				if (backup ==0)
				{
					cnt++;
					if (cnt >= 10)
					{
						cnt = 0;
					}
					P0 = ledChar[cnt];
				}
				backup = KEY4;
			}
		}
	}
}

