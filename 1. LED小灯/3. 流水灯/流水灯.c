#include <reg52.h>

//接线
sbit LED = P0^0;
sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

int main(void)
{
	unsigned int cnt = 0;
	int i = 0;
	
	//LEDS0输出低电平，开启LED总开关
	ADDR0 = 0;
	ADDR1 = 1;
	ADDR2 = 1;
	ENLED = 0;
	ADDR3 = 1;
	
	/*
	// 右边第一个小灯亮
	P0 = 0xFE;		// 0b1111_1110
	while (1);
	*/
	/*
	P0 = 0xFE << 1;
	while (1);
	*/
	
	//流水灯
	
	while(1)
	{
		P0 = ~((~0xFE) << cnt);			// 先取反再左移，再取反
		// 延时
		for (i = 0; i<10000; i++);
		
		cnt++;
		// 记满8归0
		if (cnt >= 8)
		{
			cnt = 0;
		}
	}
	
}