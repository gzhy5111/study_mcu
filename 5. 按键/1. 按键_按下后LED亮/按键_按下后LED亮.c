/*!
 * KeyOut除自己低电平，其他Out是高电平。
 * 读取KeyIn，若是低电平代表按下，高电平代表弹起。
 */

#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

//键盘按下是低电平
sbit KEY4 = P2^7;

void main()
{
	ENLED = 0;
	ADDR3 = 1;
	
	ADDR2 = 1;
	ADDR1 = 1;
	ADDR0 = 0;
	
	P2 = 0xF7;					//1111 0111 KeyOut1 = 1, 读取KeyIn4，若KeyIn4 = 0则为按下，为1是弹起
	
	while (1)
	{
		P0 = 0xFF;
		if (KEY4 == 0)		//按下
		{
			P0 = 0xFE;
		}
		else
		{
			P0 = 0xFF;
		}	
	}
	
}