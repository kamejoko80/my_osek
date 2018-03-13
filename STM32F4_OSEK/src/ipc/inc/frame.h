/*
 *  Copyright (C) : 2018
 *  File name     : frame.h
 *  Author        : Dang Minh Phuong
 *  Email         : kamejoko80@yahoo.com
 *
 *  This program is free software, you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */

#ifndef __FRAME_H__
#define __FRAME_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

/*
 * IPC Frame structure:
 *  _____ _____ ______ ______ ____________ ______________
 * |     |     |      |      |            |              |
 * | SOH | LEN | CRC8 | CRC8 |    DATA    | ZERO PADDING |
 * |_____|_____|______|______|____________|______________|
 *
 * |<----------------- IPC_TRANSFER_LEN ---------------->|
 *
 *  SOH  : uint8_t  : Start of header
 *  LEN  : uint16_t : Data length (not include data CRC8)
 *  CRC8 : uint8_t  : Header CRC checksum
 *  CRC8 : uint8_t  : Frame data checksum
 *  DATA : uint8_t  : IPC frame data
 *
 */

/*!
 * IPC parameter configuration
 */
#define IPC_TRANSFER_LEN (256)
#define IPC_DATA_MAX_LEN (IPC_TRANSFER_LEN - 5)
#define IPC_FRAME_SOH    (0xA5)

/*!
 * IPC FIFO buffer size
 */
#define FIFO_BUF_SIZE    (IPC_TRANSFER_LEN * 10)

/*!
 * IPC frame header structure
 */
typedef struct IPC_Frame_Header_s
{
    uint8_t  Soh;    /* Start of header     */
    uint16_t Len;    /* Payload length      */
    uint8_t  Crc8;   /* Header CRC checksum */
} __attribute__((packed, aligned(1))) IPC_Frame_Header_t;

/*!
 * IPC frame structure
 */
typedef struct IPC_Frame_s
{
    IPC_Frame_Header_t Header;      /* Frame header      */
    uint8_t Crc8;                   /* Data CRC checksum */
    uint8_t Data[IPC_DATA_MAX_LEN]; /* Frame data        */
} __attribute__((packed, aligned(1))) IPC_Frame_t;

#endif /* __FRAME_H__ */

