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
 * \brief ZLG GPIO 引脚配置参数定义
 *
 * \note: 配置引脚功能的时候一定要同时配置引脚的模式，如上下拉模式、推挽模式等
 *
 * \internal
 * \par Modification History
 * - 1.00 17-08-21  zcb, first implementation
 * \endinternal
 */

#ifndef __ZMF159_PIN_H
#define __ZMF159_PIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_zmf159_gpio_util.h"

 /**
 * \addtogroup zmf159_if_pin
 * \copydoc zmf159_pin.h
 * @{
 */

/**
 * \name ZMF159 GPIO 引脚编号
 * \anchor grp_gpio_pin_number
 * @{
 */

#define PIOA            0         /**< \brief 端口A引脚起始号 */
#define PIOA_0          0         /**< \brief PIOA_0 引脚号 */
#define PIOA_1          1         /**< \brief PIOA_1 引脚号 */
#define PIOA_2          2         /**< \brief PIOA_2 引脚号 */
#define PIOA_3          3         /**< \brief PIOA_3 引脚号 */
#define PIOA_4          4         /**< \brief PIOA_4 引脚号 */
#define PIOA_5          5         /**< \brief PIOA_5 引脚号 */
#define PIOA_6          6         /**< \brief PIOA_6 引脚号 */
#define PIOA_7          7         /**< \brief PIOA_7 引脚号 */
#define PIOA_8          8         /**< \brief PIOA_8 引脚号 */
#define PIOA_9          9         /**< \brief PIOA_9 引脚号 */
#define PIOA_10         10        /**< \brief PIOA_10 引脚号 */
#define PIOA_11         11        /**< \brief PIOA_11 引脚号 */
#define PIOA_12         12        /**< \brief PIOA_13 引脚号 */
#define PIOA_13         13        /**< \brief PIOA_13 引脚号 */
#define PIOA_14         14        /**< \brief PIOA_14 引脚号 */
#define PIOA_15         15        /**< \brief PIOA_15 引脚号 */

#define PIOB            16        /**< \brief 端口B引脚起始号 */
#define PIOB_0          16        /**< \brief PIOB_0 引脚号 */
#define PIOB_1          17        /**< \brief PIOB_1 引脚号 */
#define PIOB_2          18        /**< \brief PIOB_2 引脚号 */
#define PIOB_3          19        /**< \brief PIOB_3 引脚号 */
#define PIOB_4          20        /**< \brief PIOB_4 引脚号 */
#define PIOB_5          21        /**< \brief PIOB_5 引脚号 */
#define PIOB_6          22        /**< \brief PIOB_6 引脚号 */
#define PIOB_7          23        /**< \brief PIOB_7 引脚号 */
#define PIOB_8          24        /**< \brief PIOB_8 引脚号 */
#define PIOB_9          25        /**< \brief PIOB_9 引脚号 */
#define PIOB_10         26        /**< \brief PIOB_10引脚号 */
#define PIOB_11         27        /**< \brief PIOB_11引脚号 */
#define PIOB_12         28        /**< \brief PIOB_12引脚号 */
#define PIOB_13         29        /**< \brief PIOB_13引脚号 */
#define PIOB_14         30        /**< \brief PIOB_14引脚号 */
#define PIOB_15         31        /**< \brief PIOB_15引脚号 */

#define PIOC            32        /**< \brief 端口C引脚起始号 */
#define PIOC_0          32        /**< \brief PIOC_0 引脚号 */
#define PIOC_1          33        /**< \brief PIOC_1 引脚号 */
#define PIOC_2          34        /**< \brief PIOC_2 引脚号 */
#define PIOC_3          35        /**< \brief PIOC_3 引脚号 */
#define PIOC_4          36        /**< \brief PIOC_4 引脚号 */
#define PIOC_5          37        /**< \brief PIOC_5 引脚号 */
#define PIOC_6          38        /**< \brief PIOC_6 引脚号 */
#define PIOC_7          39        /**< \brief PIOC_7 引脚号 */
#define PIOC_8          40        /**< \brief PIOC_8 引脚号 */
#define PIOC_9          41        /**< \brief PIOC_9 引脚号 */
#define PIOC_10         42        /**< \brief PIOC_10引脚号 */
#define PIOC_11         43        /**< \brief PIOC_11引脚号 */
#define PIOC_12         44        /**< \brief PIOC_12引脚号 */
#define PIOC_13         45        /**< \brief PIOC_13引脚号 */
#define PIOC_14         46        /**< \brief PIOC_14引脚号 */
#define PIOC_15         47        /**< \brief PIOC_15引脚号 */

#define PIOD            48        /**< \brief 端口D引脚起始号 */
#define PIOD_0          48        /**< \brief PIOD_0 引脚号 */
#define PIOD_1          49        /**< \brief PIOD_1 引脚号 */
#define PIOD_2          50        /**< \brief PIOD_2 引脚号 */
#define PIOD_3          51        /**< \brief PIOD_3 引脚号 */
#define PIOD_4          52        /**< \brief PIOD_4 引脚号 */
#define PIOD_5          53        /**< \brief PIOD_5 引脚号 */
#define PIOD_6          54        /**< \brief PIOD_6 引脚号 */
#define PIOD_7          55        /**< \brief PIOD_7 引脚号 */
#define PIOD_8          56        /**< \brief PIOD_8 引脚号 */
#define PIOD_9          57        /**< \brief PIOD_9 引脚号 */
#define PIOD_10         58        /**< \brief PIOD_10引脚号 */
#define PIOD_11         59        /**< \brief PIOD_11引脚号 */
#define PIOD_12         60        /**< \brief PIOD_12引脚号 */
#define PIOD_13         61        /**< \brief PIOD_13引脚号 */
#define PIOD_14         62        /**< \brief PIOD_14引脚号 */
#define PIOD_15         63        /**< \brief PIOD_15引脚号 */

#define PIOE            64        /**< \brief 端口E引脚起始号 */
#define PIOE_0          64        /**< \brief PIOE_0 引脚号 */
#define PIOE_1          65        /**< \brief PIOE_1 引脚号 */
#define PIOE_2          66        /**< \brief PIOE_2 引脚号 */
#define PIOE_3          67        /**< \brief PIOE_3 引脚号 */
#define PIOE_4          68        /**< \brief PIOE_4 引脚号 */
#define PIOE_5          69        /**< \brief PIOE_5 引脚号 */
#define PIOE_6          70        /**< \brief PIOE_6 引脚号 */
#define PIOE_7          71        /**< \brief PIOE_7 引脚号 */
#define PIOE_8          72        /**< \brief PIOE_8 引脚号 */
#define PIOE_9          73        /**< \brief PIOE_9 引脚号 */
#define PIOE_10         74        /**< \brief PIOE_10引脚号 */
#define PIOE_11         75        /**< \brief PIOE_11引脚号 */
#define PIOE_12         76        /**< \brief PIOE_12引脚号 */
#define PIOE_13         77        /**< \brief PIOE_13引脚号 */
#define PIOE_14         78        /**< \brief PIOE_14引脚号 */
#define PIOE_15         79        /**< \brief PIOE_15引脚号 */

/**
 * \brief 引脚数目为72
 */
#define PIN_NUM         80

/**
 * \brief 支持同时发生最大引脚中断数是16
 */
#define PIN_INT_MAX     16

/** @} */

/**
 * \name ZMF159 引脚定义,除调试引脚SWCK、SWIO之外，所有引脚复位时都默认为GPIO功能(浮空输入)
 * @{
 */

/******************************************************************************/

/**
 * \name PIOA_0引脚复用功能
 * @{
 */
#define PIOA_0_TIM2_CH1_ETR   AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM2_CH1_ETR */
#define PIOA_0_TIM5_CH1       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM5_CH1_ETR */
#define PIOA_0_TIM8_CH1_ETR   AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM8_CH1_ETR */
#define PIOA_0_UART2_CTS      AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART2_CTS */
#define PIOA_0_UART4_TX       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART4_TX */
#define PIOA_0_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0xFF)   /**< \brief GPIO */
/** @} */

/**
 * \name PIOA_0引脚复用时功能模式
 * @{
 */
#define PIOA_0_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOA_0_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOA_0_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOA_0_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOA_0_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOA_0_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOA_0_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOA_0_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */
/** @} */

/**
 * \name PIOA_0引脚响应速率
 * @{
 */
#define PIOA_0_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOA_0_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOA_0_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */
/** @} */

/******************************************************************************/

/**
 * \name PIOA_1引脚复用功能
 * @{
 */


#define PIOA_1_TIM2_CH2       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM2_CH2 */
#define PIOA_1_TIM5_CH2       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM2_CH2 */
#define PIOA_1_UART2_RTS      AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART2_RTS */
#define PIOA_1_UART4_RX       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART4_RX */
#define PIOA_1_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0xFF)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_1引脚复用时功能模式
 * @{
 */

#define PIOA_1_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOA_1_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOA_1_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOA_1_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOA_1_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOA_1_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOA_1_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOA_1_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOA_1引脚响应速率
 * @{
 */

#define PIOA_1_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOA_1_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOA_1_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_2引脚复用功能
 * @{
 */

#define PIOA_2_TIM2_CH3       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM2_CH3 */
#define PIOA_2_TIM5_CH3       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM5_CH3 */
#define PIOA_2_UART2_TX       AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART2_TX */
#define PIOA_2_CPT2_OUT       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief CPT2_OUT */
#define PIOA_2_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0xFF)   /**< \brief GPIO */
/** @} */

/**
 * \name PIOA_2引脚复用时功能模式
 * @{
 */

#define PIOA_2_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOA_2_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOA_2_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOA_2_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOA_2_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOA_2_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOA_2_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOA_2_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOA_2引脚响应速率
 * @{
 */

#define PIOA_2_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOA_2_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOA_2_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_3引脚复用功能
 * @{
 */

#define PIOA_3_TIM2_CH4       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM2_CH4 */
#define PIOA_3_TIM5_CH4       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM2_CH4 */
#define PIOA_3_UART2_RX       AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART2_RX */
#define PIOA_3_ADC_IN3        AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief ADC_IN3 */
#define PIOA_3_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0xFF)   /**< \brief GPIO */
/** @} */

/**
 * \name PIOA_3引脚复用时功能模式
 * @{
 */

#define PIOA_3_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOA_3_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOA_3_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOA_3_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOA_3_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOA_3_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOA_3_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOA_3_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOA_3引脚响应速率
 * @{
 */

#define PIOA_3_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOA_3_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOA_3_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_4引脚复用功能
 * @{
 */

#define PIOA_4_SPI1_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x05)    /**< \brief SPI1_NSS */
#define PIOA_4_SPI3_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x06)    /**< \brief SPI3_NSS */
#define PIOA_4_UART5_TX       AM_ZMF159_GPIO_FUNC_CODE(0x08)    /**< \brief UART5_TX */
#define PIOA_4_SPI1_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x0D)    /**< \brief SPI1_MOSI */
#define PIOA_4_SPI1_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x0E)    /**< \brief SPI1_MISO */
#define PIOA_4_SPI1_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x0F)    /**< \brief SPI1_SCK */
#define PIOA_4_ADC_IN4        AM_ZMF159_GPIO_FUNC_CODE(0x0F)    /**< \brief ADC_IN4 */
#define PIOA_4_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)    /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_4引脚复用时功能模式
 * @{
 */

#define PIOA_4_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOA_4_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOA_4_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOA_4_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOA_4_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOA_4_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOA_4_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOA_4_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOA_4引脚响应速率
 * @{
 */

#define PIOA_4_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOA_4_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOA_4_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_5引脚复用功能
 * @{
 */

#define PIOA_5_TIM2_CH1_ETR   AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM2_CH1_ETR */
#define PIOA_5_TIM8_CH1N      AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM2_CH1N */
#define PIOA_5_SPI1_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI1_SCK */
#define PIOA_5_UART5_RX       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART5_RX */
#define PIOA_5_SPI1_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x0D)   /**< \brief SPI1_NSS */
#define PIOA_5_SPI1_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x0E)   /**< \brief SPI1_MOSI */
#define PIOA_5_SPI1_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief SPI1_MISO */
#define PIOA_5_ADC_IN5        AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief ADC_IN5 */
#define PIOA_5_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_5引脚复用时功能模式
 * @{
 */

#define PIOA_5_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOA_5_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOA_5_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOA_5_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOA_5_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOA_5_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOA_5_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOA_5_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOA_5引脚响应速率
 * @{
 */

#define PIOA_5_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOA_5_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOA_5_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_6引脚复用功能
 * @{
 */

#define PIOA_6_TIM1_BKIN      AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_BKIN */
#define PIOA_6_TIM3_CH1       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM3_CH3 */
#define PIOA_6_TIM8_KIN       AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM3_CH3 */
#define PIOA_6_SPI1_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI1_MISO */
#define PIOA_6_CPT1_OUT       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief CPT1_OUT */
#define PIOA_6_SPI1_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x0D)   /**< \brief SPI1_SCK */
#define PIOA_6_SPI1_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x0E)   /**< \brief SPI1_NSS */
#define PIOA_6_SPI1_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief SPI1_MOSI */
#define PIOA_6_ADC_IN6        AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief ADC_IN6 */
#define PIOA_6_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_6引脚复用时功能模式
 * @{
 */

#define PIOA_6_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOA_6_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOA_6_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOA_6_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOA_6_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOA_6_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOA_6_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOA_6_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOA_6引脚响应速率
 * @{
 */

#define PIOA_6_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOA_6_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOA_6_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_7引脚复用功能
 * @{
 */

#define PIOA_7_TIM1_CH1N      AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH1N */
#define PIOA_7_TIM3_CH2       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM3_CH2 */
#define PIOA_7_TIM8_CH1N      AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM8_CH1 */
#define PIOA_7_SPI1_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI1_MOSI */
#define PIOA_7_CRS_SYNC       AM_ZMF159_GPIO_FUNC_CODE(0x0A)   /**< \brief CPT1_OUT */
#define PIOA_7_SPI1_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x0D)   /**< \brief SPI1_SCK */
#define PIOA_7_SPI1_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x0E)   /**< \brief SPI1_NSS */
#define PIOA_7_SPI1_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief SPI1_MOSI */
#define PIOA_7_ADC_IN7        AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief ADC_IN7 */
#define PIOA_7_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_7引脚复用时功能模式
 * @{
 */

#define PIOA_7_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOA_7_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOA_7_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOA_7_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOA_7_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOA_7_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOA_7_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOA_7_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOA_7引脚响应速率
 * @{
 */

#define PIOA_7_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOA_7_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOA_7_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_8引脚复用功能
 * @{
 */

#define PIOA_8_MCO1           AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief MCO */
#define PIOA_8_TIM1_CH1       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH1 */
#define PIOA_8_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_8引脚复用时功能模式
 * @{
 */

#define PIOA_8_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOA_8_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOA_8_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOA_8_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOA_8_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOA_8_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOA_8_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOA_8_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOA_8引脚响应速率
 * @{
 */

#define PIOA_8_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOA_8_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOA_8_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_9引脚复用功能
 * @{
 */


#define PIOA_9_TIM1_CH2       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM2_CH2 */
#define PIOA_9_I2C1_SCL       AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C1_SCL */
#define PIOA_9_UART1_TX       AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART1_TX */
#define PIOA_9_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */
/** @} */

/**
 * \name PIOA_9引脚复用时功能模式
 * @{
 */

#define PIOA_9_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOA_9_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOA_9_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOA_9_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOA_9_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOA_9_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOA_9_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOA_9_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOA_9引脚响应速率
 * @{
 */

#define PIOA_9_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz输出响应速率 */
#define PIOA_9_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOA_9_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_10引脚复用功能
 * @{
 */

#define PIOA_10_TIM1_CH3       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH3 */
#define PIOA_10_I2C1_SDA       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief I2C_SDA */
#define PIOA_10_UART1_RX       AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART1_RX */
#define PIOA_10_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */
/** @} */

/**
 * \name PIOA_10引脚复用时功能模式
 * @{
 */

#define PIOA_10_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOA_10_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOA_10_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOA_10_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOA_10_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOA_10_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOA_10_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOA_10_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOA_10引脚响应速率
 * @{
 */

#define PIOA_10_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOA_10_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOA_10_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_11引脚复用功能
 * @{
 */

#define PIOA_11_TIM1_CH4       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH4 */
#define PIOA_11_UART1_CTS      AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART1_CTS */
#define PIOA_11_CAP1_OUT       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART1_CTS */
#define PIOA_11_CAN1_RX        AM_ZMF159_GPIO_FUNC_CODE(0x09)   /**< \brief UART1_CTS */
#define PIOA_11_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_11引脚复用时功能模式
 * @{
 */

#define PIOA_11_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOA_11_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOA_11_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOA_11_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOA_11_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOA_11_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOA_11_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOA_11_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOA_11引脚响应速率
 * @{
 */

#define PIOA_11_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOA_11_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOA_11_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_12引脚复用功能
 * @{
 */

#define PIOA_12_TIM1_ETR       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_ETR */
#define PIOA_12_UART1_RTS      AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART1_RTS */
#define PIOA_12_CAP2_OUT       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief CAP2_OUT */
#define PIOA_12_CAN1_TX        AM_ZMF159_GPIO_FUNC_CODE(0x09)   /**< \brief CAN1_TX */
#define PIOA_12_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_12引脚复用时功能模式
 * @{
 */

#define PIOA_12_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOA_12_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOA_12_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOA_12_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOA_12_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOA_12_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOA_12_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */

#define PIOA_12_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOA_12引脚响应速率
 * @{
 */

#define PIOA_12_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOA_12_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOA_12_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_13引脚复用功能
 * @{
 */

#define PIOA_13_SWDIO          AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief SWDIO */
#define PIOA_13_USB_VBUS_ON    AM_ZMF159_GPIO_FUNC_CODE(0x0A)   /**< \brief USB_VBUS_ON */
#define PIOA_13_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_13引脚复用时功能模式
 * @{
 */

#define PIOA_13_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOA_13_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOA_13_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOA_13_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOA_13_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOA_13_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOA_13_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOA_13_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOA_13引脚响应速率
 * @{
 */

#define PIOA_13_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOA_13_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOA_13_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_14引脚复用功能
 * @{
 */

#define PIOA_14_SWDCLK         AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief SWDCLK */
#define PIOA_14_I2C1_SDA       AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief UART2_TX */
#define PIOA_14_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_14引脚复用时功能模式
 * @{
 */

#define PIOA_14_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOA_14_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOA_14_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOA_14_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOA_14_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOA_14_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOA_14_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOA_14_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOA_14引脚响应速率
 * @{
 */

#define PIOA_14_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOA_14_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOA_14_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOA_15引脚复用功能
 * @{
 */

#define PIOA_15_JTDI           AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief JTD1 */
#define PIOA_15_TIM2_CH1_ETR   AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM2_CH1_ETR */
#define PIOA_15_I2C1_SCL       AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief UART2_RX */
#define PIOA_15_SPI1_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI1_NSS */
#define PIOA_15_SPI3_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x06)   /**< \brief SPI3_NSS */
#define PIOA_15_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOA_15引脚复用时功能模式
 * @{
 */

#define PIOA_15_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOA_15_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOA_15_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOA_15_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOA_15_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOA_15_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOA_15_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOA_15_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOA_15引脚响应速率
 * @{
 */

#define PIOA_15_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOA_15_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOA_15_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_0引脚复用功能
 * @{
 */

#define PIOB_0_TIM1_CH2N       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH2N */
#define PIOB_0_TIM3_CH3        AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM3_CH3 */
#define PIOB_0_TIM8_CH2N       AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM8_CH2N */
#define PIOB_0_UART6_TX        AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART6_TX */
#define PIOB_0_ADC_IN8         AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief ADC_IN8 */
#define PIOB_0_GPIO            AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_8引脚复用时功能模式
 * @{
 */

#define PIOB_0_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOB_0_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOB_0_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOB_0_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOB_0_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOB_0_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOB_0_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOB_0_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOB_0引脚响应速率
 * @{
 */

#define PIOB_0_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOB_0_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOB_0_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_1引脚复用功能
 * @{
 */

#define PIOB_1_TIM1_CH3N       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH2N */
#define PIOB_1_TIM3_CH4        AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM3_CH3 */
#define PIOB_1_TIM8_CH3N       AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM8_CH2N */
#define PIOB_1_UART6_RX        AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART6_RX */
#define PIOB_1_ADC_IN9         AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief ADC_IN9 */
#define PIOB_1_GPIO            AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_1引脚复用时功能模式
 * @{
 */

#define PIOB_1_AIN           AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOB_1_INPUT_FLOAT   AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOB_1_INPUT_PD      AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOB_1_INPUT_PU      AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOB_1_OUT_PP        AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOB_1_OUT_OD        AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOB_1_AF_PP         AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOB_1_AF_OD         AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOB_1引脚响应速率
 * @{
 */

#define PIOB_1_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOB_1_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOB_1_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_2引脚复用功能
 * @{
 */

#define PIOB_2_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_2引脚复用时功能模式
 * @{
 */

#define PIOB_2_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOB_2_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOB_2_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOB_2_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOB_2_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOB_2_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOB_2_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOB_2_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOB_2引脚响应速率
 * @{
 */

#define PIOB_2_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOB_2_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOB_2_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_3引脚复用功能
 * @{
 */
#define PIOB_3_JTDO           AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief JTD0 */
#define PIOB_3_TRACESWO       AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief SPI1_SCK */
#define PIOB_3_TIM2_CH2       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM2_CH1 */
#define PIOB_3_SPI1_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI1_SCK */
#define PIOB_3_SPI3_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x06)   /**< \brief SPI1_SCK */
#define PIOB_3_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */
/** @} */

/**
 * \name PIOB_3引脚复用时功能模式
 * @{
 */

#define PIOB_3_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOB_3_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOB_3_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOB_3_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOB_3_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOB_3_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOB_3_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOB_3_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOB_3引脚响应速率
 * @{
 */

#define PIOB_3_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOB_3_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOB_3_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_4引脚复用功能
 * @{
 */
#define PIOB_4_NJRST          AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief NJTRST */
#define PIOB_4_TIM3_CH1       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM3_CH1 */
#define PIOB_4_SPI1_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI1_MISO */
#define PIOB_4_SPI3_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x06)   /**< \brief SPI1_MISO */
#define PIOB_4_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_4引脚复用时功能模式
 * @{
 */

#define PIOB_4_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOB_4_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOB_4_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOB_4_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOB_4_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOB_4_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOB_4_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOB_4_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOB_4引脚响应速率
 * @{
 */

#define PIOB_4_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOB_4_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOB_4_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_5引脚复用功能
 * @{
 */

#define PIOB_5_TIM3_CH2       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM3_CH2 */
#define PIOB_5_SPI1_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI1_MOSI */
#define PIOB_5_SPI3_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x06)   /**< \brief SPI3_MOSI */
#define PIOB_5_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)  /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_5引脚复用时功能模式
 * @{
 */

#define PIOB_5_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOB_5_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOB_5_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOB_5_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOB_5_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOB_5_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOB_5_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOB_5_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOB_5引脚响应速率
 * @{
 */

#define PIOB_5_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOB_5_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOB_5_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_6引脚复用功能
 * @{
 */

#define PIOB_6_TIM4_CH1      AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM4_CH1N */
#define PIOB_6_I2C1_SCL      AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C_SCL */
#define PIOB_6_UART1_TX      AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART1_TX */
#define PIOB_6_UART7_TX      AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART6_TX */
#define PIOB_6_GPIO          AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */


/** @} */

/**
 * \name PIOB_6引脚复用时功能模式
 * @{
 */

#define PIOB_6_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOB_6_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOB_6_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOB_6_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOB_6_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOB_6_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOB_6_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOB_6_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOB_6引脚响应速率
 * @{
 */

#define PIOB_6_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOB_6_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOB_6_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_7引脚复用功能
 * @{
 */

#define PIOB_7_TIM4_CH2       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM4_CH2 */
#define PIOB_7_I2C1_SDA       AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C_SDA */
#define PIOB_7_UART1_RX       AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART1_RX */
#define PIOB_7_UART7_RX       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART7_RX */
#define PIOB_7_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_7管脚复用时引脚复用时功能模式
 * @{
 */

#define PIOB_7_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOB_7_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式(默认) */
#define PIOB_7_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOB_7_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOB_7_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOB_7_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOB_7_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOB_7_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOB_7引脚响应速率
 * @{
 */

#define PIOB_7_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOB_7_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOB_7_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_8引脚复用功能
 * @{
 */
#define PIOB_8_TIM4_CH3       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM4_CH3 */
#define PIOB_8_I2C1_SCL       AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C_SCL */
#define PIOB_8_CPT1_OUT       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief I2C_SCL */
#define PIOB_8_CAN1_RX        AM_ZMF159_GPIO_FUNC_CODE(0x09)   /**< \brief I2C_SCL */
#define PIOB_8_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_8引脚复用时功能模式
 * @{
 */

#define PIOB_8_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOB_8_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOB_8_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOB_8_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOB_8_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOB_8_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOB_8_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOB_8_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOB_8引脚响应速率
 * @{
 */

#define PIOB_8_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz输出响应速率 */
#define PIOB_8_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOB_8_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_9引脚复用功能
 * @{
 */

#define PIOB_9_TIM4_CH4       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM4_CH4 */
#define PIOB_9_I2C1_SDA       AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C_SDA */
#define PIOB_9_SPI2_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_NSS */
#define PIOB_9_CPT2_OUT       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief CPT2_OUT */
#define PIOB_9_CAN1_TX        AM_ZMF159_GPIO_FUNC_CODE(0x09)   /**< \brief CAN1_TX */
#define PIOB_9_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_9引脚复用时功能模式
 * @{
 */

#define PIOB_9_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOB_9_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOB_9_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOB_9_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOB_9_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOB_9_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOB_9_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOB_9_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOB_9引脚响应速率
 * @{
 */

#define PIOB_9_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOB_9_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOB_9_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_10引脚复用功能
 * @{
 */

#define PIOB_10_TIM2_CH3      AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM2_CH3 */
#define PIOB_10_I2C2_SCL      AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C_SCL */
#define PIOB_10_SPI2_SCK      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_SCK */
#define PIOB_10_UART3_TX       AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART3_TX */
#define PIOB_10_GPIO          AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_10引脚复用时功能模式
 * @{
 */

#define PIOB_10_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOB_10_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOB_10_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOB_10_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOB_10_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOB_10_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOB_10_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOB_10_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOB_10引脚响应速率
 * @{
 */

#define PIOB_10_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOB_10_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOB_10_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_11引脚复用功能
 * @{
 */

#define PIOB_11_TIM2_CH4       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM2_CH4 */
#define PIOB_11_I2C2_SDA       AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C_SDA */
#define PIOB_11_UART_RX        AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief I2C_SDA */
#define PIOB_11_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_11引脚复用时功能模式
 * @{
 */

#define PIOB_11_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOB_11_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOB_11_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOB_11_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOB_11_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOB_11_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOB_11_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOB_11_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOB_11引脚响应速率
 * @{
 */

#define PIOB_11_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOB_11_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOB_11_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_12引脚复用功能
 * @{
 */

#define PIOB_12_TIM1_BKIN      AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM1_BKIN */
#define PIOB_12_SPI2_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_NSS */
#define PIOB_12_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_12引脚复用时功能模式
 * @{
 */

#define PIOB_12_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOB_12_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认）*/
#define PIOB_12_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOB_12_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOB_12_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOB_12_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOB_12_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOB_12_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOB_12引脚响应速率
 *
 * @{
 */

#define PIOB_12_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOB_12_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOB_12_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_13引脚复用功能
 * @{
 */

#define PIOB_13_TIM1_CH1N      AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM1_CH1N */
#define PIOB_13_SPI2_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_SCK */
#define PIOB_13_UART3_CTS      AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief I2C_SCL */
#define PIOB_13_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_13引脚复用时功能模式
 * @{
 */

#define PIOB_13_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOB_13_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOB_13_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOB_13_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOB_13_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOB_13_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOB_13_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOB_13_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOB_13引脚响应速率
 * @{
 */

#define PIOB_13_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOB_13_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOB_13_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_14引脚复用功能
 * @{
 */

#define PIOB_14_TIM1_CH2N      AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH2N */
#define PIOB_14_TIM8_CH2N      AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM8_CH2N */
#define PIOB_14_SPI2_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_SCK */
#define PIOB_14_UART_RTS       AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART_RTS */
#define PIOB_14_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_14引脚复用时功能模式
 * @{
 */

#define PIOB_14_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOB_14_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOB_14_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOB_14_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOB_14_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOB_14_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOB_14_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOB_14_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOB_14引脚响应速率
 * @{
 */

#define PIOB_14_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOB_14_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOB_14_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOB_15引脚复用功能
 * @{
 */

#define PIOB_15_TIM1_CH3       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH3N */
#define PIOB_15_TIM8_CH3       AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM8_CH3N */
#define PIOB_15_SPI2_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_MOSI */
#define PIOB_15_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOB_15引脚复用时功能模式
 * @{
 */

#define PIOB_15_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOB_15_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOB_15_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOB_15_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOB_15_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOB_15_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOB_15_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOB_15_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOB_15引脚响应速率
 * @{
 */

#define PIOB_15_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 10MHz输出响应速率 */
#define PIOB_15_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOB_15_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_0引脚复用功能
 * @{
 */
#define PIOC_0_I2C1_SCL         AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C1_SCL */
#define PIOC_0_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_0引脚复用时功能模式
 * @{
 */

#define PIOC_0_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOC_0_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOC_0_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOC_0_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOC_0_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOC_0_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOC_0_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOC_0_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOC_0引脚响应速率
 * @{
 */

#define PIOC_0_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOC_0_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOC_0_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/


/**
 * \name PIOC_1引脚复用功能
 * @{
 */
#define PIOC_1_I2C1_SDA         AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C1_SDA */
#define PIOC_1_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_13引脚复用时功能模式
 * @{
 */

#define PIOC_1_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOC_1_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOC_1_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOC_1_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOC_1_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOC_1_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOC_1_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOC_1_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOC_13引脚响应速率
 * @{
 */

#define PIOC_1_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOC_1_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOC_1_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/


/**
 * \name PIOC_2引脚复用功能
 * @{
 */
#define PIOC_2_I2C2_SCL         AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C2_SCL */
#define PIOC_2_SPI2_MISO        AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief I2C2_SCL */
#define PIOC_2_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_2引脚复用时功能模式
 * @{
 */

#define PIOC_2_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOC_2_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOC_2_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOC_2_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOC_2_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOC_2_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOC_2_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOC_2_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOC_2引脚响应速率
 * @{
 */

#define PIOC_2_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOC_2_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOC_2_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/


/**
 * \name PIOC_3引脚复用功能
 * @{
 */
#define PIOC_3_I2C2_SDA         AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C2_SDA */
#define PIOC_3_SPI2_MOSI        AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief I2C2_MOSI */
#define PIOC_3_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_3引脚复用时功能模式
 * @{
 */

#define PIOC_3_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOC_3_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOC_3_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOC_3_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOC_3_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOC_3_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOC_3_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOC_3_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOC_3引脚响应速率
 * @{
 */

#define PIOC_3_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOC_3_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOC_3_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_4引脚复用功能
 * @{
 */
#define PIOC_4_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_4引脚复用时功能模式
 * @{
 */

#define PIOC_4_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOC_4_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOC_4_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOC_4_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOC_4_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOC_4_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOC_4_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOC_4_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOC_4引脚响应速率
 * @{
 */

#define PIOC_4_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOC_4_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOC_4_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/** @} */

/******************************************************************************/


/**
 * \name PIOC_5引脚复用功能
 * @{
 */
#define PIOC_5_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_5引脚复用时功能模式
 * @{
 */

#define PIOC_5_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOC_5_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOC_5_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOC_5_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOC_5_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOC_5_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOC_5_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOC_5_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOC_5引脚响应速率
 * @{
 */

#define PIOC_5_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOC_5_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOC_5_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/



/**
 * \name PIOC_6引脚复用功能
 * @{
 */

#define PIOC_6_TIM3_CH1         AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM3_CH1 */
#define PIOC_6_TIM8_CH1         AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM8_CH1 */
#define PIOC_6_I2C1_SCL         AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief TIM3_CH1 */
#define PIOC_6_UART6_TX         AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART6_TX */
#define PIOC_6_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_5引脚复用时功能模式
 * @{
 */

#define PIOC_6_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOC_6_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOC_6_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOC_6_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOC_6_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOC_6_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOC_6_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOC_6_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOC_5引脚响应速率
 * @{
 */

#define PIOC_6_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOC_6_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOC_6_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/



/**
 * \name PIOC_5引脚复用功能
 * @{
 */

#define PIOC_7_TIM3_CH2         AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM3_CH1 */
#define PIOC_7_TIM8_CH2         AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM8_CH1 */
#define PIOC_7_I2C1_SDA         AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief TIM3_CH1 */
#define PIOC_7_UART6_RX         AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART6_RX */
#define PIOC_7_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_5引脚复用时功能模式
 * @{
 */

#define PIOC_7_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOC_7_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOC_7_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOC_7_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOC_7_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOC_7_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOC_7_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOC_7_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOC_5引脚响应速率
 * @{
 */

#define PIOC_7_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOC_7_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOC_7_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/



/**
 * \name PIOC_5引脚复用功能
 * @{
 */
#define PIOC_8_TIM3_CH3         AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM3_CH3 */
#define PIOC_8_TIM8_CH3         AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM8_CH3 */
#define PIOC_8_I2C2_SCL         AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C1_SCL */
#define PIOC_8_SDIO_D0          AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief SDIO_D0 */
#define PIOC_8_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_5引脚复用时功能模式
 * @{
 */

#define PIOC_8_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOC_8_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOC_8_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOC_8_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOC_8_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOC_8_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOC_8_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOC_8_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOC_5引脚响应速率
 * @{
 */

#define PIOC_8_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOC_8_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOC_8_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/



/**
 * \name PIOC_9引脚复用功能
 * @{
 */

#define PIOC_9_MCO2             AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief MCO2 */
#define PIOC_9_TIM3_CH4         AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM3_CH1 */
#define PIOC_9_TIM8_CH4         AM_ZMF159_GPIO_FUNC_CODE(0x03)   /**< \brief TIM8_CH1 */
#define PIOC_9_I2C2_SDA         AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief TIM3_CH1 */
#define PIOC_9_SDIO_D1          AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief SDIO_D1 */
#define PIOC_9_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_9引脚复用时功能模式
 * @{
 */

#define PIOC_9_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOC_9_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOC_9_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOC_9_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOC_9_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOC_9_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOC_9_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOC_9_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOC_9引脚响应速率
 * @{
 */

#define PIOC_9_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOC_9_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOC_9_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/



/**
 * \name PIOC_10引脚复用功能
 * @{
 */

#define PIOC_10_SPI3_SCK         AM_ZMF159_GPIO_FUNC_CODE(0x06)   /**< \brief SPI3_SCK */
#define PIOC_10_UART3_TX         AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART3_TX */
#define PIOC_10_UART4_TX         AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART4_TX */
#define PIOC_10_SDIO_D2          AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief SDIO_D2 */
#define PIOC_10_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_5引脚复用时功能模式
 * @{
 */

#define PIOC_10_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOC_10_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOC_10_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOC_10_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOC_10_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOC_10_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOC_10_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOC_10_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOC_5引脚响应速率
 * @{
 */

#define PIOC_10_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOC_10_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOC_10_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/



/**
 * \name PIOC_5引脚复用功能
 * @{
 */

#define PIOC_11_SPI3_MISO        AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief I2C2_MOSI */
#define PIOC_11_UART3_RX         AM_ZMF159_GPIO_FUNC_CODE(0x06)   /**< \brief UART3_RT */
#define PIOC_11_UART4_RX         AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART4_RX */
#define PIOC_11_SDIO_D3          AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief SDIO_D3 */
#define PIOC_11_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_5引脚复用时功能模式
 * @{
 */

#define PIOC_11_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOC_11_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOC_11_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOC_11_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOC_11_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOC_11_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOC_11_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOC_11_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOC_5引脚响应速率
 * @{
 */

#define PIOC_11_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOC_11_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOC_11_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/



/**
 * \name PIOC_5引脚复用功能
 * @{
 */

#define PIOC_12_SPI3_MOSI        AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief I2C2_MOSI */
#define PIOC_12_UART5_TX         AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART5_TX */
#define PIOC_12_SDIO_CK          AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief SDIO_CK */
#define PIOC_12_GPIO             AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_5引脚复用时功能模式
 * @{
 */

#define PIOC_12_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOC_12_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOC_12_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOC_12_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOC_12_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOC_12_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOC_12_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOC_12_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOC_5引脚响应速率
 * @{
 */

#define PIOC_12_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOC_12_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOC_12_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_13引脚复用功能
 * @{
 */
#define PIOC_13_GPIO            AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_13引脚复用时功能模式
 * @{
 */

#define PIOC_13_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOC_13_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOC_13_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOC_13_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOC_13_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOC_13_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOC_13_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOC_13_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOC_13引脚响应速率
 * @{
 */

#define PIOC_13_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOC_13_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOC_13_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_14引脚复用功能
 * @{
 */
#define PIOC_14_GPIO            AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_14引脚复用时功能模式
 * @{
 */

#define PIOC_14_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOC_14_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOC_14_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOC_14_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOC_14_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOC_14_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOC_14_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOC_14_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOC_14引脚响应速率
 * @{
 */

#define PIOC_14_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOC_14_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOC_14_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOC_15引脚复用功能
 * @{
 */
#define PIOC_15_GPIO            AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOC_15引脚复用时功能模式
 * @{
 */

#define PIOC_15_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOC_15_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOC_15_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOC_15_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOC_15_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOC_15_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOC_15_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOC_15_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOC_15引脚响应速率
 * @{
 */

#define PIOC_15_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOC_15_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOC_15_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOD_0引脚复用功能
 * @{
 */
#define PIOD_0_UART8_TX       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART8_TX */
#define PIOD_0_CAN1_RX        AM_ZMF159_GPIO_FUNC_CODE(0x09)   /**< \brief CAN1_RX */
#define PIOD_0_FMC_DA         AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief CAN1_RX */
#define PIOD_0_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_0引脚复用时功能模式
 * @{
 */

#define PIOD_0_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOD_0_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOD_0_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOD_0_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOD_0_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOD_0_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOD_0_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOD_0_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_0引脚响应速率
 * @{
 */

#define PIOD_0_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOD_0_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOD_0_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOD_1引脚复用功能
 * @{
 */

#define PIOD_1_UART8_RX       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART8_RX */
#define PIOD_1_CAN1_TX        AM_ZMF159_GPIO_FUNC_CODE(0x09)   /**< \brief CAN1_TX */
#define PIOD_1_FMC_DA3        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA3 */
#define PIOD_1_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_1引脚复用时功能模式
 * @{
 */

#define PIOD_1_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOD_1_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOD_1_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOD_1_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOD_1_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOD_1_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOD_1_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOD_1_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_1引脚响应速率
 * @{
 */

#define PIOD_1_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOD_1_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOD_1_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOD_2引脚复用功能
 * @{
 */

#define PIOD_2_TIM3_ETR       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM3_ETR */
#define PIOD_2_UART5_RX       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART5_RX */
#define PIOD_2_SDIO_CMD       AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief SDIO_CMD */
#define PIOD_2_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_2引脚复用时功能模式
 * @{
 */

#define PIOD_2_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOD_2_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOD_2_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOD_2_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOD_2_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOD_2_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOD_2_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOD_2_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_2引脚响应速率
 * @{
 */

#define PIOD_2_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOD_2_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOD_2_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOD_3引脚复用功能
 * @{
 */

#define PIOD_3_SPI2_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_SCK */
#define PIOD_3_UART2_CTS      AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART2_CTS */
#define PIOD_3_FMC_CLK        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_CLK */
#define PIOD_3_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_3引脚复用时功能模式
 * @{
 */

#define PIOD_3_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOD_3_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOD_3_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOD_3_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOD_3_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOD_3_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOD_3_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOD_3_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOD_3_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOD_3_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOD_3_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * \name PIOD_3引脚复用功能
 * @{
 */

#define PIOD_4_SPI3_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_SCK */
#define PIOD_4_UART2_RTS      AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART2_CTS */
#define PIOD_4_FMC_NOE        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_NOE */
#define PIOD_4_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_3引脚复用时功能模式
 * @{
 */

#define PIOD_4_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOD_4_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOD_4_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOD_4_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOD_4_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOD_4_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOD_4_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOD_4_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOD_4_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOD_4_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOD_4_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOD_3引脚复用功能
 * @{
 */

#define PIOD_5_SPI3_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_SCK */
#define PIOD_5_UART2_TX       AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART2_CTS */
#define PIOD_5_FMC_NWE        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_NWE */
#define PIOD_5_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_3引脚复用时功能模式
 * @{
 */

#define PIOD_5_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOD_5_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOD_5_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOD_5_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOD_5_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOD_5_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOD_5_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOD_5_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOD_5_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOD_5_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOD_5_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOD_3引脚复用功能
 * @{
 */

#define PIOD_6_SPI3_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_SCK */
#define PIOD_6_UART2_RX       AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART2_CTS */
#define PIOD_6_FMC_NWAIT      AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_NWAIT */
#define PIOD_6_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_3引脚复用时功能模式
 * @{
 */

#define PIOD_6_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOD_6_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOD_6_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOD_6_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOD_6_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOD_6_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOD_6_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOD_6_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOD_6_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOD_6_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOD_6_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOD_3引脚复用功能
 * @{
 */

#define PIOD_7_SPI3_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI3_NSS */
#define PIOD_7_FMC_NE1        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_NE1 */
#define PIOD_7_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_3引脚复用时功能模式
 * @{
 */

#define PIOD_7_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOD_7_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOD_7_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOD_7_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOD_7_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOD_7_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOD_7_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOD_7_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOD_7_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOD_7_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOD_7_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOD_3引脚复用功能
 * @{
 */

#define PIOD_8_UART3_TX       AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART3_TX*/
#define PIOD_8_FMC_DA13       AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA13 */
#define PIOD_8_UART3_RX       AM_ZMF159_GPIO_FUNC_CODE(0x0D)   /**< \brief UART3_RX */
#define PIOD_8_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_3引脚复用时功能模式
 * @{
 */

#define PIOD_8_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOD_8_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOD_8_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOD_8_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOD_8_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOD_8_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOD_8_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOD_8_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOD_8_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOD_8_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOD_8_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOD_9引脚复用功能
 * @{
 */

#define PIOD_9_UART3_RX       AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART3_RX */
#define PIOD_9_FMC_DA14       AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA14 */
#define PIOD_9_UART3_TX       AM_ZMF159_GPIO_FUNC_CODE(0x0D)   /**< \brief UART3_TX */
#define PIOD_9_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_9引脚复用时功能模式
 * @{
 */

#define PIOD_9_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOD_9_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOD_9_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOD_9_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOD_9_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOD_9_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOD_9_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOD_9_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_9引脚响应速率
 * @{
 */

#define PIOD_9_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOD_9_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOD_9_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOD_10引脚复用功能
 * @{
 */

#define PIOD_10_FMC_DA15       AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA15 */
#define PIOD_10_I2C1_SCL       AM_ZMF159_GPIO_FUNC_CODE(0x0D)   /**< \brief I2C1_SCL */
#define PIOD_10_I2C1_SDA       AM_ZMF159_GPIO_FUNC_CODE(0x0E)   /**< \brief I2C1_SDA */
#define PIOD_10_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_3引脚复用时功能模式
 * @{
 */

#define PIOD_10_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOD_10_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOD_10_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOD_10_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOD_10_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOD_10_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOD_10_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOD_10_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOD_10_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOD_10_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOD_10_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOD_3引脚复用功能
 * @{
 */

#define PIOD_11_UART3_CTS      AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART3_CTS */
#define PIOD_11_FMC_A16        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_A16 */
#define PIOD_11_I2C1_SDA       AM_ZMF159_GPIO_FUNC_CODE(0x0D)   /**< \brief I2C1_SDA */
#define PIOD_11_I2C1_SCL       AM_ZMF159_GPIO_FUNC_CODE(0x0E)   /**< \brief I2C1_SCL */
#define PIOD_11_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_3引脚复用时功能模式
 * @{
 */

#define PIOD_11_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOD_11_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOD_11_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOD_11_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOD_11_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOD_11_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOD_11_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOD_11_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_11引脚响应速率
 * @{
 */

#define PIOD_11_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOD_11_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOD_11_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOD_12引脚复用功能
 * @{
 */

#define PIOD_12_TIM4_CH1       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM4_CH1 */
#define PIOD_12_SPI3_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x06)   /**< \brief SPI2_SCK */
#define PIOD_12_UART3_RTS      AM_ZMF159_GPIO_FUNC_CODE(0x07)   /**< \brief UART3_RTS */
#define PIOD_12_FMC_A17        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_A17 */
#define PIOD_12_SPI3_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x0D)   /**< \brief SPI3_NSS */
#define PIOD_12_SPI3_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x0E)   /**< \brief SPI3_MOSI */
#define PIOD_12_SPI3_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief SPI3_MISO */
#define PIOD_12_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_3引脚复用时功能模式
 * @{
 */

#define PIOD_12_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOD_12_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOD_12_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOD_12_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOD_12_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOD_12_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOD_12_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOD_12_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOD_12_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOD_12_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOD_12_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOD_3引脚复用功能
 * @{
 */

#define PIOD_13_TIM4_CH2       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM4_CH1 */
#define PIOD_13_SPI3_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x06)   /**< \brief SPI2_SCK */
#define PIOD_13_FMC_A18        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_A17 */
#define PIOD_13_SPI3_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x0D)   /**< \brief SPI3_SCK */
#define PIOD_13_SPI3_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x0E)   /**< \brief SPI3_NSS */
#define PIOD_13_SPI3_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief SPI3_MOSI */
#define PIOD_13_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_3引脚复用时功能模式
 * @{
 */

#define PIOD_13_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOD_13_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOD_13_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOD_13_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOD_13_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOD_13_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOD_13_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOD_13_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOD_13_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOD_13_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOD_13_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOD_3引脚复用功能
 * @{
 */

#define PIOD_14_TIM4_CH3       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM4_CH3 */
#define PIOD_14_SPI3_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x06)   /**< \brief SPI3_SCK */
#define PIOD_14_FMC_DA0        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_A17 */
#define PIOD_14_SPI3_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x0D)   /**< \brief SPI3_MISO */
#define PIOD_14_SPI3_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x0E)   /**< \brief SPI3_SCK */
#define PIOD_14_SPI3_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief SPI3_NSS */
#define PIOD_14_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_3引脚复用时功能模式
 * @{
 */

#define PIOD_14_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOD_14_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOD_14_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOD_14_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOD_14_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOD_14_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOD_14_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOD_14_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOD_14_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOD_14_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOD_14_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOD_15引脚复用功能
 * @{
 */

#define PIOD_15_TIM4_CH4       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM4_CH4 */
#define PIOD_15_SPI3_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x06)   /**< \brief SPI3_NSS */
#define PIOD_15_FMC_DA1        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA1 */
#define PIOD_15_SPI3_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x0D)   /**< \brief SPI3_MOSI */
#define PIOD_15_SPI3_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x0E)   /**< \brief SPI3_MISO */
#define PIOD_15_SPI3_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief SPI3_SCK */
#define PIOD_15_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOD_15引脚复用时功能模式
 * @{
 */

#define PIOD_15_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOD_15_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOD_15_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOD_15_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOD_15_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOD_15_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOD_15_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOD_15_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_15引脚响应速率
 * @{
 */

#define PIOD_15_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOD_15_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOD_15_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0引脚复用功能
 * @{
 */

#define PIOE_0_TIM4_ETR       AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TIM4_ETR */
#define PIOE_0_UART8_RX       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART8_RX */
#define PIOE_0_FMC_NBL0       AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_NBL0 */
#define PIOE_0_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0引脚复用时功能模式
 * @{
 */

#define PIOE_0_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOE_0_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOE_0_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOE_0_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOE_0_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOE_0_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOE_0_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOE_0_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOE_0引脚响应速率
 * @{
 */

#define PIOE_0_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOE_0_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOE_0_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_1引脚复用功能
 * @{
 */
#define PIOE_1_UART8_TX       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART8_TX */
#define PIOE_1_FMC_NBL1       AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_NBL1 */
#define PIOE_1_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_1引脚复用时功能模式
 * @{
 */

#define PIOE_1_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOE_1_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOE_1_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOE_1_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOE_1_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOE_1_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOE_1_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOE_1_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOE_1引脚响应速率
 * @{
 */

#define PIOE_1_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOE_1_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOE_1_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_2引脚复用功能
 * @{
 */

#define PIOE_2_TRACECLK       AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief TRACECLK */
#define PIOE_2_SPI2_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_SCK */
#define PIOE_2_FMC_A23        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_A23 */
#define PIOE_2_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0引脚复用时功能模式
 * @{
 */

#define PIOE_2_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOE_2_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOE_2_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOE_2_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOE_2_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOE_2_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOE_2_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOE_2_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOE_2_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOE_2_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOE_2_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0引脚复用功能
 * @{
 */

#define PIOE_3_TRACED0        AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief TRACED0 */
#define PIOE_3_SPI2_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_NSS */
#define PIOE_3_FMC_A19         AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_A19 */
#define PIOE_3_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0引脚复用时功能模式
 * @{
 */

#define PIOE_3_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOE_3_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOE_3_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOE_3_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOE_3_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOE_3_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOE_3_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOE_3_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOE_3_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOE_3_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOE_3_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_4引脚复用功能
 * @{
 */

#define PIOE_4_TRACED1        AM_ZMF159_GPIO_FUNC_CODE(0x02)   /**< \brief TRACED1 */
#define PIOE_4_SPI2_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_NSS */
#define PIOE_4_FMC_A20        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_A20 */
#define PIOE_4_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0引脚复用时功能模式
 * @{
 */

#define PIOE_4_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOE_4_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOE_4_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOE_4_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOE_4_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOE_4_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOE_4_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOE_4_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOE_4_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOE_4_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOE_4_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0引脚复用功能
 * @{
 */

#define PIOE_5_TRACED2        AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief TRACED1 */
#define PIOE_5_I2C2_SCL       AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C2_SCL */
#define PIOE_5_SPI2_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_MISO */
#define PIOE_5_FMC_A21        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_A21 */
#define PIOE_5_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0引脚复用时功能模式
 * @{
 */

#define PIOE_5_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOE_5_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOE_5_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOE_5_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOE_5_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOE_5_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOE_5_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOE_5_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOE_5_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOE_5_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOE_5_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0引脚复用功能
 * @{
 */

#define PIOE_6_TRACED3        AM_ZMF159_GPIO_FUNC_CODE(0x00)   /**< \brief TRACED3 */
#define PIOE_6_I2C2_SDA       AM_ZMF159_GPIO_FUNC_CODE(0x04)   /**< \brief I2C2_SDA */
#define PIOE_6_SPI2_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_MOSI */
#define PIOE_6_FMC_A22        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_A22 */
#define PIOE_6_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0引脚复用时功能模式
 * @{
 */

#define PIOE_6_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOE_6_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOE_6_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOE_6_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOE_6_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOE_6_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOE_6_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOE_6_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOE_6_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOE_6_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOE_6_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0引脚复用功能
 * @{
 */

#define PIOE_7_TIM1_ETR       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM4_CH4 */
#define PIOE_7_UART7_RX       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART7_RX */
#define PIOE_7_FMC_DA4        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA4 */
#define PIOE_7_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0引脚复用时功能模式
 * @{
 */

#define PIOE_7_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOE_7_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOE_7_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOE_7_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOE_7_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOE_7_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOE_7_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOE_7_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOE_7_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOE_7_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOE_7_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0引脚复用功能
 * @{
 */

#define PIOE_8_TIM1_CH1N      AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH1N */
#define PIOE_8_UART7_TX       AM_ZMF159_GPIO_FUNC_CODE(0x08)   /**< \brief UART7_TX */
#define PIOE_8_FMC_DA5        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA5 */
#define PIOE_8_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0引脚复用时功能模式
 * @{
 */

#define PIOE_8_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOE_8_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOE_8_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOE_8_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOE_8_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOE_8_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOE_8_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOE_8_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOE_8_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOE_8_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOE_8_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0引脚复用功能
 * @{
 */

#define PIOE_9_TIM1_CH1       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH1 */
#define PIOE_9_FMC_DA6        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA6 */
#define PIOE_9_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0引脚复用时功能模式
 * @{
 */

#define PIOE_9_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOE_9_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOE_9_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOE_9_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOE_9_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOE_9_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOE_9_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOE_9_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOE_9_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOE_9_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOE_9_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0引脚复用功能
 * @{
 */

#define PIOE_10_FMC_DA7        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA7 */
#define PIOE_10_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0引脚复用时功能模式
 * @{
 */

#define PIOE_10_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOE_10_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOE_10_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOE_10_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOE_10_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOE_10_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOE_10_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOE_10_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOE_10_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOE_10_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOE_10_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0引脚复用功能
 * @{
 */

#define PIOE_11_TIM1_CH2       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH2 */
#define PIOE_11_SPI1_NSS       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI1_NSS */
#define PIOE_11_FMC_DA8        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA8 */
#define PIOE_11_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0引脚复用时功能模式
 * @{
 */

#define PIOE_11_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOE_11_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOE_11_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOE_11_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOE_11_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOE_11_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOE_11_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOE_11_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOE_11_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOE_11_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOE_11_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0引脚复用功能
 * @{
 */

#define PIOE_12_TIM1_CH3N      AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH3N */
#define PIOE_12_SPI1_SCK       AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI1_SCK */
#define PIOE_12_FMC_DA9        AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA9 */
#define PIOE_12_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0引脚复用时功能模式
 * @{
 */

#define PIOE_12_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOE_12_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOE_12_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOE_12_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOE_12_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOE_12_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOE_12_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOE_12_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOE_12_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOE_12_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOE_12_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0引脚复用功能
 * @{
 */

#define PIOE_13_TIM1_CH3       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH3 */
#define PIOE_13_SPI1_MISO      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI2_NSS */
#define PIOE_13_FMC_DA10       AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA10 */
#define PIOE_13_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0引脚复用时功能模式
 * @{
 */

#define PIOE_13_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOE_13_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOE_13_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOE_13_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOE_13_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOE_13_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOE_13_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOE_13_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOE_13_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOE_13_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOE_13_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0引脚复用功能
 * @{
 */

#define PIOE_14_TIM1_CH4       AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_CH4 */
#define PIOE_14_SPI1_MOSI      AM_ZMF159_GPIO_FUNC_CODE(0x05)   /**< \brief SPI1_MOSI */
#define PIOE_14_FMC_DA11       AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA11 */
#define PIOE_14_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0引脚复用时功能模式
 * @{
 */

#define PIOE_14_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOE_14_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOE_14_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOE_14_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOE_14_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOE_14_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOE_14_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOE_14_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOE_14_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOE_14_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOE_14_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/
/**
 * \name PIOE_0引脚复用功能
 * @{
 */

#define PIOE_15_TIM1_BKIN      AM_ZMF159_GPIO_FUNC_CODE(0x01)   /**< \brief TIM1_BKIN */
#define PIOE_15_FMC_DA12       AM_ZMF159_GPIO_FUNC_CODE(0x0C)   /**< \brief FMC_DA12 */
#define PIOE_15_GPIO           AM_ZMF159_GPIO_FUNC_CODE(0x0F)   /**< \brief GPIO */

/** @} */

/**
 * \name PIOE_0引脚复用时功能模式
 * @{
 */

#define PIOE_15_AIN            AM_ZMF159_GPIO_MODE_CODE(0x0)   /**< \brief 模拟模式 */
#define PIOE_15_INPUT_FLOAT    AM_ZMF159_GPIO_MODE_CODE(0x1)   /**< \brief 输入浮空模式（默认） */
#define PIOE_15_INPUT_PD       AM_ZMF159_GPIO_MODE_CODE(0x2)   /**< \brief 输入下拉模式 */
#define PIOE_15_INPUT_PU       AM_ZMF159_GPIO_MODE_CODE(0x3)   /**< \brief 输入上拉模式 */
#define PIOE_15_OUT_PP         AM_ZMF159_GPIO_MODE_CODE(0x4)   /**< \brief 通用推挽输出模式 */
#define PIOE_15_OUT_OD         AM_ZMF159_GPIO_MODE_CODE(0x5)   /**< \brief 通用开漏输出模式 */
#define PIOE_15_AF_PP          AM_ZMF159_GPIO_MODE_CODE(0x6)   /**< \brief 复用推挽输出模式 */
#define PIOE_15_AF_OD          AM_ZMF159_GPIO_MODE_CODE(0x7)   /**< \brief 复用开漏输出模式 */

/** @} */

/**
 * \name PIOD_3引脚响应速率
 * @{
 */

#define PIOE_15_SPEED_10MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x01)   /**< \brief 10MHz输出响应速率 */
#define PIOE_15_SPEED_20MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x02)   /**< \brief 20MHz输出响应速率 */
#define PIOE_15_SPEED_50MHz    AM_ZMF159_GPIO_OUTRES_RATE_CODE(0x03)   /**< \brief 50MHz输出响应速率 */

/** @} */

/******************************************************************************/

/**
 * @}
 */

/**
 * @}if_zmf159_pin
 */

#ifdef __cplusplus
}
#endif

#endif /* __ZMF159_PIN_H */

/* end of file */
