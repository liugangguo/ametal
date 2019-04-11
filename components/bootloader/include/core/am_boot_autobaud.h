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
 * \brief 自动波特率服务，可以实现与未知波特率的串口设备自动匹配波特率
 *        支持波特率范围 1200~128000
 *
 * \internal
 * \par Modification history
 * - 1.00 18-10-25  ipk, first implementation
 * \endinternal
 */

#ifndef __AM_AUTO_BAUDRATE_H__
#define __AM_AUTO_BAUDRATE_H__

#include "am_cap.h"
#include "am_uart.h"
#include "am_timer.h"
#include "am_softimer.h"

/**
 * \brief 自动波特率设备信息
 */
typedef struct am_boot_autobaud_devinfo {

    uint8_t  cap_chanel;               /**< \brief CAP捕获通道 */
    uint8_t  timer_width;              /**< \brief TIMER定时器位数 */

    uint16_t timer_out;                /**< \brief 接收一次数据的超时时间，单位ms*/
    uint32_t cap_trigger;              /**< \brief CAP捕获边沿方式选择选择 */

    void     (*pfn_plfm_init)(void);   /**< \brief 平台初始化函数 */
    void     (*pfn_plfm_deinit)(void); /**< \brief 平台解初始化函数 */

    int      (*pfn_stat_ovflag_get)(void *); /**< \brief 溢出标志获取 */

} am_boot_autobaud_devinfo_t;

/**
 * \brief 自动波特率设备结构体
 */
typedef struct am_boot_atuobaud_dev {

    /** \brief CAP捕获句柄*/
    am_cap_handle_t         cap_handle;

    /** \brief softimer软件定时器结构体*/
    am_softimer_t           softimer;

    /** \brief 捕获引脚*/
    int                     cap_pin;

    /** \brief 捕获中断标志*/
    volatile am_bool_t      cap_flag;


    /** \brief 串口接收数据*/
    uint16_t                uart_data;

    /** \brief 接收数据的双边沿计数*/
    uint32_t                data_edge;

    /** \brief 接收数据的脉冲数*/
    uint32_t                data_pulses;

    /** \brief 接收数据超时时间计数*/
    uint16_t                time_out_ms;

    /** \brief 接收数据的脉冲宽度*/
    uint32_t                data_pulse_width[32];

    /** \brief 自动波特率设备信息*/
    am_boot_autobaud_devinfo_t  *p_devinfo;

} am_boot_autobaud_dev_t;

/**
 * \brief 自动波特率服务句柄
 */
typedef am_boot_autobaud_dev_t *am_boot_autobaud_handle_t;

/**
 * \brief 自动波特率初始化函数
 *
 * \param[in] p_dev        : 指向自动波特率服务的指针
 * \param[in] p_devinfo    : 指向自动波特率服务信息常量的指针
 * \param[in] cap_handle   : CAP捕获标准服务句柄
 * \param[in] uart_handle  : UART串口标准服务句柄
 *
 * \return 自动波特率服务操作句柄
 */
am_boot_autobaud_handle_t am_boot_autobaud_init (am_boot_autobaud_dev_t     *p_dev,
                                                 am_boot_autobaud_devinfo_t *p_devinfo,
                                                 am_cap_handle_t             cap_handle);

/**
 * \brief 自动波特率解初始化函数
 *
 * \param[in] handle        : 自动波特率服务句柄
 *
 * \return 无
 */
void am_boot_autobaud_deinit (am_boot_autobaud_handle_t handle);

/**
 * \brief 获取接收数据的波特率函数
 *
 * \param[in]  handle     : 自动波特率服务句柄
 * \param[out] p_baudrate : 指向获取的波特率地址
 *
 * \retval AM_OK    : 获取成功
 *         AM_ERROR : 获取失败
 */
int am_boot_baudrate_get (am_boot_autobaud_handle_t handle,
                          uint32_t                 *p_baudrate);

#endif

/* end of file */
