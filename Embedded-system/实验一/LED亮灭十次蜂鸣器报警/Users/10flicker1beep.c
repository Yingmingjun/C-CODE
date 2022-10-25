#include<reg52.h>
#include<intrins.h>

typedef unsigned int u16;
typedef unsigned char u8;
#define led P2

sbit beep=P1^5;	
sbit k4=P3^3;  

void delay(u16 i)
{
	while(i--);
}

void Int1Init()
{
	//设置INT1
	IT1=1;//跳变沿出发方式（下降沿）
	EX1=1;//打开INT1的中断允许。	
	EA=1;//打开总中断	
}

void main()
{	
	k4=0;
	Int1Init();  //	设置外部中断1
	
	
}
void Int1()	interrupt 2		//外部中断1的中断函数
{
	delay(1000);
	if(k4==0)
	{
		int n=0;
		for(n=0;n<10;n++)
		{
			led=0xff;
			delay(50000);
			led=0x00;
			delay(50000);
		}	
	}		
	while(1)
	{	
		beep=~beep;
		delay(10);
	}
	
}
