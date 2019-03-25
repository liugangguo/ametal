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
 * \brief ADC INT 例程，通过 HW 层接口实现
 *
 * - 操作步骤：
 *   1. PIOA_4 (ADC 通道 4) 连接模拟输入。
 *   2. PIOA_5 (ADC 通道 5) 连接模拟输入。
 *
 * - 实验现象：
 *   1. 串口输出电压采样值。
 *
 * \note
 *    1. 使用 ADC 模块功能，必须保证 ADC 模块上电；
 *    2. 需要保证对应通道引脚的初始化注释打开；
 *    3. 如需观察串口打印的调试信息，需要将 PIOA_10 引脚连接 PC 串口的 TXD，
 *       PIOA_9 引脚连接 PC 串口的 RXD。
 *    4. 若用户用户需要添加ADC轮询读取通道的数目，或者变更读取通道的顺序，只需修改
 *       adc_chan[]数组中的通道值即可，注意需要将通道引脚的初始化注释打开。
 *
 * \par 源代码
 * \snippet demo_zmf159_hw_adc_dma.c src_zmf159_hw_adc_dma
 *
 * \internal
 * \par Modification History
 * - 1.00 19-02-28  ipk, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_zmf159_hw_adc_dma
 * \copydoc demo_zmf159_hw_adc_dma.c
 */

/** [src_zmf159_hw_adc_dma] */
#include "ametal.h"
#include "am_vdebug.h"
#include "am_zmf159.h"
#include "am_gpio.h"
#include "am_clk.h"
#include "zmf159_dma_chan.h"
#include "demo_zlg_entries.h"
#include "demo_zmf159_core_entries.h"

#define  __ADC1_DMA_CHAN1         DMA1_CHAN_1 /* ADC对应DMA1通道1 */

/**
 * \brief 例程入口
 */
void demo_zmf159_core_hw_adc_dma_entry (void)
{
    AM_DBG_INFO("demo zmf159_core hw adc dma!\r\n");

    int adc_chan[] = {4, 5};

    /* 运行硬件层例程前的环境设置 ，配置引脚，使能时钟等 */
//    am_gpio_pin_cfg(PIOA_0, PIOA_0_AIN | PIOA_0_ADC_IN0); /* ADC1通道0 */
//    am_gpio_pin_cfg(PIOA_1, PIOA_1_AIN | PIOA_1_ADC_IN1); /* ADC1通道1 */
//    am_gpio_pin_cfg(PIOA_2, PIOA_2_AIN | PIOA_2_ADC_IN2); /* ADC1通道2 */
//    am_gpio_pin_cfg(PIOA_3, PIOA_3_AIN | PIOA_3_ADC_IN3); /* ADC1通道3 */
    am_gpio_pin_cfg(PIOA_4, PIOA_4_AIN | PIOA_4_ADC_IN4); /* ADC1通道4 */
    am_gpio_pin_cfg(PIOA_5, PIOA_5_AIN | PIOA_5_ADC_IN5); /* ADC1通道5 */
//    am_gpio_pin_cfg(PIOA_6, PIOA_6_AIN | PIOA_6_ADC_IN6); /* ADC1通道6 */
//    am_gpio_pin_cfg(PIOA_7, PIOA_7_AIN | PIOA_7_ADC_IN7); /* ADC1通道7 */


    am_clk_enable(CLK_ADC1);

    demo_zlg_hw_adc_dma_entry(ZMF159_ADC1,
                              adc_chan,
                              sizeof(adc_chan)/sizeof(adc_chan[0]),
                              __ADC1_DMA_CHAN1);
}
/** [src_zmf159_hw_adc_dma] */

/* end of file */
