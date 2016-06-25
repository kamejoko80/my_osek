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

#include <stdio.h>
#include "board.h"
#include "debug_console_imx.h"
#include "ccm_imx6sx.h"
#include "rdc.h"
#include "wdog_imx.h"
#include "pin_mux.h"

/*FUNCTION*---------------------------------------------------------------------
*
* Function Name    : BOARD_ClockInit
* Returned Value   : void
* Comments         : Initialize clock base on board configuration.
*
*END*-------------------------------------------------------------------------*/
void BOARD_ClockInit(void)
{
    /* OSC/PLL is already initialized by Cortex-A9 (u-boot) */

    /* Disable WDOG3 */
    WDOG_DisablePowerdown(BOARD_WDOG_BASEADDR);

    /* Enable clock gate for IP bridge and IO mux */
    CCM_ControlGate(CCM, ccmCcgrGateIomuxIptClkIo, ccmClockNeededAll);  // iomuxc
    CCM_ControlGate(CCM, ccmCcgrGateIpmux1Clk, ccmClockNeededAll);      // ipmux 1
    CCM_ControlGate(CCM, ccmCcgrGateIpmux2Clk, ccmClockNeededAll);      // ipmux 2
    CCM_ControlGate(CCM, ccmCcgrGateIpmux3Clk, ccmClockNeededAll);      // ipmux 3
}

/*FUNCTION*---------------------------------------------------------------------
*
* Function Name    : dbg_uart_init
* Returned Value   : void
* Comments         : Initialize debug console
*
*END*-------------------------------------------------------------------------*/
void dbg_uart_init(void)
{
    /* Set debug uart for M4 core domain access only */
    RDC_SetPdapAccess(RDC, BOARD_DEBUG_UART_RDC_PDAP, 3 << (BOARD_DOMAIN_ID * 2), false, false);

    /* Select board debug clock derived from OSC clock(24M) */
    CCM_SetRootMux(CCM, ccmRootUartClkSel, ccmRootmuxUartClkOsc24m);
    /* Set relevant divider = 1. */
    CCM_SetRootDivider(CCM, ccmRootUartClkPodf, 0);
    /* Enable debug uart clock */
    CCM_ControlGate(CCM, ccmCcgrGateUartClk, ccmClockNeededAll);
    CCM_ControlGate(CCM, ccmCcgrGateUartSerialClk, ccmClockNeededAll);

    /* Configure the pin IOMUX */
    configure_uart_pins(BOARD_DEBUG_UART_BASEADDR);

    DbgConsole_Init(BOARD_DEBUG_UART_BASEADDR, 24000000, 115200);
}

/*FUNCTION*---------------------------------------------------------------------
*
* Function Name    : BOARD_RdcInit
* Returned Value   : void
* Comments         : Initialize RDC
*
*END*-------------------------------------------------------------------------*/
void BOARD_RdcInit(void)
{
    /* first move M4 core to RDC domain 1 */
    RDC_SetDomainID(RDC, rdcMdaM4, BOARD_DOMAIN_ID, false);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
