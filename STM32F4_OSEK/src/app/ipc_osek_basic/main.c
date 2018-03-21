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
#include <stdlib.h>
#include "stm32f4_discovery.h"
#include "stm32f4xx_conf.h"
#include "os.h"
#include "uart_debug.h"
#include "backtrace.h"
#include "ipc.h"
#include "fifo.h"
#include "trace.h"
#include "input.h"

#define BACKTRACE_SIZE 4

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

    for(i = 0; i < Len; i++)
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

/**
 * @brief         Input_GetsCallBack
 * @param[in]     char *Buffer, uint32_t Len
 * @param[in,out] None
 * @return        void
 */
void Input_GetsCallBack(char *Buffer, uint32_t Len)
{
	/* Send event to TaskMenu */
	SetEvent(TaskDemo, evInputRcvComplete);
}

/**
 * @brief         IPC_DataRxHandler
 * @param[in]     Fifo_t *Fifo
 * @param[in,out] None
 * @return        void
 */
void IPC_DataRxHandler(Fifo_t *Fifo)
{
    IPC_Frame_t *Frame = (IPC_Frame_t *)Buff;

    /* Fetch data from FIFO buffer */
    FifoPopMulti(Fifo, Buff, IPC_TRANSFER_LEN);

    /* Reset message data buffer */
    memset(str, 0, IPC_TRANSFER_LEN);
    memcpy(str, Frame->Data, Frame->Header.Len);
    SysTrace_Message("%s", str);
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
    EventMaskType waitEventMask = 0;
    EventMaskType eventMask;

    printf("TaskIdle: Init\n");

    /* Initialize wait events */
    waitEventMask |= evSysTraceMsgQueue;

    while(1)
    {
        /*
         * Task will switch to WAIT state
         * after calling the following function
         */
        WaitEvent(waitEventMask);

        /* Check event and do the corresponding process */
        if (E_OK == GetEvent(TaskIdle, &eventMask))
        {
            SysTrace_ManageMsgQueueEvent(eventMask);
        }
        else
        {
            /* This should not be run */
            TerminateTask();
        }
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
    EventMaskType Event;

    printf("TaskDemo: Init\n");

    /* Init system trace module */
    SysTrace_Init();

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
        /* Reset message buffer */
        memset(str, 0, IPC_TRANSFER_LEN);

        /* Get message input */
        Input_GetsAsync(str, IPC_TRANSFER_LEN, &Input_GetsCallBack);

        /* Wait event */
        WaitEvent(evInputRcvComplete);
        GetEvent(TaskDemo, &Event);
        ClearEvent(evInputRcvComplete);

        SysTrace_Message("%s", str);
        IPC_Send((uint8_t *)str, strlen(str));
        STM_EVAL_LEDToggle(LED4);
    }

	TerminateTask();
}

void ErrorHook(void)
{
    uint8_t i;
    backtrace_t backtrace[BACKTRACE_SIZE];

    /* Get back trace info */
    backtrace_unwind(backtrace, BACKTRACE_SIZE);

	/* kernel panic :( */
    printf("kernel panic\n");
    printf("call stack :\n");

    for (i = 0; i < BACKTRACE_SIZE; i++)
    {
        if(strcmp("unknown", backtrace[i].name) == 0)
        {
            break;
        }

        printf("name       : %s\r\n", backtrace[i].name);
        printf("function   : %p\r\n", backtrace[i].function);
        printf("address    : %p\r\n", backtrace[i].address);
        printf("==============\n\r");
    }

	ShutdownOS(0);
}

