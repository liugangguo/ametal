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
 * \brief ZLG116 bootloader 的 bootloader 工程
 *
 * - 操作步骤：
 *    参考 {sdk}\ametal\documents\am116_core目录下 zlg116 bootloader 操作手册。
 *
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
#include "am_zlg116_inst_init.h"
/**
 * \brief AMetal 应用程序入口
 */
int am_main (void)
{
    demo_am116_core_bootloader_entry();

}
