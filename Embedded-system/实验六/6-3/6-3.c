/*ds1302显示时间（通过串口调试助手）*/
#include<reg52.h>
#include <intrins.h>
 
typedef unsigned char uint8;
typedef unsigned int  uint16;  
sbit SDA=P3^4; 	//数据	
sbit SCK=P3^5; //时钟
sbit RST=P1^7;	//DS1302复位(片选)
uint8 time[7]={50,41,20,9,8,4,12};//秒分时日月周年10-08-15 23:59:50   7代表周日
#define DS1302_W_ADDR 0x80
#define DS1302_R_ADDR 0x81
 
 
void ds1302_reset()//令SCK=0；RST=1
{
  RST=0;//停止数据传送
  SCK=0;//时钟总线清零
  RST=1;//数据操作
}
 
//写一个字节
void ds1302_write_byte(uint8 dat)
{
  uint8 i;
  
 for(i=0;i<8;i++)
 {
   SDA=dat & 0x01;
   SCK=1;
   SCK=0;
   dat>>=1;
 }
}
 
//读一个字节
//对于数据输出：开始的8 个SCLK 周期，输入一个读命令字节，数据字节在后8 个SCLK周期的下降沿输出
//注意，第一个数据字节的第一个下降沿发生后，命令字的最后一位被写入
//（Note that the first data bit to be transmitted occurs on the first falling edge after the last bit of the command byte is written. ），
//也就是命令字节最后一个字节写入后产生的下降沿使得第一个数据位被读取
 
uint8 ds1302_read_byte()
{
 uint8 i,dat=0;//用dat存储读到的数据
 for(i=0;i<8;i++)
 {
    
	dat>>=1;	
	if(SDA==1)
	  dat=dat | 0x80;//因为从低位开始读
	SCK=1;
	SCK=0;	//由上面解释可以知道：我们首先应该判断	if(SDA==1)，然后进行SCK=1，SCK=0
 
 }
 return dat;
}
 
//清除写保护
void ds1302_clear_WP()
{
  ds1302_reset();
  RST=1;
  ds1302_write_byte(0x8E);//写入地址
  ds1302_write_byte(0x00);//写入数据
  //写完后
  SDA=0;
  RST=0;
  
}
 
//设置写保护
void ds1302_set_WP()
{
  ds1302_reset();
  RST=1;
  ds1302_write_byte(0x8E);//写入地址
  ds1302_write_byte(0x80);//写入数据
  //写完后
  SDA=0;
  RST=0;
  
}
 
 
 
//写入ds1302
void ds1302_write(uint8 addr,uint8 dat)
{
  ds1302_reset();
  RST=1;
  ds1302_write_byte(addr);//写入地址
  ds1302_write_byte(dat);//写入数据
  //写完后
  RST=0;
  SDA=0;
}
 
//从ds1302读数据
uint8 ds1302_read(uint8 addr)
{
  uint8 temp=0;//存储读出来的数据
  ds1302_reset();
  RST=1;
  ds1302_write_byte(addr);//写入地址
  temp=ds1302_read_byte();//写入数据
  //写完后
  RST=0;
  SDA=0;
  return temp;
}
 
void delay(uint16 n)
{ 
  while(n--);
}
 
 
/**
 * 设定时钟数据
 其中涉及二进制和BCD转换  因为ds1302存BCD ，但是机器只认识二进制
 例如：存入ds1302为50  0101 0000  那么我们写入的是ds1302_write（80）
*/
void set_time(uint8 *timedata)
{
 	uint8 i;
	uint8 temp=0;
	for(i=0;i<7;i++)
	{
	  temp=timedata[i]/10;
	  timedata[i]=timedata[i]%10;
	  timedata[i]=timedata[i]+temp*16;
	}
	ds1302_clear_WP();//对ds1302操作前先将wp位清零
	temp=DS1302_W_ADDR;//写入起始位置
	for(i=0;i<7;i++)
	{
	  ds1302_write(temp,timedata[i]);
	  temp+=2;
	}
	ds1302_set_WP();
 
}
 
/**
 * 读时钟数据（BCD格式）
*/
void read_time(uint8 *timedata)
{
   uint8 i,temp;
   temp=DS1302_R_ADDR;//读起始位置
   for(i=0;i<7;i++)
   {
     timedata[i]=ds1302_read(temp);
	 temp+=2;
   }
}
/* UART初始化
 * 波特率：9600
*/
void uart_init(void)
{
  TMOD=0x21;
  SCON=0x50;
  
  TH1=0xFD;
  TL1=0xFD;
  
  TR1=1;  
}
 
/**
 * UART发送一字节
*/
void UART_Send_Byte(uint8 dat)
{ 
  SBUF=dat;
  while(TI==0);
   TI=0;
}
 
/**
 * 将数据转换成ASC码并通过UART发送出去
*/
void UART_Send_Dat(uint8 dat)  //注意是关于16取余
{
   UART_Send_Byte(dat/16+'0');
   UART_Send_Byte(dat%16+'0');	 
}
void main()
{
  	 
 
	uart_init();
 	set_time(&time);    //设定时间值
 
	while(1)
	{
 
		read_time(&time);   //秒分时日月周年
  	
		UART_Send_Dat(time[6]);
		UART_Send_Byte('-');
		UART_Send_Dat(time[4]);
		UART_Send_Byte('-');
		UART_Send_Dat(time[3]);
		UART_Send_Byte(' ');
 
		UART_Send_Dat(time[2]);
		UART_Send_Byte(':');
		UART_Send_Dat(time[1]);
		UART_Send_Byte(':');
		UART_Send_Dat(time[0]);
		UART_Send_Byte('\r');
		UART_Send_Byte('\n');
 
		delay(10000);
	}
}
 