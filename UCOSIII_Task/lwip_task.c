#include "lwip_task.h"
#include "LED.h"
#include "sys.h"
#include "delay.h"
#include "task.h"
#include "tftlcd.h"
//任务控制块
OS_TCB lwipTaskTCB;
//任务堆栈	
CPU_STK lwip_TASK_STK[lwip_STK_SIZE];

//led0任务函数
void lwip_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{

	//	if(FRONT_COLOR==RED)FRONT_COLOR=BLACK;
	 // else if(FRONT_COLOR==BLACK)FRONT_COLOR=RED;	
		//LCD_ShowString(10,230,tftlcd_data.width,tftlcd_data.height,16,"lwip task get the flag \n\r");	
		
    LWIP_Polling();  	
		delay_ms(1); 
	}
}
