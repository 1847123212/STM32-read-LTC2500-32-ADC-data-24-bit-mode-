#include "ltc2500.h"
#include "spi.h"
#include "delay.h"
#include "usart.h"
#include "stm32f10x_spi.h"

#define Dummy_Byte		0xFF

void LTC2500_Init(void)
{	
//  GPIO_InitTypeDef GPIO_InitStructure;
//	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );//PORTBʱ��ʹ�� 

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;  // PB12 ���� 
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //������� ��������
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);
// 	GPIO_SetBits(GPIOB,GPIO_Pin_12);
 
//  W25QXX_CS=1;				//SPI FLASH��ѡ��
	SPI2_Init();		   	//��ʼ��SPI
	SPI2_SetSpeed(SPI_BaudRatePrescaler_2);//����Ϊ18Mʱ��,����ģʽ
//	W25QXX_TYPE=W25QXX_ReadID();//��ȡFLASH ID.  

} 

/*
//��ȡ32λADCֵ
s32 SPI_LTC2500_Read(void)
{
  s32 ADCResult=0;
	s32 temp=0, temp0=0, temp1=0,temp2=0, temp3=0;
	
//	 while(1)
//      {
//            //ADC_CS_0;
//            //delayCount(10);
//            if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12))//GPIO_Mode_IPU 																��������
//            {
//                  
//            }
//            else
//            {
//                   break;
//            }
//      }
	
//	temp0 = SPI2_ReadWriteByte(Dummy_Byte);      // 
//  temp1 = SPI2_ReadWriteByte(Dummy_Byte);      // 
//  temp2 = SPI2_ReadWriteByte(Dummy_Byte);      // 
//	temp3 = SPI2_ReadWriteByte(Dummy_Byte);			 //

	temp0 = SPI2_ReadByte();      // 
  temp1 = SPI2_ReadByte();      // 
  temp2 = SPI2_ReadByte();      // 
	temp3 = SPI2_ReadByte();			 //

	temp = (temp0 << 24) | (temp1 << 16) | temp2 << 8 | temp3; 																			//���32λ����
	ADCResult=temp>>7;
	ADCResult=ADCResult&0x00ffffff;
	return ADCResult;

}

*/


//s32 Get_24BitADC(void)
//{
//	int i=0;
//	s32 adcResult=0;
//  s32 ADCResult=0;
//	
//	while(1)
//		{
//					//ADC_CS_0;
//					//delayCount(10);
//					if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4))//GPIO_Mode_IPU ��������
//					{
//								
//					}
//					else
//					{
//								 break;
//					}
//		}
//	
////	for(i=0;i<2;i++)
////	{	
//		SPI2_ReadWriteByte(0xFF);
//		adcResult+=SPI_I2S_ReceiveData(SPI2)<<16;
////	}
//	ADCResult=adcResult>>7;	//����7λ,�Ƴ�CB������
//  ADCResult&=0x00ffffff;	//�߰�λ��0�����λ����0�����õ� ADCResult 24λDB��Чֵ
//	
//	return ADCResult;
//}



