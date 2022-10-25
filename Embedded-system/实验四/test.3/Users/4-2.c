#include "reg52.h"
#include "lcd.h"

typedef unsigned int u16;	 //对数据类型进行声明定义
typedef unsigned char u8;
u16 count=0;
u16 second;
u16 minute;
u16 hour;
u8 code date[]="CHINA TIME";
u8 code time[]="NOW 23:59:55";

void Timer1Init(void)		//1ms@11.0592MHz
{

	TMOD = 0x10;	//设置定时器1-方式1
	EA = 1;			//打开总中断
	TL1 = 0x66;		
	TH1 = 0xFC;		//设置定时初值1ms
	ET1 = 1;		//清除TF0标志
	TR1 = 1;		//定时器1中断计时
} 

void clock_init()
{
	u8 i,j;
	for(i=0;i<10;i++)
	{
		LcdWriteData(date[i]);
	}
	LcdWriteCom(0x80+0x40);
	for(j=0;j<12;j++)
	{
		LcdWriteData(time[j]);
	}	
}

void write_sfm(u8 add,u16 dat)
{
	u8 shi,ge;
	shi = dat/10;
	ge = dat%10;
	LcdWriteCom(0x80+0x40+add);
	LcdWriteData(shi+0x30);
	LcdWriteData(ge+0x30);	
}

void clock_write(u16 s,u16 m,u16 h)
{
	write_sfm(4,h);
	write_sfm(7,m);
	write_sfm(10,s);
}

void main(void)
{	
	LcdInit();
	Timer1Init();
	clock_init();

	second=55;
	minute=59;
	hour=23;
	while(1)
	{
		clock_write(second,minute,hour);
	}				
}

void Timer1Interrupt() interrupt 3
{
	TL1 = 0x66;		
	TH1 = 0xFC;	//设置定时初值1ms
	count++;
	if(count>=1000)
	{
		count=0;
		second++;
	}
	if(second>=60)
	{
		second=0;
		minute++;
	}
	if(minute>=60)
	{
		minute=0;
		hour++;
	}
	if(hour>=24)
	{
		hour=0;
	}
}