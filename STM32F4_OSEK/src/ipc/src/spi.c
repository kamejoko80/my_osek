/*
 *  Copyright (C) : 2016
 *  File name     : spi.c
 *	Author        : Dang Minh Phuong
 *  Email         : kamejoko80@yahoo.com
 *
 *  This program is free software, you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "spi.h"
#include "ipc.h"
#include "os.h"

/*
 * Hardware connection description
 *
 * SPI bus :
 *
 *        Master               Slaver
 *
 *       SCK  (PA5)  ------>  SCK  (PA5)
 *       MISO (PA6)  <------  MISO (PA6)
 *       MOSI (PA7)  ------>  MOSI (PA7)
 */

/***************************************************************
 *  GLOBAL VARIABLE DEFINITION
 ***************************************************************/
static spi_cb_t  g_Callback = NULL;

/***************************************************************
 *  FUNCTION DECLARATION
 ***************************************************************/

 void SPI_RequestInConfig(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;

  /* Enable GPIOA clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* Configure PA0 pin as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Connect EXTI Line0 to PA0 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

  /* Enable and set EXTI Line0 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void SPI_RequestInExtiConfig(bool Enable)
{
    EXTI_InitTypeDef   EXTI_InitStructure;

    EXTI_InitStructure.EXTI_Line    = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;

    if(Enable)
    {
       EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    }
    else
    {
       EXTI_InitStructure.EXTI_LineCmd = DISABLE;
    }

    EXTI_Init(&EXTI_InitStructure);
}

bool SPI_RequestInGetStatus(void)
{
   if (Bit_SET == GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0))
   {
       return true;
   }
   else
   {
       return false;
   }
}

void SPI_RequestOutConfig(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;

  /* Enable GPIOA clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  /* Configure PA1 pin as output */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void SPI_RequestOutSetValue(bool Val)
{
   if (Val)
   {
       GPIO_SetBits(GPIOA, GPIO_Pin_1);
   }
   else
   {
       GPIO_ResetBits(GPIOA, GPIO_Pin_1);
   }
}

void SPI_Config(bool Master)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
  DMA_InitTypeDef DMA_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  uint32_t MemAddress = 0x01;

  /* Peripheral Clock Enable -------------------------------------------------*/
  /* Enable the SPI clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

  /* Enable GPIO clocks */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  /* Enable DMA clock */
  RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_DMA2, ENABLE);

  /* SPI GPIO Configuration --------------------------------------------------*/

  /* Connect SPI pins to AF5 */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1); // SCK
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1); // MISO
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1); // MOSI

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;

  /* SPI SCK pin configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* SPI  MISO pin configuration */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* SPI  MOSI pin configuration */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* SPI configuration -------------------------------------------------------*/
  SPI_I2S_DeInit(SPI1);
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;

  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;

  /* DMA configuration -------------------------------------------------------*/
  /* Deinitialize DMA Streams */
  DMA_DeInit(DMA2_Stream3); // SPI1_TX_DMA_STREAM
  DMA_DeInit(DMA2_Stream2); // SPI1_RX_DMA_STREAM

  /* Configure DMA Initialization Structure */
  DMA_InitStructure.DMA_BufferSize = 1; // We will configure later
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable ;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull ;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single ;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t) (&(SPI1->DR)) ;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;

  /* Configure TX DMA */
  DMA_InitStructure.DMA_Channel = DMA_Channel_3;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  DMA_InitStructure.DMA_Memory0BaseAddr = MemAddress; // We will configure later
  DMA_Init(DMA2_Stream3, &DMA_InitStructure);

  /* Configure RX DMA */
  DMA_InitStructure.DMA_Channel = DMA_Channel_3;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory ;
  DMA_InitStructure.DMA_Memory0BaseAddr = MemAddress; // We will configure later
  DMA_Init(DMA2_Stream2, &DMA_InitStructure);

  /*
   * Enable NVIC, because SPI full duplex so only one
   * Rx DMA interrupt is enough
   */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  if (true == Master)
  {
      SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  }
  else
  {
      SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
  }

  SPI_Init(SPI1, &SPI_InitStructure);

#if 0
  /* Request output configuration */
  SPI_RequestOutConfig();
  SPI_RequestOutSetValue(true);

  /* Request input configuration */
  SPI_RequestInConfig();
  SPI_RequestInExtiConfig(true);
#endif

}

void SPI_ConfigTransfer(uint8_t *TxBuffer, uint8_t *RxBuffer, uint32_t Len)
{
    // SPI1_TX_DMA_STREAM configuration
    DMA2_Stream3->NDTR = Len;
    DMA2_Stream3->M0AR = (uint32_t)TxBuffer;

    // SPI1_RX_DMA_STREAM configuration
    DMA2_Stream2->NDTR = Len;
    DMA2_Stream2->M0AR = (uint32_t)RxBuffer;
}

void SPI_StartTransfer(void)
{
  /* The Data transfer is performed in the SPI using Direct Memory Access */
  DMA_Cmd(DMA2_Stream3, ENABLE);  /* Enable DMA SPI TX Stream */
  DMA_Cmd(DMA2_Stream2, ENABLE);  /* Enable DMA SPI RX Stream */

  SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE); /* Enable SPI DMA TX Requests */
  SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Rx, ENABLE); /* Enable SPI DMA RX Requests */

  /* Enable the SPI peripheral */
  SPI_Cmd(SPI1, ENABLE);
}

void SPI_StopTransfer(void)
{
  /* Disable DMA RX complete interrupt */
  DMA_ITConfig(DMA2_Stream2, DMA_IT_TC, DISABLE);

  /* Clear DMA Transfer Complete Flags */
  DMA_ClearFlag(DMA2_Stream3, DMA_FLAG_TCIF3);
  DMA_ClearFlag(DMA2_Stream2, DMA_FLAG_TCIF2);

  DMA_Cmd(DMA2_Stream3, DISABLE); /* Disable DMA SPI TX Stream */
  DMA_Cmd(DMA2_Stream2, DISABLE); /* Disable DMA SPI RX Stream */

  SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, DISABLE); /* Disable SPI DMA TX Requsts */
  SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Rx, DISABLE); /* Disable SPI DMA RX Requsts */

  /* Disable the SPI peripheral */
  SPI_Cmd(SPI1, DISABLE);
}

void SPI_WaitTransferComplete(void)
{
  /* Waiting the end of Data transfer */
  while (DMA_GetFlagStatus(DMA2_Stream3, DMA_FLAG_TCIF3) == RESET);
  while (DMA_GetFlagStatus(DMA2_Stream2, DMA_FLAG_TCIF2) == RESET);
}

void SPI_SyncTransfer(uint8_t *TxBuffer, uint8_t *RxBuffer, uint32_t Len)
{
    SPI_ConfigTransfer(TxBuffer, RxBuffer, Len);
    SPI_StartTransfer();
    SPI_WaitTransferComplete();
    SPI_StopTransfer();
}

void SPI_AsyncTransfer(uint8_t *TxBuffer, uint8_t *RxBuffer, uint32_t Len, spi_cb_t CallBack)
{
    /* Call back function */
    g_Callback = CallBack;

    /* Enable DMA RX complete interrupt */
    DMA_ITConfig(DMA2_Stream2, DMA_IT_TC, ENABLE);

    SPI_ConfigTransfer(TxBuffer, RxBuffer, Len);
    SPI_StartTransfer();
}

ISR (DMA2_Stream2_Handler)
{
   if (SET == DMA_GetITStatus(DMA2_Stream2, DMA_IT_TCIF2))
   {
       DMA_ClearITPendingBit(DMA2_Stream2, DMA_IT_TCIF2);

       SPI_StopTransfer();

       if (NULL != g_Callback)
       {
            /* Call callback function */
            g_Callback();
       }
   }
}

void DMA2_Stream3_IRQHandler(void)
{
   if (SET == DMA_GetITStatus(DMA2_Stream3, DMA_IT_TCIF3))
   {
       DMA_ClearITPendingBit(DMA2_Stream2, DMA_IT_TCIF2);
   }
}

ISR (EXTI0_Handler)
{
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    /* Clear the EXTI line 0 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line0);
  }
}
