/*
* Copyright (c) 2024 hydrogenium2020-offical
* Copyright (c) 2018 naehrwert
* Copyright (c) 2018-2022 CTCaer
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
#ifndef _T124_MC_H_
#define _T124_MC_H_

#include "types.h"
#define	MC_SMMU_CONFIG				0x10
#define	MC_SMMU_TLB_CONFIG			0x14
#define	MC_SMMU_PTC_CONFIG			0x18
#define	MC_SMMU_PTB_ASID			0x1c
#define	MC_SMMU_PTB_DATA			0x20
#define	MC_SMMU_TLB_FLUSH			0x30
#define	MC_SMMU_PTC_FLUSH			0x34
#define	MC_EMEM_CFG					0x50
#define	MC_EMEM_ADR_CFG				0x54
#define	MC_EMEM_ADR_CFG_DEV0		0x58
#define	MC_EMEM_ADR_CFG_DEV1		0x5c
#define	MC_EMEM_ADR_CFG_BANK_MASK_0	0x64
#define	MC_EMEM_ADR_CFG_BANK_MASK_1	0x68
#define	MC_EMEM_ADR_CFG_BANK_MASK_2	0x6c
#define	MC_EMEM_ARB_CFG				0x90
#define	MC_EMEM_ARB_OUTSTANDING_REQ	0x94
#define	MC_EMEM_ARB_TIMING_RCD		0x98
#define	MC_EMEM_ARB_TIMING_RP		0x9c
#define	MC_EMEM_ARB_TIMING_RC		0xa0
#define	MC_EMEM_ARB_TIMING_RAS		0xa4
#define	MC_EMEM_ARB_TIMING_FAW		0xa8
#define	MC_EMEM_ARB_TIMING_RRD		0xac
#define	MC_EMEM_ARB_TIMING_RAP2PRE	0xb0
#define	MC_EMEM_ARB_TIMING_WAP2PRE	0xb4
#define	MC_EMEM_ARB_TIMING_R2R		0xb8
#define	MC_EMEM_ARB_TIMING_W2W		0xbc
#define	MC_EMEM_ARB_TIMING_R2W		0xc0
#define	MC_EMEM_ARB_TIMING_W2R		0xc4
#define	MC_EMEM_ARB_DA_TURNS		0xd0
#define	MC_EMEM_ARB_DA_COVERS		0xd4
#define	MC_EMEM_ARB_MISC0			0xd8
#define	MC_EMEM_ARB_MISC1			0xdc
#define	MC_EMEM_ARB_RING1_THROTTLE	0xe0
#define	MC_EMEM_ARB_RING3_THROTTLE	0xe4
#define	MC_EMEM_ARB_OVERRIDE		0xe8
#define	MC_EMEM_ARB_RSV				0xec
#define	MC_CLKEN_OVERRIDE			0xf4
#define	MC_TIMING_CONTROL_DBG		0xf8
#define	MC_TIMING_CONTROL			0xfc
#define	MC_STAT_CONTROL				0x100
#define	MC_EMEM_ARB_ISOCHRONOUS_0	0x208
#define	MC_EMEM_ARB_ISOCHRONOUS_1	0x20c
#define	MC_EMEM_ARB_ISOCHRONOUS_2	0x210
#define	MC_DIS_EXTRA_SNAP_LEVELS	0x2ac
#define	MC_VIDEO_PROTECT_VPR_OVERRIDE	0x418
#define	MC_VIDEO_PROTECT_VPR_OVERRIDE1	0x590
#define	MC_DISPLAY_SNAP_RING		0x608
#define	MC_VIDEO_PROTECT_BOM		0x648
#define	MC_VIDEO_PROTECT_SIZE_MB	0x64c
#define	MC_VIDEO_PROTECT_REG_CTRL	0x650
#define MC_IRAM_BOM                 0x65c
#define MC_IRAM_TOM                 0x660
#define	MC_EMEM_CFG_ACCESS_CTRL		0x664
#define	MC_SEC_CARVEOUT_BOM			0x670
#define	MC_SEC_CARVEOUT_SIZE_MB		0x674
#define	MC_SEC_CARVEOUT_REG_CTRL	0x678
#define	MC_EMEM_ARB_OVERRIDE_1		0x968
#define	MC_VIDEO_PROTECT_BOM_ADR_HI	0x978
#define	MC_VIDEO_PROTECT_GPU_OVERRIDE_0	0x984
#define	MC_VIDEO_PROTECT_GPU_OVERRIDE_1	0x988
#define	MC_MTS_CARVEOUT_BOM			0x9a0
#define	MC_MTS_CARVEOUT_SIZE_MB		0x9a4
#define	MC_MTS_CARVEOUT_ADR_HI		0x9a8
#define	MC_MTS_CARVEOUT_REG_CTRL	0x9ac
#define	MC_EMEM_BANK_SWIZZLE_CFG0	0x9c0
#define	MC_EMEM_BANK_SWIZZLE_CFG1	0x9c4
#define	MC_EMEM_BANK_SWIZZLE_CFG2	0x9c8
#define	MC_EMEM_BANK_SWIZZLE_CFG3	0x9cc
#define	MC_SEC_CARVEOUT_ADR_HI		0x9d4

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
	u32 emem_adr_cfg_channel_mask;	/* 0x60 */
	u32 emem_adr_cfg_bank_mask_0;	/* 0x64 */
	u32 emem_adr_cfg_bank_mask_1;	/* 0x68 */
	u32 emem_adr_cfg_bank_mask_2;	/* 0x6c */
	u32 security_cfg0;			/* 0x70 */
	u32 security_cfg1;			/* 0x74 */
	u32 rsvd_0x78[6];			/* 0x78 */
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
	u32 emem_arb_misc2;		/* 0xC8 */
	u32 rsvd_0xcc[1];			/* 0xCC */
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
	u32 rsvd_0x67c[17];		/* 0x67C-0x6BC */

	u32 emem_arb_timing_rfcpb;		/* 0x6C0 */
	u32 emem_arb_timing_ccdmw;		/* 0x6C4 */
	u32 rsvd_0x6c8[10];		/* 0x6C8-0x6EC */

	u32 emem_arb_refpb_hp_ctrl;	/* 0x6F0 */
	u32 emem_arb_refpb_bank_ctrl;	/* 0x6F4 */
	u32 rsvd_0x6f8[156];		/* 0x6F8-0x964 */

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
	u32 rsvd_0x9d8;			/* 0x9D8 */
	u32 da_config0;			/* 0x9DC */
	u32 rsvd_0x9c0[138];		/* 0x9E0-0xc04 */

	u32 security_carveout1_cfg0;	/* 0xc08 */
	u32 security_carveout1_bom;	/* 0xc0c */
	u32 security_carveout1_bom_hi;	/* 0xc10 */
	u32 security_carveout1_size_128kb;	/* 0xc14 */
	u32 security_carveout1_ca0;	/* 0xc18 */
	u32 security_carveout1_ca1;	/* 0xc1c */
	u32 security_carveout1_ca2;	/* 0xc20 */
	u32 security_carveout1_ca3;	/* 0xc24 */
	u32 security_carveout1_ca4;	/* 0xc28 */
	u32 security_carveout1_cfia0;	/* 0xc2c */
	u32 security_carveout1_cfia1;	/* 0xc30 */
	u32 security_carveout1_cfia2;	/* 0xc34 */
	u32 security_carveout1_cfia3;	/* 0xc38 */
	u32 security_carveout1_cfia4;	/* 0xc3c */
	u32 rsvd_0xc40[6];			/* 0xc40-0xc54 */

	u32 security_carveout2_cfg0;	/* 0xc58 */
	u32 security_carveout2_bom;	/* 0xc5c */
	u32 security_carveout2_bom_hi;	/* 0xc60 */
	u32 security_carveout2_size_128kb;	/* 0xc64 */
	u32 security_carveout2_ca0;	/* 0xc68 */
	u32 security_carveout2_ca1;	/* 0xc6c */
	u32 security_carveout2_ca2;	/* 0xc70 */
	u32 security_carveout2_ca3;	/* 0xc74 */
	u32 security_carveout2_ca4;	/* 0xc78 */
	u32 security_carveout2_cfia0;	/* 0xc7c */
	u32 security_carveout2_cfia1;	/* 0xc80 */
	u32 security_carveout2_cfia2;	/* 0xc84 */
	u32 security_carveout2_cfia3;	/* 0xc88 */
	u32 security_carveout2_cfia4;	/* 0xc8c */
	u32 rsvd_0xc90[6];			/* 0xc90-0xca4 */

	u32 security_carveout3_cfg0;	/* 0xca8 */
	u32 security_carveout3_bom;	/* 0xcac */
	u32 security_carveout3_bom_hi;	/* 0xcb0 */
	u32 security_carveout3_size_128kb;	/* 0xcb4 */
	u32 security_carveout3_ca0;	/* 0xcb8 */
	u32 security_carveout3_ca1;	/* 0xcbc */
	u32 security_carveout3_ca2;	/* 0xcc0 */
	u32 security_carveout3_ca3;	/* 0xcc4 */
	u32 security_carveout3_ca4;	/* 0xcc8 */
	u32 security_carveout3_cfia0;	/* 0xccc */
	u32 security_carveout3_cfia1;	/* 0xcd0 */
	u32 security_carveout3_cfia2;	/* 0xcd4 */
	u32 security_carveout3_cfia3;	/* 0xcd8 */
	u32 security_carveout3_cfia4;	/* 0xcdc */
	u32 rsvd_0xce0[6];			/* 0xce0-0xcf4 */

	u32 security_carveout4_cfg0;	/* 0xcf8 */
	u32 security_carveout4_bom;	/* 0xcfc */
	u32 security_carveout4_bom_hi;	/* 0xd00 */
	u32 security_carveout4_size_128kb;	/* 0xd04 */
	u32 security_carveout4_ca0;	/* 0xd08 */
	u32 security_carveout4_ca1;	/* 0xd0c */
	u32 security_carveout4_ca2;	/* 0xd10 */
	u32 security_carveout4_ca3;	/* 0xd14 */
	u32 security_carveout4_ca4;	/* 0xd18 */
	u32 security_carveout4_cfia0;	/* 0xd1c */
	u32 security_carveout4_cfia1;	/* 0xd20 */
	u32 security_carveout4_cfia2;	/* 0xd24 */
	u32 security_carveout4_cfia3;	/* 0xd28 */
	u32 security_carveout4_cfia4;	/* 0xd2c */
	u32 rsvd_0xd30[6];			/* 0xd30-0xd44 */

	u32 security_carveout5_cfg0;	/* 0xd48 */
	u32 security_carveout5_bom;	/* 0xd4c */
	u32 security_carveout5_bom_hi;	/* 0xd50 */
	u32 security_carveout5_size_128kb;	/* 0xd54 */
	u32 security_carveout5_ca0;	/* 0xd58 */
	u32 security_carveout5_ca1;	/* 0xd5c */
	u32 security_carveout5_ca2;	/* 0xd60 */
	u32 security_carveout5_ca3;	/* 0xd64 */
	u32 security_carveout5_ca4;	/* 0xd68 */
	u32 security_carveout5_cfia0;	/* 0xd6c */
	u32 security_carveout5_cfia1;	/* 0xd70 */
	u32 security_carveout5_cfia2;	/* 0xd74 */
	u32 security_carveout5_cfia3;	/* 0xd78 */
	u32 security_carveout5_cfia4;	/* 0xd7c */
};

void mc_enable();

#endif
