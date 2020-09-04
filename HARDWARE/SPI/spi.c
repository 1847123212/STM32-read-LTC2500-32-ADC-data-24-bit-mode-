#include "spi.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������
//SPI���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 
//������SPIģ��ĳ�ʼ�����룬���ó�����ģʽ������SD Card/W25Q64/NRF24L01						  
//SPI�ڳ�ʼ��
//�������Ƕ�SPI2�ĳ�ʼ��



void SPI2_Init(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );		//PORTBʱ��ʹ�� 
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI2,  ENABLE );		//SPI2ʱ��ʹ�� 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	//PB12 NSS
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;	//B13 SCKB   B14  MISO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  					//PB13/14/15����������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);										//��ʼ��GPIOB

	//RDLB---->LTC2500--RDLB
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;		//RDLB  PB8
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
 	GPIO_ResetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);                        //PB13/14/15����  xiala	
////  Configure MOSI pin as Alternate Function Push Pull
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
//	SPI_Cmd(SPI2, DISABLE);
	SPI_Cmd(SPI2, DISABLE); //�����Ƚ��ܣ��ſ��Ըı�MODE
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;    //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��  
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		                      //����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;		                	//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ 
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		                        //����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ	��
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	                        //����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����   1
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;															//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256  4
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;										//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial = 7;															//CRCֵ����Ķ���ʽ
	
	SPI_Init(SPI2, &SPI_InitStructure);  																	//����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
	SPI_Cmd(SPI2, ENABLE); 																								//ʹ��SPI����
	
//	SPI2_ReadWriteByte(0xff);																						//��������		 
//	LTC2500Readsg(0xffff);

}   
//SPI �ٶ����ú���
//SpeedSet:
//SPI_BaudRatePrescaler_2   2��Ƶ   
//SPI_BaudRatePrescaler_8   8��Ƶ   
//SPI_BaudRatePrescaler_16  16��Ƶ  
//SPI_BaudRatePrescaler_256 256��Ƶ 
  
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPI2->CR1&=0XFFC7;
	SPI2->CR1|=SPI_BaudRatePrescaler;	//����SPI2�ٶ� 
	SPI_Cmd(SPI2,ENABLE); 
} 

//SPIx ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI2_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) 			//���ָ����SPI��־λ�������:���ͻ���ձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPI2, TxData); 																		//ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) 		//���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SPI2); 																	//����ͨ��SPIx������յ�����					    
}

//2���ֽ�
u16 SPI2_ReadWrite2Byte(u16 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) 			//���ָ����SPI��־λ�������:���ͻ���ձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPI2, TxData); 																		//ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) 		//���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SPI2); 																	//����ͨ��SPIx������յ�����					    
}

//16λģʽ�µĶ�ȡת�� ��ȡ32λ
unsigned int LTC2500Read32(void)
{
	u8 i;
	u16 Buffer[2];
	unsigned int adcvalue = 0;
	unsigned int Adcvalue = 0;
//	SPI2_ReadWriteByte(DummyByte);
	for(i=0;i<2;i++)
		{
			Buffer[i]=SPI2_ReadWrite2Byte(DummyByte);
		}
	adcvalue = (unsigned int)Buffer[0]<<16|(unsigned int)Buffer[1];
	Adcvalue = adcvalue>>7;
	Adcvalue = Adcvalue&0x00ffffff;
	return Adcvalue;
}

//8λģʽ�µĶ�ȡת��
//unsigned int LTC2500Read32(void)
//{
//	u8 i;
//	u8 Buffer[4]={0};
//	unsigned int adcvalue = 0;
//	unsigned int Adcvalue = 0;
////	SPI2_ReadWriteByte(DummyByte);
//	for(i=0;i<4;i++)
//		{
//			Buffer[i]=SPI2_ReadWriteByte(DummyByte);
//		}
//	adcvalue = (unsigned int)Buffer[0]<<24|(unsigned int)Buffer[1]<<16|(unsigned int)Buffer[2]<<8|(unsigned int)Buffer[3];
//	Adcvalue = adcvalue>>7;
//	Adcvalue = Adcvalue&0x00ffffff;
//	return Adcvalue;
//}

unsigned int LTC2500Readsg(unsigned short TxData)
{
	unsigned short DATL;	//��16λ
	unsigned short DATH;
	unsigned short retry=0;
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) 			//���ָ����SPI��־λ�������:���ͻ���ձ�־λ
		{
		retry++;
		if(retry>300)return 0;
		}			  
	SPI_I2S_SendData(SPI2, TxData); 																		//ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) 		//���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
		{
		retry++;
		if(retry>300)return 0;
		}	  						    
	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	DATH = SPI_I2S_ReceiveData(SPI2);//��16λ
		
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) 			//���ָ����SPI��־λ�������:���ͻ���ձ�־λ
		{
		retry++;
		if(retry>300)return 0;
		}			  
	SPI_I2S_SendData(SPI2, TxData); 																		//ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) 		//���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
		{
		retry++;
		if(retry>300)return 0;
		}	  						    	
		
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
	DATL = SPI_I2S_ReceiveData(SPI2);//��16λ
	return ( (unsigned int)DATH << 16 | (unsigned int)DATL );
}	


unsigned int GetLTC2500Valuesg(void)
{	
	unsigned int adcvalue = 0;
	unsigned int Adcvalue = 0;
	adcvalue = LTC2500Readsg(0xffff);
	Adcvalue = adcvalue>>7;
	Adcvalue = Adcvalue&0x00ffffff;
	return Adcvalue;	
	
}	

unsigned int LTC2500_Average(u32 times)
{
	unsigned int temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=LTC2500Read32();
		delay_ms(5);
	}
	return temp_val/times;
} 	 






//16bit
//u16 SPI2_ReadWriteByte(u16 TxData)
//{               
//	unsigned char retry=0;                                        
//	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //
//					{
//					retry++;
//					if(retry>200)return 0;
//					}                          
//	SPI_I2S_SendData(SPI2, TxData); //
//	retry=0;

//	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) //
//					{
//					retry++;
//					if(retry>200)return 0;
//					}
//					
//	return SPI_I2S_ReceiveData(SPI2); //                                          
//}       


































