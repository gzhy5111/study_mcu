/*！
 * 功能：点亮LED2小灯
 *
*/

#include <reg52.h>

//注意端口P是大写的
sbit LED =P0^0;

//通过74HC138打开总闸门
sbit ADDR0 = P1^0;	//ADDR0接P1^0引脚
sbit ADDR1 = P1^1;	//同上理
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;


void main()
{
		ENLED = 0;
		ADDR3 = 1;
		
		// LEDS6输出低电平
		ADDR2 = 1;
		ADDR1 = 1;
		ADDR0 = 0;
		
		LED = 0;	//使LED亮
		// 使程序停止在这里
		while (1);
}