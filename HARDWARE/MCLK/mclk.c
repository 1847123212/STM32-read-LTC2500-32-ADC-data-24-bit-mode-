#include "stm32f10x.h"
#include "mclk.h"
void freq_init(void)
{
 
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);	


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
	
	RCC_MCOConfig(RCC_MCO_HSE); //RCC_MCO_NoClock --- ��ʱ�����
								//RCC_MCO_SYSCLK --- ���ϵͳʱ��(SysCLK) 
								//RCC_MCO_HSI --- ����ڲ������8MHzRC����ʱ��(HSI) 
								//RCC_MCO_HSE --- ����ⲿ����ʱ��(HSE) 
								//RCC_MCO_PLLCLK_Div2 --- ���PLL��Ƶ��Ķ���Ƶʱ��(PLLCLK/2)		
}



