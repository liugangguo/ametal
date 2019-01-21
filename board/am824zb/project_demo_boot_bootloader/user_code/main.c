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
 * \brief AM824ZB 模板工程
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 17-07-07  nwt, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_led.h"
#include "demo_am824zb_entries.h"

extern void demo_am824zb_bootloader_entry (void);

/**
 * \brief AMetal 应用程序入口
 */
void am_main (void)
{

    AM_DBG_INFO("Start up successful!\r\n");

    demo_am824zb_bootloader_entry();

    while(1) {
        ;
    }
}

/* end of file */
