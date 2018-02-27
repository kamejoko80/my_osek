IPC COMUNICATION STACK

IPC is based on SPI bus and DMA transfer mechanism,
with just only 4 signals we can create a robust and high band width
communication link between the ICs. It's useful for systems which
consist embedded Linux and real time processing (RTOS) or for IoT
devices need to expand IO control lines.

To enable master device, we've defined the following macro in ipc.h

"#define SPI_MASTER"

To enable slaver device, just comment out the macro and re-compile the
source code again.

/*
 * Hardware connection description
 *
 * SPI bus :
 *
 *        Master               Slaver
 *
 *       SCK  (PA5)  ------>  SCK  (PA5)
 *       MISO (PA6)  <------  MISO (PA6)
 *       MOSI (PA7)  ------>  MOSI (PA7)
 *
 * GPIO Signaling :
 *
 *     Slaver ready in        Slaver ready out
 *     Master (Input)         Slaver (Output)
 *          PA0     <------        PA1
 */
