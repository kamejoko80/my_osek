/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdbool.h>
#include "MCIMX6X_M4.h"

/* ----------------------------------------------------------------------------
   -- Helper macro
   ---------------------------------------------------------------------------- */
#define EXTRACT_BITFIELD(reg, shift, width) ((*(reg) & (((1 << (width)) - 1) << (shift))) >> (shift))

/* ----------------------------------------------------------------------------
   -- Vector Table offset
   ---------------------------------------------------------------------------- */
#define VECT_TAB_OFFSET  0x0

/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */
uint32_t SystemCoreClock = 227000000;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */
void SystemInit(void)
{
    /* The Vector table base address is given by linker script. */
#if defined(__CC_ARM)
    extern uint32_t Image$$VECTOR_ROM$$Base[];
#else
    extern uint32_t __VECTOR_TABLE[];
#endif

    /* Enable FPU */
#if ((1 == __FPU_PRESENT) && (1 == __FPU_USED))
    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
#endif

    /* M4 core clock root configuration. */

    /* Initialize Cache */
    /* Enable System Bus Cache */
    /* set command to invalidate all ways and write GO bit
       to initiate command */
    LMEM_PSCCR = LMEM_PSCCR_INVW1_MASK | LMEM_PSCCR_INVW0_MASK;
    LMEM_PSCCR |= LMEM_PSCCR_GO_MASK;
    /* Wait until the command completes */
    while (LMEM_PSCCR & LMEM_PSCCR_GO_MASK);
    /* Enable system bus cache, enable write buffer */
    LMEM_PSCCR = (LMEM_PSCCR_ENWRBUF_MASK | LMEM_PSCCR_ENCACHE_MASK);
    __ISB();

    /* Enable Code Bus Cache */
    /* set command to invalidate all ways and write GO bit
       to initiate command */
    LMEM_PCCCR = LMEM_PCCCR_INVW1_MASK | LMEM_PCCCR_INVW0_MASK;
    LMEM_PCCCR |= LMEM_PCCCR_GO_MASK;
    /* Wait until the command completes */
    while (LMEM_PCCCR & LMEM_PCCCR_GO_MASK);
    /* Enable code bus cache, enable write buffer */
    LMEM_PCCCR = (LMEM_PCCCR_ENWRBUF_MASK | LMEM_PCCCR_ENCACHE_MASK);
    __ISB();
    __DSB();

    /* Relocate vector table */
#if defined(__CC_ARM)
    SCB->VTOR = (uint32_t)Image$$VECTOR_ROM$$Base + VECT_TAB_OFFSET;
#else
    SCB->VTOR = (uint32_t)__VECTOR_TABLE + VECT_TAB_OFFSET;
#endif
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate(void)
{
    uint8_t coreClockRoot = EXTRACT_BITFIELD(&CCM_CHSCCDR, 6, 3);
    uint8_t coreClockDiv  = EXTRACT_BITFIELD(&CCM_CHSCCDR, 3, 3) + 1;
    uint64_t tempClk;

    /* If M4 clock is not divided from pre-muxed M4 clock. */
    if (0 != EXTRACT_BITFIELD(&CCM_CHSCCDR, 0, 3))
    {
        /* For the code size and performance reason, infrequently-used M4
         * Core clock source will not be covered in this function.
         * User need to calculate the clock frequency by themselves, if these
         * clock source is select.
         */
        return;
    }

    switch (coreClockRoot)
    {
        /* PLL2 */
        case 0:
            /* Check PLL2 bypass bit. */
            if (!EXTRACT_BITFIELD(&CCM_ANALOG_PLL_SYS, 16, 1))
            {
                tempClk = (1 == EXTRACT_BITFIELD(&CCM_ANALOG_PLL_SYS, \
                                   0, 1)) ? 528000000ul : 480000000ul;
            }
            else
            {
                /* PLL is bypassed. */
                tempClk = 24000000ul;
            }
            break;

        /* PLL3 SW CLK */
        case 1:
            /* Check PLL3 SW CLK selection and PLL3 bypass setting. */
            if (!EXTRACT_BITFIELD(&CCM_CCSR, 0, 1) &&
                !EXTRACT_BITFIELD(&CCM_ANALOG_PLL_USB1, 16, 1))
            {
                tempClk = (1 == EXTRACT_BITFIELD(&CCM_ANALOG_PLL_USB1, \
                                   0, 1)) ? 528000000ul : 480000000ul;
            }
            else
            {
                /* PLL3 bypass clock is selected. */
                tempClk = 24000000ul;
            }
            break;

        /* OSC CLK (24M) */
        case 2:
            tempClk = 24000000ul;
            break;

        /* PLL2 PFD0 */
        case 3:
            /* Check PLL2 bypass bit. */
            if (!EXTRACT_BITFIELD(&CCM_ANALOG_PLL_SYS, 16, 1))
            {
                /* Get PLL2 frequency. */
                tempClk = (1 == EXTRACT_BITFIELD(&CCM_ANALOG_PLL_SYS, \
                                   0, 1)) ? 528000000ul : 480000000ul;
                /* Get PLL2 PFD0 frequency. */
                tempClk *= 18;
                tempClk /= EXTRACT_BITFIELD(&CCM_ANALOG_PFD_528, 0, 6);
            }
            else
            {
                /* PLL is bypassed. */
                tempClk = 24000000ul;
            }
            break;

        /* PLL2 PFD2 */
        case 4:
            /* Check PLL2 bypass bit. */
            if (!EXTRACT_BITFIELD(&CCM_ANALOG_PLL_SYS, 16, 1))
            {
                /* Get PLL2 frequency. */
                tempClk = (1 == EXTRACT_BITFIELD(&CCM_ANALOG_PLL_SYS, \
                                   0, 1)) ? 528000000ul : 480000000ul;
                /* Get PLL2 PFD2 frequency. */
                tempClk *= 18;
                tempClk /= EXTRACT_BITFIELD(&CCM_ANALOG_PFD_528, 16, 6);
            }
            else
            {
                /* PLL is bypassed. */
                tempClk = 24000000ul;
            }
            break;

        /* PLL3 PFD3 */
        case 5:
            /* Check PLL3 bypass bit. */
            if (!EXTRACT_BITFIELD(&CCM_ANALOG_PLL_USB1, 16, 1))
            {
                /* Get PLL3 frequency. */
                tempClk = (1 == EXTRACT_BITFIELD(&CCM_ANALOG_PLL_USB1, \
                                   0, 1)) ? 528000000ul : 480000000ul;
                /* Get PLL3 PFD3 frequency. */
                tempClk *= 18;
                tempClk /= EXTRACT_BITFIELD(&CCM_ANALOG_PFD_480, 24, 6);
            }
            else
            {
                /* PLL is bypassed. */
                tempClk = 24000000ul;
            }
            break;

        default:
            /* Set tempClk to default clock freq. */
            tempClk = 227000000ul;
            coreClockDiv = 1;
            break;
    }

    SystemCoreClock = (uint32_t)(tempClk / coreClockDiv);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
