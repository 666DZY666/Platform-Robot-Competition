#include "IO.h"
void IO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	 //使能PA,PD端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);	 //使能PA,PD端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	 //使能PA,PD端口时钟
					 
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU; 		     //上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
//	GPIO_Init(GPIOD, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
//	GPIO_Init(GPIOD, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.8
}
