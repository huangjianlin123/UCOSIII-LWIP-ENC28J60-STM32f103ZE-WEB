#ifndef START_TASK_H_
#define START_TASK_H_


#include "includes.h"

//�������ȼ�
#define START_TASK_PRIO		3u
//�����ջ��С	
#define START_STK_SIZE 		512u

//������ƿ�
extern OS_TCB StartTaskTCB;
//�����ջ	
extern CPU_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *p_arg);


#endif
