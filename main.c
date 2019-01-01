/*  ***************�¿�������****************  */

#include<reg51.h>
#include"lcd.h"
#include"temp.h"
int settemp = 12;	//��ʼ�趨�¶�
sbit sc = P1^0
;	//���ƹ�������
sbit uptemp = P3^0;	//����¶�
sbit lowtemp = P3^1;//�����¶�
void LcdDisplay(int); //�¶���ʾ
void controlout ();	//���ƹ������
int testset();	   //����¶ȵ��������ص�����ֵ



/*   **********************������**********************    */

void main()
{  

	LcdInit();			 //��ʼ��LCD1602
	LcdWriteCom(0x88);	//д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('C');

		 
	while(1)
	{	int s;
		controlout();
	    s = testset();
		LcdWriteCom(0x8a);		 //д��ַ 80��ʾ��ʼ��ַ
	    LcdWriteData('0'+s/10); //�趨ʮλ
    	LcdWriteCom(0x8b
		);		 //д��ַ 80��ʾ��ʼ��ַ
	    LcdWriteData('0'+s%10); //�趨��λ
		LcdDisplay(Ds18b20ReadTemp());

	}
}
/*   **********����¶��趨�������趨ֵ**************     */   
 int testset ()
 {	
 int i = 1;
 if(uptemp == 1)
 {
 Lcd1602_Delay1ms(10);
 if(uptemp == 1)
 settemp++;
 while((i<500)&&(uptemp == 1))
 {
 Lcd1602_Delay1ms(1);
 i++;
 }
 }
 if(lowtemp == 1)
 {
 Lcd1602_Delay1ms(10);
 if(lowtemp == 1)
  settemp--; 
  while((i<500)&&(lowtemp == 1))
  {
  Lcd1602_Delay1ms(1);
  i++;
  }
 }
  return settemp;	   //�����趨�¶�
 }
/*    ********* ��ȡ�¶Ȳ����ƹ������************     */
	void controlout ()
	{
    int  livetemp; //ʵʱ�¶�
	livetemp = Ds18b20ReadTemp();	  //��ȡʵʱ�¶�
	if(livetemp< 0)				//���¶�ֵΪ����
  	{
		livetemp=livetemp-1;
		livetemp=~livetemp;	 //��1ȡ����ԭ��
		livetemp=livetemp*0.0625;	
  	}
 	else
        livetemp=livetemp*0.0625;	   //����	
	if(livetemp<settemp)    
	sc=0;			//	�¶ȸ�ʱ�����ͨ
	if((livetemp-settemp)>3)			
	sc=1;			 //	�¶ȵ�ʱ������ͨ
	}
/*************************************************** lcd�����ʾ*****************************                   */

void LcdDisplay(int temp) 	 //lcd��ʾ
{
   
  	unsigned char  datas[] = {0, 0, 0, 0, 0}; //��������
	float tp;
	if(temp< 0)				//���¶�ֵΪ����
  	{
	  	LcdWriteCom(0x80);	//д��ַ 80��ʾ��ʼ��ַ
	    LcdWriteData('-');  //��ʾ��
		temp=temp-1;
		temp=~temp;	 //��1ȡ����ԭ��
		tp=temp;
		temp=tp*0.0625*100+0.5;	
	
  	}
 	else
  	{			
	  	LcdWriteCom(0x80);		//д��ַ 80��ʾ��ʼ��ַ
	    LcdWriteData('+'); 		//��ʾ��
		tp=temp;              //����������Ǳ���
		temp=tp*0.0625*100+0.5;	   //����
		
	}
	 
	datas[0] = temp / 10000;	  //��λ
	datas[1] = temp % 10000 / 1000;	//ʮλ
	datas[2] = temp % 1000 / 100;  //��λ
	datas[3] = temp % 100 / 10;	   //ʮ��λ
	datas[4] = temp % 10;		   //�ٷ�λ
	

	LcdWriteCom(0x82);		  //д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('0'+datas[0]); //��λ 

	LcdWriteCom(0x83);		 //д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('0'+datas[1]); //ʮλ


	LcdWriteCom(0x84);		//д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('0'+datas[2]); //��λ 

	LcdWriteCom(0x85);		//д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('.'); 		//��ʾ ��.��

	LcdWriteCom(0x86);		    //д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('0'+datas[3]); //�ٷ�λ 


	LcdWriteCom(0x87);		 //д��ַ 80��ʾ��ʼ��ַ
	LcdWriteData('0'+datas[4]); //�ٷ�λ

	 
}

