#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "adc.h"
#include "stdio.h"
#include "pwm.h"
#include "io.h"
#include "exti.h"
#include "usart.h"
#include "spareexti.h"

#define AVERAGE_TIMES 10
#define speed1		  600      //���湥���ٶ�
#define speed2		  300      //Ѳ��
#define speed3	      400      //���Ҽ����ת
#define speed9		  400      //������ת
#define speed4        200      //ǰ����

int i=0,a=0,b=0,c=0;

void up(void);

int main(void)
{ 
	delay_init();	    	        //��ʱ������ʼ��	 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	        //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    IO_Init();                  	//GPIO��ʼ��
    TIM3_PWM_Init(899,0);	        //����Ƶ��PWMƵ��=72000/900=8Khz
    Adc_Init();		        		//adc��ʼ��	
	while(io3||io4);				//������	
    up();		        	
	EXTIX_Init();							
	while(1)
	{	
		a=Get_Adc_Average(2,AVERAGE_TIMES);
		b=Get_Adc_Average(3,AVERAGE_TIMES);
		c=Get_Adc_Average(0,AVERAGE_TIMES);
        //��⵽�з�������		
		if((c>2100)||(!io1)||(!io2))	         								//ǰ
		{
			delay_ms(2);  
            if((c>2100)||(!io1)||(!io2))			
			{
				if((c>2100)||((!io1)&&(!io2)))		
				{
					delay_ms(2);
					if((c>2100)||((!io1)&&(!io2)))
					move(0,0);
					delay_ms(2);
					move(speed1,speed1);
				}
				else if((!io1)&&(io2)) 		
				{
					delay_ms(2);
					if((!io1)&&(io2))
					move(-speed4,speed4);										
				}
				else if((io1)&&(!io2)) 		
				{
					delay_ms(5);
					if((io1)&&(!io2)) 	
					move(speed4,-speed4);
				}
			}
		}
		else if((!io3)||(!io4))										//�� 
        {
			delay_ms(5);
            if((!io3)||(!io4))
			{
				move(speed3,-speed3);
				for(i=0;(i<500)&&io1&&io2&&(!(c>2100));i++)
				delay_ms(1);
			}
		}															//��
        else if((a>2100)||(b>2100))			   
		{
			delay_ms(5);  
			if((a>2100)||(b>2100))   
			{				
				move(speed9,-speed9);
				for(i=0;(i<500)&&io1&&io2&&(!(c>2100));i++)
				delay_ms(1); 
			}
		}               
        else if((!io5)||(!io6))  									//��                        	  
        {
			delay_ms(5);
			if((!io5)||(!io6))  
			{				
				move(-speed3,speed3);
				for(i=0;(i<500)&&io1&&io2&&(!(c>2100));i++)
				delay_ms(1); 
			}
	    }
	   //δ��⵽�з���Ѳ��
       else  
	   { 
		  move(speed2,speed2+20);  
	   }      
	   //���÷���̨
	   spareexti();
	}
}
		
void up(void)
{
	move(600,600);
	delay_ms(600);
	move(500,-500);
	delay_ms(200);
	move(600,600);
	delay_ms(300);
}
			
