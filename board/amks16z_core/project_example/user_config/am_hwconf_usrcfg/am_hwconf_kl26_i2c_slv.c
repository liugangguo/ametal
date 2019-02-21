/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.fsl.cn/
*******************************************************************************/

/**
 * \file
 * \brief ZLG116 I2C从机 用户配置文件
 * \sa am_hwconf_fsl116_i2c_slv.c
 *
 * \internal
 * \par Modification history
 * - 1.00 19-01-22  bzq, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "hw/amhw_kl26_sim.h"
#include "hw/amhw_kl26_pinctrl.h"
#include "am_fsl_i2c_slv.h"
#include "am_fsl_i2c.h"
#include "am_gpio.h"

#include "../../../../../soc/freescale/kl26/kl26_clk.h"
#include "../../../../../soc/freescale/kl26/kl26_periph_map.h"
#include "../../../../../soc/freescale/kl26/kl26_pin.h"
/**
 * \addtogroup am_if_src_hwconf_fsl116_i2c_slv
 * \copydoc am_hwconf_fsl116_i2c_slv.c
 * @{
 */

/** \brief I2C0 平台初始化函数 */
static void __fsl_i2c0_plfm_init (void)
{

//    am_gpio_pin_cfg(PIOB_3, PIOB_3_I2C0_SDA);
//    am_gpio_pin_cfg(PIOB_2, PIOB_2_I2C0_SCL);
    am_gpio_pin_cfg(PIOE_25, PIOE_25_I2C0_SDA );
    am_gpio_pin_cfg(PIOE_24, PIOE_24_I2C0_SCL );

    amhw_kl26_sim_periph_clock_enable(KL26_SIM_SCGC_I2C0);
}

/** \brief 解除I2C0 平台初始化函数 */
static void __fsl_i2c0_plfm_deinit (void)
{
    amhw_kl26_sim_periph_clock_disable(KL26_SIM_SCGC_I2C0);
}

/**
 * \name I2C0 控制器参数定义
 * @{
 */

/** @} */

/**
 * \brief I2C0从 设备信息
 */
static const am_fsl_i2c_slv_devinfo_t __g_i2c0_devinfo = {
	KL26_I2C0,                /**< \brief I2C0寄存器块基址 */
    INUM_I2C0,                /**< \brief I2C0 中断编号 */
	CLK_I2C0,                 /**< \brief I2C0   时钟号 */
	10000,                     /**< \brief I2C0  保持时间 */
	__fsl_i2c0_plfm_init,     /**< \brief 平台初始化 */
	__fsl_i2c0_plfm_deinit    /**< \brief 平台去初始化 */
};

static am_fsl_i2c_slv_dev_t __g_i2c0_dev; /**< \brief I2C0 设备实例 */


/** \brief I2C1 实例初始化，获得I2C标准服务句柄 */
am_i2c_slv_handle_t  am_fsl16_i2c0_slv_inst_init (void)
{
    return am_fsl_i2c_slv_init(&__g_i2c0_dev, &__g_i2c0_devinfo);
}

/** \brief I2C1 实例解初始化 */
void am_fsl16_i2c0_slv_inst_deinit (am_i2c_slv_handle_t handle)
{
    am_fsl_i2c_slv_deinit(handle);
}

/** @} */

/* end of file */
