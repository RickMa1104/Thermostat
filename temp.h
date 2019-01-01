#ifndef __TEMP_H_
#define __TEMP_H_

#include<reg51.h>

sbit DSPORT=P2^3; // 温度单总线接口
void Delay1ms(unsigned int );	// 延时1毫秒
unsigned char Ds18b20Init();	  // 初始化
void Ds18b20WriteByte(unsigned char com);//写字节		
unsigned char Ds18b20ReadByte();	 //读字节
void  Ds18b20ChangTemp();			 //转换温度
void  Ds18b20ReadTempCom();		   //读取温度命令
int Ds18b20ReadTemp();			 //返回温度

#endif
