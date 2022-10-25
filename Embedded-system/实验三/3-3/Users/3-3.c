//编写程序，使用开发板实现以下功能：
//1、	使用定时器0的方式0，实现8个LED以0.5s间隔闪烁
//2、	使用定时器1的方式1，实现数码管前两位59s循环计时；
//注意：数码管的驱动方式请查看附带PPT自行设计；

#include "reg52.h"

typedef unsigned int u16;
typedef unsigned char u8;

u16 code smgduan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//显示0~9的值
u16 count1=0,count2=0,n=60,S=0,G=0;

sbit led0 = P2^0;
sbit led1 = P2^1;
sbit led5 = P2^5;
sbit led6 = P2^6;
sbit led7 = P2^7;
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

void delay(u16 n)
{
	u16 a=0,b=0;
	for(a=0;a<n;a++)
	{
		for(b=0;b<110;b++);
	}
}

void Timer0Init(void)		//100us@11.0592MHz
{
	EA = 1;			//打开总中断
	TMOD = 0x10;	//设置定时器0方式0,	定时器1方式1
	TL0 = 0xA4;		
	TH0 = 0x1F;		//设置定时初值100us
	ET0 = 1;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	
} 

void Timer1Init(void)		//1ms@11.0592MHz
{
	EA = 1;			//打开总中断
	TL1 = 0x66;		
	TH1 = 0xFC;		//设置定时初值1ms
	ET1 = 1;		//清除TF0标志
	TR1 = 1;		//定时器0开始计时
} 

void Timer0Interrupt() interrupt 1
{
	TL0 = 0xA4;		
	TH0 = 0x1F;		//设置定时初值100us
	count1++;
	if(count1>=50)
	{
			count1 = 0;
			led0=~led0;
			led1=~led1;
			led5=~led5;
			led6=~led6;
			led7=~led7;
	}
}

void Timer1Interrupt() interrupt 3
{
	TL1 = 0x66;		
	TH1 = 0xFC;		//设置定时初值1ms
	count2++;
	if(count2>=1000)
		{
			count2 = 0;
			n--;
			S = n/10;
			G = n%10;
			if(n<=0)
			{
				n=60;
			}

		}	
}


void DigDisplay()
{
	u8 i;
	for(i=0;i<2;i++)
	{
		switch(i)	 //位选，选择点亮的数码管，
		{
		    case(0):
				LSA=1;LSB=1;LSC=1;  P0=smgduan[S];break;//显示第0位
			case(1):
				LSA=0;LSB=1;LSC=1;  P0=smgduan[G];break;//显示第1位
		}
		delay(1); //间隔一段时间扫描1ms		
		P0=0x00;//消隐
	}


}

void main(void)
{
	led0 = 0;
	led1 = 0;
	led5 = 0;
	led6 = 0;
	led7 = 0;
    Timer0Init();
	Timer1Init();
	while(1)
	{		
		DigDisplay();
	}
}