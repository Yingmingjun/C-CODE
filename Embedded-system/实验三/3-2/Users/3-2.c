#include "reg52.h"

typedef unsigned int u16;
typedef unsigned char u8;

u16 count1=0,count2=0;
sbit led0 = P2^0;
sbit led1 = P2^1;
sbit led2 = P2^2;
sbit led3 = P2^3;
sbit led4 = P2^4;
sbit led5 = P2^5;
sbit led6 = P2^6;
sbit led7 = P2^7;


void InitTimer0(void)
{
    TMOD = 0x03;//方式三，仅适用于T0，此时T0分解为两个八位计数器，T1停止计数
    TH0 = 0xD1;///50us
    TL0 = 0xA3;//100us
    EA = 1;
    ET0 = 1;
	ET1 = 1;
    TR0 = 1;
	TR1 = 1;
}

void TL0_timer(void) interrupt 1
{
    TL0 = 0xA3;//100us
	count1++;
}

void TH0_timer(void) interrupt 3
{
    TH0 = 0xD1;///50us
	count2++;
}


void main(void)
{
			led0 = 0;
			led1 = 0;
			led2 = 0;
			led3 = 0;
			led4 = 0;
			led5 = 0;
			led6 = 0;
			led7 = 0;
	
	InitTimer0();
	while(1)
	{
		if(count1>=5000)
		{
			count1=0;
			led4 = ~led4;
			led5 = ~led5;
			led6 = ~led6;
			led7 = ~led7;	
		
		}
		if(count2>=5000)
		{
			count2=0;
			led0 = ~led0;
			led1 = ~led1;
			led2 = ~led2;
			led3 = ~led3;
		}
	}
}


