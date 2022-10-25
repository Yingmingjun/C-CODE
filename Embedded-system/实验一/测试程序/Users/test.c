#include<reg52.h>
#include <intrins.h>	
#define led P2
int n=0;

typedef unsigned char u8;
typedef unsigned int u16;

u8 score=0;
sbit k1=P3^1;
sbit beep=P1^7;
void Delay1000ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 1;
	k = 243;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void delay(u16 i)
{
	while(i--);
}

void main()
{
	beep=0;
	delay(3000);
	beep=1;
Delay1000ms();
}




