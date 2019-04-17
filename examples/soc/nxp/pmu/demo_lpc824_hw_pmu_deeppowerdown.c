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
 * \brief PMU 深度掉电模式例程，通过 HW 层接口实现
 *
 * - 实验现象：
 *   1. 运行程序，一秒后 LED0 闪烁一次后进入深度掉电模式；
 *   2. 等待 5s 后，WKT 计时时间到，CPU 被唤醒，如果通用寄存器数据校验正确，LED0
 *      闪烁一次；如果通用寄存器数据校验错误，LED0 持续闪烁。
 *
 * \note
 *    1. LED0 需要短接 J9 跳线帽，才能被 PIO0_20 控制；
 *    2. 进入深度掉电模式后，只有 WAKEUP 引脚和 WKT 定时器能唤醒芯片。对于默认状态，
 *       WAKEUP 引脚唤醒使能，所以一定确保 WAKEUP 外部上拉到电源，保证有效的高电平
 *       状态，否则会引起误唤醒操作，而观察不到 WKT 唤醒 CPU；而本例程将 WAKEUP 引脚
 *       (PIO0_4)唤醒功能禁止了，所以不需要将 PIO0_4 上拉；
 *    3. 该demo使用标准层初始化wkt定时器，需要在 am_hwconf_lpc82x_wkt.c中将wkt时钟源选择为
 *       低功耗时钟 AMHW_LPC_WKT_LOW_POWER_CLOCK；
 *    4. 使用该程序后，会导致下次程序烧写的时候检测不到芯片（由于芯片进入深度掉电
 *       模式将 SWD 调试模式关闭），下次下载时将 P0_12 拉低或按动复位键之后一秒内
 *       即可正常下载调试。
 *
 * \par 源代码
 * \snippet demo_lpc824_hw_pmu_deeppowerdown.c src_lpc824_hw_pmu_deeppowerdown
 *
 * \internal
 * \par Modification history
 * - 1.02 19-04-17  ipk, modified
 * - 1.01 15-12-01  sky, modified
 * - 1.00 15-07-14  zxl, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_lpc824_hw_pmu_deeppowerdown
 * \copydoc demo_lpc824_hw_pmu_deeppowerdown.c
 */

/** [src_lpc824_hw_pmu_deeppowerdown] */
#include "ametal.h"
#include "am_int.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "hw/amhw_lpc82x_pmu.h"
#include "hw/amhw_lpc_wkt.h"
#include "hw/amhw_lpc82x_clk.h"
#include "hw/amhw_lpc82x_syscon.h"

/*******************************************************************************
  本地全局变量定义
*******************************************************************************/

/** \brief 中断标志变量 */
am_local volatile uint8_t __g_deeppowerdown_wkt_flag = 0;

/*******************************************************************************
  本地函数定义
*******************************************************************************/

/**
 * \brief WKT 中断服务函数
 */
am_local void __deeppowerdown_wkt_isr (void *p_arg)
{
    if (amhw_lpc_wkt_alarmflag_get(LPC82X_WKT)) {
        amhw_lpc_wkt_alarmflag_clear(LPC82X_WKT);      /* 清除中断标志 */
        __g_deeppowerdown_wkt_flag = 1;                /* 改变中断标志变量 */
    }
}

/**
 * \brief PMU 深度掉电模式初始化
 */
void demo_lpc824_hw_pmu_deeppowerdown_entry (amhw_lpc82x_pmu_t *p_hw_pmu,
                                             am_timer_handle_t  wkt_handle)
{
  
    /* 延时一秒，方便下次下载程序 */
    am_mdelay(1000);

    /* LED0 闪烁一次 */
    am_led_on(LED0);
    am_mdelay(500);
    am_led_off(LED0);

    /* 已经从深度掉电中唤醒 */
    if (amhw_lpc82x_pmu_dpdflag_get(p_hw_pmu) != 0x0) {

        /* 清除深度掉电模式标志位 */
        amhw_lpc82x_pmu_dpdflag_clear(p_hw_pmu);

        if ((amhw_lpc82x_pmu_gpdata_get(p_hw_pmu, GP_REG_0) != 0x12345678) ||
            (amhw_lpc82x_pmu_gpdata_get(p_hw_pmu, GP_REG_1) != 0x87654321) ||
            (amhw_lpc82x_pmu_gpdata_get(p_hw_pmu, GP_REG_2) != 0x56781234) ||
            (amhw_lpc82x_pmu_gpdata_get(p_hw_pmu, GP_REG_3) != 0x43218765)) {

            /* 从深度掉电唤醒后，通用寄存器数据检查失败，LED0 持续闪烁 */
            AM_FOREVER {

                /* LED0 以 0.5s 的间隔一直闪烁 */
                am_led_toggle(LED0);
                am_mdelay(500);
            }
        }
    } else {

        /* 未进入深度掉电模式，设置通用寄存器数据，用于测试 */
        amhw_lpc82x_pmu_gpdata_save(p_hw_pmu, GP_REG_0, 0x12345678);
        amhw_lpc82x_pmu_gpdata_save(p_hw_pmu, GP_REG_1, 0x87654321);
        amhw_lpc82x_pmu_gpdata_save(p_hw_pmu, GP_REG_2, 0x56781234);
        amhw_lpc82x_pmu_gpdata_save(p_hw_pmu, GP_REG_3, 0x43218765);

        /* 禁用引脚 PIO0_4 上的唤醒功能 */
        amhw_lpc82x_pmu_lposcen_disable(p_hw_pmu);

        /* 配置深度掉电模式 */
        amhw_lpc82x_lowpower_mode_set(p_hw_pmu, AMHW_LPC82X_PMU_PCON_MODE_DEEPPD);

        /* WKT 连接中断回调 */
        am_timer_callback_set(wkt_handle, 0, __deeppowerdown_wkt_isr, NULL);

        /* 设置 WKT 定时时间 5s */
        am_timer_enable_us(wkt_handle, 0, 5000000);

        /* 进入深度掉电模式 */
        __WFI();
    }
    
    /* 从深度掉电模式唤醒后，通用寄存器数据检查正确，LED0 闪烁一次 */
    am_led_on(LED0);
    am_mdelay(500);
    am_led_off(LED0);

    AM_FOREVER {
        ; /* VOID */
    }
}
/** [src_lpc824_hw_pmu_deeppowerdown] */

/* end of file */
