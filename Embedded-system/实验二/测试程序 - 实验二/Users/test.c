/*/////////////////题目三//////////////////////////////////////////////////////////////////////////////////////////////
编写程序，使用两级中断，使用开发板实现以下功能： 
1、	电路正常工作，，两个LED 同时点亮；
2、	若K3先按下，，LED1熄灭，LED0闪烁10次；
3、	若在LED0闪烁期间按下K4，则LED0熄灭，LED1闪烁10次熄灭，LED0再次闪烁
4、	若K4先按下，，则LED1闪烁10次后熄灭，若在LED1闪烁期间K3按下,
	不能打断LED1的闪烁，等LED1闪烁结束后LED0闪烁10次。
5、	闪烁结束后，恢复正常工作（即两灯同时点亮的状态）。
*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include<reg52.h>
#include<intrins.h>
typedef unsigned char u8;
typedef unsigned int u16;
u16 i,j;
sbit led0=P2^0;
sbit led1=P2^7;
sbit k3=P3^2;
sbit k4=P3^3;

void delay(u16 i)
{
	while(i--);
}

void IntInit0()
{	

	//配置外部中断
	IT0=1;//下降沿
	EX0=1;//打开INT0的中断允许
}

void IntInit1()
{
	IT1=1;//下降沿激发
	EX1=1;//打开INT1中断允许	
}

void main()
{
	IP=0x04;//设置INT1的优先级为最高
	EA=1;//打开总中断	
	IntInit0();
	IntInit1();
	led0=0;
	led1=0;
	while(1);
}

void Int0()	interrupt 0		//外部中断0的中断函数
{
	if(k3==0)
	{
		delay(1000);//延时消抖
		while(!k3);
		led1=1;

		for(j=0;j<20;j++)
		{
			led0=~led0;
			delay(30000);
		}
		led1=0;
		led0=0;	
	}
}

void Int1()	interrupt 2		//外部中断1低优先级
{
    int K_3=0;
	if(k4==0)
	{
		delay(1000);//延时消抖
		while(!k4);
		led0=1;
		for(i=0;i<20;i++)
		{
		    if(k3==1)
            {
                K_3=1;
            }
			led1=~led1;
			delay(30000);
		}
		led0=0;
		led1=0;
		if(K_3==0)
        {
            led1=1;

		for(j=0;j<20;j++)
		{
			led0=~led0;
			delay(30000);
		}
		led1=0;
		led0=0;;
        }
	}
}




