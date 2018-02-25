/**
  ******************************************************************************
  * @file    uart_debug.c
  * @author  Dang Minh Phuong
  * @version V1.0.0
  * @date    06/16/2013
  * @brief   UART debug
  ******************************************************************************
  * @attention
  *
  * Licensed under the Apache License, Version 2.0 (the "License");
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  *      http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  * <h2><center>&copy; COPYRIGHT (C)2012 Yuuichi Akagawa</center></h2>
  *
  ******************************************************************************
  */

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include <stdio.h>


//USART2
USART_TypeDef* COM_USART        = USART2;
GPIO_TypeDef*  COM_TX_PORT      = GPIOA;
GPIO_TypeDef*  COM_RX_PORT      = GPIOA;
const uint32_t COM_USART_CLK    = RCC_APB1Periph_USART2;
const uint32_t COM_TX_PORT_CLK  = RCC_AHB1Periph_GPIOA;
const uint32_t COM_RX_PORT_CLK  = RCC_AHB1Periph_GPIOA;
const uint16_t COM_TX_PIN       = GPIO_Pin_2;
const uint16_t COM_RX_PIN       = GPIO_Pin_3;
const uint16_t COM_TX_PIN_SOURCE= GPIO_PinSource2;
const uint16_t COM_RX_PIN_SOURCE= GPIO_PinSource3;
const uint16_t COM_TX_AF        = GPIO_AF_USART2;
const uint16_t COM_RX_AF        = GPIO_AF_USART2;

void uart_debug_init(void)
{
	  USART_InitTypeDef USART_InitStructure;
	  GPIO_InitTypeDef GPIO_InitStructure;
	  /* USARTx configured as follow:
	        - BaudRate = 230400 baud
	        - Word Length = 8 Bits
	        - One Stop Bit
	        - No parity
	        - Hardware flow control disabled (RTS and CTS signals)
	        - Receive and transmit enabled
	  */
	  USART_InitStructure.USART_BaudRate = 115200;
	  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	  USART_InitStructure.USART_StopBits = USART_StopBits_1;
	  USART_InitStructure.USART_Parity = USART_Parity_No;
	  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	  USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	  /* Enable GPIO clock */
	  RCC_AHB1PeriphClockCmd(COM_TX_PORT_CLK | COM_RX_PORT_CLK, ENABLE);
	  /* Enable UART clock */
	  RCC_APB1PeriphClockCmd(COM_USART_CLK, ENABLE);

	  /* Connect PXx to USARTx_Tx*/
	  GPIO_PinAFConfig(COM_TX_PORT, COM_TX_PIN_SOURCE, COM_TX_AF);

	  /* Connect PXx to USARTx_Rx*/
	  GPIO_PinAFConfig(COM_RX_PORT, COM_RX_PIN_SOURCE, COM_RX_AF);

	  /* Configure USART Tx as alternate function  */
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

	  GPIO_InitStructure.GPIO_Pin = COM_TX_PIN;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(COM_TX_PORT, &GPIO_InitStructure);

	  /* Configure USART Rx as alternate function  */
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_Pin = COM_RX_PIN;
	  GPIO_Init(COM_RX_PORT, &GPIO_InitStructure);

	  /* USART configuration */
	  USART_Init(COM_USART, &USART_InitStructure);

	  /* Enable USART */
	  USART_Cmd(COM_USART, ENABLE);

		/* We need refresh the FLAG_TC before using the USART */
	  while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);

}

/*----------------------------------------------------------------------------
  SendChar
  Write character to Serial Port.
 *----------------------------------------------------------------------------*/

unsigned char SendChar (unsigned char ch)  {

    if (ch=='\n')  {

        USART_SendData(USART2, (uint8_t)'\r');
        while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
	    {}
    }

	USART_SendData(USART2, (uint8_t) ch);

	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
	{}

  	return (ch);
}

/*----------------------------------------------------------------------------
  GetKey
  Read character to Serial Port.
 *----------------------------------------------------------------------------*/
unsigned char GetKey (void)  {

  unsigned char  ret;
  /* Loop until incomming data */
  while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET)
  {}

  ret = USART_ReceiveData(USART2);
  SendChar(ret);

  return ret;
}

int _read (int fd, const void *buf, size_t count)
{
  return 0;
}

int _write (int fd, const void *buf, size_t count)
{
  size_t CharCnt = 0x00;

  (void)fd;                            /* Parameter is not used, suppress unused argument warning */
   for (;count > 0x00; --count)
   {
     SendChar((unsigned char)*(uint8_t*)buf);
     (uint8_t*)buf++;
     CharCnt++;
   }
  return CharCnt; /* CORRECT */
}
