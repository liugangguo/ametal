/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief usbd msc 例程，通过标准接口实现
 *
 * - 实验现象：
 *
 * \note
 *
 * \par 源代码
 * \snippet demo_usbd_msc.c src_usbd_msc
 *
 * \internal
 * \par Modification History
 * - 1.00 18-01-15  pea, first implementation
 * \endinternal
 */
/**
 * \brief 例程入口
 */
#include "ametal.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_zlg217_usbd.h"
#include "am_usbd_msc.h"
#include "am_zlg217_inst_init.h"

/**
 * \brief 例程入口
 */
void demo_zlg217_usbd_msc_entry (void)
{
    uint32_t  key = 0;

    am_usbd_msc_handle usbd_handle;

    AM_DBG_INFO("Start up successful!\r\n");
    /* 复位后延时一段时间，模拟USB设备拔出的动作 */
    am_mdelay(3000);

    usbd_handle = am_zlg217_usb_msc_inst_init();

    while (1) {

        /** 在相应的中断处理函数中 置位标志位，在主函数的while(1) 中轮询检查标志位，然后进行相应的处理
         *  不要在中断内直接处理批量输出/输入处理，因为批量输入/输出的数据量较大执行的时间较长，而且还是两个
         *  中断轮询执行，容易导致数据发不出去或中断执行时间较长导致程序运行出错
         */
        if (usbd_handle->int_status_out == AM_TRUE) {

            /* 先禁止中断，再执行批量输入/输出函数，接着失效标志位，最后打开中断 */
            key = am_int_cpu_lock();

            am_zlg217_usb_msc_enpoint2_bulk_out(usbd_handle);        // 数据处理

            usbd_handle->int_status_out = AM_FALSE;                  // 清空中断标志位

            am_int_cpu_unlock(key);
        }

        if (usbd_handle->int_status_in == AM_TRUE) {

            key = am_int_cpu_lock();
            am_zlg217_usb_msc_enpoint1_bulk_in(usbd_handle);

            usbd_handle->int_status_in = AM_FALSE;

            am_int_cpu_unlock(key);
        }
    }
}
/**
 * \addtogroup demo_if_usbd_msc
 * \copydoc demo_usbd_msc.c
 */


/** [src_usbd_msc] */

/* end of file */
