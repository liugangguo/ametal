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
 * \brief bootloader drivers implementation
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-15  yrh, first implementation
 * \endinternal
 */
#include "am_zlg217_boot.h"
#include "am_zlg217.h"
#include "am_arm_nvic.h"

static am_zlg217_boot_dev_t *__gp_boot_dev = NULL;
/**
 * \brief 判断应用代码是否可执行
 */
am_bool_t am_boot_app_is_ready(uint32_t app_start_addr)
{
    if(__gp_boot_dev == NULL) {
        return AM_FALSE;
    }

    if ((!app_start_addr) || (app_start_addr == 0xffffffff)) {
        return AM_FALSE;
    }
    uint32_t flash_start_addr = __gp_boot_dev->p_devinfo->flash_start_addr;
    uint32_t flash_end_adrr   = __gp_boot_dev->p_devinfo->flash_start_addr + \
        __gp_boot_dev->p_devinfo->flash_size - 1;
    uint32_t ram_start_addr = __gp_boot_dev->p_devinfo->ram_start_addr;
    uint32_t ram_size    = __gp_boot_dev->p_devinfo->ram_size;


    if(app_start_addr < flash_start_addr || app_start_addr > flash_end_adrr) {
        return AM_FALSE;
    }
    else {
        if((*(uint32_t *)app_start_addr) > (ram_start_addr + ram_size )||
           (*(uint32_t *)app_start_addr) < ram_start_addr) {
            return AM_FALSE;
        }
    }
    return AM_TRUE;
}
/**
 * \brief 跳转到应用代码
 */
int am_boot_go_application(uint32_t app_start_addr)
{
    if(__gp_boot_dev == NULL) {
        return -AM_ERROR;
    }
    uint32_t stack_pointer = *(uint32_t *)app_start_addr;

    void (*farewell_bootloader)(void);

    if(AM_TRUE != am_boot_app_is_ready(app_start_addr)) {
        return AM_ERROR;
    }

    farewell_bootloader = (void (*)(void))(*(uint32_t *)(app_start_addr + 4));

    /* 设置栈指针 */
    __set_MSP(stack_pointer);
    __set_PSP(stack_pointer);

    /* 跳转到应用代码 */
    farewell_bootloader();

    /*如果正常跳转，代码不会执行到这里*/
    return -AM_ERROR;
}

/**
 * \brief 系统重启
 */
void am_boot_reset()
{
    if(__gp_boot_dev == NULL) {
        return;
    }
    NVIC_SystemReset();
}
/**
 * \brief 获取基本的内存信息的信息
 * \param[in] mem_info : 传入存放获取后的信息

 * \retval 无
 */
void am_boot_base_mem_info_get(am_boot_mem_info_t **pp_mem_info)
{
    if(__gp_boot_dev == NULL) {
        return;
    }
    *pp_mem_info = &__gp_boot_dev->mem_info;
}

/**
 * \brief 释放系统资源
 *
 * \note bootloader在跳转到应用代码前，必须调用此接口，
 *       在bootloader中申请的资源或者初始化的某些外设都应主动释放和解初始化，避免对应用程序造成影响。

 * \retval AM_OK : 成功
 */
int am_boot_source_release(void)
{
    am_arm_nvic_deinit();

    return AM_OK;
}

/**
 * \brief BootLoader初始化函数
 */
int am_zlg217_boot_init(am_zlg217_boot_dev_t     *p_dev,
                        am_zlg217_boot_devinfo_t *p_devinfo)
{
    if(p_devinfo == NULL || p_dev == NULL) {
        return -AM_ENXIO;;
    }

    p_dev->p_devinfo          = p_devinfo;

    p_dev->mem_info.flash_size       = p_devinfo->flash_size;
    p_dev->mem_info.flash_start_addr = p_devinfo->flash_start_addr;
    p_dev->mem_info.ram_size         = p_devinfo->ram_size;
    p_dev->mem_info.ram_start_addr   = p_devinfo->ram_start_addr;

    __gp_boot_dev = p_dev;

    return AM_OK;
}

/* end of file */
