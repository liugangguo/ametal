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
 * \brief ZLG116 例程工程
 *
 * - 操作步骤：
 *   1. 取消屏蔽需要使用的例程。
 *
 * \note
 *    同一时刻只能使用一个例程。
 *
 * \internal
 * \par Modification history
 * - 1.00 18-12-14  yrh, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_led.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "demo_am116_core_entries.h"

/**
 * \brief AMetal 应用程序入口
 */
int am_main (void)
{
    AM_DBG_INFO("Start up successful!\r\n");

    demo_am116_core_kft_bootloader_entry();

    while (1) {

    }
}
