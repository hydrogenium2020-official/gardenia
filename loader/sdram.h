/*
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
#ifndef _T124_SDRAM_H_
#define _T124_SDRAM_H_

#include "types.h"

#define MEMORY_TYPE_NONE   0
#define MEMORY_TYPE_DDR    0
#define MEMORY_TYPE_LPDDR  0
#define MEMORY_TYPE_DDR2   0
#define MEMORY_TYPE_LPDDR2 1
#define MEMORY_TYPE_DDR3  2

enum {
	BOOT_ROM_PATCH_CONTROL_ENABLE_MASK = 0x1 << 31,
	BOOT_ROM_PATCH_CONTROL_OFFSET_SHIFT = 0,
	BOOT_ROM_PATCH_CONTROL_OFFSET_MASK = 0x7FFFFFFF << 0,
	BOOT_ROM_PATCH_CONTROL_BASE_ADDRESS = 0x70000000,

	EMC_ZCAL_WARM_COLD_BOOT_ENABLES_COLDBOOT_MASK = 1 << 0,
};

/**
 * Defines the SDRAM parameter structure
 */
typedef struct _sdram_params_t124 {

	/* Specifies the type of memory device */
	u32 MemoryType;

	/* MC/EMC clock source configuration */

	/* Specifies the M value for PllM */
	u32 PllMInputDivider;
	/* Specifies the N value for PllM */
	u32 PllMFeedbackDivider;
	/* Specifies the time to wait for PLLM to lock (in microseconds) */
	u32 PllMStableTime;
	/* Specifies misc. control bits */
	u32 PllMSetupControl;
	/* Enables the Div by 2 */
	u32 PllMSelectDiv2;
	/* Powers down VCO output Level shifter */
	u32 PllMPDLshiftPh45;
	/* Powers down VCO output Level shifter */
	u32 PllMPDLshiftPh90;
	/* Powers down VCO output Level shifter */
	u32 PllMPDLshiftPh135;
	/* Specifies value for Charge Pump Gain Control */
	u32 PllMKCP;
	/* Specifies VCO gain */
	u32 PllMKVCO;
	/* Spare BCT param */
	u32 EmcBctSpare0;
	/* Spare BCT param */
	u32 EmcBctSpare1;
	/* Spare BCT param */
	u32 EmcBctSpare2;
	/* Spare BCT param */
	u32 EmcBctSpare3;
	/* Spare BCT param */
	u32 EmcBctSpare4;
	/* Spare BCT param */
	u32 EmcBctSpare5;
	/* Spare BCT param */
	u32 EmcBctSpare6;
	/* Spare BCT param */
	u32 EmcBctSpare7;
	/* Spare BCT param */
	u32 EmcBctSpare8;
	/* Spare BCT param */
	u32 EmcBctSpare9;
	/* Spare BCT param */
	u32 EmcBctSpare10;
	/* Spare BCT param */
	u32 EmcBctSpare11;
	/* Defines EMC_2X_CLK_SRC, EMC_2X_CLK_DIVISOR, EMC_INVERT_DCD */
	u32 EmcClockSource;

	/* Auto-calibration of EMC pads */

	/* Specifies the value for EMC_AUTO_CAL_INTERVAL */
	u32 EmcAutoCalInterval;
	/*
	 * Specifies the value for EMC_AUTO_CAL_CONFIG
	 * Note: Trigger bits are set by the SDRAM code.
	 */
	u32 EmcAutoCalConfig;

	/* Specifies the value for EMC_AUTO_CAL_CONFIG2 */
	u32 EmcAutoCalConfig2;

	/* Specifies the value for EMC_AUTO_CAL_CONFIG3 */
	u32 EmcAutoCalConfig3;

	/*
	 * Specifies the time for the calibration
	 * to stabilize (in microseconds)
	 */
	u32 EmcAutoCalWait;

	/*
	 * DRAM size information
	 * Specifies the value for EMC_ADR_CFG
	 */
	u32 EmcAdrCfg;

	/*
	 * Specifies the time to wait after asserting pin
	 * CKE (in microseconds)
	 */
	u32 EmcPinProgramWait;
	/* Specifies the extra delay before/after pin RESET/CKE command */
	u32 EmcPinExtraWait;
	/*
	 * Specifies the extra delay after the first writing
	 * of EMC_TIMING_CONTROL
	 */
	u32 EmcTimingControlWait;

	/* Timing parameters required for the SDRAM */

	/* Specifies the value for EMC_RC */
	u32 EmcRc;
	/* Specifies the value for EMC_RFC */
	u32 EmcRfc;
	/* Specifies the value for EMC_RFC_SLR */
	u32 EmcRfcSlr;
	/* Specifies the value for EMC_RAS */
	u32 EmcRas;
	/* Specifies the value for EMC_RP */
	u32 EmcRp;
	/* Specifies the value for EMC_R2R */
	u32 EmcR2r;
	/* Specifies the value for EMC_W2W */
	u32 EmcW2w;
	/* Specifies the value for EMC_R2W */
	u32 EmcR2w;
	/* Specifies the value for EMC_W2R */
	u32 EmcW2r;
	/* Specifies the value for EMC_R2P */
	u32 EmcR2p;
	/* Specifies the value for EMC_W2P */
	u32 EmcW2p;
	/* Specifies the value for EMC_RD_RCD */
	u32 EmcRdRcd;
	/* Specifies the value for EMC_WR_RCD */
	u32 EmcWrRcd;
	/* Specifies the value for EMC_RRD */
	u32 EmcRrd;
	/* Specifies the value for EMC_REXT */
	u32 EmcRext;
	/* Specifies the value for EMC_WEXT */
	u32 EmcWext;
	/* Specifies the value for EMC_WDV */
	u32 EmcWdv;
	/* Specifies the value for EMC_WDV_MASK */
	u32 EmcWdvMask;
	/* Specifies the value for EMC_QUSE */
	u32 EmcQUse;
	/* Specifies the value for EMC_QUSE_WIDTH */
	u32 EmcQuseWidth;
	/* Specifies the value for EMC_IBDLY */
	u32 EmcIbdly;
	/* Specifies the value for EMC_EINPUT */
	u32 EmcEInput;
	/* Specifies the value for EMC_EINPUT_DURATION */
	u32 EmcEInputDuration;
	/* Specifies the value for EMC_PUTERM_EXTRA */
	u32 EmcPutermExtra;
	/* Specifies the value for EMC_PUTERM_WIDTH */
	u32 EmcPutermWidth;
	/* Specifies the value for EMC_PUTERM_ADJ */
	u32 EmcPutermAdj;
	/* Specifies the value for EMC_CDB_CNTL_1 */
	u32 EmcCdbCntl1;
	/* Specifies the value for EMC_CDB_CNTL_2 */
	u32 EmcCdbCntl2;
	/* Specifies the value for EMC_CDB_CNTL_3 */
	u32 EmcCdbCntl3;
	/* Specifies the value for EMC_QRST */
	u32 EmcQRst;
	/* Specifies the value for EMC_QSAFE */
	u32 EmcQSafe;
	/* Specifies the value for EMC_RDV */
	u32 EmcRdv;
	/* Specifies the value for EMC_RDV_MASK */
	u32 EmcRdvMask;
	/* Specifies the value for EMC_QPOP */
	u32 EmcQpop;
	/* Specifies the value for EMC_CTT */
	u32 EmcCtt;
	/* Specifies the value for EMC_CTT_DURATION */
	u32 EmcCttDuration;
	/* Specifies the value for EMC_REFRESH */
	u32 EmcRefresh;
	/* Specifies the value for EMC_BURST_REFRESH_NUM */
	u32 EmcBurstRefreshNum;
	/* Specifies the value for EMC_PRE_REFRESH_REQ_CNT */
	u32 EmcPreRefreshReqCnt;
	/* Specifies the value for EMC_PDEX2WR */
	u32 EmcPdEx2Wr;
	/* Specifies the value for EMC_PDEX2RD */
	u32 EmcPdEx2Rd;
	/* Specifies the value for EMC_PCHG2PDEN */
	u32 EmcPChg2Pden;
	/* Specifies the value for EMC_ACT2PDEN */
	u32 EmcAct2Pden;
	/* Specifies the value for EMC_AR2PDEN */
	u32 EmcAr2Pden;
	/* Specifies the value for EMC_RW2PDEN */
	u32 EmcRw2Pden;
	/* Specifies the value for EMC_TXSR */
	u32 EmcTxsr;
	/* Specifies the value for EMC_TXSRDLL */
	u32 EmcTxsrDll;
	/* Specifies the value for EMC_TCKE */
	u32 EmcTcke;
	/* Specifies the value for EMC_TCKESR */
	u32 EmcTckesr;
	/* Specifies the value for EMC_TPD */
	u32 EmcTpd;
	/* Specifies the value for EMC_TFAW */
	u32 EmcTfaw;
	/* Specifies the value for EMC_TRPAB */
	u32 EmcTrpab;
	/* Specifies the value for EMC_TCLKSTABLE */
	u32 EmcTClkStable;
	/* Specifies the value for EMC_TCLKSTOP */
	u32 EmcTClkStop;
	/* Specifies the value for EMC_TREFBW */
	u32 EmcTRefBw;

	/* FBIO configuration values */

	/* Specifies the value for EMC_FBIO_CFG5 */
	u32 EmcFbioCfg5;
	/* Specifies the value for EMC_FBIO_CFG6 */
	u32 EmcFbioCfg6;
	/* Specifies the value for EMC_FBIO_SPARE */
	u32 EmcFbioSpare;

	/* Specifies the value for EMC_CFG_RSV */
	u32 EmcCfgRsv;

	/* MRS command values */

	/* Specifies the value for EMC_MRS */
	u32 EmcMrs;
	/* Specifies the MP0 command to initialize mode registers */
	u32 EmcEmrs;
	/* Specifies the MP2 command to initialize mode registers */
	u32 EmcEmrs2;
	/* Specifies the MP3 command to initialize mode registers */
	u32 EmcEmrs3;
	/* Specifies the programming to LPDDR2 Mode Register 1 at cold boot */
	u32 EmcMrw1;
	/* Specifies the programming to LPDDR2 Mode Register 2 at cold boot */
	u32 EmcMrw2;
	/* Specifies the programming to LPDDR2 Mode Register 3 at cold boot */
	u32 EmcMrw3;
	/* Specifies the programming to LPDDR2 Mode Register 11 at cold boot */
	u32 EmcMrw4;
	/*
	 * Specifies the programming to extra LPDDR2 Mode Register
	 * at cold boot
	 */
	u32 EmcMrwExtra;
	/*
	 * Specifies the programming to extra LPDDR2 Mode Register
	 * at warm boot
	 */
	u32 EmcWarmBootMrwExtra;
	/*
	 * Specify the enable of extra Mode Register programming at
	 * warm boot
	 */
	u32 EmcWarmBootExtraModeRegWriteEnable;
	/*
	 * Specify the enable of extra Mode Register programming at
	 * cold boot
	 */
	u32 EmcExtraModeRegWriteEnable;

	/* Specifies the EMC_MRW reset command value */
	u32 EmcMrwResetCommand;
	/* Specifies the EMC Reset wait time (in microseconds) */
	u32 EmcMrwResetNInitWait;
	/* Specifies the value for EMC_MRS_WAIT_CNT */
	u32 EmcMrsWaitCnt;
	/* Specifies the value for EMC_MRS_WAIT_CNT2 */
	u32 EmcMrsWaitCnt2;

	/* EMC miscellaneous configurations */

	/* Specifies the value for EMC_CFG */
	u32 EmcCfg;
	/* Specifies the value for EMC_CFG_2 */
	u32 EmcCfg2;
	/* Specifies the pipe bypass controls */
	u32 EmcCfgPipe;
	/* Specifies the value for EMC_DBG */
	u32 EmcDbg;
	/* Specifies the value for EMC_CMDQ */
	u32 EmcCmdQ;
	/* Specifies the value for EMC_MC2EMCQ */
	u32 EmcMc2EmcQ;
	/* Specifies the value for EMC_DYN_SELF_REF_CONTROL */
	u32 EmcDynSelfRefControl;

	/* Specifies the value for MEM_INIT_DONE */
	u32 AhbArbitrationXbarCtrlMemInitDone;

	/* Specifies the value for EMC_CFG_DIG_DLL */
	u32 EmcCfgDigDll;
	/* Specifies the value for EMC_CFG_DIG_DLL_PERIOD */
	u32 EmcCfgDigDllPeriod;
	/* Specifies the value of *DEV_SELECTN of various EMC registers */
	u32 EmcDevSelect;

	/* Specifies the value for EMC_SEL_DPD_CTRL */
	u32 EmcSelDpdCtrl;

	/* Pads trimmer delays */

	/* Specifies the value for EMC_DLL_XFORM_DQS0 */
	u32 EmcDllXformDqs0;
	/* Specifies the value for EMC_DLL_XFORM_DQS1 */
	u32 EmcDllXformDqs1;
	/* Specifies the value for EMC_DLL_XFORM_DQS2 */
	u32 EmcDllXformDqs2;
	/* Specifies the value for EMC_DLL_XFORM_DQS3 */
	u32 EmcDllXformDqs3;
	/* Specifies the value for EMC_DLL_XFORM_DQS4 */
	u32 EmcDllXformDqs4;
	/* Specifies the value for EMC_DLL_XFORM_DQS5 */
	u32 EmcDllXformDqs5;
	/* Specifies the value for EMC_DLL_XFORM_DQS6 */
	u32 EmcDllXformDqs6;
	/* Specifies the value for EMC_DLL_XFORM_DQS7 */
	u32 EmcDllXformDqs7;
	/* Specifies the value for EMC_DLL_XFORM_DQS8 */
	u32 EmcDllXformDqs8;
	/* Specifies the value for EMC_DLL_XFORM_DQS9 */
	u32 EmcDllXformDqs9;
	/* Specifies the value for EMC_DLL_XFORM_DQS10 */
	u32 EmcDllXformDqs10;
	/* Specifies the value for EMC_DLL_XFORM_DQS11 */
	u32 EmcDllXformDqs11;
	/* Specifies the value for EMC_DLL_XFORM_DQS12 */
	u32 EmcDllXformDqs12;
	/* Specifies the value for EMC_DLL_XFORM_DQS13 */
	u32 EmcDllXformDqs13;
	/* Specifies the value for EMC_DLL_XFORM_DQS14 */
	u32 EmcDllXformDqs14;
	/* Specifies the value for EMC_DLL_XFORM_DQS15 */
	u32 EmcDllXformDqs15;
	/* Specifies the value for EMC_DLL_XFORM_QUSE0 */
	u32 EmcDllXformQUse0;
	/* Specifies the value for EMC_DLL_XFORM_QUSE1 */
	u32 EmcDllXformQUse1;
	/* Specifies the value for EMC_DLL_XFORM_QUSE2 */
	u32 EmcDllXformQUse2;
	/* Specifies the value for EMC_DLL_XFORM_QUSE3 */
	u32 EmcDllXformQUse3;
	/* Specifies the value for EMC_DLL_XFORM_QUSE4 */
	u32 EmcDllXformQUse4;
	/* Specifies the value for EMC_DLL_XFORM_QUSE5 */
	u32 EmcDllXformQUse5;
	/* Specifies the value for EMC_DLL_XFORM_QUSE6 */
	u32 EmcDllXformQUse6;
	/* Specifies the value for EMC_DLL_XFORM_QUSE7 */
	u32 EmcDllXformQUse7;
	/* Specifies the value for EMC_DLL_XFORM_ADDR0 */
	u32 EmcDllXformAddr0;
	/* Specifies the value for EMC_DLL_XFORM_ADDR1 */
	u32 EmcDllXformAddr1;
	/* Specifies the value for EMC_DLL_XFORM_ADDR2 */
	u32 EmcDllXformAddr2;
	/* Specifies the value for EMC_DLL_XFORM_ADDR3 */
	u32 EmcDllXformAddr3;
	/* Specifies the value for EMC_DLL_XFORM_ADDR4 */
	u32 EmcDllXformAddr4;
	/* Specifies the value for EMC_DLL_XFORM_ADDR5 */
	u32 EmcDllXformAddr5;
	/* Specifies the value for EMC_DLL_XFORM_QUSE8 */
	u32 EmcDllXformQUse8;
	/* Specifies the value for EMC_DLL_XFORM_QUSE9 */
	u32 EmcDllXformQUse9;
	/* Specifies the value for EMC_DLL_XFORM_QUSE10 */
	u32 EmcDllXformQUse10;
	/* Specifies the value for EMC_DLL_XFORM_QUSE11 */
	u32 EmcDllXformQUse11;
	/* Specifies the value for EMC_DLL_XFORM_QUSE12 */
	u32 EmcDllXformQUse12;
	/* Specifies the value for EMC_DLL_XFORM_QUSE13 */
	u32 EmcDllXformQUse13;
	/* Specifies the value for EMC_DLL_XFORM_QUSE14 */
	u32 EmcDllXformQUse14;
	/* Specifies the value for EMC_DLL_XFORM_QUSE15 */
	u32 EmcDllXformQUse15;
	/* Specifies the value for EMC_DLI_TRIM_TXDQS0 */
	u32 EmcDliTrimTxDqs0;
	/* Specifies the value for EMC_DLI_TRIM_TXDQS1 */
	u32 EmcDliTrimTxDqs1;
	/* Specifies the value for EMC_DLI_TRIM_TXDQS2 */
	u32 EmcDliTrimTxDqs2;
	/* Specifies the value for EMC_DLI_TRIM_TXDQS3 */
	u32 EmcDliTrimTxDqs3;
	/* Specifies the value for EMC_DLI_TRIM_TXDQS4 */
	u32 EmcDliTrimTxDqs4;
	/* Specifies the value for EMC_DLI_TRIM_TXDQS5 */
	u32 EmcDliTrimTxDqs5;
	/* Specifies the value for EMC_DLI_TRIM_TXDQS6 */
	u32 EmcDliTrimTxDqs6;
	/* Specifies the value for EMC_DLI_TRIM_TXDQS7 */
	u32 EmcDliTrimTxDqs7;
	/* Specifies the value for EMC_DLI_TRIM_TXDQS8 */
	u32 EmcDliTrimTxDqs8;
	/* Specifies the value for EMC_DLI_TRIM_TXDQS9 */
	u32 EmcDliTrimTxDqs9;
	/* Specifies the value for EMC_DLI_TRIM_TXDQS10 */
	u32 EmcDliTrimTxDqs10;
	/* Specifies the value for EMC_DLI_TRIM_TXDQS11 */
	u32 EmcDliTrimTxDqs11;
	/* Specifies the value for EMC_DLI_TRIM_TXDQS12 */
	u32 EmcDliTrimTxDqs12;
	/* Specifies the value for EMC_DLI_TRIM_TXDQS13 */
	u32 EmcDliTrimTxDqs13;
	/* Specifies the value for EMC_DLI_TRIM_TXDQS14 */
	u32 EmcDliTrimTxDqs14;
	/* Specifies the value for EMC_DLI_TRIM_TXDQS15 */
	u32 EmcDliTrimTxDqs15;
	/* Specifies the value for EMC_DLL_XFORM_DQ0 */
	u32 EmcDllXformDq0;
	/* Specifies the value for EMC_DLL_XFORM_DQ1 */
	u32 EmcDllXformDq1;
	/* Specifies the value for EMC_DLL_XFORM_DQ2 */
	u32 EmcDllXformDq2;
	/* Specifies the value for EMC_DLL_XFORM_DQ3 */
	u32 EmcDllXformDq3;
	/* Specifies the value for EMC_DLL_XFORM_DQ4 */
	u32 EmcDllXformDq4;
	/* Specifies the value for EMC_DLL_XFORM_DQ5 */
	u32 EmcDllXformDq5;
	/* Specifies the value for EMC_DLL_XFORM_DQ6 */
	u32 EmcDllXformDq6;
	/* Specifies the value for EMC_DLL_XFORM_DQ7 */
	u32 EmcDllXformDq7;

	/*
	 * Specifies the delay after asserting CKE pin during a WarmBoot0
	 * sequence (in microseconds)
	 */
	u32 WarmBootWait;

	/* Specifies the value for EMC_CTT_TERM_CTRL */
	u32 EmcCttTermCtrl;

	/* Specifies the value for EMC_ODT_WRITE */
	u32 EmcOdtWrite;
	/* Specifies the value for EMC_ODT_WRITE */
	u32 EmcOdtRead;

	/* Periodic ZQ calibration */

	/*
	 * Specifies the value for EMC_ZCAL_INTERVAL
	 * Value 0 disables ZQ calibration
	 */
	u32 EmcZcalInterval;
	/* Specifies the value for EMC_ZCAL_WAIT_CNT */
	u32 EmcZcalWaitCnt;
	/* Specifies the value for EMC_ZCAL_MRW_CMD */
	u32 EmcZcalMrwCmd;

	/* DRAM initialization sequence flow control */

	/* Specifies the MRS command value for resetting DLL */
	u32 EmcMrsResetDll;
	/* Specifies the command for ZQ initialization of device 0 */
	u32 EmcZcalInitDev0;
	/* Specifies the command for ZQ initialization of device 1 */
	u32 EmcZcalInitDev1;
	/*
	 * Specifies the wait time after programming a ZQ initialization
	 * command (in microseconds)
	 */
	u32 EmcZcalInitWait;
	/*
	 * Specifies the enable for ZQ calibration at cold boot [bit 0]
	 * and warm boot [bit 1]
	 */
	u32 EmcZcalWarmColdBootEnables;

	/*
	 * Specifies the MRW command to LPDDR2 for ZQ calibration
	 * on warmboot
	 */
	/* Is issued to both devices separately */
	u32 EmcMrwLpddr2ZcalWarmBoot;
	/*
	 * Specifies the ZQ command to DDR3 for ZQ calibration on warmboot
	 * Is issued to both devices separately
	 */
	u32 EmcZqCalDdr3WarmBoot;
	/*
	 * Specifies the wait time for ZQ calibration on warmboot
	 * (in microseconds)
	 */
	u32 EmcZcalWarmBootWait;
	/*
	 * Specifies the enable for DRAM Mode Register programming
	 * at warm boot
	 */
	u32 EmcMrsWarmBootEnable;
	/*
	 * Specifies the wait time after sending an MRS DLL reset command
	 * in microseconds)
	 */
	u32 EmcMrsResetDllWait;
	/* Specifies the extra MRS command to initialize mode registers */
	u32 EmcMrsExtra;
	/* Specifies the extra MRS command at warm boot */
	u32 EmcWarmBootMrsExtra;
	/* Specifies the EMRS command to enable the DDR2 DLL */
	u32 EmcEmrsDdr2DllEnable;
	/* Specifies the MRS command to reset the DDR2 DLL */
	u32 EmcMrsDdr2DllReset;
	/* Specifies the EMRS command to set OCD calibration */
	u32 EmcEmrsDdr2OcdCalib;
	/*
	 * Specifies the wait between initializing DDR and setting OCD
	 * calibration (in microseconds)
	 */
	u32 EmcDdr2Wait;
	/* Specifies the value for EMC_CLKEN_OVERRIDE */
	u32 EmcClkenOverride;
	/* Specifies the value for MC_DIS_EXTRA_SNAP_LEVELS */
	u32 McDisExtraSnapLevels;
	/*
	 * Specifies LOG2 of the extra refresh numbers after booting
	 * Program 0 to disable
	 */
	u32 EmcExtraRefreshNum;
	/* Specifies the master override for all EMC clocks */
	u32 EmcClkenOverrideAllWarmBoot;
	/* Specifies the master override for all MC clocks */
	u32 McClkenOverrideAllWarmBoot;
	/* Specifies digital dll period, choosing between 4 to 64 ms */
	u32 EmcCfgDigDllPeriodWarmBoot;

	/* Pad controls */

	/* Specifies the value for PMC_VDDP_SEL */
	u32 PmcVddpSel;
	/* Specifies the wait time after programming PMC_VDDP_SEL */
	u32 PmcVddpSelWait;
	/* Specifies the value for PMC_DDR_PWR */
	u32 PmcDdrPwr;
	/* Specifies the value for PMC_DDR_CFG */
	u32 PmcDdrCfg;
	/* Specifies the value for PMC_IO_DPD3_REQ */
	u32 PmcIoDpd3Req;
	/* Specifies the wait time after programming PMC_IO_DPD3_REQ */
	u32 PmcIoDpd3ReqWait;
	/* Specifies the value for PMC_REG_SHORT */
	u32 PmcRegShort;
	/* Specifies the value for PMC_NO_IOPOWER */
	u32 PmcNoIoPower;
	/* Specifies the wait time after programming PMC_POR_DPD_CTRL */
	u32 PmcPorDpdCtrlWait;
	/* Specifies the value for EMC_XM2CMDPADCTRL */
	u32 EmcXm2CmdPadCtrl;
	/* Specifies the value for EMC_XM2CMDPADCTRL2 */
	u32 EmcXm2CmdPadCtrl2;
	/* Specifies the value for EMC_XM2CMDPADCTRL3 */
	u32 EmcXm2CmdPadCtrl3;
	/* Specifies the value for EMC_XM2CMDPADCTRL4 */
	u32 EmcXm2CmdPadCtrl4;
	/* Specifies the value for EMC_XM2CMDPADCTRL5 */
	u32 EmcXm2CmdPadCtrl5;
	/* Specifies the value for EMC_XM2DQSPADCTRL */
	u32 EmcXm2DqsPadCtrl;
	/* Specifies the value for EMC_XM2DQSPADCTRL2 */
	u32 EmcXm2DqsPadCtrl2;
	/* Specifies the value for EMC_XM2DQSPADCTRL3 */
	u32 EmcXm2DqsPadCtrl3;
	/* Specifies the value for EMC_XM2DQSPADCTRL4 */
	u32 EmcXm2DqsPadCtrl4;
	/* Specifies the value for EMC_XM2DQSPADCTRL5 */
	u32 EmcXm2DqsPadCtrl5;
	/* Specifies the value for EMC_XM2DQSPADCTRL6 */
	u32 EmcXm2DqsPadCtrl6;
	/* Specifies the value for EMC_XM2DQPADCTRL */
	u32 EmcXm2DqPadCtrl;
	/* Specifies the value for EMC_XM2DQPADCTRL2 */
	u32 EmcXm2DqPadCtrl2;
	/* Specifies the value for EMC_XM2DQPADCTRL3 */
	u32 EmcXm2DqPadCtrl3;
	/* Specifies the value for EMC_XM2CLKPADCTRL */
	u32 EmcXm2ClkPadCtrl;
	/* Specifies the value for EMC_XM2CLKPADCTRL2 */
	u32 EmcXm2ClkPadCtrl2;
	/* Specifies the value for EMC_XM2COMPPADCTRL */
	u32 EmcXm2CompPadCtrl;
	/* Specifies the value for EMC_XM2VTTGENPADCTRL */
	u32 EmcXm2VttGenPadCtrl;
	/* Specifies the value for EMC_XM2VTTGENPADCTRL2 */
	u32 EmcXm2VttGenPadCtrl2;
	/* Specifies the value for EMC_XM2VTTGENPADCTRL3 */
	u32 EmcXm2VttGenPadCtrl3;
	/* Specifies the value for EMC_ACPD_CONTROL */
	u32 EmcAcpdControl;

	/* Specifies the value for EMC_SWIZZLE_RANK0_BYTE_CFG */
	u32 EmcSwizzleRank0ByteCfg;
	/* Specifies the value for EMC_SWIZZLE_RANK0_BYTE0 */
	u32 EmcSwizzleRank0Byte0;
	/* Specifies the value for EMC_SWIZZLE_RANK0_BYTE1 */
	u32 EmcSwizzleRank0Byte1;
	/* Specifies the value for EMC_SWIZZLE_RANK0_BYTE2 */
	u32 EmcSwizzleRank0Byte2;
	/* Specifies the value for EMC_SWIZZLE_RANK0_BYTE3 */
	u32 EmcSwizzleRank0Byte3;
	/* Specifies the value for EMC_SWIZZLE_RANK1_BYTE_CFG */
	u32 EmcSwizzleRank1ByteCfg;
	/* Specifies the value for EMC_SWIZZLE_RANK1_BYTE0 */
	u32 EmcSwizzleRank1Byte0;
	/* Specifies the value for EMC_SWIZZLE_RANK1_BYTE1 */
	u32 EmcSwizzleRank1Byte1;
	/* Specifies the value for EMC_SWIZZLE_RANK1_BYTE2 */
	u32 EmcSwizzleRank1Byte2;
	/* Specifies the value for EMC_SWIZZLE_RANK1_BYTE3 */
	u32 EmcSwizzleRank1Byte3;

	/* Specifies the value for EMC_DSR_VTTGEN_DRV */
	u32 EmcDsrVttgenDrv;

	/* Specifies the value for EMC_TXDSRVTTGEN */
	u32 EmcTxdsrvttgen;
	/* Specifies the value for EMC_BGBIAS_CTL */
	u32 EmcBgbiasCtl0;

	/* DRAM size information */

	/* Specifies the value for MC_EMEM_ADR_CFG */
	u32 McEmemAdrCfg;
	/* Specifies the value for MC_EMEM_ADR_CFG_DEV0 */
	u32 McEmemAdrCfgDev0;
	/* Specifies the value for MC_EMEM_ADR_CFG_DEV1 */
	u32 McEmemAdrCfgDev1;
	/* Specifies the value for MC_EMEM_BANK_SWIZZLE_CFG0 */
	u32 McEmemAdrCfgBankMask0;
	/* Specifies the value for MC_EMEM_BANK_SWIZZLE_CFG1 */
	u32 McEmemAdrCfgBankMask1;
	/* Specifies the value for MC_EMEM_BANK_SWIZZLE_CFG2 */
	u32 McEmemAdrCfgBankMask2;
	/* Specifies the value for MC_EMEM_BANK_SWIZZLE_CFG3 */
	u32 McEmemAdrCfgBankSwizzle3;

	/*
	 * Specifies the value for MC_EMEM_CFG which holds the external memory
	 * size (in KBytes)
	 */
	u32 McEmemCfg;

	/* MC arbitration configuration */

	/* Specifies the value for MC_EMEM_ARB_CFG */
	u32 McEmemArbCfg;
	/* Specifies the value for MC_EMEM_ARB_OUTSTANDING_REQ */
	u32 McEmemArbOutstandingReq;
	/* Specifies the value for MC_EMEM_ARB_TIMING_RCD */
	u32 McEmemArbTimingRcd;
	/* Specifies the value for MC_EMEM_ARB_TIMING_RP */
	u32 McEmemArbTimingRp;
	/* Specifies the value for MC_EMEM_ARB_TIMING_RC */
	u32 McEmemArbTimingRc;
	/* Specifies the value for MC_EMEM_ARB_TIMING_RAS */
	u32 McEmemArbTimingRas;
	/* Specifies the value for MC_EMEM_ARB_TIMING_FAW */
	u32 McEmemArbTimingFaw;
	/* Specifies the value for MC_EMEM_ARB_TIMING_RRD */
	u32 McEmemArbTimingRrd;
	/* Specifies the value for MC_EMEM_ARB_TIMING_RAP2PRE */
	u32 McEmemArbTimingRap2Pre;
	/* Specifies the value for MC_EMEM_ARB_TIMING_WAP2PRE */
	u32 McEmemArbTimingWap2Pre;
	/* Specifies the value for MC_EMEM_ARB_TIMING_R2R */
	u32 McEmemArbTimingR2R;
	/* Specifies the value for MC_EMEM_ARB_TIMING_W2W */
	u32 McEmemArbTimingW2W;
	/* Specifies the value for MC_EMEM_ARB_TIMING_R2W */
	u32 McEmemArbTimingR2W;
	/* Specifies the value for MC_EMEM_ARB_TIMING_W2R */
	u32 McEmemArbTimingW2R;
	/* Specifies the value for MC_EMEM_ARB_DA_TURNS */
	u32 McEmemArbDaTurns;
	/* Specifies the value for MC_EMEM_ARB_DA_COVERS */
	u32 McEmemArbDaCovers;
	/* Specifies the value for MC_EMEM_ARB_MISC0 */
	u32 McEmemArbMisc0;
	/* Specifies the value for MC_EMEM_ARB_MISC1 */
	u32 McEmemArbMisc1;
	/* Specifies the value for MC_EMEM_ARB_RING1_THROTTLE */
	u32 McEmemArbRing1Throttle;
	/* Specifies the value for MC_EMEM_ARB_OVERRIDE */
	u32 McEmemArbOverride;
	/* Specifies the value for MC_EMEM_ARB_OVERRIDE_1 */
	u32 McEmemArbOverride1;
	/* Specifies the value for MC_EMEM_ARB_RSV */
	u32 McEmemArbRsv;

	/* Specifies the value for MC_CLKEN_OVERRIDE */
	u32 McClkenOverride;

	/* Specifies the value for MC_STAT_CONTROL */
	u32 McStatControl;
	/* Specifies the value for MC_DISPLAY_SNAP_RING */
	u32 McDisplaySnapRing;
	/* Specifies the value for MC_VIDEO_PROTECT_BOM */
	u32 McVideoProtectBom;
	/* Specifies the value for MC_VIDEO_PROTECT_BOM_ADR_HI */
	u32 McVideoProtectBomAdrHi;
	/* Specifies the value for MC_VIDEO_PROTECT_SIZE_MB */
	u32 McVideoProtectSizeMb;
	/* Specifies the value for MC_VIDEO_PROTECT_VPR_OVERRIDE */
	u32 McVideoProtectVprOverride;
	/* Specifies the value for MC_VIDEO_PROTECT_VPR_OVERRIDE1 */
	u32 McVideoProtectVprOverride1;
	/* Specifies the value for MC_VIDEO_PROTECT_GPU_OVERRIDE_0 */
	u32 McVideoProtectGpuOverride0;
	/* Specifies the value for MC_VIDEO_PROTECT_GPU_OVERRIDE_1 */
	u32 McVideoProtectGpuOverride1;
	/* Specifies the value for MC_SEC_CARVEOUT_BOM */
	u32 McSecCarveoutBom;
	/* Specifies the value for MC_SEC_CARVEOUT_ADR_HI */
	u32 McSecCarveoutAdrHi;
	/* Specifies the value for MC_SEC_CARVEOUT_SIZE_MB */
	u32 McSecCarveoutSizeMb;
	/* Specifies the value for MC_VIDEO_PROTECT_REG_CTRL.VIDEO_PROTECT_WRITE_ACCESS */
	u32 McVideoProtectWriteAccess;
	/* Specifies the value for MC_SEC_CARVEOUT_REG_CTRL.SEC_CARVEOUT_WRITE_ACCESS */
	u32 McSecCarveoutProtectWriteAccess;

	/* Specifies enable for CA training */
	u32 EmcCaTrainingEnable;
	/* Specifies the value for EMC_CA_TRAINING_TIMING_CNTRL1 */
	u32 EmcCaTrainingTimingCntl1;
	/* Specifies the value for EMC_CA_TRAINING_TIMING_CNTRL2 */
	u32 EmcCaTrainingTimingCntl2;
	/* Set if bit 6 select is greater than bit 7 select; uses aremc.spec packet SWIZZLE_BIT6_GT_BIT7 */
	u32 SwizzleRankByteEncode;
	/* Specifies enable and offset for patched boot ROM write */
	u32 BootRomPatchControl;
	/* Specifies data for patched boot ROM write */
	u32 BootRomPatchData;
	/* Specifies the value for MC_MTS_CARVEOUT_BOM */
	u32 McMtsCarveoutBom;
	/* Specifies the value for MC_MTS_CARVEOUT_ADR_HI */
	u32 McMtsCarveoutAdrHi;
	/* Specifies the value for MC_MTS_CARVEOUT_SIZE_MB */
	u32 McMtsCarveoutSizeMb;
	/* Specifies the value for MC_MTS_CARVEOUT_REG_CTRL */
	u32 McMtsCarveoutRegCtrl;

	/* End of generated code by warmboot_code_gen */
}sdram_params_t124;


void sdram_init();
void * sdram_get_params_t124();

#endif
