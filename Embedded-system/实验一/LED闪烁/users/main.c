#include<reg52.h>
#include<intrins.h>	
typedef unsigned char u8;
typedef unsigned int u16;

#define led P2

void delay(u16 i)
{
	while(i--);
}

void main()
{
	while(1)
	{
		led=0xff;
		delay(50000);
		led=0x00;
		delay(50000);
	}
}