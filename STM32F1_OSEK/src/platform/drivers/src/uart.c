/*
 *  Copyright   : 2016
 *  File name   : uart.c
 *	Author      : Dang Minh Phuong (PhuongDM1)
 *	Description : Message implementation
 */

#include "stm32f10x_conf.h"

typedef struct
{
    GPIO_TypeDef *GPIOx;
    uint32_t Periph;    /* RCC_APB2Periph_GPIOx */
} GPIO_Periph_TypeDef;

typedef struct
{
    USART_TypeDef *USARTx;
    uint32_t Periph;    /* RCC_APB2Periph_GPIOx */
} USART_Periph_TypeDef;

static const GPIO_Periph_TypeDef GPIO_Periph[] =
{
    {GPIOA,  RCC_APB2Periph_GPIOA},
    {GPIOB,  RCC_APB2Periph_GPIOB},
    {GPIOC,  RCC_APB2Periph_GPIOC},
    {GPIOD,  RCC_APB2Periph_GPIOD},
    {GPIOE,  RCC_APB2Periph_GPIOE},
    {GPIOF,  RCC_APB2Periph_GPIOF},
    {GPIOG,  RCC_APB2Periph_GPIOG},
    {0, 0}
};

static const USART_Periph_TypeDef USART_Periph[] =
{
    {USART1,  RCC_APB2Periph_USART1},
    {USART2,  RCC_APB1Periph_USART2},
    {USART3,  RCC_APB1Periph_USART3},
    {UART4,   RCC_APB1Periph_UART4},
    {UART5,   RCC_APB1Periph_UART5},
    {0, 0}
};

void UartInit(USART_TypeDef *USARTx,
              GPIO_TypeDef *GPIOx,
              uint16_t GPIO_Pin_Tx,
              uint16_t GPIO_Pin_Rx,
              int baudrate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
    uint32_t idx = 0;

    /* Enable GPIOx clocks */
    while(GPIO_Periph[idx].GPIOx != 0)
    {
        if(GPIOx == GPIO_Periph[idx].GPIOx)
        {
            RCC_APB2PeriphClockCmd(GPIO_Periph[idx].Periph | RCC_APB2Periph_AFIO, ENABLE);
            break;
        }
        idx++;
    }

	/* Enable UART clock, if using USART2 or USART3 ... we must use RCC_APB1PeriphClockCmd(RCC_APB1Periph_USARTx, ENABLE) */

	if(USART1 == USARTx)
    {
       	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    }
    else
    {
        idx = 0;

        while(USART_Periph[idx].USARTx != 0)
        {
            if(USARTx == USART_Periph[idx].USARTx)
            {
                RCC_APB1PeriphClockCmd(USART_Periph[idx].Periph, ENABLE);
                break;
            }
            idx++;
        }

    }

	/* Configure for USART Tx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Tx;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOx, &GPIO_InitStructure);

	/* Configure for USART Rx as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Rx;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOx, &GPIO_InitStructure);

	/* USARTx configured as follow:
        - BaudRate = 115200 baud
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  	*/
	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	/* USART configuration */
	USART_Init(USARTx, &USART_InitStructure);

  /* We need refresh the FLAG_TC before using the USART */
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);

	/* Enable USART */
	USART_Cmd(USARTx, ENABLE);
}

/*----------------------------------------------------------------------------
  SendChar
  Write character to Serial Port.
 *----------------------------------------------------------------------------*/

int SendChar (USART_TypeDef *USARTx, uint8_t ch)
{
	if (ch == '\n') {
		USART_SendData(USARTx, (uint8_t) '\r');
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	}

	USART_SendData(USARTx, (uint8_t) ch);

	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);

  	return (ch);
}

/*----------------------------------------------------------------------------
  GetKey
  Read character to Serial Port.
 *----------------------------------------------------------------------------*/
int GetChar (USART_TypeDef *USARTx)
{

  int  ret;
  /* Loop until incomming data */
  while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET)
  {}

  ret = USART_ReceiveData(USARTx);

  return ret;
}
