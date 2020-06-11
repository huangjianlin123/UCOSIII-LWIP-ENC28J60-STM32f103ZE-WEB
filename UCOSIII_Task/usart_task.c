#include "usart_task.h"
#include "sys.h"
#include "led.h"
#include "usart.h"
#include "task.h"
#include "tftlcd.h"
//任务控制块
OS_TCB usartTaskTCB;
//任务堆栈	
CPU_STK usart_TASK_STK[usart_STK_SIZE];
char* usartinfo;

void usart_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{
	  LCD_ShowString(10,190,tftlcd_data.width,tftlcd_data.height,16,"usart task wait Mutex Sem ...... \n\r");
		OSMutexPend(&Mutex_Sem,0,OS_OPT_PEND_BLOCKING,0,&err);		
		OSTimeDlyHMSM(0,0,0,800,OS_OPT_TIME_HMSM_STRICT,&err); //延时500ms
		if(FRONT_COLOR==RED)FRONT_COLOR=BLACK;
	  else if(FRONT_COLOR==BLACK)FRONT_COLOR=RED;	
		LCD_ShowString(10,210,tftlcd_data.width,tftlcd_data.height,16,"usart task get the Mutex Sem . \n\r");	
		OSMutexPost(&Mutex_Sem,OS_OPT_POST_NO_SCHED,&err);
		OSTimeDlyHMSM(0,0,0,800,OS_OPT_TIME_HMSM_STRICT,&err); //延时500ms
		
	}
}
