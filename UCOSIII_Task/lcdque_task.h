#ifndef lcdque_TASK_H_
#define lcdque_TASK_H_


#include "includes.h"

//�������ȼ�
#define lcdque_TASK_PRIO		9u
//�����ջ��С	
#define lcdque_STK_SIZE 		128u
//������ƿ�
extern OS_TCB lcdqueTaskTCB;
//�����ջ	
extern CPU_STK lcdque_TASK_STK[lcdque_STK_SIZE];

void lcdque_task(void *p_arg);

#endif
