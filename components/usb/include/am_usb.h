/**
 * \file
 * \brief     USB
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-27  bob, first implementation.
 * \endinternal
 */

#ifndef __AM_USB_H
#define __AM_USB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_usb_osa.h"
#include "am_usb_misc.h"
/*!
 * @addtogroup usb_drv
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/** \brief 定义USB协议栈主版本号 */
#define AM_USB_STACK_VERSION_MAJOR  (1U)
/** \brief 定义USB协议栈负版本号 */
#define AM_USB_STACK_VERSION_MINOR  (1U)
/** \brief 定义USB协议栈修复版本号 */
#define AM_USB_STACK_VERSION_BUGFIX (0U)

#define AM_USB_VERSION              0x0110

/** \brief USB 协议栈版本号掩码 */
#define AM_USB_MAKE_VERSION(major, minor, bugfix) \
                     (((major) << 16) | ((minor) << 8) | (bugfix))

/** \brief USB错误码 */
typedef enum am_usb_status {
    AM_USB_STATUS_SUCCESS = 0x00U,              /**< \brief Success */
    AM_USB_STATUS_ERROR,                        /**< \brief Failed */

    AM_USB_STATUS_BUSY,                         /**< \brief 忙状态 */
    AM_USB_STATUS_INVALID_HANDLE,               /**< \brief handle 错误 */
    AM_USB_STATUS_INVALID_PARAMETER,            /**< \brief 参数错误 */
    AM_USB_STATUS_INVALID_REQUEST,              /**< \brief 响应错误 */
    AM_USB_STATUS_CONTROLLER_NOT_FOUND,         /**< \brief 控制接口无法找到 */
    AM_USB_STATUS_INVALID_CONTROLLER_INTERFACE, /**< \brief 非法接口 */

    AM_USB_STATUS_NOT_SUPPORTED,     /**< \brief 不支持 */
    AM_USB_STATUS_RETRY,             /**< \brief 重试 */
    AM_USB_STATUS_TRANSFER_STALL,    /**< \brief 端口阻塞 */
    AM_USB_STATUS_TRANSFER_FAILED,   /**< \brief 传输失败 */
    AM_USB_STATUS_ALLOC_FAIL,        /**< \brief 分配失败 */
    AM_USB_STATUS_LACK_SWAP_BUFFER,  /**< \brief Insufficient swap buffer for KHCI */
    AM_USB_STATUS_TRANSFER_CANCEL,   /**< \brief 传输取消 */
    AM_USB_STATUS_BAND_WIDTH_FAIL,   /**< \brief 带宽分配失败 */
    AM_USB_STATUS_MSD_STATUS_FAIL,   /**< \brief For MSD, the CSW status means fail */
} am_usb_status_t;

/** \brief USB host handle type define */
typedef void *am_usbh_handle_t;

/** \brief USB device handle type define. */
typedef void *am_usbd_handle_t;

/** \brief USB OTG handle type define */
typedef void *am_usb_otg_handle;

/**
* \brief USB协议版本号域
*/
typedef struct am_usb_version {
    uint8_t major;  /**< \brief 主版本号 */
    uint8_t minor;  /**< \brief 副版本号 */
    uint8_t bugfix; /**< \brief 修复版本号 */
} am_usb_version_t;

/*! @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_USB_H */
