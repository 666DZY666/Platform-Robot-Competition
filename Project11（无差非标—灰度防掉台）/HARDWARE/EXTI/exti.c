#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "adc.h"
#include "stdio.h"
#include "pwm.h"
#include "io.h"
#include "exti.h"
#include "usart.h"
#define speed5 800     //防掉台后退
#define speed6 500     //防掉台后退后旋转
void EXTIX_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);	//使能PORTB时钟

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;				//PC8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 			//设置成下拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);					//初始化GPIOB10
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;				//PC7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 			//设置成下拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);					//初始化GPIOB11
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);		//外部中断，需要使能AFIO时钟

	//GPIOC.8 中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource8);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line8;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;	//上升沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 						//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    //GPIOC.7	  中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource7);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  						//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;			//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
 
}

void EXTI9_5_IRQHandler(void)
{
		int a=0;										//防止台上被对方遮挡触发中断
		while(EXTI1==1&&EXTI2==0)					    //情况1,此判断条件可去除台上误触发中断
		{
			 a=1;
			 move(-200,600);
		}		 
		while(EXTI1==0&&EXTI2==1)						//情况2
		{
			 a=2;
			 move(600,-200);
		}	
		if(EXTI1==1&&EXTI2==1)     						//情况3
		{
			if(a==1) move(200,-550);
			else if(a==2) move(-550,200);
			do
			move(-speed5,-speed5);
			while(EXTI1&&EXTI2);
			move(600,600);
			delay_ms(5);
			move(speed6,-speed6);
			delay_ms(220);
		}
		EXTI_ClearITPendingBit(EXTI_Line8);  //清除LINE8线路挂起位
		EXTI_ClearITPendingBit(EXTI_Line7);  //清除LINE7线路挂起位
}

