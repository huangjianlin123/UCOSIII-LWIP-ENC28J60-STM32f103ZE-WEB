#ifndef LED_TASK_H_
#define LED_TASK_H_


#include "includes.h"

//�������ȼ�
#define LED0_TASK_PRIO		5u
//�����ջ��С	
#define LED0_STK_SIZE 		128u
//������ƿ�
extern OS_TCB Led0TaskTCB;
//�����ջ	
extern CPU_STK LED0_TASK_STK[LED0_STK_SIZE];

void led0_task(void *p_arg);

#endif
