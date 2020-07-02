/*
 * 时间：2019年11月26日 21:35:13
 * 使用中断解决数码管回影问题
 * 使用知识点：计时器、中断
 */

#include <reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code ledChar[] = {
	0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 
	0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
};

unsigned char ledBuff[6] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

unsigned char i = 0;
unsigned int cnt = 0;

void main()
{
	//sec：当前秒
	unsigned long sec = 0;
	ADDR3 = 1;
	ENLED = 0;
	
	//计时器功能选择
	TMOD = 0x01;
	
	//定时1ms
	TH0 = 0xFC;
	TL0 = 0x67;
	TR0 = 1;
	
	//打开中断
	EA = 1;
	ET0 = 1;
	
	while(1)
	{
		//一秒钟取值存入buff
		if (cnt >= 1000)
		{
			cnt = 0;
			sec++;
			ledBuff[0] = ledChar[sec%10];		//显示个位
			ledBuff[1] = ledChar[sec/10%10];
			ledBuff[2] = ledChar[sec/100%10];
			ledBuff[3] = ledChar[sec/1000%10];
			ledBuff[4] = ledChar[sec/10000%10];
			ledBuff[5] = ledChar[sec/100000%10];
		}
	}
	
}

//中断函数是自动调用的；中断的条件就是计时器溢出
void InterruptTimer0()	interrupt 1  //通过 x（中断数） * 3 + 8 = 11 计算；表示定时器0中断函数
{
	//当计时器溢出后，重装计时器
	TH0 = 0xFC;
	TL0 = 0x67;
	
	cnt++;
	//每个case执行后，将数码管显示“0”
	P0 = 0xFF;
	switch (i)
	{
		case 0: ADDR2 = 0; ADDR1 = 0; ADDR0 = 0; i++; P0 = ledBuff[0]; break;
		case 1: ADDR2 = 0; ADDR1 = 0; ADDR0 = 1; i++; P0 = ledBuff[1]; break;
		case 2: ADDR2 = 0; ADDR1 = 1; ADDR0 = 0; i++; P0 = ledBuff[2]; break;
		case 3: ADDR2 = 0; ADDR1 = 1; ADDR0 = 1; i++; P0 = ledBuff[3]; break;
		case 4: ADDR2 = 1; ADDR1 = 0; ADDR0 = 0; i++; P0 = ledBuff[4]; break;
		case 5: ADDR2 = 1; ADDR1 = 0; ADDR0 = 1; i=0; P0 = ledBuff[5]; break;
		default: break;
	}
}