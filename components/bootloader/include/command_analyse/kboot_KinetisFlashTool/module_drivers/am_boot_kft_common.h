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
 * \brief bootloader kboot KinetisFlashTool 通用工具宏定义头文件
 *
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-10-25  yrh, first implementation
 * \endinternal
 */
#ifndef __AM_BOOT_KFT_COMMON_H
#define __AM_BOOT_KFT_COMMON_H
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include "am_common.h"
#include "am_vdebug.h"

/** \brief Construct a status code value from a group and code number */
#define MAKE_STATUS(group, code) ((((group)*100) + (code)))

/**
 * \brief Status group numbers
 */
enum status_groups
{
    KFT_STATUS_GROUP_GENERIC                 = 0,   /** \brief Group number for generic status codes */
    KFT_STATUS_GROUP_APPLICATION_RANGE_START = 100,   /** \brief Starting number for application groups */
};

/**
 * \brief Generic status return codes
 */
enum generic_status
{
    KFT_STATUS_SUCCESS                 = MAKE_STATUS(KFT_STATUS_GROUP_GENERIC, 0),
    KFT_STATUS_FAIL                    = MAKE_STATUS(KFT_STATUS_GROUP_GENERIC, 1),
    KFT_STATUS_INVALID_ARGUMENT        = MAKE_STATUS(KFT_STATUS_GROUP_GENERIC, 2),
};

/**
 * \brief Type used for all status and error return values
 */
typedef int32_t status_t;


#if !defined(MIN)
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#if !defined(MAX)
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

/** \brief Computes the number of elements in an array */
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))


/**
 * \brief Build a 32-bit code from four character values
 *
 * \note The resulting value is built with a byte order such that the string
 *       being readable in expected order when viewed in a hex editor, if the value
 *       is treated as a 32-bit little endian value.
 */
#define FOUR_CHAR_CODE(a, b, c, d) (((d) << 24) | ((c) << 16) | ((b) << 8) | ((a)))

/**
 * \brief Bootloader status group numbers
 */
enum kft_bl_status_groups
{
    KFT_STATUS_GROUP_BOOTLOADER = KFT_STATUS_GROUP_APPLICATION_RANGE_START, /** \brief Bootloader status group number (100) */
    KFT_STATUS_GROUP_MEMORY_INTERFACE,                                     /** \brief Memory interface status group number (102) */
    KFT_STATUS_GROUP_PROPERTY_STORE,                                       /** \brief Property store status group number (103) */
};


/**
 * \brief Structure of version property
 */
typedef union standard_version
{
    struct
    {
        uint8_t bugfix ; /** \brief bugfix version [7:0] */
        uint8_t minor;  /** \brief minor version [15:8] */
        uint8_t major;  /** \brief major version [23:16] */
        char    name;   /** \brief name [31:24] */
    }ver;
    uint32_t    version;   /** \brief combined version numbers */
} standard_version_t;

#endif /* __AM_BOOT_KFT_COMMON_H */

/* end of file */
