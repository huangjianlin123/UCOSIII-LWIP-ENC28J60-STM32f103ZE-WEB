#include "tftlcd_task.h"
#include "led.h"
#include "sys.h"
#include "tftlcd.h"
#include "task.h"
//任务控制块
OS_TCB tftlcdTaskTCB;
//任务堆栈	
CPU_STK tftlcd_TASK_STK[tftlcd_STK_SIZE];
char* lcdinfo;
int tcnt=0;
//led0任务函数
void tftlcd_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{
  OSTimeDlyHMSM(0,0,0,400,OS_OPT_TIME_HMSM_STRICT,&err); //延时400ms	
	if(FRONT_COLOR==RED)FRONT_COLOR=BLACK;
	else if(FRONT_COLOR==BLACK)FRONT_COLOR=RED;	
	LCD_ShowString(10,150,tftlcd_data.width,tftlcd_data.height,16,"LCD task wait Mutex Sem ...... \n\r");	
	OSMutexPend(&Mutex_Sem,0,OS_OPT_PEND_BLOCKING,0,&err);
	
	LCD_ShowString(10,170,tftlcd_data.width,tftlcd_data.height,16,"LCD task get Mutex Sem \n\r");		
	OSMutexPost(&Mutex_Sem,OS_OPT_POST_NO_SCHED,&err);
	OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err); //延时500ms
	//tcnt++;	
		
	}
}
