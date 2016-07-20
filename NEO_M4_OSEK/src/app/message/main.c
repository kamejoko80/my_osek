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
#include <string.h>
#include <stdlib.h>
#include "board.h"
#include "gpio_pins.h"
#include "gpio_imx.h"
#include "uart_imx.h"
#include "debug_console_imx.h"
#include "os.h"
#include "message.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definition
////////////////////////////////////////////////////////////////////////////////

#define BUFF_SIZE 32

////////////////////////////////////////////////////////////////////////////////
// Global variables definition
////////////////////////////////////////////////////////////////////////////////

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
   debug_printf("Starting OSEK-OS in AppMode1\r\n");

   StartOS(AppMode1);

   /* we shouldn't return here */
   while(1);
}

void ErrorHook(void)
{
	/* kernel panic :( */
    debug_printf("kernel panic\r\n");
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
            debug_printf("could not get message\r\n");
            break;
        }

        debug_printf("MsgRcv1 : %X %X %X %X\r\n",
                                MsgRcv1->data[0],
                                MsgRcv1->data[1],
                                MsgRcv1->data[2],
                                MsgRcv1->data[3]);

        debug_printf("MsgRcv2 : %X %X %X %X\r\n",
                                MsgRcv2->data[0],
                                MsgRcv2->data[1],
                                MsgRcv2->data[2],
                                MsgRcv2->data[3]);

        /* Free message */
        Message_Free(MsgRcv1);
        Message_Free(MsgRcv2);
	}

	TerminateTask();
}

/*
 * This task sends message periodically
 */
TASK(TaskSend)
{
    MessageType *Msg1, *Msg2;

    /* Start periodic alarm */
    SetRelAlarm(AlarmSend, 100, 1000);

	while(1)
	{
        /* Wait for alarm */
		WaitEvent(evAlarmSend);
		ClearEvent(evAlarmSend);

        /* Allocate message */
        Msg1 = Message_Allocate(4);
        Msg2 = Message_Allocate(4);

        if ((Msg1 == NULL) || (Msg1 == NULL))
        {
            debug_printf("could not allocate message\r\n");
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


/*******************************************************************************
 * EOF
 ******************************************************************************/
