#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
//#include "w25qxx.h"	 
#include "mclk.h"
#include "ltc2500.h" 
#include "exti.h"
#include "pwm.h" 
/************************************************
 LTC2500-32  STM32
 24λģʽ
 A8 PWM
 �������
 ���ߣ����� @WangJie
 ��λ��CISD of HDU
 ������ԭ��SPI�������������б�д
************************************************/
 
 				 	
//Ҫд�뵽W25Q64���ַ�������
//const u8 TEXT_Buffer[]={"ELITE STM32 SPI TEST"};
//#define SIZE sizeof(TEXT_Buffer)
 int main(void)
 {	 

	u16 pwmval=100; 
//	freq_init();
	delay_init();	    	 //��ʱ������ʼ��	  
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
//	NVIC_Configuration();
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
//	LCD_Init();			   	//��ʼ��LCD 	
	
	TIM1_PWM_Init(719,0);//����Ƶ��PWMƵ��=72000/(899+1)=80Khz /71=1MHz��Ӧpwmval=40 /719=100KHz /143=500KHz  120  /89=800khz 80/102=700khz/119=600khz/79=900k
	//84=850K  359=200k 179=400k

	TIM_SetCompare1(TIM1,pwmval);

	LED0=0;//�ȵ������
	
//	delay_ms(50);
	EXTI_Busy_Config();
//	delay_ms(10);
	LTC2500_Init();
	while(1)	//�ȴ��жϲ���
	{
		//delay_ms(10);
	
	}
	
}


