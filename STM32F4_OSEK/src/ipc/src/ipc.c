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

#include "spi.h"
#include "ipc.h"
#include "fifo.h"

/***************************************************************
 *  MACRO DEFINITION
 ***************************************************************/

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

/***************************************************************
 *  EXTERNAL FUNCTION PROTOYPE
 ***************************************************************/
extern void MasterRxDataHandler(Fifo_t *fifo);
extern void SlaverRxDataHandler(Fifo_t *fifo);

/***************************************************************
 *  FUNCTION PROTOYPE
 ***************************************************************/
static void IPC_SlaverTransferQueue(void);
static void IPC_MasterTransferQueue(void);

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

void IPC_MasterTransferCompleted(void)
{
    if (IPC_FrameCheck(g_RxBuff, IPC_TRANSFER_LEN))
    {
        /* Pushes data to Rx FIFO buffer */
        FifoPushMulti(&g_RxFifo, g_RxBuff, IPC_TRANSFER_LEN);

        /* Execute data Rx callback function */
        MasterRxDataHandler(&g_RxFifo);
    }
}

void IPC_SlaverTransferCompleted(void)
{
    if (IPC_FrameCheck(g_RxBuff, IPC_TRANSFER_LEN))
    {
        /* Pushes data to Rx FIFO buffer */
        FifoPushMulti(&g_RxFifo, g_RxBuff, IPC_TRANSFER_LEN);

        /* Execute data Rx callback function */
        SlaverRxDataHandler(&g_RxFifo);
    }

    /* Reset IPC transmit buffer */
    memset(g_TxBuff, 0, IPC_TRANSFER_LEN + 1);

    /* Fetch data from Tx FIFO buffer */
    FifoPopMulti(&g_TxFifo, g_TxBuff, IPC_TRANSFER_LEN);

    /* Slaver transfer request DMA queue */
    IPC_SlaverTransferQueue();
}

static void IPC_MasterTransferQueue(void)
{
    /* Master transfer request */
    SPI_AsyncTransfer(g_TxBuff, g_RxBuff, IPC_TRANSFER_LEN + 1, &IPC_MasterTransferCompleted);
}

static void IPC_SlaverTransferQueue(void)
{
    /* Master transfer request */
    SPI_AsyncTransfer(g_TxBuff, g_RxBuff, IPC_TRANSFER_LEN + 1, &IPC_SlaverTransferCompleted);
}

void IPC_MasterTransferRequest(uint8_t *Buff, uint16_t Len)
{
    uint16_t LenCopy;

    /* Length copy should be limited */
    if (Len < IPC_TRANSFER_LEN)
    {
        LenCopy = Len;
    }
    else
    {
        LenCopy = IPC_TRANSFER_LEN;
    }

    /* Copy data to Tx buffer */
    memset(g_TxBuff, 0, IPC_TRANSFER_LEN);
    memcpy(g_TxBuff, Buff, LenCopy);

    /* Starts SPI transfer */
    IPC_MasterTransferQueue();
}

void IPC_SlaverTransferRequest(uint8_t *Buff, uint16_t Len)
{
    uint16_t LenCopy;

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
