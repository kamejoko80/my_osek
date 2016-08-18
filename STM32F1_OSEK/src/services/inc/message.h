/*
 *  Copyright   : 2016
 *  File name   : message.h
 *	Author      : Dang Minh Phuong (PhuongDM1)
 *	Description : Message implementation
 */

#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <stdint.h>
#include "list_head.h"

typedef struct
{
    uint8_t   *data;         /* data buffer */
	uint32_t  len;           /* data len    */
	uint32_t  id;            /* message id  */
	struct list_head list;   /* linked list */
} MessageType;

void Message_Init(void);
void Message_Free(MessageType *Message);
MessageType *Message_AllocateStatic(MessageType *Message, uint8_t *data, uint32_t len);
MessageType *Message_Allocate(uint32_t len);
MessageType *Message_Get(uint32_t id);
void Message_Queue(MessageType *Message);
StatusType Message_Send(TaskType TaskID, EventMaskType Event);

#endif /* __MESSAGE_H__ */
