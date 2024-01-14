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
#include "bootrom.h"
#include "types.h"
#include <string.h>
#include "usb.h"
#include "printf.h"
#include <stdarg.h>
#include <stdlib.h>



//USB Debug Support
typedef void (*bootrom_write)(void *buf, u32 len, u32 *pTxfrSize);
u32 _usb_log(char* msg){
    bootrom_write bootrom_write_ep1 = (bootrom_write) ( BOOTROM_USB_WRITE_EP1 | 1 );//'or 1' is to run in thumb mode instead of arm mode
    i32 write_len;
    u32 txfrSize=0;
    

    if (strlen(msg)>USB_MAX_TXFR_BYTES)
    {
        write_len=USB_MAX_TXFR_BYTES;
    }else{
        write_len=strlen(msg);
    }

    write_len=0x1000;
    bootrom_write_ep1(msg,write_len,&txfrSize);

    return txfrSize;
}