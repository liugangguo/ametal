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
 * \brief ZMF159 外设 实例初始化函数声明
 *
 * 所有外设设备（I2C、SPI、ADC...）的实例初始化函数均在本头文件中声明，使用实例
 * 初始化函数，可以轻松获得一个外设的句柄，然后使用相关的接口函数对外设进行操作。
 *
 * \sa am_zmf159_inst_init.h
 * \internal
 * \par Modification history
 * - 1.00 15-12-11  tee, first implementation
 * \endinternal
 */

#ifndef __AM_ZMF159_INST_INIT_H
#define __AM_ZMF159_INST_INIT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "am_adc.h"
#include "am_can.h"
#include "am_crc.h"
#include "am_i2c.h"
#include "am_i2c_slv.h"
#include "am_timer.h"
#include "am_cap.h"
#include "am_pwm.h"
#include "am_wdt.h"
#include "am_spi.h"
#include "am_led.h"
#include "am_uart.h"
#include "am_dac.h"
#include "am_rtc.h"
#include "am_ftl.h"
#include "am_temp.h"
#include "am_delay.h"
#include "am_hc595.h"
#include "am_ili9341.h"
#include "am_rx8025t.h"
#include "am_digitron_disp.h"
#include "am_ep24cxx.h"
#include "am_mx25xx.h"
#include "am_mtd.h"
#include "am_rngbuf.h"
#include "am_input.h"
#include "am_zlg_tim_cap.h"
#include "amhw_zlg217_rtc.h"
#include "am_zmf159_pwr.h"

#include "am_usbd_cdc_vcom.h"
#include "am_usbd_printer.h"

//#include "am_hwconf_key_gpio.h"
//#include "am_hwconf_buzzer_pwm.h"
//#include "am_hwconf_debug_uart.h"
//#include "am_hwconf_system_tick_softimer.h"
//#include "am_hwconf_lm75.h"
//#include "am_hwconf_microport.h"
//#include "am_hwconf_miniport_zlg72128.h"
//#include "am_hwconf_miniport_595.h"
//#include "am_hwconf_miniport_view.h"
//#include "am_hwconf_miniport_led.h"
//#include "am_hwconf_miniport_key.h"
//#include "am_hwconf_miniport_view_key.h"
//#include "am_event_input_key.h"
//#include "am_event_category_input.h"

/**
 * \addtogroup am_if_zlg217_inst_init
 * \copydoc am_zlg217_inst_init.h
 * @{
 */

/**
 * \brief 调试串口实例初始化
 */
am_uart_handle_t am_debug_uart_inst_init (void);

/**
 * \brief LED GPIO实例初始化
 */
int am_led_gpio_inst_init (void);

/**
 * \brief 系统滴答实例初始化(使用软件定时器)
 */
am_timer_handle_t am_system_tick_softimer_inst_init (void);

/**
 * \brief 蜂鸣器实例初始化
 */
am_pwm_handle_t am_buzzer_pwm_inst_init (void);

/**
 * \brief 实例初始化函数
 */
int am_key_gpio_inst_init (void);

/**
 * \brief 中断实例初始化，初始化中断驱动
 *
 * \param 无
 *
 * \return 返回 AW_OK 为初始化成功，其它为初始化失败
 */
int am_zmf159_nvic_inst_init (void);

/**
 * \brief 中断实例解初始化
 *
 * \param 无
 *
 * \return 无
 */
void am_zmf159_nvic_inst_deinit (void);

/**
 * \brief ILI9341 实例初始化，获得 ILI9341 标准服务句柄
 *
 * \param 无
 *
 * \return ILI9341 标准服务句柄，若为 NULL，表明初始化失败
 */
am_ili9341_handle_t am_zmf159_ili9341_inst_init (void);

/**
 * \brief ILI9341 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_ili9341_inst_init() 函数获得的 ILI9341
 *                   标准服务句柄
 *
 * \return 无
 */
void am_zmf159_ili9341_inst_deinit (am_ili9341_handle_t handle);

/**
 * \brief ADC1 实例初始化，获得 ADC 标准服务句柄
 *
 * \param 无
 *
 * \return ADC 标准服务句柄，若为 NULL，表明初始化失败
 */
am_adc_handle_t am_zmf159_adc1_inst_init (void);

/**
 * \brief ADC1 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_adc1_inst_init() 函数获得的 ADC 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_adc1_inst_deinit (am_adc_handle_t handle);

/**
 * \brief ADC2 实例初始化，获得 ADC 标准服务句柄
 *
 * \param 无
 *
 * \return ADC 标准服务句柄，若为 NULL，表明初始化失败
 */
am_adc_handle_t am_zmf159_adc2_inst_init (void);

/**
 * \brief ADC2 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_adc2_inst_init() 函数获得的 ADC 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_adc2_inst_deinit (am_adc_handle_t handle);

/**
 * \brief CLK 实例初始化，初始化系统时钟
 *
 * \param 无
 *
 * \return 返回 AW_OK 为初始化成功，其它为初始化失败
 */
int am_zmf159_clk_inst_init (void);

/**
 * \brief CRC 实例初始化，获得 CRC 标准服务句柄
 *
 * \param 无
 *
 * \return CRC 标准服务句柄，若为 NULL，表明初始化失败
 */
am_crc_handle_t am_zmf159_crc_inst_init (void);

/**
 * \brief CRC 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_crc_inst_init() 函数获得的 CRC 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_crc_inst_deinit (am_crc_handle_t handle);

/**
 * \brief DAC1 实例初始化，获得 DAC 标准服务句柄
 *
 * \param 无
 *
 * \return DAC 标准服务句柄，若为 NULL，表明初始化失败
 */
am_dac_handle_t am_zmf159_dac1_inst_init (void);

/**
 * \brief DAC1 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_dac1_inst_init() 函数获得的 DAC 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_dac1_inst_deinit (am_dac_handle_t handle);

/**
 * \brief DAC2 实例初始化，获得 DAC 标准服务句柄
 *
 * \param 无
 *
 * \return DAC 标准服务句柄，若为 NULL，表明初始化失败
 */
am_dac_handle_t am_zmf159_dac2_inst_init (void);

/**
 * \brief DAC2 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_dac2_inst_init() 函数获得的 DAC 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_dac2_inst_deinit (am_dac_handle_t handle);

/**
 * \brief DMA1 实例初始化
 *
 * \param 无
 *
 * \return 返回 AW_OK 为初始化成功，其它为初始化失败
 */
int am_zmf159_dma1_inst_init (void);

/**
 * \brief DMA2 实例初始化
 *
 * \param 无
 *
 * \return 返回 AW_OK 为初始化成功，其它为初始化失败
 */
int am_zmf159_dma2_inst_init (void);

/**
 * \brief DMA1 实例解初始化
 *
 * \param 无
 *
 * \return 无
 */
void am_zmf159_dma1_inst_deinit (void);

/**
 * \brief DMA2 实例解初始化
 *
 * \param 无
 *
 * \return 无
 */
void am_zmf159_dma2_inst_deinit (void);

/**
 * \brief GPIO 实例初始化
 *
 * \param 无
 *
 * \return 返回 AW_OK 为初始化成功，其它为初始化失败
 */
int am_zmf159_gpio_inst_init (void);

/**
 * \brief GPIO 实例解初始化
 *
 * \param 无
 *
 * \return 无
 */
void am_zmf159_gpio_inst_deinit (void);

/**
 * \brief I2C1 实例初始化，获得 I2C 标准服务句柄
 *
 * \param 无
 *
 * \return I2C 标准服务句柄，若为 NULL，表明初始化失败
 */
am_i2c_handle_t am_zmf159_i2c1_inst_init (void);

/**
 * \brief I2C1 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_i2c1_inst_init() 函数获得的 I2C 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_i2c1_inst_deinit (am_i2c_handle_t handle);

/**
 * \brief I2C2 实例初始化，获得 I2C 标准服务句柄
 *
 * \param 无
 *
 * \return I2C 标准服务句柄，若为 NULL，表明初始化失败
 */
am_i2c_handle_t am_zmf159_i2c2_inst_init (void);

/**
 * \brief I2C2 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_i2c2_inst_init() 函数获得的 I2C 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_i2c2_inst_deinit (am_i2c_handle_t handle);

/**
 * \brief I2C1 从机实例初始化，获得 I2C 从机标准服务句柄
 *
 * \param 无
 *
 * \return I2C 从机标准服务句柄，若为 NULL，表明初始化失败
 */
am_i2c_slv_handle_t am_zmf159_i2c1_slv_inst_init (void);

/**
 * \brief I2C1 从机实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_i2c1_slv_inst_init() 函数
 *                   获得的 I2C 从机标准服务句柄
 *
 * \return 无
 */
void am_zmf159_i2c1_slv_inst_deinit (am_i2c_slv_handle_t handle);

/**
 * \brief I2C2 从机实例初始化，获得 I2C 从机标准服务句柄
 *
 * \param 无
 *
 * \return I2C 从机标准服务句柄，若为 NULL，表明初始化失败
 */
am_i2c_slv_handle_t am_zmf159_i2c2_slv_inst_init (void);

/**
 * \brief I2C2 从机实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_i2c2_slv_inst_init() 函数
 *                   获得的 I2C 从机标准服务句柄
 *
 * \return 无
 */
void am_zmf159_i2c2_slv_inst_deinit (am_i2c_slv_handle_t handle);

/**
 * \brief IWDG 实例初始化，获得 WDT 标准服务句柄
 *
 * \param 无
 *
 * \return WDT 标准服务句柄，若为 NULL，表明初始化失败
 */
am_wdt_handle_t am_zmf159_iwdg_inst_init (void);

/**
 * \brief IWDG 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_iwdg_inst_init() 函数获得的 WDT 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_iwdg_inst_deinit (am_wdt_handle_t handle);

/**
 * \brief PWR 实例初始化
 *
 * \param 无
 *
 * \return PWR 标准服务句柄，若为 NULL，表明初始化失败
 */
//am_zmf159_pwr_handle_t am_zmf159_pwr_inst_init (void);

/**
 * \brief PWR 实例解初始化
 *
 * \param 无
 *
 * \return 无
 */
void am_zmf159_pwr_inst_deinit (void);

/**
 * \brief RTC 实例初始化，获得 RTC 标准服务句柄
 *
 * \param 无
 *
 * \return RTC 标准服务句柄，若为 NULL，表明初始化失败
 */
am_rtc_handle_t am_zmf159_rtc_inst_init (void);

/**
 * \brief RTC 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_rtc_inst_init() 函数获得的 RTC 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_rtc_inst_deinit (am_rtc_handle_t handle);

/**
 * \brief SPI1 DMA 实例初始化，获得 SPI 标准服务句柄
 *
 * \param 无
 *
 * \return SPI 标准服务句柄，若为 NULL，表明初始化失败
 */
am_spi_handle_t am_zmf159_spi1_dma_inst_init (void);

/**
 * \brief SPI1 DMA 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_spi1_dma_inst_init() 函数
 *                   获得的 SPI 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_spi1_dma_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SPI2 DMA 实例初始化，获得 SPI 标准服务句柄
 *
 * \param 无
 *
 * \return SPI 标准服务句柄，若为 NULL，表明初始化失败
 */
am_spi_handle_t am_zmf159_spi2_dma_inst_init (void);

/**
 * \brief SPI2 DMA 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_spi2_dma_inst_init() 函数
 *                   获得的 SPI 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_spi2_dma_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SPI1 INT 实例初始化，获得 SPI 标准服务句柄
 *
 * \param 无
 *
 * \return SPI 标准服务句柄，若为 NULL，表明初始化失败
 */
am_spi_handle_t am_zmf159_spi1_int_inst_init (void);

/**
 * \brief SPI1 INT 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_spi1_int_inst_init() 函数
 *                   获得的 SPI 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_spi1_int_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SPI2 INT 实例初始化，获得 SPI 标准服务句柄
 *
 * \param 无
 *
 * \return SPI 标准服务句柄，若为 NULL，表明初始化失败
 */
am_spi_handle_t am_zmf159_spi2_int_inst_init (void);

/**
 * \brief SPI2 INT 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_spi2_int_inst_init() 函数
 *                   获得的 SPI 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_spi2_int_inst_deinit (am_spi_handle_t handle);

/**
 * \brief SYSTICK 实例初始化，获得 TIMER 标准服务句柄
 *
 * \param 无
 *
 * \return TIMER 标准服务句柄，若为 NULL，表明初始化失败
 */
am_timer_handle_t am_zmf159_systick_inst_init (void);

/**
 * \brief SYSTICK 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_systick_inst_init() 函数
 *                   获得的 TIMER 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_systick_inst_deinit (am_timer_handle_t handle);

/**
 * \brief TIM1 CAP 实例初始化，获得 CAP 标准服务句柄
 *
 * \param 无
 *
 * \return CAP 标准服务句柄，若为 NULL，表明初始化失败
 */
am_cap_handle_t am_zmf159_tim1_cap_inst_init (void);

/**
 * \brief TIM1 CAP 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim1_cap_inst_init() 函数
 *                   获得的 CAP 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim1_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief TIM2 CAP 实例初始化，获得 CAP 标准服务句柄
 *
 * \param 无
 *
 * \return CAP 标准服务句柄，若为 NULL，表明初始化失败
 */
am_cap_handle_t am_zmf159_tim2_cap_inst_init (void);

/**
 * \brief TIM2 CAP 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim2_cap_inst_init() 函数
 *                   获得的 CAP 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim2_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief TIM3 CAP 实例初始化，获得 CAP 标准服务句柄
 *
 * \param 无
 *
 * \return CAP 标准服务句柄，若为 NULL，表明初始化失败
 */
am_cap_handle_t am_zmf159_tim3_cap_inst_init (void);

/**
 * \brief TIM3 CAP 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim3_cap_inst_init() 函数
 *                   获得的 CAP 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim3_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief TIM4 CAP 实例初始化，获得 CAP 标准服务句柄
 *
 * \param 无
 *
 * \return CAP 标准服务句柄，若为 NULL，表明初始化失败
 */
am_cap_handle_t am_zmf159_tim4_cap_inst_init (void);

/**
 * \brief TIM4 CAP 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim4_cap_inst_init() 函数
 *                   获得的 CAP 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim4_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief TIM5 CAP 实例初始化，获得 CAP 标准服务句柄
 *
 * \param 无
 *
 * \return CAP 标准服务句柄，若为 NULL，表明初始化失败
 */
am_cap_handle_t am_zmf159_tim5_cap_inst_init (void);

/**
 * \brief TIM5 CAP 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim5_cap_inst_init() 函数
 *                   获得的 CAP 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim5_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief TIM6 CAP 实例初始化，获得 CAP 标准服务句柄
 *
 * \param 无
 *
 * \return CAP 标准服务句柄，若为 NULL，表明初始化失败
 */
am_cap_handle_t am_zmf159_tim6_cap_inst_init (void);

/**
 * \brief TIM6 CAP 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim6_cap_inst_init() 函数
 *                   获得的 CAP 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim6_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief TIM7 CAP 实例初始化，获得 CAP 标准服务句柄
 *
 * \param 无
 *
 * \return CAP 标准服务句柄，若为 NULL，表明初始化失败
 */
am_cap_handle_t am_zmf159_tim7_cap_inst_init (void);

/**
 * \brief TIM4 CAP 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim7_cap_inst_init() 函数
 *                   获得的 CAP 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim7_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief TIM8 CAP 实例初始化，获得 CAP 标准服务句柄
 *
 * \param 无
 *
 * \return CAP 标准服务句柄，若为 NULL，表明初始化失败
 */
am_cap_handle_t am_zmf159_tim8_cap_inst_init (void);

/**
 * \brief TIM8 CAP 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim8_cap_inst_init() 函数
 *                   获得的 CAP 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim8_cap_inst_deinit (am_cap_handle_t handle);

/**
 * \brief TIM1 PWM 实例初始化，获得 PWM 标准服务句柄
 *
 * \param 无
 *
 * \return PWM 标准服务句柄，若为 NULL，表明初始化失败
 */
am_pwm_handle_t am_zmf159_tim1_pwm_inst_init (void);

/**
 * \brief TIM1 PWM 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim1_pwm_inst_init() 函数
 *                   获得的 PWM 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim1_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief TIM2 PWM 实例初始化，获得 PWM 标准服务句柄
 *
 * \param 无
 *
 * \return PWM 标准服务句柄，若为 NULL，表明初始化失败
 */
am_pwm_handle_t am_zmf159_tim2_pwm_inst_init (void);

/**
 * \brief TIM2 PWM 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim2_pwm_inst_init() 函数
 *                   获得的 PWM 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim2_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief TIM3 PWM 实例初始化，获得 PWM 标准服务句柄
 *
 * \param 无
 *
 * \return PWM 标准服务句柄，若为 NULL，表明初始化失败
 */
am_pwm_handle_t am_zmf159_tim3_pwm_inst_init (void);

/**
 * \brief TIM3 PWM 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim3_pwm_inst_init() 函数
 *                   获得的 PWM 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim3_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief TIM4 PWM 实例初始化，获得 PWM 标准服务句柄
 *
 * \param 无
 *
 * \return PWM 标准服务句柄，若为 NULL，表明初始化失败
 */
am_pwm_handle_t am_zmf159_tim4_pwm_inst_init (void);

/**
 * \brief TIM4 PWM 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim4_pwm_inst_init() 函数
 *                   获得的 PWM 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim4_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief TIM5 PWM 实例初始化，获得 PWM 标准服务句柄
 *
 * \param 无
 *
 * \return PWM 标准服务句柄，若为 NULL，表明初始化失败
 */
am_pwm_handle_t am_zmf159_tim5_pwm_inst_init (void);

/**
 * \brief TIM5 PWM 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim5_pwm_inst_init() 函数
 *                   获得的 PWM 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim5_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief TIM6 PWM 实例初始化，获得 PWM 标准服务句柄
 *
 * \param 无
 *
 * \return PWM 标准服务句柄，若为 NULL，表明初始化失败
 */
am_pwm_handle_t am_zmf159_tim6_pwm_inst_init (void);

/**
 * \brief TIM6 PWM 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim6_pwm_inst_init() 函数
 *                   获得的 PWM 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim6_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief TIM7 PWM 实例初始化，获得 PWM 标准服务句柄
 *
 * \param 无
 *
 * \return PWM 标准服务句柄，若为 NULL，表明初始化失败
 */
am_pwm_handle_t am_zmf159_tim7_pwm_inst_init (void);

/**
 * \brief TIM7 PWM 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim7_pwm_inst_init() 函数
 *                   获得的 PWM 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim7_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief TIM8 PWM 实例初始化，获得 PWM 标准服务句柄
 *
 * \param 无
 *
 * \return PWM 标准服务句柄，若为 NULL，表明初始化失败
 */
am_pwm_handle_t am_zmf159_tim8_pwm_inst_init (void);

/**
 * \brief TIM8 PWM 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim8_pwm_inst_init() 函数
 *                   获得的 PWM 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim8_pwm_inst_deinit (am_pwm_handle_t handle);

/**
 * \brief TIM1 TIMING 实例初始化，获得 TIMER 标准服务句柄
 *
 * \param 无
 *
 * \return PWM 标准服务句柄，若为 NULL，表明初始化失败
 */
am_timer_handle_t am_zmf159_tim1_timing_inst_init (void);

/**
 * \brief TIM1 TIMING 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim1_timing_inst_init() 函数
 *                   获得的 TIMER 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim1_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief TIM2 TIMING 实例初始化，获得 TIMER 标准服务句柄
 *
 * \param 无
 *
 * \return PWM 标准服务句柄，若为 NULL，表明初始化失败
 */
am_timer_handle_t am_zmf159_tim2_timing_inst_init (void);

/**
 * \brief TIM2 TIMING 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim2_timing_inst_init() 函数
 *                   获得的 TIMER 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim2_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief TIM3 TIMING 实例初始化，获得 TIMER 标准服务句柄
 *
 * \param 无
 *
 * \return PWM 标准服务句柄，若为 NULL，表明初始化失败
 */
am_timer_handle_t am_zmf159_tim3_timing_inst_init (void);

/**
 * \brief TIM3 TIMING 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim3_timing_inst_init() 函数
 *                   获得的 TIMER 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim3_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief TIM4 TIMING 实例初始化，获得 TIMER 标准服务句柄
 *
 * \param 无
 *
 * \return PWM 标准服务句柄，若为 NULL，表明初始化失败
 */
am_timer_handle_t am_zmf159_tim4_timing_inst_init (void);

/**
 * \brief TIM4 TIMING 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim4_timing_inst_init() 函数
 *                   获得的 TIMER 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim4_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief TIM5 TIMING 实例初始化，获得 TIMER 标准服务句柄
 *
 * \param 无
 *
 * \return PWM 标准服务句柄，若为 NULL，表明初始化失败
 */
am_timer_handle_t am_zmf159_tim5_timing_inst_init (void);

/**
 * \brief TIM5 TIMING 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim5_timing_inst_init() 函数
 *                   获得的 TIMER 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim5_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief TIM6 TIMING 实例初始化，获得 TIMER 标准服务句柄
 *
 * \param 无
 *
 * \return PWM 标准服务句柄，若为 NULL，表明初始化失败
 */
am_timer_handle_t am_zmf159_tim6_timing_inst_init (void);

/**
 * \brief TIM6 TIMING 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim6_timing_inst_init() 函数
 *                   获得的 TIMER 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim6_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief TIM7 TIMING 实例初始化，获得 TIMER 标准服务句柄
 *
 * \param 无
 *
 * \return PWM 标准服务句柄，若为 NULL，表明初始化失败
 */
am_timer_handle_t am_zmf159_tim7_timing_inst_init (void);

/**
 * \brief TIM7 TIMING 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim7_timing_inst_init() 函数
 *                   获得的 TIMER 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim7_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief TIM8 TIMING 实例初始化，获得 TIMER 标准服务句柄
 *
 * \param 无
 *
 * \return PWM 标准服务句柄，若为 NULL，表明初始化失败
 */
am_timer_handle_t am_zmf159_tim8_timing_inst_init (void);

/**
 * \brief TIM8 TIMING 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_tim8_timing_inst_init() 函数
 *                   获得的 TIMER 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_tim8_timing_inst_deinit (am_timer_handle_t handle);

/**
 * \brief UART1 实例初始化，获得 UART 标准服务句柄
 *
 * \param 无
 *
 * \return UART 标准服务句柄，若为 NULL，表明初始化失败
 */
am_uart_handle_t am_zmf159_uart1_inst_init (void);

/**
 * \brief UART1 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_uart1_inst_init() 函数获得的 UART 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_uart1_inst_deinit (am_uart_handle_t handle);

/**
 * \brief UART2 实例初始化，获得 UART 标准服务句柄
 *
 * \param 无
 *
 * \return UART 标准服务句柄，若为 NULL，表明初始化失败
 */
am_uart_handle_t am_zmf159_uart2_inst_init (void);

/**
 * \brief UART2 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_uart2_inst_init() 函数获得的 UART 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_uart2_inst_deinit (am_uart_handle_t handle);

/**
 * \brief UART3 实例初始化，获得 UART 标准服务句柄
 *
 * \param 无
 *
 * \return UART 标准服务句柄，若为 NULL，表明初始化失败
 */
am_uart_handle_t am_zmf159_uart3_inst_init (void);

/**
 * \brief UART3 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_uart3_inst_init() 函数获得的 UART 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_uart3_inst_deinit (am_uart_handle_t handle);

/**
 * \brief WWDG 实例初始化，获得 WDT 标准服务句柄
 *
 * \param 无
 *
 * \return WDT 标准服务句柄，若为 NULL，表明初始化失败
 */
am_wdt_handle_t am_zmf159_wwdg_inst_init (void);

/**
 * \brief WWDG 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_wwdg_inst_init() 函数获得的 WDT 标准服务句柄
 *
 * \return 无
 */
void am_zmf159_wwdg_inst_deinit (am_wdt_handle_t handle);

/**
 * \brief PWR 实例解初始化
 *
 * \param[in] handle 通过 am_zmf159_pwr_inst_init() 函数获得的 PWR 标准服务句柄
 *
 * \return 无
 */
am_zmf159_pwr_handle_t am_zmf159_pwr_inst_init (void);

/** \brief 实例初始化函数 */
am_temp_handle_t am_temp_lm75_inst_init (void);

/** \brief usb_printer实例初始化，获得usb_printer标准服务句柄 */
am_usbd_printer_handle am_zmf159_usbd_printer_inst_init (void);

/** \brief usb_vcom实例初始化，获得usb_vcom标准服务句柄 */
am_usbd_cdc_vcom_handle am_zmf159_usbd_vcom_inst_init (void);
/** \brief usb_vcom实例初始化，获得can标准服务句柄 */
am_can_handle_t am_zmf159_can_inst_init (void);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AM_ZMF159_INST_INIT_H */

/* end of file */
