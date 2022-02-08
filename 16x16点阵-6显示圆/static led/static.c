
/************************************************************************************/
/*     程序名：16x16点阵试验程序          							                */
/*                                                                                  */
/*     CPU型号：AT89S52/STC89C51RC    晶振：12.0 M                                  */
/*                                                                                  */                                             
/*                                                                                  */
/*     功能描述： 控制16x16LED点阵显示图形字母汉字等                                */
/*     行  扫    ： 74ls138x2 CPU P1口前四位 A P1^0	 B  P1^1  C  P1^2   D  P1^3	   	*/
/*     列扫（数据）：SCK P0^0 RCK P0^1 SER P0^2                                     */
/*     取模方式：    阳码 逐行式  逆向（低位在前）                                        								    */
/*																				    */
/*                                                      精英团队 版权所有           */                                 
/*                                                            2008-06-20            */
/************************************************************************************/ 

#include<reg52.h>
#include<math.h>

#define uchar unsigned char
#define uint unsigned int 
 


sbit  P_HC595_SCK  =  P0^0;        // CPU  pin 1       SCK        数据输入时钟
sbit  P_HC595_RCK  =  P0^1;        // CPU  pin 2       RCK        数据输出时钟
sbit  P_HC595_SER  =  P0^2;        // CPU  pin 3        SER       数据输入


uint  yanshi=500;


uchar code table[]=
{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};

uchar code table_col[]=
{0x80,0x00, 0x40,0x00, 0x20,0x00, 0x10,0x00, 0x08,0x00, 0x04,0x00, 0x02,0x00, 0x01,0x00, 0x00,0x80, 0x00,0x40,0x00,0x20,0x00,0x10,0x00,0x08,0x00,0x04,0x00,0x02,0x00,0x01};





 

void delay(uint x)                      //延时子函数
{	
	uint i,j;
	for(i=x;i>0;i--)
	   for(j=50;j>0;j--);
}


 

void Send_595(unsigned char dat)        //发送一个字节
{                
        unsigned char  i;
        for(i=0; i<8; i++)
        {
                if(dat & 0x01)           //如果dat和0x01与的结果是1，也就是需要led亮，就把数据位置0， 
  
//  0000 0000 0000 1000
//  0000 0000 0000 0001
//  0000 0000 0000 0000
//  需要右移
//  第一位获取的是0，由于是阴码 0 时led是不亮的，根据595的工作原理和电路原理，送的数据应该为 1 ，送到第四位时，与的结果为1，，数据送 0 。

				   P_HC595_SER = 0;	    //数据是 0 时，led 亮
               else                		
				   P_HC595_SER = 1;	   //数据是 1  时，led不亮		    
                
			// P_HC595_SER  =  dat & 0x80 ;   //取出最高位
				
				P_HC595_SCK = 0;
			
				//delay(1);

                P_HC595_SCK = 1;

                dat = dat >> 1;		//右移1位


        }

	
}

void Show_595_16(unsigned char dat1,dat2)  //显示一行数据


{

       Send_595(dat2);	  // 送一行的高位数据
	   Send_595(dat1);	  // 送一行的低位数据
	  	   				  
	   
	   P_HC595_RCK = 1;	  //数据锁存高电平

	   P_HC595_RCK = 0;	  //数据锁存低电平


	    

}  
 
void Show_595_point(uint x,y)  //显示一个点

{

 P1 = table[y];

 Show_595_16(table_col[2*x],table_col[2*x+1]);




}

void Show_595_round(uint x,y,r)  //显示圆

{

  unsigned int i,j;

  for (i=x-r;i<x+r;i++)
  
  
  {
  	   
   
        Show_595_point(i,(sqrt(r*r+((i-x)*(i-x))+y)-r));

   		  
   
   }

    

}


 
  


void main()
{	
 	   while(1)

	   {

  			  unsigned int i,x,y,r,j;

			  x=8;y=8;r=7;

             for (i=x-r;i<x+r;i++)
  
  
  {
  	    
   
        Show_595_point(i,(sqrt(r*r+((i-x)*(i-x))+y)));
		
   		  
   
   }

   }
	     
	    	 
			
	 	    
         

           
     

}


