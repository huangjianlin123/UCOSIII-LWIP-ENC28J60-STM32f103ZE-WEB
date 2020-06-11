#ifndef lcdque_TASK_H_
#define lcdque_TASK_H_


#include "includes.h"

//任务优先级
#define lcdque_TASK_PRIO		9u
//任务堆栈大小	
#define lcdque_STK_SIZE 		128u
//任务控制块
extern OS_TCB lcdqueTaskTCB;
//任务堆栈	
extern CPU_STK lcdque_TASK_STK[lcdque_STK_SIZE];

void lcdque_task(void *p_arg);

#endif
