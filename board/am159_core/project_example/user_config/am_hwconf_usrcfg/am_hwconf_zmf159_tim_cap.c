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
 * \brief ZMF159 TIM用于捕获功能的用户配置文件
 * \sa am_hwconf_zmf159_tim_cap.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 17-04-21  nwt, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_zmf159.h"
#include "am_zlg_tim_cap.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_zmf159_clk.h"

/**
 * \addtogroup am_if_src_hwconf_zmf159_tim_cap
 * \copydoc am_hwconf_zmf159_tim_cap.c
 * @{
 */
 
/*******************************************************************************
 * TIM1 配置
 ******************************************************************************/

/** \brief TIM1用于捕获功能的平台初始化 */
void __zlg_plfm_tim1_cap_init (void)
{

    /* 使能高级定时器1时钟 */
    am_clk_enable(CLK_TIM1);

    /* 复位高级定时器1 */
    am_zmf159_clk_reset(CLK_TIM1);
}

/** \brief 解除TIM1平台初始化 */
void __zlg_plfm_tim1_cap_deinit (void)
{

    /* 复位高级定时器1 */
    am_zmf159_clk_reset(CLK_TIM1);

    /* 禁能高级定时器1时钟 */
    am_clk_disable(CLK_TIM1);
}

/** \brief TIM1用于捕获功能的引脚配置信息列表 */
am_zlg_tim_cap_ioinfo_t __g_tim1_cap_ioinfo_list[] = {

    /** \brief 通道1 */
    {PIOA_8,  PIOA_8_TIM1_CH1  | PIOA_8_INPUT_FLOAT,  PIOA_8_GPIO  | PIOA_8_INPUT_FLOAT},

    /** \brief 通道2 */
    {PIOA_9,  PIOA_9_TIM1_CH2  | PIOA_9_INPUT_FLOAT,  PIOA_9_GPIO  | PIOA_9_INPUT_FLOAT},

    /** \brief 通道3 */
    {PIOA_10, PIOA_10_TIM1_CH3 | PIOA_10_INPUT_FLOAT, PIOA_10_GPIO | PIOA_10_INPUT_FLOAT},

    /** \brief 通道4 */
    {PIOA_11, PIOA_11_TIM1_CH4 | PIOA_11_INPUT_FLOAT, PIOA_11_GPIO | PIOA_11_INPUT_FLOAT}
};

/** \brief TIM1用于捕获功能的设备信息 */
const am_zlg_tim_cap_devinfo_t  __g_tim1_cap_devinfo = {
    ZMF159_TIM1_BASE,               /**< \brief TIM1寄存器块的基地址 */
    INUM_TIM1_CC,                   /**< \brief TIM1中断编号 */
    CLK_TIM1,                       /**< \brief TIM1时钟ID */
    4,                              /**< \brief 4个捕获通道 */
    &__g_tim1_cap_ioinfo_list[0],   /**< \brief 引脚配置信息列表 */
    AMHW_ZLG_TIM_TYPE0,             /**< \brief 定时器类型 */
    __zlg_plfm_tim1_cap_init,       /**< \brief 平台初始化函数 */
    __zlg_plfm_tim1_cap_deinit      /**< \brief 平台解初始化函数 */
};

/** \brief TIM1用于捕获功能的设备定义 */
am_zlg_tim_cap_dev_t  __g_tim1_cap_dev;

/** \brief tim1 cap实例初始化，获得cap标准服务句柄 */
am_cap_handle_t am_zmf159_tim1_cap_inst_init (void)
{
    return am_zlg_tim_cap_init(&__g_tim1_cap_dev,
                                  &__g_tim1_cap_devinfo);
}

/** \brief tim1 cap实例解初始化 */
void am_zmf159_tim1_cap_inst_deinit (am_cap_handle_t handle)
{
    am_zlg_tim_cap_deinit(handle);
}

/*******************************************************************************
 * TIM2 配置
 ******************************************************************************/

/** \brief TIM2用于捕获功能的平台初始化 */
void __zlg_plfm_tim2_cap_init (void)
{

    /* 使能通用定时器2时钟 */
    am_clk_enable(CLK_TIM2);

    /* 复位通用定时器2 */
    am_zmf159_clk_reset(CLK_TIM2);
}

/** \brief 解除TIM2平台初始化 */
void __zlg_plfm_tim2_cap_deinit (void)
{

    /* 复位通用定时器2 */
    am_zmf159_clk_reset(CLK_TIM2);

    /* 禁能通用定时器2时钟 */
    am_clk_disable(CLK_TIM2);
}

/** \brief TIM2用于捕获功能的引脚配置信息列表 */
am_zlg_tim_cap_ioinfo_t __g_tim2_cap_ioinfo_list[] = {

    /** \brief 通道1 */
    {PIOA_0, PIOA_0_TIM2_CH1_ETR | PIOA_0_INPUT_FLOAT, PIOA_0_GPIO | PIOA_0_INPUT_FLOAT},

    /** \brief 通道2 */
    {PIOA_1, PIOA_1_TIM2_CH2     | PIOB_1_INPUT_FLOAT, PIOA_1_GPIO | PIOA_1_INPUT_FLOAT},

    /** \brief 通道2 */
    {PIOA_2, PIOA_2_TIM2_CH3     | PIOB_2_INPUT_FLOAT, PIOA_2_GPIO | PIOA_2_INPUT_FLOAT},

    /** \brief 通道2 */
    {PIOA_3, PIOA_3_TIM2_CH4     | PIOB_3_INPUT_FLOAT, PIOA_3_GPIO | PIOA_3_INPUT_FLOAT},
};

/** \brief TIM2用于捕获功能的设备信息 */
const am_zlg_tim_cap_devinfo_t  __g_tim2_cap_devinfo = {
    ZMF159_TIM2_BASE,               /**< \brief TIM2寄存器块的基地址 */
    INUM_TIM2,                      /**< \brief TIM2中断编号 */
    CLK_TIM2,                       /**< \brief TIM2时钟ID */
    4,                              /**< \brief 4个捕获通道 */
    &__g_tim2_cap_ioinfo_list[0],   /**< \brief 引脚配置信息列表 */
    AMHW_ZLG_TIM_TYPE1,             /**< \brief 定时器类型 */
    __zlg_plfm_tim2_cap_init,       /**< \brief 平台初始化函数 */
    __zlg_plfm_tim2_cap_deinit      /**< \brief 平台解初始化函数 */
};

/** \brief TIM2用于捕获功能的设备定义 */
am_zlg_tim_cap_dev_t  __g_tim2_cap_dev;

/** \brief tim2 cap实例初始化，获得cap标准服务句柄 */
am_cap_handle_t am_zmf159_tim2_cap_inst_init (void)
{
    return am_zlg_tim_cap_init(&__g_tim2_cap_dev,
                                  &__g_tim2_cap_devinfo);
}

/** \brief tim2 cap实例解初始化 */
void am_zmf159_tim2_cap_inst_deinit (am_cap_handle_t handle)
{
    am_zlg_tim_cap_deinit(handle);
}

/*******************************************************************************
 * TIM3 配置
 ******************************************************************************/

/** \brief TIM3用于捕获功能的平台初始化 */
void __zlg_plfm_tim3_cap_init (void)
{

    /* 使能通用定时器3时钟 */
    am_clk_enable(CLK_TIM3);

    /* 复位通用定时器3 */
    am_zmf159_clk_reset(CLK_TIM3);
}

/** \brief 解除TIM3平台初始化 */
void __zlg_plfm_tim3_cap_deinit (void)
{

    /* 复位通用定时器3 */
    am_zmf159_clk_reset(CLK_TIM3);

    /* 禁能通用定时器3时钟 */
    am_clk_disable(CLK_TIM3);
}

/** \brief TIM3用于捕获功能的引脚配置信息列表 */
am_zlg_tim_cap_ioinfo_t __g_tim3_cap_ioinfo_list[] = {

    /** \brief 通道1 */
    {PIOB_4,  PIOB_4_TIM3_CH1 | PIOB_4_INPUT_FLOAT, PIOB_4_GPIO | PIOB_4_INPUT_FLOAT},

    /** \brief 通道2 */
    {PIOB_5,  PIOB_5_TIM3_CH2 | PIOB_5_INPUT_FLOAT, PIOB_5_GPIO | PIOB_5_INPUT_FLOAT},

    /** \brief 通道3 */
    {PIOB_0,  PIOB_0_TIM3_CH3 | PIOB_0_INPUT_FLOAT, PIOB_0_GPIO | PIOB_0_INPUT_FLOAT},

    /** \brief 通道4 */
    {PIOB_1,  PIOB_1_TIM3_CH4 | PIOB_1_INPUT_FLOAT, PIOB_1_GPIO | PIOB_1_INPUT_FLOAT},
};

/** \brief TIM3用于捕获功能的设备信息 */
const am_zlg_tim_cap_devinfo_t  __g_tim3_cap_devinfo = {
    ZMF159_TIM3_BASE,               /**< \brief TIM3寄存器块的基地址 */
    INUM_TIM3,                      /**< \brief TIM3中断编号 */
    CLK_TIM3,                       /**< \brief TIM3时钟ID */
    4,                              /**< \brief 4个捕获通道 */
    &__g_tim3_cap_ioinfo_list[0],   /**< \brief 引脚配置信息列表 */
    AMHW_ZLG_TIM_TYPE1,             /**< \brief 定时器类型 */
    __zlg_plfm_tim3_cap_init,       /**< \brief 平台初始化函数 */
    __zlg_plfm_tim3_cap_deinit      /**< \brief 平台解初始化函数 */

};

/** \brief TIM3用于捕获功能的设备定义 */
am_zlg_tim_cap_dev_t  __g_tim3_cap_dev;

/** \brief tim3 cap实例初始化，获得cap标准服务句柄 */
am_cap_handle_t am_zmf159_tim3_cap_inst_init (void)
{
    return am_zlg_tim_cap_init(&__g_tim3_cap_dev,
                                  &__g_tim3_cap_devinfo);
}

/** \brief tim3 cap实例解初始化 */
void am_zmf159_tim3_cap_inst_deinit (am_cap_handle_t handle)
{
    am_zlg_tim_cap_deinit(handle);
}

/*******************************************************************************
 * TIM4 配置
 ******************************************************************************/

/** \brief TIM4用于捕获功能的平台初始化 */
void __zlg_plfm_tim4_cap_init (void)
{

    /* 使能通用定时器4时钟 */
    am_clk_enable(CLK_TIM4);

    /* 复位通用定时器4 */
    am_zmf159_clk_reset(CLK_TIM4);
}

/** \brief 解除TIM4平台初始化 */
void __zlg_plfm_tim4_cap_deinit (void)
{

    /* 复位通用定时器4 */
    am_zmf159_clk_reset(CLK_TIM4);

    /* 禁能通用定时器4时钟 */
    am_clk_disable(CLK_TIM4);
}

/** \brief TIM4用于捕获功能的引脚配置信息列表 */
am_zlg_tim_cap_ioinfo_t __g_tim4_cap_ioinfo_list[] = {

    /** \brief 通道1 */
    {PIOB_6,  PIOB_6_TIM4_CH1 | PIOB_6_INPUT_FLOAT, PIOB_6_GPIO | PIOB_6_INPUT_FLOAT},
    /** \brief 通道2 */
    {PIOB_7,  PIOB_7_TIM4_CH2 | PIOB_7_INPUT_FLOAT, PIOB_7_GPIO | PIOB_7_INPUT_FLOAT},
    /** \brief 通道3 */
    {PIOB_8,  PIOB_8_TIM4_CH3 | PIOB_8_INPUT_FLOAT, PIOB_8_GPIO | PIOB_8_INPUT_FLOAT},
    /** \brief 通道4 */
    {PIOB_9,  PIOB_9_TIM4_CH4 | PIOB_9_INPUT_FLOAT, PIOB_9_GPIO | PIOB_9_INPUT_FLOAT},
};

/** \brief TIM4用于捕获功能的设备信息 */
const am_zlg_tim_cap_devinfo_t  __g_tim4_cap_devinfo = {
    ZMF159_TIM4_BASE,               /**< \brief TIM4寄存器块的基地址 */
    INUM_TIM4,                      /**< \brief TIM4中断编号 */
    CLK_TIM4,                       /**< \brief TIM4时钟ID */
    4,                              /**< \brief 4个捕获通道 */
    &__g_tim4_cap_ioinfo_list[0],   /**< \brief 引脚配置信息列表 */
    AMHW_ZLG_TIM_TYPE2,             /**< \brief 定时器类型 */
    __zlg_plfm_tim4_cap_init,       /**< \brief 平台初始化函数 */
    __zlg_plfm_tim4_cap_deinit      /**< \brief 平台解初始化函数 */
};

/** \brief TIM4用于捕获功能的设备定义 */
am_zlg_tim_cap_dev_t  __g_tim4_cap_dev;

/** \brief tim4 cap实例初始化，获得cap标准服务句柄 */
am_cap_handle_t am_zmf159_tim4_cap_inst_init (void)
{
    return am_zlg_tim_cap_init(&__g_tim4_cap_dev,
                               &__g_tim4_cap_devinfo);
}

/** \brief tim4 cap实例解初始化 */
void am_zmf159_tim4_cap_inst_deinit (am_cap_handle_t handle)
{
    am_zlg_tim_cap_deinit(handle);
}

/*******************************************************************************
 * TIM5 配置
 ******************************************************************************/

/** \brief TIM5用于捕获功能的平台初始化 */
void __zlg_plfm_tim5_cap_init (void)
{

    /* 使能通用定时器5时钟 */
    am_clk_enable(CLK_TIM5);

    /* 复位通用定时器5 */
    am_zmf159_clk_reset(CLK_TIM5);
}

/** \brief 解除TIM5平台初始化 */
void __zlg_plfm_tim5_cap_deinit (void)
{

    /* 复位通用定时器5 */
    am_zmf159_clk_reset(CLK_TIM5);

    /* 禁能通用定时器5时钟 */
    am_clk_disable(CLK_TIM5);
}

/** \brief TIM5用于捕获功能的引脚配置信息列表 */
am_zlg_tim_cap_ioinfo_t __g_tim5_cap_ioinfo_list[] = {

    /** \brief 通道1 */
    {PIOA_0,  PIOA_0_TIM5_CH1 | PIOA_0_INPUT_FLOAT, PIOA_0_GPIO | PIOA_0_INPUT_FLOAT},
};

/** \brief TIM5用于捕获功能的设备信息 */
const am_zlg_tim_cap_devinfo_t  __g_tim5_cap_devinfo = {
    ZMF159_TIM5_BASE,               /**< \brief TIM5寄存器块的基地址 */
    INUM_TIM5,                      /**< \brief TIM5中断编号 */
    CLK_TIM5,                       /**< \brief TIM5时钟ID */
    1,                              /**< \brief 1个捕获通道 */
    &__g_tim5_cap_ioinfo_list[0],   /**< \brief 引脚配置信息列表 */
    AMHW_ZLG_TIM_TYPE2,             /**< \brief 定时器类型 */
    __zlg_plfm_tim5_cap_init,       /**< \brief 平台初始化函数 */
    __zlg_plfm_tim5_cap_deinit      /**< \brief 平台解初始化函数 */
};

/** \brief TIM5用于捕获功能的设备定义 */
am_zlg_tim_cap_dev_t  __g_tim5_cap_dev;

/** \brief tim5 cap实例初始化，获得cap标准服务句柄 */
am_cap_handle_t am_zmf159_tim5_cap_inst_init (void)
{
    return am_zlg_tim_cap_init(&__g_tim5_cap_dev,
                               &__g_tim5_cap_devinfo);
}

/** \brief tim5 cap实例解初始化 */
void am_zmf159_tim5_cap_inst_deinit (am_cap_handle_t handle)
{
    am_zlg_tim_cap_deinit(handle);
}


/*******************************************************************************
 * TIM8 配置
 ******************************************************************************/

/** \brief TIM8用于捕获功能的平台初始化 */
void __zlg_plfm_tim8_cap_init (void)
{

    /* 使能通用定时器8时钟 */
    am_clk_enable(CLK_TIM8);

    /* 复位通用定时器8 */
    am_zmf159_clk_reset(CLK_TIM8);
}

/** \brief 解除TIM8平台初始化 */
void __zlg_plfm_tim8_cap_deinit (void)
{

    /* 复位通用定时器8 */
    am_zmf159_clk_reset(CLK_TIM8);

    /* 禁能通用定时器8时钟 */
    am_clk_disable(CLK_TIM8);
}

/** \brief TIM8用于捕获功能的引脚配置信息列表 */
am_zlg_tim_cap_ioinfo_t __g_tim8_cap_ioinfo_list[] = {

    /** \brief 通道1 */
    {PIOC_6, PIOC_6_TIM8_CH1 | PIOC_6_INPUT_FLOAT, PIOC_6_GPIO | PIOC_6_INPUT_FLOAT},
};

/** \brief TIM8用于捕获功能的设备信息 */
const am_zlg_tim_cap_devinfo_t  __g_tim8_cap_devinfo = {
    ZMF159_TIM8_BASE,               /**< \brief TIM8寄存器块的基地址 */
    INUM_TIM8_CC,                      /**< \brief TIM8中断编号 */
    CLK_TIM8,                       /**< \brief TIM8时钟ID */
    1,                              /**< \brief 1个捕获通道 */
    &__g_tim8_cap_ioinfo_list[0],  /**< \brief 引脚配置信息列表 */
    AMHW_ZLG_TIM_TYPE3,             /**< \brief 定时器类型 */
    __zlg_plfm_tim8_cap_init,       /**< \brief 平台初始化函数 */
    __zlg_plfm_tim8_cap_deinit      /**< \brief 平台解初始化函数 */

};

/** \brief TIM8用于捕获功能的设备定义 */
am_zlg_tim_cap_dev_t  __g_tim8_cap_dev;

/** \brief tim8 cap实例初始化，获得cap标准服务句柄 */
am_cap_handle_t am_zmf159_tim8_cap_inst_init (void)
{
    return am_zlg_tim_cap_init(&__g_tim8_cap_dev,
                               &__g_tim8_cap_devinfo);
}

/** \brief tim7 cap实例解初始化 */
void am_zmf159_tim8_cap_inst_deinit (am_cap_handle_t handle)
{
    am_zlg_tim_cap_deinit(handle);
}


/**
 * @}
 */

/* end of file */
