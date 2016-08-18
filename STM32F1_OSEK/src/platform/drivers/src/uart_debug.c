/*
 *  Copyright   : 2016
 *  File name   : uart_debug.c
 *	Author      : Dang Minh Phuong (PhuongDM1)
 *	Description : Message implementation
 */

#include "stm32f10x_conf.h"
#include "uart.h"

#define size_t unsigned int

#define UDBG_PORT USART1
#define UDBG_GPIO GPIOA
#define UDBG_PNTx GPIO_Pin_9
#define UDBG_PNRx GPIO_Pin_10
#define UDBG_BAUD 115200

void UartDebugInit(void)
{
    UartInit(UDBG_PORT, UDBG_GPIO, UDBG_PNTx, UDBG_PNRx, UDBG_BAUD);
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
     SendChar(UDBG_PORT, (unsigned char)*(uint8_t*)buf);
     (uint8_t*)buf++;
     CharCnt++;
   }
  return CharCnt; /* CORRECT */
}
