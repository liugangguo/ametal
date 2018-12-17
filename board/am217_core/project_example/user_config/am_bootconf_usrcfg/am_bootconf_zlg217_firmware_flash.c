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
 * \brief ZLG217 bootloader 固件存储flash方式 ，用户配置文件
 * \sa am_bootconf_zlg217_firmware_flash.c
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-21  yrh, first implementation
 * \endinternal
 */
#include "am_bootconf_zlg217_all_inst_init.h"
#include "am_zlg217_boot_firmware_flash.h"
#include "am_boot_firmware.h"
static am_zlg217_boot_firmware_flash_devinfo_t __g_zlg217_firmware_flash_devinfo = {
    /** \brief 固件在flash中存放的起始地址 */
    0x0800C400,
    /** \brief 驱动存放固件缓冲区大小，也是flash最小写入的字节数，最大不可超过1024 */
    4,
    /** \brief 平台初始化函数 */
    NULL,
    /** \brief 平台解初始化函数 */
    NULL,
};

static am_zlg217_boot_firmware_flash_dev_t __g_zlg217_firmware_flash_dev;

am_boot_firmware_handle_t am_zlg217_boot_firmware_flash()
{
    am_boot_flash_handle_t flash_handle = am_zlg217_boot_flash_inst_init();

    return am_zlg217_boot_firmware_flash_init (&__g_zlg217_firmware_flash_dev,
                                               &__g_zlg217_firmware_flash_devinfo,
                                                flash_handle);
}
