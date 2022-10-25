#include <reg52.h>	

typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;

sbit led=P2^0;	 //定义P20口是led


void InitTimer0(void)
{
    TMOD = 0x01;
	TH0=0XFC;	//给定时器赋初值，定时1ms
	TL0=0X66;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

void main(void)
{
    InitTimer0();
	while(1);
}

void Timer0Interrupt(void) interrupt 1
{
	static u16 i;
	TH0=0XFC;	//给定时器赋初值，定时1ms
	TL0=0X66;//默认使用11.0592MHz晶振
	i++;
	if(i==500)
	{
		i=0;
		led=~led;	
	}	
}
