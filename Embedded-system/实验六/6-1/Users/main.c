#include "reg52.h"		 

typedef unsigned int u16;
typedef unsigned char u8;
u8 receiveData;

void UsartInit()
{
			
	TMOD = 0x20;//设置计数器工作方式2
    SCON = 0x50;//设置为工作方式1
    TH1 = 0xFA;//计数器初始值设置，波特率4800
    TL1 = TH1;
    PCON = 0x00;//波特率不加倍
    EA = 1;//打开总中断
    ES = 1;//打开接收中断
    TR1 = 1;//打开计数器
}
	
	



void main()
{	
	UsartInit();  		//串口初始化
	while(1);		
}

void Usart() interrupt 4
{
	receiveData=SBUF;   //出去接收到的数据
	RI = 0;				//清除接收中断标志位
	SBUF=receiveData;	//将接收到的数据放入到发送寄存器
	while(!TI);			//等待发送数据完成
	TI=0;				//清除发送完成标志位
}


