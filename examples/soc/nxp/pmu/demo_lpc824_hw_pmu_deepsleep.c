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
 * \brief PMU 深度睡眠模式例程，通过 HW 层接口实现
 *
 * - 实验步骤：
 *   1. 用杜邦线将 PIO0_23 与 GND 连接，把电平拉低。
 *
 * - 实验现象：
 *   1. 运行程序，一秒后 LED0 闪烁一次后进入深度睡眠模式；
 *   2. 当 PIO0_23 与 GND 的连接断开时，CPU 被唤醒，LED0 不断闪烁。
 *
 * \note
 *    1. LED0 需要短接 J9 跳线帽，才能被 PIO0_20 控制；
 *    2. 使用该程序后，会导致下次程序烧写的时候检测不到芯片（由于芯片进入深度睡眠
 *       模式将 SWD 调试模式关闭），下次下载时将 P0_12 拉低或按动复位键之后一秒内
 *       即可正常下载调试。
 *
 * \par 源代码
 * \snippet demo_lpc824_hw_pmu_deepsleep.c src_lpc824_hw_pmu_deepsleep
 *
 * \internal
 * \par Modification history
 * - 1.02 19-04-17  ipk, modified
 * - 1.01 15-12-01  sky, modified
 * - 1.00 15-07-20  zxl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_pmu_deepsleep
 * \copydoc demo_lpc824_hw_pmu_deepsleep.c
 */

/** [src_lpc824_hw_pmu_deepsleep] */
#include "ametal.h"
#include "am_int.h"
#include "am_board.h"
#include "hw/amhw_lpc82x_pmu.h"
#include "hw/amhw_lpc82x_iocon.h"
#include "hw/amhw_lpc82x_pint.h"
#include "hw/amhw_lpc82x_syscon.h"

/*******************************************************************************
  本地全局变量定义
*******************************************************************************/

am_local volatile uint8_t __g_deepsleep_wkt_flag = 0; /**< \brief 中断标志变量 */

/**
 * \brief 引脚中断服务函数
 */
am_local void __deepsleep_pint_isr (void *p_arg)
{

    /* 清除中断标志 */
    amhw_lpc82x_pint_edge_dec_clr(LPC82X_PINT, AMHW_LPC82X_PINT_CHAN_0);

    /* 改变中断标志变量 */
    __g_deepsleep_wkt_flag = 1;
}

/**
 * \brief PMU 深度睡眠模式 初始化
 */
void demo_lpc824_hw_pmu_deepsleep_entry (amhw_lpc82x_pmu_t  *p_hw_pmu,
                                         int                 pin)
{

    /* 打开看门狗振荡器电源 */
    amhw_lpc82x_syscon_powerup(AMHW_LPC82X_SYSCON_PD_WDT_OSC);

    /* PIO0_23 中断使用中断通道 0 */
    amhw_lpc82x_syscon_pint_sel(AMHW_LPC82X_PINT_CHAN_0, pin);

    /* 配置为双边沿触发 */
    amhw_lpc82x_pint_trigger_set(LPC82X_PINT,
                                 AMHW_LPC82X_PINT_CHAN_0,
                                 AMHW_LPC82X_PINT_TRIGGER_BOTH_EDGES);

    /* PIN0 作为唤醒源 */
    amhw_lpc82x_syscon_wakeup_enable(AMHW_LPC82X_SYSCON_STARTER_PINT0);

    /* 连接中断服务函数 */
    am_int_connect(INUM_PIN_INT0, __deepsleep_pint_isr, (void *)0);

    /* 使能引脚中断 */
    am_int_enable(INUM_PIN_INT0);
  
    /* 配置为深度睡眠模式*/
    amhw_lpc82x_lowpower_mode_set(p_hw_pmu, AMHW_LPC82X_PMU_PCON_MODE_DEEPSLP);

    /* 进入深度睡眠模式 */
    __WFI();

    AM_FOREVER {

        /* 从深度睡眠模式唤醒后，LED0 不断闪烁 */
        am_led_toggle(LED0);
        am_mdelay(500);
    }
}
/** [src_lpc824_hw_pmu_deepsleep] */

/* end of file */
