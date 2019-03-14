/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief USBD
 *
 * \internal
 * \par Modification history
 * - 1.00 16-9-27  bob, first implementation.
 * \endinternal
 */

/**
 * \file
 * \brief     USB
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-27  bob, first implementation.
 * \endinternal
 */

#ifndef __AM_USBD_H
#define __AM_USBD_H

#ifdef __cplusplus
extern "C" {
#endif
#include "am_types.h"
#include "am_usb.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/**< \brief 定义事务类型 */
#define AM_USBD_CTRL_SETUP    0x00
#define AM_USBD_CTRL_IN       0x01
#define AM_USBD_CTRL_OUT      0x02
#define AM_USBD_CTRL_IDLE     0xFF


/** \brief 设备是否支持自供电 (0:不支持，1:支持)*/
#define AM_USBD_CONFIG_SELF_POWER                ((0x80) | (1 << 6U))
#define AM_USBD_CONFIG_NOT_SELF_POWER            ((0x80) | (0 << 6U))

/** \brief 设备是否支持远程唤醒功能(0:不支持，1:支持) */
#define AM_USBD_CONFIG_REMOTE_WAKEUP             ((0x80) | (1 << 5U))
#define AM_USBD_CONFIG_NOT_REMOTE_WAKEUP         ((0x80) | (0 << 5U))


#define AM_USBD_SPECIFIC_BCD_VERSION             (0x0200U)
#define AM_USBD_DEMO_BCD_VERSION                 (0x0101U)

#define AM_USBD_CLASS                            (0x00U)
#define AM_USBD_SUBCLASS                         (0x00U)
#define AM_USBD_PROTOCOL                         (0x00U)
#define AM_USBD_MAX_POWER                        (0x32U)

/**< \brief 支持的最大端点个数 */
#define AM_USBD_MAX_EP_CNT                       (10)

/**< \brief 一次性收发的最大字节个数 */
#define AM_USBD_MAX_EP_DATA_CNT                  (64U)

/**< \brief 端点掩码*/
#define AM_USBD_ENDPOINT_NUMBER_MASK             (0x0FU)

/** \brief 获取/设置状态类型 */
typedef enum am_usbd_status {
    AM_USBD_STATUS_TEST_MODE = 1U, /**< \brief 测试模式状态 */
    AM_USBD_STATUS_SPEED,          /**< \brief 当前速度状态 */
    AM_USBD_STATUS_OTG,            /**< \brief OTG 状态 */
    AM_USBD_STATUS_DEVICE,         /**< \brief 设备状态 */
    AM_USBD_STATUS_ENDPOINT,       /**< \brief 端点设备状态 */
    AM_USBD_STATUS_DEVICE_STATE,   /**< \brief 设备状态 */
    AM_USBD_STATUS_ADDRESS,        /**< \brief 设备地址状态 */
    AM_USBD_STATUS_SYNCH_FRAME,    /**< \brief 当前帧状态 */
    AM_USBD_STATUS_BUS,            /**< \brief 总线状态 */
} am_usbd_status_t;

/** \brief USB 2.0 设备状态类型 */
typedef enum am_usbd_state {
    AM_USBD_STATE_CONFIGURED = 0U, /**< \brief 设备状态, 配置 */
    AM_USBD_STATE_ADDRESS,         /**< \brief 设备状态, 地址 */
    AM_USBD_STATE_DEFAULT,         /**< \brief 设备状态, 默认*/
    AM_USBD_STATE_ADDRESSING,      /**< \brief 设备状态, 地址设置 */
    AM_USBD_STATE_TEST_MODE,       /**< \brief 设备状态, 测试模式 */
} am_usbd_state_t;


/** \brief 设备回调事件类型 */
typedef enum am_usbd_event {
    AM_USBD_EVENT_BUS_RESET = 1U,                  /**< \brief 检测到USB总线复位信号  */
    AM_USBD_EVENT_SUSPEND,                         /**< \brief 检测到USB总线暂停信号 */
    AM_USBD_EVENT_RESUME,                          /**< \brief 检测到USB总线恢复信号 */
    AM_USBD_EVENT_ERROR,                           /**< \brief 总线上发生了错误 */
    AM_USBD_EVENT_DETACH,                          /**< \brief USB 设备从主机中断开了 */
    AM_USBD_EVENT_ATTACH,                          /**< \brief USB 设备连接上主机 */
    AM_USBD_EVENT_SET_CONFIGURATION,               /**< \brief 设置配置 */
    AM_USBD_EVENT_SET_INTERFACE,                   /**< \brief 设置接口  */

    AM_USBD_EVENT_GET_DEVICE_DESCRIPTOR,           /**< \brief 获取设备描述 */
    AM_USBD_EVENT_GET_CONFIGURATION_DESCRIPTOR,    /**< \brief 获取配置描述 */
    AM_USBD_EVENT_GET_STRING_DESCRIPTOR,           /**< \brief 获取字符串描述 */
    AM_USBD_EVENT_GET_HID_DESCRIPTOR,              /**< \brief 获取 HID 描述 */
    AM_USBD_EVENT_GET_HID_REPORT_DESCRIPTOR,       /**< \brief 获取 HID 报告描述 */
    AM_USBD_EVENT_GET_HID_PHYSICAL_DESCRIPTOR,     /**< \brief 获取 HID 物理描述 */
    AM_USBD_EVENT_GET_DEVICE_QUALIFIER_DESCRIPTOR, /**< \brief 获取 设备质量描述 */
    AM_USBD_EVENT_VENDOR_REQUEST,                  /**< \brief 供应商请求 */
    AM_USBD_EVENT_SET_REMOTE_WAKEUP,               /**< \brief 使能/禁止远端唤醒功能 */
    AM_USBD_EVENT_GET_CONFIGURATION,               /**< \brief 获取当前配置索引 */
    AM_USBD_EVENT_GET_INTERFACE,                   /**< \brief 获取当前备用接口值 */
} am_usbd_event_t;


/**
 * \brief 端点初始化结构
 * 该结构体可以初始化端点信息，作为am_usbd_control 的参数传入
 */
typedef struct am_usbd_endpoint_init {
    uint8_t  endpoint_address;     /**< \brief 端点地址 */
    uint8_t  transfer_type;        /**< \brief 端点传输类型 */
    uint16_t max_packet_size;      /**< \brief 端点最大包大小 */
} am_usbd_endpoint_init_t;

/**
 * \brief 端点状态结构
 * 该结构体可以初始化端点信息，作为am_usbd_control 的参数传入
 */
typedef struct am_usbd_ep_status {
    uint8_t  endpoint_address;     /**< \brief 端点地址 */
    uint16_t endpoint_status;      /**< \brief 端点状态 : 空闲  or 挂起 */
} am_usbd_ep_status_t;

typedef struct am_usbd_descriptor {
    uint16_t  desc_wValue;             /* 高8位为描述符类型，低8位为描述符编号 */
    uint16_t  desc_size;               /* 描述符大小 */
    const uint8_t  *p_desc;                  /* 描述符内容 */
}am_usbd_descriptor_t;

#ifdef __cplusplus
}
#endif

#endif /* __AM_USBD_H */

/* end of file */
