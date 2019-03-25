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
 * \brief MiniPort 用户配置文件
 *
 * \internal
 * \par Modification history
 * - 1.00 17-11-13  pea, first implementation
 * \endinternal
 */

#ifndef __AM_HWCONF_MINIPORT_H
#define __AM_HWCONF_MINIPORT_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "ametal.h"
#include "am_time.h"
#include "am_hc595.h"

/*
 * \brief MiniPort-595 实例初始化
 *
 */
am_hc595_handle_t am_miniport_595_inst_init (void);

/*
 * \brief MiniPort-595 实例初始化
 */
int am_miniport_view_595_inst_init (void);

/*
 * \brief MiniPort-View 单独使用实例初始化
 */
int am_miniport_view_inst_init (void);

/*
 * \brief MiniPort-Key 单独使用实例初始化
 */
int am_miniport_key_inst_init (void);

/*
 * \brief MiniPort-led 单独使用实例初始化
 */
int am_miniport_led_inst_init (void);

/*
 * \brief MiniPort-view-key-595 单独使用实例初始化
 */
int am_miniport_view_key_595_inst_init (void);

/*
 * \brief MiniPort-View 和 MiniPort-Key 联合使用实例初始化
 */
int am_miniport_view_key_inst_init (void);

/*
 * \brief MiniPort-ZLG72128 实例初始化
 */
int am_miniport_zlg72128_inst_init (void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __AM_HWCONF_MINIPORT_H */

/* end of file */
