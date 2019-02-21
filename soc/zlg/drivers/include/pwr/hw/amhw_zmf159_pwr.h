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
 * \brief 电源管理接口
 *
 * \internal
 * \par History
 * - 1.00 17-04-17  nwt, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZMF159_PWR_H
#define __AMHW_ZMF159_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_zlg_pwr.h"

/**
 * \addtogroup amhw_zmf159_if_pwr
 * \copydoc amhw_zmf159_pwr.h
 * @{
 */


/**
  * \brief 系统控制寄存器块结构体
  */
typedef amhw_zlg_pwr_t amhw_zmf159_pwr_t;

typedef enum amhw_zmf159_pwr_vos {
    NORMAL_MODE       = 1,            /**< \brief 通用模式 */
    HEIGH_PROPERTY    = 3             /**< \brief 高性能模式 */
} amhw_zmf159_pwr_vos_t;

/**
 * \brief 过压选择使能
 *
 * \param[in] p_hw_pwr  ： 指向电源控制寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_pwr_odsw_enable (amhw_zmf159_pwr_t *p_hw_pwr)
{
    p_hw_pwr->cr |= (1 << 17);
}

/**
 * \brief 过压选择未使能
 *
 * \param[in] p_hw_pwr  ： 指向电源控制寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_pwr_odsw_disable (amhw_zmf159_pwr_t *p_hw_pwr)
{
    p_hw_pwr->cr &= ~(1 << 17);
}

/**
 * \brief 过压使能
 *
 * \param[in] p_hw_pwr  ： 指向电源控制寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_pwr_od_enable (amhw_zmf159_pwr_t *p_hw_pwr)
{
    p_hw_pwr->cr |= (1 << 16);
}

/**
 * \brief 过压未使能
 *
 * \param[in] p_hw_pwr  ： 指向电源控制寄存器块的指针
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_pwr_od_disable (amhw_zmf159_pwr_t *p_hw_pwr)
{
    p_hw_pwr->cr &= ~(1 << 16);
}

/**
 * \brief 调制器电压输出设置，仅在PLL未使能时配置，当PLL使能后，该位将被锁定
 *
 * \param[in] p_hw_pwr  ： 指向电源控制寄存器块的指针
 * \param[in] mode      ：设置模式
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_pwr_vos_set (amhw_zmf159_pwr_t     *p_hw_pwr,
                              amhw_zmf159_pwr_vos_t  mode)
{
    p_hw_pwr->cr |= ((mode & 0x3) << 14);
}

/**
 * \brief 过压模式选择准备
 *
 * \param[in] p_hw_pwr  ： 指向电源控制寄存器块的指针
 *
 * \return AM_TRUE  ：准备完成
 *         AM_FALSE ：没有准备完成
 */
am_static_inline
am_bool_t amhw_zmf159_pwr_odswrdy (amhw_zmf159_pwr_t *p_hw_pwr)
{
    return (am_bool_t)((p_hw_pwr->csr >> 17) & 0x1);
}

/**
 * \brief 过压模式准备
 *
 * \param[in] p_hw_pwr  ： 指向电源控制寄存器块的指针
 *
 * \return AM_TRUE  ：准备完成
 *         AM_FALSE ：没有准备完成
 */
am_static_inline
am_bool_t amhw_zmf159_pwr_odrdy (amhw_zmf159_pwr_t *p_hw_pwr)
{
    return (am_bool_t)((p_hw_pwr->csr >> 16) & 0x1);
}

/**
 * \brief 电压调制器输出选择准备
 *
 * \param[in] p_hw_pwr  ： 指向电源控制寄存器块的指针
 *
 * \return AM_TRUE  ：准备完成
 *         AM_FALSE ：没有准备完成
 */
am_static_inline
am_bool_t amhw_zmf159_pwr_vosrdy (amhw_zmf159_pwr_t *p_hw_pwr)
{
    return (am_bool_t)((p_hw_pwr->csr >> 14) & 0x1);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZMF159_PWR_H */

/* end of file */
