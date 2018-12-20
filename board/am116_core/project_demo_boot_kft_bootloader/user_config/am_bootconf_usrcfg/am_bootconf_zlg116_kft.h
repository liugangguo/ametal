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
 * \brief ZLG116 kboot KinetisFlashTool 用户配置文件
 *
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-12-13  yrh, first implementation
 * \endinternal
 */

#include "am_boot_autobaud.h"

/** \brief 自动波特率实例解初始化 */
void am_zlg116_boot_autobaud_inst_deinit (am_boot_autobaud_handle_t handle);

/** \brief 实例初始化，获得自动波特率服务句柄 */
am_boot_autobaud_handle_t am_zlg116_boot_autobaud_inst_init (void);


/**
 * \brief bootloader 标准实例初始化
 *
 *
 * \return 若为 AM_OK，表明初始化成功
 */
int am_zlg116_std_boot_inst_init();

/**
 * \brief bootloader kboot KinetisFlashTool 实例初始化
 *
 * \return 若为 AM_OK，表明初始化成功
 */
int am_zlg116_boot_kft_inst_init();
