#ifndef __SPI_H
#define __SPI_H
#include "sys.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//SPI���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

//#define LTC2500_RDLB_LOW 			GPIO_ResetBits(GPIOB,GPIO_Pin_9)
//#define LTC2500_RDLB_HIGH		 	GPIO_SetBits(GPIOB,GPIO_Pin_9)

#define DummyByte	((u16)(0xffff)) 
 				  	    													  
void SPI2_Init(void);			 //��ʼ��SPI��
void SPI2_SetSpeed(u8 SpeedSet); //����SPI�ٶ�   
u8 SPI2_ReadWriteByte(u8 TxData);//SPI���߶�дһ���ֽ�
u8 SPI2_ReadByte(void);//SPI���߶�дһ���ֽ�

unsigned int LTC2500Readsg(unsigned short TxData);

u16 SPI2_ReadWrite2Byte(u16 TxData);
unsigned int LTC2500Read(void);
unsigned int GetLTC2500Value(void);
unsigned int GetLTC2500Valuesg(void);
unsigned int LTC2500_Average(u32 times);
unsigned int LTC2500Read32(void);
//u16 SPI2_ReadWriteByte(u16 TxData);//SPI���߶�д�����ֽ�	
//s32 Get_24BitADc(void);


#endif

