#include "delay.h"
#include "includes.h"					//ucos ʹ��	  

//CPU_CFG_CRITICAL_METHOD

static u8  fac_us=0;							//us��ʱ������			   
static u16 fac_ms=0;							//ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��
	
//��delay_us/delay_ms��Ҫ֧��OS��ʱ����Ҫ������OS��صĺ궨��ͺ�����֧��
//������3���궨��:
//    delay_osrunning:���ڱ�ʾOS��ǰ�Ƿ���������,�Ծ����Ƿ����ʹ����غ���
//delay_ostickspersec:���ڱ�ʾOS�趨��ʱ�ӽ���,delay_init�����������������ʼ��systick
// delay_osintnesting:���ڱ�ʾOS�ж�Ƕ�׼���,��Ϊ�ж����治���Ե���,delay_msʹ�øò����������������
//Ȼ����3������:
//  delay_osschedlock:��������OS�������,��ֹ����
//delay_osschedunlock:���ڽ���OS�������,���¿�������
//    delay_ostimedly:����OS��ʱ,���������������.

#define delay_osrunning		OSRunning			//OS�Ƿ����б��,0,������;1,������
#define delay_ostickspersec	OSCfg_TickRate_Hz	//OSʱ�ӽ���,��ÿ����ȴ���
#define delay_osintnesting 	OSIntNestingCtr		//�ж�Ƕ�׼���,���ж�Ƕ�״���



//us����ʱʱ,�ر��������(��ֹ���us���ӳ�)
void delay_osschedlock(void)
{
	OS_ERR err; 
	OSSchedLock(&err);							//UCOSIII�ķ�ʽ,��ֹ���ȣ���ֹ���us��ʱ
}

//us����ʱʱ,�ָ��������
void delay_osschedunlock(void)
{	
	OS_ERR err; 
	OSSchedUnlock(&err);						//UCOSIII�ķ�ʽ,�ָ�����
}

//����OS�Դ�����ʱ������ʱ
//ticks:��ʱ�Ľ�����
void delay_ostimedly(u32 ticks)
{
	OS_ERR err; 
	OSTimeDly(ticks,OS_OPT_TIME_PERIODIC,&err);	//UCOSIII��ʱ��������ģʽ

}
 
//systick�жϷ�����,ʹ��ucosʱ�õ�
void SysTick_Handler(void)
{	
	if(delay_osrunning==1)						//OS��ʼ����,��ִ�������ĵ��ȴ���
	{
		OSIntEnter();							//�����ж�
		OSTimeTick();       					//����ucos��ʱ�ӷ������               
		OSIntExit();       	 					//���������л����ж�
	}
}

			   
//��ʼ���ӳٺ���
//��ʹ��OS��ʱ��,�˺������ʼ��OS��ʱ�ӽ���
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
//SYSCLK:ϵͳʱ��
void delay_init()
{
	u32 reload;
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
	fac_us=SystemCoreClock/8000000;				//Ϊϵͳʱ�ӵ�1/8  
	reload=SystemCoreClock/8000000;				//ÿ���ӵļ������� ��λΪK	   
	reload*=1000000/delay_ostickspersec;		//����delay_ostickspersec�趨���ʱ��
												//reloadΪ24λ�Ĵ���,���ֵ:16777216,��72M��,Լ��1.86s����	
	fac_ms=1000/delay_ostickspersec;			//����OS������ʱ�����ٵ�λ	   

	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	//����SYSTICK�ж�
	SysTick->LOAD=reload; 						//ÿ1/delay_ostickspersec���ж�һ��	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	//����SYSTICK    
}								    


//��ʱnus
//nusΪҪ��ʱ��us��.		    								   
void delay_us(u32 nus)
{		
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;					//LOAD��ֵ	    	 
	ticks=nus*fac_us; 							//��Ҫ�Ľ�����	  		 
	tcnt=0;
	delay_osschedlock();						//��ֹOS���ȣ���ֹ���us��ʱ
	told=SysTick->VAL;        					//�ս���ʱ�ļ�����ֵ
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;		//����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;				//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
		}  
	}
	delay_osschedunlock();						//�ָ�OS����									    
}

//��ʱnms
//nms:Ҫ��ʱ��ms��
void delay_ms(u16 nms)
{	
	if(delay_osrunning&&delay_osintnesting==0)	//���OS�Ѿ�������,���Ҳ������ж�����(�ж����治���������)	    
	{		 
		if(nms>=fac_ms)							//��ʱ��ʱ�����OS������ʱ������ 
		{ 
   			delay_ostimedly(nms/fac_ms);		//OS��ʱ
		}
		nms%=fac_ms;							//OS�Ѿ��޷��ṩ��ôС����ʱ��,������ͨ��ʽ��ʱ    
	}
	delay_us((u32)(nms*1000));					//��ͨ��ʽ��ʱ  
}




