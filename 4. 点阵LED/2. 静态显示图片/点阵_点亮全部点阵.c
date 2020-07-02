/*!
 * 知识点：中断、计时器
 */

#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

void main()
{
	//开启U4使能
	ENLED = 0;
	ADDR3 = 0;
	
	//打开中断
	EA = 1;
	ET0 = 1;
	
	//计时器
	TMOD = 0x01;
	TR0 = 1;
	
	//定时1ms
	TH0 = (65536-1000)/256;
	TL0 = (65536-1000)%256;
	while(1);
}

void InterruptTimer0() interrupt 1
{
	static unsigned char i = 0;
	TH0 = (65536-1000)/256;
	TL0 = (65536-1000)%256;
	
	P0 = 0xFF;		//熄灭
	switch(i)
	{
		case 0: ADDR2=0; ADDR1=0; ADDR0=0; i++; P0=0xFF; break;
		case 1: ADDR2=0; ADDR1=0; ADDR0=1; i++; P0=0x99; break;
		case 2: ADDR2=0; ADDR1=1; ADDR0=0; i++; P0=0x00; break;
		case 3: ADDR2=0; ADDR1=1; ADDR0=1; i++; P0=0x00; break;
		case 4: ADDR2=1; ADDR1=0; ADDR0=0; i++; P0=0x00; break;
		case 5: ADDR2=1; ADDR1=0; ADDR0=1; i++; P0=0x81; break;
		case 6: ADDR2=1; ADDR1=1; ADDR0=0; i++; P0=0xC3; break;
		case 7: ADDR2=1; ADDR1=1; ADDR0=1; i=0; P0=0xE7; break;
		default: break;
	}
}