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

int main(void)
{
    uart_debug_init();
    STM_EVAL_LEDInit(LED3);

    printf("Starting OSEK-OS in AppMode1\n");
    StartOS(AppMode1);

    /* we shouldn't return here */
    while(1);
}

void ErrorHook(void)
{
	/* kernel panic :( */
    printf("kernel panic\n");
	ShutdownOS(0);
}

TASK(TaskInit)
{
	/* Set 500 tick alarm for TaskPeriodic */
	printf("InitTask: SetRelAlarm for TaskPeriodic.\n");
	SetRelAlarm(ActivateTaskPeriodic, 0, 500);

	/* Set 1000 tick callback alarm */
	printf("InitTask: SetRelAlarm for AppCallback.\n");
	SetRelAlarm(AppCallbackAlarm, 100, 1000);

	/* Activate TaskBlink */
	printf("InitTask: Activate TaskBlink.\n");
	ActivateTask(TaskBlink);

	/* Activate TaskBackground */
	ActivateTask(TaskBackground);

	/* end InitTask */
	printf("InitTask: TerminateTask().\n");
	TerminateTask();
}

/*
 * This task waits for an event to be set in order
 * to continue execution.
 */
TASK(TaskBlink)
{
	printf("TaskBlink: Init.\n");
	while(1)
	{
		printf("TaskBlink: Waiting for event...\n");
		WaitEvent(evBlink);
		ClearEvent(evBlink);
		printf("TaskBlink: LED Toggle.\n");
		STM_EVAL_LEDToggle(LED3);
	}
	TerminateTask();
}

/*
 * This is a periodic task.
 */
TASK(TaskPeriodic)
{
	printf("TaskPeriodic: Event set.\n");
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
	printf("TaskBackground: Running!\n");
	while(1)
	{
		i++;
		if(i == 0xFFFFF)
		{
			printf("TaskBackground still running...\n");
			i = 0;
		}
	}
}

/*
 * Alarm Callback example.
 */
ALARMCALLBACK(AppCallback)
{
	printf("AppCallback.\n");
}
