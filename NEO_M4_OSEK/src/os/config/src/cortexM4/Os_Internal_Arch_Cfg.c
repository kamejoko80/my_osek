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

/* Reset_Handler is defined in startup code */
extern void Reset_Handler(void);

/** \brief External declaration for the pointer to the stack top from the Linker Script */
extern void __StackTop(void);

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
   &__StackTop,                    /* The initial stack pointer  */
   Reset_Handler,                  /* The reset handler          */
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
   OSEK_ISR_NoHandler, /* No Handler set for ISR MU_M4 (IRQ 0) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR SNVS_Consolidated (IRQ 1) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR UART4 (IRQ 2) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR RDC (IRQ 3) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR TEMPMON (IRQ 4) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR GPIO1_INT6 (IRQ 5) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR GPIO2_Combined_16_31 (IRQ 6) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR GPIO7_Combined_16_31 (IRQ 7) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR GPU (IRQ 8) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR WDOG3 (IRQ 9) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR SEMA4_CP1 (IRQ 10) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR APBH_DMA (IRQ 11) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR EIM (IRQ 12) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR BCH (IRQ 13) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR GPMI (IRQ 14) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR UART6 (IRQ 15) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR SNVS_Security (IRQ 16) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR CSU (IRQ 17) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR uSDHC1 (IRQ 18) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR uSDHC2 (IRQ 19) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR uSDHC3 (IRQ 20) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR uSDHC4 (IRQ 21) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR UART1 (IRQ 22) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR UART2 (IRQ 23) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR UART5 (IRQ 24) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR eCSPI1 (IRQ 25) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR eCSPI2 (IRQ 26) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR eCSPI3 (IRQ 27) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR eCSPI4 (IRQ 28) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR I2C4 (IRQ 29) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR I2C1 (IRQ 30) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR I2C2 (IRQ 31) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR USB_HISC (IRQ 32) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR CSI2 (IRQ 33) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR USB_OTG2 (IRQ 34) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR USB_OTG1 (IRQ 35) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR USB_PHY_UTMI0 (IRQ 36) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR USB_PHY_UTMI1 (IRQ 37) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR SSI1 (IRQ 38) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR SSI2 (IRQ 39) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR ASRC (IRQ 40) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR ESAI (IRQ 41) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR SPDIF (IRQ 42) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR MLB_Error (IRQ 43) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR PMU_BrownOut (IRQ 44) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR GPT (IRQ 45) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR EPIT1 (IRQ 46) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR EPIT2 (IRQ 47) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR GPIO1_INT5 (IRQ 48) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR GPIO1_INT4 (IRQ 49) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR GPIO1_INT3 (IRQ 50) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR GPIO1_INT2 (IRQ 51) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR GPIO1_INT1 (IRQ 52) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR GPIO1_INT0 (IRQ 53) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR GPIO1_Combined_0_15  (IRQ 54) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR GPIO1_Combined_16_31 (IRQ 55) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR GPIO3_Combined_0_15  (IRQ 56) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR GPIO3_Combined_16_31 (IRQ 57) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR GPIO4_Combined_0_15  (IRQ 58) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR GPIO4_Combined_16_31 (IRQ 59) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR GPIO5_Combined_0_15  (IRQ 60) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR GPIO5_Combined_16_31 (IRQ 61) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR GPIO6_Combined_0_15  (IRQ 62) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR GPIO6_Combined_16_31 (IRQ 63) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 64) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 65) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 66) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 67) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 68) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 69) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 70) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 71) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 72) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 73) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 74) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 75) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 76) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 77) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 78) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 79) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 80) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 81) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 82) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 83) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 84) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 85) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 86) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 87) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 88) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 89) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 90) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 91) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 92) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 93) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 94) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 95) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 96) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 97) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 98) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR  (IRQ 99) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR ADC1 (IRQ 100) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR ADC2 (IRQ 101) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR ENET2 (IRQ 102) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR ENET2_Timer (IRQ 103) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR SJC (IRQ 104) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR CAAM0 (IRQ 105) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR CAAM1 (IRQ 106) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR QSPI1 (IRQ 107) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR TZASC (IRQ 108) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR QSPI2 (IRQ 109) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR FLEXCAN1 (IRQ 110) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR FLEXCAN2 (IRQ 111) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR Reserved128 (IRQ 112) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR Reserved129 (IRQ 113) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR CANFD1 (IRQ 114) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR CANFD2 (IRQ 115) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR SEMA4_CP0 (IRQ 116) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR MLB_Channels_31_0 (IRQ 117) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR ENET1 (IRQ 118) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR ENET1_Timer (IRQ 119) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR PCIe1 (IRQ 120) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR PCIe2 (IRQ 121) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR PCIe3 (IRQ 122) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR PCIe4 (IRQ 123) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR DCIC1 (IRQ 124) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR DCIC2 (IRQ 125) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR MLB_Channels_63_32 (IRQ 126) */
   OSEK_ISR_NoHandler, /* No Handler set for ISR PMU_BrownOutCore (IRQ 127) */
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

