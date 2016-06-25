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

#ifndef __RDC_DEFS_IMX6SX__
#define __RDC_DEFS_IMX6SX__

/*!
 * @addtogroup rdc_def_imx6sx
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief RDC master assignment. */
enum _rdc_mda
{
    rdcMdaA9L2Cache  = 0U,
    rdcMdaM4         = 1U,
    rdcMdaGpu        = 2U,
    rdcMdaCsi1       = 3U,
    rdcMdaCsi2       = 4U,
    rdcMdaLcdif1     = 5U,
    rdcMdaLcdif2     = 6U,
    rdcMdaPxp        = 7U,
    rdcMdaPcieCtrl   = 8U,
    rdcMdaDap        = 9U,
    rdcMdaCaam       = 10U,
    rdcMdaSdmaPeriph = 11U,
    rdcMdaSdmaBurst  = 12U,
    rdcMdaApbhdma    = 13U,
    rdcMdaRawnand    = 14U,
    rdcMdaUsdhc1     = 15U,
    rdcMdaUsdhc2     = 16U,
    rdcMdaUsdhc3     = 17U,
    rdcMdaUsdhc4     = 18U,
    rdcMdaUsb        = 19U,
    rdcMdaMlb        = 20U,
    rdcMdaTestPort   = 21U,
    rdcMdaEnet1Tx    = 22U,
    rdcMdaEnet1Rx    = 23U,
    rdcMdaEnet2Tx    = 24U,
    rdcMdaEnet2Rx    = 25U,
    rdcMdaSdmaPort   = 26U,
};

/*! @brief RDC peripheral assignment. */
enum _rdc_pdap
{
    rdcPdapPwm1                 = 0U,
    rdcPdapPwm2                 = 1U,
    rdcPdapPwm3                 = 2U,
    rdcPdapPwm4                 = 3U,
    rdcPdapCan1                 = 4U,
    rdcPdapCan2                 = 5U,
    rdcPdapGpt                  = 6U,
    rdcPdapGpio1                = 7U,
    rdcPdapGpio2                = 8U,
    rdcPdapGpio3                = 9U,
    rdcPdapGpio4                = 10U,
    rdcPdapGpio5                = 11U,
    rdcPdapGpio6                = 12U,
    rdcPdapGpio7                = 13U,
    rdcPdapKpp                  = 14U,
    rdcPdapWdog1                = 15U,
    rdcPdapWdog2                = 16U,
    rdcPdapCcm                  = 17U,
    rdcPdapAnatopDig            = 18U,
    rdcPdapSnvsHp               = 19U,
    rdcPdapEpit1                = 20U,
    rdcPdapEpit2                = 21U,
    rdcPdapSrc                  = 22U,
    rdcPdapGpc                  = 23U,
    rdcPdapIomuxc               = 24U,
    rdcPdapIomuxcGpr            = 25U,
    rdcPdapCanfdCan1            = 26U,
    rdcPdapSdma                 = 27U,
    rdcPdapCanfdCan2            = 28U,
    rdcPdapRdcSema421           = 29U,
    rdcPdapRdcSema422           = 30U,
    rdcPdapRdc                  = 31U,
    rdcPdapAipsTz1GlobalEnable1 = 32U,
    rdcPdapAipsTz1GlobalEnable2 = 33U,
    rdcPdapUsb02hPl301          = 34U,
    rdcPdapUsb02hUsb            = 35U,
    rdcPdapEnet1                = 36U,
    rdcPdapMlb2550              = 37U,
    rdcPdapUsdhc1               = 38U,
    rdcPdapUsdhc2               = 39U,
    rdcPdapUsdhc3               = 40U,
    rdcPdapUsdhc4               = 41U,
    rdcPdapI2c1                 = 42U,
    rdcPdapI2c2                 = 43U,
    rdcPdapI2c3                 = 44U,
    rdcPdapRomcp                = 45U,
    rdcPdapMmdc                 = 46U,
    rdcPdapEnet2                = 47U,
    rdcPdapEim                  = 48U,
    rdcPdapOcotpCtrlWrapper     = 49U,
    rdcPdapCsu                  = 50U,
    rdcPdapPerfmon1             = 51U,
    rdcPdapPerfmon2             = 52U,
    rdcPdapAxiMon               = 53U,
    rdcPdapTzasc1               = 54U,
    rdcPdapSai1                 = 55U,
    rdcPdapAudmux               = 56U,
    rdcPdapSai2                 = 57U,
    rdcPdapQspi1                = 58U,
    rdcPdapQspi2                = 59U,
    rdcPdapUart2                = 60U,
    rdcPdapUart3                = 61U,
    rdcPdapUart4                = 62U,
    rdcPdapUart5                = 63U,
    rdcPdapI2c4                 = 64U,
    rdcPdapQosc                 = 65U,
    rdcPdapCaam                 = 66U,
    rdcPdapDap                  = 67U,
    rdcPdapAdc1                 = 68U,
    rdcPdapAdc2                 = 69U,
    rdcPdapWdog3                = 70U,
    rdcPdapEcspi5               = 71U,
    rdcPdapSema4                = 72U,
    rdcPdapMuA                  = 73U,
    rdcPdapCanfdCpu             = 74U,
    rdcPdapMuB                  = 75U,
    rdcPdapUart6                = 76U,
    rdcPdapPwm5                 = 77U,
    rdcPdapPwm6                 = 78U,
    rdcPdapPwm7                 = 79U,
    rdcPdapPwm8                 = 80U,
    rdcPdapAipsTz3GlobalEnable0 = 81U,
    rdcPdapAipsTz3GlobalEnable1 = 82U,
    rdcPdapSpdif                = 84U,
    rdcPdapEcspi1               = 85U,
    rdcPdapEcspi2               = 86U,
    rdcPdapEcspi3               = 87U,
    rdcPdapEcspi4               = 88U,
    rdcPdapUart1                = 91U,
    rdcPdapEsai                 = 92U,
    rdcPdapSsi1                 = 93U,
    rdcPdapSsi2                 = 94U,
    rdcPdapSsi3                 = 95U,
    rdcPdapAsrc                 = 96U,
    rdcPdapSpbaMaMegamix        = 98U,
    rdcPdapGis                  = 99U,
    rdcPdapDcic1                = 100U,
    rdcPdapDcic2                = 101U,
    rdcPdapCsi1                 = 102U,
    rdcPdapPxp                  = 103U,
    rdcPdapCsi2                 = 104U,
    rdcPdapLcdif1               = 105U,
    rdcPdapLcdif2               = 106U,
    rdcPdapVadc                 = 107U,
    rdcPdapVdec                 = 108U,
    rdcPdapSpDisplaymix         = 109U,
};

/*! @brief RDC memory region */
enum _rdc_mr
{
    rdcMrMmdc        = 0U,  /*!< alignment 4096 */
    rdcMrMmdcLast    = 7U,  /*!< alignment 4096 */
    rdcMrQspi1       = 8U,  /*!< alignment 4096 */
    rdcMrQspi1Last   = 15U, /*!< alignment 4096 */
    rdcMrQspi2       = 16U, /*!< alignment 4096 */
    rdcMrQspi2Last   = 23U, /*!< alignment 4096 */
    rdcMrWeim        = 24U, /*!< alignment 4096 */
    rdcMrWeimLast    = 31U, /*!< alignment 4096 */
    rdcMrPcie        = 32U, /*!< alignment 4096 */
    rdcMrPcieLast    = 39U, /*!< alignment 4096 */
    rdcMrOcram       = 40U, /*!< alignment 128 */
    rdcMrOcramLast   = 44U, /*!< alignment 128 */
    rdcMrOcramS      = 45U, /*!< alignment 128 */
    rdcMrOcramSLast  = 49U, /*!< alignment 128 */
    rdcMrOcramL2     = 50U, /*!< alignment 128 */
    rdcMrOcramL2Last = 54U, /*!< alignment 128 */
};

#endif /* __RDC_DEFS_IMX6SX__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
