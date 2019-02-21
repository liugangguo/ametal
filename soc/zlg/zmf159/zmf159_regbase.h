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
 * \brief ZMF159 芯片外设寄存器基址定义
 *
 * \internal
 * \par Modification history
 * - 1.00 19-02-20  ipk, first implementation
 * \endinternal
 */

#ifndef __ZMF159_REGBASE_H
#define __ZMF159_REGBASE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup zmf159_if_regbase
 * \copydoc zmf159_regbase.h
 * @{
 */

/**
 * \name 外设内存映射地址定义
 * @{
 */

/** \brief GPIO基地址 */
#define ZMF159_GPIO_BASE              (0x48000000UL)

/** \brief GPIOA基地址 */
#define ZMF159_GPIOA_BASE             (0x48000000UL)

/** \brief GPIOB基地址 */
#define ZMF159_GPIOB_BASE             (0x48000400UL)

/** \brief GPIOC基地址 */
#define ZMF159_GPIOC_BASE             (0x48000800UL)

/** \brief GPIOD基地址 */
#define ZMF159_GPIOD_BASE             (0x48000C00UL)

/** \brief GPIOE基地址 */
#define ZMF159_GPIOE_BASE             (0x48001000UL)

/** \brief 高级控制定时器1基地址 */
#define ZMF159_TIM1_BASE              (0x40012C00UL)

/** \brief 通用定时器2基地址 */
#define ZMF159_TIM2_BASE              (0x40000000UL)

/** \brief 通用定时器3基地址 */
#define ZMF159_TIM3_BASE              (0x40000400UL)

/** \brief 通用定时器4基地址 */
#define ZMF159_TIM4_BASE              (0x40000800UL)

/** \brief 通用定时器5基地址 */
#define ZMF159_TIM5_BASE              (0x40000C00UL)

/** \brief 通用定时器6基地址 */
#define ZMF159_TIM6_BASE              (0x40001000UL)

/** \brief 通用定时器7基地址 */
#define ZMF159_TIM7_BASE              (0x40001400UL)

/** \brief 高级控制定时器8基地址 */
#define ZMF159_TIM8_BASE              (0x40013400UL)

/** \brief RTC基地址 */
#define ZMF159_RTC_BASE               (0x40002800UL)

/** \brief 备份控制BKP基地址 */
#define ZMF159_BKP_BASE               (0x40002824UL)

/** \brief 电源控制PWR基地址 */
#define ZMF159_PWR_BASE               (0x40007000UL)

/** \brief UART1 基地址 */
#define ZMF159_UART1_BASE             (0x40013800UL)

/** \brief UART2 基地址 */
#define ZMF159_UART2_BASE             (0x40004400UL)

/** \brief UART3 基地址 */
#define ZMF159_UART3_BASE             (0x40004800UL)

/** \brief UART4 基地址 */
#define ZMF159_UART4_BASE             (0x40004C00UL)

/** \brief UART5 基地址 */
#define ZMF159_UART5_BASE             (0x40005000UL)

/** \brief UART6 基地址 */
#define ZMF159_UART6_BASE             (0x40013C00UL)

/** \brief UART7 基地址 */
#define ZMF159_UART7_BASE             (0x40007800UL)

/** \brief UART8 基地址 */
#define ZMF159_UART8_BASE             (0x40007C00UL)

/** \brief ADC1 基地址 */
#define ZMF159_ADC1_BASE              (0x40012400UL)

/** \brief DMA1 基地址 */
#define ZMF159_DMA1_BASE              (0x40020000UL)

/** \brief DMA2 基地址 */
#define ZMF159_DMA2_BASE              (0x40020400UL)

/** \brief RCC控制器基地址 */
#define ZMF159_RCC_BASE               (0x40021000UL)

/** \brief SPI1控制器基地址 */
#define ZMF159_SPI1_BASE              (0x40013000UL)

/** \brief SPI2控制器基地址 */
#define ZMF159_SPI2_BASE              (0x40003800UL)

/** \brief SPI3控制器基地址 */
#define ZMF159_SPI3_BASE              (0x40003C00UL)

/** \brief I2C1基地址 */
#define ZMF159_I2C1_BASE              (0x40005400UL)

/** \brief I2C2基地址 */
#define ZMF159_I2C2_BASE              (0x40005800UL)

/** \brief IWDG控制器基地址 */
#define ZMF159_IWDG_BASE              (0x40003000UL)

/** \brief WWDG控制器基地址 */
#define ZMF159_WWDG_BASE              (0x40002C00UL)

/** \brief CAN控制器基地址 */
#define ZMF159_CAN_BASE               (0x40006400UL)

/** \brief USB控制器基地址 */
#define ZMF159_USB_BASE               (0x50000000UL)

/** \brief 外部中断(事件)控制器EXTI基地址 */
#define ZMF159_EXTI_BASE              (0x40010400UL)

/** \brief FLASH 接口基地址 */
#define ZMF159_FLASH_BASE             (0x40022000UL)

/** \brief SRAM1基地址 */
#define ZMF159_SRAM1_BASE             (0x20004000UL)

/** \brief SRAM2基地址 */
#define ZMF159_SRAM2_BASE             (0x20000000UL)

/** \brief SYS FLASH 基地址 */
#define ZMF159_SYS_FLASH_BASE         (0x1FFFF400UL)

/** \brief Main FLASH 基地址 */
#define ZMF159_MAIN_FLASH_BASE        (0x08000000UL)

/** \brief CRC基地址 */
#define ZMF159_CRC_BASE               (0x40023000UL)

/** \brief SYSCFG基地址 */
#define ZMF159_SYSCFG_BASE            (0x40010000UL)

/** \brief SYSTICK基地址 */
#define ZMF159_SYSTICK                (0xE000E010UL)

/** @} */

/**
 * @} zmf159_if_regbase
 */

#ifdef __cplusplus
}
#endif

#endif/* __ZMF159_REGBASE_H */

/* end of file */
