/* ---------------------------------------------------------------------------------------*/
/*  @file:    startup_MCIMX6X_M4.s                                                        */
/*  @purpose: CMSIS Cortex-M4 Core Device Startup File                                    */
/*            MCIMX6X_M4                                                                  */
/*  @version: 2.8                                                                         */
/*  @date:    2015-05-28                                                                  */
/*  @build:   b150528                                                                     */
/* ---------------------------------------------------------------------------------------*/
/*                                                                                        */
/* Copyright (c) 2015 , Freescale Semiconductor, Inc.                                     */
/* All rights reserved.                                                                   */
/*                                                                                        */
/* Redistribution and use in source and binary forms, with or without modification,       */
/* are permitted provided that the following conditions are met:                          */
/*                                                                                        */
/* o Redistributions of source code must retain the above copyright notice, this list     */
/*   of conditions and the following disclaimer.                                          */
/*                                                                                        */
/* o Redistributions in binary form must reproduce the above copyright notice, this       */
/*   list of conditions and the following disclaimer in the documentation and/or          */
/*   other materials provided with the distribution.                                      */
/*                                                                                        */
/* o Neither the name of Freescale Semiconductor, Inc. nor the names of its               */
/*   contributors may be used to endorse or promote products derived from this            */
/*   software without specific prior written permission.                                  */
/*                                                                                        */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND        */
/* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED          */
/* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE                 */
/* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR       */
/* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES         */
/* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;           */
/* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON         */
/* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT                */
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS          */
/* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/*****************************************************************************/
/* Version: GCC for ARM Embedded Processors                                  */
/*****************************************************************************/
    .syntax unified
    .arch armv7-m

    .section .isr_vector, "a"
    .align 2
    .globl __isr_vector
__isr_vector:
    .long   __StackTop                                 /* Top of Stack */
    .long   Reset_Handler                              /* Reset Handler */
    .long   NMI_Handler                                /* NMI Handler*/
    .long   HardFault_Handler                          /* Hard Fault Handler*/
    .long   MemManage_Handler                          /* MPU Fault Handler*/
    .long   BusFault_Handler                           /* Bus Fault Handler*/
    .long   UsageFault_Handler                         /* Usage Fault Handler*/
    .long   0                                          /* Reserved*/
    .long   0                                          /* Reserved*/
    .long   0                                          /* Reserved*/
    .long   0                                          /* Reserved*/
    .long   SVC_Handler                                /* SVCall Handler*/
    .long   DebugMon_Handler                           /* Debug Monitor Handler*/
    .long   0                                          /* Reserved*/
    .long   PendSV_Handler                             /* PendSV Handler*/
    .long   SysTick_Handler                            /* SysTick Handler*/

                                                       /* External Interrupts*/
    .long   CORTEX_M4_Handler                          /* Cache Controller interrupt*/
    .long   DAP_Handler                                /* Debug Access Port interrupt request*/
    .long   SDMA_Handler                               /* SDMA interrupt request from all channels*/
    .long   Reserved19_Handler                         /* Reserved*/
    .long   SNVS_PMIC_Handler                          /* PMIC power off request*/
    .long   LCDIF1_Handler                             /* LCDIF1 Sync Interrupt*/
    .long   LCDIF2_Handler                             /* LCDIF1 Sync Interrupt*/
    .long   CSI1_Handler                               /* CMOS Sensor Interface interrupt request*/
    .long   PXP_Handler                                /* PXP interrupt*/
    .long   Reserved25_Handler                         /* Reserved*/
    .long   GPU_Handler                                /* GPU general interrupt request*/
    .long   WDOG3_Handler                              /* WDOG3 interrupt request*/
    .long   SEMA4_CP1_Handler                          /* SEMA4 CP1 interrupt request*/
    .long   APBH_DMA_Handler                           /* Logical OR of APBH DMA channels 0-3 completion and error interrupts*/
    .long   EIM_Handler                                /* EIM interrupt request*/
    .long   BCH_Handler                                /* BCH operation complete interrupt*/
    .long   GPMI_Handler                               /* GPMI operation timeout error interrupt*/
    .long   UART6_Handler                              /* UART6 interrupt request*/
    .long   eCSPI5_Handler                             /* eCSPI5 interrupt request*/
    .long   SNVS_Consolidated_Handler                  /* SNVS consolidated interrupt*/
    .long   SNVS_Security_Handler                      /* SNVS security interrupt*/
    .long   CSU_Handler                                /* CSU interrupt request 1*/
    .long   uSDHC1_Handler                             /* uSDHC1 (Enhanced SDHC) interrupt request*/
    .long   uSDHC2_Handler                             /* uSDHC2 (Enhanced SDHC) interrupt request*/
    .long   uSDHC3_Handler                             /* uSDHC3 (Enhanced SDHC) interrupt request*/
    .long   uSDHC4_Handler                             /* uSDHC4 (Enhanced SDHC) interrupt request*/
    .long   UART1_Handler                              /* UART1 interrupt request*/
    .long   UART2_Handler                              /* UART2 interrupt request*/
    .long   UART3_Handler                              /* UART3 interrupt request*/
    .long   UART4_Handler                              /* UART4 interrupt request*/
    .long   UART5_Handler                              /* UART5 interrupt request*/
    .long   eCSPI1_Handler                             /* eCSPI1 interrupt request*/
    .long   eCSPI2_Handler                             /* eCSPI2 interrupt request*/
    .long   eCSPI3_Handler                             /* eCSPI3 interrupt request*/
    .long   eCSPI4_Handler                             /* eCSPI4 interrupt request*/
    .long   I2C4_Handler                               /* I2C4 interrupt request*/
    .long   I2C1_Handler                               /* I2C1 interrupt request*/
    .long   I2C2_Handler                               /* I2C2 interrupt request*/
    .long   I2C3_Handler                               /* I2C3 interrupt request*/
    .long   RDC_Handler                                /* RDC interrupt request*/
    .long   USB_HISC_Handler                           /* USB HISC Host interrupt request*/
    .long   CSI2_Handler                               /* CSI interrupt*/
    .long   USB_OTG2_Handler                           /* USB OTG 2 interrupt request*/
    .long   USB_OTG1_Handler                           /* USB OTG 1 interrupt request*/
    .long   USB_PHY_UTMI0_Handler                      /* UTMI0 interrupt request*/
    .long   USB_PHY_UTMI1_Handler                      /* UTMI1 interrupt request*/
    .long   SSI1_Handler                               /* SSI1 interrupt request*/
    .long   SSI2_Handler                               /* SSI2 interrupt request*/
    .long   SSI3_Handler                               /* SSI3 interrupt request*/
    .long   TEMPMON_Handler                            /* Temperature Sensor (temp. greater than threshold) interrupt request*/
    .long   ASRC_Handler                               /* ASRC interrupt request*/
    .long   ESAI_Handler                               /* ESAI interrupt request*/
    .long   SPDIF_Handler                              /* SPDIF Rx/Tx interrupt*/
    .long   MLB_Error_Handler                          /* MLB error interrupt request*/
    .long   PMU_BrownOut_Handler                       /* Brown-out event*/
    .long   GPT_Handler                                /* Logical OR of GPT rollover interrupt line, input capture 1 & 2 lines, output compare 1, 2 & 3 interrupt lines*/
    .long   EPIT1_Handler                              /* EPIT1 output compare interrupt*/
    .long   EPIT2_Handler                              /* EPIT2 output compare interrupt*/
    .long   GPIO1_INT7_Handler                         /* INT7 interrupt request*/
    .long   GPIO1_INT6_Handler                         /* INT6 interrupt request*/
    .long   GPIO1_INT5_Handler                         /* INT5 interrupt request*/
    .long   GPIO1_INT4_Handler                         /* INT4 interrupt request*/
    .long   GPIO1_INT3_Handler                         /* INT3 interrupt request*/
    .long   GPIO1_INT2_Handler                         /* INT2 interrupt request*/
    .long   GPIO1_INT1_Handler                         /* INT1 interrupt request*/
    .long   GPIO1_INT0_Handler                         /* INT0 interrupt request*/
    .long   GPIO1_Combined_0_15_Handler                /* Combined interrupt indication for GPIO1 signals 0 - 15*/
    .long   GPIO1_Combined_16_31_Handler               /* Combined interrupt indication for GPIO1 signals 16 - 31*/
    .long   GPIO2_Combined_0_15_Handler                /* Combined interrupt indication for GPIO2 signals 0 - 15*/
    .long   GPIO2_Combined_16_31_Handler               /* Combined interrupt indication for GPIO2 signals 16 - 31*/
    .long   GPIO3_Combined_0_15_Handler                /* Combined interrupt indication for GPIO3 signals 0 - 15*/
    .long   GPIO3_Combined_16_31_Handler               /* Combined interrupt indication for GPIO3 signals 16 - 31*/
    .long   GPIO4_Combined_0_15_Handler                /* Combined interrupt indication for GPIO4 signals 0 - 15*/
    .long   GPIO4_Combined_16_31_Handler               /* Combined interrupt indication for GPIO4 signals 16 - 31*/
    .long   GPIO5_Combined_0_15_Handler                /* Combined interrupt indication for GPIO5 signals 0 - 15*/
    .long   GPIO5_Combined_16_31_Handler               /* Combined interrupt indication for GPIO5 signals 16 - 31*/
    .long   GPIO6_Combined_0_15_Handler                /* Combined interrupt indication for GPIO6 signals 0 - 15*/
    .long   GPIO6_Combined_16_31_Handler               /* Combined interrupt indication for GPIO6 signals 16 - 31*/
    .long   GPIO7_Combined_0_15_Handler                /* Combined interrupt indication for GPIO7 signals 0 - 15*/
    .long   GPIO7_Combined_16_31_Handler               /* Combined interrupt indication for GPIO7 signals 16 - 31*/
    .long   WDOG1_Handler                              /* WDOG1 timer reset interrupt request*/
    .long   WDOG2_Handler                              /* WDOG2 timer reset interrupt request*/
    .long   KPP_Handler                                /* Key Pad interrupt request*/
    .long   PWM1_PWM5_Handler                          /* Cumulative interrupt line for PWM1/PWM5. Logical OR of rollover, compare, and FIFO waterlevel crossing interrupts*/
    .long   PWM2_PWM6_Handler                          /* Cumulative interrupt line for PWM2/PWM6. Logical OR of rollover, compare, and FIFO waterlevel crossing interrupts*/
    .long   PWM3_PWM7_Handler                          /* Cumulative interrupt line for PWM3/PWM7. Logical OR of rollover, compare, and FIFO waterlevel crossing interrupts*/
    .long   PWM4_PWM8_Handler                          /* Cumulative interrupt line for PWM4/PWM8. Logical OR of rollover, compare, and FIFO waterlevel crossing interrupts*/
    .long   CCM1_Handler                               /* CCM interrupt request 1*/
    .long   CCM2_Handler                               /* CCM interrupt request 2*/
    .long   GPC_Handler                                /* GPC interrupt request 1*/
    .long   MU_A9_Handler                              /* Message unit interrupt to A9 core*/
    .long   SRC_Handler                                /* SRC interrupt request*/
    .long   CPU_L2_Handler                             /* L2 interrupt request*/
    .long   CPU_Parity_Handler                         /* Parity Check error interrupt request*/
    .long   CPU_Perfomance_Handler                     /* Performance Unit interrupt*/
    .long   CPU_CTI_Trigger_Handler                    /* CTI trigger outputs interrupt*/
    .long   SRC_WDOG_Handler                           /* Combined CPU wdog interrupts (4x) out of SRC*/
    .long   SAI1_Handler                               /* SAI1 interrupt request*/
    .long   SAI2_Handler                               /* SAI2 interrupt request*/
    .long   MU_M4_Handler                              /* Message unit Interrupt to M4 core*/
    .long   ADC1_Handler                               /* ADC1 interrupt request*/
    .long   ADC2_Handler                               /* ADC2 interrupt request*/
    .long   ENET2_Handler                              /* ENET2 Interrupt Request*/
    .long   ENET2_Timer_Handler                        /* ENET2 1588 Timer interrupt [synchronous] request*/
    .long   SJC_Handler                                /* SJC interrupt from General Purpose register*/
    .long   CAAM0_Handler                              /* CAAM job ring 0 interrupt*/
    .long   CAAM1_Handler                              /* CAAM job ring 1 interrupt*/
    .long   QSPI1_Handler                              /* QSPI1 interrupt request*/
    .long   TZASC_Handler                              /* TZASC (PL380) interrupt request*/
    .long   QSPI2_Handler                              /* QSPI2 interrupt request*/
    .long   FLEXCAN1_Handler                           /* FLEXCAN1 combined interrupt*/
    .long   FLEXCAN2_Handler                           /* FLEXCAN1 combined interrupt*/
    .long   Reserved128_Handler                        /* Reserved*/
    .long   Reserved129_Handler                        /* Reserved*/
    .long   CANFD1_Handler                             /* CANFD1 interrupt request*/
    .long   CANFD2_Handler                             /* CANFD2 interrupt request*/
    .long   SEMA4_CP0_Handler                          /* SEMA4 CP0 interrupt request*/
    .long   MLB_Channels_31_0_Handler                  /* MLB Interrupt request for channels [31:0]*/
    .long   ENET1_Handler                              /* ENET1 Interrupt Request*/
    .long   ENET1_Timer_Handler                        /* ENET1 1588 Timer interrupt [synchronous] request*/
    .long   PCIe1_Handler                              /* PCIe interrupt request 1*/
    .long   PCIe2_Handler                              /* PCIe interrupt request 2*/
    .long   PCIe3_Handler                              /* PCIe interrupt request 3*/
    .long   PCIe4_Handler                              /* PCIe interrupt request 4*/
    .long   DCIC1_Handler                              /* DCIC1 interrupt request*/
    .long   DCIC2_Handler                              /* DCIC2 interrupt request*/
    .long   MLB_Channels_63_32_Handler                 /* MLB Interrupt request for channels [63:32]*/
    .long   PMU_BrownOutCore_Handler                   /* Brown out of core, gpu, and chip digital regulators occurred*/

    .size    __isr_vector, . - __isr_vector

    .text
    .thumb

/* Reset Handler */

    .thumb_func
    .align 2
    .globl   Reset_Handler
    .weak    Reset_Handler
    .type    Reset_Handler, %function
Reset_Handler:

    /* Mask interrupts */
    cpsid   i

    nop
    ldr    r1, =__StackTop
    mov    sp, r1

#ifndef __NO_SYSTEM_INIT
    bl SystemInit
#endif
/*     Loop to copy data from read only memory to RAM. The ranges
 *      of copy from/to are specified by following symbols evaluated in
 *      linker script.
 *      __etext: End of code section, i.e., begin of data sections to copy from.
 *      __data_start__/__data_end__: RAM address range that data should be
 *      copied to. Both must be aligned to 4 bytes boundary.  */

    ldr    r1, =__etext
    ldr    r2, =__data_start__
    ldr    r3, =__data_end__

#if 1
/* Here are two copies of loop implemenations. First one favors code size
 * and the second one favors performance. Default uses the first one.
 * Change to "#if 0" to use the second one */
.LC0:
    cmp     r2, r3
    ittt    lt
    ldrlt   r0, [r1], #4
    strlt   r0, [r2], #4
    blt    .LC0
#else
    subs    r3, r2
    ble    .LC1
.LC0:
    subs    r3, #4
    ldr    r0, [r1, r3]
    str    r0, [r2, r3]
    bgt    .LC0
.LC1:
#endif

    /* Unmask interrupts */
    cpsie   i
    bl _start
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


    .align    1
    .thumb_func
    .weak DefaultISR
    .type DefaultISR, %function
DefaultISR:
    b    DefaultISR
    .size DefaultISR, . - DefaultISR

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro def_irq_handler    handler_name
    .weak \handler_name
    .set  \handler_name, DefaultISR
    .endm

/* Exception Handlers */
    def_irq_handler    NMI_Handler
    def_irq_handler    HardFault_Handler
    def_irq_handler    MemManage_Handler
    def_irq_handler    BusFault_Handler
    def_irq_handler    UsageFault_Handler
    def_irq_handler    SVC_Handler
    def_irq_handler    DebugMon_Handler
    def_irq_handler    PendSV_Handler
    def_irq_handler    SysTick_Handler
    def_irq_handler    CORTEX_M4_Handler
    def_irq_handler    DAP_Handler                                /* Debug Access Port interrupt request*/
    def_irq_handler    SDMA_Handler                               /* SDMA interrupt request from all channels*/
    def_irq_handler    Reserved19_Handler                         /* Reserved*/
    def_irq_handler    SNVS_PMIC_Handler                          /* PMIC power off request*/
    def_irq_handler    LCDIF1_Handler                             /* LCDIF1 Sync Interrupt*/
    def_irq_handler    LCDIF2_Handler                             /* LCDIF1 Sync Interrupt*/
    def_irq_handler    CSI1_Handler                               /* CMOS Sensor Interface interrupt request*/
    def_irq_handler    PXP_Handler                                /* PXP interrupt*/
    def_irq_handler    Reserved25_Handler                         /* Reserved*/
    def_irq_handler    GPU_Handler                                /* GPU general interrupt request*/
    def_irq_handler    WDOG3_Handler                              /* WDOG3 interrupt request*/
    def_irq_handler    SEMA4_CP1_Handler                          /* SEMA4 CP1 interrupt request*/
    def_irq_handler    APBH_DMA_Handler                           /* Logical OR of APBH DMA channels 0-3 completion and error interrupts*/
    def_irq_handler    EIM_Handler                                /* EIM interrupt request*/
    def_irq_handler    BCH_Handler                                /* BCH operation complete interrupt*/
    def_irq_handler    GPMI_Handler                               /* GPMI operation timeout error interrupt*/
    def_irq_handler    UART6_Handler                              /* UART6 interrupt request*/
    def_irq_handler    eCSPI5_Handler                             /* eCSPI5 interrupt request*/
    def_irq_handler    SNVS_Consolidated_Handler                  /* SNVS consolidated interrupt*/
    def_irq_handler    SNVS_Security_Handler                      /* SNVS security interrupt*/
    def_irq_handler    CSU_Handler                                /* CSU interrupt request 1*/
    def_irq_handler    uSDHC1_Handler                             /* uSDHC1 (Enhanced SDHC) interrupt request*/
    def_irq_handler    uSDHC2_Handler                             /* uSDHC2 (Enhanced SDHC) interrupt request*/
    def_irq_handler    uSDHC3_Handler                             /* uSDHC3 (Enhanced SDHC) interrupt request*/
    def_irq_handler    uSDHC4_Handler                             /* uSDHC4 (Enhanced SDHC) interrupt request*/
    def_irq_handler    UART1_Handler                              /* UART1 interrupt request*/
    def_irq_handler    UART2_Handler                              /* UART2 interrupt request*/
    def_irq_handler    UART3_Handler                              /* UART3 interrupt request*/
    def_irq_handler    UART4_Handler                              /* UART4 interrupt request*/
    def_irq_handler    UART5_Handler                              /* UART5 interrupt request*/
    def_irq_handler    eCSPI1_Handler                             /* eCSPI1 interrupt request*/
    def_irq_handler    eCSPI2_Handler                             /* eCSPI2 interrupt request*/
    def_irq_handler    eCSPI3_Handler                             /* eCSPI3 interrupt request*/
    def_irq_handler    eCSPI4_Handler                             /* eCSPI4 interrupt request*/
    def_irq_handler    I2C4_Handler                               /* I2C4 interrupt request*/
    def_irq_handler    I2C1_Handler                               /* I2C1 interrupt request*/
    def_irq_handler    I2C2_Handler                               /* I2C2 interrupt request*/
    def_irq_handler    I2C3_Handler                               /* I2C3 interrupt request*/
    def_irq_handler    RDC_Handler                                /* RDC interrupt request*/
    def_irq_handler    USB_HISC_Handler                           /* USB HISC Host interrupt request*/
    def_irq_handler    CSI2_Handler                               /* CSI interrupt*/
    def_irq_handler    USB_OTG2_Handler                           /* USB OTG 2 interrupt request*/
    def_irq_handler    USB_OTG1_Handler                           /* USB OTG 1 interrupt request*/
    def_irq_handler    USB_PHY_UTMI0_Handler                      /* UTMI0 interrupt request*/
    def_irq_handler    USB_PHY_UTMI1_Handler                      /* UTMI1 interrupt request*/
    def_irq_handler    SSI1_Handler                               /* SSI1 interrupt request*/
    def_irq_handler    SSI2_Handler                               /* SSI2 interrupt request*/
    def_irq_handler    SSI3_Handler                               /* SSI3 interrupt request*/
    def_irq_handler    TEMPMON_Handler                            /* Temperature Sensor (temp. greater than threshold) interrupt request*/
    def_irq_handler    ASRC_Handler                               /* ASRC interrupt request*/
    def_irq_handler    ESAI_Handler                               /* ESAI interrupt request*/
    def_irq_handler    SPDIF_Handler                              /* SPDIF Rx/Tx interrupt*/
    def_irq_handler    MLB_Error_Handler                          /* MLB error interrupt request*/
    def_irq_handler    PMU_BrownOut_Handler                       /* Brown-out event*/
    def_irq_handler    GPT_Handler                                /* Logical OR of GPT rollover interrupt line, input capture 1 & 2 lines, output compare 1, 2 & 3 interrupt lines*/
    def_irq_handler    EPIT1_Handler                              /* EPIT1 output compare interrupt*/
    def_irq_handler    EPIT2_Handler                              /* EPIT2 output compare interrupt*/
    def_irq_handler    GPIO1_INT7_Handler                         /* INT7 interrupt request*/
    def_irq_handler    GPIO1_INT6_Handler                         /* INT6 interrupt request*/
    def_irq_handler    GPIO1_INT5_Handler                         /* INT5 interrupt request*/
    def_irq_handler    GPIO1_INT4_Handler                         /* INT4 interrupt request*/
    def_irq_handler    GPIO1_INT3_Handler                         /* INT3 interrupt request*/
    def_irq_handler    GPIO1_INT2_Handler                         /* INT2 interrupt request*/
    def_irq_handler    GPIO1_INT1_Handler                         /* INT1 interrupt request*/
    def_irq_handler    GPIO1_INT0_Handler                         /* INT0 interrupt request*/
    def_irq_handler    GPIO1_Combined_0_15_Handler                /* Combined interrupt indication for GPIO1 signals 0 - 15*/
    def_irq_handler    GPIO1_Combined_16_31_Handler               /* Combined interrupt indication for GPIO1 signals 16 - 31*/
    def_irq_handler    GPIO2_Combined_0_15_Handler                /* Combined interrupt indication for GPIO2 signals 0 - 15*/
    def_irq_handler    GPIO2_Combined_16_31_Handler               /* Combined interrupt indication for GPIO2 signals 16 - 31*/
    def_irq_handler    GPIO3_Combined_0_15_Handler                /* Combined interrupt indication for GPIO3 signals 0 - 15*/
    def_irq_handler    GPIO3_Combined_16_31_Handler               /* Combined interrupt indication for GPIO3 signals 16 - 31*/
    def_irq_handler    GPIO4_Combined_0_15_Handler                /* Combined interrupt indication for GPIO4 signals 0 - 15*/
    def_irq_handler    GPIO4_Combined_16_31_Handler               /* Combined interrupt indication for GPIO4 signals 16 - 31*/
    def_irq_handler    GPIO5_Combined_0_15_Handler                /* Combined interrupt indication for GPIO5 signals 0 - 15*/
    def_irq_handler    GPIO5_Combined_16_31_Handler               /* Combined interrupt indication for GPIO5 signals 16 - 31*/
    def_irq_handler    GPIO6_Combined_0_15_Handler                /* Combined interrupt indication for GPIO6 signals 0 - 15*/
    def_irq_handler    GPIO6_Combined_16_31_Handler               /* Combined interrupt indication for GPIO6 signals 16 - 31*/
    def_irq_handler    GPIO7_Combined_0_15_Handler                /* Combined interrupt indication for GPIO7 signals 0 - 15*/
    def_irq_handler    GPIO7_Combined_16_31_Handler               /* Combined interrupt indication for GPIO7 signals 16 - 31*/
    def_irq_handler    WDOG1_Handler                              /* WDOG1 timer reset interrupt request*/
    def_irq_handler    WDOG2_Handler                              /* WDOG2 timer reset interrupt request*/
    def_irq_handler    KPP_Handler                                /* Key Pad interrupt request*/
    def_irq_handler    PWM1_PWM5_Handler                          /* Cumulative interrupt line for PWM1/PWM5. Logical OR of rollover, compare, and FIFO waterlevel crossing interrupts*/
    def_irq_handler    PWM2_PWM6_Handler                          /* Cumulative interrupt line for PWM2/PWM6. Logical OR of rollover, compare, and FIFO waterlevel crossing interrupts*/
    def_irq_handler    PWM3_PWM7_Handler                          /* Cumulative interrupt line for PWM3/PWM7. Logical OR of rollover, compare, and FIFO waterlevel crossing interrupts*/
    def_irq_handler    PWM4_PWM8_Handler                          /* Cumulative interrupt line for PWM4/PWM8. Logical OR of rollover, compare, and FIFO waterlevel crossing interrupts*/
    def_irq_handler    CCM1_Handler                               /* CCM interrupt request 1*/
    def_irq_handler    CCM2_Handler                               /* CCM interrupt request 2*/
    def_irq_handler    GPC_Handler                                /* GPC interrupt request 1*/
    def_irq_handler    MU_A9_Handler                              /* Message unit interrupt to A9 core*/
    def_irq_handler    SRC_Handler                                /* SRC interrupt request*/
    def_irq_handler    CPU_L2_Handler                             /* L2 interrupt request*/
    def_irq_handler    CPU_Parity_Handler                         /* Parity Check error interrupt request*/
    def_irq_handler    CPU_Perfomance_Handler                     /* Performance Unit interrupt*/
    def_irq_handler    CPU_CTI_Trigger_Handler                    /* CTI trigger outputs interrupt*/
    def_irq_handler    SRC_WDOG_Handler                           /* Combined CPU wdog interrupts (4x) out of SRC*/
    def_irq_handler    SAI1_Handler                               /* SAI1 interrupt request*/
    def_irq_handler    SAI2_Handler                               /* SAI2 interrupt request*/
    def_irq_handler    MU_M4_Handler                              /* Message unit Interrupt to M4 core*/
    def_irq_handler    ADC1_Handler                               /* ADC1 interrupt request*/
    def_irq_handler    ADC2_Handler                               /* ADC2 interrupt request*/
    def_irq_handler    ENET2_Handler                              /* ENET2 Interrupt Request*/
    def_irq_handler    ENET2_Timer_Handler                        /* ENET2 1588 Timer interrupt [synchronous] request*/
    def_irq_handler    SJC_Handler                                /* SJC interrupt from General Purpose register*/
    def_irq_handler    CAAM0_Handler                              /* CAAM job ring 0 interrupt*/
    def_irq_handler    CAAM1_Handler                              /* CAAM job ring 1 interrupt*/
    def_irq_handler    QSPI1_Handler                              /* QSPI1 interrupt request*/
    def_irq_handler    TZASC_Handler                              /* TZASC (PL380) interrupt request*/
    def_irq_handler    QSPI2_Handler                              /* QSPI2 interrupt request*/
    def_irq_handler    FLEXCAN1_Handler                           /* FLEXCAN1 combined interrupt*/
    def_irq_handler    FLEXCAN2_Handler                           /* FLEXCAN1 combined interrupt*/
    def_irq_handler    Reserved128_Handler                        /* Reserved*/
    def_irq_handler    Reserved129_Handler                        /* Reserved*/
    def_irq_handler    CANFD1_Handler                             /* CANFD1 interrupt request*/
    def_irq_handler    CANFD2_Handler                             /* CANFD2 interrupt request*/
    def_irq_handler    SEMA4_CP0_Handler                          /* SEMA4 CP0 interrupt request*/
    def_irq_handler    MLB_Channels_31_0_Handler                  /* MLB Interrupt request for channels [31:0]*/
    def_irq_handler    ENET1_Handler                              /* ENET1 Interrupt Request*/
    def_irq_handler    ENET1_Timer_Handler                        /* ENET1 1588 Timer interrupt [synchronous] request*/
    def_irq_handler    PCIe1_Handler                              /* PCIe interrupt request 1*/
    def_irq_handler    PCIe2_Handler                              /* PCIe interrupt request 2*/
    def_irq_handler    PCIe3_Handler                              /* PCIe interrupt request 3*/
    def_irq_handler    PCIe4_Handler                              /* PCIe interrupt request 4*/
    def_irq_handler    DCIC1_Handler                              /* DCIC1 interrupt request*/
    def_irq_handler    DCIC2_Handler                              /* DCIC2 interrupt request*/
    def_irq_handler    MLB_Channels_63_32_Handler                 /* MLB Interrupt request for channels [63:32]*/
    def_irq_handler    PMU_BrownOutCore_Handler                   /* Brown out of core, gpu, and chip digital regulators occurred*/
    .end
