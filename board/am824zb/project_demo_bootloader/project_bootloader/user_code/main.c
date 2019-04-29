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
 * \brief AM824ZB bootloader 工程 
 *
 *  使用方式可参考ametal/documents/am24zb/目录下的ametal_am824zb_bootloader操作手册
 *
 * \internal
 * \par Modification history
 * - 1.00 19-03-25  yrh, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_delay.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_led.h"
#include "demo_am824zb_entries.h"
#include "am_gpio.h"
#include "am_lpc82x.h"

extern void demo_am824zb_bootloader_entry (void);

/**
 * \brief AMetal 应用程序入口
 */
void am_main (void)
{
    /* 关闭看门狗 */
    am_gpio_pin_cfg(PIO0_22, AM_GPIO_FLOAT);

    demo_am824zb_bootloader_entry();

    while(1) {
        ;
    }
}

/* end of file */
