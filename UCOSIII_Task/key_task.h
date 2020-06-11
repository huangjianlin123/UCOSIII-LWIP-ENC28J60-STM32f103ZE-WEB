#ifndef key_TASK_H_
#define key_TASK_H_


#include "includes.h"

//任务优先级
#define key_TASK_PRIO		12u
//任务堆栈大小	
#define key_STK_SIZE 		128u
//任务控制块
extern OS_TCB keyTaskTCB;
//任务堆栈	
extern CPU_STK key_TASK_STK[key_STK_SIZE];

void key_task(void *p_arg);

#endif
