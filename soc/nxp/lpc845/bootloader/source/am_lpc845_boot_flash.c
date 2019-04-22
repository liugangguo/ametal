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
 * \brief bootloader flash drivers implementation
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-15  yrh, first implementation
 * \endinternal
 */
#include "am_lpc845_boot_flash.h"
#include "am_int.h"
#include "hw/amhw_lpc84x_iap.h"
#include "am_boot_flash.h"

static int __boot_flash_erase_region(void     *p_drv,
                                     uint32_t  start_addr,
                                     uint32_t  length);
static int __boot_flash_program(void      *p_drv,
                                uint32_t   dst_addr,
                                void      *p_src,
                                uint32_t   size);
static void __boot_flash_info_get(void *p_drv, am_boot_flash_info_t **pp_flash_info);
/**
 * \brief BootLoader flash标准层接口实现
 */
static struct am_boot_flash_drv_funcs __g_flash_drv_funcs = {
    __boot_flash_erase_region,
    __boot_flash_program,
    __boot_flash_info_get,
    NULL,
};
/**
 * \brief flash区域擦除
 */
static int __boot_flash_erase_region(void     *p_drv,
                                     uint32_t  start_addr,
                                     uint32_t  length)
{
    int key;
    amhw_lpc84x_iap_stat_t ret;
    if(length == 0) {
        return AM_OK;
    }
    am_lpc845_boot_flash_dev_t *p_dev = (am_lpc845_boot_flash_dev_t *)p_drv;
    uint32_t sector_size    = p_dev->flash_info.flash_sector_size;
    uint32_t sector_count   = p_dev->flash_info.flash_sector_count;
    uint32_t start_sector   = start_addr / sector_size;
    uint32_t end_sector = (start_addr + length) / sector_size;

    if(start_addr + length == p_dev->flash_info.flash_start_addr + p_dev->flash_info.flash_size) {
        end_sector = p_dev->flash_info.flash_sector_count - 1;
    }
    if (end_sector > sector_count) {
        return AM_ERROR;
    }

    key = am_int_cpu_lock();
    ret = amhw_lpc84x_iap_prepare(start_sector, end_sector);
    if(ret != AMHW_LPC84X_IAP_STAT_SUCCESS) {
        am_int_cpu_unlock(key);
        return AM_ERROR;
    }
    ret = amhw_lpc84x_iap_erase_sector (start_sector, end_sector);

    am_int_cpu_unlock(key);
    if(ret != AMHW_LPC84X_IAP_STAT_SUCCESS) {
        return AM_ERROR;
    }
    return AM_OK;
}

/**
 * \brief 对flash的写操作
 */
static int __boot_flash_program(void      *p_drv,
                                uint32_t   dst_addr,
                                void      *p_src,
                                uint32_t   size)
{
    int key;
    amhw_lpc84x_iap_stat_t ret;
    am_lpc845_boot_flash_dev_t *p_dev = (am_lpc845_boot_flash_dev_t *)p_drv;
    if(p_src == NULL) {
        return AM_ERROR;
    }
    if(size == 0) {
        return AM_OK;
    }
    if(size < 64) {
        return AM_ERROR;
    }
    uint32_t sector_size  = p_dev->flash_info.flash_sector_size;
    uint32_t sector_count = p_dev->flash_info.flash_sector_count;
    uint32_t start_sector = dst_addr / sector_size;
    uint32_t end_sector = (dst_addr + size) / sector_size;

    if (end_sector > sector_count) {
        return AM_ERROR;
    }

    key = am_int_cpu_lock();
    ret = amhw_lpc84x_iap_prepare(start_sector, end_sector);
    if(ret != AMHW_LPC84X_IAP_STAT_SUCCESS) {
        am_int_cpu_unlock(key);
        return ret;
    }
    ret = amhw_lpc84x_iap_copy (dst_addr,
                               (uint32_t)p_src,
                                size);
    am_int_cpu_unlock(key);
    if(ret != AMHW_LPC84X_IAP_STAT_SUCCESS) {
        return ret;
    }
    return AM_OK;
}

/**
 * \brief 获取flash的信息
 */
static void __boot_flash_info_get(void *p_drv, am_boot_flash_info_t **pp_flash_info)
{
    am_lpc845_boot_flash_dev_t *p_dev = (am_lpc845_boot_flash_dev_t *)p_drv;

    *pp_flash_info = &p_dev->flash_info;
}

/**
 * \brief BootLoader flash初始化函数
 */
am_boot_flash_handle_t am_lpc845_boot_flash_init(am_lpc845_boot_flash_dev_t     *p_dev,
                                                 am_lpc845_boot_flash_devinfo_t *p_devinfo)
{
    if(p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }
    p_dev->flash_info.flash_sector_count = p_devinfo->flash_sector_count;
    p_dev->flash_info.flash_sector_size  = p_devinfo->flash_sector_size;
    p_dev->flash_info.flash_size         = p_devinfo->flash_size;
    p_dev->flash_info.flash_start_addr   = p_devinfo->flash_start_addr;
    p_dev->flash_info.flash_sector_count = p_devinfo->flash_page_size;

    p_dev->flash_serv.p_funcs = &__g_flash_drv_funcs;
    p_dev->flash_serv.p_drv   = p_dev;

    p_dev->p_devinfo = p_devinfo;

    return &p_dev->flash_serv;
}

/* end of file */

