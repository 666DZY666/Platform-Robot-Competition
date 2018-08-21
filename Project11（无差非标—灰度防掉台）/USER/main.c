/*****************DZY*******************
作者：戴镇原
文件名：main.c
创建日期：2018.8.8
维护人：戴镇原
维护日期：2018.8.8
维护日期：2018.8.18，改善建议：1、增加车载端本地灰度初始化（显示屏+按键）；2、调试边角处理；3、调试边沿处理改进（边沿后退旋转时若周围检测到敌方就立即进攻）；
描述：机器人对抗赛程序
******************DZY********************/
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

//速度大小宏定义
#define speed1		  650      //正面攻击速度
#define speed2		  480      //（安全区）巡逻
#define speed3	    550      //左右检测旋转
#define speed4      898      //边沿后退
#define speed5      650      //边沿旋转
#define speed6		  400      //（非安全区）巡逻
//#define speed7		  550      //边角旋转
//#define speed8		  898      //边角后退
#define speed9			100      //刹车
//延时宏定义
#define t1		      300      //边沿后退
#define t2          180      //边沿旋转
#define t3          600      //检测旋转
#define t4          450      //边沿后退（进攻时）
//#define t5		      400      //边角旋转
//#define t6		      300      //边角后退
#define t7		      5        //刹车
//灰度阈值宏定义
#define V1 1750							 //前——安全区
#define V3 1450              //后左——安全区
#define V4 1450							 //后右——安全区
#define V2 2300              //前——边沿
#define V5 1850              //后左——边沿
#define V6 1850							 //后右——边沿
//#define V7 3010              //前——边角
//#define V8 2500							 //后左——边角
//#define V9 2100							 //后右——边角
//灰度差值宏定义
#define f1 5
#define f2 5
#define f3 5
#define f4 5
//#define f5 5
//#define f6 5
//#define f7 5
//#define f8 5
//AD(灰度)宏定义
#define AVERAGE_TIMES 2
#define a Get_Adc_Average(0,AVERAGE_TIMES)//前——灰度
#define b Get_Adc_Average(3,AVERAGE_TIMES)//后左
#define c Get_Adc_Average(2,AVERAGE_TIMES)//后右
//变量定义
int i=0,f=1;
//函数声明
void up(void);
//主函数(非RTOS)
int main(void)
{ 
	delay_init();	    	        	//延时函数初始化	 
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
  IO_Init();                  	//GPIO初始化
  TIM3_PWM_Init(899,0);	        //PWM初始化（速度最大值为899）
  Adc_Init();		        				//adc初始化	
	while(io4);										//软启动	
  up();		                      //进入比赛场地区域       	
//	EXTIX_Init();			
  //主循环
	while(1)
	{	
		//正向（车为双向（头），每到边沿触发防出区域动作后换向）
		if(f)
		{
			//台边（含三种情况，分别为车靠近场地左边、右边、中间）
			if(a > V2)
			{
				  //边角1
//				if((a > V7 && b > V8) && b - c > f1)
//				{
//					move(-speed7,speed7);
//					delay_ms(t5);
//					move(-speed8,-speed8);
//					delay_ms(t6);
//					move(speed9,speed9);
//					delay_ms(t7);
//					f = !f;
//				}
//				//边角2
//				else if((a > V7 && c > V9) && b - c < f1)
//				{
//					move(speed7,-speed7);
//					delay_ms(t5);
//					move(-speed8,-speed8);
//					delay_ms(t6);
//					move(speed9,speed9);
//					delay_ms(t7);
//					f = !f;
//				}
				//else if(a > V2 && b - c > f1)
				//靠左
				if(a > V2 && b - c > f1)
				{
					if(a > b || a > c)
					{
						if((!io1)||(!io2))
						{
							move(-speed4,-speed4);
							//前面检测到敌人进攻时到边沿，速度较大，后退时间更长
							//防出区域动作时若周围检测到敌方，立即终止动作检测进攻
//							for(i = 0;i < t4 && io2 && io3 && io4;i++)
//								delay_ms(1);
							delay_ms(t4);
						}
						else
						{
							move(-speed4,-speed4);
							//反之较短
//							for(i = 0;i < t1 && io2 && io3 && io4;i++)
//								delay_ms(1);
							delay_ms(t1);
						}
						//刹车
						move(speed9,speed9);
						delay_ms(t7);
						//后退后旋转
						move(-speed5,speed5);
//						for(i = 0;i < t2 && io2 && io3 && io4;i++)
//							delay_ms(1);	
						delay_ms(t2);		
						//换向标志
						f = !f;						
					}
				}
				//靠右
				else if(a > V2 && c - b > f2)
				{
					if(a > b || a > c)
					{
						if((!io1)||(!io2))
						{
							move(-speed4,-speed4);
//							for(i = 0;i < t4 && io2 && io3 && io4;i++)
//								delay_ms(1);
							delay_ms(t4);
						}
						else
						{
							move(-speed4,-speed4);
//							for(i = 0;i < t1 && io2 && io3 && io4;i++)
//								delay_ms(1);
							delay_ms(t1);
						}
						move(speed9,speed9);
						delay_ms(t7);
						move(speed5,-speed5);
//						for(i = 0;i < t2 && io2 && io3 && io4;i++)
//							delay_ms(1);	
						delay_ms(t2);
						f = !f;	
					}
				}
				//中间
				else if(a > V2)
				{
					if(a > b || a > c)
					{
						if((!io1)||(!io2))
						{
							move(-speed4,-speed4);
//							for(i = 0;i < t4 && io2 && io3 && io4;i++)
//								delay_ms(1);
							delay_ms(t4);
						}
						else
						{
							move(-speed4,-speed4);
//							for(i = 0;i < t1 && io2 && io3 && io4;i++)
//								delay_ms(1);
							delay_ms(t1);
						}
						move(speed9,speed9);
						delay_ms(t7);
						f = !f;	
					}
				}
			}
			//台中	       
				//正向
			if(f)
			{
				//检测到敌方，攻击
				if(!io1)	         		//前
				{
					move(speed1,speed1);
					f = 1;
				}
				else if(!io2)			    //后
				{
					move(-speed1,-speed1);
					f = 0;
				}
				else if(!io3)  			  //左                        	  
				{
					move(-speed3,speed3+50);
					//（可控）检测旋转（旋转过程中若前|后检测到就立即进攻，未检测到则转到最大角度）
					for(i = 0;i < t3 && io1 && io2;i++)
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
				else if(!io4)					//右 
				{
					move(speed3+50,-speed3);
					for(i = 0;i < t3 && io1 && io2;i++)
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
				//未检测到敌方，巡逻
					//非安全区减速
				else if(a > V1 && a < V2)
				//if(a > V1 && a < V2)
				{
					move(speed6,speed6);
				}
					//安全区常速
				else  
				{ 
					move(speed2,speed2);
				}  
			}
				//反向
			else
			{
				//检测到敌方，攻击
				if(!io1)	         		//前
				{
					move(speed1,speed1);
					f = 1;
				}
				else if(!io2)			   //后
				{
					move(-speed1,-speed1);
					f = 0;
				}
				else if(!io3)  			 //左                        	  
				{
					move(speed3+50,-speed3);
					for(i = 0;i < t3 && io1 && io2;i++)
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
				else if(!io4)					//右 
				{
					move(-speed3,speed3+50);
					for(i = 0;i < t3 && io1 && io2;i++)
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
				//未检测到敌方，巡逻
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
		//反向（大致同上，注意速度方向调整。防出区域、左右检测旋转等速度方向注意调整！）
		else
		{
			//台边
			if(b > V5 || c > V6)
			{
//				if((a > V7 && c > V9) && b - c < f1)
//				{
//					move(-speed7,speed7);
//					delay_ms(t5);
//					move(speed8,speed8);
//					delay_ms(t6);
//					move(-speed9,-speed9);
//					delay_ms(t7);
//				}
//				else if((a > V7 && b > V8) && b - c > f1)
//				{
//					move(speed7,-speed7);
//					delay_ms(t5);
//					move(speed8,speed8);
//					delay_ms(t6);
//					move(-speed9,-speed9);
//					delay_ms(t7);
//				}
//				else if((b > V5 || c > V6) && b - c > f3)
				if((b > V5 || c > V6) && b - c > f3)
				{
					if(b > a || c > a)
					{
						if((!io1)||(!io2))
						{
							move(speed4,speed4);
//							for(i=0;i < t4 && io1 && io3 && io4;i++)
//								delay_ms(1);
							delay_ms(t4);
						}
						else
						{
							move(speed4,speed4);
//							for(i=0;i < t1 && io1 && io3 && io4;i++)
//								delay_ms(1);
							delay_ms(t1);
						}
						move(-speed9,-speed9);
						delay_ms(t7);
						move(speed5,-speed5);
//						for(i=0;i < t2 && io1 && io3 && io4;i++)
//							delay_ms(1);
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
//							for(i=0;i < t4 && io1 && io3 && io4;i++)
//								delay_ms(1);
							delay_ms(t4);
						}
						else
						{
							move(speed4,speed4);
//							for(i=0;i < t1 && io1 && io3 && io4;i++)
//								delay_ms(1);
							delay_ms(t1);
						}
						move(-speed9,-speed9);
						delay_ms(t7);
						move(-speed5,speed5);
//						for(i=0;i < t2 && io1 && io3 && io4;i++)
//							delay_ms(1);
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
//							for(i=0;i < t4 && io1 && io3 && io4;i++)
//								delay_ms(1);
							delay_ms(t4);
						}
						else
						{
							move(speed4,speed4);
//							for(i=0;i < t1 && io1 && io3 && io4;i++)
//								delay_ms(1);
							delay_ms(t1);
						}
						move(-speed9,-speed9);
						delay_ms(t7);
						f = !f;
					}
				}
			}
			//台中	
				//正向
			if(f)
			{
				//检测到敌方，攻击
				if(!io1)	         		//前
				{
					move(speed1,speed1);
					f = 1;
				}
				else if(!io2)			   //后
				{
					move(-speed1,-speed1);
					f = 0;
				}
				else if(!io3)  			 //左                        	  
				{
					move(-speed3,speed3+50);
					for(i = 0;i < t3 && io1 && io2;i++)
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
				else if(!io4)					//右 
				{
					move(speed3+50,-speed3);
					for(i = 0;i < t3 && io1 && io2;i++)
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
				//未检测到敌方，巡逻
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
				//反向
			else
			{
				//检测到敌方，攻击
				if(!io1)	         		//前
				{
					move(speed1,speed1);
					f = 1;
				}
				else if(!io2)			   //后
				{
					move(-speed1,-speed1);
					f = 0;
				}
				else if(!io3)  			 //左                        	  
				{
					move(speed3+50,-speed3);
					for(i = 0;i < t3 && io1 && io2;i++)
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
				else if(!io4)					//右 
				{
					move(-speed3,speed3+50);
					for(i = 0;i < t3 && io1 && io2;i++)
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
				//未检测到敌方，巡逻
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
			
