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
 * \brief bootloader firmware store by flash drivers implementation
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-15  yrh, first implementation
 * \endinternal
 */
#include "am_zlg217_boot_firmware_flash.h"
#include "am_boot_firmware.h"
#include <string.h>

static int __firmware_flash_start(void *p_drv, uint32_t firmware_size);
static int __firmware_flash_bytes(void *p_drv, uint8_t *p_data, uint32_t firmware_size);
static int __firmware_flash_final(void *p_drv);

/**
 * \brief BootLoader 固件存放到flash的标准接口的实现
 */
static struct am_boot_firmware_drv_funcs __g_firmware_flash_drv_funcs = {
    __firmware_flash_start,
    __firmware_flash_bytes,
    __firmware_flash_final,
};

/**
 * \brief 固件存放到flash的开始函数
 */
static int __firmware_flash_start (void *p_drv, uint32_t firmware_size)
{
    am_zlg217_boot_firmware_flash_dev_t *p_dev = (am_zlg217_boot_firmware_flash_dev_t *)p_drv;
    p_dev->firmware_size_is_unknow = AM_FALSE;
    int ret;
    if( firmware_size <= 0) {
        p_dev->firmware_size_is_unknow = AM_TRUE;
    }

    am_boot_flash_info_t *flash_info = NULL;
    p_dev->flash_handle->p_funcs->pfn_flash_info_get(p_dev->flash_handle->p_drv,
                                                    &flash_info);

    uint32_t flash_end_addr = flash_info->flash_start_addr + \
        flash_info->flash_size - 1;

    if((p_dev->firmware_dst_addr + firmware_size) > flash_end_addr) {
        return AM_ENOMEM;
    }

    if(p_dev->firmware_dst_addr < flash_info->flash_start_addr) {
        return AM_EFAULT;
    }

    if(0 != ((p_dev->firmware_dst_addr - flash_info->flash_start_addr) &
            (flash_info->flash_sector_size - 1))) {
        return AM_EFAULT;
    }

    p_dev->firmware_total_size     = 0;
    p_dev->erase_sector_start_addr = p_dev->firmware_dst_addr;
    p_dev->curr_program_flash_addr = p_dev->firmware_dst_addr;
    p_dev->curr_buf_data_size      = 0;

    uint32_t erase_size;
    if( p_dev->firmware_size_is_unknow == AM_TRUE) {
        erase_size = flash_info->flash_sector_size;
    }else {
        erase_size = firmware_size;
    }
    ret = p_dev->flash_handle->p_funcs->pfn_flash_erase_region(
        p_dev->flash_handle->p_drv,
        p_dev->erase_sector_start_addr,
        erase_size);

    if(ret != AM_OK) {
        return AM_ERROR;
    }

    return AM_OK;
}

/**
 * \brief 存储固件
 */
static int __firmware_flash_bytes (void *p_drv, uint8_t *p_data, uint32_t firmware_size)
{
    if(p_data == NULL || firmware_size <= 0) {
        return AM_EINVAL;
    }
    int      leave_size, ret, i;
    uint32_t program_size, data_program_start_index = 0, leave_firmware_index;
    am_zlg217_boot_firmware_flash_dev_t *p_dev = (am_zlg217_boot_firmware_flash_dev_t *)p_drv;

    p_dev->firmware_total_size += firmware_size;

    am_boot_flash_info_t *flash_info = NULL;
    p_dev->flash_handle->p_funcs->pfn_flash_info_get(p_dev->flash_handle->p_drv,
                                                    &flash_info);

    uint32_t flash_end_addr = flash_info->flash_start_addr + \
        flash_info->flash_size - 1;

    if((p_dev->firmware_dst_addr + p_dev->firmware_total_size) > flash_end_addr) {
        return AM_ENOMEM;
    }

    if(p_dev->firmware_size_is_unknow == AM_TRUE) {
        uint32_t add_len = p_dev->curr_program_flash_addr - p_dev->erase_sector_start_addr + firmware_size;

        if(add_len >= flash_info->flash_sector_size) {
            uint32_t erase_sector_count;
            if(add_len & (flash_info->flash_sector_size - 1)) {
                erase_sector_count = add_len / flash_info->flash_sector_size;
            }
            else {
                erase_sector_count = add_len / flash_info->flash_sector_size - 1;
            }

            ret = p_dev->flash_handle->p_funcs->pfn_flash_erase_region(
                 p_dev->flash_handle->p_drv,
                 p_dev->erase_sector_start_addr + flash_info->flash_sector_size,
                 erase_sector_count * flash_info->flash_sector_size);
            if(ret != AM_OK) {
                return AM_ERROR;
            }
            p_dev->erase_sector_start_addr += erase_sector_count * \
                                              flash_info->flash_sector_size;
        }
    }

    if(p_dev->curr_buf_data_size != 0) {
        for(i = 0; p_dev->curr_buf_data_size < p_dev->buf_data_size; i++) {
            p_dev->buf_data[p_dev->curr_buf_data_size++] = p_data[i];
        }
        data_program_start_index = i;
        ret = p_dev->flash_handle->p_funcs->pfn_flash_program(
            p_dev->flash_handle->p_drv,
            p_dev->curr_program_flash_addr,
            p_dev->buf_data,
            p_dev->buf_data_size);
        if(ret != AM_OK) {
            return AM_ERROR;
        }
        p_dev->curr_program_flash_addr += p_dev->buf_data_size;
        p_dev->curr_buf_data_size = 0;
    }

    firmware_size = firmware_size - data_program_start_index;
    leave_size    = firmware_size & (p_dev->buf_data_size - 1);
    program_size  = firmware_size - leave_size;
    leave_firmware_index = program_size + data_program_start_index;

    ret = p_dev->flash_handle->p_funcs->pfn_flash_program(
        p_dev->flash_handle->p_drv,
        p_dev->curr_program_flash_addr,
       &p_data[data_program_start_index],
        program_size);
    if(ret != AM_OK) {
        return AM_ERROR;
    }
    p_dev->curr_program_flash_addr += program_size;

    for(i = 0; i < leave_size; i++) {
        p_dev->buf_data[p_dev->curr_buf_data_size++] = p_data[leave_firmware_index++];
    }

#if 0
    uint32_t free_buf_size = p_dev->buf_data_size - p_dev->curr_buf_data_size;

    if(free_buf_size >= firmware_size) {
        memcpy(&(p_dev->buf_data[p_dev->curr_buf_data_size]), p_data, firmware_size);
        p_dev->curr_buf_data_size += firmware_size;
    }
    else {
        memcpy(&p_dev->buf_data[p_dev->curr_buf_data_size], p_data, free_buf_size);
        p_dev->curr_buf_data_size = 0;

        ret = p_dev->flash_handle->p_funcs->pfn_flash_program(
          p_dev->flash_handle->p_drv,
          p_dev->curr_program_flash_addr,
          p_dev->buf_data,
          p_dev->buf_data_size);
        if(ret != AM_OK) {
            return AM_ERROR;
        }
        p_dev->curr_program_flash_addr += p_dev->buf_data_size;

        uint32_t leave_firmware = firmware_size - free_buf_size;
        int times = leave_firmware / p_dev->buf_data_size;
        int integ = leave_firmware % p_dev->buf_data_size;

        if(times > 0)
        {
            ret = p_dev->flash_handle->p_funcs->pfn_flash_program(
                p_dev->flash_handle->p_drv,
                p_dev->curr_program_flash_addr,
                p_data + free_buf_size,
                p_dev->buf_data_size * times);
            if(ret != AM_OK) {
                return AM_ERROR;
            }

            leave_firmware = leave_firmware - p_dev->buf_data_size * times;
            p_dev->curr_buf_data_size = 0;
            p_dev->curr_program_flash_addr += p_dev->buf_data_size * times;
        }
        else {
            memcpy(&p_dev->buf_data[p_dev->curr_buf_data_size],
                    p_data + free_buf_size,
                    leave_firmware);
            p_dev->curr_buf_data_size += leave_firmware;
            leave_firmware = 0;
        }

        if(integ != 0 && leave_firmware != 0) {
            memcpy(&p_dev->buf_data[p_dev->curr_buf_data_size],
                    p_data + firmware_size - leave_firmware,
                    leave_firmware);

            p_dev->curr_buf_data_size += leave_firmware;
            leave_firmware = 0;
        }
    }

    if(p_dev->curr_buf_data_size == p_dev->buf_data_size) {
       ret = p_dev->flash_handle->p_funcs->pfn_flash_program(
           p_dev->flash_handle->p_drv,
           p_dev->curr_program_flash_addr,
           p_dev->buf_data,
           p_dev->buf_data_size);
       if(ret != AM_OK) {
           return AM_ERROR;
       }
       p_dev->curr_buf_data_size = 0;
       p_dev->curr_program_flash_addr += p_dev->buf_data_size;
    }
#endif
    return AM_OK;
}
/**
 * \brief 固件存储结束
 */
static int __firmware_flash_final(void *p_drv)
{
    am_zlg217_boot_firmware_flash_dev_t *p_dev = (am_zlg217_boot_firmware_flash_dev_t *)p_drv;
    int ret;
    if(p_dev->curr_buf_data_size != 0) {
        while(p_dev->curr_buf_data_size < p_dev->buf_data_size) {
            p_dev->buf_data[p_dev->curr_buf_data_size++] = 0;
        }
        ret = p_dev->flash_handle->p_funcs->pfn_flash_program(
            p_dev->flash_handle->p_drv,
            p_dev->curr_program_flash_addr,
            p_dev->buf_data,
            p_dev->buf_data_size);
        if(ret != AM_OK) {
            return AM_ERROR;
        }
    }
    p_dev->curr_buf_data_size      = 0;
    p_dev->firmware_total_size     = 0;
    p_dev->erase_sector_start_addr = p_dev->firmware_dst_addr;
    p_dev->curr_program_flash_addr = p_dev->firmware_dst_addr;

    return AM_OK;
}

/**
 * \brief 固件flash存储初始化
 */
am_boot_firmware_handle_t am_zlg217_boot_firmware_flash_init (
    am_zlg217_boot_firmware_flash_dev_t     *p_dev,
    am_zlg217_boot_firmware_flash_devinfo_t *p_devinfo,
    am_boot_flash_handle_t            flash_handle)
{
    p_dev->firmware_flash_serv.pfn_funcs = &__g_firmware_flash_drv_funcs;
    p_dev->firmware_flash_serv.p_drv     = p_dev;
    p_dev->flash_handle                  = flash_handle;
    p_dev->firmware_dst_addr             = p_devinfo->dst_addr;
    p_dev->buf_data_size                 = p_devinfo->buf_size;
    p_dev->devinfo                       = p_devinfo;

    return &p_dev->firmware_flash_serv;
}
/**
 * \brief 固件flash存储解初始化
 */
void am_zlg217_boot_firmware_flash_deint()
{

}
/* end of file */
