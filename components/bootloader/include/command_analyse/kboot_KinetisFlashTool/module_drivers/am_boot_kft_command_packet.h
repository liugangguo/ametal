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
 * \brief 命令/数据 包常量
 */
enum kft_command_packet_constants
{
    KFT_MIN_PACKET_BUFFER_SIZE = 32,
    KFT_DEFAULT_MAX_PACKET_SIZE = KFT_MIN_PACKET_BUFFER_SIZE,
    /** \brief 属性可返回的最大字数，一个字是标题，一个参数保留给状态  */
    KFT_MAX_PROPERTY_RETURN_VALUES = (KFT_MIN_PACKET_BUFFER_SIZE / sizeof(uint32_t)) - 2,
    /** \brief 程序命令一次可写入最大字数，一个字是头 */
    KFT_MAX_PROGRAM_ONCE_VALUES = (KFT_MIN_PACKET_BUFFER_SIZE / sizeof(uint32_t)) - 3,
    /** \brief 非响应命令标记的数量 */
    KFT_COMMMAND_TAG_COUNT = 12,
};

/** \brief Commands codes */
enum kft_command_tags
{
    KFT_COMMAND_TAG_GENERIC_RESPONSE             = 0xa0,
    KFT_COMMAND_TAG_FLASH_ERASE_ALL              = 0x01,
    KFT_COMMAND_TAG_FLASH_ERASE_REGION           = 0x02,
    KFT_COMMAND_TAG_READ_MEMORY                  = 0x03,
    KFT_COMMAND_TAG_READ_MEMORY_RESPONSE         = 0xa3,
    KFT_COMMAND_TAG_WRITE_MEMORY                 = 0x04,
    KFT_COMMAND_TAG_FILL_MEMORY                  = 0x05,
    KFT_COMMAND_TAG_FLASH_SECURITY_DISABLE       = 0x06,
    KFT_COMMAND_TAG_GET_PROPERTY                 = 0x07,
    KFT_COMMAND_TAG_GET_PROPERTY_RESPONSE        = 0xa7,
    KFT_COMMAND_TAG_RECEIVE_SB_FILE              = 0x08,
    KFT_COMMAND_TAG_EXECUTE                      = 0x09,
    KFT_COMMAND_TAG_CALL                         = 0x0a,
    KFT_COMMAND_TAG_RESET                        = 0x0b,
    KFT_COMMAND_TAG_SET_PROPERTY                 = 0x0c,
    KFT_COMMAND_TAG_FLASH_ERASE_ALL_UNSECURE     = 0x0d,
    KFT_COMMAND_TAG_FLASH_PROGRAM_ONCE           = 0x0e,
    KFT_COMMAND_TAG_FLASH_READ_ONCE              = 0x0f,
    KFT_COMMAND_TAG_FLASH_READ_ONCE_RESPONSE     = 0xaf,
    KFT_COMMAND_TAG_FLASH_READ_RESOURCE          = 0x10,
    KFT_COMMAND_TAG_FLASH_READ_RESOURCE_RESPONSE = 0xb0,
    KFT_COMMAND_TAG_CONFIGURE_QUADSPI            = 0x11,
    KFT_COMMAND_TAG_RELIABLE_UPDATE              = 0x12,

    KFT_COMMAND_TAG_CONFIGURE_I2C                = 0xc1,  /** \brief Reserved command tag for Bus Pal */
    KFT_COMMAND_TAG_CONFIGURE_SPI                = 0xc2,  /** \brief Reserved command tag for Bus Pal */
    KFT_COMMAND_TAG_CONFIGURE_CAN                = 0xc3,  /** \brief Reserved command tag for Bus Pal */

    KFT_FIRST_COMMAND_TAG                         = KFT_COMMAND_TAG_FLASH_ERASE_ALL,
    /** \brief Maximum linearly incrementing command tag value, excluding the response commands and bus pal commands */
    KFT_LAST_COMMAND_TAG                          = KFT_COMMAND_TAG_RELIABLE_UPDATE,
    /** \brief Mask for the high nibble of a command tag that identifies it as a response command. */
    KFT_RESPONSE_COMMAND_HIGH_NIBBLE_MASK         = 0xa0
};


/** \brief Command packet flags */
enum command_packet_flags
{
    KFT_COMMAND_FLAG_NONE = 0,
    KFT_COMMAND_FLAG_HAS_DATA_PHASE = 1
};

/** \brief Flash memory identifiers */
enum flash_mem_id
{
    KFT_FLASH_MEM_INTERNAL     = 0,
    KFT_FLASH_MEM_QUAD_SPI0    = 1,
    KFT_FLASH_MEM_EXECUTE_ONLY = 0x10
};

/** \brief Command packet format */
typedef struct command_packet
{
    uint8_t command_tag;     /** \brief A command tag */
    uint8_t flags;          /** \brief Combination of packet flags */
    uint8_t reserved;       /** \brief Reserved, helpful for alignment, set to zero */
    uint8_t parameter_count; /** \brief Number of parameters that follow in buffer */
} command_packet_t;


/** \brief FlashEraseAll packet format */
typedef struct flashErase_all_packet
{
    command_packet_t command_packet; /** \brief header */
    uint32_t         memory_id;      /** \brief Paremeter 0: Flash memory identifiers */
} flash_erase_all_packet_t;

/** \brief FlashEraseRegion packet format */
typedef struct flash_erase_region_packet
{
    command_packet_t command_packet;    /** \brief header */
    uint32_t         start_address;     /** \brief Paremeter 0: start address */
    uint32_t         byte_count;        /** \brief Parameter 1: number of bytes */
} flash_erase_region_packet_t;


/**
 * \brief GetProperty packet format
 */
typedef struct get_property_packet
{
    command_packet_t command_packet; /** \brief header */
    uint32_t         property_tag;   /** \brief  Parameter 0: requested property tag */
    uint32_t         memory_id;      /** \brief Parameter 1: requested property for certain external memory */
} get_property_packet_t;


/**
 * \brief SetProperty packet format
 */
typedef struct set_property_packet
{
    command_packet_t command_packet; /** \brief header */
    uint32_t         property_tag;   /** \brief Paremeter 0: property tag */
    uint32_t         property_value; /** \brief Parameter 1: value to set */
} set_property_packet_t;

/**
 * \brief ReceiveSbFile packet format
 */
typedef struct receive_Sb_file_packet
{
    command_packet_t command_packet; /** \brief header */
    uint32_t         byte_count;     /** \brief Parameter 0: Number of bytes to receive */
} receive_sb_file_packet_t;

/**
 * \brief WriteMemory packet format
 */
typedef struct write_memory_packet
{
    command_packet_t command_packet; /** \brief header */
    uint32_t         start_address;  /** \brief Paremeter 0: Start address of memory to write to */
    uint32_t         byte_count;     /** \brief Parameter 1: Number of bytes to write */
} write_memory_packet_t;

/**
 * \brief ReadMemory packet format
 */
typedef struct read_memory_packet
{
    command_packet_t command_packet; /** \brief header */

    /** \brief Paremeter 0: Start address of memory to read from */
    uint32_t         start_address;

    uint32_t         byte_count;     /** \brief Parameter 1: Number of bytes to read */
} read_memory_packet_t;

/**
 * \brief FillMemory packet format
 */
typedef struct fill_memory_packet
{
    command_packet_t command_packet; /** \brief header */
    uint32_t         start_address;  /** \brief Paremeter 0: start address */
    uint32_t         byte_count;     /** \brief Parameter 1: number of bytes */
    uint32_t         pattern_word;   /** \brief Parameter 1: pattern word. */
} fill_memory_packet_t;

/**
 * \brief Execute/Call command function pointer definition
 */
typedef status_t (*call_function_t)(uint32_t);

/**
 * \brief Execute/Call packet format.
 */
typedef struct execute_call_packet
{
    command_packet_t command_packet; /** \brief header */
    uint32_t         call_address;   /** \brief Paremeter 0: function address */
    uint32_t         argument_word;  /** \brief Parameter 1: argument */
    uint32_t         stackpointer;   /** \brief Parameter 2: stack pointer */
} execute_call_packet_t;

/**
 * \brief FlashSecurityDisable packet format.
 */
typedef struct flash_security_disable_packet
{
    command_packet_t command_packet; /** \brief header */
    uint32_t         key_low;        /** \brief Paremeter 0: key bytes 0-3 */
    uint32_t         key_high;       /** \brief Parameter 1: key bytes 4-7 */
} flash_security_disable_packet_t;

/**
 * \brief FlashProgramOnce packet format
 */
typedef struct program_once_packet
{
    command_packet_t command_packet; /** \brief header */
    uint32_t         index;          /** \brief Parameter 0: index of pragram once field */
    uint32_t         byte_count;     /** \brief Parameter 1: number of bytes */
    /** \brief Parameter 2: data to be programmed */
    uint32_t         data[KFT_MAX_PROGRAM_ONCE_VALUES];
} flash_program_once_packet_t;

/**
 * \brief FlashReadOnce packet format
 */
typedef struct read_once_packet
{
    command_packet_t command_packet; /** \brief header */
    uint32_t         index;          /** \brief Parameter 0: index of pragram once field to be read */
    uint32_t         byte_count;     /** \brief Parameter 1: number of bytes */
} flash_read_once_packet_t;

/**
 * \brief FlashReadResource packet format
 */
typedef struct flash_read_resource_packet
{
    command_packet_t command_packet; /** \brief header */
    uint32_t         start_address;  /** \brief Parameter 0: start address */
    uint32_t         byte_count;     /** \brief Parameter 1: number of bytes */
    uint32_t         option;         /** \brief Parameter 2: option for  flash read resource command */
} flash_read_resource_packet_t;

/**
 * \brief ConfigureQuadSpi packet format
 */
typedef struct configure_quad_spi_packet
{
    command_packet_t command_packet;      /** \brief header */
    uint32_t         flash_mem_id;        /** \brief Parameter 0: quadspi ID */
    uint32_t         config_block_address;/** \brief Parameter 1: address of config block to use */
} configure_quadspi_packet_t;

/**
 * \brief ReliableUpdate packet format
 */
typedef struct reliable_update_packet
{
    command_packet_t command_packet; /** \brief header */

    /** \brief Parameter 0: For software implementation ,
     * this is backup app start address .
     * Parameter 0: For hardware implementation , this
     * is swap indicator address
     * */
    uint32_t         address;
} reliable_update_packet_t;

/**
 * \brief ConfigureI2c packet format
 */
typedef struct configure_I2c_packet
{
    command_packet_t command_packet; /** \brief header */
    uint32_t         address;        /** \brief Parameter 0: address */
    uint32_t         speed;          /** \brief Parameter 1: spee */
} configure_i2c_packet_t;



/**
 * \brief ConfigureSpi packet format
 */
typedef struct configure_spi_packet
{
    command_packet_t command_packet; /** \brief header */
    uint32_t         speed_khz;      /** \brief Parameter 0: spped Khz */
    uint32_t         polarity;       /** \brief Parameter 1: polarity */
    uint32_t         phase;          /** \brief Parameter 2: phase */
    uint32_t         direction;      /** \brief Parameter 3: directionpolarity */
} configure_spi_packet_t;

/**
 * \brief ConfigureCan packet format
 */
typedef struct configure_can_packet
{
    command_packet_t command_packet; /** \brief header */
    uint32_t         speed;          /** \brief Parameter 0: spped index */
    uint32_t         txid;           /** \brief Parameter 1: txid */
    uint32_t         rxid;           /** \brief Parameter 2: rxid */
} configure_can_packet_t;

/**
 * \brief  Generic response packet format
 */
typedef struct generic_response_packet
{
    command_packet_t command_packet; /** \brief header */
    uint32_t         status;        /** \brief parameter 0 */
    uint32_t         command_tag;    /** \brief parameter 1 */
} generic_response_packet_t;


typedef struct get_property_response_packet
{
    command_packet_t command_packet;    /** \brief header */
    uint32_t         status;           /** \brief parameter 0 */
    /** \brief up to 6 other parameters*/
    uint32_t         property_value[KFT_MAX_PROGRAM_ONCE_VALUES];
} get_property_response_packet_t;

/**
 * \brief Read Memory response packet format
 */
typedef struct read_memory_response_packet
{
    command_packet_t command_packet;   /** \brief header */
    uint32_t         status;           /** \brief parameter 0 */
    uint32_t         data_byte_count;  /** \brief parameter 1 */
} read_memory_response_packet_t;

/**
 * \brief Flash Read Once response packet format
 */
typedef struct flash_readOnce_response_packet
{
    command_packet_t command_packet;                    /** \brief header */
    uint32_t         status;                            /** \brief parameter 0 */
    uint32_t         byte_count;                        /** \brief parameter 1 */
    uint32_t         data[KFT_MAX_PROGRAM_ONCE_VALUES]; /** \brief parameter 2 */
} flash_read_once_response_packet_t;
/** \brief  */

/**
 * \brief Flash Read Resource response packet format.
 */
typedef struct flash_read_resource_response_packet
{
    command_packet_t command_packet;  /** \brief header */
    uint32_t         status;          /** \brief parameter 0 */
    uint32_t         data_byte_count; /** \brief parameter 1 */
} flash_read_resource_response_packet_t;



#endif /* __AM_BOOT_KFT_COMMAND_PACKET_H */

/* end of file */
