IPC COMUNICATION STACK

IPC is based on SPI bus and DMA transfer mechanism,
with just only 5 signals we can create a robust and high band width
communication link between the ICs. It's useful for systems which
consist embedded Linux and real time processing (RTOS) or for IoT
devices need to expand IO control lines.

To enable master device, we've defined the following macro in ipc.h

"#define SPI_MASTER"

To enable slaver device, just comment out the macro and re-compile the
source code again.

Hardware connection description:

SPI bus :

       Master               Slaver

      SCK  (PA5)  ------>  SCK  (PA5)
      MISO (PA6)  <------  MISO (PA6)
      MOSI (PA7)  ------>  MOSI (PA7)

GPIO Signaling :

    Ext IRQ                Slaver request out
    Master (Input)         Slaver (Output)
         PA0     <------        PA1

    Master request out     Ext IRQ
    Master (Output)        Slaver (Input)
         PA1     ------>        PA0

====================================================================================================================================================================================================================

```

How does it work ?

1> Slaver transfer request:

 Task(application)        TaskIPC(slaver)               IPC(slaver)                   SPI(slaver)   SPI(master)                 IPC(master)                  Ext IRQ       TaskIPC(master)         Task(application)
       |                        |                            |                            |             |                           |                           |                 |                        |
       |                        |                            |                            |             |                           |                           |                 |                        |
       |---------IPC_Send()--------------------------------->|                            |             |                           |                           |                 |                        |
       |                        |                            |                            |             |                           |                           |                 |                        |
       |                        |                            |---FifoPushMulti()---|      |             |                           |                           |                 |                        |
       |                        |                            |                     |      |             |                           |                           |                 |                        |
       |                        |                            |<--------------------|      |             |                           |                           |                 |                        |
       |                        |                            |                            |             |                           |                           |                 |                        |
       |                        |<--evIPCSlaverSendComplete--|                            |             |                           |                           |                 |                        |
       |                        |                            |                            |             |                           |                           |                 |                        |
       |                     (*)|---IPC_SPITransferQueue()-->|                            |             |                           |                           |                 |                        |
       |                        |                            |                            |             |                           |                           |                 |                        |
       |                        |                            |                            |             |                           |                           |                 |                        |
       |                        |                            |---FifoPopMulti()----|      |             |                           |                           |                 |                        |
       |                        |                            |                     |      |             |                           |                           |                 |                        |
       |                        |                            |<--------------------|      |             |                           |                           |                 |                        |
       |                        |                            |                            |             |                           |                           |                 |                        |
       |                        |                            |----SPI_AsyncTransfer()---->|             |                           |                           |                 |                        |
       |                        |                            |                            |             |                           |                           |                 |                        |
       |                        |                            |--------------------------------IPC_GpioTransferRequestSignal()---------------------------------->|                 |                        |
       |                        |                            |                            |             |                           |                           |                 |                        |
       |                        |                            |                            |             |                           |   |--EXTI0_Handler()------|                 |                        |
       |                        |                            |                            |             |                           |   |                       |                 |                        |
       |                        |                            |                            |             |                           |   |---------------------->|                 |                        |
       |                        |                            |                            |             |                           |                           |                 |                        |
       |                        |                            |                            |             |                           |<--IPC_SPITransferQueue()--|(**)             |                        |
       |                        |                            |                            |             |                           |                           |                 |                        |
       |                        |                            |                            |             |                           |---FifoPopMulti()--|       |                 |                        |
       |                        |                            |                            |             |                           |                   |       |                 |                        |
       |                        |                            |                            |             |                           |<------------------|       |                 |                        |
       |                        |                            |                            |             |                           |                           |                 |                        |
       |                        |                            |                            |             |<----SPI_AsyncTransfer()---|                           |                 |                        |
       |                        |                            |                            |     DMA     |                           |                           |                 |                        |
       |                        |                            |                            |<----------->|                           |                           |                 |                        |
       |                        |                            |                            |  Transfer   |                           |                           |                 |                        |
       |                        |                            |                            |             |                           |                           |                 |                        |
       |                        |                            |<---DMA2_Stream2_Handler()--|             |--DMA2_Stream2_Handler()-->|                           |                 |                        |
       |                        |                            |                            |             |                           |                           |                 |                        |
       |                        |<-----evIPCDataReceived-----|                            |             |                           |-----evIPCDataReceived---------------------->|                        |
       |                        |                            |                            |             |                           |                           |                 |                        |
       |<--IPC_DataRxHandler()--|                            |                            |             |                           |                           |                 |--IPC_DataRxHandler()-->|
       |                        |                            |                            |             |                           |                           |                 |                        |
       |                        |<--evIPCSlaverSendComplete--|(*)                         |             |                           |                           |                 |                        |
       |                        |                            |                            |             |                           |                           |                 |                        |
       |                        |                            |                            |             |                           |                           |                 |                        |

Note:

   (*) : TaskIPC(slaver) continues to request SPI transfer until its Tx FIFO is empty.
   (**): No matter what master's Tx FIFO is empty or not, do master SPI transfer request to receive SPI slaver Tx data.

2> Master transfer request:

 Task(application)        TaskIPC(slaver)    Ext IRQ                  IPC(slaver)                   SPI(slaver)   SPI(master)                 IPC(master)              Master Ext IRQ    TaskIPC(master)         Task(application)
       |                        |               |                           |                            |             |                           |                           |                 |                        |
       |                        |               |                           |                            |             |                           |                           |                 |                        |
       |                        |               |                           |                            |             |                           |<-----------------------------------------------------IPC_Send()------|
       |                        |               |                           |                            |             |                           |                           |                 |                        |
       |                        |               |                           |                            |             |                           |---FifoPushMulti()---|     |                 |                        |
       |                        |               |                           |                            |             |                           |                     |     |                 |                        |
       |                        |               |                           |                            |             |                           |<--------------------|     |                 |                        |
       |                        |               |                           |                            |             |                           |                           |                 |                        |
       |                        |               |<-----------------------------IPC_GpioTransferRequestSignal()-------------------------------------|                           |                 |                        |
       |                        |               |                           |                            |             |                           |                           |                 |                        |
       |                        |               |---EXTI0_Handler()---|     |                            |             |                           |                           |                 |                        |
       |                        |               |                     |     |                            |             |                           |                           |                 |                        |
       |                        |               |<--------------------|     |                            |             |                           |                           |                 |                        |
       |                        |               |                           |                            |             |                           |                           |                 |                        |
       |                        |               |--IPC_SPITransferQueue()-->|                            |             |                           |                           |                 |                        |
       |                        |               |                           |                            |             |                           |                           |                 |                        |
       |                        |               |                           |---FifoPopMulti()----|      |             |                           |                           |                 |                        |
       |                        |               |                           |                     |      |             |                           |                           |                 |                        |
       |                        |               |                           |<--------------------|      |             |                           |                           |                 |                        |
       |                        |               |                           |                            |             |                           |                           |                 |                        |
       |                        |               |                           |---SPI_AsyncTransfer()----->|             |                           |                           |                 |                        |
       |                        |               |                           |                            |             |                           |                           |                 |                        |
       |                        |               |                           |---IPC_GpioTransferRequestSignal()--------------------------------------------------------------->|                 |                        |
       |                        |               |                           |                            |             |                           |                           |                 |                        |
       |                        |               |                           |                            |             |                           |   |--EXTI0_Handler()------|                 |                        |
       |                        |               |                           |                            |             |                           |   |                       |                 |                        |
       |                        |               |                           |                            |             |                           |   |---------------------->|                 |                        |
       |                        |               |                           |                            |             |                           |                           |                 |                        |
       |                        |               |                           |                            |             |                           |<--IPC_SPITransferQueue()--|                 |                        |
       |                        |               |                           |                            |             |                           |                           |                 |                        |
       |                        |               |                           |                            |             |                           |---FifoPopMulti()--|       |                 |                        |
       |                        |               |                           |                            |             |                           |                   |       |                 |                        |
       |                        |               |                           |                            |             |                           |<------------------|       |                 |                        |
       |                        |               |                           |                            |             |                           |                           |                 |                        |
       |                        |               |                           |                            |             |<----SPI_AsyncTransfer()---|                           |                 |                        |
       |                        |               |                           |                            |     DMA     |                           |                           |                 |                        |
       |                        |               |                           |                            |<----------->|                           |                           |                 |                        |
       |                        |               |                           |                            |  Transfer   |                           |                           |                 |                        |
       |                        |               |                           |                            |             |                           |                           |                 |                        |
       |                        |               |                           |<---DMA2_Stream2_Handler()--|             |--DMA2_Stream2_Handler()-->|                           |                 |                        |
       |                        |               |                           |                            |             |                           |                           |                 |                        |
       |                        |<--------evIPCDataReceived-----------------|                            |             |                           |-----evIPCDataReceived---------------------->|                        |
       |                        |               |                           |                            |             |                           |                           |                 |                        |
       |<--IPC_DataRxHandler()--|               |                           |                            |             |                           |                           |                 |--IPC_DataRxHandler()-->|
       |                        |               |                           |                            |             |                           |                           |                 |                        |
       |                        |<-------evIPCSlaverSendComplete------------|                            |             |                           |                           |                 |                        |
       |                        |               |                           |                            |             |                           |                           |                 |                        |
       |                        |               |                           |                            |             |                           |                           |                 |                        |

```
