#ifndef tftlcd_TASK_H_
#define tftlcd_TASK_H_


#include "includes.h"

//�������ȼ�
#define tftlcd_TASK_PRIO		6u
//�����ջ��С	
#define tftlcd_STK_SIZE 		128u
//������ƿ�
extern OS_TCB tftlcdTaskTCB;
//�����ջ	
extern CPU_STK tftlcd_TASK_STK[tftlcd_STK_SIZE];
extern char* lcdinfo;
void tftlcd_task(void *p_arg);

#endif
