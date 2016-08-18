/*
 *  Copyright   : 2016
 *  File name   : main.c
 *	Author      : Dang Minh Phuong (PhuongDM1)
 *	Description : Message implementation
 */

#include <stdio.h>
#include <stdbool.h>
#include "stm32f10x_conf.h"
#include "GPIO_STM32F10x.h"
#include "uart.h"
#include "uart_debug.h"
#include "os.h"
#include "message.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definition
////////////////////////////////////////////////////////////////////////////////

#define BUFF_SIZE 32
#define TRUE 1
#define FALSE 0

#define BUFF_SIZE 32

////////////////////////////////////////////////////////////////////////////////
// Global variables definition
////////////////////////////////////////////////////////////////////////////////

MessageType gMessage1, gMessage2;

uint8_t gBuff1[BUFF_SIZE];
uint8_t gBuff2[BUFF_SIZE];

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

static void LED_ON(void)
{
    GPIOD->BSRR |= (1 << 2);
}

static void LED_OFF(void)
{
    GPIOD->BRR |= (1 << 2);
}

int main(void)
{
  /* Update system clock */
  SystemCoreClockUpdate();

  /* Initialize UART debug */
  UartDebugInit();

  /* Print introduction */
  printf("STM32F1 OSEK-OS demonstration\r\n");

  /* GPIO LED configuration */
  GPIO_PortClock (GPIOD, TRUE);

  /* LED pin as output */
  GPIO_PinConfigure(GPIOD, 2, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT50MHZ);

  /* Start the OSEK */
  printf("Starting OSEK-OS in AppMode1\r\n");

  StartOS(AppMode1);

  /* we shouldn't return here */
  while(TRUE);
}


void ErrorHook(void)
{
	/* kernel panic :( */
    printf("kernel panic\r\n");
	ShutdownOS(0);
}


/*
 * This task waits for an event to be set in order
 * to continue execution.
 */
TASK(TaskReceive)
{
    MessageType *MsgRcv1, *MsgRcv2;

	while(1)
	{
	    /* Wait for message event */
		WaitEvent(evMessage);
		ClearEvent(evMessage);

        /* Get message */
        MsgRcv1 = Message_Get(1);
        MsgRcv2 = Message_Get(2);

        /* Check valid message */
        if ((MsgRcv1 == NULL) || (MsgRcv1 == NULL))
        {
            printf("could not get message\r\n");
            break;
        }

        /* Turn on the LED */
	    LED_ON();

        printf("MsgRcv1 : %X %X %X %X\r\n",
                                MsgRcv1->data[0],
                                MsgRcv1->data[1],
                                MsgRcv1->data[2],
                                MsgRcv1->data[3]);

        printf("MsgRcv2 : %X %X %X %X\r\n",
                                MsgRcv2->data[0],
                                MsgRcv2->data[1],
                                MsgRcv2->data[2],
                                MsgRcv2->data[3]);
	}

	TerminateTask();
}

/*
 * This task sends message periodically
 */
TASK(TaskSend)
{
    MessageType *Msg1, *Msg2;

    /* Initialize message */
    Message_Init();

    /* Start periodic alarm */
    SetRelAlarm(AlarmSend, 100, 1000);

	while(1)
	{
	    /* Turn off the LED */
	    LED_OFF();

        /* Wait for alarm */
		WaitEvent(evAlarmSend);
		ClearEvent(evAlarmSend);

        /* Allocate message */
        Msg1 = Message_AllocateStatic(&gMessage1, (uint8_t*)gBuff1, 4);
        Msg2 = Message_AllocateStatic(&gMessage2, (uint8_t*)gBuff2, 4);

        if ((Msg1 == NULL) || (Msg1 == NULL))
        {
            printf("could not allocate message\r\n");
            break;
        }

        /* Prepare message data */
        Msg1->id = 1;
        Msg1->data[0] = 0x10;
        Msg1->data[1] = 0x11;
        Msg1->data[2] = 0x12;
        Msg1->data[3] = 0x13;

        Msg2->id = 2;
        Msg2->data[0] = 0x20;
        Msg2->data[1] = 0x21;
        Msg2->data[2] = 0x22;
        Msg2->data[3] = 0x23;

        /* Queue message */
        Message_Queue(Msg1);
        Message_Queue(Msg2);

        /* Send message */
        Message_Send(TaskReceive, evMessage);
	}

	TerminateTask();
}

/*
 * Just a idle task with an infinite loop,
 * it has to be defined with the minimum priority!!!
 */
TASK(TaskIdle)
{
	while(1)
	{

	}
}

