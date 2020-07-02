#include <reg52.h>

//将BeatCode数组中的值循环送入，即可让步进电机转动
unsigned char code BeatCode[8] = 
{
	0x0E, 0x0C, 0x0D, 0x09, 0x0B, 0x03, 0x07, 0x06
	//	0000 1110, 
	//	0000 1100, 
	//	0000 1101, 
	//	0000 1001,
	//	0000 1011, 
	//	0000 0011, 
	//	0000 0110, 
};

void delay()
{
	unsigned char i = 200;
	while (i--);
}

void main()
{
	unsigned char tmp;
	unsigned char index = 0;
	
	while(1)
	{
											//良好习惯：控制低四位的时候不能影响高四位
		tmp = P1;					//所以，取P1口现在的电平并赋值给tmp
		tmp = tmp&0xF0; 	//低四位清零
		tmp = tmp|BeatCode[index];
		P1 = tmp;
		index++;
		
		index = index&0x07;		//加到8归零
		delay();
	}
}