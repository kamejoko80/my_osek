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

<?php
/* 
 * Interrupt sources for STM32F4
 */
$intList = array (
    000 => "CORTEX_M4",               
    001 => "DAP",               
    002 => "SDMA",               
    003 => "Reserved19",               
    004 => "SNVS_PMIC",               
    005 => "LCDIF1",               
    006 => "LCDIF2",               
    007 => "CSI1",               
    008 => "PXP",               
    009 => "Reserved25",               
    010 => "GPU",               
    011 => "WDOG3",               
    012 => "SEMA4_CP1",               
    013 => "APBH_DMA",               
    014 => "EIM",               
    015 => "BCH",               
    016 => "GPMI",               
    017 => "UART6",               
    018 => "eCSPI5",               
    019 => "SNVS_Consolidated",              
    020 => "SNVS_Security",               
    021 => "CSU",               
    022 => "uSDHC1",               
    023 => "uSDHC2",               
    024 => "uSDHC3",               
    025 => "uSDHC4",               
    026 => "UART1",               
    027 => "UART2",               
    028 => "UART3",               
    029 => "UART4",               
    030 => "UART5",               
    031 => "eCSPI1",               
    032 => "eCSPI2",               
    033 => "eCSPI3",               
    034 => "eCSPI4",               
    035 => "I2C4",               
    036 => "I2C1",               
    037 => "I2C2",               
    038 => "I2C3",               
    039 => "RDC",               
    040 => "USB_HISC",               
    041 => "CSI2",               
    042 => "USB_OTG2",               
    043 => "USB_OTG1",               
    044 => "USB_PHY_UTMI0",               
    045 => "USB_PHY_UTMI1",               
    046 => "SSI1",               
    047 => "SSI2",               
    048 => "SSI3",               
    049 => "TEMPMON",               
    050 => "ASRC",               
    051 => "ESAI",               
    052 => "SPDIF",               
    053 => "MLB_Error",               
    054 => "PMU_BrownOut",               
    055 => "GPT",               
    056 => "EPIT1",               
    057 => "EPIT2",               
    058 => "GPIO1_INT7",               
    059 => "GPIO1_INT6",               
    060 => "GPIO1_INT5",               
    061 => "GPIO1_INT4",               
    062 => "GPIO1_INT3",               
    063 => "GPIO1_INT2",               
    064 => "GPIO1_INT1",               
    065 => "GPIO1_INT0",               
    066 => "GPIO1_Combined_0_15 ",           
    067 => "GPIO1_Combined_16_31",           
    068 => "GPIO2_Combined_0_15 ",           
    069 => "GPIO2_Combined_16_31",           
    070 => "GPIO3_Combined_0_15 ",           
    071 => "GPIO3_Combined_16_31",           
    072 => "GPIO4_Combined_0_15 ",           
    073 => "GPIO4_Combined_16_31",           
    074 => "GPIO5_Combined_0_15 ",           
    075 => "GPIO5_Combined_16_31",           
    076 => "GPIO6_Combined_0_15 ",           
    077 => "GPIO6_Combined_16_31",           
    078 => "GPIO7_Combined_0_15 ",           
    079 => "GPIO7_Combined_16_31",           
    080 => "WDOG1",               
    081 => "WDOG2",               
    082 => "KPP",               
    083 => "PWM1_PWM5",               
    084 => "PWM2_PWM6",               
    085 => "PWM3_PWM7",               
    086 => "PWM4_PWM8",               
    087 => "CCM1",               
    088 => "CCM2",               
    089 => "GPC",               
    090 => "MU_A9",               
    091 => "SRC",               
    092 => "CPU_L2",               
    093 => "CPU_Parity",               
    094 => "CPU_Perfomance",               
    095 => "CPU_CTI_Trigger",               
    096 => "SRC_WDOG",               
    097 => "SAI1",               
    098 => "SAI2",               
    099 => "MU_M4",               
    100 => "ADC1",               
    101 => "ADC2",               
    102 => "ENET2",               
    103 => "ENET2_Timer",               
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
    117 => "MLB_Channels_31_0",              
    118 => "ENET1",               
    119 => "ENET1_Timer",               
    120 => "PCIe1",               
    121 => "PCIe2",               
    122 => "PCIe3",               
    123 => "PCIe4",               
    124 => "DCIC1",               
    125 => "DCIC2",               
    126 => "MLB_Channels_63_32",             
    127 => "PMU_BrownOutCore"               
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

