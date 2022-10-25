#ifndef __I2C_H_
#define __I2C_H_

#include <reg52.h>

sbit SCL=P3^7;
sbit SDA=P3^6;

void I2cStart();
void I2cStop();
unsigned char I2cSendByte(unsigned char dat);
unsigned char I2cReadByte();
void At24c16Write(unsigned char addr,unsigned char dat);
unsigned char At24c16Read(unsigned char addr);

#endif
