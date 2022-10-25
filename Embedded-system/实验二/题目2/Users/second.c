#include<reg52.h>
typedef unsigned char u8;
typedef unsigned int u16;
u16 count=0;

sbit k3=P3^2;
sbit k4=P3^3;
sbit beep=P1^5;	
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u16 code smgduan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//显示0~9的值

void delay(u16 i)
{
	while(i--);
}


void IntInit()
{
	IT0=1;//下降沿触发
	EX0=1;//打开INT0的中断允许
	EA=1;//打开总中断	
}

void DigDisplay()
{
	u8 i;
	for(i=0;i<8;i++)
	{
		switch(i)	 //位选，选择点亮的数码管，
		{
		   case(0):
				LSA=1;LSB=1;LSC=1;  P0=0x00;break;//显示第0位
			case(1):
				LSA=0;LSB=1;LSC=1;  P0=0x00;break;//显示第1位
			case(2):
				LSA=1;LSB=0;LSC=1;  P0=0x00;break;//显示第2位
			case(3):	
				LSA=0;LSB=0;LSC=1;  P0=0x00;break;//显示第3位
			case(4):
				LSA=1;LSB=1;LSC=0;  P0=0x00;break;//显示第4位
			case(5):
				LSA=0;LSB=1;LSC=0;  P0=0x00;break;//显示第5位
			case(6):
				LSA=1;LSB=0;LSC=0;  P0=0x00;break;//显示第6位
			case(7):
				LSA=0;LSB=0;LSC=0;  P0=smgduan[count];break;//显示第7位	
		}
		delay(100); //间隔一段时间扫描	
		P0=0x00;//消隐
	}
}
void main()
{
	IntInit();
	while(1)
	{
		DigDisplay();
	}
}



void Int0()	interrupt 0		//外部中断0的中断函数
{
	if(k3==0)
	{
		delay(1000);
			while(!k3);
			count++;
		
	}
	
	if(count>=9)
	{
		while(1)
		{	
		
			beep=~beep;
			delay(10);
		}
	}
}


