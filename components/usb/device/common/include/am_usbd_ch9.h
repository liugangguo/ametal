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
 * \brief USBD CH9
 *
 * \internal
 * \par Modification history
 * - 1.00 16-9-27  bob, first implementation.
 * \endinternal
 */

#ifndef __AM_USBD_CH9_H
#define __AM_USBD_CH9_H

#include "ametal.h"
#include "am_usb_dci.h"

#ifdef __cplusplus
extern "C" {
#endif


uint8_t *am_usb_ch9_config_get(void *p_arg, uint16_t length);

uint8_t am_usb_ch9_config_set(void *p_arg);


uint8_t *am_usb_ch9_interface_get(void *p_arg, uint16_t length);

uint8_t am_usb_ch9_interface_set(void *p_arg);

uint8_t *am_usb_ch9_status_get(void *p_arg, uint16_t length);

uint8_t am_usb_ch9_feature_clr(void *p_arg);

uint8_t am_usb_ch9_ep_feature_set(void *p_arg);

uint8_t am_usb_ch9_dev_feature_set(void *p_arg);


uint8_t *std_descriptor_get(void                       *p_arg,
							uint16_t                    length,
							const am_usbd_descriptor_t *p_desc);

/*__std_descriptor_get */
uint8_t *am_usb_ch9_descriptor_get(void *p_arg, uint16_t length);



/* address set */
void am_usb_ch9_addr_set(am_usbd_dev_t *p_dev);


#ifdef __cplusplus
}
#endif

#endif /* __AM_USBD_CH9_H */

/* end of file */
