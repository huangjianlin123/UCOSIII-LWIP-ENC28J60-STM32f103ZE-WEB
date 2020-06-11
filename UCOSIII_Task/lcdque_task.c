#include "lcdque_task.h"
#include "sys.h"
#include "task.h"
#include "tftlcd.h"
//任务控制块
OS_TCB lcdqueTaskTCB;
//任务堆栈	
CPU_STK lcdque_TASK_STK[lcdque_STK_SIZE];

//led0任务函数
void lcdque_task(void *p_arg)
{
  OS_ERR err;
	OS_MSG_SIZE size;
	char *p;
	while(1)
	{
		p=OSQPend((OS_Q*		)&isr_que,   
									(OS_TICK		)0,
                  (OS_OPT		)OS_OPT_PEND_BLOCKING,
                  (OS_MSG_SIZE*	)&size,	
                  (CPU_TS*		)0,
                  (OS_ERR*		)&err);
		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //延时1s	
		if(FRONT_COLOR==RED)FRONT_COLOR=BLACK;
	  else if(FRONT_COLOR==BLACK)FRONT_COLOR=RED;	
		LCD_ShowString(10,320,tftlcd_data.width,tftlcd_data.height,16,(u8 *)p);
		
		
		
	}
}
