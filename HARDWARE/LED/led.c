#include "led.h"

void LED_Init(void)
{
 
  GPIO_InitTypeDef GPIO_InitStructure;        //����GPIO��ʼ���ṹ��
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//������ʹ��,B,C�˿�ʱ��
  //����PC.13�˿�
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);				//�����趨������ʼ��GPIOC13	,�൱���ȶ��ò������ٽ��������뵽��Ӧ��GPIO��
  GPIO_SetBits(GPIOC,GPIO_Pin_0);						 //PC13 �����

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_2 |GPIO_Pin_3 |GPIO_Pin_4|GPIO_Pin_5 |GPIO_Pin_6 |GPIO_Pin_7;				
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);				//�����趨������ʼ��GPIOC13	,�൱���ȶ��ò������ٽ��������뵽��Ӧ��GPIO��
  GPIO_SetBits(GPIOC,GPIO_Pin_1| GPIO_Pin_2|GPIO_Pin_3| GPIO_Pin_4|GPIO_Pin_5 |GPIO_Pin_6 |GPIO_Pin_7);						 

}
 
