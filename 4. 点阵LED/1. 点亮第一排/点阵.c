#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;
sbit LED = P0^0;

void main()
{
	//74HC138 U4
	ENLED = 0;
	ADDR3 = 0;
	
	//导通LEDC0
	ADDR2 = 0;
	ADDR1 = 0;
	ADDR0 = 0;
	
	//点亮第一排小灯
	P0 = 0x00;
	
	//点亮第一个小灯
	//LED = 0;
	while (1)
	{
		
	}
}