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

/*!
**  @addtogroup pin_mux_module pin_mux module documentation
**  @{
*/

#ifndef pin_mux_H_
#define pin_mux_H_

/* MODULE pin_mux. */

#include "device_imx.h"

/*
** ===================================================================
**     Method      :  pin_mux_UART (component PinSettings)
*/
/*!
**     @brief
**         UART method sets registers according routing settings. Call
**         this method code to route desired pins into:
**         UART1, UART2, UART3, UART4, UART5, UART6, UART7
**         peripherals.
**     @param
**         UART_Type* base - UART base address 1..6
*/
/* ===================================================================*/
void configure_uart_pins(UART_Type* base);

/*
** ===================================================================
**     Method      :  pin_mux_ECSPI (component PinSettings)
*/
/*!
**     @brief
**         ECSPI method sets registers according routing settings. Call
**         this method code to route desired pins into:
**         ECSPI1, ECSPI2, ECSPI3, ECSPI4, ECSPI5 peripherals.
**     @param
**         ECSPI_Type* base - ECSPI base address 1..5
*/
/* ===================================================================*/
void configure_ecspi_pins(ECSPI_Type* base);

/*
** ===================================================================
**     Method      :  pin_mux_slave_ECSPI (component PinSettings)
*/
/*!
**     @brief
**         ECSPI method sets registers according routing settings. Call
**         this method code to route desired pins into:
**         ECSPI1,ECSPI2,ECSPI3,ECSPI4,ECSPI5 peripherals.
**     @param
**         ECSPI_Type* base - ECSPI base address 1..5
*/
/* ===================================================================*/
void configure_ecspi_slave_pins(ECSPI_Type* base);

/*
** ===================================================================
**     Method      :  pin_mux_I2C (component PinSettings)
*/
/*!
**     @brief
**         I2C method sets registers according routing settings. Call
**         this method code to route desired pins into:
**         I2C1, I2C2, I2C3, I2C4
**         peripherals.
**     @param
**         I2C_Type* base - I2C base address 1..4
*/
/* ===================================================================*/
void configure_i2c_pins(I2C_Type* base);

/*
** ===================================================================
**     Method      :  pin_mux_CAN (component PinSettings)
*/
/*!
**     @brief
**         CAN method sets registers according routing
**         settings. Call this method code to route desired pins into:
**         CAN1, CAN2
**         peripherals.
**     @param
**         CAN_Type* base - CAN base address 1..2
*/
/* ===================================================================*/
void configure_flexcan_pins(CAN_Type* base);

/* END pin_mux. */
#endif /* #ifndef __pins_H_ */
/*!
** @}
*/
