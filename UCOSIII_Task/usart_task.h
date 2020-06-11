#ifndef usart_TASK_H_
#define usart_TASK_H_


#include "includes.h"

//任务优先级
#define usart_TASK_PRIO		16u
//任务堆栈大小	
#define usart_STK_SIZE 		128u
//任务控制块
extern OS_TCB usartTaskTCB;
//任务堆栈	
extern CPU_STK usart_TASK_STK[usart_STK_SIZE];
extern char* usartinfo;
void usart_task(void *p_arg);

#endif
