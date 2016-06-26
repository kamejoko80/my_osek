/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

///////////////////////////////////////////////////////////////////////////////
//  Includes
///////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "board.h"
#include "gpio_pins.h"
#include "gpio_imx.h"
#include "debug_console_imx.h"
#include "os.h"

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////


void Init_GPIO_LED(void)
{
    gpio_init_config_t led_d10 = {
        .pin = gpioLed.pin,
        .direction = gpioDigitalOutput,
        .interruptMode = gpioNoIntmode
    };

   GPIO_Init(gpioLed.base, &led_d10);

}

int main(void)
{
   /* Initialize demo application pins setting and clock setting */
   hardware_init();

   /* Configure LED D10 pad */
   configure_gpio_pin(&gpioLed);

   /* Configure GPIO LED D10 */
   Init_GPIO_LED();

   /* Turn off the LED */
   GPIO_WritePinOutput(gpioLed.base, gpioLed.pin, gpioPinClear);

   /* Start the OSEK */
   debug_printf("Starting OSEK-OS in AppMode1\n");

   StartOS(AppMode1);

   /* we shouldn't return here */
   while(TRUE);
}

void ErrorHook(void)
{
	/* kernel panic :( */
    debug_printf("kernel panic\n");
	ShutdownOS(0);
}

TASK(TaskInit)
{
	/* Set 500 tick alarm for TaskPeriodic */
	debug_printf("InitTask: SetRelAlarm for TaskPeriodic.\n");
	SetRelAlarm(ActivateTaskPeriodic, 0, 500);

	/* Set 1000 tick callback alarm */
	debug_printf("InitTask: SetRelAlarm for AppCallback.\n");
	SetRelAlarm(AppCallbackAlarm, 100, 1000);

	/* Activate TaskBlink */
	debug_printf("InitTask: Activate TaskBlink.\n");
	ActivateTask(TaskBlink);

	/* Activate TaskBackground */
	ActivateTask(TaskBackground);

	/* end InitTask */
	debug_printf("InitTask: TerminateTask().\n");
	TerminateTask();
}

/*
 * This task waits for an event to be set in order
 * to continue execution.
 */
TASK(TaskBlink)
{
    static bool flag = FALSE;

	debug_printf("TaskBlink: Init.\n");
	while(1)
	{
		debug_printf("TaskBlink: Waiting for event...\n");
		WaitEvent(evBlink);
		ClearEvent(evBlink);
		debug_printf("TaskBlink: LED Toggle.\n");

        /* Toggle the LED */
		if(TRUE == flag)
        {
            GPIO_WritePinOutput(gpioLed.base, gpioLed.pin, gpioPinClear);
            flag = FALSE;
        }
        else
        {
            GPIO_WritePinOutput(gpioLed.base, gpioLed.pin, gpioPinSet);
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
	debug_printf("TaskPeriodic: Event set.\n");
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
	debug_printf("TaskBackground: Running!\n");
	while(1)
	{
		i++;
		if(i == 0xFFFFF)
		{
			debug_printf("TaskBackground still running...\n");
			i = 0;
		}
	}
}

/*
 * Alarm Callback example.
 */
ALARMCALLBACK(AppCallback)
{
	debug_printf("AppCallback.\n");
}


/*******************************************************************************
 * EOF
 ******************************************************************************/
