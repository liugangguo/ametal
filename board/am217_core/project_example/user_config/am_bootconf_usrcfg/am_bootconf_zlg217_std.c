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
 * \brief ZLG217 bootloader 用户配置文件
 * \sa am_bootconf_zlg217.c
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-21  yrh, first implementation
 * \endinternal
 */

#include "am_zlg217_boot.h"

#include "am_boot.h"

static am_zlg217_boot_devinfo_t __g_zlg217_boot_devinfo = {
    /** \brief flash起始地址*/
    0x08000000,
    /** \brief flash大小 */
    128 * 1024,
    /** \brief ram起始地址 */
    0x20000000,
    /** \brief ram结束地址 */
    20 * 1024,
    /** \brief 平台初始化函数 */
    NULL,
    /** \brief 平台解初始化函数 */
    NULL,
};

static am_zlg217_boot_dev_t __g_zlg217_boot_dev;

am_boot_handle_t am_zlg217_std_boot_inst_init()
{
    return am_zlg217_boot_init(&__g_zlg217_boot_dev,
                               &__g_zlg217_boot_devinfo);
}

/* end of file */
