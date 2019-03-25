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
 * \brief ZMF159 时钟ID定义
 *
 * \internal
 * \par Modification History
 * - 1.00 19-02-21  ipk, first implementation
 * \endinternal
 */

#ifndef __ZMF159_CLK_H
#define __ZMF159_CLK_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup zmf159_if_clockid
 * \copydoc zmf159_clk.h
 * @{
 */

/**
 * \name 系统或外设的时钟ID
 * \anchor grp_clk_id
 * @{
 */

/* APB1外设时钟 */
#define CLK_TIM2    (0x01ul << 8 | 0ul)   /**< \brief TIM2定时器 时钟 */
#define CLK_TIM3    (0x01ul << 8 | 1ul)   /**< \brief TIM3定时器 时钟 */
#define CLK_TIM4    (0x01ul << 8 | 2ul)   /**< \brief TIM3定时器 时钟 */
#define CLK_TIM5    (0x01ul << 8 | 3ul)   /**< \brief TIM4定时器 时钟 */
#define CLK_TIM6    (0x01ul << 8 | 4ul)   /**< \brief TIM5定时器 时钟 */
#define CLK_TIM7    (0x01ul << 8 | 5ul)   /**< \brief TIM6定时器 时钟 */
#define CLK_WWDG    (0x01ul << 8 | 11ul)  /**< \brief WWDG窗口看门狗 时钟 */
#define CLK_SPI2    (0x01ul << 8 | 14ul)  /**< \brief SPI2 时钟 */
#define CLK_SPI3    (0x01ul << 8 | 14ul)  /**< \brief SPI3 时钟 */
#define CLK_UART2   (0x01ul << 8 | 17ul)  /**< \brief UART2 时钟 */
#define CLK_UART3   (0x01ul << 8 | 18ul)  /**< \brief UART3 时钟 */
#define CLK_UART4   (0x01ul << 8 | 19ul)  /**< \brief UART4 时钟 */
#define CLK_UART5   (0x01ul << 8 | 20ul)  /**< \brief UART5 时钟 */
#define CLK_I2C1    (0x01ul << 8 | 21ul)  /**< \brief I2C1 时钟 */
#define CLK_I2C2    (0x01ul << 8 | 22ul)  /**< \brief I2C2 时钟 */
#define CLK_CRS     (0x01ul << 8 | 24ul)  /**< \brief CRS 时钟 */
#define CLK_CAN     (0x01ul << 8 | 25ul)  /**< \brief CAN 时钟 */
#define CLK_BKP     (0x01ul << 8 | 27ul)  /**< \brief BKP 时钟 */
#define CLK_PWR     (0x01ul << 8 | 28ul)  /**< \brief 电源接口 时钟 */
#define CLK_UART7   (0x01ul << 8 | 30ul)  /**< \brief UART7 时钟 */
#define CLK_UART8   (0x01ul << 8 | 31ul)  /**< \brief UART8 时钟 */

/* APB2外设时钟 */
#define CLK_TIM1    (0x02ul << 8 | 0ul)  /**< \brief TIM1定时器 时钟 */
#define CLK_TIM8    (0x02ul << 8 | 1ul)  /**< \brief TIM8定时器 时钟 */
#define CLK_UART1   (0x02ul << 8 | 4ul)  /**< \brief UART1 时钟 */
#define CLK_UART6   (0x02ul << 8 | 5ul)  /**< \brief UART6 时钟 */
#define CLK_ADC1    (0x02ul << 8 | 8ul)  /**< \brief ADC1接口 时钟 */
#define CLK_SPI1    (0x02ul << 8 | 12ul) /**< \brief SPI1 时钟 */
#define CLK_SYSCFG  (0x02ul << 8 | 14ul) /**< \brief SYSCFG 时钟 */
#define CLK_COMP    (0x02ul << 8 | 15ul) /**< \brief COMP 时钟 */

/* AHB1外设时钟 */
#define CLK_IOPA    (0x03ul << 8 | 0ul)   /**< \brief IOPA 时钟 */
#define CLK_IOPB    (0x03ul << 8 | 1ul)   /**< \brief IOPB 时钟 */
#define CLK_IOPC    (0x03ul << 8 | 2ul)   /**< \brief IOPC 时钟 */
#define CLK_IOPD    (0x03ul << 8 | 3ul)   /**< \brief IOPD 时钟 */
#define CLK_IOPE    (0x03ul << 8 | 4ul)   /**< \brief IOPE 时钟 */
#define CLK_SDIO    (0x03ul << 8 | 10ul)  /**< \brief SDIO 时钟 */
#define CLK_CRC     (0x03ul << 8 | 12ul)  /**< \brief CRC 时钟 */
#define CLK_FLASH   (0x03ul << 8 | 13ul)  /**< \brief FLASH 时钟 */
#define CLK_SRAM    (0x03ul << 8 | 14ul)  /**< \brief SRAM 时钟 */
#define CLK_DMA1    (0x03ul << 8 | 21ul)  /**< \brief DMA1 时钟 */
#define CLK_DMA2    (0x03ul << 8 | 22ul)  /**< \brief DMA2 时钟 */

/* 其他时钟 */
#define CLK_PLLIN  (0x04ul << 8 | 0ul)  /**< \brief PLL输入 时钟 */
#define CLK_PLLOUT (0x04ul << 8 | 1ul)  /**< \brief PLL输出 时钟 */
#define CLK_AHB1   (0x04ul << 8 | 2ul)  /**< \brief AHB1 时钟 */
#define CLK_APB1   (0x04ul << 8 | 3ul)  /**< \brief APB1 时钟 */
#define CLK_APB2   (0x04ul << 8 | 4ul)  /**< \brief APB2 时钟 */
#define CLK_HSEOSC (0x04ul << 8 | 5ul)  /**< \brief 外部晶振 时钟 */
#define CLK_LSEOSC (0x04ul << 8 | 6ul)  /**< \brief 外部晶振 时钟 */
#define CLK_LSI    (0x04ul << 8 | 7ul)  /**< \brief LSI 时钟 */
#define CLK_HSI    (0x04ul << 8 | 8ul)  /**< \brief HSI 时钟 */
#define CLK_USB    (0x04ul << 8 | 9ul)  /**< \brief USB 时钟 */

/* 非总线时钟 */
#define CLK_SYS    (0x05ul << 8 | 0ul)  /**< \brief 系统 时钟 */
#define CLK_RTC    (0x05ul << 8 | 1ul)  /**< \brief 系统 时钟 */
/**
 * @}
 */

/**
 * @} zmf159_if_clk
 */

#ifdef __cplusplus
}
#endif

#endif /* __ZMF159_CLK_H */

/* end of file */
