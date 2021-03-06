#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code ledChar[] = {	//不能改写且存在ROM中
	0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 
	0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
};

void main()
{
	unsigned char cnt = 0;
	unsigned char sec = 0;
	ENLED = 0;
	ADDR3 = 1;
	ADDR2 = 0;
	ADDR1 = 0;
	ADDR0 = 0;
	
	TMOD = 0x01;
	// 定时器
	TH0 = 0xB8;
	TL0 = 0x00;
	// 定时器0运行控制位，等于1表示打开定时器
	TR0 = 1;
	while(1)
	{
		// TF等于1说明溢出，说明定时器到时间了。
		if (TF0 == 1)
		{
			TF0 = 0;
			TH0 = 0xB8;
			TL0 = 0x00;
			cnt++;
			// 0.02秒乘以50等于1秒。转为1s。
			if (cnt>=50)
			{
				cnt = 0;
				P0 = ledChar[sec];
				
				sec++;
				if (sec >= 16)
				{
					sec = 0;
				}
				
			}
		}
	}
}