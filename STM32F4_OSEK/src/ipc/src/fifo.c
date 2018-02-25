#include <stdio.h>
#include "fifo.h"

static uint16_t FifoNext(Fifo_t *fifo, uint16_t index)
{
    return ( index + 1 ) % fifo->Size;
}

void FifoInit(Fifo_t *fifo, uint8_t *buffer, uint16_t size)
{
    fifo->Begin = 0;
    fifo->End = 0;
    fifo->Data = buffer;
    fifo->Size = size;
    fifo->FreeSize = size;
}

void FifoPush(Fifo_t *fifo, uint8_t data)
{
    fifo->End = FifoNext(fifo, fifo->End);
    fifo->Data[fifo->End] = data;
    fifo->FreeSize--;
}

uint8_t FifoPop(Fifo_t *fifo)
{
    uint8_t data = fifo->Data[FifoNext( fifo, fifo->Begin )];

    fifo->Begin = FifoNext(fifo, fifo->Begin);
    fifo->FreeSize++;
    return data;
}

void FifoPushMulti(Fifo_t *fifo, uint8_t *buffer, uint16_t size)
{
    uint16_t i;

    if (size <= fifo->FreeSize)
    {
        for(i = 0; i < size; i++)
        {
            FifoPush(fifo, buffer[i]);
        }
    }
    else
    {
        printf("FIFO: Not enough free space\r\n");
    }
}

uint16_t FifoPopMulti(Fifo_t *fifo, uint8_t *buffer, uint16_t size)
{
    uint16_t i, FifoDataCount, PopSize = 0;

    FifoDataCount = FifoGetDataSize(fifo);

    if (size <= FifoDataCount)
    {
        for(i = 0; i < size; i++)
        {
            buffer[i] = FifoPop(fifo);
        }

        PopSize = size;
    }
    else
    {
        for(i = 0; i < FifoDataCount; i++)
        {
            buffer[i] = FifoPop(fifo);
        }

        PopSize = FifoDataCount;
    }

    return PopSize;
}

uint8_t FifoRead(Fifo_t *fifo)
{
    uint8_t data = fifo->Data[FifoNext( fifo, fifo->Begin )];
    return data;
}

void FifoFlush(Fifo_t *fifo)
{
    fifo->Begin = 0;
    fifo->End = 0;
}

uint16_t FifoGetFreeSize(Fifo_t *fifo)
{
    return fifo->FreeSize;
}

uint16_t FifoGetDataSize(Fifo_t *fifo)
{
    return (fifo->Size - fifo->FreeSize);
}

bool IsFifoEmpty(Fifo_t *fifo)
{
    return (fifo->Begin == fifo->End);
}

bool IsFifoFull(Fifo_t *fifo)
{
    return (FifoNext(fifo, fifo->End) == fifo->Begin);
}
