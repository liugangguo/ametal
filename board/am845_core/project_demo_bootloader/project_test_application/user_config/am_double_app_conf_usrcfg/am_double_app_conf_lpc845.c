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
 * \brief lpc845 双区应用程序用户配置文件
 * \sa am_double_app_conf_lpc845.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-3-25  yrh, first implementation
 * \endinternal
 */

#include "am_lpc845_boot_firmware_flash.h"
#include "am_boot_firmware.h"
#include "am_lpc845_boot_flash.h"
#include "am_lpc845_boot.h"

/*******************************************************************************
 * flash配置
 ******************************************************************************/
/**
 * < \brief bootloader flash 设备信息
 */
static am_lpc845_boot_flash_devinfo_t __g_flash_devinfo = {
    /** \brief flash的起始地址 */
    0,
    /** \brief flash的总的大小 */
    64 * 1024,
    /** \brief flash扇区大小 */
    1024,
    /** \brief flash扇区数 */
    64,
    /** \brief 页大小 */
    64,
    /** \brief flash寄存器的基地址 */
    //lpc845_FLASH_BASE,
    /** \brief 平台初始化函数 */
    NULL,
    /** \brief 平台初解始化函数 */
    NULL,
};

/**
 * < \brief bootloader flash 设备实例
 */
static am_lpc845_boot_flash_dev_t __g_flash_dev;

/**
 * \brief bootloader flash实例初始化，获得其标准服务句柄
 *
 * \param 无
 *
 * \return bootloader flash标准服务句柄，若为 NULL，表明初始化失败
 */
am_boot_flash_handle_t am_lpc845_boot_flash_inst_init(void)
{
    return am_lpc845_boot_flash_init(&__g_flash_dev, &__g_flash_devinfo);
}
/*******************************************************************************
 * 固件以flash的方式存储配置
 ******************************************************************************/
static am_lpc845_boot_firmware_flash_devinfo_t __g_firmware_flash_devinfo = {
    /** \brief 固件在flash中存放的起始地址 */
    0X9800,
    /** \brief 驱动存放固件缓冲区大小，也是flash最小写入的字节数，最大不可超过1024 */
    64,
    /** \brief 平台初始化函数 */
    NULL,
    /** \brief 平台解初始化函数 */
    NULL,
};

static am_lpc845_boot_firmware_flash_dev_t __g_firmware_flash_dev;

am_boot_firmware_handle_t am_lpc845_boot_firmware_flash(am_boot_flash_handle_t flash_handle)
{
    return am_lpc845_boot_firmware_flash_init (&__g_firmware_flash_dev,
                                               &__g_firmware_flash_devinfo,
                                                flash_handle);
}


/*******************************************************************************
 * 标准bootloader接口配置
 ******************************************************************************/
/**
 * < \brief bootloader标准设备信息
 */
static am_lpc845_boot_devinfo_t __g_lpc845_boot_devinfo = {
    /** \brief 应用代码起始地址*/
    0X3000,
    /**< \brief 升级标志的存放地址*/
    0X3000 - 64,
    /** \brief flash起始地址*/
    0,
    /** \brief flash大小 */
    64 * 1024,
     /** \brief 升级区地址 */
    0X9800,
    /** \brief ram起始地址 */
    0x10000000,
    /** \brief ram大小 */
    16 * 1024,
    /** \brief 平台初始化函数 */
    NULL,
    /** \brief 平台解初始化函数 */
    NULL,
};

/**
 * < \brief bootloader标准设备实例
 */
static am_lpc845_boot_dev_t __g_lpc845_boot_dev;

int am_lpc845_std_boot_inst_init(am_boot_flash_handle_t flash_handle)
{
    return am_lpc845_boot_init(&__g_lpc845_boot_dev, &__g_lpc845_boot_devinfo, flash_handle);
}
