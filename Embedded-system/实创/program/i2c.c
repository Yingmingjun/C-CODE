#include"i2c.h"

void Delay10us()
{
	unsigned char a,b;
	for(b=1;b>0;b--)
		for(a=2;a>0;a--);
}

void I2cStart()//起始信号：在SCL时钟信号在高电平期间SDA信号产生一个下降沿
{
	SDA=1;
	Delay10us();
	SCL=1;
	Delay10us();//建立时间是SDA保持时间>4.7us
	SDA=0;
	Delay10us();//保持时间是>4us
	SCL=0;			
	Delay10us();		
}

void I2cStop()//终止信号：在SCL时钟信号高电平期间SDA信号产生一个上升沿
{
	SDA=0;
	Delay10us();
	SCL=1;
	Delay10us();//建立时间大于4.7us
	SDA=1;
	Delay10us();		
}//结束之后保持SDA和SCL都为1；表示总线空闲


//I2cSendByte(unsigned char dat)通过I2C发送一个字节。在SCL时钟信号高电平期间，保持发送信号SDA保持稳定
unsigned char I2cSendByte(unsigned char dat)
{
	unsigned char a=0,b=0;//最大65535，一个机器周期为1us，最大延时65535us。		
	for(a=0;a<8;a++)//要发送16位，从最高位开始
	{
		SDA=dat>>7;	 //起始信号之后SCL=0，所以可以直接改变SDA信号
		dat=dat<<1;
		Delay10us();
		SCL=1;
		Delay10us();//建立时间>4.7us
		SCL=0;
		Delay10us();//时间大于4us		
	}
	SDA=1;
	Delay10us();
	SCL=1;
	while(SDA)//等待应答，也就是等待从设备把SDA拉低
	{
		b++;
		if(b>200)	 //如果超过2000us没有应答发送失败，或者为非应答，表示接收结束
		{
			SCL=0;
			Delay10us();
			return 0;
		}
	}
	SCL=0;
	Delay10us();
 	return 1;		
}


unsigned char I2cReadByte()//使用I2c读取一个字节，接收完一个字节SCL=0,SDA=1.
{
	unsigned char a=0,dat=0;
	SDA=1;			//起始和发送一个字节之后SCL都是0
	Delay10us();
	for(a=0;a<8;a++)//接收8个字节
	{
		SCL=1;
		Delay10us();
		dat<<=1;
		dat|=SDA;
		Delay10us();
		SCL=0;
		Delay10us();
	}
	return dat;		
}


void At24c16Write(unsigned char addr,unsigned char dat)//往24c16的一个地址写入一个数据
{
	I2cStart();
	I2cSendByte(0xa0);//发送写器件地址
	I2cSendByte(addr);//发送要写入内存地址
	I2cSendByte(dat);	//发送数据
	I2cStop();
}


unsigned char At24c16Read(unsigned char addr)//读取at24c16的一个地址的一个数据
{
	unsigned char num;
	I2cStart();
	I2cSendByte(0xa0); //发送写器件地址
	I2cSendByte(addr); //发送要读取的地址
	I2cStart();
	I2cSendByte(0xa1); //发送读器件地址
	num=I2cReadByte(); //读取数据
	I2cStop();
	return num;	
}

