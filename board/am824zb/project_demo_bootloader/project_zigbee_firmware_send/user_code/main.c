/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief AM824ZB bootloader 固件发送工程
 *
 *  使用方式可参考ametal/documents/am24zb/目录下的ametal_am824zb_bootloader操作手册
 *
 * \internal
 * \par Modification history
 * - 1.00 19-03-25  yrh, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_gpio.h"
#include "am_lpc82x.h"

extern void demo_zigbee_firmware_send_entry();

/**
 * \brief AMetal 应用程序入口
 */
void am_main (void)
{
	  demo_zigbee_firmware_send_entry();

    while(1) {
    }
}

/* end of file */
