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
 * \brief I2C 从机例程(此例程可以用来模拟 EEPROM)，通过 HW 层接口实现
 *
 * - 操作步骤：
 *   1. PIOC_8 引脚连接 I2C 主机的 SCL 引脚；
 *   2. PIOC_9 引脚连接 I2C 主机的 SDA 引脚。
 *
 * \note
 *    当前 I2C 的 SCL 引脚使用的是 PIOC_8，SDA 引脚使用的是 PIOC_9，
 *    可根据实际情况更换引脚。
 *
 * \par 源代码
 * \snippet demo_zmf159_hw_i2c_slave_poll.c src_zmf159_hw_i2c_slave_poll
 *
 * \internal
 * \par Modification history
 * - 1.00 17-04-27  sdy, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_zmf159_hw_i2c_slave_poll
 * \copydoc demo_zmf159_hw_i2c_slave_poll.c
 */

/** [src_zmf159_hw_i2c_slave_poll] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_gpio.h"
#include "am_zmf159.h"
#include "am_zmf159_clk.h"
#include "amhw_zlg_i2c.h"
#include "amhw_zmf159_rcc.h"
#include "demo_zlg_entries.h"
#include "demo_zmf159_core_entries.h"

/**
 * \brief 例程入口
 */
void demo_zmf159_core_hw_i2c_slave_poll_entry (void)
{
    am_kprintf("demo zmf159_core hw i2c slave poll!\r\n");

    /**
     * PIOC_8 ~ I2C2_SCL, PIOC_9 ~ I2C2_SDA
     */
    am_gpio_pin_cfg(PIOC_8, PIOC_8_I2C2_SCL | PIOC_8_AF_OD | PIOC_8_SPEED_20MHz);
    am_gpio_pin_cfg(PIOC_9, PIOC_9_I2C2_SDA | PIOC_9_AF_OD | PIOC_9_SPEED_20MHz);

    am_clk_enable(CLK_I2C2);
    am_zmf159_clk_reset(CLK_I2C2);

    demo_zlg_hw_i2c_slave_poll_entry(ZMF159_I2C2);
}
/** [src_zmf159_hw_i2c_slave_poll] */

/* end of file */
