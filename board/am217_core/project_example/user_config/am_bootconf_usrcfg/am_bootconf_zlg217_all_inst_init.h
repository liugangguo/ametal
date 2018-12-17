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
 * \brief ZLG217 bootloader 实例初始化函数声明
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-21 yrh, first implementation
 * \endinternal
 */

#ifndef __AM_BOOTCONF_ZLG217_ALL_INST_INIT_H
#define __AM_BOOTCONF_ZLG217_ALL_INST_INIT_H
#include "am_boot_autobaud.h"
#include "am_boot.h"
#include "am_boot_flash.h"
#include "am_boot_firmware.h"
#include "am_boot_startup.h"

/**
 * \brief bootloader 标准接口实例初始化，获得其标准服务句柄
 *
 * \param 无
 *
 * \return bootloader 标准接口标准服务句柄，若为 NULL，表明初始化失败
 */
am_boot_handle_t          am_zlg217_std_boot_inst_init();

/**
 * \brief bootloader flash实例初始化，获得其标准服务句柄
 *
 * \param 无
 *
 * \return bootloader flash标准服务句柄，若为 NULL，表明初始化失败
 */
am_boot_flash_handle_t    am_zlg217_boot_flash_inst_init();

/**
 * \brief bootloader 固件存储实例初始化(flash方式)，获得其标准服务句柄
 *
 * \param 无
 *
 * \return bootloader 固件存储标准服务句柄，若为 NULL，表明初始化失败
 */
am_boot_firmware_handle_t am_zlg217_boot_firmware_flash();

/**
 * \brief bootloader 启动实例初始化，获得其标准服务句柄
 *
 * \param boot_std_handle ： BootLoader标准接口实例句柄
 *
 * \return 若为 AM_OK，表明初始化成功
 */
int                       am_zlg217_boot_startup_inst_init(am_boot_handle_t boot_std_handle);
/**
 * \brief bootloader 启动实例解初始化
 *
 * \param 无
 *
 * \return 无
 */
void                      am_zlg217_boot_startup_inst_deinit(void);

/**
 * \brief bootloader 自动波特率检测实例初始化，获得其标准服务句柄
 *
 * \param 无
 *
 * \return bootloader 自动波特率检测标准服务句柄，若为 NULL，表明初始化失败
 */
am_boot_autobaud_handle_t am_zlg217_boot_autobaud_inst_init (void);



#endif /* __AM_BOOTCONF_ZLG217_ALL_INST_INIT_H */
/* end of file */
