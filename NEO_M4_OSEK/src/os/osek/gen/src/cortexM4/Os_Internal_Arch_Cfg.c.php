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
 * v0.1.2 20160713 PR   Phuong Dang : change interrupt sources to i.MX6SX
 * v0.1.2 20160426 PR   Phuong Dang : change interrupt sources to STM32F4
 * v0.1.2 20141130 PR   Added ISR cat. 2 enabling and disabling functions.
 * v0.1.1 20141115 PR   added LPC43xx interrupt sources, spelling mistake fixed
 * v0.1.0 20141115 MaCe initial version
 */

/*==================[inclusions]=============================================*/
#include "Os_Internal.h"
#include "device_imx.h"

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

<?php
/* 
 * Interrupt sources for STM32F4
 */
$intList = array (
    0 => "CORTEX_M4",               
    1 => "DAP",               
    2 => "SDMA",               
    3 => "Reserved19",               
    4 => "SNVS_PMIC",               
    5 => "LCDIF1",               
    6 => "LCDIF2",               
    7 => "CSI1",               
    8 => "PXP",               
    9 => "Reserved25",               
    10 => "GPU",               
    11 => "WDOG3",               
    12 => "SEMA4_CP1",               
    13 => "APBH_DMA",               
    14 => "EIM",               
    15 => "BCH",               
    16 => "GPMI",               
    17 => "UART6",               
    18 => "eCSPI5",               
    19 => "SNVS_CONSOLIDATED",              
    20 => "SNVS_SECURITY",               
    21 => "CSU",               
    22 => "uSDHC1",               
    23 => "uSDHC2",               
    24 => "uSDHC3",               
    25 => "uSDHC4",               
    26 => "UART1",               
    27 => "UART2",               
    28 => "UART3",               
    29 => "UART4",               
    30 => "UART5",               
    31 => "eCSPI1",               
    32 => "eCSPI2",               
    33 => "eCSPI3",               
    34 => "eCSPI4",               
    35 => "I2C4",               
    36 => "I2C1",               
    37 => "I2C2",               
    38 => "I2C3",               
    39 => "RDC",               
    40 => "USB_HISC",               
    41 => "CSI2",               
    42 => "USB_OTG2",               
    43 => "USB_OTG1",               
    44 => "USB_PHY_UTMI0",               
    45 => "USB_PHY_UTMI1",               
    46 => "SSI1",               
    47 => "SSI2",               
    48 => "SSI3",               
    49 => "TEMPMON",               
    50 => "ASRC",               
    51 => "ESAI",               
    52 => "SPDIF",               
    53 => "MLB_ERROR",               
    54 => "PMU1",               
    55 => "GPT",               
    56 => "EPIT1",               
    57 => "EPIT2",               
    58 => "GPIO1_INT7",               
    59 => "GPIO1_INT6",               
    60 => "GPIO1_INT5",               
    61 => "GPIO1_INT4",               
    62 => "GPIO1_INT3",               
    63 => "GPIO1_INT2",               
    64 => "GPIO1_INT1",               
    65 => "GPIO1_INT0",               
    66 => "GPIO1_INT15_0",           
    67 => "GPIO1_INT31_16",           
    68 => "GPIO2_INT15_0",           
    69 => "GPIO2_INT31_16",           
    70 => "GPIO3_INT15_0",           
    71 => "GPIO3_INT31_16",           
    72 => "GPIO4_INT15_0",           
    73 => "GPIO4_INT31_16",           
    74 => "GPIO5_INT15_0",           
    75 => "GPIO5_INT31_16",           
    76 => "GPIO6_INT15_0",           
    77 => "GPIO1_INT31_16",           
    78 => "GPIO7_INT15_0",           
    79 => "GPIO7_INT31_16",           
    80 => "WDOG1",               
    81 => "WDOG2",               
    82 => "KPP",               
    83 => "PWM1_PWM5",               
    84 => "PWM2_PWM6",               
    85 => "PWM3_PWM7",               
    86 => "PWM4_PWM8",               
    87 => "CCM1",               
    88 => "CCM2",               
    89 => "GPC",               
    90 => "MU_A9",               
    91 => "SRC",               
    92 => "CPU_L2",               
    93 => "CPU_PCEI",               
    94 => "CPU_PUI",               
    95 => "CPU_CTI",               
    96 => "SRC_WDOG",               
    97 => "SAI1",               
    98 => "SAI2",               
    99 => "MU_M4",               
    100 => "ADC1",               
    101 => "ADC2",               
    102 => "ENET2",               
    103 => "ENET2_TI",               
    104 => "SJC",               
    105 => "CAAM0",               
    106 => "CAAM1",               
    107 => "QSPI1",               
    108 => "TZASC",               
    109 => "QSPI2",               
    110 => "FLEXCAN1",               
    111 => "FLEXCAN2",               
    112 => "Reserved128",               
    113 => "Reserved129",               
    114 => "CANFD1",               
    115 => "CANFD2",               
    116 => "SEMA4_CP0",               
    117 => "MLB_IRCI",              
    118 => "ENET1",               
    119 => "ENET1_Timer",               
    120 => "PCIe1",               
    121 => "PCIe2",               
    122 => "PCIe3",               
    123 => "PCIe4",               
    124 => "DCIC1",               
    125 => "DCIC2",               
    126 => "MLB_LOCI",             
    127 => "PMU2"               
);

$MAX_INT_COUNT = max(array_keys($intList))+1;
?>
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

