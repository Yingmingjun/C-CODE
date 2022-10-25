#include <reg51.h>
#include "lcd.h"
#include "ds1302.h"
typedef unsigned int u16;
typedef unsigned char u8;	
sbit beep=P1^5;	  
sbit K1=P3^1;
sbit K2=P3^0;
sbit K3=P3^2;
sbit K4=P3^3;
//void delay(u16 i);
void Int0Configuration();
void LcdDisplay();
void read_time();
//unsigned char SetState,SetPlace;
//void Delay10ms(void);   //误差 0us
u8 m=0;
u16 a=0;
u8 readtime[14];
u8 sec_buf=0;
u8 sec_flag=0;

//void delay(u16 i)
//{
//	while(i--);	
//}
void Delay10ms()		//@11.0592MHz
{
	unsigned char i, j;
	i = 18;
	j = 235;
	do
	{
		while (--j);
	} while (--i);
}

void Send_char(u8 T)
{
	SBUF = T;
	while(!TI);	
	TI=0;
}

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
//	unsigned char i;
	Int0Configuration();
	LcdInit();
	Ds1302Init();
	UsartInit();  		//串口初始化
	while(1)
	{	
		read_time();
		LcdDisplay();
		if(readtime[13]!=sec_buf)
		{		
			
			EA=0;
			sec_flag=0;
			sec_buf=readtime[13];
			Send_char(2 +'0');//年
			Send_char(0 +'0');
			Send_char(readtime[2]+'0');
			Send_char(readtime[3]+'0');
			Send_char('/');
			Send_char(readtime[4]+'0');//月
			Send_char(readtime[5]+'0') ;
			Send_char('/');
			Send_char(readtime[6]+'0');//日
			Send_char(readtime[7]+'0');
			Send_char(' ');
			Send_char(readtime[8]+'0');//时
			Send_char(readtime[9]+'0');
			Send_char(':');
			Send_char(readtime [10]+'0');//分
			Send_char(readtime [11]+'0') ;
			Send_char(':');
			Send_char(readtime [12]+'0');//秒
			Send_char(readtime [13]+'0');
			Send_char('\n');
 			SBUF='\n';
			while(!TI); //等待发送完毕
			TI=0;//清中断
			EA=1;
		}
		Delay10ms();

	}
	
}


void LcdDisplay()
{
	LcdWriteCom(0x80+0X40);
	LcdWriteData('0'+TIME[2] /16);				//时
	LcdWriteData('0'+(TIME[2]&0x0f));				 
	LcdWriteData('-');
	LcdWriteData('0'+TIME[1]/16);				//分
	LcdWriteData('0'+(TIME[1]&0x0f));	
	LcdWriteData('-');
	LcdWriteData('0'+TIME[0]/16);				//秒
	LcdWriteData('0'+(TIME[0]&0x0f));

	LcdWriteCom(0x80);
	LcdWriteData('2');
	LcdWriteData('0');
	LcdWriteData('0'+TIME[6]/16);			//年
	LcdWriteData('0'+(TIME[6]&0x0f));
	LcdWriteData('-');
	LcdWriteData('0'+TIME[4]/16);			//月
	LcdWriteData('0'+(TIME[4]&0x0f));
	LcdWriteData('-');
	LcdWriteData('0'+TIME[3]/16);			//日
	LcdWriteData('0'+(TIME[3]&0x0f));
	LcdWriteCom(0x8D);
	LcdWriteData('0'+(TIME[5]&0x07));	//星期	

}

void Int0Configuration()
{
	//设置INT0
	IT0=1;//跳变沿出发方式（下降沿）
	EX0=1;//打开INT0的中断允许。
	EA=1;//打开总中断	
}



//void Delay10ms(void)   //误差 0us
//{
//    unsigned char a,b,c;
//    for(c=1;c>0;c--)
//        for(b=38;b>0;b--)
//            for(a=130;a>0;a--);
//}

void read_time()
{
	Ds1302ReadTime();
//	readtime [0]= (TIME[0]>>4); //分离出年千位
//	readtime [1]=(TIME[0]&0x0F);// 11分离出年百位
	readtime [2]=(TIME[6]>>4); //1分离出年十位
	readtime [3]= (TIME[6]&0x0F); //分离出年个位
	readtime [4]=(TIME[4]>>4); //1分离出月十位
	readtime [5]= (TIME[4]&0x0F); //分离出月个位
	readtime [6]=(TIME[3]>>4); //分离出日十位
	readtime [7]= (TIME[3]&0x0F); //分离出日个位
	readtime [8]=(TIME[2]>>4); //分离出小时十位
	readtime [9]= (TIME[2]&0x0F); //分离出小时个位
	readtime [10]=(TIME[1]>>4); //分离出分钟十位
	readtime [11]= (TIME[1]&0x0F); //分离出分钟个位
	readtime [12]=(TIME[0]>>4); //分离出秒钟十位
	readtime [13]= (TIME[0]&0x0F); //分离出秒钟个位
}
//void Usart() interrupt 4
//{
//	for(m=0;m<20;m++)
//	{
//	TIME[m] = SBUF;   //出去接收到的数据
//	RI = 0;				//清除接收中断标志位
//	SBUF=TIME[m];	//将接收到的数据放入到发送寄存器

//	}
//	while(!TI);			//等待发送数据完成
//	TI=0;				//清除发送完成标志位
//}