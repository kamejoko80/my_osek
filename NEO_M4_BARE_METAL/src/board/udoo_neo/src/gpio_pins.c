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

#include <assert.h>
#include "gpio_pins.h"

gpio_config_t gpioLed = {
    "DEBUG_LED",                                    /* name */
    &IOMUXC_SW_MUX_CTL_PAD_CSI_PIXCLK,              /* muxReg */
    5,                                              /* muxConfig */
    &IOMUXC_SW_PAD_CTL_PAD_CSI_PIXCLK,              /* padReg */
    IOMUXC_SW_PAD_CTL_PAD_CSI_DATA05_DSE(6)|        /* padConfig */
	IOMUXC_SW_PAD_CTL_PAD_CSI_DATA05_SPEED(2)|
	IOMUXC_SW_PAD_CTL_PAD_CSI_DATA05_PKE_MASK,
    GPIO1,                                          /* base */
    24                                              /* pin */
};

gpio_config_t gpioSensorAccInt = {
    "SensorAccInt",                                 /* name */
    &IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA23,             /* muxReg */
    5,                                              /* muxConfig */
    &IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA23,             /* padReg */
    IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA23_PUS(2) |      /* padConfig */
    IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA23_PUE_MASK |
    IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA23_PKE_MASK |
    IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA23_SPEED(2) |
    IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA23_DSE(6),
    GPIO3,                                          /* base */
    24                                              /* pin */
};

gpio_config_t gpioSensorMagAlsInt = {
    "SensorMagAlsInt",                              /* name */
    &IOMUXC_SW_MUX_CTL_PAD_SD2_CLK,                 /* muxReg */
    5,                                              /* muxConfig */
    &IOMUXC_SW_PAD_CTL_PAD_SD2_CLK,                 /* padReg */
    IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_PUS(2) |          /* padConfig */
    IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_PUE_MASK |
    IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_PKE_MASK |
    IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_SPEED(2) |
    IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_DSE(6),
    GPIO6,                                          /* base */
    6                                               /* pin */
};

void configure_gpio_pin(gpio_config_t *config)
{
    assert(config);

    *(config->muxReg) = config->muxConfig;
    *(config->padReg) = config->padConfig;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
