/*******************************************************************************
* 实验名			   : 万年历实验
* 使用的IO	     : 
* 实验效果       :1602显示时钟，按K3进入时钟设置，按K1选择设置的时分秒日月，按K2选择
*选择设置加1。 
*	注意					 ：
*******************************************************************************/
#include<reg51.h>
#include"lcd.h"
#include"ds1302.h"
typedef unsigned int u16;	 
sbit beep=P1^5;	  
sbit K1=P3^1;
sbit K2=P3^0;
sbit K3=P3^2;
sbit K4=P3^3;
void delay(u16 i);
void Int0Configuration();
void LcdDisplay();
unsigned char SetState,SetPlace;
void Delay10ms(void);   //误差 0us

u16 a=0;
void delay(u16 i)
{
	while(i--);	
}

/*******************************************************************************
* 函数名         : main
* 函数功能		   : 主函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

void main()
{
//	unsigned char i;
	Int0Configuration();
	LcdInit();
	Ds1302Init();
	while(1)
	{	
		if(SetState==0)
		{
			Ds1302ReadTime();
		}
		LcdDisplay();
	if(TIME[5]==0x03)
		{
			for(a=0;a<100;a++)
			{
				beep=~beep;
				delay(50); //延时大约100us   通过修改此延时时间达到不同的发声效果	
			}

		}
	}
	
}
/*******************************************************************************
* 函数名         : LcdDisplay()
* 函数功能		   : 显示函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

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
/*******************************************************************************
* 函数名         : Int0Configuration()
* 函数功能		   : 配置外部中断0
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

void Int0Configuration()
{
	//设置INT0
	IT0=1;//跳变沿出发方式（下降沿）
	EX0=1;//打开INT0的中断允许。
	EA=1;//打开总中断	
}
/*******************************************************************************
* 函数名         : Int0() 
* 函数功能		   : 外部中断0 中断函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

void Int0() interrupt 0		 
{
	Delay10ms();
	if(K3==0)
	{
		SetState=~SetState;
		SetPlace=0;
		Ds1302Init();	
	}
}
/*******************************************************************************
* 函数名         : Delay10ms
* 函数功能		   : 延时函数，延时10ms
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/
void Delay10ms(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}