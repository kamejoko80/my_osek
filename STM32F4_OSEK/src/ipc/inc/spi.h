/*
 *  Copyright (C) : 2016
 *  File name     : spi.h
 *  Author        : Dang Minh Phuong
 *  Email         : kamejoko80@yahoo.com
 *
 *  This program is free software, you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */

#ifndef __SPI_H__
#define __SPI_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

typedef void(*spi_cb_t)(void);

/**
 * @brief         SPI bus configuration
 * @param[in]     bool Master : Master = true, Slaver = false
 * @param[in,out] None
 * @return        void
 */
void SPI_Config(bool Master);

/**
 * @brief         Set up DMA source/destination buffer for a SPI transfer
 * @param[in]     uint8_t *TxBuffer
 * @param[in]     uint8_t *RxBuffer
 * @param[in]     uint32_t Len
 * @param[in,out] None
 * @return        void
 */
void SPI_ConfigTransfer(uint8_t *TxBuffer, uint8_t *RxBuffer, uint32_t Len);

/**
 * @brief         Start request DMA transfer of SPI bus
 * @param[in]     None
 * @param[in,out] None
 * @return        void
 */
void SPI_StartTransfer(void);

/**
 * @brief         Stop DMA transfer of SPI bus
 * @param[in]     None
 * @param[in,out] None
 * @return        void
 */
void SPI_StopTransfer(void);

/**
 * @brief         Wait for DMA transfer to be completed
 *                (used in synchronous transfer mode)
 * @param[in]     None
 * @param[in,out] None
 * @return        void
 */
void SPI_WaitTransferComplete(void);

/**
 * @brief         Start asynchronous DMA transfer request, this function will not be locked,
 *                a call back function will be called after DMA transfer complete.
 * @param[in]     uint8_t *TxBuffer
 * @param[out]    uint8_t *RxBuffer
 * @param[in]     uint32_t Len
 * @param[in]     spi_cb_t CallBack
 * @return        void
 */
void SPI_AsyncTransfer(uint8_t *TxBuffer, uint8_t *RxBuffer, uint32_t Len, spi_cb_t CallBack);

/**
 * @brief         Start synchronous DMA transfer request, this function will be locked
 *                until DMA transfer is completed.
 * @param[in]     uint8_t *TxBuffer
 * @param[out]    uint8_t *RxBuffer
 * @param[in]     uint32_t Len
 * @return        void
 */
void SPI_SyncTransfer(uint8_t *TxBuffer, uint8_t *RxBuffer, uint32_t Len);

/**
 * @brief         Request In interrupt Enable/Disable
 * @param[in]     bool Enable
 * @param[in,out] None
 * @return        void
 */
void SPI_RequestInExtiConfig(bool Enable);

/**
 * @brief         Request In interrupt Enable/Disable
 * @param[in]     bool Enable
 * @param[in,out] None
 * @return        void
 */
bool SPI_RequestInGetStatus(void);

/**
 * @brief         Request Out put signal
 * @param[in]     bool Val
 * @param[in,out] None
 * @return        void
 */
void SPI_RequestOutSetValue(bool Val);

#endif
