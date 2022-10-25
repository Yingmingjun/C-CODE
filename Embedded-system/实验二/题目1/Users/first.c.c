#include<reg52.h>
#include<intrins.h>	
#define led P2


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
	IT0=1;//下降沿
	EX0=1;//打开INT0的中断允许
	IT1=1;//下降沿激发
	EX1=1;//打开INT1中断允许	
	EA=1;//打开总中断	
}

void main()
{
	IntInit();
	while(1)
	{
		led=0x00;
		delay(50000);//LED八盏灯常亮
	}	
}

void Int1()	interrupt 2		//外部中断1低优先级
{
	delay(1000);//延时消抖
		led=0xfe;

			for(a=0;a<8;a++)
			{
				P2=~(0x01<<a);	 
				delay(50000); 
			}		

	
}
	

void Int0()	interrupt 0		//外部中断0的中断函数
{
	delay(1000);//延时消抖
		led=0xfe;

			for(b=0;b<8;b++)
			{
				P2=~(0x80>>b);	 
				delay(50000); 
			}	
	
}


