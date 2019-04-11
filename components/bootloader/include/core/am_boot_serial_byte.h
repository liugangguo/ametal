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
 * \brief bootloader 串行数据操作通用操作接口
 *
 *   该类主要描述了BootLoader关于串行数据操作的，属于抽象类，根据不同的驱动方式，由子类实现对其操作，
 *   列如，使用uart驱动的数据传输，使用i2c驱动的数据传输。
 *
 *
 * \par 使用示例
 * \code
 *
 *
 * \endcode
 *
 * \internal
 * \par modification history:
 * - 1.00 18-12-4  yrh, first implementation.
 * \endinternal
 */
#ifndef __AM_BOOT_SERIAL_BYTE_H
#define __AM_BOOT_SERIAL_BYTE_H

#include "am_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**< \brief 接收回调函数类型声明 */
typedef void (*serial_byte_receive_func_t)(uint8_t);

/**
 * \brief 串行设备字节传输驱动函数结构体
 */
struct am_boot_serial_byte_funcs {
    /**< \brief 发送数据 */
    int (*pfn_serial_byte_send)(void *p_arg, const uint8_t *p_buffer, uint32_t byte_count);

    /**< \brief 接收数据 */
    int (*pfn_serial_byte_receive)(void *p_arg, uint8_t *p_buffer, uint32_t requested_bytes);

    /**< \brief 用户中断接收回调函数设置 */
    int (*pfn_serial_int_callback_enable)(void *p_arg, serial_byte_receive_func_t callback_fun);
};

/**
 * \brief bootloader 串行数据处理 标准服务结构体
 */
typedef struct am_boot_serial_byte_serv {
    const struct am_boot_serial_byte_funcs *p_funcs;  /**< \brief 串行数据处理驱动函数结构体指针 */
    void                                   *p_drv;    /**< \brief 串行数据处理驱动函数第一个参数 */
} am_boot_serial_byte_serv_t;

/** \brief bootloader 串行数据操作标准服务操作句柄定义 */
typedef am_boot_serial_byte_serv_t  *am_boot_serial_handle_t;

/**
 * \brief 通过串行设备接口发数据
 *
 * \param[in] handle     : 标准服务句柄
 * \param[in] buffer     : 发送的数据
 * \param[in] byte_count : 发送数据的长度
 *
 * \retval 发送的字节数
 */
am_static_inline
int am_boot_serial_byte_send(am_boot_serial_handle_t handle,
                             const uint8_t          *p_buffer,
                             uint32_t                byte_count)
{
    if(handle && handle->p_funcs && handle->p_funcs->pfn_serial_byte_send) {
        return handle->p_funcs->pfn_serial_byte_send(handle->p_drv,
                                                     p_buffer,
                                                     byte_count);
    }
    return -AM_EINVAL;
}

/**
 * \brief 通过串行设备接口收数据
 *
 * \param[in] handle     : 标准服务句柄
 * \param[in] buffer     : 接收的数据
 * \param[in] byte_count : 接收数据的长度
 *
 * \retval 收到的字节数
 */
am_static_inline
int am_boot_serial_byte_receive(am_boot_serial_handle_t handle,
                                uint8_t                *p_buffer,
                                uint32_t                requested_bytes)
{
    if(handle && handle->p_funcs && handle->p_funcs->pfn_serial_byte_receive) {
        return handle->p_funcs->pfn_serial_byte_receive(handle->p_drv,
                                                        p_buffer,
                                                        requested_bytes);
    }
    return -AM_EINVAL;
}

/**
 * \brief 串行中断接收用户传入的回调函数设置
 *
 * 用户可以自己编写自己的回调函数，通过该接口使具体的串行设备中断接收回调里面将收到的数据传给用户回调函数。
 *
 * \param[in] handle       : 标准服务句柄
 * \param[in] callback_fun : 用户的回调处理函数,serial_byte_receive_func_t是一个函数指针类型
 *                           是中断接收到的一个字节，用户可以在回调函数里面处理这个字节
 *
 * \retval AM_OK : 成功
 */
am_static_inline
int am_boot_serial_int_recev_callback_enable(am_boot_serial_handle_t    handle,
                                             serial_byte_receive_func_t callback_fun)
{
    if(handle && handle->p_funcs && handle->p_funcs->pfn_serial_int_callback_enable) {
        return handle->p_funcs->pfn_serial_int_callback_enable(handle->p_drv,
                                                               callback_fun);
    }
    return -AM_EINVAL;
}

#ifdef __cplusplus
}
#endif

#endif /* __AM_BOOT_SERIAL_BYTE_H */
/* end of file */
