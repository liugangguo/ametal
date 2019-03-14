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
 * \brief USB_printer 驱动层实现函数
 *
 * \internal
 * \par Modification history
 * - 1.00 19-02-20  adw, first implementation.
 * \endinternal
 */

/***************************************************************************
  include
***************************************************************************/

#include "am_usb.h"
#include "am_usb_spec.h"
#include "am_usb_osa_bm.h"
#include "am_usbd_keyboard.h"


// HID键盘设备类请求
static void __usbd_keyboard_class_request(void     *p_arg,
                                          uint8_t   b_requrest)
{
//am_usbd_keyboard_t *p_dev = (am_usbd_keyboard_t *)(p_arg);
//
//    AM_USB_OSA_SR_ALLOC();
//
//    AM_USB_OSA_ENTER_CRITICAL();
//
//    switch (b_requrest)
//    {
//        case AM_USBD_KEYBOARD_REPORT_GET: // 0x01
//        {
//            break;
//        }
//
//        case AM_USBD_KEYBOARD_IDLE_GET  : // 0x02
//        {
//            break;
//        }
//
//        case AM_USBD_KEYBOARD_PROTOCOL_GET : // 0x03
//        {
//            break;
//        }
//
//        case AM_USBD_KEYBOARD_REPORT_SET :  // 0x09
//        {
//            break;
//        }
//
//        case AM_USBD_KEYBOARD_IDLE_SET :  // 0x0a
//        {
//            break;
//        }
//
//        case AM_USBD_KEYBOARD_PROTOCOL_SET : // 0x0b
//        {
//            break;
//        }
//
//        default :
//        {
//            break;
//        }
//    }
//
//    AM_USB_OSA_EXIT_CRITICAL();
}

am_usb_status_t am_usbd_keyboard_recv_req(am_usbd_keyboard_handle handle,
                                          uint8_t                *p_buff,
                                          uint8_t                 len)
{
    if(handle == NULL) {
        return AM_USB_STATUS_INVALID_HANDLE;
    }
    return am_usbd_recv(handle->p_dev, handle->p_info->ep_out, p_buff, len);
}

am_usb_status_t am_usbd_keyboard_send(am_usbd_keyboard_handle handle, uint8_t *p_buff, uint8_t len)
{
    if(handle == NULL) {
        return AM_USB_STATUS_INVALID_HANDLE;
    }
    am_usbd_send(handle->p_dev, handle->p_info->ep_in, p_buff, len);
    return AM_USB_STATUS_SUCCESS;
}

// 键盘端点发送数据中断请求
am_usb_status_t am_usbd_keyboard_vendor_request_callback(am_usbd_keyboard_handle handle,
                                                         am_vendor_request_t     pfn_cb,
                                                         void                   *p_arg)
{
    if (handle == NULL) {
        return AM_USB_STATUS_INVALID_HANDLE;
    }

    handle->p_dev->vendor_req.pfn_vendor = pfn_cb;
    handle->p_dev->vendor_req.p_arg      = p_arg;

    return AM_USB_STATUS_SUCCESS;
}

/**
 * \brief 初始化USB
 *
 * \param[in] p_dev     : 指向USB设备
 * \param[in] p_info    : 指向USB设备信息
 *
 * \return USB标准服务操作句柄。如果为 NULL，表明初始化失败。
 */
am_usbd_keyboard_handle am_usbd_keyboard_init (am_usbd_keyboard_t            *p_dev,
                                               const am_usbd_keyboard_info_t *p_info,
                                               am_usbd_dev_t                 *p_usbd)
{
    if (NULL == p_dev  || NULL == p_info) {
        return NULL;
    }

    p_dev->p_dev = p_usbd;
    p_dev->p_dev->class_req.pfn_class = __usbd_keyboard_class_request;
    p_dev->p_dev->class_req.p_arg     = p_dev;

    p_dev->p_info  = p_info;

    am_usbd_init(p_dev->p_dev);

    // 返回控制 handle
    return p_dev;
}

/**
 * \brief USB Device 去初始化
 *
 * \param[in] p_info : 指向USB设备信息
 */
void am_usbd_keyboard_deinit (am_usbd_keyboard_t *p_dev)
{
    if (p_dev != NULL) {
        am_usbd_deinit(p_dev->p_dev);
    }
}


/*end of file */
