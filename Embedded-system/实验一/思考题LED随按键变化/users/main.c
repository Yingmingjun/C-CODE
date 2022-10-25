#include<reg52.h>
#include<intrins.h>	
#define led P2
int n=0;

typedef unsigned char u8;
typedef unsigned int u16;
u16 a,b;

sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;
sbit beep=P1^5;	

void delay(u16 i)
{
	while(i--);
}

void IntInit()
{
	//配置INT0
	IT0=0;
	EX0=1;//打开INT0的中断允许
	IT1=0;
	EX1=1;//打开INT1中断允许	
	EA=1;//打开总中断	
}

void main()
{
	IntInit();
	while(1)
	{
		led=0x00;

		if(n>4)
		{
			while(1)
			{	
				beep=~beep;
				delay(10);
			}
		}
		if(k1==0)
		{
			while(!k1);
			k3=0;
		}
		if(k2==0)
		{
			while(!k2);
			k4=0;
		}
	}	
}

void Int1()	interrupt 2		//外部中断1低优先级
{

		n++;	
		led=0xfe;
			for(a=0;a<8;a++)
			{
				P2=~(0x01<<a);	 
				delay(50000); 
			}
			k4=1;			
}

void Int0()	interrupt 0		//外部中断0的中断函数
{

		n++;
		led=0xfe;

			for(b=0;b<8;b++)
			{
				P2=~(0x80>>b);	 
				delay(50000); 
				if(k2==0)
				{
				for(a=0;a<8;a++)
				{
				P2=~(0x01<<a);	 
				delay(50000); 
				}
				}
			}
			k3=1;	
	

}


