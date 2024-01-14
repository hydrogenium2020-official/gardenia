/*
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
#include "t124.h"
#include "fuse.h"
#include "printf.h"

void dump_pkc(){
    printf_("Here is your device public key\n");
    printf_("%X",FUSE(FUSE_PUBLIC_KEY0));
    printf_("%X",FUSE(FUSE_PUBLIC_KEY1));
    printf_("%X",FUSE(FUSE_PUBLIC_KEY2));
    printf_("%X",FUSE(FUSE_PUBLIC_KEY3));
    printf_("%X",FUSE(FUSE_PUBLIC_KEY4));
    printf_("%X",FUSE(FUSE_PUBLIC_KEY5));
    printf_("%X",FUSE(FUSE_PUBLIC_KEY6));
    printf_("%X",FUSE(FUSE_PUBLIC_KEY7));
    printf_("\n");
}
void fuse_disable_program()
{
	FUSE(FUSE_DISABLEREGPROGRAM) = 1;
}