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

#include "board.h"
#include "pin_mux.h"

void RDC_memory_init(void)
{
    uint32_t start_image, end_image;
#if defined(__CC_ARM)
    extern uint32_t Image$$VECTOR_ROM$$Base[];
    extern uint32_t Image$$ER_m_text$$Limit[];
    extern uint32_t Image$$RW_m_data$$Base[];
    extern uint32_t Image$$RW_m_data$$Limit[];

    start_image = (uint32_t)Image$$VECTOR_ROM$$Base & 0xFFFFF000;
    end_image = (uint32_t)(Image$$ER_m_text$$Limit + (Image$$RW_m_data$$Limit - Image$$RW_m_data$$Base));
    end_image = (end_image + 0xFFF) & 0xFFFFF000;
#else
    extern uint32_t __FLASH_START[];
    extern uint32_t __FLASH_END[];

    start_image = (uint32_t)__FLASH_START & 0xFFFFF000;
    end_image   = ((uint32_t)__FLASH_END + 0xFFF) & 0xFFFFF000;
#endif

    RDC_SetMrAccess(RDC, rdcMrMmdc, start_image, end_image, (3 << (BOARD_DOMAIN_ID * 2)), true, false);
}

void hardware_init(void)
{
    /* Board specific RDC settings */
    BOARD_RdcInit();

    /* Bound part of the DDR Memory to M4 Core */
    RDC_memory_init();

    /* Board specific clock settings */
    BOARD_ClockInit();

    /* initialize debug uart */
    dbg_uart_init();

    /* In this demo, we need to share board GPIO without RDC SEMAPHORE */
    RDC_SetPdapAccess(RDC, BOARD_GPIO_LED_RDC_PDAP, 3 << (BOARD_DOMAIN_ID * 2), false, false);

    /* Configure gpio pin IOMUX */
    configure_gpio_pin(BOARD_GPIO_LED_CONFIG);
}
