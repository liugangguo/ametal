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

/** \brief 双区用户程序有效 */
#define AM_BOOTLOADER_FLAG_APP     (0x12345678)  //305419896
/** \brief 双区升级程序有效 */
#define AM_BOOTLOADER_FLAG_UPDATE  (0x87654321)  //2271560481
/** \brief 双区无代码 */
#define AM_BOOTLOADER_FLAG_NO      (0xFFFFFFFF)


/**
 * \brief 判断应用代码是否可以跳转过去执行
 * 
 * \param[in] app_start_addr : 应用代码首地址
 * 
 * \retval  无
 */ 
am_bool_t am_boot_app_is_ready(void);

/**
 * \brief 跳转到应用代码代码
 *
 *
 * \retval AM_ERROR 跳转出错或跳转目的地址有误
 */
int am_boot_go_application(void);

/**
 * \brief 系统软件重启
 *
 * \retval 无
 */
void am_boot_reset(void);


/**
 * \brief 双区bootloader标志设置
 *
 * \param[in] flags 标志
 * AM_BOOTLOADER_FLAGS_APP    双区用户程序有效
 * AM_BOOTLOADER_FLAGS_UPDATE 双区升级程序有效
 * AM_BOOTLOADER_FLAGS_NO     双区无代码
 *
 * \retval AM_OK 成功
 */
int am_boot_update_flag_set(uint32_t flag);


#ifdef __cplusplus
}
#endif

 #endif /* __AM_BOOT_H */
 
 /* end of file */
