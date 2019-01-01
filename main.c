/*  ***************温控器程序****************  */

#include<reg51.h>
#include"lcd.h"
#include"temp.h"
int settemp = 12;	//初始设定温度
sbit sc = P1^0
;	//控制光耦的输出
sbit uptemp = P3^0;	//提高温度
sbit lowtemp = P3^1;//降低温度
void LcdDisplay(int); //温度显示
void controlout ();	//控制光耦输出
int testset();	   //检测温度调整，返回调整后值



/*   **********************主函数**********************    */

void main()
{  

	LcdInit();			 //初始化LCD1602
	LcdWriteCom(0x88);	//写地址 80表示初始地址
	LcdWriteData('C');

		 
	while(1)
	{	int s;
		controlout();
	    s = testset();
		LcdWriteCom(0x8a);		 //写地址 80表示初始地址
	    LcdWriteData('0'+s/10); //设定十位
    	LcdWriteCom(0x8b
		);		 //写地址 80表示初始地址
	    LcdWriteData('0'+s%10); //设定个位
		LcdDisplay(Ds18b20ReadTemp());

	}
}
/*   **********检查温度设定并返回设定值**************     */   
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
  return settemp;	   //返回设定温度
 }
/*    ********* 获取温度并控制光耦输出************     */
	void controlout ()
	{
    int  livetemp; //实时温度
	livetemp = Ds18b20ReadTemp();	  //获取实时温度
	if(livetemp< 0)				//当温度值为负数
  	{
		livetemp=livetemp-1;
		livetemp=~livetemp;	 //减1取反求原码
		livetemp=livetemp*0.0625;	
  	}
 	else
        livetemp=livetemp*0.0625;	   //换算	
	if(livetemp<settemp)    
	sc=0;			//	温度高时，光耦不通
	if((livetemp-settemp)>3)			
	sc=1;			 //	温度低时，光耦通
	}
/*************************************************** lcd输出显示*****************************                   */

void LcdDisplay(int temp) 	 //lcd显示
{
   
  	unsigned char  datas[] = {0, 0, 0, 0, 0}; //定义数组
	float tp;
	if(temp< 0)				//当温度值为负数
  	{
	  	LcdWriteCom(0x80);	//写地址 80表示初始地址
	    LcdWriteData('-');  //显示负
		temp=temp-1;
		temp=~temp;	 //减1取反求原码
		tp=temp;
		temp=tp*0.0625*100+0.5;	
	
  	}
 	else
  	{			
	  	LcdWriteCom(0x80);		//写地址 80表示初始地址
	    LcdWriteData('+'); 		//显示正
		tp=temp;              //正数补码就是本身
		temp=tp*0.0625*100+0.5;	   //换算
		
	}
	 
	datas[0] = temp / 10000;	  //百位
	datas[1] = temp % 10000 / 1000;	//十位
	datas[2] = temp % 1000 / 100;  //个位
	datas[3] = temp % 100 / 10;	   //十分位
	datas[4] = temp % 10;		   //百分位
	

	LcdWriteCom(0x82);		  //写地址 80表示初始地址
	LcdWriteData('0'+datas[0]); //百位 

	LcdWriteCom(0x83);		 //写地址 80表示初始地址
	LcdWriteData('0'+datas[1]); //十位


	LcdWriteCom(0x84);		//写地址 80表示初始地址
	LcdWriteData('0'+datas[2]); //个位 

	LcdWriteCom(0x85);		//写地址 80表示初始地址
	LcdWriteData('.'); 		//显示 ‘.’

	LcdWriteCom(0x86);		    //写地址 80表示初始地址
	LcdWriteData('0'+datas[3]); //百分位 


	LcdWriteCom(0x87);		 //写地址 80表示初始地址
	LcdWriteData('0'+datas[4]); //百分位

	 
}

