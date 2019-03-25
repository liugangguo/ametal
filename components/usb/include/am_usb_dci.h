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
 * \brief     USBD标准接口
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-27  bob, first implementation.
 * \endinternal
 */

#ifndef __AM_USB_DCI_H
#define __AM_USB_DCI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_usbd.h"
#include "am_usb_spec.h"


/**
 * \addtogroup am_if_usb_dci
 * \copydoc am_usb_dci.h
 * @{
 */

/** \brief Control type for controller */
typedef enum am_usbd_control_type {
    AM_USBD_CONTROL_RUN = 0U,            /**< \brief 使用设备 */
    AM_USBD_CONTROL_STOP,                /**< \brief 停止设备 */
    AM_USBD_CONTROL_ENDPOINT_INIT,       /**< \brief 初始化设备 */
    AM_USBD_CONTROL_ENDPOINT_DEINIT,     /**< \brief 解初始化 */
    AM_USBD_CONTROL_ENDPOINT_STALL,      /**< \brief 端点阻塞 */
    AM_USBD_CONTROL_ENDPOINT_UNSTALL,    /**< \brief 端点非阻塞 */
    AM_USBD_CONTROL_GET_DEVICE_STATUS,   /**< \brief 获取设备状态 */
    AM_USBD_CONTROL_GET_ENDPOINT_STATUS, /**< \brief 获取端点状态 */
	AM_USBD_CONTROL_SET_ENDPOINT_STATUS, /**< \brief 设置端点状态 */
    AM_USBD_CONTROL_SET_DEVICE_ADDRESS,  /**< \brief 设置设备地址 */
    AM_USBD_CONTROL_GET_SYNCH_FRAME,     /**< \brief 获取同步帧 */
    AM_USBD_CONTROL_RESUME,              /**< \brief 设备唤醒 */
    AM_USBD_CONTROL_SET_DEFAULT_STATUS,  /**< \brief 设置控制器默认值 */
    AM_USBD_CONTROL_GET_SPEED,           /**< \brief 获取当前速度 */
    AM_USBD_CONTROL_GET_OTG_STATUS,      /**< \brief 获取OTG状态 */
    AM_USBD_CONTROL_SET_OTG_STATUS,      /**< \brief 设置OUG状态 */
    AM_USBD_CONTROL_SET_TEST_MODE,       /**< \brief 测试模式 */
} am_usbd_control_type_t;

/** \brief 初始化 */
typedef am_usb_status_t (*am_usbd_init_t)(am_usbd_handle_t handle);

/** \brief 解初始化 */
typedef am_usb_status_t (*am_usbd_deinit_t)(am_usbd_handle_t handle);

/** \brief 发送函数 */
typedef am_usb_status_t (*am_usbd_send_t)(am_usbd_handle_t handle,
                                         uint8_t           endpoint,
                                         uint8_t          *p_buffer,
                                         uint32_t          length);

/** \brief 接收函数 */
typedef am_usb_status_t (*am_usbd_recv_t)(am_usbd_handle_t handle,
                                         uint8_t           endpoint,
                                         uint8_t          *p_buffer,
                                         uint32_t          length);

/** \brief 取消 */
typedef am_usb_status_t (*am_usbd_cancel_t)(am_usbd_handle_t handle,
                                           uint8_t           endpoint);

/** \brief 控制 */
typedef am_usb_status_t (*am_usbd_control_t)(am_usbd_handle_t       handle,
                                             am_usbd_control_type_t command,
                                             void                  *p_param);

/** \brief 端点回调函数类型*/
typedef am_usb_status_t (*am_usbd_ep_callback_t)(void *p_arg);

/* 厂商请求回调函数类型.*/
typedef void (*am_vendor_request_t)(void *p_arg, uint8_t b_requrest);

/* 类请求回调函数类型.*/
typedef uint8_t (*am_class_request_t)(void *p_arg, uint8_t b_requrest);

/** \brief usb device 控制接口结构体 */
typedef struct am_usbd_interface {
    am_usbd_init_t    pfn_device_init;      /**< \brief 设备初始化 */
    am_usbd_deinit_t  pfn_device_deinit;    /**< \brief 设备初始化 */
    am_usbd_send_t    pfn_device_send;      /**< \brief 设备发送数据 */
    am_usbd_recv_t    pfn_device_recv;      /**< \brief 设备接收数据 */
    am_usbd_cancel_t  pfn_device_cancel;    /**< \brief 取消端点传输 */
    am_usbd_control_t pfn_device_control;   /**< \brief 设备控制函数 */
} am_usbd_interface_t;


/** \brief 端点状态结构 */
typedef struct am_usbd_ep_info {
    uint8_t                inuse;           /**< \brief 端点是否会被使用 */
    uint8_t                stalled;         /**< \brief 端点是否阻塞 */
    uint8_t                ep_address;      /**< \brief 端点地址（方向 + 端点号）*/

    /** \brief 端点传输类 型 (控制传输, 同步传输, 批量传输, 中断传输)*/
    uint8_t                transfer_type;   /**< \brief 端点数据类型*/
    uint8_t                val_length;      /**< \brief 端点有效数据长度*/
    uint16_t               max_packet_size; /**< \brief 端点一次性传输的最大包大小 */
    am_usbd_ep_callback_t  pfn_callback;    /**< \brief 端点回调函数指针 */
    void                  *p_arg;           /**< \brief 端点回调参数 */
} am_usbd_ep_info_t;


/** \brief USB设备信息结构体*/
typedef struct am_usbd_devinfo {
    const am_usbd_descriptor_t *p_descriptor;       /**< \brief 描述符首地址 */
    uint8_t                     descriptor_num;     /**< \brief 描述符个数 */
}am_usbd_devinfo_t ;

/* 类请求回调函数结构体定义*/
typedef struct am_usbd_class_req_callback {
	am_class_request_t   pfn_class;   /**< \brief 类请求回调函数*/
	void                *p_arg;       /**< \brief 类请求回调函数参数*/
}am_usbd_class_req_cb_t;

/* 厂商请求回调函数结构体定义*/
typedef struct am_vendor_req_callback {
	am_vendor_request_t  pfn_vendor;  /**< \brief 厂商请求回调函数*/
	void                *p_arg;       /**< \brief 厂商请求回调函数参数*/
}am_usbd_vendor_req_cb_t;


/** \brief 定义usb device*/
typedef struct am_usbd_dev am_usbd_dev_t;

/** \brief 定义标准设备请求函数类型*/
typedef void (*am_std_request_t)(am_usbd_dev_t *p_dev);


typedef struct __endpoint_info
{
  uint16_t  Usb_wLength;
  uint16_t  Usb_wOffset;
  uint16_t  PacketSize;
  uint8_t   *(*CopyData)(void *p_arg, uint16_t Length);
}am_data_info_t;


/** \brief USB device struct  */
struct am_usbd_dev {
	/**
	 *  \brief 控制器handle
	 *
	 *  保留底层控制器handle 为了上层接口调用，例如an_usbd_send函数
	 */
	am_usbd_handle_t      ctrl_handle;

    uint8_t               device_address; /**< \brief 设备地址 */
    uint8_t               state;          /**< \brief 设备状态 */

    uint8_t               cur_feature;
    uint8_t               cur_config;       /* Selected configuration */
    uint8_t               cur_interface;    /* Selected interface of current configuration */
    uint8_t               cur_alt;          /* Selected Alternate Setting of current
                                             interface*/

    uint8_t sta_info;


//    uint8_t                    running_ctrl_state;

    const am_usbd_interface_t *p_interface;    /**< \brief 控制器接口 */

    /** \brief 标准设备请求函数指针数组的指针*/
    const am_std_request_t    *pfn_std_request;

    /** \brief USB device 信息结构体, 存放描述符信息*/
    const am_usbd_devinfo_t   *p_info;

    /**< \brief 类请求回调函数, 在USB类中被赋值*/
    am_usbd_class_req_cb_t    class_req;

    /**< \brief 厂商请求回调函数，由具体的产商定义功能，在支持的类中有对应接口 */
    am_usbd_vendor_req_cb_t   vendor_req;


    /** \brief 接收到的setup包中的数据USB标准设备请求结构 */
    am_usb_setup_t            setup_data;

    /** \brief 端点状态 */
    am_usbd_ep_info_t         endpoint_info[AM_USBD_MAX_EP_CNT];

    am_data_info_t            ctrl_info;
};

/*****************************************************************************
 * API
 ****************************************************************************/

am_static_inline
am_usb_status_t am_usbd_init(am_usbd_dev_t  *p_dev)
{
    return p_dev->p_interface->pfn_device_init(p_dev->ctrl_handle);
}

/**
 * \brief 初始化 USB
 *
 * \param[in] handle                  usb设备句柄
 *
 * \retval  AM_USB_STATUS_SUCCESS               通知成功
 * \retval  AM_USB_STATUS_ERROR                 通知失败
 * \retval  AM_USB_STATUS_INVALID_REQUEST       USB 响应错误
 * \retval  AM_USB_STATUS_INVALID_HANDLE        无效的句柄
 * \retval  AM_USB_STATUS_INVALID_PARAMETER     参数错误
 */
am_static_inline
am_usb_status_t am_usbd_send(am_usbd_dev_t   *p_dev,
                             uint8_t          endpoint_address,
                             uint8_t         *buffer,
                             uint32_t         length)
{
    return p_dev->p_interface->pfn_device_send(p_dev->ctrl_handle,
                                               endpoint_address,
                                               buffer,
                                               length);
}

/**
 * \brief USB接收数据
 *
 */
am_static_inline
am_usb_status_t am_usbd_recv(am_usbd_dev_t   *p_dev,
                             uint8_t          endpoint,
                             uint8_t         *buffer,
                             uint32_t         length)
{
    return p_dev->p_interface->pfn_device_recv(p_dev->ctrl_handle,
                                               endpoint,
                                               buffer,
                                               length);
}

/**
 * \brief USB设置控制类型
 *
 */
am_static_inline
am_usb_status_t am_usbd_control(am_usbd_dev_t         *p_dev,
                                am_usbd_control_type_t type,
                                void                  *param)
{
    return p_dev->p_interface->pfn_device_control(p_dev->ctrl_handle,
                                                  type,
                                                  param);
}


/**
 * \brief USB取消操作
 *
 */
am_static_inline
am_usb_status_t am_usbd_cancel(am_usbd_dev_t   *p_dev,
                               uint8_t          endpoint)
{
    return p_dev->p_interface->pfn_device_cancel(p_dev->ctrl_handle, endpoint);
}

/**
 * \brief USB解初始化操作
 *
 */
am_static_inline
am_usb_status_t am_usbd_deinit(am_usbd_dev_t   *p_dev)
{
    return p_dev->p_interface->pfn_device_deinit(p_dev->ctrl_handle);
}

am_static_inline
void am_usbd_protocol_stack_version(am_usb_version_t *p_usb)
{
	p_usb->major  = AM_USB_STACK_VERSION_MAJOR;
	p_usb->minor  = AM_USB_STACK_VERSION_MINOR;
	p_usb->bugfix = AM_USB_STACK_VERSION_BUGFIX;
}
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_USB_DCI_H */
