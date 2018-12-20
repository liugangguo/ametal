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
 * \brief bootloader 通用基本标准接口
 *
 * \internal
 * \par Modification History
 * - 1.00 18-11-13  yrh, first implementation.
 * \endinternal
 */
 
 #ifndef __AM_BOOT_H
 #define __AM_BOOT_H
 
#ifdef __cplusplus
extern "C" {
#endif
#include "ametal.h"

typedef struct am_boot_mem_info {
    uint32_t  flash_start_addr;    /**< \brief flash的起始地址*/
    uint32_t  flash_size;          /**< \brief flash的大小 */

    uint32_t  ram_start_addr;      /**< \brief ram起始地址 */
    uint32_t  ram_size;            /**< \brief ram的大小 */
}am_boot_mem_info_t;


/**
 * \brief 判断应用代码是否可以跳转过去执行
 * 
 * \param[in] app_start_addr : 应用代码首地址
 * 
 * \retval  无
 */ 
am_bool_t am_boot_app_is_ready(uint32_t app_start_addr);

/**
 * \brief 跳转到应用代码代码
 *
 * \param[in] app_start_addr : 应用代码首地址
 *
 * \retval AM_ERROR 跳转出错或者参数传入不合法
 */
int am_boot_go_application(uint32_t app_start_addr);

/**
 * \brief 系统软件重启
 *
 * \retval 无
 */
void am_boot_reset(void);

/**
 * \brief 获取基本的内存信息的信息
 * \param[in] mem_info : 传入存放获取后的信息

 * \retval 无
 */
void am_boot_base_mem_info_get(am_boot_mem_info_t **pp_mem_info);

/**
 * \brief 释放系统资源
 *
 * \note bootloader在跳转到应用代码前，必须调用此接口，
 *       在bootloader中申请的资源或者初始化的某些外设都应主动释放和解初始化，避免对应用程序造成影响。

 * \retval AM_OK : 成功
 */
int am_boot_source_release(void);

#ifdef __cplusplus
}
#endif

 #endif /* __AM_BOOTS_H */
 
 /* end of file */
