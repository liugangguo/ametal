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
 * \brief ZMF159 DMA 通道编号定义
 *
 * \internal
 * \par Modification History
 *
 * - 1.00 17-08-23  lqy, first implementation
 *
 * \endinternal
 */

#ifndef __ZMF159_DMA_CHAN_H
#define __ZMF159_DMA_CHAN_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup zmf159_if_dma_chan
 * \copydoc zmf159_dma_chan.h
 * @{
 */

/**
 * \name ZMF159 DMA 通道编号
 * @{
 */
#define DMA1_CHAN_1                0               /**< \brief DMA1通道1 */
#define DMA1_CHAN_2                1               /**< \brief DMA1通道2 */
#define DMA1_CHAN_3                2               /**< \brief DMA1通道3 */
#define DMA1_CHAN_4                3               /**< \brief DMA1通道4 */
#define DMA1_CHAN_5                4               /**< \brief DMA1通道5 */
#define DMA1_CHAN_6                5               /**< \brief DMA1通道6 */
#define DMA1_CHAN_7                6               /**< \brief DMA1通道7 */

#define DMA2_CHAN_1                0               /**< \brief DMA2通道1 */
#define DMA2_CHAN_2                1               /**< \brief DMA2通道2 */
#define DMA2_CHAN_3                2               /**< \brief DMA2通道3 */
#define DMA2_CHAN_4                3               /**< \brief DMA2通道4 */
#define DMA2_CHAN_5                4               /**< \brief DMA2通道5 */

/** @} */

/**
 * \name 外设的DMA请求通道
 * \anchor dma_request_src
 * @{
 */

#define DMA_CHAN_ADC1           DMA1_CHAN_1     /**< \brief ADC      请求 */

#define DMA_CHAN_SPI1_RX        DMA1_CHAN_2     /**< \brief SPI1 RX   请求 */
#define DMA_CHAN_SPI1_TX        DMA1_CHAN_3     /**< \brief SPI1 TX   请求 */
#define DMA_CHAN_SPI2_RX        DMA1_CHAN_4     /**< \brief SPI2 RX   请求 */
#define DMA_CHAN_SPI2_TX        DMA1_CHAN_5     /**< \brief SPI2 TX   请求 */
#define DMA_CHAN_SPI3_RX        DMA2_CHAN_1     /**< \brief SPI3 RX   请求 */
#define DMA_CHAN_SPI3_TX        DMA2_CHAN_2     /**< \brief SPI3 TX   请求 */

#define DMA_CHAN_UART3_TX       DMA1_CHAN_2     /**< \brief UART1 TX  请求 */
#define DMA_CHAN_UART3_RX       DMA1_CHAN_3     /**< \brief UART1 RX  请求 */
#define DMA_CHAN_UART1_TX       DMA1_CHAN_4     /**< \brief UART2 TX  请求 */
#define DMA_CHAN_UART1_RX       DMA1_CHAN_5     /**< \brief UART2 RX  请求 */
#define DMA_CHAN_UART2_RX       DMA1_CHAN_6     /**< \brief UART2 TX  请求 */
#define DMA_CHAN_UART2_TX       DMA1_CHAN_7     /**< \brief UART2 RX  请求 */
#define DMA_CHAN_UART5_RX       DMA2_CHAN_1     /**< \brief UART5 RX  请求 */
#define DMA_CHAN_UART5_TX       DMA2_CHAN_2     /**< \brief UART5 TX  请求 */
#define DMA_CHAN_UART4_RX       DMA2_CHAN_3     /**< \brief UART4 RX  请求 */
#define DMA_CHAN_UART4_TX       DMA2_CHAN_5     /**< \brief UART4 TX  请求 */

#define DMA_CHAN_I2C2_TX        DMA1_CHAN_4     /**< \brief I2C TX   请求 */
#define DMA_CHAN_I2C2_RX        DMA1_CHAN_5     /**< \brief I2C RX   请求 */
#define DMA_CHAN_I2C1_TX        DMA1_CHAN_6     /**< \brief I2C TX   请求 */
#define DMA_CHAN_I2C1_RX        DMA1_CHAN_7     /**< \brief I2C RX   请求 */

#define DMA_CHAN_SDIO           DMA2_CHAN_4     /**< \brief SDIO   请求 */

#define DMA_CHAN_TIM1_CH1       DMA1_CHAN_2     /**< \brief TIM1 CH1 请求 */
#define DMA_CHAN_TIM1_CH2       DMA1_CHAN_3     /**< \brief TIM1 CH2 请求 */
#define DMA_CHAN_TIM1_CH4       DMA1_CHAN_4     /**< \brief TIM1 CH4 请求 */
#define DMA_CHAN_TIM1_TRIG      DMA1_CHAN_4     /**< \brief TIM1 TRIG请求 */
#define DMA_CHAN_TIM1_COM       DMA1_CHAN_4     /**< \brief TIM1 COM 请求 */
#define DMA_CHAN_TIM1_UP        DMA1_CHAN_5     /**< \brief TIM1 UP  请求 */
#define DMA_CHAN_TIM1_CH3       DMA1_CHAN_6     /**< \brief TIM1 CH3 请求 */

#define DMA_CHAN_TIM2_CH3       DMA1_CHAN_1     /**< \brief TIM2 CH3 请求 */
#define DMA_CHAN_TIM2_UP        DMA1_CHAN_2     /**< \brief TIM2 UP  请求 */
#define DMA_CHAN_TIM2_CH1       DMA1_CHAN_5     /**< \brief TIM2 CH1 请求 */
#define DMA_CHAN_TIM2_CH2       DMA1_CHAN_7     /**< \brief TIM2 CH2 请求 */
#define DMA_CHAN_TIM2_CH4       DMA1_CHAN_7     /**< \brief TIM2 CH4 请求 */

#define DMA_CHAN_TIM3_CH3       DMA1_CHAN_2     /**< \brief TIM3 CH3 请求 */
#define DMA_CHAN_TIM3_CH4       DMA1_CHAN_3     /**< \brief TIM3 CH4 请求 */
#define DMA_CHAN_TIM3_UP        DMA1_CHAN_3     /**< \brief TIM3 UP  请求 */
#define DMA_CHAN_TIM3_CH1       DMA1_CHAN_6     /**< \brief TIM3 CH1 请求 */
#define DMA_CHAN_TIM3_TRIG      DMA1_CHAN_6     /**< \brief TIM3 TRIG请求 */

#define DMA_CHAN_TIM4_CH1       DMA1_CHAN_1     /**< \brief TIM4 CH1 请求 */
#define DMA_CHAN_TIM4_CH2       DMA1_CHAN_4     /**< \brief TIM4 CH2请求 */
#define DMA_CHAN_TIM4_CH3       DMA1_CHAN_5     /**< \brief TIM4 CH3请求 */
#define DMA_CHAN_TIM4_UP        DMA1_CHAN_7     /**< \brief TIM4 UP请求 */

#define DMA_CHAN_TIM5_CH3       DMA2_CHAN_2     /**< \brief TIM5 CH3 请求 */
#define DMA_CHAN_TIM5_CH4       DMA2_CHAN_1     /**< \brief TIM5 CH4 请求 */
#define DMA_CHAN_TIM5_UP        DMA2_CHAN_2     /**< \brief TIM5 UP  请求 */
#define DMA_CHAN_TIM5_CH1       DMA2_CHAN_5     /**< \brief TIM5 CH1 请求 */
#define DMA_CHAN_TIM5_TRIG      DMA2_CHAN_1     /**< \brief TIM5 TRIG请求 */

#define DMA_CHAN_TIM6_UP        DMA2_CHAN_3     /**< \brief TIM6 UP  请求 */

#define DMA_CHAN_TIM7_UP        DMA2_CHAN_4     /**< \brief TIM7 UP  请求 */

#define DMA_CHAN_TIM8_CH1       DMA2_CHAN_3     /**< \brief TIM8 CH1 请求 */
#define DMA_CHAN_TIM8_CH2       DMA2_CHAN_5     /**< \brief TIM8 CH2 请求 */
#define DMA_CHAN_TIM8_CH4       DMA2_CHAN_2     /**< \brief TIM8 CH4 请求 */
#define DMA_CHAN_TIM8_TRIG      DMA2_CHAN_2     /**< \brief TIM8 TRIG请求 */
#define DMA_CHAN_TIM8_COM       DMA2_CHAN_2     /**< \brief TIM8 COM 请求 */
#define DMA_CHAN_TIM8_UP        DMA2_CHAN_1     /**< \brief TIM8 UP  请求 */
#define DMA_CHAN_TIM8_CH3       DMA2_CHAN_1     /**< \brief TIM8 CH3 请求 */


/** @} */

/**
 * @} zmf159_if_dma_chan
 */

#ifdef __cplusplus
}
#endif

#endif /* __ZMF159_DMA_CHAN_H */

/* end of file */
