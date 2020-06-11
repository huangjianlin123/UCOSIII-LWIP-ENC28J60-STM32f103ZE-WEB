#include "stm32f10x.h"                  // Device header
#include "usart.h"
#include "includes.h"
#include "task.h"
#include "LED.h"
#include "delay.h"


#include "key.h"
#include "mysys.h"

#include "rtc.h" 
#include "adc.h"
#include "tsensor.h"
#include "enc28j60.h"			   
#include "math.h" 	
#include "string.h"	 
#include "tftlcd.h"
#include "lwip/init.h"
#include "lwip/ip.h"
#include "lwip/dhcp.h"
#include "lwip/tcp_impl.h"
#include "lwip/ip_frag.h"
#include "netif/etharp.h"
#include "netif/ethernetif.h"
#include "arch/sys_arch.h"

#include "lwip_demo.h"



#define CLOCKTICKS_PER_MS 10    //定义时钟节拍
static ip_addr_t ipaddr, netmask, gw; //定义IP地址
struct netif enc28j60_netif;  //定义网络接口
u32_t last_arp_time;			
u32_t last_tcp_time;	
u32_t last_ipreass_time;
u32_t input_time;

//LWIP查询
void LWIP_Polling(void){
	
// if(timer_expired(&input_time,5)) //接收包，周期处理函数
 // {
    ethernetif_input(&enc28j60_netif); 
 // }
  if(timer_expired(&last_tcp_time,TCP_TMR_INTERVAL/CLOCKTICKS_PER_MS))//TCP处理定时器处理函数
  {
	 tcp_tmr();
  }
  if(timer_expired(&last_arp_time,ARP_TMR_INTERVAL/CLOCKTICKS_PER_MS))//ARP处理定时器
  {
	etharp_tmr();
  }
	if(timer_expired(&last_ipreass_time,IP_TMR_INTERVAL/CLOCKTICKS_PER_MS)){ //IP重新组装定时器
		ip_reass_tmr();
  }
  #if LWIP_DHCP>0			   					
  if(timer_expired(&last_dhcp_fine_time,DHCP_FINE_TIMER_MSECS/CLOCKTICKS_PER_MS))
  {
	 dhcp_fine_tmr();
  }
  if(timer_expired(&last_dhcp_coarse_time,DHCP_COARSE_TIMER_MSECS/CLOCKTICKS_PER_MS))
  {
	dhcp_coarse_tmr();
  }  
  #endif
  
}
void BSP_init(void);
 
int main()
{  
	OS_ERR err;
	CPU_SR_ALLOC();
	BSP_init();
	
	OSInit(&err); 
	OS_CRITICAL_ENTER();
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//任务控制块
				 (CPU_CHAR	* )"start task", 		//任务名字
                 (OS_TASK_PTR )start_task, 			//任务函数
                 (void		* )0,					//传递给任务函数的参数
                 (OS_PRIO	  )START_TASK_PRIO,     //任务优先级
                 (CPU_STK   * )&START_TASK_STK[0],	//任务堆栈基地址
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//任务堆栈深度限位
                 (CPU_STK_SIZE)START_STK_SIZE,		//任务堆栈大小
                 (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,					//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
                 (OS_ERR 	* )&err);				//存放该函数错误时的返回值
	OS_CRITICAL_EXIT();
	OSStart(&err);
	
	while(1){}
}



void BSP_init(void)
{
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为9600
 	LED_Init();			     //LED端口初始化
	RTC_Init();				//初始化RTC
	Adc_Init();				//初始化ADC	  
	TFTLCD_Init();			//LCD初始化
	KEY_Init();
	FRONT_COLOR=RED;
	LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,16,"LWIP UCOSIII STM32F103ZE Test!");	
	
	FRONT_COLOR=BLUE;
	IP4_ADDR(&ipaddr, 10, 128, 209, 216);  		//设置本地ip地址
	IP4_ADDR(&gw, 10, 128, 209, 254);			//网关
	IP4_ADDR(&netmask, 255, 255, 255, 0);		//子网掩码	 

   
   init_lwip_timer();  //初始化LWIP定时器
	//初始化LWIP协议栈,执行检查用户所有可配置的值，初始化所有的模块
	lwip_init(); 
	//添加网络接口
	while((netif_add(&enc28j60_netif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &ethernet_input)==NULL))
	{
			delay_ms(200);
	}
	printf("ENC28J60 Init OK!\r\n");
	LCD_ShowString(10,50,tftlcd_data.width,tftlcd_data.height,16,"                    ");
	LCD_ShowString(10,70,tftlcd_data.width,tftlcd_data.height,16,"IP:10.128.209.216");
	LCD_ShowString(10,90,tftlcd_data.width,tftlcd_data.height,16,"MASK:255.255.255.0");
	LCD_ShowString(10,110,tftlcd_data.width,tftlcd_data.height,16,"GATEWAY:10.128.209.254");
	FRONT_COLOR=RED;
	//注册默认的网络接口
	netif_set_default(&enc28j60_netif);
	//建立网络接口用于处理通信
 	netif_set_up(&enc28j60_netif); 


	lwip_demo_init();		//初始化lwip_demo
}


