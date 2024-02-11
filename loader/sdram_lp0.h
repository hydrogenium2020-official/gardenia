/*
 * Copyright (c) 2013, NVIDIA CORPORATION.  All rights reserved.
 * Copyright 2014 Google Inc.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 */

/**
 * Defines the SDRAM parameter structure.
 *
 * Note that PLLM is used by EMC. The field names are in camel case to ease
 * directly converting BCT config files (*.cfg) into C structure.
 */

#ifndef _T124_SDRAM_LP0_
#define _T124_SDRAM_LP0_

#include <stddef.h>
#include <stdint.h>
#include "types.h"

void sdram_lp0_save_params(const sdram_params_t124 *sdram);

// Memory Controller registers we need/care about
struct tegra_mc_regs {
	u32 rsvd_0x0[4];			/* 0x00 */
	u32 smmu_config;			/* 0x10 */
	u32 smmu_tlb_config;		/* 0x14 */
	u32 smmu_ptc_config;		/* 0x18 */
	u32 smmu_ptb_asid;			/* 0x1c */
	u32 smmu_ptb_data;			/* 0x20 */
	u32 rsvd_0x24[3];			/* 0x24 */
	u32 smmu_tlb_flush;		/* 0x30 */
	u32 smmu_ptc_flush;		/* 0x34 */
	u32 rsvd_0x38[6];			/* 0x38 */
	u32 emem_cfg;			/* 0x50 */
	u32 emem_adr_cfg;			/* 0x54 */
	u32 emem_adr_cfg_dev0;		/* 0x58 */
	u32 emem_adr_cfg_dev1;		/* 0x5c */
	u32 rsvd_0x60[1];			/* 0x60 */
	u32 emem_adr_cfg_bank_mask_0;	/* 0x64 */
	u32 emem_adr_cfg_bank_mask_1;	/* 0x68 */
	u32 emem_adr_cfg_bank_mask_2;	/* 0x6c */
	u32 rsvd_0x70[8];			/* 0x70 */
	u32 emem_arb_cfg;			/* 0x90 */
	u32 emem_arb_outstanding_req;	/* 0x94 */
	u32 emem_arb_timing_rcd;		/* 0x98 */
	u32 emem_arb_timing_rp;		/* 0x9c */
	u32 emem_arb_timing_rc;		/* 0xa0 */
	u32 emem_arb_timing_ras;		/* 0xa4 */
	u32 emem_arb_timing_faw;		/* 0xa8 */
	u32 emem_arb_timing_rrd;		/* 0xac */
	u32 emem_arb_timing_rap2pre;	/* 0xb0 */
	u32 emem_arb_timing_wap2pre;	/* 0xb4 */
	u32 emem_arb_timing_r2r;		/* 0xb8 */
	u32 emem_arb_timing_w2w;		/* 0xbc */
	u32 emem_arb_timing_r2w;		/* 0xc0 */
	u32 emem_arb_timing_w2r;		/* 0xc4 */
	u32 rsvd_0xc8[2];			/* 0xc8 */
	u32 emem_arb_da_turns;		/* 0xd0 */
	u32 emem_arb_da_covers;		/* 0xd4 */
	u32 emem_arb_misc0;		/* 0xd8 */
	u32 emem_arb_misc1;		/* 0xdc */
	u32 emem_arb_ring1_throttle;	/* 0xe0 */
	u32 emem_arb_ring3_throttle;	/* 0xe4 */
	u32 emem_arb_override;		/* 0xe8 */
	u32 emem_arb_rsv;			/* 0xec */
	u32 rsvd_0xf0[1];			/* 0xf0 */
	u32 clken_override;		/* 0xf4 */
	u32 timing_control_dbg;		/* 0xf8 */
	u32 timing_control;		/* 0xfc */
	u32 stat_control;			/* 0x100 */
	u32 rsvd_0x104[65];		/* 0x104 */
	u32 emem_arb_isochronous_0;	/* 0x208 */
	u32 emem_arb_isochronous_1;	/* 0x20c */
	u32 emem_arb_isochronous_2;	/* 0x210 */
	u32 rsvd_0x214[38];		/* 0x214 */
	u32 dis_extra_snap_levels;		/* 0x2ac */
	u32 rsvd_0x2b0[90];		/* 0x2b0 */
	u32 video_protect_vpr_override;	/* 0x418 */
	u32 rsvd_0x41c[93];		/* 0x41c */
	u32 video_protect_vpr_override1;	/* 0x590 */
	u32 rsvd_0x594[29];		/* 0x594 */
	u32 display_snap_ring;		/* 0x608 */
	u32 rsvd_0x60c[15];		/* 0x60c */
	u32 video_protect_bom;		/* 0x648 */
	u32 video_protect_size_mb;		/* 0x64c */
	u32 video_protect_reg_ctrl;	/* 0x650 */
	u32 rsvd_0x654[4];			/* 0x654 */
	u32 emem_cfg_access_ctrl;		/* 0x664 */
	u32 rsvd_0x668[2];			/* 0x668 */
	u32 sec_carveout_bom;		/* 0x670 */
	u32 sec_carveout_size_mb;		/* 0x674 */
	u32 sec_carveout_reg_ctrl;		/* 0x678 */
	u32 rsvd_0x67c[187];		/* 0x67c */
	u32 emem_arb_override_1;		/* 0x968 */
	u32 rsvd_0x96c[3];			/* 0x96c */
	u32 video_protect_bom_adr_hi;	/* 0x978 */
	u32 rsvd_0x97c[2];			/* 0x97c */
	u32 video_protect_gpu_override_0;	/* 0x984 */
	u32 video_protect_gpu_override_1;	/* 0x988 */
	u32 rsvd_0x98c[5];			/* 0x98c */
	u32 mts_carveout_bom;		/* 0x9a0 */
	u32 mts_carveout_size_mb;		/* 0x9a4 */
	u32 mts_carveout_adr_hi;		/* 0x9a8 */
	u32 mts_carveout_reg_ctrl;		/* 0x9ac */
	u32 rsvd_0x9b0[4];			/* 0x9b0 */
	u32 emem_bank_swizzle_cfg0;	/* 0x9c0 */
	u32 emem_bank_swizzle_cfg1;	/* 0x9c4 */
	u32 emem_bank_swizzle_cfg2;	/* 0x9c8 */
	u32 emem_bank_swizzle_cfg3;	/* 0x9cc */
	u32 rsvd_0x9d0[1];			/* 0x9d0 */
	u32 sec_carveout_adr_hi;		/* 0x9d4 */
};

enum {
	MC_EMEM_CFG_SIZE_MB_SHIFT = 0,
	MC_EMEM_CFG_SIZE_MB_MASK = 0x3fff,

	MC_EMEM_ARB_MISC0_MC_EMC_SAME_FREQ_SHIFT = 27,
	MC_EMEM_ARB_MISC0_MC_EMC_SAME_FREQ_MASK = 1 << 27,

	MC_EMEM_CFG_ACCESS_CTRL_WRITE_ACCESS_DISABLED = 1,

	MC_TIMING_CONTROL_TIMING_UPDATE = 1,
};

struct tegra_emc_regs {
	u32 intstatus;		/* 0x0 */
	u32 intmask;		/* 0x4 */
	u32 dbg;			/* 0x8 */
	u32 cfg;			/* 0xc */
	u32 adr_cfg;		/* 0x10 */
	u32 rsvd_0x14[3];		/* 0x14 */

	u32 refctrl;		/* 0x20 */
	u32 pin;			/* 0x24 */
	u32 timing_control;	/* 0x28 */
	u32 rc;			/* 0x2c */
	u32 rfc;			/* 0x30 */
	u32 ras;			/* 0x34 */
	u32 rp;			/* 0x38 */
	u32 r2w;			/* 0x3c */
	u32 w2r;			/* 0x40 */
	u32 r2p;			/* 0x44 */
	u32 w2p;			/* 0x48 */
	u32 rd_rcd;		/* 0x4c */
	u32 wr_rcd;		/* 0x50 */
	u32 rrd;			/* 0x54 */
	u32 rext;			/* 0x58 */
	u32 wdv;			/* 0x5c */
	u32 quse;			/* 0x60 */
	u32 qrst;			/* 0x64 */
	u32 qsafe;			/* 0x68 */
	u32 rdv;			/* 0x6c */
	u32 refresh;		/* 0x70 */
	u32 burst_refresh_num;	/* 0x74 */
	u32 pdex2wr;		/* 0x78 */
	u32 pdex2rd;		/* 0x7c */
	u32 pchg2pden;		/* 0x80 */
	u32 act2pden;		/* 0x84 */
	u32 ar2pden;		/* 0x88 */
	u32 rw2pden;		/* 0x8c */
	u32 txsr;			/* 0x90 */
	u32 tcke;			/* 0x94 */
	u32 tfaw;			/* 0x98 */
	u32 trpab;			/* 0x9c */
	u32 tclkstable;		/* 0xa0 */
	u32 tclkstop;		/* 0xa4 */
	u32 trefbw;		/* 0xa8 */
	u32 rsvd_0xac[1];		/* 0xac */
	u32 odt_write;		/* 0xb0 */
	u32 odt_read;		/* 0xb4 */
	u32 wext;			/* 0xb8 */
	u32 ctt;			/* 0xbc */
	u32 rfc_slr;		/* 0xc0 */
	u32 mrs_wait_cnt2;		/* 0xc4 */
	u32 mrs_wait_cnt;		/* 0xc8 */
	u32 mrs;			/* 0xcc */
	u32 emrs;			/* 0xd0 */
	u32 ref;			/* 0xd4 */
	u32 pre;			/* 0xd8 */
	u32 nop;			/* 0xdc */
	u32 self_ref;		/* 0xe0 */
	u32 dpd;			/* 0xe4 */
	u32 mrw;			/* 0xe8 */
	u32 mrr;			/* 0xec */
	u32 cmdq;			/* 0xf0 */
	u32 mc2emcq;		/* 0xf4 */
	u32 xm2dqspadctrl3;	/* 0xf8 */
	u32 rsvd_0xfc[1];		/* 0xfc */
	u32 fbio_spare;		/* 0x100 */
	u32 fbio_cfg5;		/* 0x104 */
	u32 fbio_wrptr_eq_2;	/* 0x108 */
	u32 rsvd_0x10c[2];		/* 0x10c */

	u32 fbio_cfg6;		/* 0x114 */
	u32 rsvd_0x118[2];		/* 0x118 */

	u32 cfg_rsv;		/* 0x120 */
	u32 acpd_control;		/* 0x124 */
	u32 rsvd_0x128[1];		/* 0x128 */
	u32 emrs2;			/* 0x12c */
	u32 emrs3;			/* 0x130 */
	u32 mrw2;			/* 0x134 */
	u32 mrw3;			/* 0x138 */
	u32 mrw4;			/* 0x13c */
	u32 clken_override;	/* 0x140 */
	u32 r2r;			/* 0x144 */
	u32 w2w;			/* 0x148 */
	u32 einput;		/* 0x14c */
	u32 einput_duration;	/* 0x150 */
	u32 puterm_extra;		/* 0x154 */
	u32 tckesr;		/* 0x158 */
	u32 tpd;			/* 0x15c */
	u32 rsvd_0x160[81];		/* 0x160 */

	u32 auto_cal_config;	/* 0x2a4 */
	u32 auto_cal_interval;	/* 0x2a8 */
	u32 auto_cal_status;	/* 0x2ac */
	u32 req_ctrl;		/* 0x2b0 */
	u32 status;		/* 0x2b4 */
	u32 cfg_2;			/* 0x2b8 */
	u32 cfg_dig_dll;		/* 0x2bc */
	u32 cfg_dig_dll_period;	/* 0x2c0 */
	u32 rsvd_0x2c4[1];		/* 0x2c4 */
	u32 dig_dll_status;	/* 0x2c8 */
	u32 rdv_mask;		/* 0x2cc */
	u32 wdv_mask;		/* 0x2d0 */
	u32 rsvd_0x2d4[1];		/* 0x2d4 */
	u32 ctt_duration;		/* 0x2d8 */
	u32 ctt_term_ctrl;		/* 0x2dc */
	u32 zcal_interval;		/* 0x2e0 */
	u32 zcal_wait_cnt;		/* 0x2e4 */
	u32 zcal_mrw_cmd;		/* 0x2e8 */
	u32 zq_cal;		/* 0x2ec */
	u32 xm2cmdpadctrl;		/* 0x2f0 */
	u32 xm2cmdpadctrl2;	/* 0x2f4 */
	u32 xm2dqspadctrl;		/* 0x2f8 */
	u32 xm2dqspadctrl2;	/* 0x2fc */
	u32 xm2dqpadctrl;		/* 0x300 */
	u32 xm2dqpadctrl2;		/* 0x304 */
	u32 xm2clkpadctrl;		/* 0x308 */
	u32 xm2comppadctrl;	/* 0x30c */
	u32 xm2vttgenpadctrl;	/* 0x310 */
	u32 xm2vttgenpadctrl2;	/* 0x314 */
	u32 xm2vttgenpadctrl3;	/* 0x318 */
	u32 emcpaden;		/* 0x31c */
	u32 xm2dqspadctrl4;	/* 0x320 */
	u32 scratch0;		/* 0x324 */
	u32 dll_xform_dqs0;	/* 0x328 */
	u32 dll_xform_dqs1;	/* 0x32c */
	u32 dll_xform_dqs2;	/* 0x330 */
	u32 dll_xform_dqs3;	/* 0x334 */
	u32 dll_xform_dqs4;	/* 0x338 */
	u32 dll_xform_dqs5;	/* 0x33c */
	u32 dll_xform_dqs6;	/* 0x340 */
	u32 dll_xform_dqs7;	/* 0x344 */
	u32 dll_xform_quse0;	/* 0x348 */
	u32 dll_xform_quse1;	/* 0x34c */
	u32 dll_xform_quse2;	/* 0x350 */
	u32 dll_xform_quse3;	/* 0x354 */
	u32 dll_xform_quse4;	/* 0x358 */
	u32 dll_xform_quse5;	/* 0x35c */
	u32 dll_xform_quse6;	/* 0x360 */
	u32 dll_xform_quse7;	/* 0x364 */
	u32 dll_xform_dq0;		/* 0x368 */
	u32 dll_xform_dq1;		/* 0x36c */
	u32 dll_xform_dq2;		/* 0x370 */
	u32 dll_xform_dq3;		/* 0x374 */
	u32 dli_rx_trim0;		/* 0x378 */
	u32 dli_rx_trim1;		/* 0x37c */
	u32 dli_rx_trim2;		/* 0x380 */
	u32 dli_rx_trim3;		/* 0x384 */
	u32 dli_rx_trim4;		/* 0x388 */
	u32 dli_rx_trim5;		/* 0x38c */
	u32 dli_rx_trim6;		/* 0x390 */
	u32 dli_rx_trim7;		/* 0x394 */
	u32 dli_tx_trim0;		/* 0x398 */
	u32 dli_tx_trim1;		/* 0x39c */
	u32 dli_tx_trim2;		/* 0x3a0 */
	u32 dli_tx_trim3;		/* 0x3a4 */
	u32 dli_trim_txdqs0;	/* 0x3a8 */
	u32 dli_trim_txdqs1;	/* 0x3ac */
	u32 dli_trim_txdqs2;	/* 0x3b0 */
	u32 dli_trim_txdqs3;	/* 0x3b4 */
	u32 dli_trim_txdqs4;	/* 0x3b8 */
	u32 dli_trim_txdqs5;	/* 0x3bc */
	u32 dli_trim_txdqs6;	/* 0x3c0 */
	u32 dli_trim_txdqs7;	/* 0x3c4 */
	u32 rsvd_0x3c8[1];		/* 0x3c8 */
	u32 stall_then_exe_after_clkchange;	/* 0x3cc */
	u32 rsvd_0x3d0[1];		/* 0x3d0 */
	u32 auto_cal_clk_status;	/* 0x3d4 */
	u32 sel_dpd_ctrl;		/* 0x3d8 */
	u32 pre_refresh_req_cnt;	/* 0x3dc */
	u32 dyn_self_ref_control;	/* 0x3e0 */
	u32 txsrdll;		/* 0x3e4 */
	u32 ccfifo_addr;		/* 0x3e8 */
	u32 ccfifo_data;		/* 0x3ec */
	u32 ccfifo_status;		/* 0x3f0 */
	u32 cdb_cntl_1;		/* 0x3f4 */
	u32 cdb_cntl_2;		/* 0x3f8 */
	u32 xm2clkpadctrl2;	/* 0x3fc */
	u32 swizzle_rank0_byte_cfg;	/* 0x400 */
	u32 swizzle_rank0_byte0;	/* 0x404 */
	u32 swizzle_rank0_byte1;	/* 0x408 */
	u32 swizzle_rank0_byte2;	/* 0x40c */
	u32 swizzle_rank0_byte3;	/* 0x410 */
	u32 swizzle_rank1_byte_cfg;	/* 0x414 */
	u32 swizzle_rank1_byte0;	/* 0x418 */
	u32 swizzle_rank1_byte1;	/* 0x41c */
	u32 swizzle_rank1_byte2;	/* 0x420 */
	u32 swizzle_rank1_byte3;	/* 0x424 */
	u32 ca_training_start;	/* 0x428 */
	u32 ca_training_busy;	/* 0x42c */
	u32 ca_training_cfg;	/* 0x430 */
	u32 ca_training_timing_cntl1;	/* 0x434 */
	u32 ca_training_timing_cntl2;	/* 0x438 */
	u32 ca_training_ca_lead_in;	/* 0x43c */
	u32 ca_training_ca;	/* 0x440 */
	u32 ca_training_ca_lead_out;	/* 0x444 */
	u32 ca_training_result1;	/* 0x448 */
	u32 ca_training_result2;	/* 0x44c */
	u32 ca_training_result3;	/* 0x450 */
	u32 ca_training_result4;	/* 0x454 */
	u32 auto_cal_config2;	/* 0x458 */
	u32 auto_cal_config3;	/* 0x45c */
	u32 auto_cal_status2;	/* 0x460 */
	u32 xm2cmdpadctrl3;	/* 0x464 */
	u32 ibdly;			/* 0x468 */
	u32 dll_xform_addr0;	/* 0x46c */
	u32 dll_xform_addr1;	/* 0x470 */
	u32 dll_xform_addr2;	/* 0x474 */
	u32 dli_addr_trim;		/* 0x478 */
	u32 dsr_vttgen_drv;	/* 0x47c */
	u32 txdsrvttgen;		/* 0x480 */
	u32 xm2cmdpadctrl4;	/* 0x484 */
	u32 xm2cmdpadctrl5;	/* 0x488 */
	u32 rsvd_0x48c[5];		/* 0x48c */

	u32 dll_xform_dqs8;	/* 0x4a0 */
	u32 dll_xform_dqs9;	/* 0x4a4 */
	u32 dll_xform_dqs10;	/* 0x4a8 */
	u32 dll_xform_dqs11;	/* 0x4ac */
	u32 dll_xform_dqs12;	/* 0x4b0 */
	u32 dll_xform_dqs13;	/* 0x4b4 */
	u32 dll_xform_dqs14;	/* 0x4b8 */
	u32 dll_xform_dqs15;	/* 0x4bc */
	u32 dll_xform_quse8;	/* 0x4c0 */
	u32 dll_xform_quse9;	/* 0x4c4 */
	u32 dll_xform_quse10;	/* 0x4c8 */
	u32 dll_xform_quse11;	/* 0x4cc */
	u32 dll_xform_quse12;	/* 0x4d0 */
	u32 dll_xform_quse13;	/* 0x4d4 */
	u32 dll_xform_quse14;	/* 0x4d8 */
	u32 dll_xform_quse15;	/* 0x4dc */
	u32 dll_xform_dq4;		/* 0x4e0 */
	u32 dll_xform_dq5;		/* 0x4e4 */
	u32 dll_xform_dq6;		/* 0x4e8 */
	u32 dll_xform_dq7;		/* 0x4ec */
	u32 rsvd_0x4f0[12];		/* 0x4f0 */

	u32 dli_trim_txdqs8;	/* 0x520 */
	u32 dli_trim_txdqs9;	/* 0x524 */
	u32 dli_trim_txdqs10;	/* 0x528 */
	u32 dli_trim_txdqs11;	/* 0x52c */
	u32 dli_trim_txdqs12;	/* 0x530 */
	u32 dli_trim_txdqs13;	/* 0x534 */
	u32 dli_trim_txdqs14;	/* 0x538 */
	u32 dli_trim_txdqs15;	/* 0x53c */
	u32 cdb_cntl_3;		/* 0x540 */
	u32 xm2dqspadctrl5;	/* 0x544 */
	u32 xm2dqspadctrl6;	/* 0x548 */
	u32 xm2dqpadctrl3;		/* 0x54c */
	u32 dll_xform_addr3;	/* 0x550 */
	u32 dll_xform_addr4;	/* 0x554 */
	u32 dll_xform_addr5;	/* 0x558 */
	u32 rsvd_0x55c[1];		/* 0x55c */
	u32 cfg_pipe;		/* 0x560 */
	u32 qpop;			/* 0x564 */
	u32 quse_width;		/* 0x568 */
	u32 puterm_width;		/* 0x56c */
	u32 bgbias_ctl0;		/* 0x570 */
	u32 puterm_adj;		/* 0x574 */
} __packed;


enum {
	EMC_PIN_RESET_MASK = 1 << 8,
	EMC_PIN_RESET_ACTIVE = 0 << 8,
	EMC_PIN_RESET_INACTIVE = 1 << 8,
	EMC_PIN_DQM_MASK = 1 << 4,
	EMC_PIN_DQM_NORMAL = 0 << 4,
	EMC_PIN_DQM_INACTIVE = 1 << 4,
	EMC_PIN_CKE_MASK = 1 << 0,
	EMC_PIN_CKE_POWERDOWN = 0 << 0,
	EMC_PIN_CKE_NORMAL = 1 << 0,

	EMC_REF_CMD_MASK = 1 << 0,
	EMC_REF_CMD_REFRESH = 1 << 0,
	EMC_REF_NORMAL_MASK = 1 << 1,
	EMC_REF_NORMAL_INIT = 0 << 1,
	EMC_REF_NORMAL_ENABLED = 1 << 1,
	EMC_REF_NUM_SHIFT = 8,
	EMC_REF_NUM_MASK = 0xFF << EMC_REF_NUM_SHIFT,
	EMC_REF_DEV_SELECTN_SHIFT = 30,
	EMC_REF_DEV_SELECTN_MASK = 3 << EMC_REF_DEV_SELECTN_SHIFT,

	EMC_REFCTRL_REF_VALID_MASK = 1 << 31,
	EMC_REFCTRL_REF_VALID_DISABLED = 0 << 31,
	EMC_REFCTRL_REF_VALID_ENABLED = 1 << 31,

	EMC_CFG_EMC2PMACRO_CFG_BYPASS_ADDRPIPE_MASK = 1 << 1,
	EMC_CFG_EMC2PMACRO_CFG_BYPASS_DATAPIPE1_MASK = 1 << 2,
	EMC_CFG_EMC2PMACRO_CFG_BYPASS_DATAPIPE2_MASK = 1 << 3,

	EMC_NOP_NOP_CMD_SHIFT = 0,
	EMC_NOP_NOP_CMD_MASK = 1 << EMC_NOP_NOP_CMD_SHIFT,
	EMC_NOP_NOP_DEV_SELECTN_SHIFT = 30,
	EMC_NOP_NOP_DEV_SELECTN_MASK = 3 << EMC_NOP_NOP_DEV_SELECTN_SHIFT,

	EMC_TIMING_CONTROL_TIMING_UPDATE = 1,
};

#endif /* __SOC_NVIDIA_TEGRA124_SDRAM_PARAM_H__ */




