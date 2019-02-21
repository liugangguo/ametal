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
 * \brief
 *
 * \internal
 * \par Modification history
 * - 1.00 19-02-20  ipk, first implementation
 * \endinternal
 */

#ifndef __AMHW_ZMF159_RCC_H
#define __AMHW_ZMF159_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "zmf159_periph_map.h"

/*
 * \brief 匿名结构体段的开始
 */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/**
 * \addtogroup amhw_zmf159_if_rcc
 * \copydoc amhw_zmf159_rcc.h
 * @{
 */

/**
 * \brief RCC寄存器块结构体
 */
typedef struct amhw_zmf159_rcc {
  __IO uint32_t cr;         /**< \brief 时钟控制寄存器 */
  __IO uint32_t cfgr;       /**< \brief 时钟配置寄存器 */
  __IO uint32_t cir;        /**< \brief 时钟中断寄存器 */
  __IO uint32_t ahb3rstr;   /**< \brief AHB3外设复位寄存器 */
  __IO uint32_t ahb2rstr;   /**< \brief AHB2外设复位寄存器 */
  __IO uint32_t ahb1rstr;   /**< \brief AHB1外设复位寄存器 */
  __IO uint32_t apb2rstr;   /**< \brief APB2外设复位寄存器 */
  __IO uint32_t apb1rstr;   /**< \brief APB1外设复位寄存器 */
  __IO uint32_t ahb3enr;    /**< \brief AHB3外设时钟使能寄存器 */
  __IO uint32_t ahb2enr;    /**< \brief AHB2外设时钟使能寄存器 */
  __IO uint32_t ahb1enr;    /**< \brief AHB1外设时钟使能寄存器 */
  __IO uint32_t apb2enr;    /**< \brief APB2外设时钟使能寄存器 */
  __IO uint32_t apb1enr;    /**< \brief APB1外设时钟使能寄存器 */
  __IO uint32_t bdcr;       /**< \brief 备份控制寄存器 */
  __IO uint32_t csr;        /**< \brief 控制状态寄存器 */
  __IO uint32_t syscfg;     /**< \brief 系统配置寄存器 */
} amhw_zmf159_rcc_t;

/**
 * \brief 系统时钟源
 */
typedef enum {
    AMHW_ZMF159_SYSCLK_HSI_DIV6,  /**< \brief HSI 振荡器  6 分频作为系统时钟 */
    AMHW_ZMF159_SYSCLK_HSE,       /**< \brief HSE 作为系统时钟 */
    AMHW_ZMF159_SYSCLK_PLL,       /**< \brief PLL 输出作为系统时钟 */
    AMHW_ZMF159_SYSCLK_LSI,       /**< \brief LSI 输出作为系统时钟 */
}amhw_zmf159_sys_clk_src;

/**
 * \brief RTC时钟源
 */
typedef enum {
    AMHW_ZMF159_RTCCLK_LSE = 1,       /**< \brief PLL 输出作为系统时钟 */
    AMHW_ZMF159_RTCCLK_LSI = 2,       /**< \brief HSI 振荡器  6 分频作为系统时钟 */
    AMHW_ZMF159_RTCCLK_HSE_DIV128 =3, /**< \brief HSE 作为系统时钟 */
}amhw_zmf159_rtc_clk_src;

/**
 * \brief PLL时钟源
 */
typedef enum {
    AMHW_ZMF159_PLLCLK_HSI_DIV4,  /**< \brief HSI 振荡器  4 分频作为PLL输入时钟 */
    AMHW_ZMF159_PLLCLK_HSE,       /**< \brief HSE 作为PLL输入时钟 */
}amhw_zmf159_pll_clk_src;

/**
 * \brief 时钟中断标志
 */
typedef enum {
    AMHW_ZMF159_CLKINT_INDEX_LSI = 0,  /**< \brief LSI标志 */
    AMHW_ZMF159_CLKINT_INDEX_LSE = 1,  /**< \brief LSE标志 */
    AMHW_ZMF159_CLKINT_INDEX_HSI,      /**< \brief HSI标志 */
    AMHW_ZMF159_CLKINT_INDEX_HSE,      /**< \brief HSE标志 */
    AMHW_ZMF159_CLKINT_INDEX_PLL,      /**< \brief PLL标志 */
    AMHW_ZMF159_CLKINT_INDEX_CSSF = 7, /**< \brief CSSF(时钟安全系统中断)标志 */
}amhw_zmf159_clk_int_index;

/**
 * \brief AHB1外设枚举
 */
typedef enum {
    AMHW_ZMF159_RCC_AHB1_IOPA   = 0,  /**< \brief IOPA */
    AMHW_ZMF159_RCC_AHB1_IOPB   = 1,  /**< \brief IOPB */
    AMHW_ZMF159_RCC_AHB1_IOPC   = 2,  /**< \brief IOPC */
    AMHW_ZMF159_RCC_AHB1_IOPD   = 3,  /**< \brief IOPD */
    AMHW_ZMF159_RCC_AHB1_IOPE   = 4,  /**< \brief IOPE */
    AMHW_ZMF159_RCC_AHB1_SDIO   = 10, /**< \brief SDIO */
    AMHW_ZMF159_RCC_AHB1_CRC    = 12, /**< \brief CRC */
    AMHW_ZMF159_RCC_AHB1_FLASH  = 13, /**< \brief FLASH */
    AMHW_ZMF159_RCC_AHB1_SRAM   = 14, /**< \brief SRAM */
    AMHW_ZMF159_RCC_AHB1_DMA1   = 21, /**< \brief DMA1 */
    AMHW_ZMF159_RCC_AHB1_DMA2   = 22, /**< \brief DMA2 */
}amhw_zmf159_ahb1_peripheral;

/**
 * \brief AHB2外设枚举
 */
typedef enum {
    AMHW_ZMF159_RCC_AHB2_USBFS   = 7,  /**< \brief USBFS */
}amhw_zmf159_ahb2_peripheral;

/**
 * \brief AHB3外设枚举
 */
typedef enum {
    AMHW_ZMF159_RCC_AHB3_FSMC   = 0,  /**< \brief FSMC */
}amhw_zmf159_ahb3_peripheral;

/**
 * \brief APB2外设枚举
 */
typedef enum {
    AMHW_ZMF159_RCC_APB2_TIM1   = 0,  /**< \brief TIM1 */
    AMHW_ZMF159_RCC_APB2_TIM8   = 1,  /**< \brief TIM8 */
    AMHW_ZMF159_RCC_APB2_UART1  = 4,  /**< \brief UART1 */
    AMHW_ZMF159_RCC_APB2_UART6  = 5,  /**< \brief UART6 */
    AMHW_ZMF159_RCC_APB2_ADC1   = 8,  /**< \brief ADC1 */
    AMHW_ZMF159_RCC_APB2_SPI1   = 12, /**< \brief SPI1 */
    AMHW_ZMF159_RCC_APB2_SYSCFG = 14, /**< \brief SYSCFG */
    AMHW_ZMF159_RCC_APB2_COMP   = 15, /**< \brief COMP */
}amhw_zmf159_apb2_peripheral;

/**
 * \brief APB1外设枚举
 */
typedef enum {
    AMHW_ZMF159_RCC_APB1_TIM2   = 0,   /**< \brief TIM2定时器 */
    AMHW_ZMF159_RCC_APB1_TIM3   = 1,   /**< \brief TIM3定时器 */
    AMHW_ZMF159_RCC_APB1_TIM4   = 2,   /**< \brief TIM4定时器 */
    AMHW_ZMF159_RCC_APB1_TIM5   = 3,   /**< \brief TIM5定时器 */
    AMHW_ZMF159_RCC_APB1_TIM6   = 4,   /**< \brief TIM6定时器 */
    AMHW_ZMF159_RCC_APB1_TIM7   = 5,   /**< \brief TIM7定时器 */
    AMHW_ZMF159_RCC_APB1_WWDG   = 11,  /**< \brief WWDG窗口看门狗 */
    AMHW_ZMF159_RCC_APB1_SPI2   = 14,  /**< \brief SPI2 */
    AMHW_ZMF159_RCC_APB1_SPI3   = 15,  /**< \brief SPI3 */
    AMHW_ZMF159_RCC_APB1_UART2  = 17,  /**< \brief UART2 */
    AMHW_ZMF159_RCC_APB1_UART3  = 18,  /**< \brief UART3 */
    AMHW_ZMF159_RCC_APB1_UART4  = 19,  /**< \brief UART4 */
    AMHW_ZMF159_RCC_APB1_UART5  = 20,  /**< \brief UART5 */
    AMHW_ZMF159_RCC_APB1_I2C1   = 21,  /**< \brief I2C1 */
    AMHW_ZMF159_RCC_APB1_I2C2   = 22,  /**< \brief I2C2 */
    AMHW_ZMF159_RCC_APB1_CRS    = 24,  /**< \brief CRS */
    AMHW_ZMF159_RCC_APB1_CAN    = 25,  /**< \brief CAN */
    AMHW_ZMF159_RCC_APB1_BKP    = 27,  /**< \brief BKP */
    AMHW_ZMF159_RCC_APB1_PWR    = 28,  /**< \brief 电源接口 */
    AMHW_ZMF159_RCC_APB1_UART7  = 30,  /**< \brief UART7 */
    AMHW_ZMF159_RCC_APB1_UART8  = 31,  /**< \brief UART8 */
}amhw_zmf159_apb1_peripheral;

/**
 * \brief 复位标志
 */
#define    AMHW_ZMF159_RCC_CSR_PINRSTF    (1ul << 26) /**< \brief NRST管脚复位标志 */
#define    AMHW_ZMF159_RCC_CSR_PORRSTF    (1ul << 27) /**< \brief 上电/掉电复位标志 */
#define    AMHW_ZMF159_RCC_CSR_SFTRSTF    (1ul << 28) /**< \brief 软件复位标志 */
#define    AMHW_ZMF159_RCC_CSR_IWDGRSTF   (1ul << 29) /**< \brief 独立看门狗复位标志 */
#define    AMHW_ZMF159_RCC_CSR_WWDGRSTF   (1ul << 30) /**< \brief 窗口看门狗复位标志 */
#define    AMHW_ZMF159_RCC_CSR_LPWRRSTF   (1ul << 31) /**< \brief 低功耗管理复位标志 */


/**
 * \brief 系统配置寄存器枚举
 */
typedef enum{
    AMHW_ZMF159_RCC_SYSCFG_0  =0,
    AMHW_ZMF159_RCC_SYSCFG_1  =1,
}amhw_zmf159_syscfg_peripheral;

/**
 * \brief USB时钟源选择
 */
typedef enum{
    AMHW_ZMF159_RCC_USB_PLL_48M  =0,
    AMHW_ZMF159_RCC_USB_HSI_48M  =1,
}amhw_zmf159_usb_clk_t;

/**
 * \brief 内部高速时钟使能
 *
 * \return 无
 *
 */
am_static_inline
void amhw_zmf159_rcc_hsion_enable (void)
{
    ZMF159_RCC->cr |= 1ul;
}

/**
 * \brief 内部高速时钟就绪标志读取
 *
 * \retval TRUE  : 内部 8MHz时钟没有就绪
 * \retval FALSE : 内部 8MHz时钟就绪
 */
am_static_inline
am_bool_t amhw_zmf159_rcc_hsirdy_read (void)
{
    return (am_bool_t)((ZMF159_RCC->cr & 0x2ul) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief 外部高速时钟(HSE 振荡器)使能
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_hseon_enable (void)
{
    ZMF159_RCC->cr |= (1ul << 16);
}

/**
 * \brief 外部高速时钟就绪标志读取
 *
 * \retval TRUE  : 外部时钟没有就绪
 * \retval FALSE : 外部时钟就绪
 */
am_static_inline
am_bool_t amhw_zmf159_rcc_hserdy_read (void)
{
    return (am_bool_t)((ZMF159_RCC->cr & (1ul << 17)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief 外部高速时钟旁路使能
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_hsebyp_enable (void)
{
    ZMF159_RCC->cr |= (1ul << 18);
}

/**
 * \brief 时钟安全系统使能
 *
 * \details 如果外部 8-24MHz振荡器就绪，时钟监测器开启。
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_ccson_enable (void)
{
    ZMF159_RCC->cr |= (1ul << 19);
}

/**
 * \brief PLL分频系数设置
 *
 * \param[in]  div ：分频值
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_plldm_set (uint8_t div)
{
    ZMF159_RCC->cr = ((div & 0x7ul) << 20) |
                            (ZMF159_RCC->cr & ~(0x7ul << 20));
}

/**
 * \brief PLL倍频系数设置
 *
 * \param[in]  mul ：倍频值
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_plldn_set (uint8_t mul)
{

    ZMF159_RCC->cr = ((mul & 0x3ful) << 26) |
                            (ZMF159_RCC->cr & ~(0x3ful << 26));
}

/**
 * \brief PLL 使能
 *
 * \details 当进入待机和停止模式时，该位由硬件清零。
 *          当 PLL 时钟被用作或被选择将要作为系统时钟时,
 *          该位不能被清零。
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_pll_enable (void)
{
    ZMF159_RCC->cr |= (1ul << 24);
}

/**
 * \brief PLL 禁能
 *
 * \details 当进入待机和停止模式时，该位由硬件清零。
 *          当 PLL 时钟被用作或被选择将要作为系统时钟时,
 *          该位不能被清零。
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_pll_disable (void)
{
    ZMF159_RCC->cr &= ~(1ul << 24);
}

/**
 * \brief PLL 时钟就绪标志读取
 *
 * \retval TRUE  : PLL 未锁定
 * \retval FALSE : PLL 锁定
 */
am_static_inline
am_bool_t amhw_zmf159_rcc_pllrdy_read (void)
{
    return (am_bool_t)((ZMF159_RCC->cr & (1ul << 25)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief 系统时钟切换
 *
 * \param[in]  src ：系统时钟源
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_sys_clk_set (amhw_zmf159_sys_clk_src src)
{

    ZMF159_RCC->cfgr = ((src & 0x3ul) << 0) |
                              (ZMF159_RCC->cfgr & ~(0x3ul << 0));
}

/**
 * \brief 当前系统时钟获取
 *
 * \return 当前系统时钟源
 */
am_static_inline
amhw_zmf159_sys_clk_src amhw_zmf159_rcc_sys_clk_get (void)
{

    return (amhw_zmf159_sys_clk_src)((ZMF159_RCC->cfgr >> 2ul) & 0x3ul);
}

/**
 * \brief 设置AHB1 预分频
 *
 * \param[in]  div ：预分频值
 *
 *       - 0-7 ： 不分频
 *       - 8   ： 2分频
 *       - 9   ： 4分频
 *       - 10  ： 8分频
 *       - 11  ： 16分频
 *       - 12  ： 64分频
 *       - 13  ： 128分频
 *       - 14  ： 256分频
 *       - 15  ： 512分频
 *
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_ahb1_div_set (uint8_t div)
{

    ZMF159_RCC->cfgr = ((div & 0xful) << 4) |
                              (ZMF159_RCC->cfgr & ~(0xful << 4));
}

/**
 * \brief 设置 低速 APB 预分频（APB1）
 *
 * \param[in]  div ：预分频值
 *
 *       - 0-3 ： 不分频
 *       - 4   ： 2分频
 *       - 5   ： 4分频
 *       - 6   ： 8分频
 *       - 7   ： 16分频
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_apb1_div_set (uint8_t div)
{

    ZMF159_RCC->cfgr = ((div & 0x7ul) << 8) |
                              (ZMF159_RCC->cfgr & ~(0x7ul << 8));
}

/**
 * \brief 获取 低速 APB1 预分频（APB1）
 *
 * \return 预分频值
 *       - 0-3 ： 不分频
 *       - 4   ： 2分频
 *       - 5   ： 4分频
 *       - 6   ： 8分频
 *       - 7   ： 16分频
 */
am_static_inline
uint8_t amhw_zmf159_rcc_apb1_div_get (void)
{

    return (uint8_t)((ZMF159_RCC->cfgr >> 8) & 0x7ul);
}

/**
 * \brief 设置 高速 APB 预分频（APB2）
 *
 * \param[in]  div ：预分频值
 *
 *       - 0-3 ： 不分频
 *       - 4   ： 2分频
 *       - 5   ： 4分频
 *       - 6   ： 8分频
 *       - 7   ： 16分频
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_apb2_div_set (uint8_t div)
{

    ZMF159_RCC->cfgr = ((div & 0x7ul) << 11) |
                              (ZMF159_RCC->cfgr & ~(0x7ul << 11));
}

/**
 * \brief 获取 高速 APB 预分频（APB2）
 *
 * \return 预分频值
 *       - 0-3 ： 不分频
 *       - 4   ： 2分频
 *       - 5   ： 4分频
 *       - 6   ： 8分频
 *       - 7   ： 16分频
 */
am_static_inline
uint8_t amhw_zmf159_rcc_apb2_div_get (void)
{

    return (uint8_t)((ZMF159_RCC->cfgr >> 11) & 0x7ul);
}

/**
 * \brief STOP 模式下设置时钟控制位
 *
 * \param[in]  status值 ：AM_TRUE： 在STOP模式下，硬件不会自动关闭PLL、HSI、HSE
 *                               和PLL_LDO，用户可以通过配置RCC_CR寄存器来关闭相应时钟
 *
 *                      AM_FALSE：在STOP模式下，硬件不会自动关闭PLL、HSI、HSE和PLL_LDO
 *
 * \return 无
 */
am_static_inline
void amhw_amf159_rcc_ckoff_sft_set (am_bool_t status)
{
    ZMF159_RCC->cfgr |= AM_SBF(status, 14);
}

/**
 * \brief USB 48M时钟源选择
 *
 * \return 无
 */
am_static_inline
void amhw_amf159_rcc_clk48msel_set (amhw_zmf159_usb_clk_t flog)
{
    ZMF159_RCC->cfgr |= AM_SBF(flog, 15);
}

/**
 * \brief PLL输入时钟选择
 *
 * \param[in]  src ：PLL输入时钟源
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_pll_clk_set (amhw_zmf159_pll_clk_src src)
{

    ZMF159_RCC->cfgr = ((src & 0x3ul) << 16) |
                              (ZMF159_RCC->cfgr & ~(0x3ul << 16));
}

/**
 * \brief 当前PLL输入时钟获取
 *
 * \return 当前PLL输入时钟源
 */
am_static_inline
amhw_zmf159_pll_clk_src amhw_zmf159_rcc_pll_clk_get (void)
{

    return (amhw_zmf159_pll_clk_src)((ZMF159_RCC->cfgr >> 16ul) & 0x3ul);
}

/**
 * \brief 选择 HSE 分频器作为 PLL 输入
 *
 * \param[in]  div ：分频值
 *
 *      - 0  ： 不分频
 *      - 1  ： 2分频
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_hseforpll_set (uint8_t div)
{

    ZMF159_RCC->cfgr = ((div & 0x1ul) << 17) |
                              (ZMF159_RCC->cfgr & ~(0x1ul << 17));
}

/**
 * \brief 选择 USB 预分频
 *
 * \param[in]  div ：分频值
 *
 *      - 0  ： PLL 时钟直接作为 USB 时钟
 *      - 1  ： PLL 时钟2 分频作为 USB时钟
 *      - 2  ： PLL 时钟3 分频作为 USB时钟
 *      - 3  ： PLL 时钟4 分频作为 USB时钟
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_pllforusb_set (uint8_t div)
{

    ZMF159_RCC->cfgr = ((div & 0x3ul) << 22) |
                              (ZMF159_RCC->cfgr & ~(0x3ul << 22));
}

/**
 * \brief USB 预分频获取
 *
 * \retval  0  ： PLL 时钟直接作为 USB 时钟
 * \retval  1  ： PLL 时钟2 分频作为 USB时钟
 * \retval  2  ： PLL 时钟3 分频作为 USB时钟
 * \retval  3  ： PLL 时钟4 分频作为 USB时钟
 */
am_static_inline
uint8_t amhw_zmf159_rcc_pllforusb_get (void)
{

    return (uint8_t)((ZMF159_RCC->cfgr >> 22ul) & 0x3ul);
}

/**
 * \brief 微控制器时钟输出选择
 *
 * \details 1.该时钟输出在启动和切换 MCO 时钟源时可能会被截断,
 *          2.在系统时钟作为输出至 MCO 管脚时，请保证输出时钟频
 *            率不超过 50MHz（IO口最高频率）
 *
 * \param[in]  src ：时钟源
 *
 *      - 0-1 ： 没有时钟输出
 *      - 2   ： LSI 时钟输出
 *      - 3   ： 保留
 *      - 4   ： 系统时钟（SYSCLK）输出
 *      - 5   ： HSI 时钟输出
 *      - 6   ： HSE 时钟输出
 *      - 7   ： PLL 时钟2 分频后输出
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_mco_src_set (uint8_t src)
{

    ZMF159_RCC->cfgr = ((src & 0x7ul) << 24ul) |
                              (ZMF159_RCC->cfgr & ~(0x7ul << 24ul));
}

/**
 * \brief 就绪中断使能
 *
 * \param[in]  index ：就绪标志
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_clkint_enable (amhw_zmf159_clk_int_index index)
{

    ZMF159_RCC->cir |= ((index & 0x1ful) << 8);
}

/**
 * \brief 就绪中断禁能
 *
 * \param[in]  index ：就绪标志
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_clkint_disable (amhw_zmf159_clk_int_index index)
{

    ZMF159_RCC->cir &= ~((index & 0x1ful) << 8);
}

/**
 * \brief 读取中断标志
 *
 * \return 中断标志
 */
am_static_inline
amhw_zmf159_clk_int_index amhw_zmf159_rcc_clkint_flag_read (void)
{

    return (amhw_zmf159_clk_int_index)(ZMF159_RCC->cir & 0x9ful);
}

/**
 * \brief 清除中断标志
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_clkint_flag_clear (amhw_zmf159_clk_int_index index)
{

    ZMF159_RCC->cir |= ((index & 0x9ful) << 16);
}

/**
 * \brief 复位AHB1外设
 *
 * \param[in]  reset ：需要复位的外设
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_ahb1_reset (amhw_zmf159_ahb1_peripheral reset)
{

    ZMF159_RCC->ahb1rstr |= (1ul << reset);
}

/**
 * \brief 停止复位AHB1外设
 *
 * \param[in]  reset ：需要停止复位的外设
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_ahb1_reset_stop (amhw_zmf159_ahb1_peripheral reset)
{

    ZMF159_RCC->ahb1rstr &= ~(1ul << reset);
}

/**
 * \brief 复位APB2外设
 *
 * \param[in]  reset ：需要复位的外设
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_apb2_reset (amhw_zmf159_apb2_peripheral reset)
{

    ZMF159_RCC->apb2rstr |= (1ul << reset);
}

/**
 * \brief 停止复位APB2外设
 *
 * \param[in]  reset ：需要复位的外设
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_apb2_reset_stop (amhw_zmf159_apb2_peripheral reset)
{

    ZMF159_RCC->apb2rstr &= ~(1ul << reset);
}

/**
 * \brief 复位APB1外设
 *
 * \param[in]  reset ：需要复位的外设
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_apb1_reset (amhw_zmf159_apb1_peripheral reset)
{

    ZMF159_RCC->apb1rstr |= (1ul << reset);
}

/**
 * \brief 停止复位APB1外设
 *
 * \param[in]  reset ：需要复位的外设
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_apb1_reset_stop (amhw_zmf159_apb1_peripheral reset)
{

    ZMF159_RCC->apb1rstr &= ~(1ul << reset);
}

/**
 * \brief 使能APB1外设
 *
 * \param[in]  peri ：需要使能的外设
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_apb1_enable (amhw_zmf159_apb1_peripheral peri)
{

    ZMF159_RCC->apb1enr |= (1ul << peri);
}

/**
 * \brief 禁能APB1外设
 *
 * \param[in]  peri ：需要禁能的外设
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_apb1_disable (amhw_zmf159_apb1_peripheral peri)
{

    ZMF159_RCC->apb1enr &= ~(1ul << peri);
}

/**
 * \brief 使能APB2外设
 *
 * \param[in]  peri ：需要使能的外设
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_apb2_enable (amhw_zmf159_apb2_peripheral peri)
{

    ZMF159_RCC->apb2enr |= (1ul << peri);
}

/**
 * \brief 禁能APB2外设
 *
 * \param[in]  peri ：需要禁能的外设
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_apb2_disable (amhw_zmf159_apb2_peripheral peri)
{

    ZMF159_RCC->apb2enr &= ~(1ul << peri);
}

/**
 * \brief 使能AHB1外设
 *
 * \param[in]  peri ：需要使能的外设
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_ahb1_enable (amhw_zmf159_ahb1_peripheral peri)
{

    ZMF159_RCC->ahb1enr |= (1 << peri);
}

/**
 * \brief 禁能AHB1外设
 *
 * \param[in]  peri ：需要禁能的外设
 *
 * \return 无
 *
 */
am_static_inline
void amhw_zmf159_rcc_ahb1_disable (amhw_zmf159_ahb1_peripheral peri)
{

    ZMF159_RCC->ahb1enr &= ~(1 << peri);
}

/**
 * \brief 使能AHB2外设
 *
 * \param[in]  peri ：需要使能的外设
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_ahb2_enable (amhw_zmf159_ahb2_peripheral peri)
{

    ZMF159_RCC->ahb2enr |= (1 << peri);
}

/**
 * \brief 禁能AHB2外设
 *
 * \param[in]  peri ：需要禁能的外设
 *
 * \return 无
 *
 */
am_static_inline
void amhw_zmf159_rcc_ahb2_disable (amhw_zmf159_ahb2_peripheral peri)
{

    ZMF159_RCC->ahb2enr &= ~(1 << peri);
}

/**
 * \brief 使能AHB3外设
 *
 * \param[in]  peri ：需要使能的外设
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_ahb3_enable (amhw_zmf159_ahb3_peripheral peri)
{

    ZMF159_RCC->ahb3enr |= (1 << peri);
}

/**
 * \brief 禁能AHB3外设
 *
 * \param[in]  peri ：需要禁能的外设
 *
 * \return 无
 *
 */
am_static_inline
void amhw_zmf159_rcc_ahb3_disable (amhw_zmf159_ahb3_peripheral peri)
{

    ZMF159_RCC->ahb3enr &= ~(1 << peri);
}

/**
 * \brief 使能LSI
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_lsi_enable (void)
{

    ZMF159_RCC->csr |= (1ul << 0);
}

/**
 * \brief 禁能LSI
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_lsi_disable (void)
{

    ZMF159_RCC->csr &= ~(1ul << 0);
}

/**
 * \brief 内部低速时钟就绪标志读取
 *
 * \retval TRUE  : 内部 40kHz 振荡器时钟就绪
 * \retval FALSE : 内部 40kHz 振荡器时钟未就绪
 */
am_static_inline
am_bool_t amhw_zmf159_rcc_lsirdy_read (void)
{
    return (am_bool_t)((ZMF159_RCC->csr & (1ul << 1)) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief 获取复位标志
 *
 * \return 复位标志
 */
am_static_inline
uint32_t amhw_zmf159_rcc_reset_flag (void)
{

    return (uint32_t)(ZMF159_RCC->csr & 0xfc000000);
}

/**
 * \brief 清除复位标志
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_reset_flag_clear (void)
{

    ZMF159_RCC->csr |= (1ul << 24);
}
/**
 * \brief 外部低速振荡器使能
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_bdcr_lseon_enable (void)
{

    ZMF159_RCC->bdcr |= (1ul << 0);
}
/**
 * \brief 外部低速振荡器禁能
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_bdcr_lseon_disable (void)
{
    ZMF159_RCC->bdcr &= ~(1ul << 0);
}
/**
 * \brief 外部低速振荡器就绪标志读取
 *
 * \retval TRUE  : 内部 32MHz时钟没有就绪
 * \retval FALSE : 内部 32MHz时钟就绪
 */
am_static_inline
am_bool_t amhw_zmf159_rcc_bdcr_lserdy_read (void)
{
    return (am_bool_t)((ZMF159_RCC->bdcr & 0x2ul) ? AM_TRUE : AM_FALSE);
}

/**
 * \brief 外部低速时钟旁路状态
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_bdcr_lsebyp_set (uint32_t lsebyp)
{
    ZMF159_RCC->bdcr |= (lsebyp << 2);
}
/**
 * \brief 外部低速时钟旁路状态
 *
 * \retval TRUE  : LSE 时钟被旁路
 * \retval FALSE : LSE 时钟未被旁路
 */
am_static_inline
am_bool_t amhw_zmf159_rcc_bdcr_lsebyp_get (void)
{
    return (am_bool_t)((ZMF159_RCC->bdcr & 0x4ul) ? AM_TRUE : AM_FALSE);
}
/**
 * \brief RTC输入时钟选择
 *
 * \param[in]  src ：RTC输入时钟源
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_bdcr_rtc_clk_set (amhw_zmf159_rtc_clk_src src)
{

    ZMF159_RCC->bdcr = ((src & 0x3ul) << 8) |
                              (ZMF159_RCC->bdcr & ~(0x3ul << 8));
}

/**
 * \brief RTC输入时钟获取
 *
 * \retval  rtc时钟源获取
 */
am_static_inline
amhw_zmf159_rtc_clk_src amhw_zmf159_rcc_bdcr_rtc_clk_get (void)
{
    return (amhw_zmf159_rtc_clk_src)((ZMF159_RCC->bdcr >> 8) & 0x3ul);
}

/**
 * \brief RTC时钟使能
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_bdcr_rtc_enable (void)
{

    ZMF159_RCC->bdcr |= (1ul << 15);
}
/**
 * \brief RTC时钟禁能
 *
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_bdcr_rtc_disable (void)
{

    ZMF159_RCC->bdcr &= ~(1ul << 15);
}

/**
 * \brief 备份域软件复位
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_bdcr_bdrst_reset (void)
{

    ZMF159_RCC->bdcr |= (1ul << 16);
}
/**
 * \brief 备份域软件复位结束
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_bdcr_bdrst_reset_end (void)
{

    ZMF159_RCC->bdcr &= ~(1ul << 16);
}
/**
 * \brief 系统配置寄存器flash擦除
 *
 * \param[in] flag flash页擦除时擦除的大小 1：1K字节 0：512字节
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_syscfg_erasure (uint32_t flag)
{

    ZMF159_RCC->syscfg &= (flag << 1);
}
/**
 * \brief 系统配置寄存器flash检查
 *
 * \param[in] flag flash页擦除时是否检查 1：检查 0：不检查
 * \return 无
 */
am_static_inline
void amhw_zmf159_rcc_syscfg_checkout (uint32_t flag)
{

    ZMF159_RCC->syscfg &= (flag << 0);
}

/**
 * @}
 */
/*
 * \brief 匿名结构体段的结束
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif

#ifdef __cplusplus
}
#endif /* __ZMF159_RCC_H */

#endif

/* end of file */
