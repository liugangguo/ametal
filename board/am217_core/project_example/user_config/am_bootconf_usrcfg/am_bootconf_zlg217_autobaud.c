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
 * \brief KL26 自动波特率用户配置文件，实际使用时需要将捕获引脚配置为串口的接收引脚
 * \sa am_hwconf_auto_baudrate.c
 *
 * \internal
 * \par Modification history
 * - 1.00 16-09-13  ipk, first implementation.
 * \endinternal
 */

#include "am_boot_autobaud.h"
#include "ametal.h"
#include "am_zlg217.h"
#include "am_gpio.h"
#include "am_zlg217_inst_init.h"
#include "am_zlg_tim_cap.h"

/**
 * \addtogroup am_if_hwconf_auto_baudrate
 * \copydoc am_hwconf_auto_baudrate.c
 * @{
 */

/** \brief 需要用到的定时器位数 */
#define     TIMER_WIDTH           16

/** \brief 自动波特率的平台初始化 */
void __zlg217_plfm_autobaud_init (void)
{
    amhw_zlg_tim_prescale_set((amhw_zlg_tim_t *)ZLG217_TIM1_BASE, 8);

}

/** \brief 自动波特率的平台解初始化  */
void __zlg217_plfm_autobaud_deinit (void)
{

}

/** \brief 平台捕获定时器溢出标志获取  */
int __fsl_plfm_stat_flag_get (void *parg)
{
    return 0;
}

/** \brief 自动波特率的设备信息实例 */
static am_boot_autobaud_devinfo_t  __g_zlg217_boot_autobaud_devinfo = {

    3,                          /**< \brief CAP捕获通道号 */
    TIMER_WIDTH,                /**< \brief TIMER定时器位数 */
    10,                         /**< \brief 接收一次数据的超时时间(ms)*/

    __zlg217_plfm_autobaud_init,  /**< \brief 平台初始化函数 */
    __zlg217_plfm_autobaud_deinit,/**< \brief 平台解初始化函数 */

    __fsl_plfm_stat_flag_get
};

/** \brief 自动波特率功能的设备实例 */
am_boot_autobaud_dev_t  __g_zlg217_boot_autobaud_dev;

/** \brief 实例初始化，获得自动波特率服务句柄 */
am_boot_autobaud_handle_t am_zlg217_boot_autobaud_inst_init (void)
{
    am_cap_handle_t   cap_handle   = am_zlg217_tim2_cap_inst_init();

    am_zlg_tim_cap_dev_t *p_cap_dev = (am_zlg_tim_cap_dev_t *)cap_handle;

    __g_zlg217_boot_autobaud_dev.cap_pin =
            p_cap_dev->p_devinfo->p_ioinfo[__g_zlg217_boot_autobaud_devinfo.cap_chanel].gpio;

    return am_boot_autobaud_init(&__g_zlg217_boot_autobaud_dev,
                                 &__g_zlg217_boot_autobaud_devinfo,
                                  cap_handle);
}

/** \brief 自动波特率实例解初始化 */
void am_zlg217_boot_autobaud_inst_deinit (am_boot_autobaud_handle_t handle)
{
    am_zlg217_tim1_cap_inst_deinit(handle->cap_handle);

    am_boot_autobaud_deinit(handle);
}

/**
 * @}
 */

/* end of file */




