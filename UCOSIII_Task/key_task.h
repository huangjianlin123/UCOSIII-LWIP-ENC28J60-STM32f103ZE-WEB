#ifndef key_TASK_H_
#define key_TASK_H_


#include "includes.h"

//�������ȼ�
#define key_TASK_PRIO		12u
//�����ջ��С	
#define key_STK_SIZE 		128u
//������ƿ�
extern OS_TCB keyTaskTCB;
//�����ջ	
extern CPU_STK key_TASK_STK[key_STK_SIZE];

void key_task(void *p_arg);

#endif
