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
 * \brief bootloader memory 标准设备实现（flash驱动）
 *
 * \internal
 * \par modification history:
 * - 1.00 18-11-30  yrh, first implementation.
 * \endinternal
 */
#include "ametal.h"
#include "am_boot_flash_memory.h"

static int __boot_flash_mem_write(void *p_drv, uint32_t address, uint32_t length, uint8_t *p_buffer)
{
    am_boot_flash_mem_dev_t *p_dev = (am_boot_flash_mem_dev_t *)p_drv;
    return am_boot_flash_program(p_dev->flash_handle,
                                 address,
                                 p_buffer,
                                 length);
}

static int __boot_flash_mem_erase(void *p_drv, uint32_t address, uint32_t length)
{
    am_boot_flash_mem_dev_t *p_dev = (am_boot_flash_mem_dev_t *)p_drv;
    return am_boot_flash_erase_region(p_dev->flash_handle,
                                      address,
                                      length);
}

static const struct am_boot_mem_drv_funcs __g_boot_flash_mem_drv_funcs = {
       NULL,
     __boot_flash_mem_write,
     __boot_flash_mem_erase,
};

static am_boot_flash_mem_dev_t __g_flash_mem_dev;

am_boot_mem_handle_t am_boot_flash_mem_init(am_boot_flash_handle_t flash_handle)
{
    if (flash_handle == NULL) {
        return NULL;
    }
    __g_flash_mem_dev.isa.p_funcs  = &__g_boot_flash_mem_drv_funcs;
    __g_flash_mem_dev.isa.p_drv    = &__g_flash_mem_dev;
    __g_flash_mem_dev.flash_handle = flash_handle;

    return &__g_flash_mem_dev.isa;
}

/* end of file */
