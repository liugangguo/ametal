/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief 低功耗模式硬件层接口
 * 
 * \internal
 * \par Modification History
 * - 1.00 19-04-16  ipk, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "hw/amhw_lpc82x_pmu.h"
#include "hw/amhw_lpc82x_syscon.h"

/**
 * \brief 系统控制寄存器设定
 *
 * \param[in] flags 系统控制寄存器宏 (#AMHW_LPC82X_SCR_ISRBACK_NTO_SLP)
 *
 * \return 无
 */
am_local void __scb_scr_set (uint32_t flags)
{
    SCB->SCR = flags;
}

/**
 * \brief 低功耗模式设置
 */
int amhw_lpc82x_lowpower_mode_set (amhw_lpc82x_pmu_t       *p_hw_pmu,
                                   amhw_lpc82x_pmu_pm_src_t mode)
{
    uint32_t flag;

    switch (mode) {
        case AMHW_LPC82X_PMU_PCON_MODE_NORMAL:
             flag = AMHW_LPC82X_SCR_ISRBACK_NTO_SLP| /* 中断返回时不进入睡眠模式 */
                    AMHW_LPC82X_SCR_LOWPWR_MODE_SLP| /* 睡眠模式作为低功耗模式 */
                    AMHW_LPC82X_SCR_WKUP_BY_ENAISR;  /* 只有使能的中断才能唤醒 */
            break;
        case AMHW_LPC82X_PMU_PCON_MODE_DEEPSLP:
        case AMHW_LPC82X_PMU_PCON_MODE_PD:
            flag = AMHW_LPC82X_SCR_ISRBACK_NTO_SLP   | /* 中断返回时不进入睡眠模式 */
                   AMHW_LPC82X_SCR_LOWPWR_MODE_DPSLP | /* 深度睡眠模式作为低功耗模式 */
                   AMHW_LPC82X_SCR_WKUP_BY_ENAISR;     /* 只有使能的中断才能唤醒 */
            break;
        case AMHW_LPC82X_PMU_PCON_MODE_DEEPPD:
             flag = AMHW_LPC82X_SCR_LOWPWR_MODE_DPSLP;
             break;
        default:
            return AM_ERROR;
    }

    if (mode == AMHW_LPC82X_PMU_PCON_MODE_DEEPPD) {

        /* 使能低功耗振荡器 */
        amhw_lpc82x_pmu_lposcen_enable(p_hw_pmu);

        /* 深度掉电模式下使能低功耗振荡器 */
        amhw_lpc82x_pmu_lposcdpden_enable(p_hw_pmu);
    } else {

        /* 配置唤醒寄存器 */
        amhw_lpc82x_syscon_deepwakeup_cfg(amhw_lpc82x_syscon_powerstat_get());

        /* BOD上电，看门狗振荡器电源上电 */
        amhw_lpc82x_syscon_deepsleep_enable(AMHW_LPC82X_SYSCON_PD_BOD |
                                            AMHW_LPC82X_SYSCON_PD_WDT_OSC);
    }

    /* ARM Cortex-M0+ 内核的低功耗模式 */
    __scb_scr_set(flag);

    amhw_lpc82x_pmu_pm_cfg(p_hw_pmu, mode);

    return AM_OK;
}

/* end of file */
