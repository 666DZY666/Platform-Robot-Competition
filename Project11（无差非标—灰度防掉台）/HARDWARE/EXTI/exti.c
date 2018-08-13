#include "delay.h"
#include "sys.h"
#include "timer.h"
#include "adc.h"
#include "stdio.h"
#include "pwm.h"
#include "io.h"
#include "exti.h"
#include "usart.h"
#define speed5 800     //����̨����
#define speed6 500     //����̨���˺���ת
void EXTIX_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);	//ʹ��PORTBʱ��

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;				//PC8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 			//���ó���������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);					//��ʼ��GPIOB10
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_7;				//PC7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 			//���ó���������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);					//��ʼ��GPIOB11
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);		//�ⲿ�жϣ���Ҫʹ��AFIOʱ��

	//GPIOC.8 �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource8);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line8;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;	//�����ش���
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 						//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    //GPIOC.7	  �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource7);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  						//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;			//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
 
}

void EXTI9_5_IRQHandler(void)
{
		int a=0;										//��ֹ̨�ϱ��Է��ڵ������ж�
		while(EXTI1==1&&EXTI2==0)					    //���1,���ж�������ȥ��̨���󴥷��ж�
		{
			 a=1;
			 move(-200,600);
		}		 
		while(EXTI1==0&&EXTI2==1)						//���2
		{
			 a=2;
			 move(600,-200);
		}	
		if(EXTI1==1&&EXTI2==1)     						//���3
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
		EXTI_ClearITPendingBit(EXTI_Line8);  //���LINE8��·����λ
		EXTI_ClearITPendingBit(EXTI_Line7);  //���LINE7��·����λ
}

