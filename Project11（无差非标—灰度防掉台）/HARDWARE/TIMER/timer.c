#include "timer.h"
void TIM3_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	//PA��PB����ʱ��3ʱ������
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
 	//PA6��PA7��PB0��PB1������� 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //����(PWM)�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                                                   	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;        //PC4��5|PA6��7���ٶȷ���
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	//��ʱ��3��4·PWM�����CH1��CH4��
	TIM_TimeBaseStructure.TIM_Period = arr; 						//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 						//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 					//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 				//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 				//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 	//�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; 								//���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 		//�������:TIM����Ƚϼ��Ը�
	
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM3, ENABLE); 							//ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	TIM_Cmd(TIM3, ENABLE);  										//ʹ��TIM1
}

