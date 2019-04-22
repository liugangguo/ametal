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
 * \brief LPC84X PMU 硬件操作接口描述
 * 
 * 1. 节能模式控制；
 * 2. 低功耗振荡器控制；
 * 3. 五个通用备份寄存器可在深度掉电模式下保存数据；
 * 4. 在温度范围(-40°~ 105°)，Vdd电压值范围(1.8V~3.35V)可以正常工作。
 * 注意：
 *     深度掉电模式在以下情况不能工作(勘误手册说明)：
 *         - 温度小于等于25度，Vdd电压值大于3.4V
 *         - 温度大于25度，Vdd电压值大于3.35V
 *
 * \internal
 * \par Modification History
 * - 1.01 15-12-01  sky, modified.
 * - 1.00 15-07-13  zxl, first implementation.
 * \endinternal
 */

#ifndef __AMHW_LPC84X_PMU_H
#define __AMHW_LPC84X_PMU_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

 /** 
 * \addtogroup amhw_lpc84x_if_pmu
 * \copydoc amhw_lpc84x_pmu.h
 * @{
 */

#include "hw/amhw_lpc82x_pmu.h"

/**
 * \brief 低功耗模式设置
 *
 * \param[in] p_hw_pmu : 指向PMU电源控制寄存器块的指针
 * \param[in] mode     : 需要配置的模式
 *
 * \return AM_ERROR    : 设置失败
 *         AM_OK       : 设置成功
 */
int amhw_lpc84x_lowpower_mode_set (amhw_lpc82x_pmu_t       *p_hw_pmu,
                                   amhw_lpc82x_pmu_pm_src_t mode);


/**
 * @} amhw_lpc82x_if_pmu
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_LPC84X_PMU_H */

/* end of file */
