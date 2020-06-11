#include "led_task.h"
#include "LED.h"
#include "sys.h"
#include "task.h"
#include "tftlcd.h"
//任务控制块
OS_TCB Led0TaskTCB;
//任务堆栈	
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];

//led0任务函数
void led0_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{
	  OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); //延时1s		
		OSFlagPend((OS_FLAG_GRP*)&event_flag,
			 (OS_FLAGS	)FLAG_BIT(0)|FLAG_BIT(1),
				(OS_TICK     )0,
			 (OS_OPT	    )OS_OPT_PEND_FLAG_SET_ALL+OS_OPT_PEND_FLAG_CONSUME,
			 (CPU_TS*     )0,
			 (OS_ERR*	    )&err);
		if(FRONT_COLOR==RED)FRONT_COLOR=BLACK;
	  else if(FRONT_COLOR==BLACK)FRONT_COLOR=RED;	
		LCD_ShowString(10,250,tftlcd_data.width,tftlcd_data.height,16,"Led8 task,keyup get event flag group.\n\r");	
		LED7=1;	
		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //延时200ms
		LED7=0;
	  
	}
}
