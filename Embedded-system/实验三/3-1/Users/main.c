#include <reg52.h>
#define uchar unsigned char
	
sbit p1=P1^0;
uchar  a = 0;

//void int1() interrupt 1
//{
//	a%=10;
//	if(a<2)
//	{
//		p1=1;
//	}
//	else 
//	{
//		p1=0;
//	}
//	a++;
//}

void int1() interrupt 1
{
	a++;
	if(a==80)
	{
		p1=1;
	}
	if(a==100)
	{
		P1=0;
		a=0;
	}

}

void main()
{
	TMOD=0x02; //设置T0为方式2
	TH0=216;
	TL0=216; //每次40微秒
	TR0=1; //启动T0定时器
	ET0=1; //允许外部中断0中断
	EA=1; //总中断允许
	while(1);
}