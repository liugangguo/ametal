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
 * \brief bootloader kboot KinetisFlashTool 总初始化实现
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-25  yrh, first implementation
 * \endinternal
 */
#include "am_boot_kft.h"
#include "am_boot_kft_serial_packet.h"
#include "am_boot_flash_memory.h"
#include "am_arm_nvic.h"

static am_boot_kft_dev_t *__gp_boot_kft_dev;

/**
 * \brief bootloader 组件初始化
 */
int am_boot_kft_init(am_boot_kft_dev_t      *p_dev,
                     am_boot_kft_dev_info_t *p_devinfo,
                     am_boot_flash_handle_t  flash_handle,
                     am_boot_serial_handle_t serial_handle)
{
    if(p_devinfo == NULL || p_dev == NULL) {
        return -AM_ENXIO;
    }
    p_dev->p_dev_info = p_devinfo;

    am_boot_mem_handle_t memory_handle = am_boot_flash_mem_init(flash_handle);
    am_boot_kft_property_devinfo_t porperty_devifo;
    porperty_devifo.app_start_addr   = p_devinfo->app_start_addr;
    porperty_devifo.flash_size       = p_devinfo->flash_size;
    porperty_devifo.flash_start_addr = p_devinfo->flash_start_addr;
    porperty_devifo.ram_size         = p_devinfo->ram_size;
    porperty_devifo.ram_start_addr   = p_devinfo->ram_start_addr;

    am_boot_kft_property_handle_t  property_handle = am_boot_kft_property_init(
        flash_handle, &porperty_devifo);

    am_boot_kft_packet_handle_t packet_handle = am_boot_kft_packet_init(serial_handle);

    p_dev->command_handle = am_boot_kft_command_init(packet_handle,
                                                     memory_handle,
                                                     property_handle,
                                                     flash_handle);
    __gp_boot_kft_dev = p_dev;
    return AM_OK;
}

/**
 * \brief bootloader kboot KinetisFlashTool 命令处理(命令状态机)
 *
 * \note 该函数需要用户在应用程序里面循环调用，上位机会一直发送信息给bootloader,状态机需要一直去解析
 */
int am_boot_kft_command_pump()
{
    if (__gp_boot_kft_dev == NULL) {
        return -AM_ENXIO;
    }
    __gp_boot_kft_dev->command_handle->p_funcs->pfn_pump(
        __gp_boot_kft_dev->command_handle->p_drv);

    return AM_OK;
}

/* end of file */
