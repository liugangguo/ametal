/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/   http://www.zlgmcu.com/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief USB DEVICE驱动
 *
 * \internal
 * \par Modification History
 * - 1.00 19-03-07  adw, first implementation.
 * \endinternal
 */

#ifndef __AM_ZMF159_USBD_H_
#define __AM_ZMF159_USBD_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "am_usbd.h"
#include "am_usb_dci.h"
#include "amhw_zmf159_usb.h"

#define  AM_ZMF159MAX_EP_NUM         7

#define EP_NUM                      (4)

//#define ENDP0   ((uint8_t)0)
//#define ENDP1   ((uint8_t)1)
//#define ENDP2   ((uint8_t)2)
//#define ENDP3   ((uint8_t)3)
//#define ENDP4   ((uint8_t)4)



//typedef struct line_coding {
//  uint32_t bitrate;
//  uint8_t format;
//  uint8_t paritytype;
//  uint8_t datatype;
//}line_coding_t;

typedef enum _CONTROL_STATE {
  WAIT_SETUP,       /* 0 */
  SETTING_UP,       /* 1 */
  IN_DATA,          /* 2 */
  OUT_DATA,         /* 3 */
  LAST_IN_DATA,     /* 4 */
  LAST_OUT_DATA,    /* 5 */
  WAIT_STATUS_IN,   /* 6 */
  WAIT_STATUS_OUT,  /* 7 */
  STALLED,          /* 8 */
  PAUSE             /* 9 */
} CONTROL_STATE;    /* The state machine states of a control pipe */


/**
 * \brief
 */
typedef struct am_zmf159_usbd_devinfo{
    uint32_t usb_regbase;          /**< \brief usb 基地址*/

    int inum;                      /**< \brief 中断号 */

    void (*pfn_plfm_init)(void);   /**< \brief 平台初始化函数  */

    void (*pfn_plfm_deinit)(void); /**< \brief 平台去初始化函数 */

    const am_usbd_devinfo_t *p_devinfo;

}am_zmf159_usbd_devinfo_t;


typedef struct am_zmf159_usbd_dev am_zmf159_usbd_dev_t;


typedef struct am_zmf159_usbd_dev
{
    am_usbd_dev_t  isa;

    uint8_t state;            /* of type CONTROL_STATE */
//    uint8_t cur_feature;
//    uint8_t cur_config;       /* Selected configuration */
//    uint8_t cur_interface;    /* Selected interface of current configuration */
//    uint8_t cur_alt;          /* Selected Alternate Setting of current
//                                       interface*/

    uint8_t ep_num;           /* Number of endpoints that are used */
    uint8_t config_num;       /* Number of configuration available */

//    uint8_t sta_info;

    uint8_t rx_odd[16] ;
    uint8_t tx_odd[16] ;

    uint8_t ep_indata_num[16] ;

    am_bool_t data_mul;

    uint8_t *rx_buf;
    uint8_t  max_packsizee;

    amhw_zmf159_usb_bdt_t *p_usb_bdt;

    const am_zmf159_usbd_devinfo_t *p_info;

}am_zmf159_device_t;



///*******************************************************************************
//   外部声明函数
//*******************************************************************************/

// 临时
am_usbd_dev_t *am_zmf159_usbd_init(am_zmf159_device_t             *,
                                       const am_zmf159_usbd_devinfo_t *);


//am_usbd_dev_t *am_zmf159_usbd_init (am_zmf159_usbd_dev_t           *p_dev,
//                                      const am_zmf159_usbd_devinfo_t *p_info);

void am_zmf159_usbd_deinit (const am_zmf159_usbd_devinfo_t *p_info);

/**
 * @} mm32_if_usbd
 */

#ifdef __cplusplus
}
#endif







#endif /* __AM_ZMF159_USBD_H_ */

/* end of file */
