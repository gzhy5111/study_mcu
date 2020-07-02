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

void main()
{
	//backup是保存上次的值
	char backup = 1;		//一位，默认弹起
	unsigned char cnt = 0;
	
	ENLED = 0;
	ADDR3 = 1;
	
	ADDR2 = 0;
	ADDR1 = 0;
	ADDR0 = 0;
	
	P2 = 0xF7;	//1111 0111, KeyOut1 = 0, KeyIn1 = 1
	P0 = ledChar[cnt];
	

	while (1)
	{
		if (KEY4 != backup)		//不等于上次，则触发
		{
			if (backup == 0)
			{
				
				cnt++;
				
				//数码管显示0~9
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