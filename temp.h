#ifndef __TEMP_H_
#define __TEMP_H_

#include<reg51.h>

sbit DSPORT=P2^3; // �¶ȵ����߽ӿ�
void Delay1ms(unsigned int );	// ��ʱ1����
unsigned char Ds18b20Init();	  // ��ʼ��
void Ds18b20WriteByte(unsigned char com);//д�ֽ�		
unsigned char Ds18b20ReadByte();	 //���ֽ�
void  Ds18b20ChangTemp();			 //ת���¶�
void  Ds18b20ReadTempCom();		   //��ȡ�¶�����
int Ds18b20ReadTemp();			 //�����¶�

#endif
