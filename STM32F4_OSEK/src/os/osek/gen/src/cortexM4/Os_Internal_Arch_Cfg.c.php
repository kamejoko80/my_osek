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
#include "stm32f4xx.h"

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

<?php
/* 
 * Interrupt sources for STM32F4
 */
$intList = array (
    0 => "WWDG",
    1 => "PVD",
    2 => "TAMP_STAMP",
    3 => "RTC_WKUP",
    4 => "FLASH",
    5 => "RCC",
    6 => "EXTI0",
    7 => "EXTI1",
    8 => "EXTI2",
    9 => "EXTI3",
    10 => "EXTI4",
    11 => "DMA1_Stream0",
    12 => "DMA1_Stream1",
    13 => "DMA1_Stream2",
    14 => "DMA1_Stream3",
    15 => "DMA1_Stream4",
    16 => "DMA1_Stream5",
    17 => "DMA1_Stream6",
    18 => "ADC",
    19 => "CAN1_TX",
    20 => "CAN1_RX0",
    21 => "CAN1_RX1",
    22 => "CAN1_SCE",
    23 => "EXTI9_5",
    24 => "TIM1_BRK_TIM9",
    25 => "TIM1_UP_TIM10",
    26 => "TIM1_TRG_COM_TIM11",
    27 => "TIM1_CC",
    28 => "TIM2",
    29 => "TIM3",
    30 => "TIM4",
    31 => "I2C1",
    32 => "I2C1",
    33 => "I2C2",
    34 => "I2C2",
    35 => "SPI1",
    36 => "SPI2",
    37 => "USART1",
    38 => "USART2",
    39 => "USART3",
    40 => "EXTI15",
    41 => "RTC_Alarm",
    42 => "OTG_FS_WKUP",
    43 => "TIM8_BRK_TIM12",
    44 => "TIM8_UP_TIM13",
    45 => "TIM8_TRG_COM_TIM14",
    46 => "TIM8_CC",
    47 => "DMA1_Stream7",
    48 => "FSMC",
    49 => "SDIO",
    50 => "TIM5",
    51 => "SPI3",
    52 => "UART4",
    53 => "UART5",
    54 => "TIM6_DAC",
    55 => "TIM7",
    56 => "DMA2_Stream0",
    57 => "DMA2_Stream1",
    58 => "DMA2_Stream2",
    59 => "DMA2_Stream3",
    60 => "DMA2_Stream4",
    61 => "ETH",
    62 => "ETH_WKUP",
    63 => "CAN2_TX",
    64 => "CAN2_RX0",
    65 => "CAN2_RX1",
    66 => "CAN2_SCE",
    67 => "OTG_FS",
    68 => "DMA2_Stream5",
    69 => "DMA2_Stream6",
    70 => "DMA2_Stream7",
    71 => "USART6",
    72 => "I2C3_EV",
    73 => "I2C3_ER",
    74 => "OTG_HS_EP1_OUT",
    75 => "OTG_HS_EP1_IN",
    76 => "OTG_HS_WKUP",
    77 => "OTG_HS",
    78 => "DCMI",
    79 => "CRYP",
    80 => "HASH_RNG",
    81 => "FPU"
);

$MAX_INT_COUNT = max(array_keys($intList))+1;
?>
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
<?php

/* get ISRs defined by user application */
$intnames = $config->getList("/OSEK","ISR");

for($i=0; $i < $MAX_INT_COUNT; $i++)
{
   $src_found = 0;
   foreach ($intnames as $int)
   {
      $intcat = $config->getValue("/OSEK/" . $int,"CATEGORY");
      $source = $config->getValue("/OSEK/" . $int,"INTERRUPT");

      if($intList[$i] == $source)
      {
         if ($intcat == 2)
         {
            print "   OSEK_ISR2_$int, /* ISR for " . $intList[$i] . " (IRQ $i) Category 2 */\n";
            $src_found = 1;
         } elseif ($intcat == 1)
         {
            print "   OSEK_ISR_$int, /* ISR for " . $intList[$i] . " (IRQ $i) Category 1 */\n";
            $src_found = 1;
         } else
         {
            error("Interrupt $int type $inttype has an invalid category $intcat");
         }
      }
   }
   if($src_found == 0)
   {
      print "   OSEK_ISR_NoHandler, /* No Handler set for ISR " . $intList[$i] . " (IRQ $i) */\n";
   }
}
?>
};

/** \brief Interrupt enabling and priority setting function */
void Enable_User_ISRs(void)
{
<?php
/* get ISRs defined by user application */
$intnames = $config->getList("/OSEK","ISR");
foreach ($intnames as $int)
{
   $source = $config->getValue("/OSEK/" . $int,"INTERRUPT");
   $prio = $config->getValue("/OSEK/" . $int,"PRIORITY");

   print "   /* Enabling IRQ $source with priority $prio */\n";
   print "   NVIC_EnableIRQ(" . array_search($source, $intList) . ");\n";
   print "   NVIC_SetPriority(" . array_search($source, $intList) . ", $prio);\n\n";
}
?>
}

/** \brief Enable user defined category 2 ISRs */
void Enable_ISR2_Arch(void)
{
<?php
/* get ISRs defined by user application */
$intnames = $config->getList("/OSEK","ISR");
foreach ($intnames as $int)
{
   $source = $config->getValue("/OSEK/" . $int,"INTERRUPT");
   $cat = $config->getValue("/OSEK/" . $int,"CATEGORY");

   if($cat == 2)
   {
      print "   /* Enabling IRQ $source */\n";
      print "   NVIC_EnableIRQ(" . array_search($source, $intList) . ");\n";
   }
}
?>
}

/** \brief Disable user defined category 2 ISRs */
void Disable_ISR2_Arch(void)
{
<?php
/* get ISRs defined by user application */
$intnames = $config->getList("/OSEK","ISR");
foreach ($intnames as $int)
{
   $source = $config->getValue("/OSEK/" . $int,"INTERRUPT");
   $cat = $config->getValue("/OSEK/" . $int,"CATEGORY");

   if($cat == 2)
   {
      print "   /* Disabling IRQ $source */\n";
      print "   NVIC_DisableIRQ(" . array_search($source, $intList) . ");\n";
   }
}
?>
}

/** @} doxygen end group definition */
/** @} doxygen end group definition */
/** @} doxygen end group definition */
/*==================[end of file]============================================*/

