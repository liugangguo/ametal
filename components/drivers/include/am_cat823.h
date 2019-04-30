/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief  CAT823 drivers for WDT standard interface
 * 
 * \internal
 * \par Modification history
 * - 1.00 19-04-28  ipk, first implementation.
 * \endinternal
 */

#ifndef __AM_CAT823_H
#define __AM_CAT823_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_wdt.h"
#include "am_timer.h"
    
/** 
 * \addtogroup am_cat823_if_iwdt
 * \copydoc am_cat823_iwdt.h
 * @{
 */

/**
 * \brief CAT823 WDT device information
 */
typedef struct am_cat823_devinfo {
    int    wdi_pin;
} am_cat823_devinfo_t;
    
/**
 * \brief CAT823 IWDT  device structure
 */
typedef struct am_cat823_dev {
    am_wdt_serv_t               wdt_serv;   /**< \brief for standard IWDT service         */
    const am_cat823_devinfo_t  *p_devinfo;  /**< \brief Pointer to the device information */
} am_cat823_dev_t;

/**
 * \brief Initialize the CAT823 as WDT
 *
 * \param[in] p_dev     : Pointer to the IWDT device
 * \param[in] p_devinfo : Pointer to the IWDT device information to initialize
 *
 * \return The handle for standard IWDT port.if NULL,Indicate that initialize failed
 */
am_wdt_handle_t am_cat823_init(am_cat823_dev_t           *p_dev,
                               const am_cat823_devinfo_t *p_devinfo);

/**
 * \brief De-initialize the WDT
 * \param[in] p_dev : Pointer to the WDT device
 * \return None
 */
void am_cat823_deinit(am_cat823_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_CAT823_H */

/* end of file */
