/*
 *  Copyright (C) : 2018
 *  File name     : ipc.h
 *	Author        : Dang Minh Phuong
 *  Email         : kamejoko80@yahoo.com
 *
 *  This program is free software, you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */

#ifndef __IPC_H__
#define __IPC_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "spi.h"
#include "fifo.h"
#include "frame.h"

#define SPI_MASTER

/**
 * @brief         IPC_Init
 * @param[in]     None
 * @param[in,out] None
 * @return        void
 */
void IPC_Init(void);

/**
 * @brief         IPC_InitStatus
 * @param[in]     None
 * @param[in,out] None
 * @return        bool IPC initialization status
 */
bool IPC_InitStatus(void);

/**
 * @brief         IPC send data request
 * @param[in]     uint8_t *Data
 * @param[in]     uint32_t Len
 * @param[in,out] None
 * @return        void
 */
void IPC_Send(uint8_t *Data, uint16_t Len);

#endif /* __IPC_H__ */

