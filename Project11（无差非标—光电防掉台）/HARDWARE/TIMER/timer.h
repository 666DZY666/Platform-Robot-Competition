#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"	  
//void TIM1_PWM_Init(u16 arr,u16 psc);
void TIM3_PWM_Init(u16 arr,u16 psc);
#define v1 PCout(4)
#define v2 PCout(5)
#define v3 PAout(6)
#define v4 PAout(7)
#endif

