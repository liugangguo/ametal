/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief bootloader 例程，本demo是作为单区bootloader应用程序。
 *
 * - 操作步骤：
 *   参考AMmetal-AM845-Core-bootloader操作手册
 *
 *
 * \par 源代码
 * \snippet demo_am845_core_gcc_application.c src_demo_am845_core_gcc_application
 *
 * \internal
 * \par Modification History
 * - 1.00 19-03-25  yrh, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am845_core_gcc_application
 * \copydoc demo_am845_core_gcc_application.c
 */

#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
#include "am_softimer.h"
#include "am_lpc84x_inst_init.h"
#include <string.h>

void demo_am845_core_application_entry (void)
{
    am_kprintf("application : am845_core_bootloader_single_application start up successful!\r\n");

    while (1) {
        am_kprintf("application : am845_core_bootloader_single_application running!\r\n");
        am_led_toggle(0);
        am_mdelay(500);
    }
}
/* end of file */
