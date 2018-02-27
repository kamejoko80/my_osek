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

/**
 * @brief         PrintBuffer
 * @param[in]     uint8_t *RxBuffer
 * @param[in]     uint32_t Len
 * @param[in,out] char *str
 * @return        void
 */
void PrintBuffer(uint8_t *RxBuffer, uint32_t Len)
{
    int i;

    for(i = 0; i < IPC_TRANSFER_LEN; i++)
    {
        printf("%c", RxBuffer[i]);
    }

    printf("\r\n");
}

/**
 * @brief         get_string
 * @param[in]     None
 * @param[in,out] char *str
 * @return        void
 */
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

void IPC_DataRxHandler(Fifo_t *Fifo)
{
    IPC_Frame_t *Frame = (IPC_Frame_t *)Buff;

    /* Fetch data from FIFO buffer */
    FifoPopMulti(Fifo, Buff, IPC_TRANSFER_LEN);
    PrintBuffer(Frame->Data, IPC_TRANSFER_LEN);
}

/**
 * @brief         main
 * @param[in]     None
 * @param[in,out] None
 * @return        int
 */
int main(void)
{
    /* Uart debug init */
    uart_debug_init();

    /* LED init */
    STM_EVAL_LEDInit(LED3);
    STM_EVAL_LEDInit(LED4);
    STM_EVAL_LEDInit(LED5);
    STM_EVAL_LEDInit(LED6);

    printf("STM32F4 IPC chatting demo\n");
    printf("Starting OSEK-OS in AppMode1...\n");
    StartOS(AppMode1);

    /* we should not return here */
    while(1);
}

/**
 * @brief         TaskIdle
 * @param[in]     None
 * @param[in,out] None
 * @return        None
 */
TASK(TaskIdle)
{
    printf("TaskIdle: Init\n");
    while(1)
    {

    }

	TerminateTask();
}

/**
 * @brief         TaskDemo
 * @param[in]     None
 * @param[in,out] None
 * @return        None
 */
TASK(TaskDemo)
{
    printf("TaskDemo: Init\n");

    /* Wait for IPC initialization completed */
    while (false == IPC_InitStatus());

#ifdef SPI_MASTER
    printf("IPC Master Start\n");
    printf("String input\r\n");
#else
    printf("IPC Slaver Start\n");
    printf("String input\r\n");
#endif

    while(1)
    {
        memset(str, 0, IPC_TRANSFER_LEN);
        get_string(str);
        printf("%s\r\n", str);
        IPC_Send((uint8_t *)str, strlen(str));

        STM_EVAL_LEDToggle(LED4);
    }

	TerminateTask();
}

void ErrorHook(void)
{
	/* kernel panic :( */
    printf("kernel panic\n");
	ShutdownOS(0);
}

