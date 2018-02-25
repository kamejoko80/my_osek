
#ifndef __FIFO_H__
#define __FIFO_H__

#include <stdbool.h>
#include <stdint.h>

/*!
 * FIFO structure
 */
typedef struct Fifo_s
{
    uint16_t Begin;
    uint16_t End;
    uint8_t *Data;
    uint16_t Size;
    uint16_t FreeSize;
}Fifo_t;

/*!
 * Initializes the FIFO structure
 *
 * \param [IN] fifo   Pointer to the FIFO object
 * \param [IN] buffer Buffer to be used as FIFO
 * \param [IN] size   Size of the buffer
 */
void FifoInit(Fifo_t *fifo, uint8_t *buffer, uint16_t size);

/*!
 * Pushes data to the FIFO
 *
 * \param [IN] fifo Pointer to the FIFO object
 * \param [IN] data Data to be pushed into the FIFO
 */
void FifoPush(Fifo_t *fifo, uint8_t data);

/*!
 * Pops data from the FIFO
 *
 * \param [IN] fifo Pointer to the FIFO object
 * \retval data     Data popped from the FIFO
 */
uint8_t FifoPop(Fifo_t *fifo);

/*!
 * Pushes multi data to the FIFO
 *
 * \param [IN] fifo   Pointer to the FIFO object
 * \param [IN] buffer Data buffer to be pushed into the FIFO
 * \param [IN] size   Size of the buffer
 */
void FifoPushMulti(Fifo_t *fifo, uint8_t *buffer, uint16_t size);

/*!
 * Pops multi data from the FIFO and returns the actual data size
 *
 * \param [IN] fifo   Pointer to the FIFO object
 * \param [IN] buffer Data buffer to be pop from the FIFO
 * \param [IN] size   Size of the buffer
 */
uint16_t FifoPopMulti(Fifo_t *fifo, uint8_t *buffer, uint16_t size);

/*!
 * Read data from the FIFO (without change FIFO buffer)
 *
 * \param [IN] fifo Pointer to the FIFO object
 * \retval data     Data popped from the FIFO
 */
uint8_t FifoRead(Fifo_t *fifo);

/*!
 * Flushes the FIFO
 *
 * \param [IN] fifo   Pointer to the FIFO object
 */
void FifoFlush(Fifo_t *fifo);

/*!
 * Return free space of FIFO
 *
 * \param [IN] fifo   Pointer to the FIFO object
 */
uint16_t FifoGetFreeSize(Fifo_t *fifo);

/*!
 * Return data count of FIFO
 *
 * \param [IN] fifo   Pointer to the FIFO object
 */
uint16_t FifoGetDataSize(Fifo_t *fifo);

/*!
 * Checks if the FIFO is empty
 *
 * \param [IN] fifo   Pointer to the FIFO object
 * \retval isEmpty    true: FIFO is empty, false FIFO is not empty
 */
bool IsFifoEmpty(Fifo_t *fifo);

/*!
 * Checks if the FIFO is full
 *
 * \param [IN] fifo   Pointer to the FIFO object
 * \retval isFull     true: FIFO is full, false FIFO is not full
 */
bool IsFifoFull(Fifo_t *fifo);

#endif // __FIFO_H__
