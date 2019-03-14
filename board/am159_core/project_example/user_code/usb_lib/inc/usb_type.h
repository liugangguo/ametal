/******************** (C) COPYRIGHT 2018 MindMotion ********************
* File Name          : usb_type.h
* Version            : V1.0.0
* Date               : 2018/08/21
* Description        : Type definitions used by the USB Library
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, MindMotion SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_TYPE_H
#define __USB_TYPE_H

/* Includes ------------------------------------------------------------------*/
#include "ametal.h"
#include "zmf159_periph_map.h"
#include "../../usb_app/inc/usb_conf.h"
#ifndef NULL
#define NULL ((void *)0)
#endif
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* External variables --------------------------------------------------------*/


typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

#endif /* __USB_TYPE_H */

/******************* (C) COPYRIGHT 2018 MindMotion *****END OF FILE****/
