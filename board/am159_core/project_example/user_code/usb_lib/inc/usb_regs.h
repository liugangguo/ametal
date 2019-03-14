
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_REGS_H
#define __USB_REGS_H

#include "ametal.h"
#include "am_types.h"
#include "usb_type.h"

/* endpoints enumeration */
#define ENDP0   ((uint8_t)0)
#define ENDP1   ((uint8_t)1)
#define ENDP2   ((uint8_t)2)
#define ENDP3   ((uint8_t)3)
#define ENDP4   ((uint8_t)4)

/**
* @}
*/
#define OTG_FS_INT_STAT_RST         ((uint32_t)0x01)
#define OTG_FS_INT_STAT_ERROR       ((uint32_t)0x02)
#define OTG_FS_INT_STAT_SOF         ((uint32_t)0x04)
#define OTG_FS_INT_STAT_DNE         ((uint32_t)0x08)
#define OTG_FS_INT_STAT_SLEEP       ((uint32_t)0x10)
#define OTG_FS_INT_STAT_RESUME      ((uint32_t)0x20)
#define OTG_FS_INT_STAT_ATTACH      ((uint32_t)0x40)
#define OTG_FS_INT_STAT_STALL       ((uint32_t)0x80)

#define  USB_INT_STAT_RST       0x01
#define  USB_INT_STAT_ERROR     0x02
#define  USB_INT_STAT_SOF_TOK   0x04
#define  USB_INT_STAT_TOK_DNE   0x08
#define  USB_INT_STAT_SLEEP     0x10
#define  USB_INT_STAT_RESUME    0x20
#define  USB_INT_STAT_ATTACH    0x40
#define  USB_INT_STAT_STALL     0x80


/**
* @}
*/


#endif /* __USB_REGS_H */

/******************* (C) COPYRIGHT 2018 MindMotion *****END OF FILE****/
