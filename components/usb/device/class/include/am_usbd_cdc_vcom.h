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
 * \brief USBD cdc uart
 *
 * \internal
 * \par Modification history
 * - 1.00 19-02-21  adw, first implementation.
 * \endinternal
 */

#ifndef __AM_USBD_CDC_VCOM_H
#define __AM_USBD_CDC_VCOM_H

#include "am_usb.h"
#include "am_usb_dci.h"
#include "am_usb_cdc.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/** \beief communication interface codes*/
#define AM_USBD_CDC_VCOM_CIC_CLASS                (AM_USB_CDC_COMM_CLASS)
#define AM_USBD_CDC_VCOM_CIC_SUBCLASS             (AM_USB_CDC_COMM_SUB_ABS)
#define AM_USBD_CDC_VCOM_CIC_PROTOCOL             (AM_USB_CDC_COMM_PROT_AT_ITU_T)

/** \beief data interface codes*/
#define AM_USBD_CDC_VCOM_DIC_CLASS                (AM_USB_CDC_DATA_CLASS)
#define AM_USBD_CDC_VCOM_DIC_SUBCLASS             (0x00)
#define AM_USBD_CDC_VCOM_DIC_PROTOCOL             (AM_USB_CDC_INTER_PROT_NO_PROT)


/* Currently configured line coding */
#define AM_USBD_CDC_VCOM_LINE_CODING_SIZE             (0x07U)

#define AM_USBD_CDC_VCOM_LINE_CODING_DTERATE          (9600) /**< \brief [D0:D3], data terminal rate*/

#define AM_USBD_CDC_VCOM_LINE_CODING_CHARFORMAT_1     (0x00U)   /**< \brief [D4], stop bit*/
#define AM_USBD_CDC_VCOM_LINE_CODING_CHARFORMAT_1_5   (0x01U)
#define AM_USBD_CDC_VCOM_LINE_CODING_CHARFORMAT_2     (0x02U)

#define AM_USBD_CDC_VCOM_LINE_CODING_PARITYTYPE_NONE  (0x00U)
#define AM_USBD_CDC_VCOM_LINE_CODING_PARITYTYPE_ODD   (0x01U)
#define AM_USBD_CDC_VCOM_LINE_CODING_PARITYTYPE_EVEN  (0x02U)
#define AM_USBD_CDC_VCOM_LINE_CODING_PARITYTYPE_MARK  (0x03U)
#define AM_USBD_CDC_VCOM_LINE_CODING_PARITYTYPE_SPACE (0x04U)

#define AM_USBD_CDC_VCOM_LINE_CODING_DATABITS_5       (0x05U)
#define AM_USBD_CDC_VCOM_LINE_CODING_DATABITS_6       (0x06U)
#define AM_USBD_CDC_VCOM_LINE_CODING_DATABITS_7       (0x07U)
#define AM_USBD_CDC_VCOM_LINE_CODING_DATABITS_8       (0x08U)
#define AM_USBD_CDC_VCOM_LINE_CODING_DATABITS_16      (0x10U)

/* Communications feature */
#define AM_USBD_CDC_VCOM_COMM_FEATURE_DATA_SIZE       (0x02U)
#define AM_USBD_CDC_VCOM_STATUS_ABSTRACT_STATE        (0x0000U)
#define AM_USBD_CDC_VCOM_COUNTRY_SETTING              (0x0000U)

/* Notification of serial state */
#define AM_USBD_CDC_VCOM_NOTIF_PACKET_SIZE            (0x08)
#define AM_USBD_CDC_VCOM_UART_BITMAP_SIZE             (0x02)
#define AM_USBD_CDC_VCOM_NOTIF_REQUEST_TYPE           (0xA1)

/*  Control Signal Bitmap Values for SetControlLineState*/
#define AM_USBD_CDC_VCOM_LINE_STATE_RTS_ACT           (0x02)
#define AM_USBD_CDC_VCOM_LINE_STATE_RTS_DEACT         (0x00)
#define AM_USBD_CDC_VCOM_LINE_STATE_DTR_PRESENT       (0x01)
#define AM_USBD_CDC_VCOM_LINE_STATE_DTR_NO_PRESENT    (0x00)

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif


// 接收回调函数类型
typedef void (*am_cdc_vcom_recv_cb_t)(void *p_arg, uint8_t *p_buf, uint8_t len);

typedef void (*am_cdc_vcom_send_cb_t)(void *p_arg);


/** \brief 打印机信息结构体 */
typedef struct am_usbd_cdc_vcom_info {

    uint8_t interrupt_in_ep;

    uint8_t  ep_in;
    uint8_t  ep_out;
//    uint8_t *p_buf_in;
    uint8_t *p_buf_out;
} am_usbd_cdc_vcom_info_t;


/** \brief usb device printer struct */
typedef struct am_usbd_cdc_vcom {
    am_usbd_dev_t                 *p_dev;      /**< \brief 保存usb设备类指针*/
    const am_usbd_cdc_vcom_info_t *p_info;     /**< \brief 串口设备信息*/

    uint8_t serial_status_buff[AM_USBD_CDC_VCOM_NOTIF_PACKET_SIZE + AM_USBD_CDC_VCOM_UART_BITMAP_SIZE];

    uint8_t starttransactions;
    uint8_t hassentstate;

    /* Define the infomation relates to abstract control model */
    uint8_t   dtepresent;       // 表示数据终端设备（DTE）是否存在
    uint8_t   dtestatus;        // 终端设备状态
    uint16_t  uartstate;        // CDC 设备串口状态

    am_cdc_vcom_recv_cb_t  pfn_recv;
    void                  *p_arg_recv;

    am_cdc_vcom_send_cb_t  pfn_send;
    void                  *p_arg_send;

} am_usbd_cdc_vcom_t;

/*USBD keyboard 通用句柄*/
typedef am_usbd_cdc_vcom_t  *am_usbd_cdc_vcom_handle;



/**
 * \brief 初始化USB
 *
 * \param[in] p_dev     : 指向USB设备
 * \param[in] p_info    : 指向USB设备信息
 *
 * \return USB标准服务操作句柄。如果为 NULL，表明初始化失败。
 */
am_usbd_cdc_vcom_handle am_usbd_cdc_vcom_init (am_usbd_cdc_vcom_t            *p_dev,
                                               const am_usbd_cdc_vcom_info_t *p_info,
                                               am_usbd_dev_t                 *p_usbd);

/**
 * \brief USB Device 去初始化
 *
 * \param[in] p_info : 指向USB设备信息
 */
void am_usbd_cdc_vcom_deinit (am_usbd_cdc_vcom_t *p_dev);


am_usb_status_t am_usbd_cdc_vcom_vendor_request_callback(am_usbd_cdc_vcom_handle handle,
                                                         am_vendor_request_t     pfn_cb,
                                                         void                   *p_arg);


am_usb_status_t am_usbd_cdc_vcom_send(am_usbd_cdc_vcom_handle handle, uint8_t *p_buff, uint8_t len);

// 接收回调函数
am_usb_status_t am_usbd_cdc_vcom_recv_cb (am_usbd_cdc_vcom_handle     handle,
		                                  am_cdc_vcom_recv_cb_t       pfn,
                                          void                       *p_arg);

// 发送回调函数
am_usb_status_t am_usbd_cdc_vcom_send_cb (am_usbd_cdc_vcom_handle     handle,
                                          am_cdc_vcom_send_cb_t       pfn,
                                          void                       *p_arg);


#if defined(__cplusplus)
}
#endif


#endif /* __AM_USBD_CDC_VCOM_H */

/* end of file */



