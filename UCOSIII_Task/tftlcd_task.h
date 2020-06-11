#ifndef tftlcd_TASK_H_
#define tftlcd_TASK_H_


#include "includes.h"

//任务优先级
#define tftlcd_TASK_PRIO		6u
//任务堆栈大小	
#define tftlcd_STK_SIZE 		128u
//任务控制块
extern OS_TCB tftlcdTaskTCB;
//任务堆栈	
extern CPU_STK tftlcd_TASK_STK[tftlcd_STK_SIZE];
extern char* lcdinfo;
void tftlcd_task(void *p_arg);

#endif
