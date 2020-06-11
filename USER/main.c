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



#define CLOCKTICKS_PER_MS 10    //����ʱ�ӽ���
static ip_addr_t ipaddr, netmask, gw; //����IP��ַ
struct netif enc28j60_netif;  //��������ӿ�
u32_t last_arp_time;			
u32_t last_tcp_time;	
u32_t last_ipreass_time;
u32_t input_time;

//LWIP��ѯ
void LWIP_Polling(void){
	
// if(timer_expired(&input_time,5)) //���հ������ڴ�����
 // {
    ethernetif_input(&enc28j60_netif); 
 // }
  if(timer_expired(&last_tcp_time,TCP_TMR_INTERVAL/CLOCKTICKS_PER_MS))//TCP����ʱ��������
  {
	 tcp_tmr();
  }
  if(timer_expired(&last_arp_time,ARP_TMR_INTERVAL/CLOCKTICKS_PER_MS))//ARP����ʱ��
  {
	etharp_tmr();
  }
	if(timer_expired(&last_ipreass_time,IP_TMR_INTERVAL/CLOCKTICKS_PER_MS)){ //IP������װ��ʱ��
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
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//������ƿ�
				 (CPU_CHAR	* )"start task", 		//��������
                 (OS_TASK_PTR )start_task, 			//������
                 (void		* )0,					//���ݸ��������Ĳ���
                 (OS_PRIO	  )START_TASK_PRIO,     //�������ȼ�
                 (CPU_STK   * )&START_TASK_STK[0],	//�����ջ����ַ
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//�����ջ�����λ
                 (CPU_STK_SIZE)START_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,					//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
	OS_CRITICAL_EXIT();
	OSStart(&err);
	
	while(1){}
}



void BSP_init(void)
{
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
	RTC_Init();				//��ʼ��RTC
	Adc_Init();				//��ʼ��ADC	  
	TFTLCD_Init();			//LCD��ʼ��
	KEY_Init();
	FRONT_COLOR=RED;
	LCD_ShowString(10,10,tftlcd_data.width,tftlcd_data.height,16,"LWIP UCOSIII STM32F103ZE Test!");	
	
	FRONT_COLOR=BLUE;
	IP4_ADDR(&ipaddr, 10, 128, 209, 216);  		//���ñ���ip��ַ
	IP4_ADDR(&gw, 10, 128, 209, 254);			//����
	IP4_ADDR(&netmask, 255, 255, 255, 0);		//��������	 

   
   init_lwip_timer();  //��ʼ��LWIP��ʱ��
	//��ʼ��LWIPЭ��ջ,ִ�м���û����п����õ�ֵ����ʼ�����е�ģ��
	lwip_init(); 
	//�������ӿ�
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
	//ע��Ĭ�ϵ�����ӿ�
	netif_set_default(&enc28j60_netif);
	//��������ӿ����ڴ���ͨ��
 	netif_set_up(&enc28j60_netif); 


	lwip_demo_init();		//��ʼ��lwip_demo
}


