#ifndef __LED_H
#define __LED_H	 
#include "mysys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
#define LED0 PCout(0) 
#define LED1 PCout(1) 
#define LED2 PCout(2)
#define LED3 PCout(3)
#define LED4 PCout(4)
#define LED5 PCout(5)
#define LED6 PCout(6)
#define LED7 PCout(7)
void LED_Init(void);//��ʼ��

		 				    
#endif
