IPC communication Bus

IPC is based on SPI bus and DMA transfer mechanism,
with just only 4 signals we can create a robust and high band width
communication link between the ICs. It's useful for systems which
consist embedded Linux and real time processing (RTOS) or for IoT
devices need to expand IO control lines.

The project is firstly implemented on STM32F4 discovery as Ping Pong
application demo. We need 2 boards STM32F4 discovery to connect together,
one acts as a SPI master device and the other one acts as a slaver device.

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
 *       Request In             Request Out
 * Master (Input, EXTI)       Slaver (Output)
 *          PA0     <------        PA1
 */