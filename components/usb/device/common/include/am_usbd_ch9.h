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

void am_usbd_ch9_std_request(am_usbd_dev_t *p_dev);

#ifdef __cplusplus
}
#endif

#endif /* __AM_USBD_CH9_H */

/* end of file */
