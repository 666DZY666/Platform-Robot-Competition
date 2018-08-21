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
#define speed1		  600      //正面攻击速度
#define speed2		  300      //巡逻
#define speed3	      400      //左右检测旋转
#define speed9		  400      //后检测旋转
#define speed4        200      //前矫正

int i=0,a=0,b=0,c=0;

void up(void);

int main(void)
{ 
	delay_init();	    	        //延时函数初始化	 
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	        //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    IO_Init();                  	//GPIO初始化
    TIM3_PWM_Init(899,0);	        //不分频。PWM频率=72000/900=8Khz
    Adc_Init();		        		//adc初始化	
	while(io3||io4);				//软启动	
    up();		        	
	EXTIX_Init();							
	while(1)
	{	
		a=Get_Adc_Average(2,AVERAGE_TIMES);
		b=Get_Adc_Average(3,AVERAGE_TIMES);
		c=Get_Adc_Average(0,AVERAGE_TIMES);
        //检测到敌方，攻击		
		if((c>2100)||(!io1)||(!io2))	         								//前
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
		else if((!io3)||(!io4))										//右 
        {
			delay_ms(5);
            if((!io3)||(!io4))
			{
				move(speed3,-speed3);
				for(i=0;(i<500)&&io1&&io2&&(!(c>2100));i++)
				delay_ms(1);
			}
		}															//后
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
        else if((!io5)||(!io6))  									//左                        	  
        {
			delay_ms(5);
			if((!io5)||(!io6))  
			{				
				move(-speed3,speed3);
				for(i=0;(i<500)&&io1&&io2&&(!(c>2100));i++)
				delay_ms(1); 
			}
	    }
	   //未检测到敌方，巡逻
       else  
	   { 
		  move(speed2,speed2+20);  
	   }      
	   //备用防掉台
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
			
