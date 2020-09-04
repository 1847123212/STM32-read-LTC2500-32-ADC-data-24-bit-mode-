#include "exti.h"
#include "led.h"
//#include "key.h"
#include "delay.h"
#include "usart.h"
//#include "beep.h"
#include "ltc2500.h"
#include "lcd.h"
#include "spi.h"
#include "filter.h"
//#include "stm32f10x_exti.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������
//�ⲿ�ж� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   
//�ⲿ�ж�0�������

/**
  * @brief  NVIC����
  * @param  ��
  * @retval ��
  */
static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;               
	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);           //�������ȼ�����
	
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;          //�����ж�Դ
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        //�����ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //ʹ���жϼĴ���

    NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  EXTI BUSY�ж�����
  * @param  ��
  * @retval ��
  */
void EXTI_Busy_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
	
    /* ���ú�������NVIC */
    NVIC_Configuration();
	
    /* ��ʼ��GPIO */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	//BUSY���� A0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  								//�������� GPIO_Mode_IN_FLOATING    �������� GPIO_Mode_IPU
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
    /* ��ʼ��EXTI */
    // �����ж��ߵ�����Դ
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0); 

    EXTI_InitStructure.EXTI_Line = EXTI_Line0;            			// �����ж���EXTI0
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;  				// ����Ϊ�ж�ģʽ
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;			//�½��ش����ж�
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;             			// ʹ���ж�
    EXTI_Init(&EXTI_InitStructure);
}

/**
  * @brief  EXTI0���жϷ�����
  * @param  �� 
  * @retval ��
  */
void EXTI0_IRQHandler(void)
{
		unsigned int ADCx;
		double temp;
    if(EXTI_GetITStatus(EXTI_Line0) != RESET) // ȷ��������EXTI0���ж� 
    {
//				ADCx =  filter10();
			
//				ADCx = LTC2500_Average(50);
//				ADCx=GetLTC2500Valuesg();
				ADCx=LTC2500Read32();
				temp=(double)ADCx*9.9782/(16777216-1);// 4.9883/16777216;//Vref = 5v    5.0/16777216      ���� 5.0/16777215 = 0.00000029802324164052257779375182352971    2^24 = 16777216
	
				printf("%d %.9f\r\n",ADCx,temp);//1.0195V 4.9832v 4.8953
			
//				LCD_ShowxNum(124,130,ADCx,8,16,0);//��ʾADC��ֵ  8λ
//				temp=(double)ADCx*4.9883/16777216;//Vref = 5v    5.0/16777216      ���� 5.0/16777215 = 0.00000029802324164052257779375182352971    2^24 = 16777216
//				ADCx=temp;
//				LCD_ShowxNum(124,150,ADCx,1,16,0);//��ʾ��ѹֵ��������
//				temp-=ADCx;
//				temp*=1000000;//С�����6λ
//				LCD_ShowxNum(139,150,temp,6,16,0X80);//��ʾ��ѹֵС������
        EXTI_ClearITPendingBit(EXTI_Line0);// ����жϱ�־λ
    }
}








/*
void EXTIX_Init(void)
{
 
   	EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	�����˿ڳ�ʼ��

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��



   //GPIOE.3	  �ж����Լ��жϳ�ʼ������ �½��ش��� //KEY1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

   //GPIOE.4	  �ж����Լ��жϳ�ʼ������  �½��ش���	//KEY0
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


   //GPIOA.0	  �ж����Լ��жϳ�ʼ������ �����ش��� PA0  WK_UP
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 

  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
 
}

//�ⲿ�ж�0������� 
void EXTI0_IRQHandler(void)
{
	delay_ms(10);//����
	if(WK_UP==1)	 	 //WK_UP����
	{				 
		BEEP=!BEEP;	
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  
}
 

//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY1==0)	 //����KEY1
	{				 
		LED1=!LED1;
	}		 
	EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ  
}

void EXTI4_IRQHandler(void)
{
	delay_ms(10);//����
	if(KEY0==0)	 //����KEY0
	{
		LED0=!LED0;
		LED1=!LED1; 
	}		 
	EXTI_ClearITPendingBit(EXTI_Line4);  //���LINE4�ϵ��жϱ�־λ  
}
*/ 
