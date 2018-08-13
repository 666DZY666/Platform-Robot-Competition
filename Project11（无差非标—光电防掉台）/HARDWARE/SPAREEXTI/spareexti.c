#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "adc.h"
#include "stdio.h"
#include "pwm.h"
#include "io.h"
#include "exti.h"
#include "usart.h"
#define speed7 650     //����̨���ˣ����ã�
#define speed8 600     //����̨���˺���ת�����ã�
void spareexti(void)
{
	if(EXTI1&&EXTI2&&io1&&io2)
	{
		delay_ms(10);
		if(EXTI1&&EXTI2&&io1&&io2)
		{
			do
			move(-speed7,-speed7);
			while(EXTI1||EXTI2);
			move(speed8,-speed8);
			delay_ms(140);
		}
	}
}
