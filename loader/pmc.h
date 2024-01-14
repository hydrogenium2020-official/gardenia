/*
* Copyright (c) 2024 hydrogenium2020-offical
* Copyright (c) 2018 naehrwert
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
#include "types.h"
#define APBDEV_PMC_OSC_EDPD_OVER 0x1a4
#define APBDEV_PMC_CNTRL2 0x440
#define APBDEV_PMC_TSC_MULT 0x2B4

#define  PMC_OSC_EDPD_OVER_OSC_CTRL_OVER   BIT(22)
#define  PMC_CNTRL2_HOLD_CKE_LOW_EN        BIT(12)