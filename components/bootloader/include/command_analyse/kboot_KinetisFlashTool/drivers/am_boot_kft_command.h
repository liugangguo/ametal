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
 * \brief bootloader kboot KinetisFlashTool 命令解析模块
 *
 * 主要是通过状态解析上位机KinetisFlashTool发送过来的的packet，packet包含命令，通过命令执行相应的handle函数
 *
 * \internal
 * \par Modification history
 * - 1.00 18-10-25  yrh, first implementation
 * \endinternal
 */
#ifndef __AM_BOOT_KFT_COMMAND_H
#define __AM_BOOT_KFT_COMMAND_H

#include "am_boot_kft_common.h"
#include "am_boot_kft_serial_packet.h"
#include "am_boot_kft_property.h"
#include "am_boot_memory.h"
#include "am_boot.h"

typedef struct am_boot_kft_command_dev  am_boot_kft_command_dev_t;

/**
 * \name 命令状态机状态
 * @{
 */
#define  AM_BOOT_KFT_COMMAND_STATE_COMMAND_PHASE  0   /** \BRIEF 命令阶段 */
#define  AM_BOOT_KFT_COMMAND_STATE_DATA_PHASE     1   /** \brief 数据阶段 */
/** @} */


/**
 * \brief 命令处理程序条目的形式
 */
typedef struct am_boot_kft_command_handler_entry
{
    /** \brief command dispose */
    void     (*pfn_handle_Command) (am_boot_kft_command_dev_t *p_dev,
                                    uint8_t                   *p_packet,
                                    uint32_t                   packet_length);

    /** \brief date dispose */
    int32_t (*pfn_handle_Data) (am_boot_kft_command_dev_t *p_dev,
                                am_bool_t                 *p_has_more_data);
} am_boot_kft_command_handler_entry_t;


/**
 * \brief 命令处理器数据格式
 */
typedef struct am_boot_kft_command_processor_data
{
    int32_t      state;                /** \brief 当前状态机状态  */
    uint8_t     *p_packet;             /** \brief 指向正在处理的数据包的指针  */
    uint32_t     packet_length;        /** \brief 正在处理的包的长度  */
    struct data_phase {
        uint8_t *p_data;               /** \brief 数据阶段的数据  */
        uint32_t count;                /** \brief 剩余计数生产/消费  */
        uint32_t address;              /** \brief 数据阶段的地址  */
        uint32_t data_bytes_available; /** \brief 数据指针可用的字节数 */
        uint8_t  command_tag;          /** \brief 运行数据阶段的命令标志  */
        uint8_t  option;               /** \brief 特殊命令选项  */
    } data_phase;
    /** \brief 指向正在处理的数据包的树立程序表条目的指针  */
    const am_boot_kft_command_handler_entry_t *p_handler_entry;
}am_boot_kft_command_processor_data_t;

struct am_boot_kft_command_funcs {
    int32_t   (*pfn_pump)(void *p_arg);
};

typedef struct am_boot_kft_command_serv {
    struct am_boot_kft_command_funcs *p_funcs;
    void                             *p_drv;
}am_boot_kft_command_serv_t;

typedef am_boot_kft_command_serv_t *am_boot_kft_command_handle_t;

typedef struct am_boot_kft_command_dev {
    am_boot_kft_command_serv_t            command_serv;
    am_boot_kft_command_handler_entry_t  *p_handler_table;
    am_boot_kft_command_processor_data_t  state_data;
    am_boot_kft_packet_handle_t           packet_handle;
    am_boot_kft_property_handle_t         property_handle;
    am_boot_mem_handle_t                  memory_handle;
    am_boot_flash_handle_t                flash_handle;
}am_boot_kft_command_dev_t;

/**
 * \brief bootloader 命令模块初始化
 */
am_boot_kft_command_handle_t am_boot_kft_command_init(am_boot_kft_packet_handle_t   packet_handle,
                                                      am_boot_mem_handle_t          memory_handle,
                                                      am_boot_kft_property_handle_t property_handle,
                                                      am_boot_flash_handle_t        flash_handle);


#endif /* __AM_BOOT_KFT_COMMAND_H */

/* end of file */
