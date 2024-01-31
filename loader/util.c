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
#include "t124.h"
#include "timer.h"
#include "types.h"

//1 tick is about 1 us!
void sleep(u32 ticks)
{
	u32 start = TIMER0(TIMERUS_CNTR_1US);
	while (TIMER0(TIMERUS_CNTR_1US) - start <= ticks)
		;
}
