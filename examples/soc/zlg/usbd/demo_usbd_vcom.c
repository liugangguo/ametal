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
 * \brief USB printer_counter 例程
 *
 * - 实验现象：
 * 1.将USB 电缆的 DN 接AM227_core 板 的引脚PA11, DP接core 板PA12， 将USB的另端点接入PC机。
 * 2.给板子烧录该例程，等待3秒(程序中有3秒延时，为了模拟USB拔出过程)，3秒后pc机会提示安装驱动，
 *   这里默认安装windows 通用打印机驱动，详细可看驱动安装说明文档，如果用户想要用自己的驱动，可以自行更新。
 * 3.在电脑桌面新建一个txt文件，输入字符串,之后点击文件打印，即在串口中可以看到文件内容.
 *
 * \par 源代码
 * \snippet demo_usbd_printer.c src_usbd_printer
 *
 * \internal
 * \par Modification History
 * - 1.00 19-1-09  adw, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_usbd_printer
 * \copydoc demo_usbd_printer.c
 */

/** [src_usbd_printer] */
#include "ametal.h"
#include "string.h"
#include "am_int.h"
#include "am_delay.h"
#include "am_rngbuf.h"
#include "am_vdebug.h"
#include "am_softimer.h"
#include "am_zmf159_usbd.h"
#include "am_zmf159_inst_init.h"
#include "am_zmf159_usbd.h"
#include "am_usbd_cdc_vcom.h"

extern am_usbd_cdc_vcom_handle am_zmf159_usbd_vcom_inst_init (void);

/**
 * \brief 例程入口
 */
void demo_zmf159_usbd_vcom_entry (void)
{
    am_kprintf("zmf159 vcom demo \r\n");

    am_usbd_cdc_vcom_handle handle = am_zmf159_usbd_vcom_inst_init();

    for (;;){
    	am_mdelay(1000);

    	am_usbd_cdc_vcom_send(handle, (uint8_t *)"1234", sizeof("1234"));
    }

}
/** [src_usbd_printer] */

/* end of file */
