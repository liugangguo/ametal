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
 * \brief ZMF159 TIM 定时功能用户配置文件
 * \sa am_hwconf_zmf159_tim_timing.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 17-04-21  nwt, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_clk.h"
#include "am_zmf159.h"
#include "am_zmf159_clk.h"
#include "am_zlg_tim_timing.h"

/**
 * \addtogroup am_if_src_hwconf_zmf159_tim_timing
 * \copydoc am_hwconf_zmf159_tim_timing.c
 * @{
 */

/*******************************************************************************
 * TIM1 配置
 ******************************************************************************/

/** \brief TIM1 平台初始化 */
void __zlg_plfm_tim1_timing_init (void)
{

    /* 使能高级定时器1时钟 */
    am_clk_enable(CLK_TIM1);

    /* 复位高级定时器1 */
    am_zmf159_clk_reset(CLK_TIM1);
}

/** \brief 解除 TIM1 平台初始化 */
void __zlg_plfm_tim1_timing_deinit (void)
{

    /* 复位高级定时器1 */
    am_zmf159_clk_reset(CLK_TIM1);

    /* 禁能高级定时器1时钟 */
    am_clk_disable(CLK_TIM1);
}


/** \brief TIM1 设备信息 */
const am_zlg_tim_timing_devinfo_t  __g_tim1_timing_devinfo = {
    ZMF159_TIM1_BASE,                /**< \brief TIM1寄存器块的基地址 */
    INUM_TIM1_UP,                    /**< \brief TIM1中断编号 */
    CLK_TIM1,                        /**< \brief TIM1时钟ID */
    AMHW_ZLG_TIM_TYPE0,              /**< \brief 定时器类型 */
    __zlg_plfm_tim1_timing_init,     /**< \brief 平台初始化函数 */
    __zlg_plfm_tim1_timing_deinit    /**< \brief 平台解析初始化函数 */
};

/** \brief TIM1 设备定义 */
am_zlg_tim_timing_dev_t  __g_tim1_timing_dev;

/** \brief 定时器TIM1 Timing实例初始化，获得Timer标准服务句柄 */
am_timer_handle_t am_zmf159_tim1_timing_inst_init (void)
{
    return am_zlg_tim_timing_init(&__g_tim1_timing_dev,
                                  &__g_tim1_timing_devinfo);
}

/** \brief TIM1 Timing实例解初始化 */
void am_zmf159_tim1_timing_inst_deinit (am_timer_handle_t handle)
{
    am_zlg_tim_timing_deinit(handle);
}

/*******************************************************************************
 * TIM2 配置
 ******************************************************************************/

/** \brief TIM2 平台初始化 */
void __zlg_plfm_tim2_timing_init (void)
{

    /* 使能通用定时器2时钟 */
    am_clk_enable(CLK_TIM2);

    /* 复位通用定时器2 */
    am_zmf159_clk_reset(CLK_TIM2);
}

/** \brief 解除 TIM2 平台初始化 */
void __zlg_plfm_tim2_timing_deinit (void)
{

    /* 复位通用定时器2 */
    am_zmf159_clk_reset(CLK_TIM2);

    /* 禁能通用定时器2时钟 */
    am_clk_disable(CLK_TIM2);
}

/** \brief TIM2 设备信息 */
const am_zlg_tim_timing_devinfo_t  __g_tim2_timing_devinfo = {
    ZMF159_TIM2_BASE,                /**< \brief TIM2寄存器块的基地址 */
    INUM_TIM2,                       /**< \brief TIM2中断编号 */
    CLK_TIM2,                        /**< \brief TIM2时钟ID */
    AMHW_ZLG_TIM_TYPE1,              /**< \brief 定时器类型 */
    __zlg_plfm_tim2_timing_init,     /**< \brief 平台初始化函数 */
    __zlg_plfm_tim2_timing_deinit    /**< \brief 平台解析初始化函数 */
};

/** \brief TIM2 设备定义 */
am_zlg_tim_timing_dev_t  __g_tim2_timing_dev;

/** \brief TIM2 Timing实例初始化，获得Timer标准服务句柄 */
am_timer_handle_t am_zmf159_tim2_timing_inst_init (void)
{
    return am_zlg_tim_timing_init(&__g_tim2_timing_dev,
                                  &__g_tim2_timing_devinfo);
}

/** \brief TIM2 Timing实例解初始化 */
void am_zmf159_tim2_timing_inst_deinit (am_timer_handle_t handle)
{
    am_zlg_tim_timing_deinit(handle);
}


/*******************************************************************************
 * TIM3配置
 ******************************************************************************/
/** \brief TIM3平台初始化 */
void __zlg_plfm_tim3_timing_init (void)
{

    /* 使能通用定时器3时钟 */
    am_clk_enable(CLK_TIM3);

    /* 复位通用定时器3 */
    am_zmf159_clk_reset(CLK_TIM3);
}

/** \brief 解除TIM3平台初始化 */
void __zlg_plfm_tim3_timing_deinit (void)
{

    /* 复位通用定时器3 */
    am_zmf159_clk_reset(CLK_TIM3);

    /* 禁能通用定时器3时钟 */
    am_clk_disable(CLK_TIM3);
}

/** \brief TIM3 设备信息 */
const am_zlg_tim_timing_devinfo_t  __g_tim3_timing_devinfo = {
    ZMF159_TIM3_BASE,                /**< \brief TIM3寄存器块的基地址 */
    INUM_TIM3,                       /**< \brief TIM3中断编号 */
    CLK_TIM3,                        /**< \brief TIM3时钟ID */
    AMHW_ZLG_TIM_TYPE1,              /**< \brief 定时器类型 */
    __zlg_plfm_tim3_timing_init,     /**< \brief 平台初始化函数 */
    __zlg_plfm_tim3_timing_deinit    /**< \brief 平台解初始化函数 */
};

/** \brief TIM3设备定义 */
am_zlg_tim_timing_dev_t  __g_tim3_timing_dev;

/** \brief TIM3 Timing实例初始化，获得Timer标准服务句柄 */
am_timer_handle_t am_zmf159_tim3_timing_inst_init (void)
{
    return am_zlg_tim_timing_init(&__g_tim3_timing_dev,
                                  &__g_tim3_timing_devinfo);
}

/** \brief TIM3 Timing实例解初始化 */
void am_zmf159_tim3_timing_inst_deinit (am_timer_handle_t handle)
{
    am_zlg_tim_timing_deinit(handle);
}

/*******************************************************************************
 * TIM4配置
 ******************************************************************************/
/** \brief TIM4平台初始化 */
void __zlg_plfm_tim4_timing_init (void)
{

    /* 使能通用定时器4时钟 */
    am_clk_enable(CLK_TIM4);

    /* 复位通用定时器4 */
    am_zmf159_clk_reset(CLK_TIM4);
}

/** \brief 解除TIM4平台初始化 */
void __zlg_plfm_tim4_timing_deinit (void)
{

    /* 复位通用定时器4 */
    am_zmf159_clk_reset(CLK_TIM4);

    /* 禁能通用定时器4时钟 */
    am_clk_disable(CLK_TIM4);
}

/** \brief TIM4设备信息 */
const am_zlg_tim_timing_devinfo_t  __g_tim4_timing_devinfo = {
    ZMF159_TIM4_BASE,                 /**< \brief TIM4寄存器块的基地址 */
    INUM_TIM4,                        /**< \brief TIM4中断编号 */
    CLK_TIM4,                         /**< \brief TIM4时钟ID */
    AMHW_ZLG_TIM_TYPE1,               /**< \brief 定时器类型 */
    __zlg_plfm_tim4_timing_init,     /**< \brief 平台初始化函数 */
    __zlg_plfm_tim4_timing_deinit    /**< \brief 平台解初始化函数 */
};

/** \brief TIM4设备定义 */
am_zlg_tim_timing_dev_t  __g_tim4_timing_dev;

/** \brief TIM4 Timing实例初始化，获得Timer标准服务句柄 */
am_timer_handle_t am_zmf159_tim4_timing_inst_init (void)
{
    return am_zlg_tim_timing_init(&__g_tim4_timing_dev,
                                  &__g_tim4_timing_devinfo);
}

/** \brief TIM4 Timing实例解初始化 */
void am_zmf159_tim4_timing_inst_deinit (am_timer_handle_t handle)
{
    am_zlg_tim_timing_deinit(handle);
}

/*******************************************************************************
 * TIM5配置
 ******************************************************************************/
/** \brief TIM5平台初始化 */
void __zlg_plfm_tim5_timing_init (void)
{

    /* 使能通用定时器5时钟 */
    am_clk_enable(CLK_TIM5);

    /* 复位通用定时器5 */
    am_zmf159_clk_reset(CLK_TIM5);
}

/** \brief 解除TIM5平台初始化 */
void __zlg_plfm_tim5_timing_deinit (void)
{

    /* 复位通用定时器5 */
    am_zmf159_clk_reset(CLK_TIM5);

    /* 禁能通用定时器5时钟 */
    am_clk_disable(CLK_TIM5);
}

/** \brief TIM5设备信息 */
const am_zlg_tim_timing_devinfo_t  __g_tim5_timing_devinfo = {
    ZMF159_TIM5_BASE,                 /**< \brief TIM5寄存器块的基地址 */
    INUM_TIM5,                        /**< \brief TIM5中断编号 */
    CLK_TIM5,                         /**< \brief TIM5时钟ID */
    AMHW_ZLG_TIM_TYPE1,               /**< \brief 定时器类型 */
    __zlg_plfm_tim5_timing_init,      /**< \brief 平台初始化函数 */
    __zlg_plfm_tim5_timing_deinit     /**< \brief 平台解初始化函数 */
};

/** \brief TIM5设备定义 */
am_zlg_tim_timing_dev_t  __g_tim5_timing_dev;

/** \brief TIM5 Timing实例初始化，获得Timer标准服务句柄 */
am_timer_handle_t am_zmf159_tim5_timing_inst_init (void)
{
    return am_zlg_tim_timing_init(&__g_tim5_timing_dev,
                                  &__g_tim5_timing_devinfo);
}

/** \brief TIM5 Timing实例解初始化 */
void am_zmf159_tim5_timing_inst_deinit (am_timer_handle_t handle)
{
    am_zlg_tim_timing_deinit(handle);
}

/*******************************************************************************
 * TIM6配置
 ******************************************************************************/

/** \brief TIM6平台初始化 */
void __zlg_plfm_tim6_timing_init (void)
{

    /* 使能通用定时器6时钟 */
    am_clk_enable(CLK_TIM6);

    /* 复位通用定时器6 */
    am_zmf159_clk_reset(CLK_TIM6);
}

/** \brief 解除TIM6平台初始化 */
void __zlg_plfm_tim6_timing_deinit (void)
{

    /* 复位通用定时器6 */
    am_zmf159_clk_reset(CLK_TIM6);

    /* 禁能通用定时器6时钟 */
    am_clk_disable(CLK_TIM6);
}

/** \brief TIM6设备信息 */
const am_zlg_tim_timing_devinfo_t  __g_tim6_timing_devinfo = {
    ZMF159_TIM6_BASE,                 /**< \brief TIM6寄存器块的基地址 */
    INUM_TIM6,                        /**< \brief TIM6中断编号 */
    CLK_TIM6,                         /**< \brief TIM6时钟ID */
    AMHW_ZLG_TIM_TYPE3,               /**< \brief 定时器类型 */
    __zlg_plfm_tim6_timing_init,      /**< \brief 平台初始化函数 */
    __zlg_plfm_tim6_timing_deinit     /**< \brief 平台解初始化函数 */
};

/** \brief TIM6设备定义 */
am_zlg_tim_timing_dev_t  __g_tim6_timing_dev;

/** \brief 定时器TIM6 Timing实例初始化，获得Timer标准服务句柄 */
am_timer_handle_t am_zmf159_tim6_timing_inst_init (void)
{
    return am_zlg_tim_timing_init(&__g_tim6_timing_dev,
                                  &__g_tim6_timing_devinfo);
}

/** \brief TIM6 Timing实例解初始化 */
void am_zmf159_tim6_timing_inst_deinit (am_timer_handle_t handle)
{
    am_zlg_tim_timing_deinit(handle);
}

/*******************************************************************************
 * TIM7配置
 ******************************************************************************/

/** \brief TIM7平台初始化 */
void __zlg_plfm_tim7_timing_init (void)
{

    /* 使能通用定时器7时钟 */
    am_clk_enable(CLK_TIM7);

    /* 复位通用定时器7 */
    am_zmf159_clk_reset(CLK_TIM7);
}

/** \brief 解除TIM7平台初始化 */
void __zlg_plfm_tim7_timing_deinit (void)
{

    /* 复位通用定时器7 */
    am_zmf159_clk_reset(CLK_TIM7);

    /* 禁能通用定时器7时钟 */
    am_clk_disable(CLK_TIM7);
}

/** \brief TIM7设备信息 */
const am_zlg_tim_timing_devinfo_t  __g_tim7_timing_devinfo = {
    ZMF159_TIM7_BASE,                /**< \brief TIM7寄存器块的基地址 */
    INUM_TIM7,                       /**< \brief TIM7中断编号 */
    CLK_TIM7,                        /**< \brief TIM7时钟ID */
    AMHW_ZLG_TIM_TYPE3,              /**< \brief 定时器类型 */
    __zlg_plfm_tim7_timing_init,     /**< \brief 平台初始化函数 */
    __zlg_plfm_tim7_timing_deinit    /**< \brief 平台解初始化函数 */
};

/** \brief TIM7设备定义 */
am_zlg_tim_timing_dev_t  __g_tim7_timing_dev;

/** \brief 定时器TIM7 Timing实例初始化，获得Timer标准服务句柄 */
am_timer_handle_t am_zmf159_tim7_timing_inst_init (void)
{
    return am_zlg_tim_timing_init(&__g_tim7_timing_dev,
                                     &__g_tim7_timing_devinfo);
}

/** \brief TIM7 Timing实例解初始化 */
void am_zmf159_tim7_timing_inst_deinit (am_timer_handle_t handle)
{
    am_zlg_tim_timing_deinit(handle);
}

/*******************************************************************************
 * TIM8配置
 ******************************************************************************/

/** \brief TIM8平台初始化 */
void __zlg_plfm_tim8_timing_init (void)
{

    /* 使能通用定时器8时钟 */
    am_clk_enable(CLK_TIM8);

    /* 复位通用定时器8 */
    am_zmf159_clk_reset(CLK_TIM8);
}

/** \brief 解除TIM8平台初始化 */
void __zlg_plfm_tim8_timing_deinit (void)
{

    /* 复位通用定时器7 */
    am_zmf159_clk_reset(CLK_TIM8);

    /* 禁能通用定时器8时钟 */
    am_clk_disable(CLK_TIM8);
}

/** \brief TIM8设备信息 */
const am_zlg_tim_timing_devinfo_t  __g_tim8_timing_devinfo = {
    ZMF159_TIM8_BASE,                /**< \brief TIM8寄存器块的基地址 */
    INUM_TIM8_UP,                    /**< \brief TIM8中断编号 */
    CLK_TIM8,                        /**< \brief TIM8时钟ID */
    AMHW_ZLG_TIM_TYPE0,              /**< \brief 定时器类型 */
    __zlg_plfm_tim7_timing_init,     /**< \brief 平台初始化函数 */
    __zlg_plfm_tim7_timing_deinit    /**< \brief 平台解初始化函数 */
};

/** \brief TIM8设备定义 */
am_zlg_tim_timing_dev_t  __g_tim8_timing_dev;

/** \brief 定时器TIM8 Timing实例初始化，获得Timer标准服务句柄 */
am_timer_handle_t am_zmf159_tim8_timing_inst_init (void)
{
    return am_zlg_tim_timing_init(&__g_tim8_timing_dev,
                                  &__g_tim8_timing_devinfo);
}

/** \brief TIM8 Timing实例解初始化 */
void am_zmf159_tim8_timing_inst_deinit (am_timer_handle_t handle)
{
    am_zlg_tim_timing_deinit(handle);
}

/**
 * @}
 */

/* end of file */
