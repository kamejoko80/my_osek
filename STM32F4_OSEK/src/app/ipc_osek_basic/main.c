/*
**
**                           Main.c
**
**
**********************************************************************/
/*
   Last committed:     $Revision : 1.2
   Last changed by:    $Author   : Dang Minh Phuong
   Last changed date:  $Date     : 20160427
   ID:                 $Id       : 00

**********************************************************************/
#include <stdio.h>
#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h"
#include "os.h"
#include "uart_debug.h"
#include "ipc.h"
#include "fifo.h"

char str[IPC_TRANSFER_LEN] = {0};
uint8_t Buff[IPC_TRANSFER_LEN] = {0};

void Delay(uint32_t m)
{
    uint32_t i, j;

    for (i = 0; i < m; i++)
       for(j = 0; j < 10000; j++);
}

void PrintBuffer(uint8_t *RxBuffer, uint32_t Len)
{
    int i;

    for(i = 0; i < Len; i++)
    {
        printf("%c", RxBuffer[i]);
    }

    printf("\r\n");
}

void MasterRxDataHandler(Fifo_t *fifo)
{
    FifoPopMulti(fifo, Buff, IPC_TRANSFER_LEN);
    PrintBuffer(Buff, IPC_TRANSFER_LEN);
}

void SlaverRxDataHandler(Fifo_t *fifo)
{
    FifoPopMulti(fifo, Buff, IPC_TRANSFER_LEN);
    PrintBuffer(Buff, IPC_TRANSFER_LEN);
}

void get_string(char *str)
{
   char c;

   while(1)
   {
      c = (char)GetKey();
      if(c == 13)
      {
          break;
      }
      *str++ = c;
   }
}

int main(void)
{
    uart_debug_init();
    STM_EVAL_LEDInit(LED3);

    printf("STM32F4 IPC chatting demo\n");
    printf("Starting OSEK-OS in AppMode1...\n");
    StartOS(AppMode1);

    /* we should not return here */
    while(1);
}

void ErrorHook(void)
{
	/* kernel panic :( */
    printf("kernel panic\n");
	ShutdownOS(0);
}

TASK(TaskIdle)
{
    printf("TaskIdle: Init\n");
    while(1)
    {

    }

	TerminateTask();
}

TASK(TaskIPC)
{
	printf("TaskIPC: Init\n");
    IPC_Init();
    printf("String input\r\n");

	while(1)
	{
        #ifdef SPI_MASTER
            memset(str, 0, IPC_TRANSFER_LEN);
            get_string(str);
            printf("%s\r\n", str);
            IPC_MasterTransferRequest((uint8_t *)str, IPC_TRANSFER_LEN);
        #else
            memset(str, 0, IPC_TRANSFER_LEN);
            get_string(str);
            printf("%s\r\n", str);
            IPC_SlaverTransferRequest((uint8_t *)str, IPC_TRANSFER_LEN);
        #endif

		STM_EVAL_LEDToggle(LED3);
	}
	TerminateTask();
}
