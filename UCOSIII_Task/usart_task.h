#ifndef usart_TASK_H_
#define usart_TASK_H_


#include "includes.h"

//�������ȼ�
#define usart_TASK_PRIO		16u
//�����ջ��С	
#define usart_STK_SIZE 		128u
//������ƿ�
extern OS_TCB usartTaskTCB;
//�����ջ	
extern CPU_STK usart_TASK_STK[usart_STK_SIZE];
extern char* usartinfo;
void usart_task(void *p_arg);

#endif
