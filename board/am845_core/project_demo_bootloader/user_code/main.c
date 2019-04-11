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
 * \brief LPC84X bootloader工程
 *
 * - 操作步骤：
 *   参考AMmetal-AM845-Core-bootloader操作手册
 *
 * \internal
 * \par Modification history
 * - 1.00 19-03-25  yrh, first implementation
 * \endinternal
 */

#include "ametal.h"
#include "demo_am845_core_entries.h"

/**
 * \brief AMetal 应用程序入口
 */
void am_main (void) 
{ 

   demo_am845_core_bootloader_entry();

}

/* end of file */
