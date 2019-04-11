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
 * \brief bootloader kboot KinetisFlashTool 不同类型的命令包声明
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-10-25  yrh, first implementation
 * \endinternal
 */
#ifndef __AM_BOOT_KFT_COMMAND_PACKET_H
#define __AM_BOOT_KFT_COMMAND_PACKET_H
#include "am_boot_kft_common.h"

/**
 * \name 命令/数据 包常量
 * @{
 */
#define  AM_BOOT_KFT_MIN_PACKET_BUFFER_SIZE       32
#define  AM_BOOT_KFT_DEFAULT_MAX_PACKET_SIZE      AM_BOOT_KFT_MIN_PACKET_BUFFER_SIZE
/** \brief 属性可返回的最大字数，一个字是标题，一个参数保留给状态  */
#define  AM_BOOT_KFT_MAX_PROPERTY_RETURN_VALUES ((AM_BOOT_KFT_MIN_PACKET_BUFFER_SIZE \
                                                  / sizeof(uint32_t)) - 2)
/** \brief 程序命令一次可写入最大字数，一个字是头 */
#define  AM_BOOT_KFT_MAX_PROGRAM_ONCE_VALUES    ((AM_BOOT_KFT_MIN_PACKET_BUFFER_SIZE \
                                                  / sizeof(uint32_t)) - 3)
/** \brief 非响应命令标记的数量 */
#define  AM_BOOT_KFT_COMMMAND_TAG_COUNT           12
/** @} */


/**
 * \name Command packet flags
 * @{
 */
#define  AM_BOOT_KFT_COMMAND_FLAG_NONE             0
#define  AM_BOOT_KFT_COMMAND_FLAG_HAS_DATA_PHASE   1

/** @} */

/**
 * \name Flash memory identifiers
 * @{
 */
#define  AM_BOOT_KFT_FLASH_MEM_INTERNAL      0
#define  AM_BOOT_KFT_FLASH_MEM_QUAD_SPI0     1
#define  AM_BOOT_KFT_FLASH_MEM_EXECUTE_ONLY  0x10
/** @} */

/** \brief Commands codes */
enum am_boot_kft_command_tags
{
    AM_BOOT_KFT_COMMAND_TAG_GENERIC_RESPONSE             = 0xa0,
    AM_BOOT_KFT_COMMAND_TAG_FLASH_ERASE_ALL              = 0x01,
    AM_BOOT_KFT_COMMAND_TAG_FLASH_ERASE_REGION           = 0x02,
    AM_BOOT_KFT_COMMAND_TAG_READ_MEMORY                  = 0x03,
    AM_BOOT_KFT_COMMAND_TAG_READ_MEMORY_RESPONSE         = 0xa3,
    AM_BOOT_KFT_COMMAND_TAG_WRITE_MEMORY                 = 0x04,
    AM_BOOT_KFT_COMMAND_TAG_FILL_MEMORY                  = 0x05,
    AM_BOOT_KFT_COMMAND_TAG_FLASH_SECURITY_DISABLE       = 0x06,
    AM_BOOT_KFT_COMMAND_TAG_GET_PROPERTY                 = 0x07,
    AM_BOOT_KFT_COMMAND_TAG_GET_PROPERTY_RESPONSE        = 0xa7,
    AM_BOOT_KFT_COMMAND_TAG_RECEIVE_SB_FILE              = 0x08,
    AM_BOOT_KFT_COMMAND_TAG_EXECUTE                      = 0x09,
    AM_BOOT_KFT_COMMAND_TAG_CALL                         = 0x0a,
    AM_BOOT_KFT_COMMAND_TAG_RESET                        = 0x0b,
    AM_BOOT_KFT_COMMAND_TAG_SET_PROPERTY                 = 0x0c,
    AM_BOOT_KFT_COMMAND_TAG_FLASH_ERASE_ALL_UNSECURE     = 0x0d,
    AM_BOOT_KFT_COMMAND_TAG_FLASH_PROGRAM_ONCE           = 0x0e,
    AM_BOOT_KFT_COMMAND_TAG_FLASH_READ_ONCE              = 0x0f,
    AM_BOOT_KFT_COMMAND_TAG_FLASH_READ_ONCE_RESPONSE     = 0xaf,
    AM_BOOT_KFT_COMMAND_TAG_FLASH_READ_RESOURCE          = 0x10,
    AM_BOOT_KFT_COMMAND_TAG_FLASH_READ_RESOURCE_RESPONSE = 0xb0,
    AM_BOOT_KFT_COMMAND_TAG_CONFIGURE_QUADSPI            = 0x11,
    AM_BOOT_KFT_COMMAND_TAG_RELIABLE_UPDATE              = 0x12,
    /** \brief Reserved command tag for Bus Pal */
    AM_BOOT_KFT_COMMAND_TAG_CONFIGURE_I2C                = 0xc1,
    /** \brief Reserved command tag for Bus Pal */
    AM_BOOT_KFT_COMMAND_TAG_CONFIGURE_SPI                = 0xc2,
    /** \brief Reserved command tag for Bus Pal */
    AM_BOOT_KFT_COMMAND_TAG_CONFIGURE_CAN                = 0xc3,

    /** \brief Mask for the high nibble of a command tag that identifies it as a response command. */
    AM_BOOT_KFT_RESPONSE_COMMAND_HIGH_NIBBLE_MASK        = 0xa0,

    AM_BOOT_KFT_FIRST_COMMAND_TAG = AM_BOOT_KFT_COMMAND_TAG_FLASH_ERASE_ALL,
    /** \brief Maximum linearly incrementing command tag value, excluding the response commands and bus pal commands */
    AM_BOOT_KFT_LAST_COMMAND_TAG  = AM_BOOT_KFT_COMMAND_TAG_RELIABLE_UPDATE,

};

/** \brief Command packet format */
typedef struct am_boot_kft_command_packet
{
    uint8_t command_tag;     /** \brief A command tag */
    uint8_t flags;           /** \brief Combination of packet flags */
    uint8_t reserved;        /** \brief Reserved, helpful for alignment, set to zero */
    uint8_t parameter_count; /** \brief Number of parameters that follow in buffer */
} am_boot_kft_command_packet_t;


/** \brief FlashEraseAll packet format */
typedef struct am_boot_kft_flashErase_all_packet
{
    /** \brief header */
    am_boot_kft_command_packet_t command_packet;

    /** \brief Paremeter 0: Flash memory identifiers */
    uint32_t                     memory_id;
} am_boot_kft_flash_erase_all_packet_t;

/** \brief FlashEraseRegion packet format */
typedef struct am_boot_kft_flash_erase_region_packet
{
    am_boot_kft_command_packet_t command_packet;    /** \brief header */
    uint32_t                     start_address;     /** \brief Paremeter 0: start address */
    uint32_t                     byte_count;        /** \brief Parameter 1: number of bytes */
} am_boot_kft_flash_erase_region_packet_t;


/**
 * \brief GetProperty packet format
 */
typedef struct am_boot_kft_get_property_packet
{
    /** \brief header */
    am_boot_kft_command_packet_t command_packet;

    /** \brief  Parameter 0: requested property tag */
    uint32_t                     property_tag;

    /** \brief Parameter 1: requested property for certain external memory */
    uint32_t                     memory_id;
} am_boot_kft_get_property_packet_t;


/**
 * \brief SetProperty packet format
 */
typedef struct am_boot_kft_set_property_packet
{
    /** \brief header */
    am_boot_kft_command_packet_t command_packet;

    /** \brief Paremeter 0: property tag */
    uint32_t                     property_tag;

    /** \brief Parameter 1: value to set */
    uint32_t                     property_value;
} am_boot_kft_set_property_packet_t;

/**
 * \brief WriteMemory packet format
 */
typedef struct am_boot_kft_write_memory_packet
{
    /** \brief header */
    am_boot_kft_command_packet_t command_packet;

    /** \brief Paremeter 0: Start address of memory to write to */
    uint32_t                     start_address;

    /** \brief Parameter 1: Number of bytes to write */
    uint32_t                     byte_count;
} am_boot_kft_write_memory_packet_t;

/**
 * \brief ReadMemory packet format
 */
typedef struct am_boot_kft_read_memory_packet
{
    /** \brief header */
    am_boot_kft_command_packet_t command_packet;

    /** \brief Paremeter 0: Start address of memory to read from */
    uint32_t                     start_address;

    /** \brief Parameter 1: Number of bytes to read */
    uint32_t                     byte_count;
} am_boot_kft_read_memory_packet_t;

/**
 * \brief FillMemory packet format
 */
typedef struct am_boot_kft_fill_memory_packet
{
    /** \brief header */
    am_boot_kft_command_packet_t command_packet;

    /** \brief Paremeter 0: start address */
    uint32_t                     start_address;

    /** \brief Parameter 1: number of bytes */
    uint32_t                     byte_count;

    /** \brief Parameter 1: pattern word. */
    uint32_t                     pattern_word;
} am_boot_kft_fill_memory_packet_t;

/**
 * \brief Execute/Call command function pointer definition
 */
typedef int32_t (*call_function_t)(uint32_t);

/**
 * \brief Execute/Call packet format.
 */
typedef struct am_boot_kft_execute_call_packet
{
    /** \brief header */
    am_boot_kft_command_packet_t command_packet;

    /** \brief Paremeter 0: function address */
    uint32_t                     call_address;

    /** \brief Parameter 1: argument */
    uint32_t                     argument_word;

    /** \brief Parameter 2: stack pointer */
    uint32_t                     stackpointer;
} am_boot_kft_execute_call_packet_t;

/**
 * \brief FlashSecurityDisable packet format.
 */
typedef struct am_boot_kft_flash_security_disable_packet
{
    /** \brief header */
    am_boot_kft_command_packet_t command_packet;

    /** \brief Paremeter 0: key bytes 0-3 */
    uint32_t                     key_low;

    /** \brief Parameter 1: key bytes 4-7 */
    uint32_t                     key_high;
} am_boot_kft_flash_security_disable_packet_t;

/**
 * \brief FlashReadResource packet format
 */
typedef struct am_boot_kft_flash_read_resource_packet
{
    /** \brief header */
    am_boot_kft_command_packet_t command_packet;

    /** \brief Parameter 0: start address */
    uint32_t                     start_address;

    /** \brief Parameter 1: number of bytes */
    uint32_t                     byte_count;

    /** \brief Parameter 2: option for  flash read resource command */
    uint32_t                     option;
} am_boot_kft_flash_read_resource_packet_t;

/**
 * \brief  Generic response packet format
 */
typedef struct am_boot_kft_generic_response_packet
{
    /** \brief header */
    am_boot_kft_command_packet_t command_packet;

    /** \brief parameter 0 */
    uint32_t                     status;

    /** \brief parameter 1 */
    uint32_t                     command_tag;
} am_boot_kft_generic_response_packet_t;


typedef struct am_boot_kft_get_property_response_packet
{
    /** \brief header */
    am_boot_kft_command_packet_t command_packet;

    /** \brief parameter 0 */
    uint32_t                     status;

    /** \brief up to 6 other parameters*/
    uint32_t                     property_value[AM_BOOT_KFT_MAX_PROGRAM_ONCE_VALUES];
} am_boot_kft_get_property_response_packet_t;

/**
 * \brief Read Memory response packet format
 */
typedef struct am_boot_kft_read_memory_response_packet
{
    /** \brief header */
    am_boot_kft_command_packet_t command_packet;

    /** \brief parameter 0 */
    uint32_t                     status;

    /** \brief parameter 1 */
    uint32_t                     data_byte_count;
} am_boot_kft_read_memory_response_packet_t;

/**
 * \brief Flash Read Once response packet format
 */
typedef struct am_boot_kft_flash_readOnce_response_packet
{
    /** \brief header */
    am_boot_kft_command_packet_t command_packet;

    /** \brief parameter 0 */
    uint32_t                     status;

    /** \brief parameter 1 */
    uint32_t                     byte_count;

    /** \brief parameter 2 */
    uint32_t                     data[AM_BOOT_KFT_MAX_PROGRAM_ONCE_VALUES];
} am_boot_kft_flash_read_once_response_packet_t;

/**
 * \brief Flash Read Resource response packet format.
 */
typedef struct am_boot_kft_flash_read_resource_response_packet
{
    /** \brief header */
    am_boot_kft_command_packet_t command_packet;

    /** \brief parameter 0 */
    uint32_t                     status;

    /** \brief parameter 1 */
    uint32_t                     data_byte_count;
} am_boot_kft_flash_read_resource_response_packet_t;

#endif /* __AM_BOOT_KFT_COMMAND_PACKET_H */

/* end of file */
