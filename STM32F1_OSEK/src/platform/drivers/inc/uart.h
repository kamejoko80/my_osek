#ifndef __UART_H__
#define __UART_H__

#include "stm32f10x_conf.h"

void UartInit(USART_TypeDef *USARTx,
              GPIO_TypeDef *GPIOx,
              uint16_t GPIO_Pin_Tx,
              uint16_t GPIO_Pin_Rx,
              int baudrate);

int SendChar (USART_TypeDef *USARTx, uint8_t ch);
int GetChar (USART_TypeDef *USARTx);

#endif /* __UART_H__ */
