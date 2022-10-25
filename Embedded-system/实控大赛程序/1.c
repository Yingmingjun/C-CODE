#include <reg52.h>
#include <intrins.h>
typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;

sbit A0 = P1^0;
sbit A1 = P1^1;
sbit A2 = P1^2;
sbit beep = P1^5;
sbit select = P1^6;
sbit enter = P1^7;
u16 c1,c2,c3,c4;
u8 x,y;
u8 code number_1[]={0x00,0x00,0x82,0xFF,0x80,0x00,0x00,0x00};
u8 code number_2[]={0x00,0x00,0x79,0x49,0x49,0x4F,0x00,0x00};
u8 code number_3[]={0x00,0x00,0x49,0x49,0x49,0x7F,0x00,0x00};
u8 code level[]={0,500,300,150};//难度选择数组
u8 code ledduan[]={0x03,0x0C,0x30,0xC0};
u8 code ledsmile[]={0x3C,0x42,0x95,0xA1,0xA1,0x95,0x42,0x3C};
void delay(u16 i)
{
	for(x=0;x<i;x++)
	{
		for(y=0;y<120;y++);
	}
}

void check0()//开机自检程序，2*2点亮，循环16次
{	u16 c5;
	for(c1=0;c1<4;c1++)
	{	
		for(c5=0;c5<380;c5++)
		{
			A0=0;A1=0;A2=0;P0=ledduan[c1];
			delay(1);
			A0=1;A1=0;A2=0;P0=ledduan[c1];
			delay(1);
			P0=0;
		}
		for(c5=0;c5<380;c5++)
		{		
			A0=0;A1=1;A2=0;P0=ledduan[c1];
			delay(1);
			A0=1;A1=1;A2=0;P0=ledduan[c1];
			delay(1);
			P0=0;
		}
		for(c5=0;c5<380;c5++)
		{
			A0=0;A1=0;A2=1;P0=ledduan[c1];
			delay(1);
			A0=1;A1=0;A2=1;P0=ledduan[c1];
			delay(1);
			P0=0;
		}
		for(c5=0;c5<380;c5++)
		{
			A0=0;A1=1;A2=1;P0=ledduan[c1];
			delay(1);
			A0=1;A1=1;A2=1;P0=ledduan[c1];
			delay(1);
			P0=0;
		}
	}
}
void displaysmile()//smile_display with beeping 
{	
	beep = 0;
	for(c4=0;c4<500;c4++)
	{
		for(c3=0;c3<8;c3++)
		{				
			P0 = ledsmile[c3];
			if(P1==0x08)
			{
				P1=0;
			}P1++;	
			delay(1);
		}	
	}
	P0=0;
	beep = 1;	
}

void displaynumber(u8 n)
{
	u8 c3=0;
	if(n==1)
	{	
		for(c4=0;c4<500;c4++)
		{
			for(c3=0;c3<8;c3++)
			{				
				P0 = number_1[c3];
				if(P1==0x08)
				{
					P1 = 0;
				}P1++;	
				delay(1);
			}	
		}
	}
	
	if(n==2)
	{	
		for(c4=0;c4<500;c4++)
		{
			for(c3=0;c3<8;c3++)
			{				
				P0 = number_2[c3];
				if(P1==0x08)
				{
					P1=0;
				}P1++;	
				delay(1);
			}	
		}
	}
	
	if(n==3)
	{	
		for(c4=0;c4<500;c4++)
		{
			for(c3=0;c3<8;c3++)
			{				
				P0 = number_3[c3];
				if(P1==0x08)
				{
					P1=0;
				}P1++;	
				delay(1);
			}	
		}
	}
}

void model_select()
{	
	u8 *p = 0;
	u8 mod = *p;
	select=1;
	enter=1;
	while(enter)
	{
		if(mod>3)
		{
			mod=0;
		}
		if(select==0)
		{ 
			while(!select);
			mod++;	
		}displaynumber(mod);	
	}
}

void main()
{	
//	check0();
//	displaysmile();
	model_select();
	P0=0;

}

//void KeyDown1()//检测有无按键按下并读取键值
//{
////	char m;
//    for(;;)
//    {
//	GPIO_KEY=0x0f;
//	delay10ms();delay10ms();
//	if(GPIO_KEY!=0x0f)
//	{
//		delay10ms();
//		if(GPIO_KEY!=0x0f)
//		{
//			KeyState1=1; 
//			//测试列
//// 			Delay10ms();
//			switch(GPIO_KEY)
//			{
//				case(0X07):	KeyValue1=0;break;//0000 0111
//				case(0X0b):	KeyValue1=1;break;//0000 1011
//				case(0X0d): KeyValue1=2;break;//0000 1101
//				case(0X0e):	KeyValue1=3;break;//0000 1110
////				default:	KeyValue=17;	//检测出错回复17意思是把数码管全灭掉。
//			}
//			//测试行
//			GPIO_KEY=0xf0;
//			delay10ms();
//			switch(GPIO_KEY)
//			{
//				case(0X70):	KeyValue1=KeyValue1;break;
//				case(0Xb0):	KeyValue1=KeyValue1+4;break;
//				case(0Xd0): KeyValue1=KeyValue1+8;break;
//				case(0Xe0):	KeyValue1=KeyValue1+12;break;
////				default:	KeyValue1=17;
//			}
////			while((m<50)&&(GPIO_KEY!=0xf0))	 //检测按键松手检测
////			{
////			delay10ms();
////				m++;
////			}

//		}
//	}
//	DigDisplayN(KeyValue1);
//	if(KeyState1==1)
//        break;
//    }
//}



