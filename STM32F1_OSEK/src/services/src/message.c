/*
 *  Copyright   : 2016
 *  File name   : message.c
 *	Author      : Dang Minh Phuong (PhuongDM1)
 *	Description : Message implementation
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "os.h"
#include "message.h"
#include "list_head.h"

static MessageType MessageList;

void Message_Init(void)
{
	INIT_LIST_HEAD(&MessageList.list);
}

/*
 * Static message allocation
 */
MessageType *Message_AllocateStatic(MessageType *Message, uint8_t *data, uint32_t len)
{
	if((NULL == Message) || (NULL == data))
	{
		return NULL;
	}

	/* allocate data buffer */
	Message->data = data;
	Message->len  = len;

	return Message;
}

/*
 * Dynamic message allocation
 */
MessageType *Message_Allocate(uint32_t len)
{
	MessageType *Message;

	/* Allocate message data structure */
	Message = (MessageType *)malloc(sizeof(MessageType));

	if(Message == NULL)
	{
		return NULL;
	}

	/* allocate data buffer */
	Message->data = (uint8_t *)malloc(len);
	Message->len  = len;

	if(Message->data == NULL)
	{
		/* Free Message object */
		free(Message);
		return NULL;
	}

	return Message;
}

/*
 * Only use with dynamic message allocation
 */
void Message_Free(MessageType *Message)
{
	if(Message != NULL)
	{
		if(Message->data != NULL)
		{
			free(Message->data);
		}
		free(Message);
		Message = NULL;
	}
}

MessageType *Message_Get(uint32_t id)
{
	struct list_head *pos;
	MessageType *Mesage;

	/* check for each item */
	list_for_each(pos, &MessageList.list)
	{
		/* get entry from list */
		Mesage = list_entry(pos, MessageType, list);

		/* check mail receive*/
		if (Mesage->id == id)
		{
			list_del(&Mesage->list);
			return Mesage;
		}
	}

	return NULL;
}

void Message_Queue(MessageType *Message)
{
    /* Enter critical section */
    asm ("cpsid i");

    /* Add message into list head */
    list_add(&(Message->list), &(MessageList.list));

    /* Exit critical section */
    asm ("cpsie i");
}

StatusType Message_Send(TaskType TaskID, EventMaskType Event)
{
    return SetEvent(TaskID, Event);
}
