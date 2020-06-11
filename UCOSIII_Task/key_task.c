#include "key_task.h"
#include "sys.h"
#include "key.h"
#include "led.h"
#include "task.h"
#include "tftlcd.h"
//任务控制块
OS_TCB keyTaskTCB;
//任务堆栈	
CPU_STK key_TASK_STK[key_STK_SIZE];
u8 mode;
//led0任务函数
void key_task(void *p_arg)
{
	OS_ERR err;
		u8 test[40];
	u8 times = 0;
CPU_SR_ALLOC();
	u8 temp;
	p_arg = p_arg;
	while(1)
	{
    mode=KEY_Scan(0);
		if(mode==KEY_UP){
	    	OSFlagPost((OS_FLAG_GRP*)&event_flag,
								 (OS_FLAGS	  )FLAG_BIT(0),
								 (OS_OPT	  )OS_OPT_POST_FLAG_SET,
								 (OS_ERR*     )&err);
				OSFlagPost((OS_FLAG_GRP*)&event_flag,
								 (OS_FLAGS	  )FLAG_BIT(1),
								 (OS_OPT	  )OS_OPT_POST_FLAG_SET,
								 (OS_ERR*     )&err);
		}
		else if(mode==KEY_DOWN){
          OS_CRITICAL_ENTER();			
					sprintf((char *)test,"this is queue information ");			
          OS_CRITICAL_EXIT();				
			    FRONT_COLOR=BLUE;
					LCD_ShowString(10,300,tftlcd_data.width,tftlcd_data.height,16,"key_down task sending que....\r\n");
			    FRONT_COLOR=RED;
					OSQPost((OS_Q*		)&isr_que,		
					        (void*		)test,
					         (OS_MSG_SIZE)40,
					        (OS_OPT		)OS_OPT_POST_FIFO,
				        	(OS_ERR*	)&err);
		}
		OSTimeDlyHMSM(0,0,0,50,OS_OPT_TIME_HMSM_STRICT,&err); //延时500ms
	}
}
