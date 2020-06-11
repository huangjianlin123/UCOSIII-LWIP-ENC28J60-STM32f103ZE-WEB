#include "start_task.h"
#include "led_task.h"
#include "lwip_task.h"
#include "tftlcd_task.h"
#include "usart_task.h"
#include "task.h"
#include "key_task.h"
#include "lcdque_task.h"
OS_FLAG_GRP event_flag;
OS_SEM SYNC_SEM;
OS_Q isr_que;

OS_MUTEX Mutex_Sem;
//������ƿ�
OS_TCB StartTaskTCB;
//�����ջ	
CPU_STK START_TASK_STK[START_STK_SIZE];
//��ʼ������
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//ͳ������                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//���ʹ���˲����жϹر�ʱ��
    CPU_IntDisMeasMaxCurReset();	
#endif
	
#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
	 //ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		
	
	OS_CRITICAL_ENTER();	//�����ٽ���
	/*sem*/
	OSSemCreate ((OS_SEM*	)&SYNC_SEM,
                 (CPU_CHAR*	)"SYNC_SEM",
                 (OS_SEM_CTR)0,		
                 (OS_ERR*	)&err);
	/*mutexsem*/							 
	OSMutexCreate((OS_MUTEX*)&Mutex_Sem,
								(CPU_CHAR*)"Mutex_Sem",
								&err);
	/*event flag*/							
	OSFlagCreate((OS_FLAG_GRP *)&event_flag,
								(CPU_CHAR *)"event flag",
								(OS_FLAGS)0x00,
								(OS_ERR *)&err
								);						
	OSQCreate((OS_Q *)&isr_que,
						(CPU_CHAR *)"isr_que",
						(OS_MSG_QTY)5,
						(OS_ERR *)&err);	


	OSTaskCreate((OS_TCB 	* )&Led0TaskTCB,		
			 (CPU_CHAR	* )"led7 task", 		
							 (OS_TASK_PTR )led0_task, 			
							 (void		* )0,					
							 (OS_PRIO	  )LED0_TASK_PRIO,     
							 (CPU_STK   * )&LED0_TASK_STK[0],	
							 (CPU_STK_SIZE)LED0_STK_SIZE/10,	
							 (CPU_STK_SIZE)LED0_STK_SIZE,		
							 (OS_MSG_QTY  )0,					
							 (OS_TICK	  )0,					
							 (void   	* )0,					
							 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
							 (OS_ERR 	* )&err);			
							 
	OSTaskCreate((OS_TCB 	* )&lwipTaskTCB,									
		 (CPU_CHAR	* )"lwip task", 		
						 (OS_TASK_PTR )lwip_task, 			
						 (void		* )0,					
						 (OS_PRIO	  )lwip_TASK_PRIO,     
						 (CPU_STK   * )&lwip_TASK_STK[0],	
						 (CPU_STK_SIZE)lwip_STK_SIZE/10,	
						 (CPU_STK_SIZE)lwip_STK_SIZE,		
						 (OS_MSG_QTY  )0,					
						 (OS_TICK	  )0,					
						 (void   	* )0,					
						 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
						 (OS_ERR 	* )&err);		
						 
	OSTaskCreate((OS_TCB 	* )&tftlcdTaskTCB,									
		 (CPU_CHAR	* )"tftlcd task", 		
						 (OS_TASK_PTR )tftlcd_task, 			
						 (void		* )0,					
						 (OS_PRIO	  )tftlcd_TASK_PRIO,     
						 (CPU_STK   * )&tftlcd_TASK_STK[0],	
						 (CPU_STK_SIZE)tftlcd_STK_SIZE/10,	
						 (CPU_STK_SIZE)tftlcd_STK_SIZE,		
						 (OS_MSG_QTY  )0,					
						 (OS_TICK	  )0,					
						 (void   	* )0,					
						 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
						 (OS_ERR 	* )&err);			
						 
	OSTaskCreate((OS_TCB 	* )&usartTaskTCB,									
		 (CPU_CHAR	* )"usart task", 		
						 (OS_TASK_PTR )usart_task, 			
						 (void		* )0,					
						 (OS_PRIO	  )usart_TASK_PRIO,     
						 (CPU_STK   * )&usart_TASK_STK[0],	
						 (CPU_STK_SIZE)usart_STK_SIZE/10,	
						 (CPU_STK_SIZE)usart_STK_SIZE,		
						 (OS_MSG_QTY  )0,					
						 (OS_TICK	  )0,					
						 (void   	* )0,					
						 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
						 (OS_ERR 	* )&err);		
	OSTaskCreate((OS_TCB 	* )&keyTaskTCB,									
		 (CPU_CHAR	* )"key task", 		
						 (OS_TASK_PTR )key_task, 			
						 (void		* )0,					
						 (OS_PRIO	  )key_TASK_PRIO,     
						 (CPU_STK   * )&key_TASK_STK[0],	
						 (CPU_STK_SIZE)key_STK_SIZE/10,	
						 (CPU_STK_SIZE)key_STK_SIZE,		
						 (OS_MSG_QTY  )0,					
						 (OS_TICK	  )0,					
						 (void   	* )0,					
						 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
						 (OS_ERR 	* )&err);		
	OSTaskCreate((OS_TCB 	* )&lcdqueTaskTCB,									
		 (CPU_CHAR	* )"lcdque task", 		
						 (OS_TASK_PTR )lcdque_task, 			
						 (void		* )0,					
						 (OS_PRIO	  )lcdque_TASK_PRIO,     
						 (CPU_STK   * )&lcdque_TASK_STK[0],	
						 (CPU_STK_SIZE)lcdque_STK_SIZE/10,	
						 (CPU_STK_SIZE)lcdque_STK_SIZE,		
						 (OS_MSG_QTY  )0,					
						 (OS_TICK	  )0,					
						 (void   	* )0,					
						 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
						 (OS_ERR 	* )&err);							 
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//����ʼ����							 
	OS_CRITICAL_EXIT();	//�����ٽ���
}
