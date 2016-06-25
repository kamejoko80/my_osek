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

#ifndef __CCM_IMX6SX_H__
#define __CCM_IMX6SX_H__

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include "device_imx.h"

/*!
 * @addtogroup ccm_driver
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define CCM_TUPLE(reg, shift, mask) ((offsetof(CCM_Type, reg) & 0xFF) | ((shift) << 8) | (((mask >> shift) & 0xFFFF) << 16))
#define CCM_TUPLE_REG(base, tuple)  (*((volatile uint32_t *)((uint32_t)base + ((tuple) & 0xFF))))
#define CCM_TUPLE_SHIFT(tuple)      (((tuple) >> 8) & 0x1F)
#define CCM_TUPLE_MASK(tuple)       ((uint32_t)((((tuple) >> 16) & 0xFFFF) << ((((tuple) >> 8) & 0x1F))))

/*!
 * @brief Root control names for root clock setting.
 *
 * These constants define the root control names for root clock setting.
 * 0:7   : REG offset to CCM_BASE in bytes.
 * 8:15  : Root clock setting bit field shift.
 * 16:31 : Root clock setting bit field width.
 */
enum _ccm_root_clock_control {
    ccmRootPll1SwClkSel     = CCM_TUPLE(CCSR, CCM_CCSR_pll1_sw_clk_sel_SHIFT, CCM_CCSR_pll1_sw_clk_sel_MASK),
    ccmRootStepSel          = CCM_TUPLE(CCSR, CCM_CCSR_step_sel_SHIFT, CCM_CCSR_step_sel_MASK),
    ccmRootPeriph2ClkSel    = CCM_TUPLE(CBCDR, CCM_CBCDR_periph2_clk_sel_SHIFT, CCM_CBCDR_periph2_clk_sel_MASK),
    ccmRootPrePeriph2ClkSel = CCM_TUPLE(CBCMR, CCM_CBCMR_pre_periph2_clk_sel_SHIFT, CCM_CBCMR_pre_periph2_clk_sel_MASK),
    ccmRootPeriph2Clk2Sel   = CCM_TUPLE(CBCMR, CCM_CBCMR_periph2_clk2_sel_SHIFT, CCM_CBCMR_periph2_clk2_sel_MASK),
    ccmRootPll3SwClkSel     = CCM_TUPLE(CCSR, CCM_CCSR_pll3_sw_clk_sel_SHIFT, CCM_CCSR_pll3_sw_clk_sel_MASK),
    ccmRootOcramClkSel      = CCM_TUPLE(CBCDR, CCM_CBCDR_ocram_clk_sel_SHIFT, CCM_CBCDR_ocram_clk_sel_MASK),
    ccmRootOcramAltClkSel   = CCM_TUPLE(CBCDR, CCM_CBCDR_ocram_alt_clk_sel_SHIFT, CCM_CBCDR_ocram_alt_clk_sel_MASK),
    ccmRootPeriphClkSel     = CCM_TUPLE(CBCDR, CCM_CBCDR_periph_clk_sel_SHIFT, CCM_CBCDR_periph_clk_sel_MASK),
    ccmRootPeriphClk2Sel    = CCM_TUPLE(CBCMR, CCM_CBCMR_periph_clk2_sel_SHIFT, CCM_CBCMR_periph_clk2_sel_MASK),
    ccmRootPrePeriphClkSel  = CCM_TUPLE(CBCMR, CCM_CBCMR_pre_periph_clk_sel_SHIFT, CCM_CBCMR_pre_periph_clk_sel_MASK),
    ccmRootPcieAxiClkSel    = CCM_TUPLE(CBCMR, CCM_CBCMR_pcie_axi_clk_sel_SHIFT, CCM_CBCMR_pcie_axi_clk_sel_MASK),
    ccmRootPerclkClkSel     = CCM_TUPLE(CSCMR1, CCM_CSCMR1_perclk_clk_sel_SHIFT, CCM_CSCMR1_perclk_clk_sel_MASK),
    ccmRootUsdhc1ClkSel     = CCM_TUPLE(CSCMR1, CCM_CSCMR1_usdhc1_clk_sel_SHIFT, CCM_CSCMR1_usdhc1_clk_sel_MASK),
    ccmRootUsdhc2ClkSel     = CCM_TUPLE(CSCMR1, CCM_CSCMR1_usdhc2_clk_sel_SHIFT, CCM_CSCMR1_usdhc2_clk_sel_MASK),
    ccmRootUsdhc3ClkSel     = CCM_TUPLE(CSCMR1, CCM_CSCMR1_usdhc3_clk_sel_SHIFT, CCM_CSCMR1_usdhc3_clk_sel_MASK),
    ccmRootUsdhc4ClkSel     = CCM_TUPLE(CSCMR1, CCM_CSCMR1_usdhc4_clk_sel_SHIFT, CCM_CSCMR1_usdhc4_clk_sel_MASK),
    ccmRootAclkEimSlowSel   = CCM_TUPLE(CSCMR1, CCM_CSCMR1_aclk_eim_slow_sel_SHIFT, CCM_CSCMR1_aclk_eim_slow_sel_MASK),
    ccmRootGpuAxiSel        = CCM_TUPLE(CBCMR, CCM_CBCMR_gpu_axi_sel_SHIFT, CCM_CBCMR_gpu_axi_sel_MASK),
    ccmRootGpuCoreSel       = CCM_TUPLE(CBCMR, CCM_CBCMR_gpu_core_sel_SHIFT, CCM_CBCMR_gpu_core_sel_MASK),
    ccmRootVidClkSel        = CCM_TUPLE(CSCMR2, CCM_CSCMR2_vid_clk_sel_SHIFT, CCM_CSCMR2_vid_clk_sel_MASK),
    ccmRootEsaiClkSel       = CCM_TUPLE(CSCMR2, CCM_CSCMR2_esai_clk_sel_SHIFT, CCM_CSCMR2_esai_clk_sel_MASK),
    ccmRootAudioClkSel      = CCM_TUPLE(CDCDR, CCM_CDCDR_audio_clk_sel_SHIFT, CCM_CDCDR_audio_clk_sel_MASK),
    ccmRootSpdif0ClkSel     = CCM_TUPLE(CDCDR, CCM_CDCDR_spdif0_clk_sel_SHIFT, CCM_CDCDR_spdif0_clk_sel_MASK),
    ccmRootSsi1ClkSel       = CCM_TUPLE(CSCMR1, CCM_CSCMR1_ssi1_clk_sel_SHIFT, CCM_CSCMR1_ssi1_clk_sel_MASK),
    ccmRootSsi2ClkSel       = CCM_TUPLE(CSCMR1, CCM_CSCMR1_ssi2_clk_sel_SHIFT, CCM_CSCMR1_ssi2_clk_sel_MASK),
    ccmRootSsi3ClkSel       = CCM_TUPLE(CSCMR1, CCM_CSCMR1_ssi3_clk_sel_SHIFT, CCM_CSCMR1_ssi3_clk_sel_MASK),
    ccmRootLcdif2ClkSel     = CCM_TUPLE(CSCDR2, CCM_CSCDR2_lcdif2_clk_sel_SHIFT, CCM_CSCDR2_lcdif2_clk_sel_MASK),
    ccmRootLcdif2PreClkSel  = CCM_TUPLE(CSCDR2, CCM_CSCDR2_lcdif2_pre_clk_sel_SHIFT, CCM_CSCDR2_lcdif2_pre_clk_sel_MASK),
    ccmRootLdbDi1ClkSel     = CCM_TUPLE(CS2CDR, CCM_CS2CDR_ldb_di1_clk_sel_SHIFT, CCM_CS2CDR_ldb_di1_clk_sel_MASK),
    ccmRootLdbDi0ClkSel     = CCM_TUPLE(CS2CDR, CCM_CS2CDR_ldb_di0_clk_sel_SHIFT, CCM_CS2CDR_ldb_di0_clk_sel_MASK),
    ccmRootLcdif1ClkSel     = CCM_TUPLE(CSCDR2, CCM_CSCDR2_lcdif1_clk_sel_SHIFT, CCM_CSCDR2_lcdif1_clk_sel_MASK),
    ccmRootLcdif1PreClkSel  = CCM_TUPLE(CSCDR2, CCM_CSCDR2_lcdif1_pre_clk_sel_SHIFT, CCM_CSCDR2_lcdif1_pre_clk_sel_MASK),
    ccmRootM4ClkSel         = CCM_TUPLE(CHSCCDR, CCM_CHSCCDR_m4_clk_sel_SHIFT, CCM_CHSCCDR_m4_clk_sel_MASK),
    ccmRootM4PreClkSel      = CCM_TUPLE(CHSCCDR, CCM_CHSCCDR_m4_pre_clk_sel_SHIFT, CCM_CHSCCDR_m4_pre_clk_sel_MASK),
    ccmRootEnetClkSel       = CCM_TUPLE(CHSCCDR, CCM_CHSCCDR_enet_clk_sel_SHIFT, CCM_CHSCCDR_enet_clk_sel_MASK),
    ccmRootEnetPreClkSel    = CCM_TUPLE(CHSCCDR, CCM_CHSCCDR_enet_pre_clk_sel_SHIFT, CCM_CHSCCDR_enet_pre_clk_sel_MASK),
    ccmRootQspi2ClkSel      = CCM_TUPLE(CS2CDR, CCM_CS2CDR_qspi2_clk_sel_SHIFT, CCM_CS2CDR_qspi2_clk_sel_MASK),
    ccmRootDisplayClkSel    = CCM_TUPLE(CSCDR3, CCM_CSCDR3_display_clk_sel_SHIFT, CCM_CSCDR3_display_clk_sel_MASK),
    ccmRootCsiClkSel        = CCM_TUPLE(CSCDR3, CCM_CSCDR3_csi_clk_sel_SHIFT, CCM_CSCDR3_csi_clk_sel_MASK),
    ccmRootCanClkSel        = CCM_TUPLE(CSCMR2, CCM_CSCMR2_can_clk_sel_SHIFT, CCM_CSCMR2_can_clk_sel_MASK),
    ccmRootEcspiClkSel      = CCM_TUPLE(CSCDR2, CCM_CSCDR2_ecspi_clk_sel_SHIFT, CCM_CSCDR2_ecspi_clk_sel_MASK),
    ccmRootUartClkSel       = CCM_TUPLE(CSCDR1, CCM_CSCDR1_uart_clk_sel_SHIFT, CCM_CSCDR1_uart_clk_sel_MASK)
};

/*!
 * @brief Root clock select enumeration for pll1_sw_clk_sel.
 */
enum _ccm_rootmux_pll1_sw_clk_sel {
    ccmRootmuxPll1SwClkPll1MainClk = 0U,
    ccmRootmuxPll1SwClkStepClk     = 1U
};

/*!
 * @brief Root clock select enumeration for step_sel.
 */
enum _ccm_rootmux_step_sel {
    ccmRootmuxStepOsc24m   = 0U,
    ccmRootmuxStepPll2Pfd2 = 1U
};

/*!
 * @brief Root clock select enumeration for periph2_clk_sel.
 */
enum _ccm_rootmux_periph2_clk_sel {
    ccmRootmuxPeriph2ClkPrePeriph2Clk = 0U,
    ccmRootmuxPeriph2ClkPeriph2Clk2   = 1U
};

/*!
 * @brief Root clock select enumeration for pre_periph2_clk_sel.
 */
enum _ccm_rootmux_pre_periph2_clk_sel {
    ccmRootmuxPrePeriph2ClkPll2     = 0U,
    ccmRootmuxPrePeriph2ClkPll2Pfd2 = 1U,
    ccmRootmuxPrePeriph2ClkPll2Pfd0 = 2U,
    ccmRootmuxPrePeriph2ClkPll4     = 3U
};

/*!
 * @brief Root clock select enumeration for periph2_clk2_sel.
 */
enum _ccm_rootmux_periph2_clk2_sel {
    ccmRootmuxPeriph2Clk2Pll3SwClk = 0U,
    ccmRootmuxPeriph2Clk2Osc24m    = 1U
};

/*!
 * @brief Root clock select enumeration for pll3_sw_clk_sel.
 */
enum _ccm_rootmux_pll3_sw_clk_sel {
    ccmRootmuxPll3SwClkPll3          = 0U,
    ccmRootmuxPll3SwClkPll3BypassClk = 1U
};

/*!
 * @brief Root clock select enumeration for ocram_clk_sel.
 */
enum _ccm_rootmux_ocram_clk_sel {
    ccmRootmuxOcramClkPeriphClk   = 0U,
    ccmRootmuxOcramClkOcramAltClk = 1U
};

/*!
 * @brief Root clock select enumeration for ocram_alt_clk_sel.
 */
enum _ccm_rootmux_ocram_alt_clk_sel {
    ccmRootmuxOcramAltClkPll2Pfd2 = 0U,
    ccmRootmuxOcramAltClkPll3Pfd1 = 1U
};

/*!
 * @brief Root clock select enumeration for periph_clk_sel.
 */
enum _ccm_rootmux_periph_clk_sel {
    ccmRootmuxPeriphClkPrePeriphClkSel = 0U,
    ccmRootmuxPeriphClkPeriphClk2Sel   = 1U
};

/*!
 * @brief Root clock select enumeration for periph_clk2_sel.
 */
enum _ccm_rootmux_periph_clk2_sel {
    ccmRootmuxPeriphClk2Pll3SwClk = 0U,
    ccmRootmuxPeriphClk2OSC24m    = 1U,
    ccmRootmuxPeriphClk2Pll2      = 2U
};

/*!
 * @brief Root clock select enumeration for pre_periph_clk_sel.
 */
enum _ccm_rootmux_pre_periph_clk_sel {
    ccmRootmuxPrePeriphClkPll2         = 0U,
    ccmRootmuxPrePeriphClkPll2Pfd2     = 1U,
    ccmRootmuxPrePeriphClkPll2Pfd0     = 2U,
    ccmRootmuxPrePeriphClkPll2Pfd2div2 = 3U
};

/*!
 * @brief Root clock select enumeration for pcie_axi_clk_sel.
 */
enum _ccm_rootmux_pcie_axi_clk_sel {
    ccmRootmuxPcieAxiClkAxiClk = 0U,
    ccmRootmuxPcieAxiClkAhbClk = 1U
};

/*!
 * @brief Root clock select enumeration for perclk_clk_sel.
 */
enum _ccm_rootmux_perclk_clk_sel {
    ccmRootmuxPerclkClkIpgClkRoot = 0U,
    ccmRootmuxPerclkClkOsc24m     = 1U
};

/*!
 * @brief Root clock select enumeration for usdhc1_clk_sel.
 */
enum _ccm_rootmux_usdhc1_clk_sel {
    ccmRootmuxUsdhc1ClkPll2Pfd2 = 0U,
    ccmRootmuxUsdhc1ClkPll2Pfd0 = 1U
};

/*!
 * @brief Root clock select enumeration for usdhc2_clk_sel.
 */
enum _ccm_rootmux_usdhc2_clk_sel {
    ccmRootmuxUsdhc2ClkPll2Pfd2 = 0U,
    ccmRootmuxUsdhc2ClkPll2Pfd0 = 1U
};

/*!
 * @brief Root clock select enumeration for usdhc3_clk_sel.
 */
enum _ccm_rootmux_usdhc3_clk_sel {
    ccmRootmuxUsdhc3ClkPll2Pfd2 = 0U,
    ccmRootmuxUsdhc3ClkPll2Pfd0 = 1U
};

/*!
 * @brief Root clock select enumeration for usdhc4_clk_sel.
 */
enum _ccm_rootmux_usdhc4_clk_sel {
    ccmRootmuxUsdhc4ClkPll2Pfd2 = 0U,
    ccmRootmuxUsdhc4ClkPll2Pfd0 = 1U
};

/*!
 * @brief Root clock select enumeration for aclk_eim_slow_sel.
 */
enum _ccm_rootmux_aclk_eim_slow_sel {
    ccmRootmuxAclkEimSlowAxiClk    = 0U,
    ccmRootmuxAclkEimSlowPll3SwClk = 1U,
    ccmRootmuxAclkEimSlowPll2Pfd2  = 2U,
    ccmRootmuxAclkEimSlowPll3Pfd0  = 3U
};

/*!
 * @brief Root clock select enumeration for gpu_axi_sel.
 */
enum _ccm_rootmux_gpu_axi_sel {
    ccmRootmuxGpuAxiPll2Pfd2 = 0U,
    ccmRootmuxGpuAxiPll3Pfd0 = 1U,
    ccmRootmuxGpuAxiPll2Pfd1 = 2U,
    ccmRootmuxGpuAxiPll2     = 3U
};

/*!
 * @brief Root clock select enumeration for gpu_core_sel.
 */
enum _ccm_rootmux_gpu_core_sel {
    ccmRootmuxGpuCorePll3Pfd1 = 0U,
    ccmRootmuxGpuCorePll3Pfd0 = 1U,
    ccmRootmuxGpuCorePll2     = 2U,
    ccmRootmuxGpuCorePll2Pfd2 = 3U
};

/*!
 * @brief Root clock select enumeration for vid_clk_sel.
 */
enum _ccm_rootmux_vid_clk_sel {
    ccmRootmuxVidClkPll3Pfd1 = 0U,
    ccmRootmuxVidClkPll3     = 1U,
    ccmRootmuxVidClkPll3Pfd3 = 2U,
    ccmRootmuxVidClkPll4     = 3U,
    ccmRootmuxVidClkPll5     = 4U
};

/*!
 * @brief Root clock select enumeration for esai_clk_sel.
 */
enum _ccm_rootmux_esai_clk_sel {
    ccmRootmuxEsaiClkPll4      = 0U,
    ccmRootmuxEsaiClkPll3Pfd2  = 1U,
    ccmRootmuxEsaiClkPll5      = 2U,
    ccmRootmuxEsaiClkPll3SwClk = 3U
};

/*!
 * @brief Root clock select enumeration for audio_clk_sel.
 */
enum _ccm_rootmux_audio_clk_sel {
    ccmRootmuxAudioClkPll4      = 0U,
    ccmRootmuxAudioClkPll3Pfd2  = 1U,
    ccmRootmuxAudioClkPll5      = 2U,
    ccmRootmuxAudioClkPll3SwClk = 3U
};

/*!
 * @brief Root clock select enumeration for spdif0_clk_sel.
 */
enum _ccm_rootmux_spdif0_clk_sel {
    ccmRootmuxSpdif0ClkPll4      = 0U,
    ccmRootmuxSpdif0ClkPll3Pfd2  = 1U,
    ccmRootmuxSpdif0ClkPll5      = 2U,
    ccmRootmuxSpdif0ClkPll3SwClk = 3U
};

/*!
 * @brief Root clock select enumeration for ssi1_clk_sel.
 */
enum _ccm_rootmux_ssi1_clk_sel {
    ccmRootmuxSsi1ClkPll3Pfd2 = 0U,
    ccmRootmuxSsi1ClkPll5     = 1U,
    ccmRootmuxSsi1ClkPll4     = 2U
};

/*!
 * @brief Root clock select enumeration for ssi2_clk_sel.
 */
enum _ccm_rootmux_ssi2_clk_sel {
    ccmRootmuxSsi2ClkPll3Pfd2 = 0U,
    ccmRootmuxSsi2ClkPll5     = 1U,
    ccmRootmuxSsi2ClkPll4     = 2U
};

/*!
 * @brief Root clock select enumeration for ssi3_clk_sel.
 */
enum _ccm_rootmux_ssi3_clk_sel {
    ccmRootmuxSsi3ClkPll3Pfd2 = 0U,
    ccmRootmuxSsi3ClkPll5     = 1U,
    ccmRootmuxSsi3ClkPll4     = 2U
};

/*!
 * @brief Root clock select enumeration for lcdif2_clk_sel.
 */
enum _ccm_rootmux_lcdif2_clk_sel {
    ccmRootmuxLcdif2ClkLcdif2PreClk = 0U,
    ccmRootmuxLcdif2ClkIppDi0Clk    = 1U,
    ccmRootmuxLcdif2ClkIppDi1Clk    = 2U,
    ccmRootmuxLcdif2ClkLdbDi0Clk    = 3U,
    ccmRootmuxLcdif2ClkLdbDi1Clk    = 4U
};

/*!
 * @brief Root clock select enumeration for lcdif2_pre_clk_sel.
 */
enum _ccm_rootmux_lcdif2_pre_clk_sel {
    ccmRootmuxLcdif2ClkPrePll2     = 0U,
    ccmRootmuxLcdif2ClkPrePll3Pfd3 = 1U,
    ccmRootmuxLcdif2ClkPrePll5     = 2U,
    ccmRootmuxLcdif2ClkPrePll2Pfd0 = 3U,
    ccmRootmuxLcdif2ClkPrePll2Pfd3 = 4U,
    ccmRootmuxLcdif2ClkPrePll3Pfd1 = 5U
};

/*!
 * @brief Root clock select enumeration for ldb_di1_clk_sel.
 */
enum _ccm_rootmux_ldb_di1_clk_sel {
    ccmRootmuxLdbDi1ClkPll3SwClk = 0U,
    ccmRootmuxLdbDi1ClkPll2Pfd0  = 1U,
    ccmRootmuxLdbDi1ClkPll2Pfd2  = 2U,
    ccmRootmuxLdbDi1ClkPll2      = 3U,
    ccmRootmuxLdbDi1ClkPll3Pfd3  = 4U,
    ccmRootmuxLdbDi1ClkPll3Pfd2  = 5U
};

/*!
 * @brief Root clock select enumeration for ldb_di0_clk_sel.
 */
enum _ccm_rootmux_ldb_di0_clk_sel {
    ccmRootmuxLdbDi0ClkPll5     = 0U,
    ccmRootmuxLdbDi0ClkPll2Pfd0 = 1U,
    ccmRootmuxLdbDi0ClkPll2Pfd2 = 2U,
    ccmRootmuxLdbDi0ClkPll2Pfd3 = 3U,
    ccmRootmuxLdbDi0ClkPll3Pfd1 = 4U,
    ccmRootmuxLdbDi0ClkPll3Pfd3 = 5U
};

/*!
 * @brief Root clock select enumeration for lcdif1_clk_sel.
 */
enum _ccm_rootmux_lcdif1_clk_sel {
    ccmRootmuxLcdif1ClkLcdif1PreClk = 0U,
    ccmRootmuxLcdif1ClkIppDi0Clk    = 1U,
    ccmRootmuxLcdif1ClkIppDi1Clk    = 2U,
    ccmRootmuxLcdif1ClkLdbDi0Clk    = 3U,
    ccmRootmuxLcdif1ClkLdbDi1Clk    = 4U
};

/*!
 * @brief Root clock select enumeration for lcdif1_pre_clk_sel.
 */
enum _ccm_rootmux_lcdif1_pre_clk_sel {
    ccmRootmuxLcdif1PreClkPll2     = 0U,
    ccmRootmuxLcdif1PreClkPll3Pfd3 = 1U,
    ccmRootmuxLcdif1PreClkPll5     = 2U,
    ccmRootmuxLcdif1PreClkPll2Pfd0 = 3U,
    ccmRootmuxLcdif1PreClkPll2Pfd1 = 4U,
    ccmRootmuxLcdif1PreClkPll3Pfd1 = 5U
};

/*!
 * @brief Root clock select enumeration for m4_clk_sel.
 */
enum _ccm_rootmux_m4_clk_sel {
    ccmRootmuxM4ClkM4PreClk  = 0U,
    ccmRootmuxM4ClkPll3Pfd3  = 1U,
    ccmRootmuxM4ClkIppDi0Clk = 2U,
    ccmRootmuxM4ClkIppDi1Clk = 3U,
    ccmRootmuxM4ClkLdbDi0Clk = 4U,
    ccmRootmuxM4ClkLdbDi1Clk = 5U
};

/*!
 * @brief Root clock select enumeration for m4_pre_clk_sel.
 */
enum _ccm_rootmux_m4_pre_clk_sel {
    ccmRootmuxM4PreClkPll2      = 0U,
    ccmRootmuxM4PreClkPll3SwClk = 1U,
    ccmRootmuxM4PreClkOsc24m    = 2U,
    ccmRootmuxM4PreClkPll2Pfd0  = 3U,
    ccmRootmuxM4PreClkPll2Pfd2  = 4U,
    ccmRootmuxM4PreClkPll3Pfd3  = 5U
};

/*!
 * @brief Root clock select enumeration for nent_clk_sel.
 */
enum _ccm_rootmux_enet_clk_sel {
    ccmRootmuxEnetClkEnetPreClk = 0U,
    ccmRootmuxEnetClkIppDi0Clk  = 1U,
    ccmRootmuxEnetClkIppDi1Clk  = 2U,
    ccmRootmuxEnetClkLdbDi0Clk  = 3U,
    ccmRootmuxEnetClkLdbDi1Clk  = 4U
};

/*!
 * @brief Root clock select enumeration for nent_pre_clk_sel.
 */
enum _ccm_rootmux_enet_pre_clk_sel {
    ccmRootmuxEnetPreClkPll2      = 0U,
    ccmRootmuxEnetPreClkPll3SwClk = 1U,
    ccmRootmuxEnetPreClkPll5      = 2U,
    ccmRootmuxEnetPreClkPll2Pfd0  = 3U,
    ccmRootmuxEnetPreClkPll2Pfd2  = 4U,
    ccmRootmuxEnetPreClkPll3Pfd2  = 5U
};

/*!
 * @brief Root clock select enumeration for qspi2_clk_sel.
 */
enum _ccm_rootmux_qspi2_clk_sel {
    ccmRootmuxQspi2ClkPll2Pfd0  = 0U,
    ccmRootmuxQspi2ClkPll2      = 1U,
    ccmRootmuxQspi2ClkPll3SwClk = 2U,
    ccmRootmuxQspi2ClkPll2Pfd2  = 3U,
    ccmRootmuxQspi2ClkPll3Pfd3  = 4U
};

/*!
 * @brief Root clock select enumeration for display_clk_sel.
 */
enum _ccm_rootmux_display_clk_sel {
    ccmRootmuxDisplayClkPll2      = 0U,
    ccmRootmuxDisplayClkPll2Pfd2  = 1U,
    ccmRootmuxDisplayClkPll3SwClk = 2U,
    ccmRootmuxDisplayClkPll3Pfd1  = 3U
};

/*!
 * @brief Root clock select enumeration for csi_clk_sel.
 */
enum _ccm_rootmux_csi_clk_sel {
    ccmRootmuxCsiClkOSC24m        = 0U,
    ccmRootmuxCsiClkPll2Pfd2      = 1U,
    ccmRootmuxCsiClkPll3SwClkDiv2 = 2U,
    ccmRootmuxCsiClkPll3Pfd1      = 3U
};

/*!
 * @brief Root clock select enumeration for can_clk_sel.
 */
enum _ccm_rootmux_can_clk_sel {
    ccmRootmuxCanClkPll3SwClkDiv8     = 0U,
    ccmRootmuxCanClkOsc24m            = 1U,
    ccmRootmuxCanClkPll3SwClkDiv6     = 2U,
    ccmRootmuxCanClkDisableFlexcanClk = 3U
};

/*!
 * @brief Root clock select enumeration for ecspi_clk_sel.
 */
enum _ccm_rootmux_ecspi_clk_sel {
    ccmRootmuxEcspiClkPll3SwClkDiv8 = 0U,
    ccmRootmuxEcspiClkOsc24m        = 1U
};

/*!
 * @brief Root clock select enumeration for uart_clk_sel.
 */
enum _ccm_rootmux_uart_clk_sel {
    ccmRootmuxUartClkPll3SwClkDiv6 = 0U,
    ccmRootmuxUartClkOsc24m        = 1U
};

/*!
 * @brief Root control names for root divider setting.
 *
 * These constants define the root control names for root divider setting.
 * 0:7   : REG offset to CCM_BASE in bytes.
 * 8:15  : Root divider setting bit field shift.
 * 16:31 : Root divider setting bit field width.
 */
enum _ccm_root_div_control {
    ccmRootArmPodf         = CCM_TUPLE(CACRR, CCM_CACRR_arm_podf_SHIFT, CCM_CACRR_arm_podf_MASK),
    ccmRootFabricMmdcPodf  = CCM_TUPLE(CBCDR, CCM_CBCDR_fabric_mmdc_podf_SHIFT, CCM_CBCDR_fabric_mmdc_podf_MASK),
    ccmRootPeriph2Clk2Podf = CCM_TUPLE(CBCDR, CCM_CBCDR_periph2_clk2_podf_SHIFT, CCM_CBCDR_periph2_clk2_podf_MASK),
    ccmRootOcramPodf       = CCM_TUPLE(CBCDR, CCM_CBCDR_ocram_podf_SHIFT, CCM_CBCDR_ocram_podf_MASK),
    ccmRootAhbPodf         = CCM_TUPLE(CBCDR, CCM_CBCDR_ahb_podf_SHIFT, CCM_CBCDR_ahb_podf_MASK),
    ccmRootPeriphClk2Podf  = CCM_TUPLE(CBCDR, CCM_CBCDR_periph_clk2_podf_SHIFT, CCM_CBCDR_periph_clk2_podf_MASK),
    ccmRootPerclkPodf      = CCM_TUPLE(CSCMR1, CCM_CSCMR1_perclk_podf_SHIFT, CCM_CSCMR1_perclk_podf_MASK),
    ccmRootIpgPodf         = CCM_TUPLE(CBCDR, CCM_CBCDR_ipg_podf_SHIFT, CCM_CBCDR_ipg_podf_MASK),
    ccmRootUsdhc1Podf      = CCM_TUPLE(CSCDR1, CCM_CSCDR1_usdhc1_podf_SHIFT, CCM_CSCDR1_usdhc1_podf_MASK),
    ccmRootUsdhc2Podf      = CCM_TUPLE(CSCDR1, CCM_CSCDR1_usdhc2_podf_SHIFT, CCM_CSCDR1_usdhc2_podf_MASK),
    ccmRootUsdhc3Podf      = CCM_TUPLE(CSCDR1, CCM_CSCDR1_usdhc3_podf_SHIFT, CCM_CSCDR1_usdhc3_podf_MASK),
    ccmRootUsdhc4Podf      = CCM_TUPLE(CSCDR1, CCM_CSCDR1_usdhc4_podf_SHIFT, CCM_CSCDR1_usdhc4_podf_MASK),
    ccmRootAclkEimSlowPodf = CCM_TUPLE(CSCMR1, CCM_CSCMR1_aclk_eim_slow_podf_SHIFT, CCM_CSCMR1_aclk_eim_slow_podf_MASK),
    ccmRootGpuAxiPodf      = CCM_TUPLE(CBCMR, CCM_CBCMR_gpu_axi_podf_SHIFT, CCM_CBCMR_gpu_axi_podf_MASK),
    ccmRootGpuCorePodf     = CCM_TUPLE(CBCMR, CCM_CBCMR_gpu_core_podf_SHIFT, CCM_CBCMR_gpu_core_podf_MASK),
    ccmRootVidClkPodf      = CCM_TUPLE(CSCMR2, CCM_CSCMR2_vid_clk_podf_SHIFT, CCM_CSCMR2_vid_clk_podf_MASK),
    ccmRootEsaiClkPodf     = CCM_TUPLE(CS1CDR, CCM_CS1CDR_esai_clk_podf_SHIFT, CCM_CS1CDR_esai_clk_podf_MASK),
    ccmRootEsaiClkPred     = CCM_TUPLE(CS1CDR, CCM_CS1CDR_esai_clk_pred_SHIFT, CCM_CS1CDR_esai_clk_pred_MASK),
    ccmRootAudioClkPodf    = CCM_TUPLE(CDCDR, CCM_CDCDR_audio_clk_podf_SHIFT, CCM_CDCDR_audio_clk_podf_MASK),
    ccmRootAudioClkPred    = CCM_TUPLE(CDCDR, CCM_CDCDR_audio_clk_pred_SHIFT, CCM_CDCDR_audio_clk_pred_MASK),
    ccmRootSpdif0ClkPodf   = CCM_TUPLE(CDCDR, CCM_CDCDR_spdif0_clk_podf_SHIFT, CCM_CDCDR_spdif0_clk_podf_MASK),
    ccmRootSpdif0ClkPred   = CCM_TUPLE(CDCDR, CCM_CDCDR_spdif0_clk_pred_SHIFT, CCM_CDCDR_spdif0_clk_pred_MASK),
    ccmRootSsi1ClkPodf     = CCM_TUPLE(CS1CDR, CCM_CS1CDR_ssi1_clk_podf_SHIFT, CCM_CS1CDR_ssi1_clk_podf_MASK),
    ccmRootSsi1ClkPred     = CCM_TUPLE(CS1CDR, CCM_CS1CDR_ssi1_clk_pred_SHIFT, CCM_CS1CDR_ssi1_clk_pred_MASK),
    ccmRootSsi2ClkPodf     = CCM_TUPLE(CS2CDR, CCM_CS2CDR_ssi2_clk_podf_SHIFT, CCM_CS2CDR_ssi2_clk_podf_MASK),
    ccmRootSsi2ClkPred     = CCM_TUPLE(CS2CDR, CCM_CS2CDR_ssi2_clk_pred_SHIFT, CCM_CS2CDR_ssi2_clk_pred_MASK),
    ccmRootSsi3ClkPodf     = CCM_TUPLE(CS1CDR, CCM_CS1CDR_ssi3_clk_podf_SHIFT, CCM_CS1CDR_ssi3_clk_podf_MASK),
    ccmRootSsi3ClkPred     = CCM_TUPLE(CS1CDR, CCM_CS1CDR_ssi3_clk_pred_SHIFT, CCM_CS1CDR_ssi3_clk_pred_MASK),
    ccmRootLcdif2Podf      = CCM_TUPLE(CSCMR1, CCM_CSCMR1_lcdif2_podf_SHIFT, CCM_CSCMR1_lcdif2_podf_MASK),
    ccmRootLcdif2Pred      = CCM_TUPLE(CSCDR2, CCM_CSCDR2_lcdif2_pred_SHIFT, CCM_CSCDR2_lcdif2_pred_MASK),
    ccmRootLdbDi1Div       = CCM_TUPLE(CSCMR2, CCM_CSCMR2_ldb_di1_div_SHIFT, CCM_CSCMR2_ldb_di1_div_MASK),
    ccmRootLdbDi0Div       = CCM_TUPLE(CSCMR2, CCM_CSCMR2_ldb_di0_div_SHIFT, CCM_CSCMR2_ldb_di0_div_MASK),
    ccmRootLcdif1Podf      = CCM_TUPLE(CBCMR, CCM_CBCMR_lcdif1_podf_SHIFT, CCM_CBCMR_lcdif1_podf_MASK),
    ccmRootLcdif1Pred      = CCM_TUPLE(CSCDR2, CCM_CSCDR2_lcdif1_pred_SHIFT, CCM_CSCDR2_lcdif1_pred_MASK),
    ccmRootM4Podf          = CCM_TUPLE(CHSCCDR, CCM_CHSCCDR_m4_podf_SHIFT, CCM_CHSCCDR_m4_podf_MASK),
    ccmRootEnetPodf        = CCM_TUPLE(CHSCCDR, CCM_CHSCCDR_enet_podf_SHIFT, CCM_CHSCCDR_enet_podf_MASK),
    ccmRootQspi1Podf       = CCM_TUPLE(CSCMR1, CCM_CSCMR1_qspi1_podf_SHIFT, CCM_CSCMR1_qspi1_podf_MASK),
    ccmRootQspi2ClkPodf    = CCM_TUPLE(CS2CDR, CCM_CS2CDR_qspi2_clk_podf_SHIFT, CCM_CS2CDR_qspi2_clk_podf_MASK),
    ccmRootQspi2ClkPred    = CCM_TUPLE(CS2CDR, CCM_CS2CDR_qspi2_clk_pred_SHIFT, CCM_CS2CDR_qspi2_clk_pred_MASK),
    ccmRootDisplayPodf     = CCM_TUPLE(CSCDR3, CCM_CSCDR3_display_podf_SHIFT, CCM_CSCDR3_display_podf_MASK),
    ccmRootCsiPodf         = CCM_TUPLE(CSCDR3, CCM_CSCDR3_csi_podf_SHIFT, CCM_CSCDR3_csi_podf_MASK),
    ccmRootCanClkPodf      = CCM_TUPLE(CSCMR2, CCM_CSCMR2_can_clk_podf_SHIFT, CCM_CSCMR2_can_clk_podf_MASK),
    ccmRootEcspiClkPodf    = CCM_TUPLE(CSCDR2, CCM_CSCDR2_ecspi_clk_podf_SHIFT, CCM_CSCDR2_ecspi_clk_podf_MASK),
    ccmRootUartClkPodf     = CCM_TUPLE(CSCDR1, CCM_CSCDR1_uart_clk_podf_SHIFT, CCM_CSCDR1_uart_clk_podf_MASK)
};

/*!
 * @brief CCM CCGR gate control for each module independently.
 *
 * These constants define the ccm ccgr clock gate for each module.
 * 0:7   : REG offset to CCM_BASE in bytes.
 * 8:15  : Root divider setting bit field shift.
 * 16:31 : Root divider setting bit field width.
 */
enum _ccm_ccgr_gate {
    ccmCcgrGateAipsTz1Clk         = CCM_TUPLE(CCGR0, CCM_CCGR0_CG0_SHIFT, CCM_CCGR0_CG0_MASK),
    ccmCcgrGateAipsTz2Clk         = CCM_TUPLE(CCGR0, CCM_CCGR0_CG1_SHIFT, CCM_CCGR0_CG1_MASK),
    ccmCcgrGateApbhdmaHclk        = CCM_TUPLE(CCGR0, CCM_CCGR0_CG2_SHIFT, CCM_CCGR0_CG2_MASK),
    ccmCcgrGateAsrcClk            = CCM_TUPLE(CCGR0, CCM_CCGR0_CG3_SHIFT, CCM_CCGR0_CG3_MASK),
    ccmCcgrGateCaamSecureMemClk   = CCM_TUPLE(CCGR0, CCM_CCGR0_CG4_SHIFT, CCM_CCGR0_CG4_MASK),
    ccmCcgrGateCaamWrapperAclk    = CCM_TUPLE(CCGR0, CCM_CCGR0_CG5_SHIFT, CCM_CCGR0_CG5_MASK),
    ccmCcgrGateCaamWrapperIpg     = CCM_TUPLE(CCGR0, CCM_CCGR0_CG6_SHIFT, CCM_CCGR0_CG6_MASK),
    ccmCcgrGateCan1Clk            = CCM_TUPLE(CCGR0, CCM_CCGR0_CG7_SHIFT, CCM_CCGR0_CG7_MASK),
    ccmCcgrGateCan1SerialClk      = CCM_TUPLE(CCGR0, CCM_CCGR0_CG8_SHIFT, CCM_CCGR0_CG8_MASK),
    ccmCcgrGateCan2Clk            = CCM_TUPLE(CCGR0, CCM_CCGR0_CG9_SHIFT, CCM_CCGR0_CG9_MASK),
    ccmCcgrGateCan2SerialClk      = CCM_TUPLE(CCGR0, CCM_CCGR0_CG10_SHIFT, CCM_CCGR0_CG10_MASK),
    ccmCcgrGateArmDbgClk          = CCM_TUPLE(CCGR0, CCM_CCGR0_CG11_SHIFT, CCM_CCGR0_CG11_MASK),
    ccmCcgrGateDcic1Clk           = CCM_TUPLE(CCGR0, CCM_CCGR0_CG12_SHIFT, CCM_CCGR0_CG12_MASK),
    ccmCcgrGateDcic2Clk           = CCM_TUPLE(CCGR0, CCM_CCGR0_CG13_SHIFT, CCM_CCGR0_CG13_MASK),
    ccmCcgrGateAipsTz3Clk         = CCM_TUPLE(CCGR0, CCM_CCGR0_CG15_SHIFT, CCM_CCGR0_CG15_MASK),
    ccmCcgrGateEcspi1Clk          = CCM_TUPLE(CCGR1, CCM_CCGR1_CG0_SHIFT, CCM_CCGR1_CG0_MASK),
    ccmCcgrGateEcspi2Clk          = CCM_TUPLE(CCGR1, CCM_CCGR1_CG1_SHIFT, CCM_CCGR1_CG1_MASK),
    ccmCcgrGateEcspi3Clk          = CCM_TUPLE(CCGR1, CCM_CCGR1_CG2_SHIFT, CCM_CCGR1_CG2_MASK),
    ccmCcgrGateEcspi4Clk          = CCM_TUPLE(CCGR1, CCM_CCGR1_CG3_SHIFT, CCM_CCGR1_CG3_MASK),
    ccmCcgrGateEcspi5Clk          = CCM_TUPLE(CCGR1, CCM_CCGR1_CG4_SHIFT, CCM_CCGR1_CG4_MASK),
    ccmCcgrGateEpit1Clk           = CCM_TUPLE(CCGR1, CCM_CCGR1_CG6_SHIFT, CCM_CCGR1_CG6_MASK),
    ccmCcgrGateEpit2Clk           = CCM_TUPLE(CCGR1, CCM_CCGR1_CG7_SHIFT, CCM_CCGR1_CG7_MASK),
    ccmCcgrGateEsaiClk            = CCM_TUPLE(CCGR1, CCM_CCGR1_CG8_SHIFT, CCM_CCGR1_CG8_MASK),
    ccmCcgrGateWakeupClk          = CCM_TUPLE(CCGR1, CCM_CCGR1_CG9_SHIFT, CCM_CCGR1_CG9_MASK),
    ccmCcgrGateGptClk             = CCM_TUPLE(CCGR1, CCM_CCGR1_CG10_SHIFT, CCM_CCGR1_CG10_MASK),
    ccmCcgrGateGptSerialClk       = CCM_TUPLE(CCGR1, CCM_CCGR1_CG11_SHIFT, CCM_CCGR1_CG11_MASK),
    ccmCcgrGateGpuClk             = CCM_TUPLE(CCGR1, CCM_CCGR1_CG13_SHIFT, CCM_CCGR1_CG13_MASK),
    ccmCcgrGateOcramSClk          = CCM_TUPLE(CCGR1, CCM_CCGR1_CG14_SHIFT, CCM_CCGR1_CG14_MASK),
    ccmCcgrGateCanfdClk           = CCM_TUPLE(CCGR1, CCM_CCGR1_CG15_SHIFT, CCM_CCGR1_CG15_MASK),
    ccmCcgrGateCsiClk             = CCM_TUPLE(CCGR2, CCM_CCGR2_CG1_SHIFT, CCM_CCGR2_CG1_MASK),
    ccmCcgrGateI2c1Serialclk      = CCM_TUPLE(CCGR2, CCM_CCGR2_CG3_SHIFT, CCM_CCGR2_CG3_MASK),
    ccmCcgrGateI2c2Serialclk      = CCM_TUPLE(CCGR2, CCM_CCGR2_CG4_SHIFT, CCM_CCGR2_CG4_MASK),
    ccmCcgrGateI2c3Serialclk      = CCM_TUPLE(CCGR2, CCM_CCGR2_CG5_SHIFT, CCM_CCGR2_CG5_MASK),
    ccmCcgrGateIimClk             = CCM_TUPLE(CCGR2, CCM_CCGR2_CG6_SHIFT, CCM_CCGR2_CG6_MASK),
    ccmCcgrGateIomuxIptClkIo      = CCM_TUPLE(CCGR2, CCM_CCGR2_CG7_SHIFT, CCM_CCGR2_CG7_MASK),
    ccmCcgrGateIpmux1Clk          = CCM_TUPLE(CCGR2, CCM_CCGR2_CG8_SHIFT, CCM_CCGR2_CG8_MASK),
    ccmCcgrGateIpmux2Clk          = CCM_TUPLE(CCGR2, CCM_CCGR2_CG9_SHIFT, CCM_CCGR2_CG9_MASK),
    ccmCcgrGateIpmux3Clk          = CCM_TUPLE(CCGR2, CCM_CCGR2_CG10_SHIFT, CCM_CCGR2_CG10_MASK),
    ccmCcgrGateIpsyncIp2apbtTasc1 = CCM_TUPLE(CCGR2, CCM_CCGR2_CG11_SHIFT, CCM_CCGR2_CG11_MASK),
    ccmCcgrGateLcdClk             = CCM_TUPLE(CCGR2, CCM_CCGR2_CG14_SHIFT, CCM_CCGR2_CG14_MASK),
    ccmCcgrGatePxpClk             = CCM_TUPLE(CCGR2, CCM_CCGR2_CG15_SHIFT, CCM_CCGR2_CG15_MASK),
    ccmCcgrGateM4Clk              = CCM_TUPLE(CCGR3, CCM_CCGR3_CG1_SHIFT, CCM_CCGR3_CG1_MASK),
    ccmCcgrGateEnetClk            = CCM_TUPLE(CCGR3, CCM_CCGR3_CG2_SHIFT, CCM_CCGR3_CG2_MASK),
    ccmCcgrGateDispAxiClk         = CCM_TUPLE(CCGR3, CCM_CCGR3_CG3_SHIFT, CCM_CCGR3_CG3_MASK),
    ccmCcgrGateLcdif2PixClk       = CCM_TUPLE(CCGR3, CCM_CCGR3_CG4_SHIFT, CCM_CCGR3_CG4_MASK),
    ccmCcgrGateLcdif1PixClk       = CCM_TUPLE(CCGR3, CCM_CCGR3_CG5_SHIFT, CCM_CCGR3_CG5_MASK),
    ccmCcgrGateLdbDi0Clk          = CCM_TUPLE(CCGR3, CCM_CCGR3_CG6_SHIFT, CCM_CCGR3_CG6_MASK),
    ccmCcgrGateQspi1Clk           = CCM_TUPLE(CCGR3, CCM_CCGR3_CG7_SHIFT, CCM_CCGR3_CG7_MASK),
    ccmCcgrGateMlbClk             = CCM_TUPLE(CCGR3, CCM_CCGR3_CG9_SHIFT, CCM_CCGR3_CG9_MASK),
    ccmCcgrGateMmdcCoreAclkFastP0 = CCM_TUPLE(CCGR3, CCM_CCGR3_CG10_SHIFT, CCM_CCGR3_CG10_MASK),
    ccmCcgrGateMmdcCoreIpgClkP0   = CCM_TUPLE(CCGR3, CCM_CCGR3_CG12_SHIFT, CCM_CCGR3_CG12_MASK),
    ccmCcgrGateMmdcCoreIpgClkP1   = CCM_TUPLE(CCGR3, CCM_CCGR3_CG13_SHIFT, CCM_CCGR3_CG13_MASK),
    ccmCcgrGateOcramClk           = CCM_TUPLE(CCGR3, CCM_CCGR3_CG14_SHIFT, CCM_CCGR3_CG14_MASK),
    ccmCcgrGatePcieRoot           = CCM_TUPLE(CCGR4, CCM_CCGR4_CG0_SHIFT, CCM_CCGR4_CG0_MASK),
    ccmCcgrGateQspi2Clk           = CCM_TUPLE(CCGR4, CCM_CCGR4_CG5_SHIFT, CCM_CCGR4_CG5_MASK),
    ccmCcgrGatePl301Mx6qper1Bch   = CCM_TUPLE(CCGR4, CCM_CCGR4_CG6_SHIFT, CCM_CCGR4_CG6_MASK),
    ccmCcgrGatePl301Mx6qper2Main  = CCM_TUPLE(CCGR4, CCM_CCGR4_CG7_SHIFT, CCM_CCGR4_CG7_MASK),
    ccmCcgrGatePwm1Clk            = CCM_TUPLE(CCGR4, CCM_CCGR4_CG8_SHIFT, CCM_CCGR4_CG8_MASK),
    ccmCcgrGatePwm2Clk            = CCM_TUPLE(CCGR4, CCM_CCGR4_CG9_SHIFT, CCM_CCGR4_CG9_MASK),
    ccmCcgrGatePwm3Clk            = CCM_TUPLE(CCGR4, CCM_CCGR4_CG10_SHIFT, CCM_CCGR4_CG10_MASK),
    ccmCcgrGatePwm4Clk            = CCM_TUPLE(CCGR4, CCM_CCGR4_CG11_SHIFT, CCM_CCGR4_CG11_MASK),
    ccmCcgrGateRawnandUBchInptApb = CCM_TUPLE(CCGR4, CCM_CCGR4_CG12_SHIFT, CCM_CCGR4_CG12_MASK),
    ccmCcgrGateRawnandUGpmiBch    = CCM_TUPLE(CCGR4, CCM_CCGR4_CG13_SHIFT, CCM_CCGR4_CG13_MASK),
    ccmCcgrGateRawnandUGpmiGpmiIo = CCM_TUPLE(CCGR4, CCM_CCGR4_CG14_SHIFT, CCM_CCGR4_CG14_MASK),
    ccmCcgrGateRawnandUGpmiInpApb = CCM_TUPLE(CCGR4, CCM_CCGR4_CG15_SHIFT, CCM_CCGR4_CG15_MASK),
    ccmCcgrGateRomClk             = CCM_TUPLE(CCGR5, CCM_CCGR5_CG0_SHIFT, CCM_CCGR5_CG0_MASK),
    ccmCcgrGateSdmaClk            = CCM_TUPLE(CCGR5, CCM_CCGR5_CG3_SHIFT, CCM_CCGR5_CG3_MASK),
    ccmCcgrGateSpbaClk            = CCM_TUPLE(CCGR5, CCM_CCGR5_CG6_SHIFT, CCM_CCGR5_CG6_MASK),
    ccmCcgrGateSpdifAudioClk      = CCM_TUPLE(CCGR5, CCM_CCGR5_CG7_SHIFT, CCM_CCGR5_CG7_MASK),
    ccmCcgrGateSsi1Clk            = CCM_TUPLE(CCGR5, CCM_CCGR5_CG9_SHIFT, CCM_CCGR5_CG9_MASK),
    ccmCcgrGateSsi2Clk            = CCM_TUPLE(CCGR5, CCM_CCGR5_CG10_SHIFT, CCM_CCGR5_CG10_MASK),
    ccmCcgrGateSsi3Clk            = CCM_TUPLE(CCGR5, CCM_CCGR5_CG11_SHIFT, CCM_CCGR5_CG11_MASK),
    ccmCcgrGateUartClk            = CCM_TUPLE(CCGR5, CCM_CCGR5_CG12_SHIFT, CCM_CCGR5_CG12_MASK),
    ccmCcgrGateUartSerialClk      = CCM_TUPLE(CCGR5, CCM_CCGR5_CG13_SHIFT, CCM_CCGR5_CG13_MASK),
    ccmCcgrGateSai1Clk            = CCM_TUPLE(CCGR5, CCM_CCGR5_CG14_SHIFT, CCM_CCGR5_CG14_MASK),
    ccmCcgrGateSai2Clk            = CCM_TUPLE(CCGR5, CCM_CCGR5_CG15_SHIFT, CCM_CCGR5_CG15_MASK),
    ccmCcgrGateUsboh3Clk          = CCM_TUPLE(CCGR6, CCM_CCGR6_CG0_SHIFT, CCM_CCGR6_CG0_MASK),
    ccmCcgrGateUsdhc1Clk          = CCM_TUPLE(CCGR6, CCM_CCGR6_CG1_SHIFT, CCM_CCGR6_CG1_MASK),
    ccmCcgrGateUsdhc2Clk          = CCM_TUPLE(CCGR6, CCM_CCGR6_CG2_SHIFT, CCM_CCGR6_CG2_MASK),
    ccmCcgrGateUsdhc3Clk          = CCM_TUPLE(CCGR6, CCM_CCGR6_CG3_SHIFT, CCM_CCGR6_CG3_MASK),
    ccmCcgrGateUsdhc4Clk          = CCM_TUPLE(CCGR6, CCM_CCGR6_CG4_SHIFT, CCM_CCGR6_CG4_MASK),
    ccmCcgrGateEimSlowClk         = CCM_TUPLE(CCGR6, CCM_CCGR6_CG5_SHIFT, CCM_CCGR6_CG5_MASK),
    ccmCcgrGatePwm8Clk            = CCM_TUPLE(CCGR6, CCM_CCGR6_CG8_SHIFT, CCM_CCGR6_CG8_MASK),
    ccmCcgrGateVadcClk            = CCM_TUPLE(CCGR6, CCM_CCGR6_CG10_SHIFT, CCM_CCGR6_CG10_MASK),
    ccmCcgrGateGisClk             = CCM_TUPLE(CCGR6, CCM_CCGR6_CG11_SHIFT, CCM_CCGR6_CG11_MASK),
    ccmCcgrGateI2c4SerialClk      = CCM_TUPLE(CCGR6, CCM_CCGR6_CG12_SHIFT, CCM_CCGR6_CG12_MASK),
    ccmCcgrGatePwm5Clk            = CCM_TUPLE(CCGR6, CCM_CCGR6_CG13_SHIFT, CCM_CCGR6_CG13_MASK),
    ccmCcgrGatePwm6Clk            = CCM_TUPLE(CCGR6, CCM_CCGR6_CG14_SHIFT, CCM_CCGR6_CG14_MASK),
    ccmCcgrGatePwm7Clk            = CCM_TUPLE(CCGR6, CCM_CCGR6_CG15_SHIFT, CCM_CCGR6_CG15_MASK)
};

/*!
 * @brief CCM gate control value
 */
enum _ccm_gate_value {
    ccmClockNotNeeded = 0U, /*!< Clock always disabled.*/
    ccmClockNeededRun = 1U, /*!< Clock enabled when CPU is running.*/
    ccmClockNeededAll = 3U  /*!< Clock always enabled.*/
};

/*!
 * @brief CCM overrided clock enable signal from module.
 */
enum _ccm_overrided_enable_signal {
    ccmOverridedSignalFromGpt     = 1U << 5,  /*!< Overide clock enable signal from GPT.*/
    ccmOverridedSignalFromEpit    = 1U << 6,  /*!< Overide clock enable signal from EPIT.*/
    ccmOverridedSignalFromUsdhc   = 1U << 7,  /*!< Overide clock enable signal from USDHC.*/
    ccmOverridedSignalFromGpu     = 1U << 10, /*!< Overide clock enable signal from GPU.*/
    ccmOverridedSignalFromCan2Cpi = 1U << 28, /*!< Overide clock enable signal from CAN2.*/
    ccmOverridedSignalFromCan1Cpi = 1U << 30  /*!< Overide clock enable signal from CAN1.*/
};

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name CCM Root Clock Setting
 * @{
 */

/*!
 * @brief Set clock root mux.
 * User maybe need to set more than one mux node according to the clock tree
 * description on the reference manual.
 *
 * @param base CCM base pointer.
 * @param ccmRootClk Root clock control (see @ref _ccm_root_clock_control enumeration).
 * @param mux Root mux value (see @ref _ccm_rootmux_xxx enumeration).
 */
static inline void CCM_SetRootMux(CCM_Type * base, uint32_t ccmRootClk, uint32_t mux)
{
    CCM_TUPLE_REG(base, ccmRootClk) = (CCM_TUPLE_REG(base, ccmRootClk) & (~CCM_TUPLE_MASK(ccmRootClk))) |
                                      (((uint32_t)((mux) << CCM_TUPLE_SHIFT(ccmRootClk))) & CCM_TUPLE_MASK(ccmRootClk));
}

/*!
 * @brief Get clock root mux.
 * In order to get the clock source of root, user maybe need to get more than one
 * node's mux value to obtain the final clock source of root.
 *
 * @param base CCM base pointer.
 * @param ccmRootClk Root clock control (see @ref _ccm_root_clock_control enumeration).
 * @return Root mux value (see @ref _ccm_rootmux_xxx enumeration).
 */
static inline uint32_t CCM_GetRootMux(CCM_Type * base, uint32_t ccmRootClk)
{
    return (CCM_TUPLE_REG(base, ccmRootClk) & CCM_TUPLE_MASK(ccmRootClk)) >> CCM_TUPLE_SHIFT(ccmRootClk);
}

/*!
 * @brief Set root clock divider.
 * User should set the dividers carefully according to the clock tree on
 * the reference manual. Take care of that the setting of one divider value
 * may affect several clock root.
 *
 * @param base CCM base pointer.
 * @param ccmRootDiv Root divider control (see @ref _ccm_root_div_control enumeration)
 * @param div Divider value (divider = div + 1).
 */
static inline void CCM_SetRootDivider(CCM_Type * base, uint32_t ccmRootDiv, uint32_t div)
{
    CCM_TUPLE_REG(base, ccmRootDiv) = (CCM_TUPLE_REG(base, ccmRootDiv) & (~CCM_TUPLE_MASK(ccmRootDiv))) |
                                      (((uint32_t)((div) << CCM_TUPLE_SHIFT(ccmRootDiv))) & CCM_TUPLE_MASK(ccmRootDiv));
}

/*!
 * @brief Get root clock divider.
 * In order to get divider value of clock root, user shouold get specific
 * divider value according to the clock tree description on reference manual.
 * Then calculate the root clock with those divider value.
 *
 * @param base CCM base pointer.
 * @param ccmRootDiv Root control (see @ref _ccm_root_div_control enumeration).
 * @param div Pointer to divider value store address.
 * @return Root divider value.
 */
static inline uint32_t CCM_GetRootDivider(CCM_Type * base, uint32_t ccmRootDiv)
{
    return (CCM_TUPLE_REG(base, ccmRootDiv) & CCM_TUPLE_MASK(ccmRootDiv)) >> CCM_TUPLE_SHIFT(ccmRootDiv);
}

/*!
 * @brief Set handshake mask of MMDC module.
 * During divider ratio mmdc_axi_podf change or sync mux periph2_clk_sel
 * change (but not jtag) or SRC request during warm reset, mask handshake with mmdc module.
 *
 * @param base CCM base pointer.
 * @param mask True: mask handshake with MMDC; False: allow handshake with MMDC.
 */
void CCM_SetMmdcHandshakeMask(CCM_Type * base, bool mask);

/*@}*/

/*!
 * @name CCM Gate Control
 * @{
 */

/*!
 * @brief Set CCGR gate control for each module
 * User should set specific gate for each module according to the description
 * of the table of system clocks, gating and override in CCM chapter of
 * reference manual. Take care of that one module may need to set more than
 * one clock gate.
 *
 * @param base CCM base pointer.
 * @param ccmGate Gate control for each module (see @ref _ccm_ccgr_gate enumeration).
 * @param control Gate control value (see @ref _ccm_gate_value).
 */
static inline void CCM_ControlGate(CCM_Type * base, uint32_t ccmGate, uint32_t control)
{
    CCM_TUPLE_REG(base, ccmGate) = (CCM_TUPLE_REG(base, ccmGate) & (~CCM_TUPLE_MASK(ccmGate))) |
                                      (((uint32_t)((control) << CCM_TUPLE_SHIFT(ccmGate))) & CCM_TUPLE_MASK(ccmGate));
}

/*!
 * @brief Set override or do not override clock enable signal from module.
 * This is applicable only for modules whose clock enable signals are used.
 *
 * @param base CCM base pointer.
 * @param signal Overrided enable signal from module (see @ref _ccm_overrided_enable_signal enumeration).
 * @param control Override / Do not override clock enable signal from module.
 *                - true: override clock enable signal.
 *                - false: Do not override clock enable signal.
 */
void CCM_SetClockEnableSignalOverrided(CCM_Type * base, uint32_t signal, bool control);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __CCM_IMX6SX_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/
