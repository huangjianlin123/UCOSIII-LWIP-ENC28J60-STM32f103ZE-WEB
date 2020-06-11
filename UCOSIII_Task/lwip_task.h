#ifndef lwip_TASK_H_
#define lwip_TASK_H_


#include "includes.h"

//任务优先级
#define lwip_TASK_PRIO		15u
//任务堆栈大小	
#define lwip_STK_SIZE 		128u
//任务控制块
extern OS_TCB lwipTaskTCB;
//任务堆栈	
extern CPU_STK lwip_TASK_STK[lwip_STK_SIZE];

void lwip_task(void *p_arg);

#endif
