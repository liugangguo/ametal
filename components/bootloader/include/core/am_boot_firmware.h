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
 * \brief bootloader 固件存储的接口，不依赖于命令解析的上位机
 *
 * \internal
 * \par Modification history
 * - 1.00 18-11-16  yrh, first implementation
 * \endinternal
 */

#ifndef __AM_BOOT_FIRMWARE_H
#define __AM_BOOT_FIRMWARE_H

#include "ametal.h"
/**
 * \brief bootloader接收固件头部数据
 */
typedef struct am_boot_firmware_verify_info {

    /** \brief 固件长度 */
    uint32_t len;

    /** \brief 固件校验码 */
    uint32_t verify_value;

} am_boot_firmware_verify_info_t;

struct am_boot_firmware_drv_funcs {
    /**< \brief 固件存储开始驱动函数*/
    int (*pfn_store_start)(void *p_drv, uint32_t firmware_size);

    /**< \brief 固件存储驱动函数*/
    int (*pfn_store_bytes)(void *p_drv, uint8_t *p_data, uint32_t firmware_size);

    /**< \brief 固件存储结束驱动函数*/
    int (*pfn_store_final)(void *p_drv);

    /**< \brief 固件校验*/
    int (*pfn_verify)(void *p_drv, am_boot_firmware_verify_info_t *p_verify_info);
};

/**< \brief 固件存储标准服务 */
typedef struct am_boot_firmware_serv {
    /**< \brief 标准服务驱动函数结构体指针 */
    struct am_boot_firmware_drv_funcs *pfn_funcs;

    /**< \brief 驱动函数的第一个参数 */
    void                              *p_drv;
}am_boot_firmware_serv_t;

/**< \brief 固件存储标准服务操作句柄的类型定义 */
typedef am_boot_firmware_serv_t *am_boot_firmware_handle_t;

/**
 * \brief 固件存储的开始处理
 *
 * 如果暂时不知道固件的长度可以分别传入0.如果知道固件的大小就直接传入固件的大小
 *
 * \param[in] total_firmware_size : 固件的总长度
 *
 * \retval AM_ENOMEM   固件超出内存大小
 * \retval AM_EFAULT   固件存放的地址有误（1.地址错误，不在正常的存储范围，2.不是扇区的首地址）
 * \retval AM_EINVAL   传入的参数不合法
 * \retval AM_OK       成功
 */
am_static_inline
int am_boot_firmware_store_start(am_boot_firmware_handle_t  handle,
                                 uint32_t                   total_firmware_size)
{
    return handle->pfn_funcs->pfn_store_start(handle->p_drv, total_firmware_size);
}

/**
 * \brief 固件数据存储
 *
 * 将固件存放到预定好的地址中去。如果一开始传输的时候不知道固件的大小，那么调用am_boot_firmware_store_start时，
 * 第二个参数固件的大小传入0，后面调用am_boot_firmware_store_bytes时就需要一边擦除flash，一边进行flash写.
 * 所以am_boot_firmware_store_bytes（）函数执行需要一定的时间，调用时注意固件传输的时间，防止数据传输丢失。
 *
 * \param[in] p_data        : 传入的固件的首地址
 * \param[in] firmware_size : 固件长度（要是4的整数倍大小，最后不够的补0）
 *
 * \retval AM_EINVAL   参数无效
 * \retval AM_ENOMEM   空间（内存）不足
 * \retval AM_ERROR    擦除或写入失败
 * \retval AM_OK       成功
 */
am_static_inline
int am_boot_firmware_store_bytes(am_boot_firmware_handle_t handle,
                                 uint8_t                  *p_data,
                                 uint32_t                  firmware_size)
{
    return handle->pfn_funcs->pfn_store_bytes(handle->p_drv, p_data, firmware_size);
}

/**
 * \brief 固件存储的结束
 *
 * \retval AM_ERROR 出错
 * \retval AM_OK    成功
 */
am_static_inline
int am_boot_firmware_store_final(am_boot_firmware_handle_t handle)
{
    return handle->pfn_funcs->pfn_store_final(handle->p_drv);
}

/**
 * \brief 固件校验
 *
 * \param[in] handle        : 操作句柄
 * \param[in] p_verify_info : 校验信息的结构体，包含固件长度和校验码
 *
 * \retval AM_ERROR 出错
 * \retval AM_OK    成功
 */
am_static_inline
int am_boot_firmware_verify(am_boot_firmware_handle_t handle, am_boot_firmware_verify_info_t *p_verify_info)
{
    return handle->pfn_funcs->pfn_verify(handle->p_drv, p_verify_info);
}


#endif /* __AM_BOOT_FIRMWARE_H */

/* end of file */
