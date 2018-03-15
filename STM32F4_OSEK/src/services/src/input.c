/*
 *  Copyright (C) : 2018
 *  File name     : input.c
 *  Author        : Dang Minh Phuong
 *  Email         : kamejoko80@yahoo.com
 *
 *  This program is free software, you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "stm32f4xx.h"
#include "uart_debug.h"
#include "input.h"
#include "os.h"

/***************************************************************
 *  MACRO DEFINITION
 ***************************************************************/

/***************************************************************
 *  GLOBAL VARIABLE DEFINITION
 ***************************************************************/

/*
 * Input buffer objects definition
 */
static uint32_t       g_Len = 0;
static uint32_t       g_RxCount = 0;
static char          *g_Buffer = 0;
static CallBackType   g_CallBack = 0;

/***************************************************************
 *  EXTERNAL FUNCTION PROTOYPE
 ***************************************************************/

/***************************************************************
 *  FUNCTION PROTOYPE
 ***************************************************************/

/***************************************************************
 *  FUNCTION DEFINITION
 ***************************************************************/

void Input_GetsAsync(char *Buffer, uint32_t Len, CallBackType CallBack)
{
    /* Initialize global variables */
    if (g_Buffer == NULL)
    {
        g_Buffer = Buffer;
        g_Len = Len;
        g_RxCount = 0;
        g_CallBack = CallBack;

        /* Enable UART RX interrupt */
        USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    }
}

ISR (USART2_Handler)
{
    char c;

    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        /* Get UART data */
        c = (char)USART_ReceiveData(USART2);

        /* Send the Echo */
        SendChar(c);

        /* Check if we received enough data */
        if (g_Buffer && (g_RxCount < g_Len))
        {
            if (('\n' != c) && ('\r' != c))
            {
                g_Buffer[g_RxCount] = c;
                g_RxCount++;
            }

            if (('\r' == c) || ('\n' == c) || (g_RxCount >= g_Len))
            {
                /* Run call back function */
                if (g_CallBack != NULL)
                {
                    g_CallBack(g_Buffer, g_RxCount);
                }

                /* Reset global variables */
                g_Buffer = 0;
                g_RxCount = 0;
                g_Len = 0;

                /* Disable UART RX interrupt */
                USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
            }
        }

        /* Clear USART pending interrupt flag */
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    }
}
