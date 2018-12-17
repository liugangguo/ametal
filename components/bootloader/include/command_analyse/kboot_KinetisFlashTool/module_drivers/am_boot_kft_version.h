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
 * \brief bootloader kboot KinetisFlashTool 版本管理
 *
 *
 *
 * \par 使用示例
 * \code
 *
 *
 * \endcode
 *
 * \internal
 * \par modification history:
 * - 1.00 18-12-4  yrh, first implementation.
 * \endinternal
 */
#ifndef __AM_BOOT_KFT_VERSION_H
#define __AM_BOOT_KFT_VERSION_H

/* Version constants for the bootloader */
enum bootloader_version_constants
{
    KBOOTLOADER_VERSION_NAME   = 'k',
    KBOOTLOADER_VERSION_MAJOR  = 1,
    KBOOTLOADER_VERSION_MINOR  = 0,
    KBOOTLOADER_VERSION_BUGFIX = 0
};

#endif /* __AM_BOOT_KFT_VERSION_H */

/* end of file */
