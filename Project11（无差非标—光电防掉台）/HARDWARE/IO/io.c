#include "IO.h"
void IO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	 //ʹ��PA,PD�˿�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);	 //ʹ��PA,PD�˿�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);	 //ʹ��PA,PD�˿�ʱ��
					 
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU; 		     //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init(GPIOD, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOD, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.8
}
