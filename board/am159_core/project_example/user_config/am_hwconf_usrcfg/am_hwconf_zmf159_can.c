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
 * \brief ZMF159 CAN 用户配置文件
 * \sa am_hwconf_zmf159_can.c
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
#include "am_zmf159_can.h"
#include "am_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zmf159_adc
 * \copydoc am_hwconf_zmf159_adc.c
 * @{
 */

#define MAX     10

/** \brief ADC平台初始化 */
static void __zmf159_plfm_can_init (void)
{
    am_gpio_pin_cfg(PIOA_11, PIOA_11_CAN1_RX);
    am_gpio_pin_cfg(PIOA_12, PIOA_12_CAN1_TX);
    am_clk_enable(CLK_CAN);
}

/** \brief 解除ADC平台初始化 */
static void __zmf159_plfm_can_deinit (void)
{
    am_gpio_pin_cfg(PIOA_11, PIOA_11_CAN1_RX);
    am_gpio_pin_cfg(PIOA_12, PIOA_12_CAN1_TX);
    am_clk_disable (CLK_CAN);
}

static am_zmf159_can_intcb_info_t    __g_can_intcb_info[MAX];

/** \brief 设备信息 */
static const am_zmf159_can_devinfo_t __g_can_devinfo = {

    ZMF159_CAN_BASE,                 /**< \brief ADC */
    INUM_CAN_RX1,                    /**< \brief ADC的中断编号 */
    AMHW_ZMF159_CAN_BASIC_CAN,       /**< \brief ADC时钟号 */
    __g_can_intcb_info,              /**< \brief 参考电压 */
    MAX,                             /**< \brief 转换精度 */

    __zmf159_plfm_can_init,          /**< \brief ADC1的平台初始化 */
    __zmf159_plfm_can_deinit,        /**< \brief ADC1的平台去初始化 */

};

/**< \brief 设备实例 */
static am_zmf159_can_dev_t  __g_can_dev;

/** \brief ADC实例初始化，获得ADC标准服务句柄 */
am_can_handle_t am_zmf159_can_inst_init (void)
{
    return am_zmf159_can_init(&__g_can_dev, &__g_can_devinfo);
}

/** \brief ADC实例解初始化 */
void am_zmf159_can_inst_deinit (am_can_handle_t handle)
{
    am_zmf159_can_deinit(handle);
}

/**
 * @}
 */

/* end of file */
