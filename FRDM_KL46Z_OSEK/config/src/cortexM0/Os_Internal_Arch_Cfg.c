/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

/* Copyright 2014, 2015 Mariano Cerdeiro
 * Copyright 2014, 2015 Pablo Ridolfi
 * Copyright 2015, Alejandro Permingeat
 * All rights reserved.
 *
 * This file is part of CIAA Firmware.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/** \brief FreeOSEK Os Generated Internal Achitecture Configuration Implementation File
 **
 ** \file cortexM0/Os_Internal_Arch_Cfg.c
 ** \arch cortexM0
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.5 20150831 PR   cortexM0 first version
 * v0.1.4 20150307 MaCe rework port for CIAA-FLS
 * v0.1.3 20150303 Apermingeat added K60_120 interrupt sources
 * v0.1.2 20141130 PR   Added ISR cat. 2 enabling and disabling functions.
 * v0.1.1 20141115 PR   added LPC43xx interrupt sources, spelling mistake fixed
 * v0.1.0 20141115 MaCe initial version
 */

/*==================[inclusions]=============================================*/
#include "Os_Internal.h"
#if (CPU == MKL46ZXXX)
/* THIS IS A DIRTY WORKAROUND :( ciaa/Firmware#309*/
#undef FALSE
#undef TRUE
#endif

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/
#if (CPU == MKL46ZXXX)
/* Reset_Handler is defined in startup_MKL46Z4.s */
extern void Reset_Handler(void);

/** \brief External declaration for the pointer to the stack top from the Linker Script */
extern void __StackTop(void);
#else
#error Not supported CPU
#endif

/** \brief Handlers used by OSEK */
extern void PendSV_Handler(void);

extern void SysTick_Handler(void);

/*==================[internal functions definition]==========================*/
/* Default exception handlers. */
__attribute__ ((section(".text")))
void NMI_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".text")))
void HardFault_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".text")))
void SVC_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".text")))
void DebugMon_Handler(void) {
    while (1) {
    }
}

/*==================[external functions definition]==========================*/
/** \brief MKL46ZXXX Interrupt vector */
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
   /* System ISRs */
   &__StackTop,                    /* The initial stack pointer  */
   Reset_Handler,                  /* The reset handler          */
   NMI_Handler,                    /* The NMI handler            */
   HardFault_Handler,              /* The hard fault handler     */
   0,                              /* The MPU fault handler      */
   0,                              /* The bus fault handler      */
   0,                              /* The usage fault handler    */
   0,                              /* Reserved                   */
   0,                              /* Reserved                   */
   0,                              /* Reserved                   */
   0,                              /* Reserved                   */
   SVC_Handler,                    /* SVCall handler             */
   0,                              /* Debug monitor handler      */
   0,                              /* Reserved                   */
   PendSV_Handler,                 /* The PendSV handler         */
   SysTick_Handler,                /* The SysTick handler        */
   /*** User Interrupts ***/
   OSEK_ISR_NoHandler, /* 0x10 0x00000040 - No Handler set for ISR DMA0 (IRQ 0) */
   OSEK_ISR_NoHandler, /* 0x11 0x00000044 - No Handler set for ISR DMA1 (IRQ 1) */
   OSEK_ISR_NoHandler, /* 0x12 0x00000048 - No Handler set for ISR DMA2 (IRQ 2) */
   OSEK_ISR_NoHandler, /* 0x13 0x0000004C - No Handler set for ISR DMA3 (IRQ 3) */
   OSEK_ISR_NoHandler, /* 0x14 0x00000050 - No Handler set for ISR Reserved20 (IRQ 4) */
   OSEK_ISR_NoHandler, /* 0x15 0x00000054 - No Handler set for ISR FTFA (IRQ 5) */
   OSEK_ISR_NoHandler, /* 0x16 0x00000058 - No Handler set for ISR LVD_LVW (IRQ 6) */
   OSEK_ISR_NoHandler, /* 0x17 0x0000005C - No Handler set for ISR LLW (IRQ 7) */
   OSEK_ISR_NoHandler, /* 0x18 0x00000060 - No Handler set for ISR I2C0 (IRQ 8) */
   OSEK_ISR_NoHandler, /* 0x19 0x00000064 - No Handler set for ISR I2C1 (IRQ 9) */
   OSEK_ISR_NoHandler, /* 0x1a 0x00000068 - No Handler set for ISR SPI0 (IRQ 10) */
   OSEK_ISR_NoHandler, /* 0x1b 0x0000006C - No Handler set for ISR SPI1 (IRQ 11) */
   OSEK_ISR_NoHandler, /* 0x1c 0x00000070 - No Handler set for ISR UART0 (IRQ 12) */
   OSEK_ISR_NoHandler, /* 0x1d 0x00000074 - No Handler set for ISR UART1 (IRQ 13) */
   OSEK_ISR_NoHandler, /* 0x1e 0x00000078 - No Handler set for ISR UART2 (IRQ 14) */
   OSEK_ISR_NoHandler, /* 0x1f 0x0000007C - No Handler set for ISR ADC0 (IRQ 15) */
   OSEK_ISR_NoHandler, /* 0x20 0x00000080 - No Handler set for ISR CMP0 (IRQ 16) */
   OSEK_ISR_NoHandler, /* 0x21 0x00000084 - No Handler set for ISR TPM0 (IRQ 17) */
   OSEK_ISR_NoHandler, /* 0x22 0x00000088 - No Handler set for ISR TPM1 (IRQ 18) */
   OSEK_ISR_NoHandler, /* 0x23 0x0000008C - No Handler set for ISR TPM2 (IRQ 19) */
   OSEK_ISR_NoHandler, /* 0x24 0x00000090 - No Handler set for ISR RTC (IRQ 20) */
   OSEK_ISR_NoHandler, /* 0x25 0x00000094 - No Handler set for ISR RTC_Seconds (IRQ 21) */
   OSEK_ISR_NoHandler, /* 0x26 0x00000098 - No Handler set for ISR PIT (IRQ 22) */
   OSEK_ISR_NoHandler, /* 0x27 0x0000009C - No Handler set for ISR I2S0 (IRQ 23) */
   OSEK_ISR_NoHandler, /* 0x28 0x000000A0 - No Handler set for ISR USB0 (IRQ 24) */
   OSEK_ISR_NoHandler, /* 0x29 0x000000A4 - No Handler set for ISR DAC0 (IRQ 25) */
   OSEK_ISR_NoHandler, /* 0x2a 0x000000A8 - No Handler set for ISR TSI0 (IRQ 26) */
   OSEK_ISR_NoHandler, /* 0x2b 0x000000AC - No Handler set for ISR MCG (IRQ 27) */
   OSEK_ISR_NoHandler, /* 0x2c 0x000000B0 - No Handler set for ISR LPTimer (IRQ 28) */
   OSEK_ISR_NoHandler, /* 0x2d 0x000000B4 - No Handler set for ISR LCD (IRQ 29) */
   OSEK_ISR_NoHandler, /* 0x2e 0x000000B8 - No Handler set for ISR PORTA (IRQ 30) */
   OSEK_ISR_NoHandler, /* 0x2f 0x000000BC - No Handler set for ISR PORTC_PORTD (IRQ 31) */
};

/** \brief Interrupt enabling and priority setting function */
void Enable_User_ISRs(void)
{
}

/** \brief Enable user defined category 2 ISRs */
void Enable_ISR2_Arch(void)
{
}

/** \brief Disable user defined category 2 ISRs */
void Disable_ISR2_Arch(void)
{
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/
