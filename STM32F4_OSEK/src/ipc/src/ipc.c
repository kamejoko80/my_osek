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
/***************************************************************
 *  FUNCTION PROTOYPE
 ***************************************************************/
#ifdef SPI_MASTER
    static void IPC_MasterTransferQueue(void);
#else
    static void IPC_SlaverTransferQueue(void);
#endif

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
    IPC_SlaverTransferQueue();
#endif

    g_IsIPCInit = true;
}

bool IPC_InitStatus(void)
{
    return g_IsIPCInit;
}

static bool IPC_FrameCheck(uint8_t *Buff, uint16_t Len)
{
    bool ret = false;

    if(Buff[0] != 0)
    {
        ret = true;
    }
    else
    {
        ret = false;
    }

    return ret;
}

#ifdef SPI_MASTER

void IPC_MasterTransferCompleted(void)
{
    if (IPC_FrameCheck(g_RxBuff, IPC_TRANSFER_LEN))
    {
        /* Pushes data to Rx FIFO buffer */
        FifoPushMulti(&g_RxFifo, g_RxBuff, IPC_TRANSFER_LEN);

        /* Notify Master data received */
        SetEvent(TaskIPC, evMasterDataReceived);
    }
}

static void IPC_MasterTransferQueue(void)
{
    /* Master transfer request */
    SPI_AsyncTransfer(g_TxBuff, g_RxBuff, IPC_TRANSFER_LEN + 1, &IPC_MasterTransferCompleted);
}

void IPC_MasterTransferRequest(uint8_t *Buff, uint16_t Len)
{
    uint16_t LenCopy;

    if(FifoGetFreeSize(&g_TxFifo) >= IPC_TRANSFER_LEN)
    {
        /* Length copy should be limited */
        if (Len < IPC_TRANSFER_LEN)
        {
            LenCopy = Len;
        }
        else
        {
            LenCopy = IPC_TRANSFER_LEN;
        }

        /* Copy data */
        memset(g_TmpBuff, 0, IPC_TRANSFER_LEN);
        memcpy(g_TmpBuff, Buff, LenCopy);

        /* Store data into Tx Fifo buffer */
        FifoPushMulti(&g_TxFifo, g_TmpBuff, IPC_TRANSFER_LEN);
    }
}

static void IPC_ManageIPCMasterTransmit(EventMaskType eventMask)
{
    /*
     * No matter what Tx FIFO buffer empty or not
     * master should request SPI DMA transfer to
     * poll the received data from slaver
     */
    if (eventMask & evAlarmIPCMasterTransmit)
    {
        /* Check if SPI slaver is free */
        if(SPI_RequestInGetStatus())
        {
            /* Reset IPC transmit buffer */
            memset(g_TxBuff, 0, IPC_TRANSFER_LEN + 1);

            /* Fetch data from Tx FIFO buffer */
            FifoPopMulti(&g_TxFifo, g_TxBuff, IPC_TRANSFER_LEN);

            /* Master transfer request SPI DMA queue */
            IPC_MasterTransferQueue();
        }

        /* Clear the event */
        ClearEvent(evAlarmIPCMasterTransmit);
    }
}

void __attribute__((weak)) IPC_MasterDataRxHandler(Fifo_t *Fifo)
{
    /* Pops data to free Rx FIFO buffer */
    FifoPopMulti(Fifo, g_TmpBuff, IPC_TRANSFER_LEN);
}

static void IPC_ManageMasterDataReceived(EventMaskType eventMask)
{
    if (eventMask & evMasterDataReceived)
    {
        /* Execute data received handler */
        IPC_MasterDataRxHandler(&g_RxFifo);

        /* Toggles debug LED */
        STM_EVAL_LEDToggle(LED3);

        /* Clear the event */
        ClearEvent(evMasterDataReceived);
    }
}

#else /* SPI_MASTER */

void IPC_SlaverTransferCompleted(void)
{
    /* Signals that SPI slaver is busy */
    SPI_RequestOutSetValue(false);

    if (IPC_FrameCheck(g_RxBuff, IPC_TRANSFER_LEN))
    {
        /* Pushes data to Rx FIFO buffer */
        FifoPushMulti(&g_RxFifo, g_RxBuff, IPC_TRANSFER_LEN);

        /* Notify Slaver data received */
        SetEvent(TaskIPC, evSlaverDataReceived);
    }

    /* Reset IPC transmit buffer */
    memset(g_TxBuff, 0, IPC_TRANSFER_LEN + 1);

    /* Fetch data from Tx FIFO buffer */
    FifoPopMulti(&g_TxFifo, g_TxBuff, IPC_TRANSFER_LEN);

    /* Slaver transfer request SPI DMA queue */
    IPC_SlaverTransferQueue();

}

static void IPC_SlaverTransferQueue(void)
{
    /* Master transfer request */
    SPI_AsyncTransfer(g_TxBuff, g_RxBuff, IPC_TRANSFER_LEN + 1, &IPC_SlaverTransferCompleted);

    /* Signals that SPI slaver is free */
    SPI_RequestOutSetValue(true);
}

void IPC_SlaverTransferRequest(uint8_t *Buff, uint16_t Len)
{
    uint16_t LenCopy;

    if(FifoGetFreeSize(&g_TxFifo) >= IPC_TRANSFER_LEN)
    {
        /* Length copy should be limited */
        if (Len < IPC_TRANSFER_LEN)
        {
            LenCopy = Len;
        }
        else
        {
            LenCopy = IPC_TRANSFER_LEN;
        }

        /* Copy data */
        memset(g_TmpBuff, 0, IPC_TRANSFER_LEN);
        memcpy(g_TmpBuff, Buff, LenCopy);

        /* Store data into Tx Fifo buffer */
        FifoPushMulti(&g_TxFifo, g_TmpBuff, IPC_TRANSFER_LEN);
    }

}

void __attribute__((weak)) IPC_SlaverDataRxHandler(Fifo_t *Fifo)
{
    /* Pops data to free Rx FIFO buffer */
    FifoPopMulti(Fifo, g_TmpBuff, IPC_TRANSFER_LEN);
}

static void IPC_ManageSlaverDataReceived(EventMaskType eventMask)
{
    if (eventMask & evSlaverDataReceived)
    {
        /* Execute data received handler */
        IPC_SlaverDataRxHandler(&g_RxFifo);

        /* Toggles debug LED */
        STM_EVAL_LEDToggle(LED3);

        /* Clear the event */
        ClearEvent(evSlaverDataReceived);
    }
}

#endif /* SPI_MASTER */

TASK(TaskIPC)
{
    EventMaskType waitEventMask = 0;
    EventMaskType eventMask;

	printf("TaskIPC: Init\n");

    /* Initialize IPC module */
    IPC_Init();

    /* Initialize wait events */
    waitEventMask |= evAlarmIPCMasterTransmit |
                     evMasterDataReceived |
                     evSlaverDataReceived;

#ifdef SPI_MASTER
    /* Start IPC master transfer periodic alarm */
    SetRelAlarm(AlarmIPCMasterTransmit, 10, IPC_MASTER_TRANSMIT_INTERVAL);
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
                #ifdef SPI_MASTER
                    /* Master transfer request complete */
                    IPC_ManageMasterDataReceived(eventMask);

                    /* Master transfer SPI DMA queue */
                    IPC_ManageIPCMasterTransmit(eventMask);
                #else
                    /* Slaver data received event */
                    IPC_ManageSlaverDataReceived(eventMask);
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

