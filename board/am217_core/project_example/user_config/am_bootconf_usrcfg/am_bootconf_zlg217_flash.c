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
 * \brief ZLG217 bootloader flash 用户配置文件
 * \sa am_bootconf_zlg217_flash.c
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-21  yrh, first implementation
 * \endinternal
 */

#include "am_zlg217_boot_flash.h"
#include "am_boot_flash.h"
#include "am_zlg_flash.h"
#include "am_zlg217.h"
#include "zlg217_regbase.h"

static am_zlg217_boot_flash_devinfo_t __g_zlg217_flash_devinfo = {
    /** \brief flash的起始地址 */
    0x08000000,
    /** \brief flash的总的大小 */
    128 * 1024,
    /** \brief flash扇区大小 */
    1024,
    /** \brief flash扇区数 */
    128,
    /** \brief flash寄存器的基地址 */
    ZLG217_FLASH_BASE,
    /** \brief 平台初始化函数 */
    NULL,
    /** \brief 平台初解始化函数 */
    NULL,
};

static am_zlg217_boot_flash_dev_t __g_zlg217_flash_dev;

am_boot_flash_handle_t am_zlg217_boot_flash_inst_init()
{
    return am_boot_flash_init(&__g_zlg217_flash_dev, &__g_zlg217_flash_devinfo);
}
/* end of file */
