/********************************************************
 * DO NOT CHANGE THIS FILE, IT IS GENERATED AUTOMATICALY*
 ********************************************************/

/* Copyright 2014, Mariano Cerdeiro
 * Copyright 2014, Pablo Ridolfi
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
 ** \file cortexM4/Os_Internal_Arch_Cfg.c
 ** \arch cortexM4
 **/

/** \addtogroup FreeOSEK
 ** @{ */
/** \addtogroup FreeOSEK_Os
 ** @{ */
/** \addtogroup FreeOSEK_Os_Internal
 ** @{ */

/*
 * Initials     Name
 * ---------------------------
 * MaCe         Mariano Cerdeiro
 * PR           Pablo Ridolfi
 */

/*
 * modification history (new versions first)
 * -----------------------------------------------------------
 * v0.1.2 20160426 PR   Phuong Dang : change interrupt sources to STM32F4
 * v0.1.2 20141130 PR   Added ISR cat. 2 enabling and disabling functions.
 * v0.1.1 20141115 PR   added LPC43xx interrupt sources, spelling mistake fixed
 * v0.1.0 20141115 MaCe initial version
 */

/*==================[inclusions]=============================================*/
#include "Os_Internal.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/* ResetISR is defined in cr_startup_lpc43xx.c */
extern void ResetISR(void);

/** \brief External declaration for the pointer to the stack top from the Linker Script */
extern void _vStackTop(void);

/** \brief Handlers used by OSEK */
extern void SysTick_Handler(void);
extern void PendSV_Handler(void);

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
void MemManage_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".text")))
void BusFault_Handler(void) {
    while (1) {
    }
}
__attribute__ ((section(".text")))
void UsageFault_Handler(void) {
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

/** \brief STM32F4 Interrupt vector */
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
   /* Core Level - CM4 */
   &_vStackTop,                    /* The initial stack pointer  */
   ResetISR,                       /* The reset handler          */
   NMI_Handler,                    /* The NMI handler            */
   HardFault_Handler,              /* The hard fault handler     */
   MemManage_Handler,              /* The MPU fault handler      */
   BusFault_Handler,               /* The bus fault handler      */
   UsageFault_Handler,             /* The usage fault handler    */
   0,                              /* Reserved                   */
   0,                              /* Reserved                   */
   0,                              /* Reserved                   */
   0,                              /* Reserved                   */
   SVC_Handler,                    /* SVCall handler             */
   DebugMon_Handler,               /* Debug monitor handler      */
   0,                              /* Reserved                   */
   PendSV_Handler,                 /* The PendSV handler         */
   SysTick_Handler,                /* The SysTick handler        */

   /* Chip Level - STM32F4 (M4 core) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR WWDG (IRQ 0) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR PVD (IRQ 1) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR TAMP_STAMP (IRQ 2) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR RTC_WKUP (IRQ 3) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR FLASH (IRQ 4) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR RCC (IRQ 5) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR EXTI0 (IRQ 6) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR EXTI1 (IRQ 7) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR EXTI2 (IRQ 8) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR EXTI3 (IRQ 9) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR EXTI4 (IRQ 10) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR DMA1_Stream0 (IRQ 11) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR DMA1_Stream1 (IRQ 12) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR DMA1_Stream2 (IRQ 13) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR DMA1_Stream3 (IRQ 14) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR DMA1_Stream4 (IRQ 15) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR DMA1_Stream5 (IRQ 16) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR DMA1_Stream6 (IRQ 17) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR ADC (IRQ 18) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR CAN1_TX (IRQ 19) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR CAN1_RX0 (IRQ 20) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR CAN1_RX1 (IRQ 21) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR CAN1_SCE (IRQ 22) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR EXTI9_5 (IRQ 23) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR TIM1_BRK_TIM9 (IRQ 24) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR TIM1_UP_TIM10 (IRQ 25) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR TIM1_TRG_COM_TIM11 (IRQ 26) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR TIM1_CC (IRQ 27) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR TIM2 (IRQ 28) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR TIM3 (IRQ 29) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR TIM4 (IRQ 30) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR I2C1 (IRQ 31) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR I2C1 (IRQ 32) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR I2C2 (IRQ 33) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR I2C2 (IRQ 34) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR SPI1 (IRQ 35) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR SPI2 (IRQ 36) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR USART1 (IRQ 37) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR USART2 (IRQ 38) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR USART3 (IRQ 39) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR EXTI15 (IRQ 40) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR RTC_Alarm (IRQ 41) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR OTG_FS_WKUP (IRQ 42) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR TIM8_BRK_TIM12 (IRQ 43) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR TIM8_UP_TIM13 (IRQ 44) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR TIM8_TRG_COM_TIM14 (IRQ 45) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR TIM8_CC (IRQ 46) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR DMA1_Stream7 (IRQ 47) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR FSMC (IRQ 48) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR SDIO (IRQ 49) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR TIM5 (IRQ 50) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR SPI3 (IRQ 51) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR UART4 (IRQ 52) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR UART5 (IRQ 53) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR TIM6_DAC (IRQ 54) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR TIM7 (IRQ 55) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR DMA2_Stream0 (IRQ 56) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR DMA2_Stream1 (IRQ 57) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR DMA2_Stream2 (IRQ 58) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR DMA2_Stream3 (IRQ 59) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR DMA2_Stream4 (IRQ 60) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR ETH (IRQ 61) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR ETH_WKUP (IRQ 62) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR CAN2_TX (IRQ 63) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR CAN2_RX0 (IRQ 64) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR CAN2_RX1 (IRQ 65) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR CAN2_SCE (IRQ 66) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR OTG_FS (IRQ 67) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR DMA2_Stream5 (IRQ 68) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR DMA2_Stream6 (IRQ 69) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR DMA2_Stream7 (IRQ 70) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR USART6 (IRQ 71) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR I2C3_EV (IRQ 72) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR I2C3_ER (IRQ 73) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR OTG_HS_EP1_OUT (IRQ 74) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR OTG_HS_EP1_IN (IRQ 75) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR OTG_HS_WKUP (IRQ 76) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR OTG_HS (IRQ 77) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR DCMI (IRQ 78) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR CRYP (IRQ 79) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR HASH_RNG (IRQ 80) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR FPU (IRQ 81) */
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

