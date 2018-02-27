/*
 *  Copyright (C) : 2018
 *  File name     : ipc.c
 *	Author        : Dang Minh Phuong
 *  Email         : kamejoko80@yahoo.com
 *
 *  This program is free software, you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "ipc.h"
#include "os.h"

/***************************************************************
 *  MACRO DEFINITION
 ***************************************************************/
#define IPC_MASTER_TRANSMIT_INTERVAL 10 /* ms */

/***************************************************************
 *  GLOBAL VARIABLE DEFINITION
 ***************************************************************/
/*
 * IPC buffers definition
 */
static uint8_t g_TxBuff[IPC_TRANSFER_LEN + 1] = {0};
static uint8_t g_RxBuff[IPC_TRANSFER_LEN + 1] = {0};

/*
 * Temporary buffers definition
 */
static uint8_t g_TmpBuff[IPC_TRANSFER_LEN] = {0};

/*
 * FIFO buffers definition
 */
static uint8_t g_TxFifoBuff[FIFO_BUF_SIZE];
static uint8_t g_RxFifoBuff[FIFO_BUF_SIZE];

/*
 * FIFO objects definition
 */
static Fifo_t g_TxFifo;
static Fifo_t g_RxFifo;

/*
 * IPC Initialization status
 */
 static bool g_IsIPCInit = false;

/***************************************************************
 *  EXTERNAL FUNCTION PROTOYPE
 ***************************************************************/
extern bool IPC_Frame_Create(IPC_Frame_t *Frame, uint8_t *Data, uint16_t Len);
extern bool IPC_Frame_Check(IPC_Frame_t *Frame);
extern void IPC_Frame_Print(IPC_Frame_t *Frame);

/***************************************************************
 *  FUNCTION PROTOYPE
 ***************************************************************/
static void IPC_SPITransferQueue(void);
static void IPC_ManageDataReceived(EventMaskType eventMask);
void IPC_TransferCompleted(void);

/***************************************************************
 *  FUNCTION DEFINITION
 ***************************************************************/
void IPC_Init(void)
{
    /* FIFO initialization */
    FifoInit(&g_TxFifo, g_TxFifoBuff, FIFO_BUF_SIZE);
    FifoInit(&g_RxFifo, g_RxFifoBuff, FIFO_BUF_SIZE);

#ifdef SPI_MASTER
    SPI_Config(true);
#else
    SPI_Config(false);
    IPC_SPITransferQueue();
#endif

    g_IsIPCInit = true;
}

bool IPC_InitStatus(void)
{
    return g_IsIPCInit;
}

/*!
 * Function : SPI transfer request
 * Context  : Interrupt or TaskIPC
 */
static void IPC_SPITransferQueue(void)
{
    /* Master transfer request */
    SPI_AsyncTransfer(g_TxBuff, g_RxBuff, IPC_TRANSFER_LEN + 1, &IPC_TransferCompleted);

#ifndef SPI_MASTER
    /* Signals that SPI slaver is free */
    SPI_RequestOutSetValue(true);
#endif
}

/*!
 * Function : IPC transfer complete
 * Context  : Interrupt
 */
void IPC_TransferCompleted(void)
{
    IPC_Frame_t *Frame = (IPC_Frame_t *)g_RxBuff;

#ifndef SPI_MASTER
    /* Signals that SPI slaver is busy */
    SPI_RequestOutSetValue(false);
#endif

    if (IPC_Frame_Check(Frame))
    {
        /* Pushes data to Rx FIFO buffer */
        FifoPushMulti(&g_RxFifo, g_RxBuff, IPC_TRANSFER_LEN);

        /* Notify data received handler */
        SetEvent(TaskIPC, evIPCDataReceived);
    }

#ifndef SPI_MASTER
    /* Reset IPC slaver transmit buffer */
    memset(g_TxBuff, 0, IPC_TRANSFER_LEN + 1);

    /* Fetch data from Tx FIFO buffer */
    FifoPopMulti(&g_TxFifo, g_TxBuff, IPC_TRANSFER_LEN);

    /* Slaver transfer request SPI DMA queue */
    IPC_SPITransferQueue();
#endif
}

#ifdef SPI_MASTER
/*!
 * Function : Manage periodic SPI master transfer request
 * Context  : TaskIPC
 */
static void IPC_ManageSPIMasterTransmit(EventMaskType eventMask)
{
    /*
     * No matter what Tx FIFO buffer empty or not
     * master should request SPI DMA transfer to
     * poll the received data from slaver
     */
    if (eventMask & evAlarmSPIMasterTransmit)
    {
        /* Check if SPI slaver is free */
        if(SPI_RequestInGetStatus())
        {
            /* Reset IPC transmit buffer */
            memset(g_TxBuff, 0, IPC_TRANSFER_LEN + 1);

            /* Fetch data from Tx FIFO buffer */
            FifoPopMulti(&g_TxFifo, g_TxBuff, IPC_TRANSFER_LEN);

            /* Master transfer request SPI DMA queue */
            IPC_SPITransferQueue();
        }

        /* Clear the event */
        ClearEvent(evAlarmSPIMasterTransmit);
    }
}
#endif

/*!
 * Function : IPC data received handler
 * Context  : TaskIPC
 */
void __attribute__((weak)) IPC_DataRxHandler(Fifo_t *Fifo)
{
    /* Pops data to free Rx FIFO buffer */
    FifoPopMulti(Fifo, g_TmpBuff, IPC_TRANSFER_LEN);
}

/*!
 * Function : Menage IPC data received event
 * Context  : TaskIPC
 */
static void IPC_ManageDataReceived(EventMaskType eventMask)
{
    if (eventMask & evIPCDataReceived)
    {
        /* Execute data received handler */
        IPC_DataRxHandler(&g_RxFifo);

        /* Toggles debug LED */
        STM_EVAL_LEDToggle(LED3);

        /* Clear the event */
        ClearEvent(evIPCDataReceived);
    }
}

/*!
 * Function : IPC data transfer request
 * Context  : Any
 */
void IPC_Send(uint8_t *Data, uint16_t Len)
{
    IPC_Frame_t *Frame = (IPC_Frame_t *)g_TmpBuff;

    if(FifoGetFreeSize(&g_TxFifo) >= IPC_TRANSFER_LEN)
    {
        if(IPC_Frame_Create(Frame, Data, Len))
        {
            FifoPushMulti(&g_TxFifo, (uint8_t *)Frame, IPC_TRANSFER_LEN);
        }
    }
}

/*!
 * Function : IPC task function
 * Context  : TaskIPC
 */
TASK(TaskIPC)
{
    EventMaskType waitEventMask = 0;
    EventMaskType eventMask;

	printf("TaskIPC: Init\n");

    /* Initialize IPC module */
    IPC_Init();

    /* Initialize wait events */
    waitEventMask |= evAlarmSPIMasterTransmit |
                     evIPCDataReceived;

#ifdef SPI_MASTER
    /* Start IPC master transfer periodic alarm */
    SetRelAlarm(AlarmSPIMasterTransmit, 10, IPC_MASTER_TRANSMIT_INTERVAL);
#endif

    /* TaskIPC main loop */
	while(1)
	{
            /*
             * Task will switched to WAIT state
             * after calling the following function
             */
            WaitEvent(waitEventMask);

            /* Check event and do the corresponding process */
            if (E_OK == GetEvent(TaskIPC, &eventMask))
            {
                    /* IPC transfer request complete */
                    IPC_ManageDataReceived(eventMask);

                #ifdef SPI_MASTER
                    /* Master transfer SPI DMA queue */
                    IPC_ManageSPIMasterTransmit(eventMask);
                #endif

                STM_EVAL_LEDToggle(LED5);
            }
            else
            {
                /* This should not be run */
                TerminateTask();
            }
	}

	/* This should not be run */
	TerminateTask();
}

