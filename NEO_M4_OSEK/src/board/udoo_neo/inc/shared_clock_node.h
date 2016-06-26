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

#ifndef __SHARED_CLOCK_NODE_H__
#define __SHARED_CLOCK_NODE_H__

/*Here we assume every clock node is shared*/
typedef enum _shared_clk_index
{
    SHARED_CLK_PLL2 = 0,
    SHARED_CLK_PLL2_PFD0,
    SHARED_CLK_PLL2_PFD2,
    SHARED_CLK_PLL3,
    SHARED_CLK_PLL3_PFD1,
    SHARED_CLK_PLL3_PFD2,
    SHARED_CLK_PLL3_PFD3,
    SHARED_CLK_PLL4,
    SHARED_CLK_PLL5,
    SHARED_CLK_OCRAM,
    SHARED_CLK_FLEXCAN1,
    SHARED_CLK_FLEXCAN1_IPG,
    SHARED_CLK_FLEXCAN2,
    SHARED_CLK_FLEXCAN2_IPG,
    SHARED_CLK_CANFD,
    SHARED_CLK_ECSPI1,
    SHARED_CLK_ECSPI2,
    SHARED_CLK_ECSPI3,
    SHARED_CLK_ECSPI4,
    SHARED_CLK_ECSPI5,
    SHARED_CLK_QSPI1,
    SHARED_CLK_QSPI2,
    SHARED_CLK_SSI1,
    SHARED_CLK_SSI2,
    SHARED_CLK_SSI3,
    SHARED_CLK_UART,
    SHARED_CLK_UART_IPG,
    SHARED_CLK_PERIPH2,
    SHARED_CLK_ALT_OCRAM,
    SHARED_CLK_I2C1,
    SHARED_CLK_I2C2,
    SHARED_CLK_I2C3,
    SHARED_CLK_I2C4,
    SHARED_CLK_EPIT1,
    SHARED_CLK_EPIT2,
    SHARED_CLK_COUNT
} shared_clk_index_t;

#endif /* __SHARED_CLOCK_NODE_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
