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
 * - 1.00 19-03-20  adw, first implementation.
 * \endinternal
 */

/***************************************************************************
  include
***************************************************************************/

#include "am_usb.h"
#include "am_usb_spec.h"
#include "am_usb_osa_bm.h"
#include "am_usbd_cdc_vcom.h"


line_coding_t linecoding = {
    9600,   /* baud rate*/
    0x00,   /* stop bits-1*/
    0x00,   /* parity - none*/
    0x08    /* no. of bits 8*/
};


/*******************************************************************************
* Function Name  : Virtual_Com_Port_GetLineCoding.
* Description    : send the linecoding structure to the PC host.
* Input          : Length.
* Output         : None.
* Return         : Inecoding structure base address.
*******************************************************************************/
static uint8_t *__virtual_com_port_getlinecoding(void *p_arg, uint16_t Length)
{
	am_usbd_dev_t  *p_dev = (am_usbd_dev_t *)p_arg;
    if (Length == 0) {
        p_dev->ctrl_info.Usb_wLength = sizeof(linecoding);
        return NULL;
    }
    return(uint8_t *)&linecoding;
}

/*******************************************************************************
* Function Name  : Virtual_Com_Port_SetLineCoding.
* Description    : Set the linecoding structure fields.
* Input          : Length.
* Output         : None.
* Return         : Linecoding structure base address.
*******************************************************************************/
static uint8_t *__virtual_com_port_setlinecoding(void *p_arg, uint16_t Length)
{
	am_usbd_dev_t *p_dev = (am_usbd_dev_t *)p_arg;

    if (Length == 0) {
        p_dev->ctrl_info.Usb_wLength = sizeof(linecoding);
        return NULL;
    }
    return(uint8_t *)&linecoding;
}


/*******************************************************************************
* Function Name  : Virtual_Com_Port_Data_Setup
* Description    : handle the data class specific requests
* Input          : Request Nb.
* Output         : None.
* Return         : USB_UNSUPPORT or USB_SUCCESS.
*******************************************************************************/
static uint8_t vcom_class_req(void *p_arg, uint8_t num)
{
	am_usbd_dev_t  *p_dev = (am_usbd_dev_t *)p_arg;
    uint8_t  *(*CopyRoutine)(void *p_arg, uint16_t);

    CopyRoutine = NULL;

    switch (num) {

    case AM_USB_CDC_REQ_SET_COMM_FEATURE :
    {
    	return AM_USB_STATUS_SUCCESS;
    }
    case AM_USB_CDC_REQ_GET_LINE_CODING :
    {
        if (p_dev->setup_data.bm_request_type & (AM_USB_REQ_TYPE_TYPE_CLASS | AM_USB_REQ_TYPE_RECIPIENT_INTERFACE))
        {
            CopyRoutine = __virtual_com_port_getlinecoding;
        }
        break;
    }

    case AM_USB_CDC_REQ_SET_LINE_CODING:
    {
        if (p_dev->setup_data.bm_request_type & (AM_USB_REQ_TYPE_TYPE_CLASS | AM_USB_REQ_TYPE_RECIPIENT_INTERFACE))
        {
            CopyRoutine = __virtual_com_port_setlinecoding;
        }
        break;
    }

    case AM_USB_CDC_REQ_SET_CTRL_LINE_STATE:
    {
        return AM_USB_STATUS_SUCCESS;
    }

    default :
        break;
    }

    if (CopyRoutine == NULL) {
        return AM_USB_STATUS_NOT_SUPPORTED;
    }

    p_dev->ctrl_info.CopyData = CopyRoutine;
    p_dev->ctrl_info.Usb_wOffset = 0;

    (*CopyRoutine)(p_dev, 0);
    return AM_USB_STATUS_SUCCESS;
}


am_usb_status_t am_usbd_cdc_vcom_send(am_usbd_cdc_vcom_handle handle, uint8_t *p_buff, uint8_t len)
{
	am_usbd_send(handle->p_dev->ctrl_handle,
                 handle->p_info->ep_in,
				 p_buff,
				 len);

    return AM_USB_STATUS_SUCCESS;
}



/*******************************************************************************
* Function Name  : EP3_IN_Callback
* Description    : USB数据接收
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
static am_usb_status_t __vcom_recv_cb(void *p_arg)
{
    am_usbd_cdc_vcom_t*p_dev = (am_usbd_cdc_vcom_t * )p_arg;

    am_usbd_recv(p_dev->p_dev->ctrl_handle,
    			 p_dev->p_info->ep_out,
				 p_dev->p_info->p_buf_out,
				 0x40);

    return AM_USB_STATUS_SUCCESS;
}

/*******************************************************************************
* Function Name  : EP1_IN_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
static am_usb_status_t __vcom_send_cb(void *p_arg)
{
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

	p_dev->p_dev = p_usbd;
	p_dev->p_info = p_info;

    p_dev->p_dev->endpoint_info[p_dev->p_info->ep_in].pfn_callback = __vcom_send_cb;
    p_dev->p_dev->endpoint_info[p_dev->p_info->ep_in].p_arg = p_dev;

    p_dev->p_dev->endpoint_info[p_dev->p_info->ep_out].pfn_callback = __vcom_recv_cb;
    p_dev->p_dev->endpoint_info[p_dev->p_info->ep_out].p_arg = p_dev;

    p_dev->p_dev->class_req.pfn_class = vcom_class_req;
    p_dev->p_dev->class_req.p_arg = p_usbd;

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
