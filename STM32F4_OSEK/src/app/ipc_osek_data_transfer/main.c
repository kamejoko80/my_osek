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

/*
 * Message catalog:
 *
 * Name        : CMD_SEND_DATA_SIZE
 * Byte 0      : 0x01
 * Byte 1-4    : Data size
 * Emitter     : SoC
 * Description : SoC sends data size to MCU
 *
 * Name        : CMD_SEND_DATA
 * Byte 0      : 0x02
 * Byte 1      : Data len
 * Byte 2-n    : Data
 * Emitter     : SoC
 * Description : SoC sends data to MCU
 *
 * Name        : CMD_ACK
 * Byte 0      : 0x03
 * Emitter     : MCU, SoC
 * Description : Send ACK
 *
 * Name        : CMD_NAK
 * Byte 0      : 0x04
 * Byte 1      : Error code
 * Emitter     : MCU, SoC
 * Description : Send NAK with error code
 */

/* Message commands definition */
#define CMD_SEND_DATA_SIZE (0x01)
#define CMD_SEND_DATA      (0x02)
#define CMD_ACK            (0x03)
#define CMD_NAK            (0x04)

#define BACKTRACE_SIZE 4

char str[IPC_TRANSFER_LEN] = {0};
uint8_t Buff[IPC_TRANSFER_LEN] = {0};

volatile uint32_t DataSize = 0;
volatile uint8_t step = 1;

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

uint32_t Get_Data(IPC_Frame_t *Frame)
{
    /* Check valid frame */
    if(Frame->Header.Len != (Frame->Data[1] + 2))
    {
        return 0;
    }
    else
    {
        /* Process data here */

        /* Retrieve data length */
        return (Frame->Data[1]);
    }
}

void Send_ACK(void)
{
    uint8_t Ack = CMD_ACK;

    IPC_Send((uint8_t *)&Ack, 1);
}

void Send_NAK(uint8_t ErrCode)
{
    uint8_t buff[2];

    buff[0] = CMD_NAK;
    buff[1] = ErrCode;
    IPC_Send((uint8_t *)buff, 2);
}

uint32_t Get_DataSize(IPC_Frame_t *Frame)
{
    return (Frame->Data[1] |
           (Frame->Data[2] << 8) |
           (Frame->Data[3] << 16) |
           (Frame->Data[3] << 24));
}

void Disp_Progress(uint32_t Len, uint32_t Size)
{
    if(Len == Size)
    {
       printf("100%c\n", '%');
    }
    else if((Len * 100) >= (5 * step * Size))
    {
       printf("%3d%c\n", 5 * step, '%');
       step++;
    }
}

void Message_Process(IPC_Frame_t *Frame)
{
    uint32_t Len;

    printf("Message_Process\n");

    switch (Frame->Data[0])
    {
        case CMD_SEND_DATA_SIZE:
            printf("CMD_SEND_DATA_SIZE\n");
            DataSize = Get_DataSize(Frame);
            if(DataSize)
            {
               printf("Data Size = %d\n", DataSize);
               step = 1;
               Send_ACK();
            }
            else
            {
                printf("Invalid data size NAK\n");
                Send_NAK(0x01);
            }

        break;

        case CMD_SEND_DATA:
            Len = Get_Data(Frame);
            if(Len != 0)
            {
                printf("Received data len = %d\n", Len);
                Disp_Progress(Len, DataSize);
                Send_ACK();
            }
            else
            {
                printf("Data transfer error NAK\n");
                Send_NAK(0x02);
            }
        break;

        default:
        break;
    }

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
    FifoPopMulti(Fifo, (void *)Frame , IPC_TRANSFER_LEN);

    /* Consume the data */
    Message_Process(Frame);
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

    printf("STM32F4 IPC data transfer demo\n");
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
    #error "This demo only supports slaver mode, please change to slaver mode by editing ipc.h"
#else
    printf("IPC Slaver Start\n");
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
        //IPC_Send((uint8_t *)str, strlen(str));
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

