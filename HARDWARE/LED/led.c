#include "led.h"

void LED_Init(void)
{
 
  GPIO_InitTypeDef GPIO_InitStructure;        //定义GPIO初始化结构体
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//必须先使能,B,C端口时钟
  //配置PC.13端口
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);				//根据设定参数初始化GPIOC13	,相当于先定好参数，再将参数输入到相应的GPIO口
  GPIO_SetBits(GPIOC,GPIO_Pin_0);						 //PC13 输出高

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_2 |GPIO_Pin_3 |GPIO_Pin_4|GPIO_Pin_5 |GPIO_Pin_6 |GPIO_Pin_7;				
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);				//根据设定参数初始化GPIOC13	,相当于先定好参数，再将参数输入到相应的GPIO口
  GPIO_SetBits(GPIOC,GPIO_Pin_1| GPIO_Pin_2|GPIO_Pin_3| GPIO_Pin_4|GPIO_Pin_5 |GPIO_Pin_6 |GPIO_Pin_7);						 

}
 
