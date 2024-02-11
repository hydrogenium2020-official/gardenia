/*
 * Copyright 2014 Google Inc.
 * Copyright (c) 2018 naehrwert
 * Copyright (c) 2018 balika011
 * Copyright (c) 2019-2023 CTCaer
 * Copyright (c) 2024 hydrogenium2020-offical
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "sdram.h"
#include "memory_map.h"
//#include "pmc.h"
#include "util.h"
#include "string.h"
#include "sdram_config_h5tc4g63afr-rda-792mhz.inl"
#include "t124.h"
#include "printf.h"
#include "sdram_lp0.h"
#include "pmc_lp0.h"
#include "clock_lp0.h"
#include "io.h"
static struct clk_rst_ctlr *clk_rst = (void *)CLOCK_BASE;
void *sdram_get_params_t124()
{
	// Copy base parameters.
	u32 *params = (u32 *)SDRAM_PARAMS_ADDR;
	memcpy(params, &dram_cfg_4gb_h5tc4g63afr_rda_792mhz, sizeof(sdram_params_t124));
	printf_("%u",sizeof(sdram_params_t124));

	return (void *)params;
}


static void sdram_patch(uintptr_t addr, u32 value)
{
	if (addr)
		write32((u32 *)addr, value);
}

static void writebits(u32 value, u32 *addr, u32 mask)
{
	clrsetbits32(addr, mask, (value & mask));
}

/* PMC must be configured before clock-enable and de-reset of MC/EMC. */
static void sdram_configure_pmc(const sdram_params_t124 *param,
				struct tegra_pmc_regs *regs)
{
	/* VDDP Select */
	write32(&regs->vddp_sel, param->PmcVddpSel);
	sleep(param->PmcVddpSelWait);

	/* Set DDR pad voltage */
	writebits(param->PmcDdrPwr, &regs->ddr_pwr, PMC_DDR_PWR_VAL_MASK);

	/* Set package and DPD pad control */
	writebits(param->PmcDdrCfg, &regs->ddr_cfg,
		  (PMC_DDR_CFG_PKG_MASK | PMC_DDR_CFG_IF_MASK |
		   PMC_DDR_CFG_XM0_RESET_TRI_MASK |
		   PMC_DDR_CFG_XM0_RESET_DPDIO_MASK));

	/* Turn on MEM IO Power */
	writebits(param->PmcNoIoPower, &regs->no_iopower,
		  (PMC_NO_IOPOWER_MEM_MASK | PMC_NO_IOPOWER_MEM_COMP_MASK));

	write32(&regs->reg_short, param->PmcRegShort);
}
void clock_enable_clear_reset(u32 l, u32 h, u32 u, u32 v, u32 w, u32 x)
{
	if (l) write32(&clk_rst->clk_enb_l_set, l);
	if (h) write32(&clk_rst->clk_enb_h_set, h);
	if (u) write32(&clk_rst->clk_enb_u_set, u);
	if (v) write32(&clk_rst->clk_enb_v_set, v);
	if (w) write32(&clk_rst->clk_enb_w_set, w);
	if (x) write32(&clk_rst->clk_enb_x_set, x);

	/* Give clocks time to stabilize. */
	sleep(2);

	if (l) write32(&clk_rst->rst_dev_l_clr, l);
	if (h) write32(&clk_rst->rst_dev_h_clr, h);
	if (u) write32(&clk_rst->rst_dev_u_clr, u);
	if (v) write32(&clk_rst->rst_dev_v_clr, v);
	if (w) write32(&clk_rst->rst_dev_w_clr, w);
	if (x) write32(&clk_rst->rst_dev_x_clr, x);
}
/* Start PLLM for SDRAM. */
void clock_sdram(u32 m, u32 n, u32 p, u32 setup, u32 ph45, u32 ph90,
		 u32 ph135, u32 kvco, u32 kcp, u32 stable_time, u32 emc_source,
		 u32 same_freq)
{

	u32 misc1 = ((setup << PLLM_MISC1_SETUP_SHIFT) |
		     (ph45 << PLLM_MISC1_PD_LSHIFT_PH45_SHIFT) |
		     (ph90 << PLLM_MISC1_PD_LSHIFT_PH90_SHIFT) |
		     (ph135 << PLLM_MISC1_PD_LSHIFT_PH135_SHIFT)),
	    misc2 = ((kvco << PLLM_MISC2_KVCO_SHIFT) |
		     (kcp << PLLM_MISC2_KCP_SHIFT)),
	    base;

	if (same_freq)
		emc_source |= CLK_SOURCE_EMC_MC_EMC_SAME_FREQ;
	else
		emc_source &= ~CLK_SOURCE_EMC_MC_EMC_SAME_FREQ;

	/*
	 * Note PLLM_BASE.PLLM_OUT1_RSTN must be in RESET_ENABLE mode, and
	 * PLLM_BASE.ENABLE must be in DISABLE state (both are the default
	 * values after coldboot reset).
	 */

	write32(&clk_rst->pllm_misc1, misc1);
	write32(&clk_rst->pllm_misc2, misc2);

	/* PLLM.BASE needs BYPASS=0, different from general init_pll */
	base = read32(&clk_rst->pllm_base);
	base &= ~(PLLCMX_BASE_DIVN_MASK | PLLCMX_BASE_DIVM_MASK |
		  PLLM_BASE_DIVP_MASK | PLL_BASE_BYPASS);
	base |= ((m << PLL_BASE_DIVM_SHIFT) | (n << PLL_BASE_DIVN_SHIFT) |
		 (p << PLL_BASE_DIVP_SHIFT));
	write32(&clk_rst->pllm_base, base);

	setbits32(&clk_rst->pllm_base, PLL_BASE_ENABLE);
	/* stable_time is required, before we can start to check lock. */
	sleep(stable_time);

	while (!(read32(&clk_rst->pllm_base) & PLL_BASE_LOCK)) {
		sleep(1);
	}
	/*
	 * After PLLM reports being locked, we have to delay 10us before
	 * enabling PLLM_OUT.
	 */
	sleep(10);

	/* Put OUT1 out of reset state (start to output). */
	setbits32(&clk_rst->pllm_out, PLLM_OUT1_RSTN_RESET_DISABLE);

	/* Enable and start MEM(MC) and EMC. */
	clock_enable_clear_reset(0, (0x1 << 0) | (0x1 << 25), 0, 0, 0, 0);
	write32(&clk_rst->clk_src_emc, emc_source);
	sleep(2);
}

static void sdram_start_clocks(const sdram_params_t124 *param)
{
	u32 is_same_freq = (param->McEmemArbMisc0 &
			    MC_EMEM_ARB_MISC0_MC_EMC_SAME_FREQ_MASK) ? 1 : 0;

	clock_sdram(param->PllMInputDivider, param->PllMFeedbackDivider,
		    param->PllMSelectDiv2, param->PllMSetupControl,
		    param->PllMPDLshiftPh45, param->PllMPDLshiftPh90,
		    param->PllMPDLshiftPh135, param->PllMKVCO,
		    param->PllMKCP, param->PllMStableTime,
		    param->EmcClockSource, is_same_freq);
}

static void sdram_deassert_clock_enable_signal(const sdram_params_t124 *param,
					       struct tegra_pmc_regs *regs)
{
	clrbits32(&regs->por_dpd_ctrl,
		  PMC_POR_DPD_CTRL_MEM0_HOLD_CKE_LOW_OVR_MASK);
	sleep(param->PmcPorDpdCtrlWait);
}

static void sdram_deassert_sel_dpd(const sdram_params_t124 *param,
				   struct tegra_pmc_regs *regs)
{
	clrbits32(&regs->por_dpd_ctrl,
		  (PMC_POR_DPD_CTRL_MEM0_ADDR0_CLK_SEL_DPD_MASK |
		   PMC_POR_DPD_CTRL_MEM0_ADDR1_CLK_SEL_DPD_MASK));
	/*
	 * Note NVIDIA recommended to always do 10us delay here and ignore
	 * BCT.PmcPorDpdCtrlWait.
	 * */
	sleep(10);
}

static void sdram_set_swizzle(const sdram_params_t124 *param,
			      struct tegra_emc_regs *regs)
{
	write32(&regs->swizzle_rank0_byte_cfg, param->EmcSwizzleRank0ByteCfg);
	write32(&regs->swizzle_rank0_byte0, param->EmcSwizzleRank0Byte0);
	write32(&regs->swizzle_rank0_byte1, param->EmcSwizzleRank0Byte1);
	write32(&regs->swizzle_rank0_byte2, param->EmcSwizzleRank0Byte2);
	write32(&regs->swizzle_rank0_byte3, param->EmcSwizzleRank0Byte3);
	write32(&regs->swizzle_rank1_byte_cfg, param->EmcSwizzleRank1ByteCfg);
	write32(&regs->swizzle_rank1_byte0, param->EmcSwizzleRank1Byte0);
	write32(&regs->swizzle_rank1_byte1, param->EmcSwizzleRank1Byte1);
	write32(&regs->swizzle_rank1_byte2, param->EmcSwizzleRank1Byte2);
	write32(&regs->swizzle_rank1_byte3, param->EmcSwizzleRank1Byte3);
}

static void sdram_set_pad_controls(const sdram_params_t124 *param,
				   struct tegra_emc_regs *regs)
{
	/* Program the pad controls */
	write32(&regs->xm2cmdpadctrl, param->EmcXm2CmdPadCtrl);
	write32(&regs->xm2cmdpadctrl2, param->EmcXm2CmdPadCtrl2);
	write32(&regs->xm2cmdpadctrl3, param->EmcXm2CmdPadCtrl3);
	write32(&regs->xm2cmdpadctrl4, param->EmcXm2CmdPadCtrl4);
	write32(&regs->xm2cmdpadctrl5, param->EmcXm2CmdPadCtrl5);

	write32(&regs->xm2dqspadctrl, param->EmcXm2DqsPadCtrl);
	write32(&regs->xm2dqspadctrl2, param->EmcXm2DqsPadCtrl2);
	write32(&regs->xm2dqspadctrl3, param->EmcXm2DqsPadCtrl3);
	write32(&regs->xm2dqspadctrl4, param->EmcXm2DqsPadCtrl4);
	write32(&regs->xm2dqspadctrl5, param->EmcXm2DqsPadCtrl5);
	write32(&regs->xm2dqspadctrl6, param->EmcXm2DqsPadCtrl6);

	write32(&regs->xm2dqpadctrl, param->EmcXm2DqPadCtrl);
	write32(&regs->xm2dqpadctrl2, param->EmcXm2DqPadCtrl2);
	write32(&regs->xm2dqpadctrl3, param->EmcXm2DqPadCtrl3);

	write32(&regs->xm2clkpadctrl, param->EmcXm2ClkPadCtrl);
	write32(&regs->xm2clkpadctrl2, param->EmcXm2ClkPadCtrl2);

	write32(&regs->xm2comppadctrl, param->EmcXm2CompPadCtrl);

	write32(&regs->xm2vttgenpadctrl, param->EmcXm2VttGenPadCtrl);
	write32(&regs->xm2vttgenpadctrl2, param->EmcXm2VttGenPadCtrl2);
	write32(&regs->xm2vttgenpadctrl3, param->EmcXm2VttGenPadCtrl3);

	write32(&regs->ctt_term_ctrl, param->EmcCttTermCtrl);
}

static void sdram_trigger_emc_timing_update(struct tegra_emc_regs *regs)
{
	write32(&regs->timing_control, EMC_TIMING_CONTROL_TIMING_UPDATE);
}

static void sdram_init_mc(const sdram_params_t124 *param,
			  struct tegra_mc_regs *regs)
{
	/* Initialize MC VPR settings */
	write32(&regs->display_snap_ring, param->McDisplaySnapRing);
	write32(&regs->video_protect_bom, param->McVideoProtectBom);
	write32(&regs->video_protect_bom_adr_hi,
		param->McVideoProtectBomAdrHi);
	write32(&regs->video_protect_size_mb, param->McVideoProtectSizeMb);
	write32(&regs->video_protect_vpr_override,
		param->McVideoProtectVprOverride);
	write32(&regs->video_protect_vpr_override1,
		param->McVideoProtectVprOverride1);
	write32(&regs->video_protect_gpu_override_0,
		param->McVideoProtectGpuOverride0);
	write32(&regs->video_protect_gpu_override_1,
		param->McVideoProtectGpuOverride1);

	/* Program SDRAM geometry paarameters */
	write32(&regs->emem_adr_cfg, param->McEmemAdrCfg);
	write32(&regs->emem_adr_cfg_dev0, param->McEmemAdrCfgDev0);
	write32(&regs->emem_adr_cfg_dev1, param->McEmemAdrCfgDev1);

	/* Program bank swizzling */
	write32(&regs->emem_bank_swizzle_cfg0, param->McEmemAdrCfgBankMask0);
	write32(&regs->emem_bank_swizzle_cfg1, param->McEmemAdrCfgBankMask1);
	write32(&regs->emem_bank_swizzle_cfg2, param->McEmemAdrCfgBankMask2);
	write32(&regs->emem_bank_swizzle_cfg3,
		param->McEmemAdrCfgBankSwizzle3);

	/* Program external memory aperature (base and size) */
	write32(&regs->emem_cfg, param->McEmemCfg);

	/* Program SEC carveout (base and size) */
	write32(&regs->sec_carveout_bom, param->McSecCarveoutBom);
	write32(&regs->sec_carveout_adr_hi, param->McSecCarveoutAdrHi);
	write32(&regs->sec_carveout_size_mb, param->McSecCarveoutSizeMb);

	/* Program MTS carveout (base and size) */
	write32(&regs->mts_carveout_bom, param->McMtsCarveoutBom);
	write32(&regs->mts_carveout_adr_hi, param->McMtsCarveoutAdrHi);
	write32(&regs->mts_carveout_size_mb, param->McMtsCarveoutSizeMb);

	/* Program the memory arbiter */
	write32(&regs->emem_arb_cfg, param->McEmemArbCfg);
	write32(&regs->emem_arb_outstanding_req,
		param->McEmemArbOutstandingReq);
	write32(&regs->emem_arb_timing_rcd, param->McEmemArbTimingRcd);
	write32(&regs->emem_arb_timing_rp, param->McEmemArbTimingRp);
	write32(&regs->emem_arb_timing_rc, param->McEmemArbTimingRc);
	write32(&regs->emem_arb_timing_ras, param->McEmemArbTimingRas);
	write32(&regs->emem_arb_timing_faw, param->McEmemArbTimingFaw);
	write32(&regs->emem_arb_timing_rrd, param->McEmemArbTimingRrd);
	write32(&regs->emem_arb_timing_rap2pre, param->McEmemArbTimingRap2Pre);
	write32(&regs->emem_arb_timing_wap2pre, param->McEmemArbTimingWap2Pre);
	write32(&regs->emem_arb_timing_r2r, param->McEmemArbTimingR2R);
	write32(&regs->emem_arb_timing_w2w, param->McEmemArbTimingW2W);
	write32(&regs->emem_arb_timing_r2w, param->McEmemArbTimingR2W);
	write32(&regs->emem_arb_timing_w2r, param->McEmemArbTimingW2R);
	write32(&regs->emem_arb_da_turns, param->McEmemArbDaTurns);
	write32(&regs->emem_arb_da_covers, param->McEmemArbDaCovers);
	write32(&regs->emem_arb_misc0, param->McEmemArbMisc0);
	write32(&regs->emem_arb_misc1, param->McEmemArbMisc1);
	write32(&regs->emem_arb_ring1_throttle, param->McEmemArbRing1Throttle);
	write32(&regs->emem_arb_override, param->McEmemArbOverride);
	write32(&regs->emem_arb_override_1, param->McEmemArbOverride1);
	write32(&regs->emem_arb_rsv, param->McEmemArbRsv);

	/* Program extra snap levels for display client */
	write32(&regs->dis_extra_snap_levels, param->McDisExtraSnapLevels);

	/* Trigger MC timing update */
	write32(&regs->timing_control, MC_TIMING_CONTROL_TIMING_UPDATE);

	/* Program second-level clock enable overrides */
	write32(&regs->clken_override, param->McClkenOverride);

	/* Program statistics gathering */
	write32(&regs->stat_control, param->McStatControl);
}

static void sdram_init_emc(const sdram_params_t124 *param,
			   struct tegra_emc_regs *regs)
{
	/* Program SDRAM geometry parameters */
	write32(&regs->adr_cfg, param->EmcAdrCfg);

	/* Program second-level clock enable overrides */
	write32(&regs->clken_override, param->EmcClkenOverride);

	/* Program EMC pad auto calibration */
	write32(&regs->auto_cal_interval, param->EmcAutoCalInterval);
	write32(&regs->auto_cal_config2, param->EmcAutoCalConfig2);
	write32(&regs->auto_cal_config3, param->EmcAutoCalConfig3);
	write32(&regs->auto_cal_config, param->EmcAutoCalConfig);
	sleep(param->EmcAutoCalWait);
}

static void sdram_set_emc_timing(const sdram_params_t124 *param,
				 struct tegra_emc_regs *regs)
{
	/* Program EMC timing configuration */
	write32(&regs->cfg_2, param->EmcCfg2);
	write32(&regs->cfg_pipe, param->EmcCfgPipe);
	write32(&regs->dbg, param->EmcDbg);
	write32(&regs->cmdq, param->EmcCmdQ);
	write32(&regs->mc2emcq, param->EmcMc2EmcQ);
	write32(&regs->mrs_wait_cnt, param->EmcMrsWaitCnt);
	write32(&regs->mrs_wait_cnt2, param->EmcMrsWaitCnt2);
	write32(&regs->fbio_cfg5, param->EmcFbioCfg5);
	write32(&regs->rc, param->EmcRc);
	write32(&regs->rfc, param->EmcRfc);
	write32(&regs->rfc_slr, param->EmcRfcSlr);
	write32(&regs->ras, param->EmcRas);
	write32(&regs->rp, param->EmcRp);
	write32(&regs->r2r, param->EmcR2r);
	write32(&regs->w2w, param->EmcW2w);
	write32(&regs->r2w, param->EmcR2w);
	write32(&regs->w2r, param->EmcW2r);
	write32(&regs->r2p, param->EmcR2p);
	write32(&regs->w2p, param->EmcW2p);
	write32(&regs->rd_rcd, param->EmcRdRcd);
	write32(&regs->wr_rcd, param->EmcWrRcd);
	write32(&regs->rrd, param->EmcRrd);
	write32(&regs->rext, param->EmcRext);
	write32(&regs->wext, param->EmcWext);
	write32(&regs->wdv, param->EmcWdv);
	write32(&regs->wdv_mask, param->EmcWdvMask);
	write32(&regs->quse, param->EmcQUse);
	write32(&regs->quse_width, param->EmcQuseWidth);
	write32(&regs->ibdly, param->EmcIbdly);
	write32(&regs->einput, param->EmcEInput);
	write32(&regs->einput_duration, param->EmcEInputDuration);
	write32(&regs->puterm_extra, param->EmcPutermExtra);
	write32(&regs->puterm_width, param->EmcPutermWidth);
	write32(&regs->puterm_adj, param->EmcPutermAdj);
	write32(&regs->cdb_cntl_1, param->EmcCdbCntl1);
	write32(&regs->cdb_cntl_2, param->EmcCdbCntl2);
	write32(&regs->cdb_cntl_3, param->EmcCdbCntl3);
	write32(&regs->qrst, param->EmcQRst);
	write32(&regs->qsafe, param->EmcQSafe);
	write32(&regs->rdv, param->EmcRdv);
	write32(&regs->rdv_mask, param->EmcRdvMask);
	write32(&regs->qpop, param->EmcQpop);
	write32(&regs->ctt, param->EmcCtt);
	write32(&regs->ctt_duration, param->EmcCttDuration);
	write32(&regs->refresh, param->EmcRefresh);
	write32(&regs->burst_refresh_num, param->EmcBurstRefreshNum);
	write32(&regs->pre_refresh_req_cnt, param->EmcPreRefreshReqCnt);
	write32(&regs->pdex2wr, param->EmcPdEx2Wr);
	write32(&regs->pdex2rd, param->EmcPdEx2Rd);
	write32(&regs->pchg2pden, param->EmcPChg2Pden);
	write32(&regs->act2pden, param->EmcAct2Pden);
	write32(&regs->ar2pden, param->EmcAr2Pden);
	write32(&regs->rw2pden, param->EmcRw2Pden);
	write32(&regs->txsr, param->EmcTxsr);
	write32(&regs->txsrdll, param->EmcTxsrDll);
	write32(&regs->tcke, param->EmcTcke);
	write32(&regs->tckesr, param->EmcTckesr);
	write32(&regs->tpd, param->EmcTpd);
	write32(&regs->tfaw, param->EmcTfaw);
	write32(&regs->trpab, param->EmcTrpab);
	write32(&regs->tclkstable, param->EmcTClkStable);
	write32(&regs->tclkstop, param->EmcTClkStop);
	write32(&regs->trefbw, param->EmcTRefBw);
	write32(&regs->odt_write, param->EmcOdtWrite);
	write32(&regs->odt_read, param->EmcOdtRead);
	write32(&regs->fbio_cfg6, param->EmcFbioCfg6);
	write32(&regs->cfg_dig_dll, param->EmcCfgDigDll);
	write32(&regs->cfg_dig_dll_period, param->EmcCfgDigDllPeriod);

	/* Don't write bit 1: addr swizzle lock bit. Written at end of sequence. */
	write32(&regs->fbio_spare, param->EmcFbioSpare & 0xfffffffd);

	write32(&regs->cfg_rsv, param->EmcCfgRsv);
	write32(&regs->dll_xform_dqs0, param->EmcDllXformDqs0);
	write32(&regs->dll_xform_dqs1, param->EmcDllXformDqs1);
	write32(&regs->dll_xform_dqs2, param->EmcDllXformDqs2);
	write32(&regs->dll_xform_dqs3, param->EmcDllXformDqs3);
	write32(&regs->dll_xform_dqs4, param->EmcDllXformDqs4);
	write32(&regs->dll_xform_dqs5, param->EmcDllXformDqs5);
	write32(&regs->dll_xform_dqs6, param->EmcDllXformDqs6);
	write32(&regs->dll_xform_dqs7, param->EmcDllXformDqs7);
	write32(&regs->dll_xform_dqs8, param->EmcDllXformDqs8);
	write32(&regs->dll_xform_dqs9, param->EmcDllXformDqs9);
	write32(&regs->dll_xform_dqs10, param->EmcDllXformDqs10);
	write32(&regs->dll_xform_dqs11, param->EmcDllXformDqs11);
	write32(&regs->dll_xform_dqs12, param->EmcDllXformDqs12);
	write32(&regs->dll_xform_dqs13, param->EmcDllXformDqs13);
	write32(&regs->dll_xform_dqs14, param->EmcDllXformDqs14);
	write32(&regs->dll_xform_dqs15, param->EmcDllXformDqs15);
	write32(&regs->dll_xform_quse0, param->EmcDllXformQUse0);
	write32(&regs->dll_xform_quse1, param->EmcDllXformQUse1);
	write32(&regs->dll_xform_quse2, param->EmcDllXformQUse2);
	write32(&regs->dll_xform_quse3, param->EmcDllXformQUse3);
	write32(&regs->dll_xform_quse4, param->EmcDllXformQUse4);
	write32(&regs->dll_xform_quse5, param->EmcDllXformQUse5);
	write32(&regs->dll_xform_quse6, param->EmcDllXformQUse6);
	write32(&regs->dll_xform_quse7, param->EmcDllXformQUse7);
	write32(&regs->dll_xform_quse8, param->EmcDllXformQUse8);
	write32(&regs->dll_xform_quse9, param->EmcDllXformQUse9);
	write32(&regs->dll_xform_quse10, param->EmcDllXformQUse10);
	write32(&regs->dll_xform_quse11, param->EmcDllXformQUse11);
	write32(&regs->dll_xform_quse12, param->EmcDllXformQUse12);
	write32(&regs->dll_xform_quse13, param->EmcDllXformQUse13);
	write32(&regs->dll_xform_quse14, param->EmcDllXformQUse14);
	write32(&regs->dll_xform_quse15, param->EmcDllXformQUse15);
	write32(&regs->dll_xform_dq0, param->EmcDllXformDq0);
	write32(&regs->dll_xform_dq1, param->EmcDllXformDq1);
	write32(&regs->dll_xform_dq2, param->EmcDllXformDq2);
	write32(&regs->dll_xform_dq3, param->EmcDllXformDq3);
	write32(&regs->dll_xform_dq4, param->EmcDllXformDq4);
	write32(&regs->dll_xform_dq5, param->EmcDllXformDq5);
	write32(&regs->dll_xform_dq6, param->EmcDllXformDq6);
	write32(&regs->dll_xform_dq7, param->EmcDllXformDq7);
	write32(&regs->dll_xform_addr0, param->EmcDllXformAddr0);
	write32(&regs->dll_xform_addr1, param->EmcDllXformAddr1);
	write32(&regs->dll_xform_addr2, param->EmcDllXformAddr2);
	write32(&regs->dll_xform_addr3, param->EmcDllXformAddr3);
	write32(&regs->dll_xform_addr4, param->EmcDllXformAddr4);
	write32(&regs->dll_xform_addr5, param->EmcDllXformAddr5);
	write32(&regs->acpd_control, param->EmcAcpdControl);
	write32(&regs->dsr_vttgen_drv, param->EmcDsrVttgenDrv);
	write32(&regs->txdsrvttgen, param->EmcTxdsrvttgen);
	write32(&regs->bgbias_ctl0, param->EmcBgbiasCtl0);

	/*
	 * Set pipe bypass enable bits before sending any DRAM commands.
	 * Note other bits in EMC_CFG must be set AFTER REFCTRL is configured.
	 */
	writebits(param->EmcCfg, &regs->cfg,
		  (EMC_CFG_EMC2PMACRO_CFG_BYPASS_ADDRPIPE_MASK |
		   EMC_CFG_EMC2PMACRO_CFG_BYPASS_DATAPIPE1_MASK |
		   EMC_CFG_EMC2PMACRO_CFG_BYPASS_DATAPIPE2_MASK));
}

static void sdram_patch_bootrom(const sdram_params_t124 *param,
				struct tegra_mc_regs *regs)
{
	if (param->BootRomPatchControl & BOOT_ROM_PATCH_CONTROL_ENABLE_MASK) {
		uintptr_t addr = ((param->BootRomPatchControl &
				  BOOT_ROM_PATCH_CONTROL_OFFSET_MASK) >>
				  BOOT_ROM_PATCH_CONTROL_OFFSET_SHIFT);
		addr = BOOT_ROM_PATCH_CONTROL_BASE_ADDRESS + (addr << 2);
		write32((u32 *)addr, param->BootRomPatchData);
		write32(&regs->timing_control, 1);
	}
}

static void sdram_set_dpd3(const sdram_params_t124 *param,
			   struct tegra_pmc_regs *regs)
{
	/* Program DPD request */
	write32(&regs->io_dpd3_req, param->PmcIoDpd3Req);
	sleep(param->PmcIoDpd3ReqWait);
}

static void sdram_set_dli_trims(const sdram_params_t124 *param,
				struct tegra_emc_regs *regs)
{
	/* Program DLI trims */
	write32(&regs->dli_trim_txdqs0, param->EmcDliTrimTxDqs0);
	write32(&regs->dli_trim_txdqs1, param->EmcDliTrimTxDqs1);
	write32(&regs->dli_trim_txdqs2, param->EmcDliTrimTxDqs2);
	write32(&regs->dli_trim_txdqs3, param->EmcDliTrimTxDqs3);
	write32(&regs->dli_trim_txdqs4, param->EmcDliTrimTxDqs4);
	write32(&regs->dli_trim_txdqs5, param->EmcDliTrimTxDqs5);
	write32(&regs->dli_trim_txdqs6, param->EmcDliTrimTxDqs6);
	write32(&regs->dli_trim_txdqs7, param->EmcDliTrimTxDqs7);
	write32(&regs->dli_trim_txdqs8, param->EmcDliTrimTxDqs8);
	write32(&regs->dli_trim_txdqs9, param->EmcDliTrimTxDqs9);
	write32(&regs->dli_trim_txdqs10, param->EmcDliTrimTxDqs10);
	write32(&regs->dli_trim_txdqs11, param->EmcDliTrimTxDqs11);
	write32(&regs->dli_trim_txdqs12, param->EmcDliTrimTxDqs12);
	write32(&regs->dli_trim_txdqs13, param->EmcDliTrimTxDqs13);
	write32(&regs->dli_trim_txdqs14, param->EmcDliTrimTxDqs14);
	write32(&regs->dli_trim_txdqs15, param->EmcDliTrimTxDqs15);

	write32(&regs->ca_training_timing_cntl1,
		param->EmcCaTrainingTimingCntl1);
	write32(&regs->ca_training_timing_cntl2,
		param->EmcCaTrainingTimingCntl2);

	sdram_trigger_emc_timing_update(regs);
	sleep(param->EmcTimingControlWait);
}

static void sdram_set_clock_enable_signal(const sdram_params_t124 *param,
					  struct tegra_emc_regs *regs)
{
	volatile u32 dummy = 0;
	clrbits32(&regs->pin, (EMC_PIN_RESET_MASK | EMC_PIN_DQM_MASK |
			       EMC_PIN_CKE_MASK));
	/*
	 * Assert dummy read of PIN register to ensure above write to PIN
	 * register went through. 200 is the recommended value by NVIDIA.
	 */
	dummy |= read32(&regs->pin);
	sleep(200 + param->EmcPinExtraWait);

	/* Deassert reset */
	setbits32(&regs->pin, EMC_PIN_RESET_INACTIVE);
	/*
	 * Assert dummy read of PIN register to ensure above write to PIN
	 * register went through. 200 is the recommended value by NVIDIA.
	 */
	dummy |= read32(&regs->pin);
	sleep(500 + param->EmcPinExtraWait);

	/* Enable clock enable signal */
	setbits32(&regs->pin, EMC_PIN_CKE_NORMAL);
	/*
	 * Assert dummy read of PIN register to ensure above write to PIN
	 * register went through. 200 is the recommended value by NVIDIA.
	 */
	dummy |= read32(&regs->pin);
	sleep(param->EmcPinProgramWait);

	if (!dummy) {
		printf_("Failed to program EMC pin.");
	}

	/* Send NOP (trigger) */
	writebits(((1 << EMC_NOP_NOP_CMD_SHIFT) |
		   (param->EmcDevSelect << EMC_NOP_NOP_DEV_SELECTN_SHIFT)),
		  &regs->nop,
		  EMC_NOP_NOP_CMD_MASK | EMC_NOP_NOP_DEV_SELECTN_MASK);

	/* Write mode registers */
	write32(&regs->emrs2, param->EmcEmrs2);
	write32(&regs->emrs3, param->EmcEmrs3);
	write32(&regs->emrs, param->EmcEmrs);
	write32(&regs->mrs, param->EmcMrs);

	if (param->EmcExtraModeRegWriteEnable) {
		write32(&regs->mrs, param->EmcMrwExtra);
	}
}

static void sdram_init_zq_calibration(const sdram_params_t124 *param,
				      struct tegra_emc_regs *regs)
{
	if ((param->EmcZcalWarmColdBootEnables &
	     EMC_ZCAL_WARM_COLD_BOOT_ENABLES_COLDBOOT_MASK) == 1) {
		/* Need to initialize ZCAL on coldboot. */
		write32(&regs->zq_cal, param->EmcZcalInitDev0);
		sleep(param->EmcZcalInitWait);

		if ((param->EmcDevSelect & 2) == 0) {
			write32(&regs->zq_cal, param->EmcZcalInitDev1);
			sleep(param->EmcZcalInitWait);
		}
	} else {
		sleep(param->EmcZcalInitWait);
	}
}

static void sdram_set_zq_calibration(const sdram_params_t124 *param,
				     struct tegra_emc_regs *regs)
{
	/* Start periodic ZQ calibration */
	write32(&regs->zcal_interval, param->EmcZcalInterval);
	write32(&regs->zcal_wait_cnt, param->EmcZcalWaitCnt);
	write32(&regs->zcal_mrw_cmd, param->EmcZcalMrwCmd);
}

static void sdram_set_refresh(const sdram_params_t124 *param,
			      struct tegra_emc_regs *regs)
{
	/* Insert burst refresh */
	if (param->EmcExtraRefreshNum > 0) {
		u32 refresh_num = (1 << param->EmcExtraRefreshNum) - 1;
		writebits((EMC_REF_CMD_REFRESH | EMC_REF_NORMAL_ENABLED |
			   (refresh_num << EMC_REF_NUM_SHIFT) |
			   (param->EmcDevSelect << EMC_REF_DEV_SELECTN_SHIFT)),
			  &regs->ref, (EMC_REF_CMD_MASK | EMC_REF_NORMAL_MASK |
				       EMC_REF_NUM_MASK |
				       EMC_REF_DEV_SELECTN_MASK));
	}

	/* Enable refresh */
	write32(&regs->refctrl,
		(param->EmcDevSelect | EMC_REFCTRL_REF_VALID_ENABLED));

	write32(&regs->dyn_self_ref_control, param->EmcDynSelfRefControl);
	write32(&regs->cfg, param->EmcCfg);
	write32(&regs->sel_dpd_ctrl, param->EmcSelDpdCtrl);

	/* Write addr swizzle lock bit */
	write32(&regs->fbio_spare, param->EmcFbioSpare);

	/* Re-trigger timing to latch power saving functions */
	sdram_trigger_emc_timing_update(regs);
}

static void sdram_enable_arbiter(const sdram_params_t124 *param)
{
	/* TODO(hungte) Move values here to standalone header file. */
	u32 *AHB_ARBITRATION_XBAR_CTRL = (u32*)(0x6000c000 + 0xe0);
	setbits32(AHB_ARBITRATION_XBAR_CTRL,
		  param->AhbArbitrationXbarCtrlMemInitDone << 16);
}

static void sdram_lock_carveouts(const sdram_params_t124 *param,
				 struct tegra_mc_regs *regs)
{
	/* Lock carveouts, and emem_cfg registers */
	write32(&regs->video_protect_reg_ctrl,
		param->McVideoProtectWriteAccess);
	write32(&regs->emem_cfg_access_ctrl,
		MC_EMEM_CFG_ACCESS_CTRL_WRITE_ACCESS_DISABLED);
	write32(&regs->sec_carveout_reg_ctrl,
		param->McSecCarveoutProtectWriteAccess);
	write32(&regs->mts_carveout_reg_ctrl, param->McMtsCarveoutRegCtrl);
}
/* CRC_OSC_CTRL_0 0x50 */
#define OSC_FREQ_SHIFT			28
#define OSC_FREQ_MASK			(0xf << OSC_FREQ_SHIFT)
#define OSC_PREDIV_SHIFT		26
#define OSC_PREDIV_MASK			(0x3 << OSC_PREDIV_SHIFT)
#define OSC_XOFS_SHIFT			4
#define OSC_XOFS_MASK			(0x3F << OSC_XOFS_SHIFT)
#define OSC_DRIVE_STRENGTH		7
#define OSC_XOBP			(1 << 1)
#define OSC_XOE				(1 << 0)
int clock_get_pll_input_khz(void)
{
	u32 osc_ctrl = CLOCK(0x50);
	u32 osc_bits = (osc_ctrl & OSC_FREQ_MASK) >> OSC_FREQ_SHIFT;
	u32 pll_ref_div = (osc_ctrl & OSC_PREDIV_MASK) >> OSC_PREDIV_SHIFT;
	return 12000 >> pll_ref_div;
}




void sdram_init()
{
	const sdram_params_t124 *param=sdram_get_params_t124();
	struct tegra_pmc_regs *pmc = (struct tegra_pmc_regs*)PMC_BASE;
	struct tegra_mc_regs *mc = (struct tegra_mc_regs*)MC_BASE;
	struct tegra_emc_regs *emc = (struct tegra_emc_regs*)EMC_BASE;

	printf_("Initializing SDRAM of type %d with %dKHz\n",
		param->MemoryType, clock_get_pll_input_khz() *
		param->PllMFeedbackDivider / param->PllMInputDivider /
		(1 + param->PllMSelectDiv2));
	if (param->MemoryType != MEMORY_TYPE_DDR3)
		printf_("Unsupported memory type!\n");

	sdram_configure_pmc(param, pmc);
	sdram_patch(param->EmcBctSpare0, param->EmcBctSpare1);

	sdram_start_clocks(param);
	sdram_patch(param->EmcBctSpare2, param->EmcBctSpare3);

	sdram_deassert_sel_dpd(param, pmc);
	sdram_set_swizzle(param, emc);
	sdram_set_pad_controls(param, emc);
	sdram_patch(param->EmcBctSpare4, param->EmcBctSpare5);



	sdram_trigger_emc_timing_update(emc);
	sdram_init_mc(param, mc);
	sdram_init_emc(param, emc);
	sdram_patch(param->EmcBctSpare6, param->EmcBctSpare7);


	sdram_set_emc_timing(param, emc);
	sdram_patch_bootrom(param, mc);
	sdram_set_dpd3(param, pmc);
	sdram_set_dli_trims(param, emc);
	sdram_deassert_clock_enable_signal(param, pmc);
	sdram_set_clock_enable_signal(param, emc);
	sdram_init_zq_calibration(param, emc);
	sdram_patch(param->EmcBctSpare8, param->EmcBctSpare9);


	sdram_set_zq_calibration(param, emc);
	sdram_patch(param->EmcBctSpare10, param->EmcBctSpare11);

	sdram_trigger_emc_timing_update(emc);
	sdram_set_refresh(param, emc);
	sdram_enable_arbiter(param);
	sdram_lock_carveouts(param, mc);

	sdram_lp0_save_params(param);
}

u32 sdram_get_ram_code(void)
{
	struct tegra_pmc_regs *pmc = (struct tegra_pmc_regs*)PMC_BASE;
	return ((read32(&pmc->strapping_opt_a) &
		 PMC_STRAPPING_OPT_A_RAM_CODE_MASK) >>
		PMC_STRAPPING_OPT_A_RAM_CODE_SHIFT);
}



