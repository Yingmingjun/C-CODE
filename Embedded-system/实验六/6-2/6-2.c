#include <reg52.h>
#include <intrins.h>
 

#define GPIO_DIG P0
//使用138译码器接八个数码管
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
typedef unsigned int u16;
typedef unsigned char u8;
u8 receiveData;
u8 i=0;
u16 j=10;
//--定义全局变量--//
unsigned char code DIG_CODE[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
//0、1、2、3、4、5、6、7、8、9的显示码
unsigned char DisplayData[3];
//用来存放要显示的3位数的值

//--声明全局函数--//
void DigDisplay();         //动态显示函数           
void UsartConfiguration();
 
void main()
{
        UsartConfiguration();
		
        while(1)
        {
                DigDisplay();
        }
}

 
void UsartConfiguration()
{
    TMOD = 0x20;
    SCON = 0x50;
    TH1 = 0xF4;
    TL1 = 0xF4;
    PCON = 0x80;
    EA = 1;
    ES = 1;
    TR1 = 1; //打开计数器
}

void DigDisplay()
{


                switch(i)         //位选，选择点亮的数码管，
                {
                        case(0):
                                LSA=0;LSB=0;LSC=0;GPIO_DIG=0x40; //显示第0位个位
						case(1):
                                LSA=1;LSB=0;LSC=0;GPIO_DIG=DisplayData[i-1];//显示第1位十位
//						case(2):
//                                LSA=0;LSB=1;LSC=0; break;//显示第2位百位
                }
                j=10;                                                 //扫描间隔时间设定
                while(j--);        
                GPIO_DIG=0x00;//消隐
}



void Usart() interrupt 4
{
	receiveData=SBUF;   //出去接收到的数据
	RI = 0;				//清除接收中断标志位
	SBUF=receiveData;	//将接收到的数据放入到发送寄存器
	while(!TI);			//等待发送数据完成
    DisplayData[0] = DIG_CODE[(receiveData-'0')%10];//个位
//	DisplayData[1] = DIG_CODE[(receiveData-'0')%100/10];//十位
//	DisplayData[2] = DIG_CODE[(receiveData-'0')/100];//百位
	i=1;
	TI=0;				//清除发送完成标志位
}


