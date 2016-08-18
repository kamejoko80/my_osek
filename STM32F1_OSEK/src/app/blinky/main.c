/*
**
**                           Main.c
**
**
**********************************************************************/
/*
   Last committed:     $Revision: 00 $
   Last changed by:    $Author: $
   Last changed date:  $Date:  $
   ID:                 $Id:  $

**********************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include "stm32f10x_conf.h"
#include "GPIO_STM32F10x.h"
#include "uart.h"
#include "uart_debug.h"
#include "os.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definition
////////////////////////////////////////////////////////////////////////////////

#define TRUE  1
#define FALSE 0

#define LED_PIN 12

////////////////////////////////////////////////////////////////////////////////
// Global variables definition
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

static void LED_ON(void)
{
    GPIOC->BSRR |= (1 << LED_PIN);
}

static void LED_OFF(void)
{
    GPIOC->BRR |= (1 << LED_PIN);
}

int main(void)
{
  /* Update system clock */
  SystemCoreClockUpdate();

  /* Initialize UART debug */
  UartDebugInit();

  /* GPIO LED configuration */
  GPIO_PortClock (GPIOC, TRUE);

  /* LED pin as output */
  GPIO_PinConfigure(GPIOC, LED_PIN, GPIO_OUT_PUSH_PULL, GPIO_MODE_OUT50MHZ);

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

TASK(TaskInit)
{
	/* Set 500 tick alarm for TaskPeriodic */
	printf("InitTask: SetRelAlarm for TaskPeriodic.\r\n");
	SetRelAlarm(ActivateTaskPeriodic, 0, 500);

	/* Set 1000 tick callback alarm */
	printf("InitTask: SetRelAlarm for AppCallback.\r\n");
	SetRelAlarm(AppCallbackAlarm, 100, 1000);

	/* Activate TaskBlink */
	printf("InitTask: Activate TaskBlink.\r\n");
	ActivateTask(TaskBlink);

	/* Activate TaskBackground */
	ActivateTask(TaskBackground);

	/* end InitTask */
	printf("InitTask: TerminateTask().\r\n");
	TerminateTask();
}

/*
 * This task waits for an event to be set in order
 * to continue execution.
 */
TASK(TaskBlink)
{
    static bool flag = FALSE;

	printf("TaskBlink: Init.\r\n");
	while(1)
	{
		printf("TaskBlink: Waiting for event...\r\n");
		WaitEvent(evBlink);
		ClearEvent(evBlink);
		printf("TaskBlink: LED Toggle.\r\n");

        /* Toggle the LED */
		if(TRUE == flag)
        {
            LED_ON();
            flag = FALSE;
        }
        else
        {
            LED_OFF();
            flag = TRUE;
        }

	}
	TerminateTask();
}

/*
 * This is a periodic task.
 */
TASK(TaskPeriodic)
{
	printf("TaskPeriodic: Event set.\r\n");
	SetEvent(TaskBlink, evBlink);

	/* end TaskPeriodic */
	TerminateTask();
}

/*
 * Just a background task with an infinite loop,
 * it has to be defined with the minimum priority!!!
 */
TASK(TaskBackground)
{
	volatile int i = 0;
	printf("TaskBackground: Running!\r\n");
	while(1)
	{
		i++;
		if(i == 0xFFFFF)
		{
			printf("TaskBackground still running...\r\n");
			i = 0;
		}
	}
}

/*
 * Alarm Callback example.
 */
ALARMCALLBACK(AppCallback)
{
	printf("AppCallback.\r\n");
}
