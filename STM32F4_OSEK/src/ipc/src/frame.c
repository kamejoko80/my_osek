/*
 *  Copyright (C) : 2018
 *  File name     : frame.c
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

/***************************************************************
 *  MACRO DEFINITION
 ***************************************************************/

/***************************************************************
 *  GLOBAL VARIABLE DEFINITION
 ***************************************************************/

/***************************************************************
 *  EXTERNAL FUNCTION PROTOYPE
 ***************************************************************/

/***************************************************************
 *  FUNCTION PROTOYPE
 ***************************************************************/

/***************************************************************
 *  FUNCTION DEFINITION
 ***************************************************************/

uint8_t IPC_Frame_Crc8(uint8_t *Data, uint16_t Len)
{
  unsigned Crc = 0;
  int i, j;

  /* Using x^8 + x^2 + x + 1 polynomial */
  for (j = Len; j; j--, Data++)
  {
    Crc ^= (*Data << 8);

    for(i = 8; i; i--)
    {
      if (Crc & 0x8000)
      {
        Crc ^= (0x1070 << 3);
      }
      Crc <<= 1;
    }
  }
  return (uint8_t)(Crc >> 8);
}

bool IPC_Frame_Create(IPC_Frame_t *Frame, uint8_t *Data, uint16_t Len)
{
    bool ret = false;

    if(Len <= IPC_DATA_MAX_LEN)
    {
        /* Reset IPC frame */
        memset((void *)Frame, 0, sizeof(IPC_Frame_t));

        /* Creates IPC frame header */
        Frame->Header.Soh  = IPC_FRAME_SOH;
        Frame->Header.Len  = Len;
        Frame->Header.Crc8 = IPC_Frame_Crc8((uint8_t *)&Frame->Header, 3);

        /* Create IPC frame data and CRC8 */
        memcpy(Frame->Data, Data, Len);
        Frame->Crc8 = IPC_Frame_Crc8(Frame->Data, Len);

        ret = true;
    }
    else
    {
        printf("Error data length exceeds allow max length\r\n");
    }

    return ret;
}

bool IPC_Frame_Check(IPC_Frame_t *Frame)
{
    bool ret = false;

    if(Frame->Header.Soh != IPC_FRAME_SOH)
    {
        // printf("Error IPC frame header SOH\r\n");
    }
    else if(IPC_Frame_Crc8((uint8_t *)&Frame->Header, 3) != Frame->Header.Crc8)
    {
        printf("Error IPC frame header\r\n");
    }
    else if(IPC_Frame_Crc8(Frame->Data, Frame->Header.Len) != Frame->Crc8)
    {
        printf("Error IPC frame data\r\n");
    }
    else
    {
        ret = true;
    }

    return ret;
}

void IPC_Frame_Print(IPC_Frame_t *Frame)
{
    int i;

    printf("===== IPC Frame Info =====\r\n");
    printf("Header:\r\n");
    printf("  Soh : 0x%X\r\n", Frame->Header.Soh);
    printf("  Len : %d\r\n", Frame->Header.Len);
    printf("  Data: ");

    for (i = 0; i < Frame->Header.Len; i++)
    {
        printf("%X ", Frame->Data[i]);
    }

    printf("\r\n");
}

