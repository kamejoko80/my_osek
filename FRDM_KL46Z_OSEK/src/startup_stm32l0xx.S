/*
 * Purpose: startup file for Cortex-M0+ devices. Should use with
 *   GCC for ARM Embedded Processors
 * Version: V1.3
 * Date: 08 Feb 2012
 *
 * Copyright (c) 2012, ARM Limited
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the ARM Limited nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ARM LIMITED BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES//
 * LOSS OF USE, DATA, OR PROFITS// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

 /*************************************************************************

 WARNING: This is a generic startup file for the STM32L0 series,
          not every device supports all the defined ISR handlers.

****************************************************************************/

    .syntax unified
    .arch armv6-m

    .section .stack
    .align 3
#ifdef __STACK_SIZE
    .equ    Stack_Size, __STACK_SIZE
#else
    .equ    Stack_Size, 0x400
#endif
    .globl    __StackTop
    .globl    __StackLimit
__StackLimit:
    .space    Stack_Size
    .size __StackLimit, . - __StackLimit
__StackTop:
    .size __StackTop, . - __StackTop

    .section .heap
    .align 3
#ifdef __HEAP_SIZE
    .equ    Heap_Size, __HEAP_SIZE
#else
    .equ    Heap_Size, 0xC00
#endif
    .globl    __HeapBase
    .globl    __HeapLimit
__HeapBase:
    .if    Heap_Size
    .space    Heap_Size
    .endif
    .size __HeapBase, . - __HeapBase
__HeapLimit:
    .size __HeapLimit, . - __HeapLimit

    .section .isr_vector
    .align 2
    .globl __isr_vector
__isr_vector:
    .long    __StackTop                // Top of Stack
    .long    Reset_Handler             // Reset Handler
    .long    NMI_Handler               // NMI Handler
    .long    HardFault_Handler         // Hard Fault Handler
    .long    0                         // Reserved
    .long    0                         // Reserved
    .long    0                         // Reserved
    .long    0                         // Reserved
    .long    0                         // Reserved
    .long    0                         // Reserved
    .long    0                         // Reserved
    .long    SVC_Handler               // SVCall Handler
    .long    DebugMon_Handler          // Debug Monitor Handler
    .long    0                         // Reserved
    .long    PendSV_Handler            // PendSV Handler
    .long    SysTick_Handler           // SysTick Handler

                // External Interrupts
    .long    WWDG_IRQHandler                // Window Watchdog
    .long    PVD_IRQHandler                 // PVD through EXTI Line detect
    .long    RTC_IRQHandler                 // RTC through EXTI Line
    .long    FLASH_IRQHandler               // FLASH
    .long    RCC_CRS_IRQHandler             // RCC and CRS
    .long    EXTI0_1_IRQHandler             // EXTI Line 0 and 1
    .long    EXTI2_3_IRQHandler             // EXTI Line 2 and 3
    .long    EXTI4_15_IRQHandler            // EXTI Line 4 to 15
    .long    TSC_IRQHandler                 // TSC
    .long    DMA1_Channel1_IRQHandler       // DMA1 Channel 1
    .long    DMA1_Channel2_3_IRQHandler     // DMA1 Channel 2 and Channel 3
    .long    DMA1_Channel4_5_6_7_IRQHandler // DMA1 Channel 4, Channel 5, Channel 6 and Channel 7
    .long    ADC1_COMP_IRQHandler           // ADC1, COMP1 and COMP2
    .long    LPTIM1_IRQHandler              // LPTIM1
    .long    0                              // Reserved
    .long    TIM2_IRQHandler                // TIM2
    .long    0                              // Reserved
    .long    TIM6_DAC_IRQHandler            // TIM6 and DAC
    .long    0                              // Reserved
    .long    0                              // Reserved
    .long    TIM21_IRQHandler               // TIM21
    .long    0                              // Reserved
    .long    TIM22_IRQHandler               // TIM22
    .long    I2C1_IRQHandler                // I2C1
    .long    I2C2_IRQHandler                // I2C2
    .long    SPI1_IRQHandler                // SPI1
    .long    SPI2_IRQHandler                // SPI2
    .long    USART1_IRQHandler              // USART1
    .long    USART2_IRQHandler              // USART2
    .long    AES_RNG_LPUART1_IRQHandler     // AES, RNG and LPUART1
    .long    LCD_IRQHandler                 // LCD
    .long    USB_IRQHandler                 // USB

    .size    __isr_vector, . - __isr_vector

    .text
    .thumb
    .thumb_func
    .align 2
    .globl    Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:
/*     Loop to copy data from read only memory to RAM. The ranges
 *      of copy from/to are specified by following symbols evaluated in
 *      linker script.
 *      __etext: End of code section, i.e., begin of data sections to copy from.
 *      __data_start__/__data_end__: RAM address range that data should be
 *      copied to. Both must be aligned to 4 bytes boundary.  */

    ldr    r1, =__etext
    ldr    r2, =__data_start__
    ldr    r3, =__data_end__


    subs    r3, r2
    ble    .flash_to_ram_loop_end
.flash_to_ram_loop:
    subs    r3, #4
    ldr    r0, [r1, r3]
    str    r0, [r2, r3]
    bgt    .flash_to_ram_loop
.flash_to_ram_loop_end:


#ifndef __NO_SYSTEM_INIT
    ldr    r0, =SystemInit
    blx    r0
#endif

    ldr    r0, =_start
    bx    r0
    .pool
    .size Reset_Handler, . - Reset_Handler

/* Our weak _start alternative if we don't use the library _start
 * The zero init section must be cleared, otherwise the librtary is
 * doing that */
    .align 1
    .thumb_func
    .weak _start
    .type _start, %function
_start:

    /* Zero fill the bss segment. */
    ldr   r1, = __bss_start__
    ldr   r2, = __bss_end__
    movs  r3, #0
    b  .fill_zero_bss
.loop_zero_bss:
    str  r3, [r1]
    adds  r1,#4

.fill_zero_bss:
    cmp  r1, r2
    bcc  .loop_zero_bss

    /* Jump to our main */
    bl main
    b .
    .size    _start, . - _start

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro    def_irq_handler    handler_name
    .align 1
    .thumb_func
    .weak    \handler_name
    .type    \handler_name, %function
\handler_name :
    b    .
    .size    \handler_name, . - \handler_name
    .endm

    def_irq_handler    NMI_Handler
    def_irq_handler    HardFault_Handler
    def_irq_handler    SVC_Handler
    def_irq_handler    DebugMon_Handler
    def_irq_handler    PendSV_Handler
    def_irq_handler    SysTick_Handler

                // External Interrupts
    def_irq_handler    WWDG_IRQHandler
    def_irq_handler    PVD_IRQHandler
    def_irq_handler    RTC_IRQHandler
    def_irq_handler    FLASH_IRQHandler
    def_irq_handler    RCC_CRS_IRQHandler
    def_irq_handler    EXTI0_1_IRQHandler
    def_irq_handler    EXTI2_3_IRQHandler
    def_irq_handler    EXTI4_15_IRQHandler
    def_irq_handler    TSC_IRQHandler
    def_irq_handler    DMA1_Channel1_IRQHandler
    def_irq_handler    DMA1_Channel2_3_IRQHandler
    def_irq_handler    DMA1_Channel4_5_6_7_IRQHandler
    def_irq_handler    ADC1_COMP_IRQHandler
    def_irq_handler    LPTIM1_IRQHandler
    def_irq_handler    TIM2_IRQHandler
    def_irq_handler    TIM6_DAC_IRQHandler
    def_irq_handler    TIM21_IRQHandler
    def_irq_handler    TIM22_IRQHandler
    def_irq_handler    I2C1_IRQHandler
    def_irq_handler    I2C2_IRQHandler
    def_irq_handler    SPI1_IRQHandler
    def_irq_handler    SPI2_IRQHandler
    def_irq_handler    USART1_IRQHandler
    def_irq_handler    USART2_IRQHandler
    def_irq_handler    AES_RNG_LPUART1_IRQHandler
    def_irq_handler    LCD_IRQHandler
    def_irq_handler    USB_IRQHandler

    .end
