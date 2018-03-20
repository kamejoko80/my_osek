/*
 *  Copyright (C) : 2018
 *  File name     : trace.c
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
#include "fifo.h"
#include "os.h"

/***************************************************************
 *  MACRO DEFINITION
 ***************************************************************/

#define SYS_TRACE_MAX_MSG_QUEUE (100)
#define SYS_TRACE_MAX_MSG_LEN   (256)
#define SYS_TRACE_BUF_SIZE      (SYS_TRACE_MAX_MSG_LEN * SYS_TRACE_MAX_MSG_QUEUE)

#define TIME_FORMAT_SIZE        (13)
#define SEPARATE_CHAR           ':'


/***************************************************************
 *  GLOBAL VARIABLE DEFINITION
 ***************************************************************/

/*
 * System Tick Counter
 */
volatile uint32_t g_SystemTickCounter = 0;

/*
 * FIFO objects definition
 */
static Fifo_t g_SysTraceFifo;

/*
 * FIFO buffers definition
 */
static uint8_t g_SysTraceBuff[SYS_TRACE_BUF_SIZE];

/*
 * System trace temporally buffer
 */
static char g_SysTraceTempBuff[SYS_TRACE_MAX_MSG_LEN];


/***************************************************************
 *  EXTERNAL FUNCTION PROTOYPE
 ***************************************************************/

/***************************************************************
 *  FUNCTION PROTOYPE
 ***************************************************************/

/***************************************************************
 *  FUNCTION DEFINITION
 ***************************************************************/

void SysTrace_Init(void)
{
    /* FIFO initialization */
    FifoInit(&g_SysTraceFifo, g_SysTraceBuff, SYS_TRACE_BUF_SIZE);

    /* Set 1ms system tick callback alarm */
    SetRelAlarm(SysTickCallbackAlarm, 0, 1);
}

uint32_t SysTrace_GetTime(char *TimeStr)
{
    uint32_t TickCount = g_SystemTickCounter;
    uint32_t Hour, Minute, Second, MilliSecond;
    char str[TIME_FORMAT_SIZE] = {'0', '0', 'h', '0', '0', 'm', '0', '0', 's', '0', '0', '0', 0};
    char digit[4] = {0};

    /*
     * Format : DD:HH:MM:SS:UUU
     * Example: 00h24m35s192
     */

    /* Hour */
    Hour = TickCount / (1000 * 60 * 60);
    /* Only keep 2 digits for hour */
    Hour %= 100;

    /* Minute */
    TickCount %= (1000 * 60 * 60);
    Minute = TickCount / (1000 * 60);

    /* Second */
    TickCount %= (1000 * 60);
    Second = TickCount / 1000;

    /* Millisecond */
    MilliSecond = TickCount % 1000;

    /* Convert hour to string */
    itoa(Hour, digit, 10);

    if(Hour < 10)
    {
        memcpy(&str[1], digit, strlen(digit));
    }
    else
    {
        memcpy(&str[0], digit, strlen(digit));
    }

    /* Convert minute to string */
    itoa(Minute, digit, 10);

    if(Minute < 10)
    {
        memcpy(&str[4], digit, strlen(digit));
    }
    else
    {
        memcpy(&str[3], digit, strlen(digit));
    }

    /* Convert second to string */
    itoa(Second, digit, 10);

    if(Second < 10)
    {
        memcpy(&str[7], digit, strlen(digit));
    }
    else
    {
        memcpy(&str[6], digit, strlen(digit));
    }

    /* Convert millisecond to string */
    itoa(MilliSecond, digit, 10);

    if (MilliSecond < 10)
    {
        memcpy(&str[11], digit, strlen(digit));
    }
    else if (MilliSecond < 100)
    {
        memcpy(&str[10], digit, strlen(digit));
    }
    else
    {
        memcpy(&str[9], digit, strlen(digit));
    }

    memcpy(TimeStr, str, strlen(str));

    return strlen(str);
}

void SysTrace_Message(char *Format, ...)
{
    va_list args;
    uint32_t Len;
    char *Message;
    char TimeStamp[TIME_FORMAT_SIZE] = {0};

    /* Get system time stamp */
    Len = SysTrace_GetTime(TimeStamp);

    /* Reset message buffer */
    memset(g_SysTraceTempBuff, 0, SYS_TRACE_MAX_MSG_LEN);

    /* Copy time stamp */
    memcpy(g_SysTraceTempBuff, TimeStamp, Len);

    /* Move to message position */
    Message = &g_SysTraceTempBuff[Len];

    /* Add separate character */
    *Message = SEPARATE_CHAR;
    Message++;
    *Message = ' ';
    Message++;

    /* Get message contain */
    va_start(args, Format);

    /* Store message */
    vsprintf(Message, Format, args);

    /* Push data into the FIFO */
    FifoPushMulti(&g_SysTraceFifo, (uint8_t *)g_SysTraceTempBuff, SYS_TRACE_MAX_MSG_LEN);

    /* Raise a system trace message queue event */
    SetEvent(TaskIdle, evSysTraceMsgQueue);
}

void SysTrace_PrintOut(void)
{
    if(FifoGetDataSize(&g_SysTraceFifo) >= SYS_TRACE_MAX_MSG_LEN)
    {
        memset(g_SysTraceTempBuff, 0, SYS_TRACE_MAX_MSG_LEN);
        FifoPopMulti(&g_SysTraceFifo, (uint8_t *)g_SysTraceTempBuff, SYS_TRACE_MAX_MSG_LEN);
        printf("%s\r\n", g_SysTraceTempBuff);
    }
    else
    {
        /* Clear the event if there is no saved buffer data */
        ClearEvent(evSysTraceMsgQueue);
    }
}

/*!
 * Function : Manage IPC data received event
 * Context  : TaskIPC
 */
void SysTrace_ManageMsgQueueEvent(EventMaskType eventMask)
{
    if (eventMask & evSysTraceMsgQueue)
    {
        /* Print out the message trace */
        SysTrace_PrintOut();
    }
}

/*
 * System Tick Alarm Callback.
 */
ALARMCALLBACK(SysTickCallback)
{
    g_SystemTickCounter++;
}

