
/************************************************************************************/
/*     ��������16x16�����������          							                */
/*                                                                                  */
/*     CPU�ͺţ�AT89S52/STC89C51RC    ����12.0 M                                  */
/*                                                                                  */                                             
/*                                                                                  */
/*     ���������� ����16x16LED������ʾͼ����ĸ���ֵ�                                */
/*     ��  ɨ    �� 74ls138x2 CPU P1��ǰ��λ A P1^0	 B  P1^1  C  P1^2   D  P1^3	   	*/
/*     ��ɨ�����ݣ���SCK P0^0 RCK P0^1 SER P0^2                                     */
/*     ȡģ��ʽ��    ���� ����ʽ  ���򣨵�λ��ǰ��                                        								    */
/*																				    */
/*                                                      ��Ӣ�Ŷ� ��Ȩ����           */                                 
/*                                                            2008-06-20            */
/************************************************************************************/ 

#include<reg52.h>
#include<math.h>

#define uchar unsigned char
#define uint unsigned int 
 


sbit  P_HC595_SCK  =  P0^0;        // CPU  pin 1       SCK        ��������ʱ��
sbit  P_HC595_RCK  =  P0^1;        // CPU  pin 2       RCK        �������ʱ��
sbit  P_HC595_SER  =  P0^2;        // CPU  pin 3        SER       ��������


uint  yanshi=500;


uchar code table[]=
{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};

uchar code table_col[]=
{0x80,0x00, 0x40,0x00, 0x20,0x00, 0x10,0x00, 0x08,0x00, 0x04,0x00, 0x02,0x00, 0x01,0x00, 0x00,0x80, 0x00,0x40,0x00,0x20,0x00,0x10,0x00,0x08,0x00,0x04,0x00,0x02,0x00,0x01};





 

void delay(uint x)                      //��ʱ�Ӻ���
{	
	uint i,j;
	for(i=x;i>0;i--)
	   for(j=50;j>0;j--);
}


 

void Send_595(unsigned char dat)        //����һ���ֽ�
{                
        unsigned char  i;
        for(i=0; i<8; i++)
        {
                if(dat & 0x01)           //���dat��0x01��Ľ����1��Ҳ������Ҫled�����Ͱ�����λ��0�� 
  
//  0000 0000 0000 1000
//  0000 0000 0000 0001
//  0000 0000 0000 0000
//  ��Ҫ����
//  ��һλ��ȡ����0������������ 0 ʱled�ǲ����ģ�����595�Ĺ���ԭ��͵�·ԭ���͵�����Ӧ��Ϊ 1 ���͵�����λʱ����Ľ��Ϊ1���������� 0 ��

				   P_HC595_SER = 0;	    //������ 0 ʱ��led ��
               else                		
				   P_HC595_SER = 1;	   //������ 1  ʱ��led����		    
                
			// P_HC595_SER  =  dat & 0x80 ;   //ȡ�����λ
				
				P_HC595_SCK = 0;
			
				//delay(1);

                P_HC595_SCK = 1;

                dat = dat >> 1;		//����1λ


        }

	
}

void Show_595_16(unsigned char dat1,dat2)  //��ʾһ������


{

       Send_595(dat2);	  // ��һ�еĸ�λ����
	   Send_595(dat1);	  // ��һ�еĵ�λ����
	  	   				  
	   
	   P_HC595_RCK = 1;	  //��������ߵ�ƽ

	   P_HC595_RCK = 0;	  //��������͵�ƽ


	    

}  
 
void Show_595_point(uint x,y)  //��ʾһ����

{

 P1 = table[y];

 Show_595_16(table_col[2*x],table_col[2*x+1]);




}

void Show_595_round(uint x,y,r)  //��ʾԲ

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


