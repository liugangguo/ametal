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
 * \brief PMU 睡眠模式例程，通过 HW 层接口实现
 *
 * - 实验步骤：
 *   1. 用杜邦线将 PIO0_23 与 GND 连接，把电平拉低。
*
 * - 实验现象：
 *   1. 运行程序，一秒后 LED0 闪烁一次后进入睡眠模式；
 *   2. 当 PIO0_23 与 GND 的连接断开时，CPU 被唤醒，LED0 不断闪烁。
 *
 * \note
 *    1. LED0 需要短接 J9 跳线帽，才能被 PIO0_20 控制；
 *    2. 由于 MRT 默认作为系统滴答使用，使用测试本 Demo 前需要将 am_prj_config.h 中
 *       的 AM_CFG_SOFTIMER_ENABLE、 AM_CFG_SYSTEM_TICK_ENABLE 以及
 *       AM_CFG_KEY_GPIO_ENABLE 定义为 0，不使用软件定时器、系统嘀嗒、板载独立按键，
 *       防止进入睡眠模式后被 MRT 定时器中断唤醒；
 *    2. 使用该程序后，会导致下次程序烧写的时候检测不到芯片（由于芯片进入睡眠
 *       模式将 SWD 调试模式关闭），下次下载时将 P0_12 拉低或按动复位键之后一秒内
 *       即可正常下载调试。
 *
 * \par 源代码
 * \snippet demo_lpc824_hw_pmu_sleep.c src_lpc824_hw_pmu_sleep
 *
 * \internal
 * \par Modification history
 * - 1.02 19-04-17  ipk, modified
 * - 1.01 15-12-01  sky, modified
 * - 1.00 15-07-21  zxl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_pmu_sleep
 * \copydoc demo_lpc824_hw_pmu_sleep.c
 */

/** [src_lpc824_hw_pmu_sleep] */
#include "ametal.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc82x_pmu.h"
#include "hw/amhw_lpc82x_iocon.h"
#include "hw/amhw_lpc82x_pint.h"
#include "hw/amhw_lpc82x_syscon.h"
#include "am_lpc82x.h"

/*******************************************************************************
  本地全局变量定义
*******************************************************************************/
volatile uint8_t __g_sleep_wkt_flag = 0; /**< \brief 中断标志变量 */

/**
 * \brief 引脚中断服务函数
 */
am_local void __sleep_pint_isr (void *p_arg)
{

    /* 清除中断标志 */
    amhw_lpc82x_pint_edge_dec_clr(LPC82X_PINT, AMHW_LPC82X_PINT_CHAN_0);

    /* 改变中断标志变量 */
    __g_sleep_wkt_flag = 1;
}

/**
 * \brief PMU 睡眠模式 初始化
 */
void demo_lpc824_hw_pmu_sleep_entry (amhw_lpc82x_pmu_t  *p_hw_pmu,
                                     int                 pin)
{

    /* LED0 闪烁一次 */
    am_led_on(LED0);
    am_mdelay(500);
    am_led_off(LED0);
  
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
    am_int_connect(INUM_PIN_INT0, __sleep_pint_isr, (void *)0);

    /* 使能引脚中断 */
    am_int_enable(INUM_PIN_INT0);
  
    /* 配置为睡眠模式 */
    amhw_lpc82x_lowpower_mode_set(p_hw_pmu, AMHW_LPC82X_PMU_PCON_MODE_NORMAL);

    /* 进入睡眠模式 */
    __WFI();

    AM_FOREVER {

        /* 从睡眠模式唤醒后，LED0 不断闪烁 */
        am_led_toggle(LED0);
        am_mdelay(500);
    }
}
/** [src_lpc824_hw_pmu_sleep] */

/* end of file */
