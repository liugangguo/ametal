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
 * \brief ZMF159 ADC 用户配置文件
 * \sa am_hwconf_zmf159_adc.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-22  fra, first implementation
 * \endinternal
 */

#include "zmf159_periph_map.h"
#include "am_zmf159.h"
#include "zmf159_inum.h"
#include "am_gpio.h"
#include "am_zlg_adc.h"
#include "am_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zmf159_adc
 * \copydoc am_hwconf_zlg217_adc.c
 * @{
 */

/** \brief ADC平台初始化 */
static void __zlg_plfm_adc1_init (void)
{
    am_gpio_pin_cfg(PIOA_4, PIOA_4_AIN);
    am_clk_enable(CLK_ADC1);
}

/** \brief 解除ADC平台初始化 */
static void __zlg_plfm_adc1_deinit (void)
{
    am_gpio_pin_cfg(PIOA_4, PIOA_4_INPUT_FLOAT);
    am_clk_disable (CLK_ADC1);
}

/** \brief 设备信息 */
static const am_zlg_adc_devinfo_t __g_adc1_devinfo = {

    ZMF159_ADC1_BASE,                 /**< \brief ADC */
    INUM_ADC1_2,                      /**< \brief ADC的中断编号 */
    CLK_ADC1,                         /**< \brief ADC时钟号 */

    3300,                             /**< \brief 参考电压 */
    AMHW_ZLG_ADC_DATA_VALID_12BIT, /**< \brief 转换精度 */

    __zlg_plfm_adc1_init,             /**< \brief ADC1的平台初始化 */
    __zlg_plfm_adc1_deinit,           /**< \brief ADC1的平台去初始化 */

};

/**< \brief 设备实例 */
static am_zlg_adc_dev_t  __g_adc1_dev;

/** \brief ADC实例初始化，获得ADC标准服务句柄 */
am_adc_handle_t am_zlg217_adc1_inst_init (void)
{
    return am_zlg_adc_init(&__g_adc1_dev, &__g_adc1_devinfo);
}

/** \brief ADC实例解初始化 */
void am_zlg217_adc1_inst_deinit (am_adc_handle_t handle)
{
    am_zlg_adc_deinit(handle);
}

/**
 * @}
 */

/* end of file */
