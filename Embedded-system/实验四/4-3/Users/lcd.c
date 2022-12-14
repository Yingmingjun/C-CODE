#include "lcd.h"

//延时函数，延时1ms
//该函数是在11.0592MHZ晶振下，12分频单片机的延时
void Lcd1602_Delay1ms(uint c)   //误差 0us
{
    uchar a,b;
	for (; c>0; c--)
	{
		for(b=102;b>0;b--)
		{
			for(a=3;a>0;a--);  
		}
	}	
}

void LcdWriteCom(uchar com)	  //写入命令
{
	LCD1602_E = 0;     //使能
	LCD1602_RS = 0;	   //选择发送命令
	LCD1602_RW = 0;	   //选择写入
	
	LCD1602_DATAPINS = com;     //放入命令
	Lcd1602_Delay1ms(1);		//等待数据稳定

	LCD1602_E = 1;	          //写入时序
	Lcd1602_Delay1ms(5);	  //保持时间
	LCD1602_E = 0;
}	   
   
void LcdWriteData(uchar dat)			//写入数据
{
	LCD1602_E = 0;	//使能清零
	LCD1602_RS = 1;	//选择输入数据
	LCD1602_RW = 0;	//选择写入
	Lcd1602_Delay1ms(1);
	LCD1602_DATAPINS = dat; //写入数据
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;   //写入时序
	Lcd1602_Delay1ms(5);   //保持时间
	LCD1602_E = 0;
	Lcd1602_Delay1ms(5);   //保持时间
}
/*******************************************************************************
* 函 数 名       : LcdInit()
* 函数功能		 : 初始化LCD屏
* 输    入       : 无
* 输    出       : 无
*******************************************************************************/		   

void LcdInit()						  //LCD初始化子程序
{
 	LcdWriteCom(0x38);  //开显示(功能设定指令)
	Lcd1602_Delay1ms(5);   //保持时间
	LcdWriteCom(0x0C);  //开显示不显示光标(显示开关控制指令)
	LcdWriteCom(0x01);  //清屏
	LcdWriteCom(0x06);  //写一个指针加1
}

