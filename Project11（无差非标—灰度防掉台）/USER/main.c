/*****************DZY*******************
���ߣ�����ԭ
�ļ�����main.c
�������ڣ�2018.8.8
ά���ˣ�����ԭ
ά�����ڣ�2018.8.8
�����������˶Կ�������
****************************************/
#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "adc.h"
//#include "stdio.h"
#include "pwm.h"
#include "io.h"
//#include "exti.h"
#include "usart.h"
//#include "spareexti.h"

//�ٶȴ�С�궨��
#define speed1		  650      //���湥���ٶ�
#define speed2		  480      //����ȫ����Ѳ��
#define speed3	    550      //���Ҽ����ת
#define speed4      898      //���غ���
#define speed5      650      //������ת
#define speed6		  400      //���ǰ�ȫ����Ѳ��
//��ʱ�궨��
#define t1		      300      //���غ���
#define t2          180      //������ת
#define t3          600      //�����ת
#define t4          450      //���غ��ˣ�����ʱ��
//�Ҷ���ֵ�궨��
#define V1 1750							 //ǰ������ȫ��
#define V2 2300              //ǰ��������
#define V3 1450              //���󡪡���ȫ��
#define V4 1450							 //���ҡ�����ȫ��
#define V5 1850              //���󡪡�����
#define V6 1850							 //���ҡ�������
  //�ҶȲ�ֵ
#define f1 5
#define f2 5
#define f3 5
#define f4 5
//AD(�Ҷ�)�궨��
#define AVERAGE_TIMES 2
#define a Get_Adc_Average(0,AVERAGE_TIMES)//ǰ�����Ҷ�
#define b Get_Adc_Average(3,AVERAGE_TIMES)//����
#define c Get_Adc_Average(2,AVERAGE_TIMES)//����
//��������
int i=0,f=1;
//��������
void up(void);
//������(��RTOS)
int main(void)
{ 
	delay_init();	    	        	//��ʱ������ʼ��	 
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
  IO_Init();                  	//GPIO��ʼ��
  TIM3_PWM_Init(899,0);	        //PWM��ʼ�����ٶ����ֵΪ899��
  Adc_Init();		        				//adc��ʼ��	
	while(io4);										//������	
  up();		                      //���������������       	
//	EXTIX_Init();			
  //��ѭ��
	while(1)
	{	
		//���򣨳�Ϊ˫��ͷ����ÿ�����ش�����������������
		if(f)
		{
			//̨�ߣ�������������ֱ�Ϊ������������ߡ��ұߡ��м䣩
			if(a > V2)
			{
				//����
				if(a > V2 && b - c > f1)
				{
					if(a > b || a > c)
					{
						if((!io1)||(!io2))
						{
							move(-speed4,-speed4);
							//ǰ���⵽���˽���ʱ�����أ��ٶȽϴ󣬺���ʱ�����
							delay_ms(t4);
						}
						else
						{
							move(-speed4,-speed4);
							//��֮�϶�
							delay_ms(t1);
						}
						//ɲ��
						move(0,0);
						delay_ms(5);
						//���˺���ת
						move(-speed5,speed5);
						delay_ms(t2);		
						//�����־
						f = !f;						
					}
				}
				//����
				else if(a > V2 && c - b > f2)
				{
					if(a > b || a > c)
					{
						if((!io1)||(!io2))
						{
							move(-speed4,-speed4);
							delay_ms(t4);
						}
						else
						{
							move(-speed4,-speed4);
							delay_ms(t1);
						}
						move(0,0);
						delay_ms(5);
						move(speed5,-speed5);
						delay_ms(t2);
						f = !f;	
					}
				}
				//�м�
				else if(a > V2)
				{
					if(a > b || a > c)
					{
						if((!io1)||(!io2))
						{
							move(-speed4,-speed4);
							delay_ms(t4);
						}
						else
						{
							move(-speed4,-speed4);
							delay_ms(t1);
						}
						move(0,0);
						delay_ms(5);
						f = !f;	
					}
				}
			}
			//̨��	       
				//����
			if(f)
			{
				//��⵽�з�������
				if(!io1)	         		//ǰ
				{
					move(speed1,speed1);
					f = 1;
				}
				else if(!io2)			    //��
				{
					move(-speed1,-speed1);
					f = 0;
				}
				else if(!io3)  			  //��                        	  
				{
					move(-speed3,speed3+50);
					//���ɿأ������ת����ת��������ǰ|���⵽������������δ��⵽��ת�����Ƕȣ�
					for(i=0;(i<t3)&&io1&&io2;i++)
						delay_ms(1); 
					if(!io1)
					{
						move(speed1,speed1);
					}
					else if(!io2)
					{
						move(-speed1,-speed1);
					}
				}
				else if(!io4)					//�� 
				{
					move(speed3+50,-speed3);
					for(i=0;(i<t3)&&io1;i++)
						delay_ms(1);
					if(!io1)
					{
						move(speed1,speed1);
					}
					else if(!io2)
					{
						move(-speed1,-speed1);
					}
				}															
				//δ��⵽�з���Ѳ��
					//�ǰ�ȫ������
				else if(a > V1 && a < V2)
				//if(a > V1 && a < V2)
				{
					move(speed6,speed6);
				}
					//��ȫ������
				else  
				{ 
					move(speed2,speed2);
				}  
			}
				//����
			else
			{
				//��⵽�з�������
				if(!io1)	         		//ǰ
				{
					move(speed1,speed1);
					f = 1;
				}
				else if(!io2)			   //��
				{
					move(-speed1,-speed1);
					f = 0;
				}
				else if(!io3)  			 //��                        	  
				{
					move(speed3+50,-speed3);
					for(i=0;(i<t3)&&io1&&io2;i++)
						delay_ms(1); 
					if(!io1)
					{
						move(speed1,speed1);
					}
					else if(!io2)
					{
						move(-speed1,-speed1);
					}
				}
				else if(!io4)					//�� 
				{
					move(-speed3,speed3+50);
					for(i=0;(i<t3)&&io1;i++)
						delay_ms(1);
					if(!io1)
					{
						move(speed1,speed1);
					}
					else if(!io2)
					{
						move(-speed1,-speed1);
					}
				}															
				//δ��⵽�з���Ѳ��
				else if((b > V3 && b < V5) || (c > V4 && c < V6))
				//if((b > V3 && b < V5) || (c > V4 && c < V6))
				{
					move(-speed6,-speed6);
				}
				else  
				{ 
					move(-speed2,-speed2);
				}  
			}
		}
		//���򣨴���ͬ�ϣ�ע���ٶȷ�������������������Ҽ����ת���ٶȷ���ע���������
		else
		{
			//̨��
			if(b > V5 || c > V6)
			{
				if((b > V5 || c > V6) && b - c > f3)
				{
					if(b > a || c > a)
					{
						if((!io1)||(!io2))
						{
							move(speed4,speed4);
							delay_ms(t4);
						}
						else
						{
							move(speed4,speed4);
							delay_ms(t1);
						}
						move(0,0);
						delay_ms(5);
						move(speed5,-speed5);
						delay_ms(t2);	
						f = !f;
					}						
				}
				else if((b > V5 || c > V6) && c - b > f4)
				{
					if(b > a || c > a)
					{
						if((!io1)||(!io2))
						{
							move(speed4,speed4);
							delay_ms(t4);
						}
						else
						{
							move(speed4,speed4);
							delay_ms(t1);
						}
						move(0,0);
						delay_ms(5);
						move(-speed5,speed5);
						delay_ms(t2);
						f = !f;
					}
				}
				else if(b > V5 || c > V6)
				{
					if(b > a || c > a)
					{
						if((!io1)||(!io2))
						{
							move(speed4,speed4);
							delay_ms(t4);
						}
						else
						{
							move(speed4,speed4);
							delay_ms(t1);
						}
						move(0,0);
						delay_ms(5);
						f = !f;
					}
				}
			}
			//̨��	
				//����
			if(f)
			{
				//��⵽�з�������
				if(!io1)	         		//ǰ
				{
					move(speed1,speed1);
					f = 1;
				}
				else if(!io2)			   //��
				{
					move(-speed1,-speed1);
					f = 0;
				}
				else if(!io3)  			 //��                        	  
				{
					move(-speed3,speed3+50);
					for(i=0;(i<t3)&&io1&&io2;i++)
						delay_ms(1); 
					if(!io1)
					{
						move(speed1,speed1);
					}
					else if(!io2)
					{
						move(-speed1,-speed1);
					}
				}
				else if(!io4)					//�� 
				{
					move(speed3+50,-speed3);
					for(i=0;(i<t3)&&io1;i++)
						delay_ms(1);
					if(!io1)
					{
						move(speed1,speed1);
					}
					else if(!io2)
					{
						move(-speed1,-speed1);
					}
				}															
				//δ��⵽�з���Ѳ��
				else if(a > V1 && a < V2)
				//if(a > V1 && a < V2)
				{
					move(speed6,speed6);
				}
				else  
				{ 
					move(speed2,speed2);
				}  
			}
				//����
			else
			{
				//��⵽�з�������
				if(!io1)	         		//ǰ
				{
					move(speed1,speed1);
					f = 1;
				}
				else if(!io2)			   //��
				{
					move(-speed1,-speed1);
					f = 0;
				}
				else if(!io3)  			 //��                        	  
				{
					move(speed3+50,-speed3);
					for(i=0;(i<t3)&&io1&&io2;i++)
						delay_ms(1); 
					if(!io1)
					{
						move(speed1,speed1);
					}
					else if(!io2)
					{
						move(-speed1,-speed1);
					}
				}
				else if(!io4)					//�� 
				{
					move(-speed3,speed3+50);
					for(i=0;(i<t3)&&io1;i++)
						delay_ms(1);
					if(!io1)
					{
						move(speed1,speed1);
					}
					else if(!io2)
					{
						move(-speed1,-speed1);
					}
				}															
				//δ��⵽�з���Ѳ��
				else if((b > V3 && b < V5) || (c > V4 && c < V6))
				//if((b > V3 && b < V5) || (c > V4 && c < V6))
				{
					move(-speed6,-speed6);
				}
					else  
				{ 
					move(-speed2,-speed2);
				}  
			}
		}
	}
}
		
void up(void)
{
	move(500,500);
	delay_ms(1000);
	move(-500,500);
	delay_ms(400);
}
			
