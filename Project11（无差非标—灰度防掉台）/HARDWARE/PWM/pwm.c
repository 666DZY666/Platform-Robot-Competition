#include "sys.h"
#include "delay.h"	
#include "timer.h" 
#include "pwm.h"
void move(int l_speed,int r_speed)           //l_speed,r_speed�ķ�ΧΪ-300 ~ +300
{                                            //���ٶȴﵽ200~300ʱ����û��̫��ı仯
    if(l_speed>=0&&r_speed>=0)
	{     
		v1=0;
		v2=1;
		v3=0;
		v4=1;
	}
    else if(l_speed>0&&r_speed<0)
	{     
		v1=0;
		v2=1;
		v3=1;
		v4=0;
		r_speed=0-r_speed;
	}
	else if(l_speed<0&&r_speed>0)   
	{     
		v1=1;
		v2=0;
		v3=0;
		v4=1;
		l_speed=0-l_speed;
	}
	else
	{
		v1=1;
		v2=0;
		v3=1;
		v4=0;
		r_speed=0-r_speed;l_speed=0-l_speed;
	}
	TIM_SetCompare3(TIM3,l_speed);
	TIM_SetCompare4(TIM3,r_speed);
}
