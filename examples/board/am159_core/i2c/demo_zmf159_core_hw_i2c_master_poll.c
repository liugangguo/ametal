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
 * \brief I2C 轮询模式下操作 EEPROM 例程，通过 HW 层接口实现
 *
 * - 操作步骤：
 *   1. PIOC_8 引脚连接 EEPROM 的 SCL 引脚；
 *   2. PIOC_9 引脚连接 EEPROM 的 SDA 引脚。
 *
 * - 实验现象：
 *   1. 向 EEPROM 设备写入 8字节（小于或等于一页）数据；
 *   2. 读取 EEPROM 中的数据通过串口打印出来；
 *   3. 若写入数据和读取的数据一致，校验通过，LED0 以 200ms 间隔闪烁。
 *
 * \note
 *    1. LED0 需要短接 J9 跳线帽，才能被 PIOC_9 控制；
 *    2. 如需观察串口打印的调试信息，需要将 PIOA_10 引脚连接 PC 串口的 TXD，
 *       PIOA_9 引脚连接 PC 串口的 RXD；
 *    3. 当前 I2C 的 SCL 引脚使用的是 PIOB_6，SDA 引脚使用的是 PIOB_7，
 *       可根据实际情况更换引脚。
 *
 * \par 源代码
 * \snippet demo_zmf159_hw_i2c_master_poll.c src_zmf159_hw_i2c_master_poll
 *
 * \internal
 * \par History
 * - 1.00 17-09-5  fra, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zmf159_hw_i2c_master_poll
 * \copydoc demo_zmf159_hw_i2c_master_poll.c
 */

/** [src_zmf159_hw_i2c_master_poll] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_zmf159.h"
#include "am_zmf159_clk.h"
#include "amhw_zmf159_rcc.h"
#include "demo_zlg_entries.h"
#include "demo_zmf159_core_entries.h"

#define I2C_MASTER    (amhw_zlg_i2c_t *)ZMF159_I2C2_BASE   /**< \brief I2C主机控制器通道号定义 */

/**
 * \brief 例程入口
 */
void demo_zmf159_core_hw_i2c_master_poll_entry (void)
{

    am_kprintf("demo zmf159_core hw i2c master poll!\r\n");

    /**
     * PIOC_8 ~ I2C2_SCL, PIOC_9 ~ I2C2_SDA
     */
    am_gpio_pin_cfg(PIOC_8, PIOC_8_I2C2_SCL | PIOC_8_AF_OD | PIOC_8_SPEED_20MHz);
    am_gpio_pin_cfg(PIOC_9, PIOC_9_I2C2_SDA | PIOC_9_AF_OD | PIOC_9_SPEED_20MHz);

    am_clk_enable(CLK_I2C2);
    am_zmf159_clk_reset(CLK_I2C2);

    demo_zlg_hw_i2c_master_poll_entry(I2C_MASTER, am_clk_rate_get(CLK_APB1));

}
/** [src_zmf159_hw_i2c_master_poll] */

/* end of file */
