/* Copyright (c) 2012, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef SITAR_CODEC_DIGITAL_H
#define SITAR_CODEC_DIGITAL_H

#define SITAR_A_PIN_CTL_OE0			(0x10)
#define SITAR_A_PIN_CTL_OE0__POR			(0x00000000)
#define SITAR_A_PIN_CTL_OE1			(0x11)
#define SITAR_A_PIN_CTL_OE1__POR			(0x00000000)
#define SITAR_A_PIN_CTL_DATA0			(0x12)
#define SITAR_A_PIN_CTL_DATA0__POR			(0x00000000)
#define SITAR_A_PIN_CTL_DATA1			(0x13)
#define SITAR_A_PIN_CTL_DATA1__POR			(0x00000000)
#define SITAR_A_HDRIVE_GENERIC			(0x18)
#define SITAR_A_HDRIVE_GENERIC__POR			(0x00000000)
#define SITAR_A_HDRIVE_OVERRIDE			(0x19)
#define SITAR_A_HDRIVE_OVERRIDE__POR			(0x00000008)
#define SITAR_A_ANA_CSR_WAIT_STATE			(0x20)
#define SITAR_A_ANA_CSR_WAIT_STATE__POR			(0x00000044)
#define SITAR_A_PROCESS_MONITOR_CTL0			(0x40)
#define SITAR_A_PROCESS_MONITOR_CTL0__POR			(0x00000080)
#define SITAR_A_PROCESS_MONITOR_CTL1			(0x41)
#define SITAR_A_PROCESS_MONITOR_CTL1__POR			(0x00000000)
#define SITAR_A_PROCESS_MONITOR_CTL2			(0x42)
#define SITAR_A_PROCESS_MONITOR_CTL2__POR			(0x00000000)
#define SITAR_A_PROCESS_MONITOR_CTL3			(0x43)
#define SITAR_A_PROCESS_MONITOR_CTL3__POR			(0x00000001)
#define SITAR_A_QFUSE_CTL			(0x48)
#define SITAR_A_QFUSE_CTL__POR			(0x00000000)
#define SITAR_A_QFUSE_STATUS			(0x49)
#define SITAR_A_QFUSE_STATUS__POR			(0x00000000)
#define SITAR_A_QFUSE_DATA_OUT0			(0x4A)
#define SITAR_A_QFUSE_DATA_OUT0__POR			(0x00000000)
#define SITAR_A_QFUSE_DATA_OUT1			(0x4B)
#define SITAR_A_QFUSE_DATA_OUT1__POR			(0x00000000)
#define SITAR_A_QFUSE_DATA_OUT2			(0x4C)
#define SITAR_A_QFUSE_DATA_OUT2__POR			(0x00000000)
#define SITAR_A_QFUSE_DATA_OUT3			(0x4D)
#define SITAR_A_QFUSE_DATA_OUT3__POR			(0x00000000)
#define SITAR_A_QFUSE_DATA_OUT4			(0x4E)
#define SITAR_A_QFUSE_DATA_OUT4__POR			(0x00000000)
#define SITAR_A_QFUSE_DATA_OUT5			(0x4F)
#define SITAR_A_QFUSE_DATA_OUT5__POR			(0x00000000)
#define SITAR_A_QFUSE_DATA_OUT6			(0x50)
#define SITAR_A_QFUSE_DATA_OUT6__POR			(0x00000000)
#define SITAR_A_QFUSE_DATA_OUT7			(0x51)
#define SITAR_A_QFUSE_DATA_OUT7__POR			(0x00000000)
#define SITAR_A_CDC_CTL			(0x80)
#define SITAR_A_CDC_CTL__POR			(0x00000000)
#define SITAR_A_LEAKAGE_CTL			(0x88)
#define SITAR_A_LEAKAGE_CTL__POR			(0x00000004)
#define SITAR_A_INTR_MODE			(0x90)
#define SITAR_A_INTR_MODE__POR			(0x00000000)
#define SITAR_A_INTR_MASK0			(0x94)
#define SITAR_A_INTR_MASK0__POR			(0x000000ff)
#define SITAR_A_INTR_MASK1			(0x95)
#define SITAR_A_INTR_MASK1__POR			(0x000000ff)
#define SITAR_A_INTR_MASK2			(0x96)
#define SITAR_A_INTR_MASK2__POR			(0x000000ff)
#define SITAR_A_INTR_STATUS0			(0x98)
#define SITAR_A_INTR_STATUS0__POR			(0x00000000)
#define SITAR_A_INTR_STATUS1			(0x99)
#define SITAR_A_INTR_STATUS1__POR			(0x00000000)
#define SITAR_A_INTR_STATUS2			(0x9A)
#define SITAR_A_INTR_STATUS2__POR			(0x00000000)
#define SITAR_A_INTR_CLEAR0			(0x9C)
#define SITAR_A_INTR_CLEAR0__POR			(0x00000000)
#define SITAR_A_INTR_CLEAR1			(0x9D)
#define SITAR_A_INTR_CLEAR1__POR			(0x00000000)
#define SITAR_A_INTR_CLEAR2			(0x9E)
#define SITAR_A_INTR_CLEAR2__POR			(0x00000000)
#define SITAR_A_INTR_LEVEL0			(0xA0)
#define SITAR_A_INTR_LEVEL0__POR			(0x00000001)
#define SITAR_A_INTR_LEVEL1			(0xA1)
#define SITAR_A_INTR_LEVEL1__POR			(0x00000000)
#define SITAR_A_INTR_LEVEL2			(0xA2)
#define SITAR_A_INTR_LEVEL2__POR			(0x00000000)
#define SITAR_A_INTR_TEST0			(0xA4)
#define SITAR_A_INTR_TEST0__POR			(0x00000000)
#define SITAR_A_INTR_TEST1			(0xA5)
#define SITAR_A_INTR_TEST1__POR			(0x00000000)
#define SITAR_A_INTR_TEST2			(0xA6)
#define SITAR_A_INTR_TEST2__POR			(0x00000000)
#define SITAR_A_INTR_SET0			(0xA8)
#define SITAR_A_INTR_SET0__POR			(0x00000000)
#define SITAR_A_INTR_SET1			(0xA9)
#define SITAR_A_INTR_SET1__POR			(0x00000000)
#define SITAR_A_INTR_SET2			(0xAA)
#define SITAR_A_INTR_SET2__POR			(0x00000000)
#define SITAR_A_CDC_TX_I2S_SCK_MODE			(0xC0)
#define SITAR_A_CDC_TX_I2S_SCK_MODE__POR			(0x00000000)
#define SITAR_A_CDC_TX_I2S_WS_MODE			(0xC1)
#define SITAR_A_CDC_TX_I2S_WS_MODE__POR			(0x00000000)
#define SITAR_A_CDC_DMIC_DATA0_MODE			(0xC4)
#define SITAR_A_CDC_DMIC_DATA0_MODE__POR			(0x00000000)
#define SITAR_A_CDC_DMIC_CLK0_MODE			(0xC5)
#define SITAR_A_CDC_DMIC_CLK0_MODE__POR			(0x00000000)
#define SITAR_A_CDC_DMIC_DATA1_MODE			(0xC6)
#define SITAR_A_CDC_DMIC_DATA1_MODE__POR			(0x00000000)
#define SITAR_A_CDC_DMIC_CLK1_MODE			(0xC7)
#define SITAR_A_CDC_DMIC_CLK1_MODE__POR			(0x00000000)
#define SITAR_A_CDC_TX_I2S_SD0_MODE			(0xC8)
#define SITAR_A_CDC_TX_I2S_SD0_MODE__POR			(0x00000000)
#define SITAR_A_CDC_INTR_MODE			(0xC9)
#define SITAR_A_CDC_INTR_MODE__POR			(0x00000000)
#define SITAR_A_CDC_RX_I2S_SD0_MODE			(0xCA)
#define SITAR_A_CDC_RX_I2S_SD0_MODE__POR			(0x00000000)
#define SITAR_A_CDC_RX_I2S_SD1_MODE			(0xCB)
#define SITAR_A_CDC_RX_I2S_SD1_MODE__POR			(0x00000000)
#define SITAR_A_BIAS_REF_CTL			(0x100)
#define SITAR_A_BIAS_REF_CTL__POR			(0x0000001c)
#define SITAR_A_BIAS_CENTRAL_BG_CTL			(0x101)
#define SITAR_A_BIAS_CENTRAL_BG_CTL__POR			(0x00000050)
#define SITAR_A_BIAS_PRECHRG_CTL			(0x102)
#define SITAR_A_BIAS_PRECHRG_CTL__POR			(0x00000007)
#define SITAR_A_BIAS_CURR_CTL_1			(0x103)
#define SITAR_A_BIAS_CURR_CTL_1__POR			(0x00000052)
#define SITAR_A_BIAS_CURR_CTL_2			(0x104)
#define SITAR_A_BIAS_CURR_CTL_2__POR			(0x00000000)
#define SITAR_A_BIAS_OSC_BG_CTL			(0x105)
#define SITAR_A_BIAS_OSC_BG_CTL__POR			(0x00000016)
#define SITAR_A_CLK_BUFF_EN1			(0x108)
#define SITAR_A_CLK_BUFF_EN1__POR			(0x00000004)
#define SITAR_A_CLK_BUFF_EN2			(0x109)
#define SITAR_A_CLK_BUFF_EN2__POR			(0x00000002)
#define SITAR_A_LDO_H_MODE_1			(0x110)
#define SITAR_A_LDO_H_MODE_1__POR			(0x00000065)
#define SITAR_A_LDO_H_MODE_2			(0x111)
#define SITAR_A_LDO_H_MODE_2__POR			(0x000000a8)
#define SITAR_A_LDO_H_LOOP_CTL			(0x112)
#define SITAR_A_LDO_H_LOOP_CTL__POR			(0x0000006b)
#define SITAR_A_LDO_H_COMP_1			(0x113)
#define SITAR_A_LDO_H_COMP_1__POR			(0x00000084)
#define SITAR_A_LDO_H_COMP_2			(0x114)
#define SITAR_A_LDO_H_COMP_2__POR			(0x000000e0)
#define SITAR_A_LDO_H_BIAS_1			(0x115)
#define SITAR_A_LDO_H_BIAS_1__POR			(0x0000006d)
#define SITAR_A_LDO_H_BIAS_2			(0x116)
#define SITAR_A_LDO_H_BIAS_2__POR			(0x000000a5)
#define SITAR_A_LDO_H_BIAS_3			(0x117)
#define SITAR_A_LDO_H_BIAS_3__POR			(0x00000060)
#define SITAR_A_MICB_CFILT_1_CTL			(0x128)
#define SITAR_A_MICB_CFILT_1_CTL__POR			(0x00000040)
#define SITAR_A_MICB_CFILT_1_VAL			(0x129)
#define SITAR_A_MICB_CFILT_1_VAL__POR			(0x00000080)
#define SITAR_A_MICB_CFILT_1_PRECHRG			(0x12A)
#define SITAR_A_MICB_CFILT_1_PRECHRG__POR			(0x00000038)
#define SITAR_A_MICB_1_CTL			(0x12B)
#define SITAR_A_MICB_1_CTL__POR			(0x00000016)
#define SITAR_A_MICB_1_INT_RBIAS			(0x12C)
#define SITAR_A_MICB_1_INT_RBIAS__POR			(0x00000024)
#define SITAR_A_MICB_1_MBHC			(0x12D)
#define SITAR_A_MICB_1_MBHC__POR			(0x00000001)
#define SITAR_A_MICB_CFILT_2_CTL			(0x12E)
#define SITAR_A_MICB_CFILT_2_CTL__POR			(0x00000040)
#define SITAR_A_MICB_CFILT_2_VAL			(0x12F)
#define SITAR_A_MICB_CFILT_2_VAL__POR			(0x00000080)
#define SITAR_A_MICB_CFILT_2_PRECHRG			(0x130)
#define SITAR_A_MICB_CFILT_2_PRECHRG__POR			(0x00000038)
#define SITAR_A_MICB_2_CTL			(0x131)
#define SITAR_A_MICB_2_CTL__POR			(0x00000016)
#define SITAR_A_MICB_2_INT_RBIAS			(0x132)
#define SITAR_A_MICB_2_INT_RBIAS__POR			(0x00000024)
#define SITAR_A_MICB_2_MBHC			(0x133)
#define SITAR_A_MICB_2_MBHC__POR			(0x00000002)
#define SITAR_A_TX_COM_BIAS			(0x14C)
#define SITAR_A_TX_COM_BIAS__POR			(0x000000e0)
#define SITAR_A_MBHC_SCALING_MUX_1			(0x14E)
#define SITAR_A_MBHC_SCALING_MUX_1__POR			(0x00000000)
#define SITAR_A_MBHC_SCALING_MUX_2			(0x14F)
#define SITAR_A_MBHC_SCALING_MUX_2__POR			(0x00000080)
#define SITAR_A_TX_SUP_SWITCH_CTRL_1			(0x151)
#define SITAR_A_TX_SUP_SWITCH_CTRL_1__POR			(0x00000000)
#define SITAR_A_TX_SUP_SWITCH_CTRL_2			(0x152)
#define SITAR_A_TX_SUP_SWITCH_CTRL_2__POR			(0x00000080)
#define SITAR_A_TX_1_2_EN			(0x153)
#define SITAR_A_TX_1_2_EN__POR			(0x00000000)
#define SITAR_A_TX_1_2_TEST_EN			(0x154)
#define SITAR_A_TX_1_2_TEST_EN__POR			(0x000000cc)
#define SITAR_A_TX_1_2_ADC_CH1			(0x155)
#define SITAR_A_TX_1_2_ADC_CH1__POR			(0x00000044)
#define SITAR_A_TX_1_2_ADC_CH2			(0x156)
#define SITAR_A_TX_1_2_ADC_CH2__POR			(0x00000044)
#define SITAR_A_TX_1_2_ATEST_REFCTRL			(0x157)
#define SITAR_A_TX_1_2_ATEST_REFCTRL__POR			(0x00000000)
#define SITAR_A_TX_1_2_TEST_CTL			(0x158)
#define SITAR_A_TX_1_2_TEST_CTL__POR			(0x00000038)
#define SITAR_A_TX_1_2_TEST_BLOCK_EN			(0x159)
#define SITAR_A_TX_1_2_TEST_BLOCK_EN__POR			(0x000000fc)
#define SITAR_A_TX_1_2_TXFE_CLKDIV			(0x15A)
#define SITAR_A_TX_1_2_TXFE_CLKDIV__POR			(0x000000ee)
#define SITAR_A_TX_1_2_SAR_ERR_CH1			(0x15B)
#define SITAR_A_TX_1_2_SAR_ERR_CH1__POR			(0x00000000)
#define SITAR_A_TX_1_2_SAR_ERR_CH2			(0x15C)
#define SITAR_A_TX_1_2_SAR_ERR_CH2__POR			(0x00000000)
#define SITAR_A_TX_3_EN			(0x15D)
#define SITAR_A_TX_3_EN__POR			(0x00000000)
#define SITAR_A_TX_3_TEST_EN			(0x15E)
#define SITAR_A_TX_3_TEST_EN__POR			(0x000000cc)
#define SITAR_A_TX_3_ADC			(0x15F)
#define SITAR_A_TX_3_ADC__POR			(0x00000044)
#define SITAR_A_TX_3_MBHC_ATEST_REFCTRL			(0x161)
#define SITAR_A_TX_3_MBHC_ATEST_REFCTRL__POR			(0x00000000)
#define SITAR_A_TX_3_TEST_CTL			(0x162)
#define SITAR_A_TX_3_TEST_CTL__POR			(0x00000038)
#define SITAR_A_TX_3_TEST_BLOCK_EN			(0x163)
#define SITAR_A_TX_3_TEST_BLOCK_EN__POR			(0x000000fc)
#define SITAR_A_TX_3_TXFE_CKDIV			(0x164)
#define SITAR_A_TX_3_TXFE_CKDIV__POR			(0x000000ee)
#define SITAR_A_TX_3_SAR_ERR			(0x165)
#define SITAR_A_TX_3_SAR_ERR__POR			(0x00000000)
#define SITAR_A_TX_4_MBHC_EN			(0x171)
#define SITAR_A_TX_4_MBHC_EN__POR			(0x0000000c)
#define SITAR_A_TX_4_MBHC_ADC			(0x173)
#define SITAR_A_TX_4_MBHC_ADC__POR			(0x00000044)
#define SITAR_A_TX_4_MBHC_TEST_CTL			(0x174)
#define SITAR_A_TX_4_MBHC_TEST_CTL__POR			(0x00000038)
#define SITAR_A_TX_4_MBHC_SAR_ERR			(0x175)
#define SITAR_A_TX_4_MBHC_SAR_ERR__POR			(0x00000000)
#define SITAR_A_TX_4_TXFE_CLKDIV			(0x176)
#define SITAR_A_TX_4_TXFE_CLKDIV__POR			(0x0000001c)
#define SITAR_A_AUX_COM_CTL			(0x180)
#define SITAR_A_AUX_COM_CTL__POR			(0x00000034)
#define SITAR_A_AUX_COM_ATEST			(0x181)
#define SITAR_A_AUX_COM_ATEST__POR			(0x00000000)
#define SITAR_A_AUX_L_EN			(0x182)
#define SITAR_A_AUX_L_EN__POR			(0x00000000)
#define SITAR_A_AUX_L_GAIN			(0x183)
#define SITAR_A_AUX_L_GAIN__POR			(0x0000001f)
#define SITAR_A_AUX_L_PA_CONN			(0x184)
#define SITAR_A_AUX_L_PA_CONN__POR			(0x00000000)
#define SITAR_A_AUX_L_PA_CONN_INV			(0x185)
#define SITAR_A_AUX_L_PA_CONN_INV__POR			(0x00000000)
#define SITAR_A_AUX_R_EN			(0x186)
#define SITAR_A_AUX_R_EN__POR			(0x00000000)
#define SITAR_A_AUX_R_GAIN			(0x187)
#define SITAR_A_AUX_R_GAIN__POR			(0x0000001f)
#define SITAR_A_AUX_R_PA_CONN			(0x188)
#define SITAR_A_AUX_R_PA_CONN__POR			(0x00000000)
#define SITAR_A_AUX_R_PA_CONN_INV			(0x189)
#define SITAR_A_AUX_R_PA_CONN_INV__POR			(0x00000000)
#define SITAR_A_CP_EN			(0x192)
#define SITAR_A_CP_EN__POR			(0x000000e6)
#define SITAR_A_CP_CLK			(0x193)
#define SITAR_A_CP_CLK__POR			(0x00000029)
#define SITAR_A_CP_STATIC			(0x194)
#define SITAR_A_CP_STATIC__POR			(0x00000010)
#define SITAR_A_CP_DCC1			(0x195)
#define SITAR_A_CP_DCC1__POR			(0x00000052)
#define SITAR_A_CP_DCC3			(0x196)
#define SITAR_A_CP_DCC3__POR			(0x00000001)
#define SITAR_A_CP_ATEST			(0x197)
#define SITAR_A_CP_ATEST__POR			(0x00000000)
#define SITAR_A_CP_DTEST			(0x198)
#define SITAR_A_CP_DTEST__POR			(0x00000000)
#define SITAR_A_RX_COM_TIMER_DIV			(0x19E)
#define SITAR_A_RX_COM_TIMER_DIV__POR			(0x000000e8)
#define SITAR_A_RX_COM_OCP_CTL			(0x19F)
#define SITAR_A_RX_COM_OCP_CTL__POR			(0x0000001f)
#define SITAR_A_RX_COM_OCP_COUNT			(0x1A0)
#define SITAR_A_RX_COM_OCP_COUNT__POR			(0x00000077)
#define SITAR_A_RX_COM_DAC_CTL			(0x1A1)
#define SITAR_A_RX_COM_DAC_CTL__POR			(0x00000000)
#define SITAR_A_RX_COM_BIAS			(0x1A2)
#define SITAR_A_RX_COM_BIAS__POR			(0x00000000)
#define SITAR_A_RX_HPH_BIAS_PA			(0x1A6)
#define SITAR_A_RX_HPH_BIAS_PA__POR			(0x00000057)
#define SITAR_A_RX_HPH_BIAS_LDO			(0x1A7)
#define SITAR_A_RX_HPH_BIAS_LDO__POR			(0x00000056)
#define SITAR_A_RX_HPH_BIAS_CNP			(0x1A8)
#define SITAR_A_RX_HPH_BIAS_CNP__POR			(0x0000008a)
#define SITAR_A_RX_HPH_BIAS_WG			(0x1A9)
#define SITAR_A_RX_HPH_BIAS_WG__POR			(0x00000060)
#define SITAR_A_RX_HPH_OCP_CTL			(0x1AA)
#define SITAR_A_RX_HPH_OCP_CTL__POR			(0x000000e8)
#define SITAR_A_RX_HPH_CNP_EN			(0x1AB)
#define SITAR_A_RX_HPH_CNP_EN__POR			(0x00000080)
#define SITAR_A_RX_HPH_CNP_WG_CTL			(0x1AC)
#define SITAR_A_RX_HPH_CNP_WG_CTL__POR			(0x000000dc)
#define SITAR_A_RX_HPH_CNP_WG_TIME			(0x1AD)
#define SITAR_A_RX_HPH_CNP_WG_TIME__POR			(0x00000028)
#define SITAR_A_RX_HPH_L_GAIN			(0x1AE)
#define SITAR_A_RX_HPH_L_GAIN__POR			(0x00000000)
#define SITAR_A_RX_HPH_L_TEST			(0x1AF)
#define SITAR_A_RX_HPH_L_TEST__POR			(0x00000001)
#define SITAR_A_RX_HPH_L_PA_CTL			(0x1B0)
#define SITAR_A_RX_HPH_L_PA_CTL__POR			(0x00000040)
#define SITAR_A_RX_HPH_L_DAC_CTL			(0x1B1)
#define SITAR_A_RX_HPH_L_DAC_CTL__POR			(0x00000000)
#define SITAR_A_RX_HPH_L_ATEST			(0x1B2)
#define SITAR_A_RX_HPH_L_ATEST__POR			(0x00000000)
#define SITAR_A_RX_HPH_L_STATUS			(0x1B3)
#define SITAR_A_RX_HPH_L_STATUS__POR			(0x00000004)
#define SITAR_A_RX_HPH_R_GAIN			(0x1B4)
#define SITAR_A_RX_HPH_R_GAIN__POR			(0x00000000)
#define SITAR_A_RX_HPH_R_TEST			(0x1B5)
#define SITAR_A_RX_HPH_R_TEST__POR			(0x00000001)
#define SITAR_A_RX_HPH_R_PA_CTL			(0x1B6)
#define SITAR_A_RX_HPH_R_PA_CTL__POR			(0x00000040)
#define SITAR_A_RX_HPH_R_DAC_CTL			(0x1B7)
#define SITAR_A_RX_HPH_R_DAC_CTL__POR			(0x00000000)
#define SITAR_A_RX_HPH_R_ATEST			(0x1B8)
#define SITAR_A_RX_HPH_R_ATEST__POR			(0x00000000)
#define SITAR_A_RX_HPH_R_STATUS			(0x1B9)
#define SITAR_A_RX_HPH_R_STATUS__POR			(0x00000004)
#define SITAR_A_RX_EAR_BIAS_PA			(0x1BA)
#define SITAR_A_RX_EAR_BIAS_PA__POR			(0x000000a6)
#define SITAR_A_RX_EAR_BIAS_CMBUFF			(0x1BB)
#define SITAR_A_RX_EAR_BIAS_CMBUFF__POR			(0x000000a0)
#define SITAR_A_RX_EAR_EN			(0x1BC)
#define SITAR_A_RX_EAR_EN__POR			(0x00000000)
#define SITAR_A_RX_EAR_GAIN			(0x1BD)
#define SITAR_A_RX_EAR_GAIN__POR			(0x00000002)
#define SITAR_A_RX_EAR_CMBUFF			(0x1BE)
#define SITAR_A_RX_EAR_CMBUFF__POR			(0x00000004)
#define SITAR_A_RX_EAR_ICTL			(0x1BF)
#define SITAR_A_RX_EAR_ICTL__POR			(0x00000040)
#define SITAR_A_RX_EAR_CCOMP			(0x1C0)
#define SITAR_A_RX_EAR_CCOMP__POR			(0x00000008)
#define SITAR_A_RX_EAR_VCM			(0x1C1)
#define SITAR_A_RX_EAR_VCM__POR			(0x00000003)
#define SITAR_A_RX_EAR_CNP			(0x1C2)
#define SITAR_A_RX_EAR_CNP__POR			(0x000000f2)
#define SITAR_A_RX_EAR_ATEST			(0x1C3)
#define SITAR_A_RX_EAR_ATEST__POR			(0x00000000)
#define SITAR_A_RX_EAR_STATUS			(0x1C5)
#define SITAR_A_RX_EAR_STATUS__POR			(0x00000004)
#define SITAR_A_RX_LINE_BIAS_PA			(0x1C6)
#define SITAR_A_RX_LINE_BIAS_PA__POR			(0x000000aa)
#define SITAR_A_RX_LINE_BIAS_LDO			(0x1C7)
#define SITAR_A_RX_LINE_BIAS_LDO__POR			(0x00000086)
#define SITAR_A_RX_LINE_BIAS_CNP1			(0x1C8)
#define SITAR_A_RX_LINE_BIAS_CNP1__POR			(0x00000060)
#define SITAR_A_RX_LINE_COM			(0x1C9)
#define SITAR_A_RX_LINE_COM__POR			(0x00000000)
#define SITAR_A_RX_LINE_CNP_EN			(0x1CA)
#define SITAR_A_RX_LINE_CNP_EN__POR			(0x00000080)
#define SITAR_A_RX_LINE_CNP_WG_CTL			(0x1CB)
#define SITAR_A_RX_LINE_CNP_WG_CTL__POR			(0x000000dc)
#define SITAR_A_RX_LINE_CNP_WG_TIME			(0x1CC)
#define SITAR_A_RX_LINE_CNP_WG_TIME__POR			(0x00000028)
#define SITAR_A_RX_LINE_1_GAIN			(0x1CD)
#define SITAR_A_RX_LINE_1_GAIN__POR			(0x00000000)
#define SITAR_A_RX_LINE_1_TEST			(0x1CE)
#define SITAR_A_RX_LINE_1_TEST__POR			(0x00000001)
#define SITAR_A_RX_LINE_1_DAC_CTL			(0x1CF)
#define SITAR_A_RX_LINE_1_DAC_CTL__POR			(0x00000000)
#define SITAR_A_RX_LINE_1_STATUS			(0x1D0)
#define SITAR_A_RX_LINE_1_STATUS__POR			(0x00000004)
#define SITAR_A_RX_LINE_2_GAIN			(0x1D1)
#define SITAR_A_RX_LINE_2_GAIN__POR			(0x00000000)
#define SITAR_A_RX_LINE_2_TEST			(0x1D2)
#define SITAR_A_RX_LINE_2_TEST__POR			(0x00000001)
#define SITAR_A_RX_LINE_2_DAC_CTL			(0x1D3)
#define SITAR_A_RX_LINE_2_DAC_CTL__POR			(0x00000000)
#define SITAR_A_RX_LINE_2_STATUS			(0x1D4)
#define SITAR_A_RX_LINE_2_STATUS__POR			(0x00000004)
#define SITAR_A_RX_LINE_BIAS_CNP2			(0x1E1)
#define SITAR_A_RX_LINE_BIAS_CNP2__POR			(0x0000008a)
#define SITAR_A_RX_LINE_OCP_CTL			(0x1E2)
#define SITAR_A_RX_LINE_OCP_CTL__POR			(0x000000e8)
#define SITAR_A_RX_LINE_1_PA_CTL			(0x1E3)
#define SITAR_A_RX_LINE_1_PA_CTL__POR			(0x00000040)
#define SITAR_A_RX_LINE_2_PA_CTL			(0x1E4)
#define SITAR_A_RX_LINE_2_PA_CTL__POR			(0x00000040)
#define SITAR_A_RX_LINE_CNP_DBG			(0x1EC)
#define SITAR_A_RX_LINE_CNP_DBG__POR			(0x00000000)
#define SITAR_A_MBHC_HPH			(0x1ED)
#define SITAR_A_MBHC_HPH__POR			(0x00000048)
#define SITAR_A_RC_OSC_FREQ			(0x1F7)
#define SITAR_A_RC_OSC_FREQ__POR			(0x00000046)
#define SITAR_A_RC_OSC_TEST			(0x1F8)
#define SITAR_A_RC_OSC_TEST__POR			(0x0000000a)
#define SITAR_A_RC_OSC_STATUS			(0x1F9)
#define SITAR_A_RC_OSC_STATUS__POR			(0x0000001c)
#define SITAR_A_RC_OSC_TUNER			(0x1FA)
#define SITAR_A_RC_OSC_TUNER__POR			(0x00000000)
#define SITAR_A_CDC_ANC1_CTL			(0x200)
#define SITAR_A_CDC_ANC1_CTL__POR			(0x00000000)
#define SITAR_A_CDC_ANC1_SHIFT			(0x201)
#define SITAR_A_CDC_ANC1_SHIFT__POR			(0x00000000)
#define SITAR_A_CDC_ANC1_IIR_B1_CTL			(0x202)
#define SITAR_A_CDC_ANC1_IIR_B1_CTL__POR			(0x00000000)
#define SITAR_A_CDC_ANC1_IIR_B2_CTL			(0x203)
#define SITAR_A_CDC_ANC1_IIR_B2_CTL__POR			(0x00000000)
#define SITAR_A_CDC_ANC1_IIR_B3_CTL			(0x204)
#define SITAR_A_CDC_ANC1_IIR_B3_CTL__POR			(0x00000000)
#define SITAR_A_CDC_ANC1_IIR_B4_CTL			(0x205)
#define SITAR_A_CDC_ANC1_IIR_B4_CTL__POR			(0x00000000)
#define SITAR_A_CDC_ANC1_LPF_B1_CTL			(0x206)
#define SITAR_A_CDC_ANC1_LPF_B1_CTL__POR			(0x00000000)
#define SITAR_A_CDC_ANC1_LPF_B2_CTL			(0x207)
#define SITAR_A_CDC_ANC1_LPF_B2_CTL__POR			(0x00000000)
#define SITAR_A_CDC_ANC1_LPF_B3_CTL			(0x208)
#define SITAR_A_CDC_ANC1_LPF_B3_CTL__POR			(0x00000000)
#define SITAR_A_CDC_ANC1_SPARE			(0x209)
#define SITAR_A_CDC_ANC1_SPARE__POR			(0x00000000)
#define SITAR_A_CDC_ANC1_SMLPF_CTL			(0x20A)
#define SITAR_A_CDC_ANC1_SMLPF_CTL__POR			(0x00000000)
#define SITAR_A_CDC_ANC1_DCFLT_CTL			(0x20B)
#define SITAR_A_CDC_ANC1_DCFLT_CTL__POR			(0x00000000)
#define SITAR_A_CDC_TX1_VOL_CTL_TIMER			(0x220)
#define SITAR_A_CDC_TX1_VOL_CTL_TIMER__POR			(0x00000000)
#define SITAR_A_CDC_TX1_VOL_CTL_GAIN			(0x221)
#define SITAR_A_CDC_TX1_VOL_CTL_GAIN__POR			(0x00000000)
#define SITAR_A_CDC_TX2_VOL_CTL_GAIN			(0x229)
#define SITAR_A_CDC_TX2_VOL_CTL_GAIN__POR			   (0x00000000)
#define SITAR_A_CDC_TX3_VOL_CTL_GAIN			(0x231)
#define SITAR_A_CDC_TX3_VOL_CTL_GAIN__POR			   (0x00000000)
#define SITAR_A_CDC_TX4_VOL_CTL_GAIN			(0x239)
#define SITAR_A_CDC_TX4_VOL_CTL_GAIN__POR			   (0x00000000)
#define SITAR_A_CDC_TX5_VOL_CTL_GAIN			(0x241)
#define SITAR_A_CDC_TX5_VOL_CTL_GAIN__POR			   (0x00000000)
#define SITAR_A_CDC_TX1_VOL_CTL_CFG			 (0x222)
#define SITAR_A_CDC_TX1_VOL_CTL_CFG__POR			    (0x00000000)
#define SITAR_A_CDC_TX2_VOL_CTL_CFG			 (0x22A)
#define SITAR_A_CDC_TX2_VOL_CTL_CFG__POR			    (0x00000000)
#define SITAR_A_CDC_TX3_VOL_CTL_CFG			 (0x232)
#define SITAR_A_CDC_TX3_VOL_CTL_CFG__POR			    (0x00000000)
#define SITAR_A_CDC_TX4_VOL_CTL_CFG			 (0x23A)
#define SITAR_A_CDC_TX4_VOL_CTL_CFG__POR			    (0x00000000)

#define SITAR_A_CDC_TX1_MUX_CTL			(0x223)
#define SITAR_A_CDC_TX1_MUX_CTL__POR			(0x00000008)
#define SITAR_A_CDC_TX1_CLK_FS_CTL                      (0x00000224)
#define SITAR_A_CDC_TX1_CLK_FS_CTL__POR                 (0x00000003)
#define SITAR_A_CDC_TX2_CLK_FS_CTL                      (0x0000022C)
#define SITAR_A_CDC_TX2_CLK_FS_CTL__POR                 (0x00000003)
#define SITAR_A_CDC_TX3_CLK_FS_CTL                      (0x00000234)
#define SITAR_A_CDC_TX3_CLK_FS_CTL__POR                 (0x00000003)
#define SITAR_A_CDC_TX4_CLK_FS_CTL                      (0x0000023C)
#define SITAR_A_CDC_TX4_CLK_FS_CTL__POR                 (0x00000003)
#define SITAR_A_CDC_TX1_DMIC_CTL			(0x225)
#define SITAR_A_CDC_TX1_DMIC_CTL__POR			(0x00000000)
#define SITAR_A_CDC_TX2_MUX_CTL                 (0x22B)
#define SITAR_A_CDC_TX2_MUX_CTL__POR			(0x00000008)
#define SITAR_A_CDC_TX3_MUX_CTL                 (0x233)
#define SITAR_A_CDC_TX3_MUX_CTL__POR			(0x00000008)
#define SITAR_A_CDC_TX4_MUX_CTL                 (0x23B)
#define SITAR_A_CDC_TX4_MUX_CTL__POR			(0x00000008)
#define SITAR_A_CDC_TX5_MUX_CTL                 (0x243)
#define SITAR_A_CDC_TX5_MUX_CTL__POR			(0x00000008)

#define SITAR_A_CDC_SRC1_PDA_CFG			(0x2A0)
#define SITAR_A_CDC_SRC1_PDA_CFG__POR			(0x00000000)
#define SITAR_A_CDC_SRC1_FS_CTL			(0x2A1)
#define SITAR_A_CDC_SRC1_FS_CTL__POR			(0x0000001b)

#define SITAR_A_CDC_RX1_B1_CTL                  (0x000002B0)
#define SITAR_A_CDC_RX1_B1_CTL__POR			 (0x00000000)
#define SITAR_A_CDC_RX2_B1_CTL                  (0x000002B8)
#define SITAR_A_CDC_RX2_B1_CTL__POR			 (0x00000000)
#define SITAR_A_CDC_RX3_B1_CTL                  (0x000002C0)
#define SITAR_A_CDC_RX3_B1_CTL__POR			 (0x00000000)

#define SITAR_A_CDC_RX1_B2_CTL                  (0x000002B1)
#define SITAR_A_CDC_RX1_B2_CTL__POR			 (0x00000000)
#define SITAR_A_CDC_RX2_B2_CTL                  (0x000002B9)
#define SITAR_A_CDC_RX2_B2_CTL__POR			 (0x00000000)
#define SITAR_A_CDC_RX3_B2_CTL                  (0x000002C1)
#define SITAR_A_CDC_RX3_B2_CTL__POR			 (0x00000000)

#define SITAR_A_CDC_RX1_B3_CTL                  (0x000002B2)
#define SITAR_A_CDC_RX1_B3_CTL__POR			 (0x00000000)
#define SITAR_A_CDC_RX2_B3_CTL                  (0x000002BA)
#define SITAR_A_CDC_RX2_B3_CTL__POR			 (0x00000000)
#define SITAR_A_CDC_RX3_B3_CTL                  (0x000002C2)
#define SITAR_A_CDC_RX3_B3_CTL__POR			 (0x00000000)

#define SITAR_A_CDC_RX1_B4_CTL                  (0x000002B3)
#define SITAR_A_CDC_RX1_B4_CTL__POR			 (0x00000000)
#define SITAR_A_CDC_RX2_B4_CTL                  (0x000002BB)
#define SITAR_A_CDC_RX2_B4_CTL__POR			 (0x00000000)
#define SITAR_A_CDC_RX3_B4_CTL                  (0x000002C3)
#define SITAR_A_CDC_RX3_B4_CTL__POR			 (0x00000000)

#define SITAR_A_CDC_RX1_B5_CTL                  (0x000002B4)
#define SITAR_A_CDC_RX1_B5_CTL__POR			 (0x00000078)
#define SITAR_A_CDC_RX2_B5_CTL                  (0x000002BC)
#define SITAR_A_CDC_RX2_B5_CTL__POR			 (0x00000078)
#define SITAR_A_CDC_RX3_B5_CTL                  (0x000002C4)
#define SITAR_A_CDC_RX3_B5_CTL__POR			 (0x00000078)

#define SITAR_A_CDC_RX1_B6_CTL                  (0x000002B5)
#define SITAR_A_CDC_RX1_B6_CTL__POR			 (0x00000080)
#define SITAR_A_CDC_RX2_B6_CTL                  (0x000002BD)
#define SITAR_A_CDC_RX2_B6_CTL__POR			 (0x00000080)
#define SITAR_A_CDC_RX3_B6_CTL                  (0x000002C5)
#define SITAR_A_CDC_RX3_B6_CTL__POR			 (0x00000080)


#define SITAR_A_CDC_RX1_VOL_CTL_B1_CTL			(0x2B6)
#define SITAR_A_CDC_RX1_VOL_CTL_B1_CTL__POR			(0x00000000)
#define SITAR_A_CDC_RX1_VOL_CTL_B2_CTL			(0x2B7)
#define SITAR_A_CDC_RX1_VOL_CTL_B2_CTL__POR			(0x00000000)
#define SITAR_A_CDC_RX2_VOL_CTL_B2_CTL                  (0x2BF)
#define SITAR_A_CDC_RX2_VOL_CTL_B2_CTL__POR                     (0x00000000)
#define SITAR_A_CDC_RX3_VOL_CTL_B2_CTL			(0x2C7)
#define SITAR_A_CDC_RX3_VOL_CTL_B2_CTL__POR                     (0x00000000)

#define SITAR_A_CDC_CLK_ANC_RESET_CTL			(0x300)
#define SITAR_A_CDC_CLK_ANC_RESET_CTL__POR			(0x00000000)
#define SITAR_A_CDC_CLK_RX_RESET_CTL			(0x301)
#define SITAR_A_CDC_CLK_RX_RESET_CTL__POR			(0x00000000)
#define SITAR_A_CDC_CLK_TX_RESET_B1_CTL			(0x302)
#define SITAR_A_CDC_CLK_TX_RESET_B1_CTL__POR			(0x00000000)
#define SITAR_A_CDC_CLK_TX_RESET_B2_CTL			(0x303)
#define SITAR_A_CDC_CLK_TX_RESET_B2_CTL__POR			(0x00000000)
#define SITAR_A_CDC_CLK_DMIC_CTL			(0x304)
#define SITAR_A_CDC_CLK_DMIC_CTL__POR			(0x00000000)
#define SITAR_A_CDC_CLK_RX_I2S_CTL			(0x305)
#define SITAR_A_CDC_CLK_RX_I2S_CTL__POR			(0x00000003)
#define SITAR_A_CDC_CLK_TX_I2S_CTL			(0x306)
#define SITAR_A_CDC_CLK_TX_I2S_CTL__POR			(0x00000003)
#define SITAR_A_CDC_CLK_OTHR_RESET_CTL			(0x307)
#define SITAR_A_CDC_CLK_OTHR_RESET_CTL__POR			(0x00000010)
#define SITAR_A_CDC_CLK_TX_CLK_EN_B1_CTL			(0x308)
#define SITAR_A_CDC_CLK_TX_CLK_EN_B1_CTL__POR			(0x00000000)
#define SITAR_A_CDC_CLK_OTHR_CTL			(0x30A)
#define SITAR_A_CDC_CLK_OTHR_CTL__POR			(0x00000000)
#define SITAR_A_CDC_CLK_RDAC_CLK_EN_CTL			(0x30B)
#define SITAR_A_CDC_CLK_RDAC_CLK_EN_CTL__POR			(0x00000000)
#define SITAR_A_CDC_CLK_ANC_CLK_EN_CTL			(0x30C)
#define SITAR_A_CDC_CLK_ANC_CLK_EN_CTL__POR			(0x00000000)
#define SITAR_A_CDC_CLK_RX_B1_CTL			(0x30D)
#define SITAR_A_CDC_CLK_RX_B1_CTL__POR			(0x00000000)
#define SITAR_A_CDC_CLK_RX_B2_CTL			(0x30E)
#define SITAR_A_CDC_CLK_RX_B2_CTL__POR			(0x00000000)
#define SITAR_A_CDC_CLK_MCLK_CTL			(0x30F)
#define SITAR_A_CDC_CLK_MCLK_CTL__POR			(0x00000000)
#define SITAR_A_CDC_CLK_PDM_CTL			(0x310)
#define SITAR_A_CDC_CLK_PDM_CTL__POR			(0x00000000)
#define SITAR_A_CDC_CLK_SD_CTL			(0x311)
#define SITAR_A_CDC_CLK_SD_CTL__POR			(0x00000000)
#define SITAR_A_CDC_CLK_LP_CTL			(0x312)
#define SITAR_A_CDC_CLK_LP_CTL__POR			(0x00000000)
#define SITAR_A_CDC_CLSG_FREQ_THRESH_B1_CTL			(0x320)
#define SITAR_A_CDC_CLSG_FREQ_THRESH_B1_CTL__POR	(0x00000007)
#define SITAR_A_CDC_CLSG_FREQ_THRESH_B2_CTL		(0x321)
#define SITAR_A_CDC_CLSG_FREQ_THRESH_B2_CTL__POR	(0x00000013)
#define SITAR_A_CDC_CLSG_FREQ_THRESH_B3_CTL		(0x322)
#define SITAR_A_CDC_CLSG_FREQ_THRESH_B3_CTL__POR	(0x0000001b)
#define SITAR_A_CDC_CLSG_FREQ_THRESH_B4_CTL		(0x323)
#define SITAR_A_CDC_CLSG_FREQ_THRESH_B4_CTL__POR	(0x0000007f)
#define SITAR_A_CDC_CLSG_GAIN_THRESH_CTL		(0x324)
#define SITAR_A_CDC_CLSG_GAIN_THRESH_CTL__POR		(0x00000026)
#define SITAR_A_CDC_CLSG_TIMER_B1_CFG			(0x325)
#define SITAR_A_CDC_CLSG_TIMER_B1_CFG__POR		(0x0000000a)
#define SITAR_A_CDC_CLSG_TIMER_B2_CFG			(0x326)
#define SITAR_A_CDC_CLSG_TIMER_B2_CFG__POR		(0x00000000)
#define SITAR_A_CDC_CLSG_CTL			(0x327)
#define SITAR_A_CDC_CLSG_CTL__POR			(0x00000013)
#define SITAR_A_CDC_IIR1_GAIN_B1_CTL			(0x340)
#define SITAR_A_CDC_IIR1_GAIN_B1_CTL__POR		(0x00000000)
#define SITAR_A_CDC_IIR1_GAIN_B2_CTL			(0x341)
#define SITAR_A_CDC_IIR1_GAIN_B2_CTL__POR		(0x00000000)
#define SITAR_A_CDC_IIR1_GAIN_B3_CTL			(0x342)
#define SITAR_A_CDC_IIR1_GAIN_B3_CTL__POR		(0x00000000)
#define SITAR_A_CDC_IIR1_GAIN_B4_CTL			(0x343)
#define SITAR_A_CDC_IIR1_GAIN_B4_CTL__POR		(0x00000000)
#define SITAR_A_CDC_IIR1_GAIN_B5_CTL			(0x344)
#define SITAR_A_CDC_IIR1_GAIN_B5_CTL__POR		(0x00000000)
#define SITAR_A_CDC_IIR1_GAIN_B6_CTL			(0x345)
#define SITAR_A_CDC_IIR1_GAIN_B6_CTL__POR		(0x00000000)
#define SITAR_A_CDC_IIR1_GAIN_B7_CTL			(0x346)
#define SITAR_A_CDC_IIR1_GAIN_B7_CTL__POR		(0x00000000)
#define SITAR_A_CDC_IIR1_GAIN_B8_CTL			(0x347)
#define SITAR_A_CDC_IIR1_GAIN_B8_CTL__POR		(0x00000000)
#define SITAR_A_CDC_IIR1_CTL				(0x348)
#define SITAR_A_CDC_IIR1_CTL__POR			(0x00000040)
#define SITAR_A_CDC_IIR1_GAIN_TIMER_CTL			(0x349)
#define SITAR_A_CDC_IIR1_GAIN_TIMER_CTL__POR		(0x00000000)
#define SITAR_A_CDC_IIR1_COEF_B1_CTL			(0x34A)
#define SITAR_A_CDC_IIR1_COEF_B1_CTL__POR		(0x00000000)
#define SITAR_A_CDC_IIR1_COEF_B2_CTL			(0x34B)
#define SITAR_A_CDC_IIR1_COEF_B2_CTL__POR		(0x00000000)
#define SITAR_A_CDC_IIR1_COEF_B3_CTL			(0x34C)
#define SITAR_A_CDC_IIR1_COEF_B3_CTL__POR		(0x00000000)
#define SITAR_A_CDC_IIR1_COEF_B4_CTL			(0x34D)
#define SITAR_A_CDC_IIR1_COEF_B4_CTL__POR		(0x00000000)
#define SITAR_A_CDC_IIR1_COEF_B5_CTL			(0x34E)
#define SITAR_A_CDC_IIR1_COEF_B5_CTL__POR		(0x00000000)
#define SITAR_A_CDC_TOP_GAIN_UPDATE			(0x360)
#define SITAR_A_CDC_TOP_GAIN_UPDATE__POR		(0x00000000)
#define SITAR_A_CDC_TOP_RDAC_DOUT_CTL			(0x361)
#define SITAR_A_CDC_TOP_RDAC_DOUT_CTL__POR		(0x00000000)
#define SITAR_A_CDC_DEBUG_B1_CTL			(0x368)
#define SITAR_A_CDC_DEBUG_B1_CTL__POR			(0x00000000)
#define SITAR_A_CDC_DEBUG_B2_CTL			(0x369)
#define SITAR_A_CDC_DEBUG_B2_CTL__POR			(0x00000000)
#define SITAR_A_CDC_DEBUG_B3_CTL			(0x36A)
#define SITAR_A_CDC_DEBUG_B3_CTL__POR			(0x00000000)
#define SITAR_A_CDC_DEBUG_B4_CTL			(0x36B)
#define SITAR_A_CDC_DEBUG_B4_CTL__POR			(0x00000000)
#define SITAR_A_CDC_DEBUG_B5_CTL			(0x36C)
#define SITAR_A_CDC_DEBUG_B5_CTL__POR			(0x00000000)
#define SITAR_A_CDC_DEBUG_B6_CTL			(0x36D)
#define SITAR_A_CDC_DEBUG_B6_CTL__POR			(0x00000000)
#define SITAR_A_CDC_DEBUG_B7_CTL			(0x36E)
#define SITAR_A_CDC_DEBUG_B7_CTL__POR			(0x00000000)
#define SITAR_A_CDC_COMP1_B1_CTL			(0x370)
#define SITAR_A_CDC_COMP1_B1_CTL__POR			(0x00000030)
#define SITAR_A_CDC_COMP1_B2_CTL			(0x371)
#define SITAR_A_CDC_COMP1_B2_CTL__POR			(0x000000b5)
#define SITAR_A_CDC_COMP1_B3_CTL			(0x372)
#define SITAR_A_CDC_COMP1_B3_CTL__POR			(0x00000028)
#define SITAR_A_CDC_COMP1_B4_CTL			(0x373)
#define SITAR_A_CDC_COMP1_B4_CTL__POR			(0x0000003c)
#define SITAR_A_CDC_COMP1_B5_CTL			(0x374)
#define SITAR_A_CDC_COMP1_B5_CTL__POR			(0x0000001f)
#define SITAR_A_CDC_COMP1_B6_CTL			(0x375)
#define SITAR_A_CDC_COMP1_B6_CTL__POR			(0x00000000)
#define SITAR_A_CDC_COMP1_SHUT_DOWN_STATUS		(0x376)
#define SITAR_A_CDC_COMP1_SHUT_DOWN_STATUS__POR		(0x00000003)
#define SITAR_A_CDC_COMP1_FS_CFG			(0x377)
#define SITAR_A_CDC_COMP1_FS_CFG__POR			(0x0000001b)
#define SITAR_A_CDC_CONN_RX1_B1_CTL			(0x380)
#define SITAR_A_CDC_CONN_RX1_B1_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_RX1_B2_CTL			(0x381)
#define SITAR_A_CDC_CONN_RX1_B2_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_RX1_B3_CTL			(0x382)
#define SITAR_A_CDC_CONN_RX1_B3_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_RX2_B1_CTL			(0x383)
#define SITAR_A_CDC_CONN_RX2_B1_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_RX2_B2_CTL			(0x384)
#define SITAR_A_CDC_CONN_RX2_B2_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_RX2_B3_CTL			(0x385)
#define SITAR_A_CDC_CONN_RX2_B3_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_RX3_B1_CTL			(0x386)
#define SITAR_A_CDC_CONN_RX3_B1_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_RX3_B2_CTL			(0x387)
#define SITAR_A_CDC_CONN_RX3_B2_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_RX3_B3_CTL			(0x388)
#define SITAR_A_CDC_CONN_RX3_B3_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_ANC_B1_CTL			(0x391)
#define SITAR_A_CDC_CONN_ANC_B1_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_ANC_B2_CTL			(0x392)
#define SITAR_A_CDC_CONN_ANC_B2_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_TX_B1_CTL			(0x393)
#define SITAR_A_CDC_CONN_TX_B1_CTL__POR			(0x00000000)
#define SITAR_A_CDC_CONN_TX_B2_CTL			(0x394)
#define SITAR_A_CDC_CONN_TX_B2_CTL__POR			(0x00000000)
#define SITAR_A_CDC_CONN_EQ1_B1_CTL			(0x397)
#define SITAR_A_CDC_CONN_EQ1_B1_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_EQ1_B2_CTL			(0x398)
#define SITAR_A_CDC_CONN_EQ1_B2_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_EQ1_B3_CTL			(0x399)
#define SITAR_A_CDC_CONN_EQ1_B3_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_EQ1_B4_CTL			(0x39A)
#define SITAR_A_CDC_CONN_EQ1_B4_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_EQ2_B1_CTL			(0x39B)
#define SITAR_A_CDC_CONN_EQ2_B1_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_EQ2_B2_CTL			(0x39C)
#define SITAR_A_CDC_CONN_EQ2_B2_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_EQ2_B3_CTL			(0x39D)
#define SITAR_A_CDC_CONN_EQ2_B3_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_EQ2_B4_CTL			(0x39E)
#define SITAR_A_CDC_CONN_EQ2_B4_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_SRC1_B1_CTL			(0x39F)
#define SITAR_A_CDC_CONN_SRC1_B1_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_SRC1_B2_CTL			(0x3A0)
#define SITAR_A_CDC_CONN_SRC1_B2_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_SRC2_B1_CTL			(0x3A1)
#define SITAR_A_CDC_CONN_SRC2_B1_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_SRC2_B2_CTL			(0x3A2)
#define SITAR_A_CDC_CONN_SRC2_B2_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_TX_SB_B1_CTL			(0x3A3)
#define SITAR_A_CDC_CONN_TX_SB_B1_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_TX_SB_B2_CTL			(0x3A4)
#define SITAR_A_CDC_CONN_TX_SB_B2_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_TX_SB_B3_CTL			(0x3A5)
#define SITAR_A_CDC_CONN_TX_SB_B3_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_TX_SB_B4_CTL			(0x3A6)
#define SITAR_A_CDC_CONN_TX_SB_B4_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_TX_SB_B5_CTL			(0x3A7)
#define SITAR_A_CDC_CONN_TX_SB_B5_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_RX_SB_B1_CTL			(0x3AE)
#define SITAR_A_CDC_CONN_RX_SB_B1_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_RX_SB_B2_CTL			(0x3AF)
#define SITAR_A_CDC_CONN_RX_SB_B2_CTL__POR		(0x00000000)
#define SITAR_A_CDC_CONN_CLSG_CTL			(0x3B0)
#define SITAR_A_CDC_CONN_CLSG_CTL__POR			(0x00000000)
#define SITAR_A_CDC_CONN_SPARE			(0x3B1)
#define SITAR_A_CDC_CONN_SPARE__POR			(0x00000000)
#define SITAR_A_CDC_MBHC_EN_CTL			(0x3C0)
#define SITAR_A_CDC_MBHC_EN_CTL__POR			(0x00000000)
#define SITAR_A_CDC_MBHC_FIR_B1_CFG			(0x3C1)
#define SITAR_A_CDC_MBHC_FIR_B1_CFG__POR		(0x00000000)
#define SITAR_A_CDC_MBHC_FIR_B2_CFG			(0x3C2)
#define SITAR_A_CDC_MBHC_FIR_B2_CFG__POR		(0x00000006)
#define SITAR_A_CDC_MBHC_TIMER_B1_CTL			(0x3C3)
#define SITAR_A_CDC_MBHC_TIMER_B1_CTL__POR		(0x00000003)
#define SITAR_A_CDC_MBHC_TIMER_B2_CTL			(0x3C4)
#define SITAR_A_CDC_MBHC_TIMER_B2_CTL__POR		(0x00000009)
#define SITAR_A_CDC_MBHC_TIMER_B3_CTL			(0x3C5)
#define SITAR_A_CDC_MBHC_TIMER_B3_CTL__POR		(0x0000001e)
#define SITAR_A_CDC_MBHC_TIMER_B4_CTL			(0x3C6)
#define SITAR_A_CDC_MBHC_TIMER_B4_CTL__POR		(0x00000045)
#define SITAR_A_CDC_MBHC_TIMER_B5_CTL			(0x3C7)
#define SITAR_A_CDC_MBHC_TIMER_B5_CTL__POR		(0x00000004)
#define SITAR_A_CDC_MBHC_TIMER_B6_CTL			(0x3C8)
#define SITAR_A_CDC_MBHC_TIMER_B6_CTL__POR		(0x00000078)
#define SITAR_A_CDC_MBHC_B1_STATUS			(0x3C9)
#define SITAR_A_CDC_MBHC_B1_STATUS__POR			(0x00000000)
#define SITAR_A_CDC_MBHC_B2_STATUS			(0x3CA)
#define SITAR_A_CDC_MBHC_B2_STATUS__POR			(0x00000000)
#define SITAR_A_CDC_MBHC_B3_STATUS			(0x3CB)
#define SITAR_A_CDC_MBHC_B3_STATUS__POR			(0x00000000)
#define SITAR_A_CDC_MBHC_B4_STATUS			(0x3CC)
#define SITAR_A_CDC_MBHC_B4_STATUS__POR			(0x00000000)
#define SITAR_A_CDC_MBHC_B5_STATUS			(0x3CD)
#define SITAR_A_CDC_MBHC_B5_STATUS__POR			(0x00000000)
#define SITAR_A_CDC_MBHC_B1_CTL			(0x3CE)
#define SITAR_A_CDC_MBHC_B1_CTL__POR			(0x000000c0)
#define SITAR_A_CDC_MBHC_B2_CTL			(0x3CF)
#define SITAR_A_CDC_MBHC_B2_CTL__POR			(0x0000005d)
#define SITAR_A_CDC_MBHC_VOLT_B1_CTL			(0x3D0)
#define SITAR_A_CDC_MBHC_VOLT_B1_CTL__POR			(0x00000000)
#define SITAR_A_CDC_MBHC_VOLT_B2_CTL			(0x3D1)
#define SITAR_A_CDC_MBHC_VOLT_B2_CTL__POR			(0x00000000)
#define SITAR_A_CDC_MBHC_VOLT_B3_CTL			(0x3D2)
#define SITAR_A_CDC_MBHC_VOLT_B3_CTL__POR			(0x00000000)
#define SITAR_A_CDC_MBHC_VOLT_B4_CTL			(0x3D3)
#define SITAR_A_CDC_MBHC_VOLT_B4_CTL__POR			(0x00000000)
#define SITAR_A_CDC_MBHC_VOLT_B5_CTL			(0x3D4)
#define SITAR_A_CDC_MBHC_VOLT_B5_CTL__POR			(0x00000000)
#define SITAR_A_CDC_MBHC_VOLT_B6_CTL			(0x3D5)
#define SITAR_A_CDC_MBHC_VOLT_B6_CTL__POR			(0x00000000)
#define SITAR_A_CDC_MBHC_VOLT_B7_CTL			(0x3D6)
#define SITAR_A_CDC_MBHC_VOLT_B7_CTL__POR			(0x000000ff)
#define SITAR_A_CDC_MBHC_VOLT_B8_CTL			(0x3D7)
#define SITAR_A_CDC_MBHC_VOLT_B8_CTL__POR			(0x00000007)
#define SITAR_A_CDC_MBHC_VOLT_B9_CTL			(0x3D8)
#define SITAR_A_CDC_MBHC_VOLT_B9_CTL__POR			(0x000000ff)
#define SITAR_A_CDC_MBHC_VOLT_B10_CTL			(0x3D9)
#define SITAR_A_CDC_MBHC_VOLT_B10_CTL__POR			(0x0000007f)
#define SITAR_A_CDC_MBHC_VOLT_B11_CTL			(0x3DA)
#define SITAR_A_CDC_MBHC_VOLT_B11_CTL__POR			(0x00000000)
#define SITAR_A_CDC_MBHC_VOLT_B12_CTL			(0x3DB)
#define SITAR_A_CDC_MBHC_VOLT_B12_CTL__POR			(0x00000080)
#define SITAR_A_CDC_MBHC_CLK_CTL			(0x3DC)
#define SITAR_A_CDC_MBHC_CLK_CTL__POR			(0x00000000)
#define SITAR_A_CDC_MBHC_INT_CTL			(0x3DD)
#define SITAR_A_CDC_MBHC_INT_CTL__POR			(0x00000000)
#define SITAR_A_CDC_MBHC_DEBUG_CTL			(0x3DE)
#define SITAR_A_CDC_MBHC_DEBUG_CTL__POR			(0x00000000)
#define SITAR_A_CDC_MBHC_SPARE			(0x3DF)
#define SITAR_A_CDC_MBHC_SPARE__POR			(0x00000000)
/* SLIMBUS Slave Registers */
#define SITAR_SLIM_PGD_PORT_INT_EN0			 (0x30)
#define SITAR_SLIM_PGD_PORT_INT_STATUS0                 (0x34)
#define SITAR_SLIM_PGD_PORT_INT_CLR0			(0x38)
#define SITAR_SLIM_PGD_PORT_INT_SOURCE0                 (0x60)

/* Macros for Packing Register Writes into a U32 */
#define SITAR_PACKED_REG_SIZE sizeof(u32)

#define SITAR_CODEC_PACK_ENTRY(reg, mask, val) ((val & 0xff)|\
	((mask & 0xff) << 8)|((reg & 0xffff) << 16))

#define SITAR_CODEC_UNPACK_ENTRY(packed, reg, mask, val) \
	do { \
		((reg) = ((packed >> 16) & (0xffff))); \
		((mask) = ((packed >> 8) & (0xff))); \
		((val) = ((packed) & (0xff))); \
	} while (0);
#endif
