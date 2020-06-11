#ifndef _TASK_H_
#define _TASK_H_

#include "start_task.h"

#include "led_task.h"

#include "lwip_task.h"
#include "lcdque_task.h"
#include "tftlcd_task.h"
#include "key_task.h"
#include "usart_task.h"
extern OS_FLAG_GRP event_flag;
extern OS_SEM SYNC_SEM;
extern OS_MUTEX Mutex_Sem;
extern OS_Q isr_que;
#define FLAG_BIT(n)  1<<n
#endif
