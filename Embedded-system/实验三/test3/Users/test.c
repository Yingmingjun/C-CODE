#include "reg52.h"
typedef unsigned int u16;
typedef unsigned char u8;
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u8 code seg[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
u8 code dig[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d};

#define led P2
 u16 i=0,m=0,g=0,s=0;

void delay(u16 t)
{
	while(t)
		t--;
}

void display()
{
	u16 n=6;
	for(;n<8;n++)
	{
		switch (n)
		{
			case 6:
				LSA=0;LSB=1;LSC=1;P0=seg[g];break;
			case 7:
				LSA=1;LSB=1;LSC=1;P0=dig[s]; break;
		}
		delay(100);
		P0=0x00;
	}
}


void main()
{
 TMOD=0x10;
 TL0=0x78;
	TH0=0x0c;
	TL1=0x78;
	TH1=0xec;
	ET1=1;
 ET0=1;
 EA=1;
 //TR0=1;
	TR1=1;

 while(1) display();
}

/*void timer0() interrupt 1
{

 TL0=0x78;
	TH0=0x0c;
i++;

if(i>=100)
{
	P2=~P2;
	i=0;
	TL0=0x78;
	TH0=0x0c;
}
else
{
TL0=0x78;
	TH0=0x0c;
}
}*/
void timer1() interrupt 3
{

 TL1=0x00;
	TH1=0xee;
  m++;

if(m>=200)
{
	g++;
	 if(g>=10)
	{
		s++;
		g=0;
		if(s>=6)
			s=0;
	}
	m=0;
	TL1=0x00;
	TH1=0xee;
}
else
{
 TL1=0x00;
	TH1=0xee;
}
}