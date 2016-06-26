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

#ifndef __GPIO_PINS_H__
#define __GPIO_PINS_H__

#include "device_imx.h"

/*! @brief i.MX GPIO initialize structure. */
typedef struct _gpio_config
{
    const char        *name;
    __IO  uint32_t    *muxReg;
    uint32_t           muxConfig;
    __IO  uint32_t    *padReg;
    uint32_t           padConfig;
    GPIO_Type         *base;
    uint32_t           pin;
} gpio_config_t;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*! @brief GPIO pin configuration */
extern gpio_config_t gpioLed;
extern gpio_config_t gpioSensorAccInt;
extern gpio_config_t gpioSensorMagAlsInt;
/*! @brief Configure specific GPIO pin */
void configure_gpio_pin(gpio_config_t *config);

#endif /* __GPIO_PINS_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
