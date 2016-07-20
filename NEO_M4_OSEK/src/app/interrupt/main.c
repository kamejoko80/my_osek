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
#include "board.h"
#include "gpio_pins.h"
#include "gpio_imx.h"
#include "uart_imx.h"
#include "debug_console_imx.h"
#include "os.h"

////////////////////////////////////////////////////////////////////////////////
// Macro definition
////////////////////////////////////////////////////////////////////////////////

#define BUFF_SIZE 32


////////////////////////////////////////////////////////////////////////////////
// Global variables definition
////////////////////////////////////////////////////////////////////////////////

typedef void(*CallBack_Type)(uint8_t * buffer, uint8_t len);

static uint8_t        g_len = 0;
static uint8_t        g_rx_count = 0;
static uint8_t       *g_buffer = 0;
static CallBack_Type  g_callback = 0;
static uint8_t        g_rx_buffer[BUFF_SIZE];

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

void UART_AsyncReceive(uint8_t len, uint8_t * buffer, CallBack_Type CallBack);
void UART_RxComplete(uint8_t * buffer, uint8_t len);
void Menu_Display(void);
void Process_Item(uint32_t Item);

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
   while(1);
}

void ErrorHook(void)
{
	/* kernel panic :( */
    debug_printf("kernel panic\n");
	ShutdownOS(0);
}


/*
 * This task waits for an event to be set in order
 * to continue execution.
 */
TASK(TaskMenu)
{
    EventMaskType Event;

	while(1)
	{
	    /* Display the menu content */
	    Menu_Display();

	    /* Clear input buffer */
        memset((char *)g_rx_buffer, 0, BUFF_SIZE);

        /* Get UART input */
        UART_AsyncReceive(20, g_rx_buffer, &UART_RxComplete);

        /* Wait for event */
		if (E_OK == WaitEvent(evUART))
        {
            /* Get event */
            GetEvent(TaskMenu, &Event);
            ClearEvent(evUART);

            /* Check incoming event and process */
            if (evUART & Event)
            {
                switch (g_rx_buffer[0])
                {
                    case '0':
                        /* Return to display menu */
                    break;
                    case '1':
                        Process_Item((uint32_t)(g_rx_buffer[0] - '0'));
                    break;
                    case '2':
                        Process_Item((uint32_t)(g_rx_buffer[0] - '0'));
                    break;
                    case '3':
                        Process_Item((uint32_t)(g_rx_buffer[0] - '0'));
                    break;
                    case '4':
                        Process_Item((uint32_t)(g_rx_buffer[0] - '0'));
                    break;
                    default:
                    break;
                }
            }
        }


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

void Menu_Display(void)
{
    debug_printf("\r\n--------- UDOO-NEO OSEK DEMO -------\r\n");
    debug_printf("0: Display Menu\r\n");
    debug_printf("1: Item 1\r\n");
    debug_printf("2: Item 2\r\n");
    debug_printf("3: Item 3\r\n");
    debug_printf("4: Item 4\r\n");
}

void Process_Item(uint32_t Item)
{
    EventMaskType Event;

    /* Do the item process here */
    debug_printf("\r\n");
    debug_printf("Processing item %d...\r\n", Item);

    /* Wait for keyboard input after doing the process */
    debug_printf("Press any key to exit\r\n");

	/* Clear input buffer */
    memset((char *)g_rx_buffer, 0, BUFF_SIZE);

    /* Get UART input */
    UART_AsyncReceive(20, g_rx_buffer, &UART_RxComplete);

    WaitEvent(evUART);
    GetEvent(TaskMenu, &Event);
    ClearEvent(evUART);
}

void UART_SendChar(char c)
{
    UART_Putchar(UART5, c);
    while (!UART_GetStatusFlag(UART5, uartStatusTxComplete));
}

void UART_SendString(char *str)
{
    while(*str != 0)
    {
        UART_SendChar(*str);
        str++;
    }
}

void UART_AsyncReceive(uint8_t len, uint8_t * buffer, CallBack_Type CallBack)
{
  /* Initialize global variables */
  if ((g_buffer == NULL) && (len > 0))
  {
     g_buffer = buffer;
     g_len = len;
     g_rx_count = 0;
     g_callback = CallBack;

     /* Enable UART RX interrupt */
     UART_SetIntCmd(UART5, uartIntRxDataReady, true);
  }
}

void UART_RxComplete(uint8_t * buffer, uint8_t len)
{
	UART_SendString((char *)buffer);
	/* Send event to TaskMenu */
	SetEvent(TaskMenu, evUART);
}

ISR(UART5_Handler)
{
    bool ret;
    char c;

    /* Get the status of RX int flag */
    ret = UART_GetStatusFlag(UART5, uartStatusRxReady);

    /* Reset the RX int flag */
    if (ret)
    {
        /* Get UART data */
        c = UART_Getchar(UART5);

        /* Send the Echo */
        UART_SendChar(c);

        /* Check if we received enough data */
        if ((g_len > 0) && g_buffer && (g_rx_count < g_len))
        {
            if (('\n' != c) && ('\r' != c))
            {
                g_buffer[g_rx_count] = c;
                g_rx_count++;
            }

            if (('\r' == c) || ('\n' == c) || (g_rx_count >= g_len))
            {
                /* Run call back function */
                if (g_callback != NULL)
                {
                    g_callback(g_buffer, g_rx_count);
                }

                /* Reset global variables */
                g_buffer = 0;
                g_rx_count = 0;
                g_len = 0;

                /* Disable UART RX interrupt */
                UART_SetIntCmd(UART5, uartIntRxDataReady, false);
            }
        }

        /* Clear flag to accept next data */
        UART_ClearStatusFlag(UART5, uartStatusRxReady);
    }

}

/*******************************************************************************
 * EOF
 ******************************************************************************/
