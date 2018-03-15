/*
 *  Copyright (C) : 2018
 *  File name     : ipc.c
 *  Author        : Dang Minh Phuong
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
#include "trace.h"

/***************************************************************
 *  MACRO DEFINITION
 ***************************************************************/
#define EXTI0_IRQ 6 /* EXT0 IRQ number */

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
static void IPC_ManageDataReceived(EventMaskType eventMask);
void IPC_SPITransferQueue(void);
void IPC_TransferCompleted(void);

/***************************************************************
 *  FUNCTION DEFINITION
 ***************************************************************/

/*!
 * Function : IPC_Init
 * Context  : Task
 */
void IPC_Init(void)
{
    /* FIFO initialization */
    FifoInit(&g_TxFifo, g_TxFifoBuff, FIFO_BUF_SIZE);
    FifoInit(&g_RxFifo, g_RxFifoBuff, FIFO_BUF_SIZE);

#ifdef SPI_MASTER
    SPI_Config(true);
#else
    SPI_Config(false);
#endif

    g_IsIPCInit = true;
}

/*!
 * Function : IPC_InitStatus
 * Context  : Task
 */
bool IPC_InitStatus(void)
{
    return g_IsIPCInit;
}

/*!
 * Function : IPC_GpioTransferRequestSignal
 * Context  : Task
 */
static void IPC_GpioTransferRequestSignal(void)
{
    /* Generate transfer request signal on GPIO */
    SPI_RequestOutSetValue(false);
    SPI_RequestOutSetValue(true);
}

/*!
 * Function : IPC_DisableIntRqstSignal
 * Context  : Task
 */
static void IPC_DisableIntRqstSignal(void)
{
    NVIC_DisableIRQ(EXTI0_IRQ);
}

/*!
 * Function : IPC_EnableIntRqstSignal
 * Context  : Task
 */
static void IPC_EnableIntRqstSignal(void)
{
    NVIC_EnableIRQ(EXTI0_IRQ);
}

/*!
 * Function : SPI transfer request
 * Context  : Interrupt or TaskIPC
 */
void IPC_SPITransferQueue(void)
{
    /* Reset IPC transmit buffer */
    memset(g_TxBuff, 0, IPC_TRANSFER_LEN + 1);

    /* Fetch data from Tx FIFO buffer */
    FifoPopMulti(&g_TxFifo, g_TxBuff, IPC_TRANSFER_LEN);

    /* SPI transfer request */
    SPI_AsyncTransfer(g_TxBuff, g_RxBuff, IPC_TRANSFER_LEN + 1, &IPC_TransferCompleted);

#ifndef SPI_MASTER
    /* Generate slaver transfer request signal */
    IPC_GpioTransferRequestSignal();
#endif

}

/*!
 * Function : IPC transfer complete
 * Context  : Interrupt
 */
void IPC_TransferCompleted(void)
{
    IPC_Frame_t *Frame = (IPC_Frame_t *)g_RxBuff;

    if (IPC_Frame_Check(Frame))
    {
        /* Pushes data to Rx FIFO buffer */
        FifoPushMulti(&g_RxFifo, g_RxBuff, IPC_TRANSFER_LEN);

        /* Notify data received handler */
        SetEvent(TaskIPC, evIPCDataReceived);
    }

#ifndef SPI_MASTER
        /* Notify slaver transfer complete */
        SetEvent(TaskIPC, evIPCSlaverSendComplete);
#endif

}

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
 * Function : Manage IPC data received event
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

#ifndef SPI_MASTER
/*!
 * Function : Manage slaver transfer complete
 * Context  : TaskIPC
 */
static void IPC_ManageSlaverTransferComplete(EventMaskType eventMask)
{
    if (eventMask & evIPCSlaverSendComplete)
    {
        if(FifoGetDataSize(&g_TxFifo) >= IPC_TRANSFER_LEN)
        {
            /* Queue data transfer */
            IPC_SPITransferQueue();
        }

        /* Clear the event */
        ClearEvent(evIPCSlaverSendComplete);
    }
}
#endif

/*!
 * Function : IPC data transfer request
 * Context  : Any
 */
void IPC_Send(uint8_t *Data, uint16_t Len)
{
    IPC_Frame_t *Frame = (IPC_Frame_t *)g_TmpBuff;

    /* Push data into the Tx FIFO buffer */
    if(FifoGetFreeSize(&g_TxFifo) >= IPC_TRANSFER_LEN)
    {
        if(IPC_Frame_Create(Frame, Data, Len))
        {
            /* Critical section enter */
            IPC_DisableIntRqstSignal();

            /* Push data into the Tx FIFO */
            FifoPushMulti(&g_TxFifo, (uint8_t *)Frame, IPC_TRANSFER_LEN);

            /* Critical section exit */
            IPC_EnableIntRqstSignal();
        }
    }

#ifdef SPI_MASTER
    /* Generate master transfer request signal */
    IPC_GpioTransferRequestSignal();
#else
    /* Trigger data transfer request */
    SetEvent(TaskIPC, evIPCSlaverSendComplete);
#endif

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
    waitEventMask |= evIPCDataReceived | evIPCSlaverSendComplete;

    /* TaskIPC main loop */
	while(1)
	{
            /*
             * Task will switch to WAIT state
             * after calling the following function
             */
            WaitEvent(waitEventMask);

            /* Check event and do the corresponding process */
            if (E_OK == GetEvent(TaskIPC, &eventMask))
            {
                /* IPC transfer request complete */
                IPC_ManageDataReceived(eventMask);

                #ifndef SPI_MASTER
                /* Manage IPC slaver transfer complete */
                IPC_ManageSlaverTransferComplete(eventMask);
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

