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
 * \brief bootloader drivers for standard interface
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-15  yrh, first implementation
 * \endinternal
 */

#ifndef __AM_ZLG217_BOOT_H
#define __AM_ZLG217_BOOT_H

#include "am_boot.h"
#include "amhw_zlg_flash.h"

typedef struct am_zlg217_boot_devinfo {
    uint32_t  flash_start_addr;    /**< \brief flash的起始地址*/
    uint32_t  flash_size;          /**< \brief flash的大小 */

    uint32_t  ram_start_addr;      /**< \brief ram起始地址 */
    uint32_t  ram_size;            /**< \brief ram的大小 */

    void (*pfn_plfm_init)(void);   /**< \brief 平台初始化函数 */

    void (*pfn_plfm_deinit)(void); /**< \brief 平台去初始化函数 */
}am_zlg217_boot_devinfo_t;

typedef struct am_zlg217_boot_dev {
    am_boot_serv_t    boot_serv;        /**< \brief 标准的BootLoader服务 */

//    uint32_t          flash_start_addr; /**< \brief flash起始地址 */
//    uint32_t          flash_size;       /**< \brief flash大小 */
//
//    uint32_t          ram_start_addr;   /**< \brief ram起始地址 */
//    uint32_t          ram_size;         /**< \brief ram的大小 */

    am_zlg217_boot_devinfo_t *p_devinfo;
    amhw_zlg_flash_t          amhw_zlg_flash;   /**< \brief flash寄存器结构体 */

}am_zlg217_boot_dev_t;

/**
 * \brief 初始化BootLoader，返回BootLoader标准服务操作句柄
 *
 * \param[in] p_dev     : 指向BootLoader设备的指针
 * \param[in] p_devinfo : 指向BootLoader设备信息常量的指针
 *
 * \return BootLoader标准服务操作句柄，值为NULL时表明初始化失败
 */
am_boot_handle_t am_zlg217_boot_init(am_zlg217_boot_dev_t     *p_dev,
                              am_zlg217_boot_devinfo_t *p_devinfo);

/**
 * \brief 不使用BootLoader时，解初始化BootLoader，释放相关资源
 *
 * \param[in] p_dev : 指向BootLoader设备的指针
 */
void am_zlg217_boot_deinit(am_zlg217_boot_dev_t  *p_dev);

#endif /* __AM_ZLG217_BOOT_H */
