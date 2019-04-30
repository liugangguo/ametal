/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief CAT823 WDT drivers implementation
 * 
 * \internal
 * \par Modification history
 * - 1.00 19-04-28  ipk, first implementation.
 * \endinternal
 */
 
#include "am_cat823.h"
#include "am_int.h"
#include "am_clk.h"
#include "am_gpio.h"

/*******************************************************************************
* Functions declaration
*******************************************************************************/

static int __cat823_wdt_feed(void *p_drv);
static int __cat823_wdt_enable(void *p_drv, uint32_t timeout_ms);
static int __cat823_wdt_info_get(void *p_drv, am_wdt_info_t *p_info);

/** \brief wwdt driver functions */
static const struct am_wdt_drv_funcs __g_iwdt_drv_funcs = {
    __cat823_wdt_info_get,
    __cat823_wdt_enable,
    __cat823_wdt_feed,
};

static int __cat823_wdt_info_get(void *p_drv, am_wdt_info_t *p_info)
{
    p_info->min_timeout_ms = 1120;
    p_info->max_timeout_ms = 1120;
    return AM_OK;
}

static int __cat823_wdt_feed(void *p_drv)
{
    am_cat823_dev_t *p_dev = (am_cat823_dev_t *)p_drv;

    am_gpio_toggle(p_dev->p_devinfo->wdi_pin);
    return AM_OK;
}

static int __cat823_wdt_enable(void *p_drv, uint32_t timeout_ms)
{
    am_cat823_dev_t *p_dev = (am_cat823_dev_t *)p_drv;
    if (p_dev->p_devinfo->wdi_pin < 0) {
        return AM_ERROR;
    }
    if(timeout_ms != 1120) {
        return AM_ERROR;
    }

    am_gpio_pin_cfg(p_dev->p_devinfo->wdi_pin, AM_GPIO_OUTPUT_INIT_HIGH);

    return AM_OK;
}

am_wdt_handle_t am_cat823_init (am_cat823_dev_t           *p_dev,
                                const am_cat823_devinfo_t *p_devinfo)
{
    p_dev->p_devinfo        = p_devinfo;
    p_dev->wdt_serv.p_funcs = (struct am_wdt_drv_funcs *)&__g_iwdt_drv_funcs;
    p_dev->wdt_serv.p_drv   = (void *)p_dev;

    /* ¹Ø±Õ¿´ÃÅ¹· */
    am_gpio_pin_cfg(p_dev->p_devinfo->wdi_pin, AM_GPIO_FLOAT);

    return &(p_dev->wdt_serv);
}

void am_cat823_deinit (am_cat823_dev_t *p_dev)
{

}

/* end of file */
