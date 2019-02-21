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
 * \brief ZMF159 SPI 从设备用户配置文件
 * \sa am_hwconf_zmf159_spi_slv_dma.c
 *
 * \internal
 * \par Modification history
 * - 1.00 17-12-07  vir, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "am_zmf159.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "am_zlg_spi_slv_dma.h"
#include "hw/amhw_zlg_spi.h"
#include "zmf159_dma_chan.h"

/**
 * \addtogroup am_if_src_hwconf_zmf159_spi_slv_dma
 * \copydoc am_hwconf_zmf159_spi_slv_dma.c
 * @{
 */

/** \brief SPI1 从设备平台初始化 */
static void __zmf159_spi1_slv_dma_plfm_init (void)
{
    am_gpio_pin_cfg(PIOA_5, PIOA_5_SPI1_SCK | PIOA_5_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOA_6, PIOA_6_SPI1_MISO | PIOA_6_AF_PP );
    am_gpio_pin_cfg(PIOA_7, PIOA_7_SPI1_MOSI | PIOA_7_INPUT_FLOAT);

    am_clk_enable(CLK_SPI1);
}

/** \brief 解除 SPI1 从设备平台初始化 */
static void __zmf159_spi1_slv_dma_plfm_deinit (void)
{
    am_clk_disable(CLK_SPI1);
}

/**
 * \brief SPI1 从设备设备信息
 */
const  am_zlg_spi_slv_dma_devinfo_t __g_spi1_slv_devinfo = {
    ZMF159_SPI1_BASE,                      /* SPI1 寄存器指针 */
    CLK_SPI1,                              /* 时钟 ID 号 */
    DMA_CHAN_SPI1_TX,
    DMA_CHAN_SPI1_RX,
    PIOA_4,
    __zmf159_spi1_slv_dma_plfm_init,       /* SPI1 平台初始化函数 */
    __zmf159_spi1_slv_dma_plfm_deinit      /* SPI1 平台解初始化函数 */
};

/** \brief SPI1 从机设备实例 */
static am_zlg_spi_slv_dma_dev_t __g_spi1_slv_dev;

/** \brief SPI1 从机实例初始化，获得 SPI 从机标准服务句柄 */
am_spi_slv_handle_t am_zmf159_spi1_slv_dma_inst_init (void)
{
    return am_zlg_spi_slv_dma_init(&__g_spi1_slv_dev, &__g_spi1_slv_devinfo);
}

/** \brief SPI1 从设备实例解初始化 */
void am_zmf159_spi1_slv_dma_inst_deinit (am_spi_slv_handle_t handle)
{
    am_zlg_spi_slv_dma_deinit(handle);
}

/*******************************************************************************/

/** \brief SPI2 从设备平台初始化 */
static void __zmf159_spi2_slv_dma_plfm_init (void)
{
    am_gpio_pin_cfg(PIOB_13, PIOB_13_SPI2_SCK | PIOB_13_AF_PP);
    am_gpio_pin_cfg(PIOB_14, PIOB_14_SPI2_MISO | PIOB_14_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOB_15, PIOB_15_SPI2_MOSI  | PIOB_15_INPUT_FLOAT);

    am_clk_enable(CLK_SPI2);
}

/** \brief 解除 SPI1 从设备平台初始化 */
static void __zmf159_spi2_slv_dma_plfm_deinit (void)
{
    am_clk_disable(CLK_SPI2);
}

/**
 * \brief SPI1 从设备设备信息
 */
const am_zlg_spi_slv_dma_devinfo_t __g_spi2_slv_devinfo = {
    ZMF159_SPI2_BASE,                      /* SPI2 寄存器指针   */
    CLK_SPI2,                              /* 时钟 ID 号   */
    DMA_CHAN_SPI2_TX,
    DMA_CHAN_SPI2_RX,
    PIOB_12,
    __zmf159_spi2_slv_dma_plfm_init,       /* SPI2 平台初始化函数 */
    __zmf159_spi2_slv_dma_plfm_deinit      /* SPI2 平台解初始化函数 */
};

/** \brief SPI2 从机设备实例 */
static am_zlg_spi_slv_dma_dev_t __g_spi2_slv_dev;

/** \brief SPI2 从机实例初始化，获得 SPI 从机标准服务句柄 */
am_spi_slv_handle_t am_zmf159_spi2_slv_dma_inst_init (void)
{
    return am_zlg_spi_slv_dma_init(&__g_spi2_slv_dev, &__g_spi2_slv_devinfo);
}

/** \brief SPI1 从设备实例解初始化 */
void am_zmf159_spi2_slv_dma_inst_deinit (am_spi_slv_handle_t handle)
{
    am_zlg_spi_slv_dma_deinit(handle);
}

/*******************************************************************************/

/** \brief SPI3 从设备平台初始化 */
static void __zmf159_spi3_slv_dma_plfm_init (void)
{
    am_gpio_pin_cfg(PIOB_13, PIOB_13_SPI2_SCK | PIOB_13_AF_PP);
    am_gpio_pin_cfg(PIOB_14, PIOB_14_SPI2_MISO | PIOB_14_INPUT_FLOAT);
    am_gpio_pin_cfg(PIOB_15, PIOB_15_SPI2_MOSI  | PIOB_15_INPUT_FLOAT);

    am_clk_enable(CLK_SPI3);
}

/** \brief 解除 SPI3 从设备平台初始化 */
static void __zmf159_spi3_slv_dma_plfm_deinit (void)
{
    am_clk_disable(CLK_SPI3);
}

/**
 * \brief SPI3 从设备设备信息
 */
const am_zlg_spi_slv_dma_devinfo_t __g_spi3_slv_devinfo = {
    ZMF159_SPI3_BASE,                      /* SPI3 寄存器指针   */
    CLK_SPI3,                              /* 时钟 ID 号   */
    DMA_CHAN_SPI3_TX,
    DMA_CHAN_SPI3_RX,
    PIOB_12,
    __zmf159_spi3_slv_dma_plfm_init,       /* SPI3 平台初始化函数 */
    __zmf159_spi3_slv_dma_plfm_deinit      /* SPI3 平台解初始化函数 */
};

/** \brief SPI3 从机设备实例 */
static am_zlg_spi_slv_dma_dev_t __g_spi3_slv_dev;

/** \brief SPI3 从机实例初始化，获得 SPI 从机标准服务句柄 */
am_spi_slv_handle_t am_zmf159_spi3_slv_dma_inst_init (void)
{
    return am_zlg_spi_slv_dma_init(&__g_spi3_slv_dev, &__g_spi3_slv_devinfo);
}

/** \brief SPI3 从设备实例解初始化 */
void am_zmf159_spi3_slv_dma_inst_deinit (am_spi_slv_handle_t handle)
{
    am_zlg_spi_slv_dma_deinit(handle);
}

/**
 * @}
 */

/* end of file */
