/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2010-2020 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
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
#include "am_usbd_cdc_vcom.h"

/* Line codinig of cdc device */
static uint8_t __g_linecoding[AM_USBD_CDC_VCOM_LINE_CODING_SIZE] = {
    /* E.g. 115200 */
    (AM_USBD_CDC_VCOM_LINE_CODING_DTERATE >> 0U) & 0x000000FFU,
    (AM_USBD_CDC_VCOM_LINE_CODING_DTERATE >> 8U) & 0x000000FFU,
    (AM_USBD_CDC_VCOM_LINE_CODING_DTERATE >> 16U) & 0x000000FFU,
    (AM_USBD_CDC_VCOM_LINE_CODING_DTERATE >> 24U) & 0x000000FFU,
    /* 1停止位*/
    AM_USBD_CDC_VCOM_LINE_CODING_CHARFORMAT_1,

    /* 无奇偶校验*/
    AM_USBD_CDC_VCOM_LINE_CODING_PARITYTYPE_NONE,

    /* 8 bit */
    AM_USBD_CDC_VCOM_LINE_CODING_DATABITS_8
};

/* Abstract state of cdc device */
static uint8_t __g_abstractState[AM_USBD_CDC_VCOM_COMM_FEATURE_DATA_SIZE] =
{(AM_USBD_CDC_VCOM_STATUS_ABSTRACT_STATE >> 0U) & 0x00FFU,
 (AM_USBD_CDC_VCOM_STATUS_ABSTRACT_STATE >> 8U) & 0x00FFU};

/* Country code of cdc device */
static uint8_t __g_countryCode[AM_USBD_CDC_VCOM_COMM_FEATURE_DATA_SIZE] =
{(AM_USBD_CDC_VCOM_COUNTRY_SETTING >> 0U) & 0x00FFU,
 (AM_USBD_CDC_VCOM_COUNTRY_SETTING >> 8U) & 0x00FFU};



// HID键盘设备类请求
static void __usbd_cdc_vcom_class_request(void     *p_arg,
                                          uint8_t   b_requrest)
{
    am_usbd_cdc_vcom_t *p_dev = (am_usbd_cdc_vcom_t *)(p_arg);

    uint16_t  w_value = p_dev->p_dev->setup_data.w_value;
    uint8_t  *p_buf = NULL;
//    uint8_t   length = 0;
    uint8_t   array[8] = {0};
    uint8_t   i = 0;

    am_kprintf(" interface :%d \n", p_dev->p_dev->setup_data.bm_request_type);
    am_kprintf("in class request ,b_requrest is 0x%02x \n", b_requrest);
    if (p_dev->p_dev->setup_data.w_index != 0) {  //todo 待修改 通讯类索引 USB_CDC_VCOM_COMM_INTERFACE_INDEX
    	am_kprintf("req error\r\n");
        return ;
    }
//
//    AM_USB_OSA_SR_ALLOC();
//    AM_USB_OSA_ENTER_CRITICAL();

    switch (b_requrest)
    {
        case AM_USB_CDC_REQ_SEND_ENCAP_CMD: // 0x00
        {
            break;
        }

        case AM_USB_CDC_REQ_GET_ENCAP_RESPONSE  : // 0x01
        {
            break;
        }

        case AM_USB_CDC_REQ_SET_COMM_FEATURE : // 0x02
        {
            if ( AM_USB_CDC_FEATURE_ABST_STATE == w_value ) {
                p_buf = __g_abstractState;
            } else if (AM_USB_CDC_FEATURE_COUNTRY_SET == w_value) {
                p_buf = __g_countryCode;
            }
            break;
        }

        case AM_USB_CDC_REQ_GET_COMM_FEATURE : // 0x03
        {
            if ( AM_USB_CDC_FEATURE_ABST_STATE == w_value ) {
                p_buf  = __g_abstractState;
            } else if (AM_USB_CDC_FEATURE_COUNTRY_SET == w_value) {
                p_buf = __g_countryCode;
            }
            am_usbd_send(p_dev->p_dev, 0, p_buf, AM_USBD_CDC_VCOM_COMM_FEATURE_DATA_SIZE);
            break;
        }

        case AM_USB_CDC_REQ_CLEAR_COMM_FEATURE :  // 0x04
        {
            break;
        }

        case AM_USB_CDC_REQ_SET_LINE_CODING :  // 0x20
        {
            p_buf = __g_linecoding;
//            am_kprintf("req20: length %x\n", p_dev->p_dev->setup_data.w_length);
//            am_kprintf("req20: value %x\n", p_dev->p_dev->setup_data.w_value);
            am_usbd_recv(p_dev->p_dev, 0, array, AM_USBD_CDC_VCOM_LINE_CODING_SIZE);
//            am_kprintf("FIFO value:  %x %x %x %x %x %x %x\n", array[0], array[1], array[2], array[3], array[4], array[5], array[6]);
            for (i = 0; i < AM_USBD_CDC_VCOM_LINE_CODING_SIZE; i++) {
            	__g_linecoding[i] = array[i];
            }
            //            am_usbd_send(p_dev->p_dev, 0, p_buf, AM_USBD_CDC_VCOM_LINE_CODING_SIZE);
            break;
        }

        case AM_USB_CDC_REQ_GET_LINE_CODING : // 0x21
        {
//            p_buf  = __g_linecoding;
//            length = AM_USBD_CDC_VCOM_LINE_CODING_SIZE;
            am_usbd_send(p_dev->p_dev, 0, __g_linecoding, AM_USBD_CDC_VCOM_LINE_CODING_SIZE);
            break;
        }

        case AM_USB_CDC_REQ_SET_CTRL_LINE_STATE : // 0x22
        {
//            p_dev->dtestatus = w_value;
//
//            /* activate/deactivate Tx carrier */
//            if (p_dev->dtestatus & AM_USB_CDC_CTRL_SIG_BITMAP_CARRIER_ACT) {
//                p_dev->uartstate |= AM_USB_CDC_UART_STATE_TX_CARRIER;
//            } else {
//                p_dev->uartstate &= (uint16_t)~AM_USB_CDC_UART_STATE_TX_CARRIER;
//            }
//
//            /* activate carrier and DTE */
//            if (p_dev->dtestatus & AM_USB_CDC_CTRL_SIG_BITMAP_DTE_PRESENCE) {
//                p_dev->uartstate |= AM_USB_CDC_UART_STATE_RX_CARRIER;
//            } else {
//                p_dev->uartstate &= (uint16_t)~AM_USB_CDC_UART_STATE_RX_CARRIER;
//            }
//
//            /* Indicates to DCE if DTE is present or not */
//            p_dev->dtepresent = (p_dev->dtestatus & AM_USB_CDC_CTRL_SIG_BITMAP_DTE_PRESENCE) ? 1 : 0;
//
//            /* Initialize the serial state buffer */
//            p_dev->serial_status_buff[0] = AM_USBD_CDC_VCOM_NOTIF_REQUEST_TYPE;
//            p_dev->serial_status_buff[1] = AM_USB_CDC_REQ_SERIAL_STATE;
//            p_dev->serial_status_buff[2] = 0x00;
//            p_dev->serial_status_buff[3] = 0x00;
//            p_dev->serial_status_buff[4] = 0x00; /* wIndex */
//            p_dev->serial_status_buff[5] = 0x00;
//            p_dev->serial_status_buff[6] = AM_USBD_CDC_VCOM_UART_BITMAP_SIZE; /* wLength */
//            p_dev->serial_status_buff[7] = 0x00;
//
//            /* Notifiy to host the line state */
//            p_dev->serial_status_buff[4] = p_dev->p_dev->setup_data.w_index;
//
//            /* Lower byte of UART BITMAP */
//            p_buf = (uint8_t *)&p_dev->serial_status_buff[AM_USBD_CDC_VCOM_NOTIF_PACKET_SIZE + AM_USBD_CDC_VCOM_UART_BITMAP_SIZE - 2];
//            p_buf[0] = p_dev->uartstate & 0xffu;
//            p_buf[1] = (p_dev->uartstate >> 8) & 0xffu;
//            length   = (uint32_t)(AM_USBD_CDC_VCOM_NOTIF_PACKET_SIZE + AM_USBD_CDC_VCOM_UART_BITMAP_SIZE);
//
//            if (0 == p_dev->hassentstate) {
//                am_usbd_send(p_dev->p_dev,
//                             p_dev->p_info->interrupt_in_ep,
//							 p_dev->serial_status_buff,
//                             10);
//                p_dev->hassentstate = 1;
//            }
//
//            /* Update status */
//            if(p_dev->dtestatus & AM_USB_CDC_CTRL_SIG_BITMAP_CARRIER_ACT) {
//                // todo CARRIER_ACTIVATED
//            } else {
//                // todo CARRIER_DEACTIVATED
//            }
//
//            if (p_dev->dtestatus & AM_USB_CDC_CTRL_SIG_BITMAP_DTE_PRESENCE) {
//
//                /* DTE_ACTIVATED */
//                p_dev->starttransactions = 1;
//
//            } else {
//                p_dev->starttransactions = 0;
//            }
//        	am_kprintf("22 req length : %x", p_dev->p_dev->setup_data.w_length);
//        	am_usbd_send(p_dev->p_dev, 0, p_buf, 0);
            break;
        }

        case AM_USB_CDC_REQ_SEND_BREAK:     // 0x23
        {
            break;
        }


        default :
        {
            break;
        }
    }
//
//    AM_USB_OSA_EXIT_CRITICAL();
}

// 中断输入端点回调
static am_usb_status_t __usbd_cdc_interruptin_cb(void *p_arg)
{
    am_usbd_cdc_vcom_handle handle = (am_usbd_cdc_vcom_handle)p_arg;

    if(handle == NULL) {
        return AM_USB_STATUS_INVALID_HANDLE;
    }

    handle->hassentstate = 0;

    return AM_USB_STATUS_ERROR;
}


// 输入端点回调
static am_usb_status_t __usbd_cdc_vcom_bulkin_cb(void *p_arg)
{
    am_usbd_cdc_vcom_handle handle = (am_usbd_cdc_vcom_handle)p_arg;

    if(handle == NULL) {
        return AM_USB_STATUS_INVALID_HANDLE;
    }

//    if (handle->starttransactions == 0) {
//        return AM_USB_STATUS_INVALID_REQUEST;
//    }

    if(handle->pfn_send != NULL){
    	(handle->pfn_send)(handle->p_arg_send);
    }

    return AM_USB_STATUS_SUCCESS;
}


// 输出端点回调
static am_usb_status_t __usbd_cdc_vcom_bulkout_cb(void *p_arg)
{
    am_usbd_cdc_vcom_handle handle = (am_usbd_cdc_vcom_handle)p_arg;
    uint8_t  length = 0;

    if(handle == NULL) {
        return AM_USB_STATUS_INVALID_HANDLE;
    }

//    if (handle->starttransactions == 0) {
//        return AM_USB_STATUS_INVALID_REQUEST;
//    }

    am_usbd_recv(handle->p_dev,
                 handle->p_info->ep_out,
				 handle->p_info->p_buf_out,
				 handle->p_dev->endpoint_info[handle->p_info->ep_out].max_packet_size);

    length = handle->p_dev->endpoint_info[handle->p_info->ep_out].val_length;
    /* 将有效数据长度的后一位置为'\0'，表示数据结束位置 */
    handle->p_info->p_buf_out[length] = '\0';


    if(handle->pfn_recv != NULL){
    	(handle->pfn_recv)(handle->p_arg_recv, handle->p_info->p_buf_out, length);
    }

    return AM_USB_STATUS_SUCCESS;
}





// 接收回调
am_usb_status_t am_usbd_cdc_vcom_recv_cb (am_usbd_cdc_vcom_handle     handle,
		                                  am_cdc_vcom_recv_cb_t       pfn,
                                          void                       *p_arg)
{
    if(handle == NULL) {
        return AM_USB_STATUS_INVALID_HANDLE;
    }

    handle->pfn_recv   = pfn;
    handle->p_arg_recv = p_arg;

    return AM_USB_STATUS_SUCCESS;
}

// 发送回调
am_usb_status_t am_usbd_cdc_vcom_send_cb (am_usbd_cdc_vcom_handle     handle,
		                                  am_cdc_vcom_send_cb_t       pfn,
                                          void                       *p_arg)
{
    if(handle == NULL) {
        return AM_USB_STATUS_INVALID_HANDLE;
    }

    handle->pfn_send   = pfn;
    handle->p_arg_send = p_arg;

    return AM_USB_STATUS_SUCCESS;
}


// 发送数据请求
am_usb_status_t am_usbd_cdc_vcom_send(am_usbd_cdc_vcom_handle  handle,
                                      uint8_t                 *p_buff,
                                      uint8_t                  len)
{
    if(handle == NULL) {
        return AM_USB_STATUS_INVALID_HANDLE;
    }

    if (p_buff == NULL) {
    	return AM_USB_STATUS_INVALID_PARAMETER;
    }
    return am_usbd_send(handle->p_dev, handle->p_info->ep_in, p_buff, len);
}

// 厂商请求
am_usb_status_t am_usbd_cdc_vcom_vendor_request_callback(am_usbd_cdc_vcom_handle handle,
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
am_usbd_cdc_vcom_handle am_usbd_cdc_vcom_init (am_usbd_cdc_vcom_t            *p_dev,
                                               const am_usbd_cdc_vcom_info_t *p_info,
                                               am_usbd_dev_t                 *p_usbd)
{
	uint8_t i = 0;
    if (NULL == p_dev  || NULL == p_info) {
        return NULL;
    }

    p_dev->p_dev = p_usbd;
    p_dev->p_dev->class_req.pfn_class = __usbd_cdc_vcom_class_request;
    p_dev->p_dev->class_req.p_arg     = p_dev;

    p_dev->p_info  = p_info;

    p_dev->dtepresent        = 0;
    p_dev->dtestatus         = 0;
    p_dev->hassentstate      = 0;
    p_dev->starttransactions = 0;
    p_dev->uartstate         = 0;

    // 不要使用memset
    for (i = 0; i < AM_USBD_CDC_VCOM_NOTIF_PACKET_SIZE + AM_USBD_CDC_VCOM_UART_BITMAP_SIZE; i++) {
        *(p_dev->serial_status_buff + i) = 0;
    }
//    memset(p_dev->serial_status_buff, 0, AM_USBD_CDC_VCOM_NOTIF_PACKET_SIZE + AM_USBD_CDC_VCOM_UART_BITMAP_SIZE);

    /* 定义中断端点回调函数*/
    p_dev->p_dev->endpoint_info[p_dev->p_info->interrupt_in_ep].pfn_callback = __usbd_cdc_interruptin_cb;
    p_dev->p_dev->endpoint_info[p_dev->p_info->interrupt_in_ep].p_arg        = p_dev;

    /* 定义输入端点回调函数*/
    p_dev->p_dev->endpoint_info[p_dev->p_info->ep_in].pfn_callback = __usbd_cdc_vcom_bulkin_cb;
    p_dev->p_dev->endpoint_info[p_dev->p_info->ep_in].p_arg        = p_dev;

    /* 定义输出端点回调函数*/
    p_dev->p_dev->endpoint_info[p_dev->p_info->ep_out].pfn_callback = __usbd_cdc_vcom_bulkout_cb;
    p_dev->p_dev->endpoint_info[p_dev->p_info->ep_out].p_arg        = p_dev;


    am_usbd_init(p_dev->p_dev);

    // 返回控制 handle
    return p_dev;
}

/**
 * \brief USB Device 去初始化
 *
 * \param[in] p_info : 指向USB设备信息
 */
void am_usbd_cdc_vcom_deinit (am_usbd_cdc_vcom_t *p_dev)
{
    if (p_dev != NULL) {
        am_usbd_deinit(p_dev->p_dev);
    }
}


/*end of file */
