#ifndef lwip_TASK_H_
#define lwip_TASK_H_


#include "includes.h"

//�������ȼ�
#define lwip_TASK_PRIO		15u
//�����ջ��С	
#define lwip_STK_SIZE 		128u
//������ƿ�
extern OS_TCB lwipTaskTCB;
//�����ջ	
extern CPU_STK lwip_TASK_STK[lwip_STK_SIZE];

void lwip_task(void *p_arg);

#endif
