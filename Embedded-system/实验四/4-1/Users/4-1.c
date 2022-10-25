/**********************************************************************************
编写程序，使用开发板与1602液晶显示模块实现以下功能：
1、	在1602的第一行上显示自己的座位号；
2、	在1602上第二行显示自己名字的首字母；比如（潘英杰：PYJ、徐访：XF）
注意：1、座位号请按照附件单片机实验成绩登记表.xlsx中的座位号
2、LCD1602液晶数据手册见附件
3、LCD1602液晶驱动请看附件文件夹
***********************************************************************************/

#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器
#include "lcd.h"

typedef unsigned int u16;	 //对数据类型进行声明定义
typedef unsigned char u8;

u8 Disp1[] = "63";
u8 Disp2[] = "YMJ";

void main(void)
{
	u8 i=0,j=0;
	LcdInit();
	LcdWriteCom(0x80);  //设置数据指针起点（第一行显示）
	for(i=0;i<2;i++)
	{
		LcdWriteData(Disp1[i]);	
		Lcd1602_Delay1ms(5);
	}
	
	LcdWriteCom(0xC0);  //设置数据指针起点（第二行显示）
	for(j=0;j<3;j++)
	{
		LcdWriteData(Disp2[j]);	
		Lcd1602_Delay1ms(5);
	}
	while(1);				
}



//判忙功能加入
//https://blog.csdn.net/u013151320/article/details/46663167
