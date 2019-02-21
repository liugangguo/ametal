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
 * \brief ZMF159 Õ‚…Ë”≥…‰
 *
 * \internal
 * \par Modification history
 * - 1.00 17-08-23  lqy, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZMF159_PERIPH_MAP_H
#define __AMHW_ZMF159_PERIPH_MAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "zmf159_regbase.h"

#include "hw/amhw_zlg_adc.h"
#include "hw/amhw_zlg_bkp.h"
#include "hw/amhw_zlg_cmp.h"
#include "hw/amhw_zlg_crc.h"
#include "hw/amhw_zlg_dac.h"
#include "hw/amhw_zlg_flash.h"
#include "hw/amhw_zlg_i2c.h"
#include "hw/amhw_zlg_spi.h"
#include "hw/amhw_zlg_tim.h"
#include "hw/amhw_zlg_uart.h"
#include "hw/amhw_zlg_iwdg.h"
#include "hw/amhw_zlg_wwdg.h"
#include "hw/amhw_zlg_pwr.h"
#include "hw/amhw_zmf159_exti.h"
#include "hw/amhw_zlg_syscfg.h"
#include "hw/amhw_zlg_gpio.h"
#include "hw/amhw_zlg_dma.h"
#include "hw/amhw_zmf159_pwr.h"
#include "hw/amhw_zmf159_usb.h"

/**
 * \addtogroup amhw_zmf159_if_periph_map
 * \copydoc amhw_zmf159_periph_map.h
 * @{
 */

/**
 * \name Õ‚…Ë∂®“Â
 * @{
 */

#define ZMF159_GPIO    ((amhw_zlg_gpio_t         *)ZMF159_GPIO_BASE)

/** \brief RCCøÿ÷∆∆˜ºƒ¥Ê∆˜øÈ÷∏’Î */
#define ZMF159_RCC     ((amhw_zmf159_rcc_t       *)ZMF159_RCC_BASE)

/** \brief FLASHºƒ¥Ê∆˜øÈ÷∏’Î */
#define ZMF159_FLASH   ((amhw_zlg_flash_t        *)ZMF159_FLASH_BASE)

/** \brief œµÕ≥≈‰÷√(SYSCFG)ºƒ¥Ê∆˜øÈ÷∏’Î */
#define ZMF159_SYSCFG  ((amhw_zlg_syscfg_t       *)ZMF159_SYSCFG_BASE)

/** \brief  */
#define ZMF159_EXTI    ((amhw_zmf159_exti_t      *)ZMF159_EXTI_BASE)

/** \brief  */
#define ZMF159_PWR     ((amhw_zmf159_pwr_t       *)ZMF159_PWR_BASE)

/** \brief  */
#define ZMF159_BKP     ((amhw_zlg_bkp_t          *)ZMF159_BKP_BASE)

/** \brief  */
#define ZMF159_WWDG    ((amhw_zlg_wwdg_t        *)ZMF159_WWDG_BASE)

/** \brief  */
#define ZMF159_RTC     ((amhw_zlg217_rtc_t         *)ZMF159_RTC_BASE)

/** \brief  */
#define ZMF159_IWDG     ((amhw_zlg_iwdg_t       *)ZMF159_IWDG_BASE)

/** \brief  */
#define ZMF159_SPI1     ((amhw_zlg_spi_t       *)ZMF159_SPI1_BASE)

/** \brief  */
#define ZMF159_SPI2     ((amhw_zlg_spi_t       *)ZMF159_SPI2_BASE)

/** \brief  */
#define ZMF159_SPI3     ((amhw_zlg_spi_t       *)ZMF159_SPI3_BASE)

/** \brief  */
#define ZMF159_UART1     ((amhw_zlg_uart_t      *)ZMF159_UART1_BASE)

/** \brief  */
#define ZMF159_UART2     ((amhw_zlg_uart_t      *)ZMF159_UART2_BASE)

/** \brief  */
#define ZMF159_UART3     ((amhw_zlg_uart_t      *)ZMF159_UART3_BASE)

/** \brief  */
#define ZMF159_UART4     ((amhw_zlg_uart_t      *)ZMF159_UART4_BASE)

/** \brief  */
#define ZMF159_UART5     ((amhw_zlg_uart_t      *)ZMF159_UART5_BASE)

/** \brief  */
#define ZMF159_UART6     ((amhw_zlg_uart_t      *)ZMF159_UART6_BASE)

/** \brief  */
#define ZMF159_UART7     ((amhw_zlg_uart_t      *)ZMF159_UART7_BASE)

/** \brief  */
#define ZMF159_UART8     ((amhw_zlg_uart_t      *)ZMF159_UART8_BASE)

/** \brief  */
#define ZMF159_I2C1     ((amhw_zlg_i2c_t      *)ZMF159_I2C1_BASE)

/** \brief  */
#define ZMF159_I2C2     ((amhw_zlg_i2c_t      *)ZMF159_I2C2_BASE)

/** \brief  */
#define ZMF159_ADC1     ((amhw_zlg_adc_t      *)ZMF159_ADC1_BASE)

/** \brief  */
#define ZMF159_TIM1     ((amhw_zlg_tim_t      *)ZMF159_TIM1_BASE)

/** \brief  */
#define ZMF159_TIM2     ((amhw_zlg_tim_t      *)ZMF159_TIM2_BASE)

/** \brief  */
#define ZMF159_TIM3     ((amhw_zlg_tim_t      *)ZMF159_TIM3_BASE)

/** \brief  */
#define ZMF159_TIM4     ((amhw_zlg_tim_t      *)ZMF159_TIM4_BASE)

/** \brief  */
#define ZMF159_TIM5     ((amhw_zlg_tim_t      *)ZMF159_TIM5_BASE)

/** \brief  */
#define ZMF159_TIM6     ((amhw_zlg_tim_t      *)ZMF159_TIM6_BASE)

/** \brief  */
#define ZMF159_TIM7     ((amhw_zlg_tim_t      *)ZMF159_TIM7_BASE)

/** \brief  */
#define ZMF159_TIM8     ((amhw_zlg_tim_t      *)ZMF159_TIM8_BASE)

/** \brief  */
#define ZMF159_GPIOA     ((amhw_zlg_gpio_t     *)ZMF159_GPIOA_BASE)

/** \brief  */
#define ZMF159_GPIOB     ((amhw_zlg_gpio_t     *)ZMF159_GPIOB_BASE)

/** \brief  */
#define ZMF159_GPIOC     ((amhw_zlg_gpio_t     *)ZMF159_GPIOC_BASE)

/** \brief  */
#define ZMF159_GPIOD     ((amhw_zlg_gpio_t     *)ZMF159_GPIOD_BASE)

/** \brief  */
#define ZMF159_GPIOE     ((amhw_zlg_gpio_t     *)ZMF159_GPIOE_BASE)

/** \brief  */
#define ZMF159_USB       ((amhw_zmf159_usb_t   *)ZMF159_USB_BASE)

/** @} */

/**
 * @} amhw_ZMF159_if_periph_map
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_ZMF159_REG_BASE_H */

/* end of file */
