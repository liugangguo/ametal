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
 * \brief bootloader kboot KinetisFlashTool 属性
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-10-25  yrh, first implementation
 * \endinternal
 */
#ifndef __AM_BOOT_KFT_PROPERTY_H
#define __AM_BOOT_KFT_PROPERTY_H

#include <stdint.h>
#include "am_boot_kft_command_packet.h"
#include "am_boot_kft_serial_packet.h"
#include "am_boot_kft_serial_packet.h"
#include "am_boot_flash.h"

/**
 * \name Property store status codes
 * @{
 */
#define  AM_BOOT_KFT_STATUS_UNKNOWN_PROPERTY       AM_BOOT_KFT_MAKE_STATUS(AM_BOOT_KFT_STATUS_GROUP_PROPERTY_STORE, 0)
#define  AM_BOOT_KFT_STATUS_READONLY_PROPERTY      AM_BOOT_KFT_MAKE_STATUS(AM_BOOT_KFT_STATUS_GROUP_PROPERTY_STORE, 1)
#define  AM_BOOT_KFT_STATUS_INVALID_PROPERTY_VALUE AM_BOOT_KFT_MAKE_STATUS(AM_BOOT_KFT_STATUS_GROUP_PROPERTY_STORE, 2)
/** @} */


/**
 * \brief Property tags
 *
 * \note Do not change any tag values. Add tags at the end
 */
enum am_boot_kft_property_tag
{
    AM_BOOT_KFT_PROPERTY_TAG_BOOTLOADER_VERSION     = 0x01,
    AM_BOOT_KFT_PROPERTY_TAG_AVAILABLE_PERIPHERALS  = 0x02,
    AM_BOOT_KFT_PROPERTY_TAG_FLASH_START_ADDRESS    = 0x03,
    AM_BOOT_KFT_PROPERTY_TAG_FLASH_SIZE_IN_BYTES    = 0x04,
    AM_BOOT_KFT_PROPERTY_TAG_FLASH_SECTOR_SIZE      = 0x05,
    AM_BOOT_KFT_PROPERTY_TAG_FLASH_BLOCK_COUNT      = 0x06,
    AM_BOOT_KFT_PROPERTY_TAG_AVAILABLE_COMMANDS     = 0x07,
    AM_BOOT_KFT_PROPERTY_TAG_VERIFY_WRITES          = 0x0a,
    AM_BOOT_KFT_PROPERTY_TAG_MAX_PACKET_SIZE        = 0x0b,
    AM_BOOT_KFT_PROPERTY_TAG_RESERVED_REGIONS       = 0x0c,
    AM_BOOT_KFT_PROPERTY_TAG_RAM_START_ADDRESS      = 0x0e,
    AM_BOOT_KFT_PROPERTY_TAG_RAM_SIZE_IN_BYTES      = 0x0f,
    AM_BOOT_KFT_PROPERTY_TAG_FLASH_SECURITY_STATE   = 0x11,
    AM_BOOT_KFT_PROPERTY_TAG_FLASH_READ_MARGIN      = 0x16,
    AM_BOOT_KFT_PROPERTY_TAG_TARGET_VERSION         = 0x18,
    AM_BOOT_KFT_PROPERTY_TAG_RELIABLE_UPDATE_STATUS = 0x1a,
    AM_BOOT_KFT_PROPERTY_TAG_INVALID_PROPERTY       = 0xFF,
};

/**
 * \name Property constants
 * @{
 */
#define  AM_BOOT_KFT_PROPERTY_RESERVED_REGIONS_COUNT          2
#define  AM_BOOT_KFT_PROPERTY_FLASH_RESERVED_REGION_INDEX     0
#define  AM_BOOT_KFT_PROPERTY_RAM_RESERVED_REGION_INDEX       1
#define  AM_BOOT_KFT_PROPERTY_FLASH_VERSION_ID_SIZE_IN_BYTES  8
/** @} */

#define  __RAM_COUNT               1

/**
 * \name Memory Map index constants
 * @{
 */
#define  AM_BOOT_KFT_INDEX_FLASH  0
#define  AM_BOOT_KFT_INDEX_RAM    1
/** @} */

/**
 * \name property_store_tags
 * @{
 */
/** \brief Tag value used to validate the bootloader configuration data. */
#define  AM_BOOT_KFT_PROPERTY_STORE_TAG  AM_BOOT_KFT_FOUR_CHAR_CODE('k', 'c', 'f', 'g')
/** @} */

/**
 * \brief  Format of bootloader configuration data on Flash
 */
typedef struct am_boot_kft_configuration_data
{
    /** \brief [00:03] Tag value used to validate the bootloader
     *  configuration data. Must be set to 'kcfg'.
     */
    uint32_t  tag;

    /** \brief [04:07] */
    uint32_t  crc_start_address;

    /** \brief [08:0b] */
    uint32_t  crc_byte_count;

    /** \brief [0c:0f] */
    uint32_t  crc_expected_value;

    /** \brief [10:10] */
    uint8_t   enabled_peripherals;

    /** \brief [11:11] */
    uint8_t   i2c_slave_address;

    /** \brief [12:13] Timeout in milliseconds for peripheral detection before jumping */
    uint16_t  peripheral_detection_timeout_ms;

    /** \brief [14:15] */
    uint16_t  usb_vid;

    /** \brief [16:17] */
    uint16_t  usb_pid;

    /** \brief [18:1b]  */
    uint32_t  usb_strings_pointer;

    /** \brief [1c:1c] High Speed and other clock options*/
    uint8_t   clock_flags;

    /** \brief [1d:1d] One's complement of clock divider, zero divider is divide by 1 */
    uint8_t   clock_divider;

    /** \brief [1e:1e] One's complemnt of direct boot flag, 0xFE represents direct boot */
    uint8_t   boot_Flags;

    /** \brief [1f:1f] Reserved, set to 0xFF */
    uint8_t   pad0;

    /** \brief [20:23] Holds a pointer value to the MMCAU configuration */
    uint32_t  mmcau_config_pointer;

    /** \brief [24:27] Holds a pointer value to the key blob array used to configure OTFAD */
    uint32_t  key_blob_pointer;

    /** \brief [28:28] reserved */
    uint8_t   pad1;
    /** \brief [29:29] ClkSel[1], PropSeg[3], SpeedIndex[4] */
    uint8_t   can_config1;

    /** \brief [2a:2b] Pdiv[8], Pseg1[3], Pseg2[3],  rjw[2] */
    uint16_t  can_config2;

    /** \brief [2c:2d] txId */
    uint16_t  can_tx_id;

    /** \brief [2e:2f] rxId */
    uint16_t  can_rx_id;

    /** \brief [30:33] QSPI config block pointer */
    uint32_t  qspi_config_block_pointer;
} am_boot_kft_configuration_data_t;

/**
 * \brief Structure of a reserved regions entry
 */
typedef struct am_boot_kft_reserved_region
{
    uint32_t start_address;
    uint32_t end_address;
} am_boot_kft_reserved_region_t;

/**
 * \brief Structure of property store
 */
typedef struct am_boot_kft_property_store
{
    /** \brief Current bootloader version */
    am_boot_kft_standard_version_t  bootloader_version;

    /** \brief Serial protocol version number */
    am_boot_kft_standard_version_t  serial_protocol_version;

    /** \brief Target version number */
    am_boot_kft_standard_version_t  target_version;

    /** \brief Start address of program flash. */
    uint32_t                        flash_start_address;

    /** \brief Size in bytes of program flash. */
    uint32_t                        flash_size_in_bytes;

    /** \brief The size in bytes of one sector of program flash. This is the minimum erase size. */
    uint32_t                        flash_sector_size;

    /** \brief The size in bytes of one block of program flash */
    uint32_t                        flash_block_size;

    /** \brief Number of blocks in the flash array */
    uint32_t                        flash_block_count;

    /** \brief Start address of RAM */
    uint32_t                        ram_start_address[__RAM_COUNT];

    /** \brief Size in bytes of RAM */
    uint32_t                        ram_size_in_bytes[__RAM_COUNT];

    /** \brief Status code from the last CRC check operation. */
    uint32_t                        crc_check_status;

    /** \brief Boolean controlling whether the bootloader will verify writes to flash. Non-zero enables */
    uint32_t                        verify_writes;

    /** \brief verificaton. Writable by host */
    uint32_t                        available_commands;

    /** \brief The margin level setting for flash erase and program Verify CMDs */
    uint32_t                        flash_read_margin;
    /** \brief Result of QSPI+OTFAD init during bootloader startup */
    uint32_t                        qspi_init_status;

    /** \brief Flash and Ram reserved regions. */
    am_boot_kft_reserved_region_t   reserved_regions[AM_BOOT_KFT_PROPERTY_RESERVED_REGIONS_COUNT];

    /** \brief Configuration data from flash address 0x3c0-0x3ff in sector 0 (64 bytes max) */
    am_boot_kft_configuration_data_t configuration_data;

    /** \brief Status of reliable update */
    uint32_t                        reliable_update_status;
} am_boot_kft_property_store_t;

typedef struct am_boot_kft_property_devinfo {
    uint32_t  app_start_addr;      /**< \brief 应用代码的起始地址*/
    uint32_t  flash_start_addr;    /**< \brief flash的起始地址*/
    uint32_t  flash_size;          /**< \brief flash的大小 */

    uint32_t  ram_start_addr;      /**< \brief ram起始地址 */
    uint32_t  ram_size;            /**< \brief ram的大小 */
}am_boot_kft_property_devinfo_t;


/**
 * \brief bootloader 属性驱动函数
 */
struct am_boot_kft_property_funcs {
    /** \brief 装载用户配置 */
    int32_t (*pfn_load_user_config)(void *p_arg);

    /** \brief 获取属性 */
    int32_t (*pfn_get_property)(void       *p_arg,
                               uint8_t      tag,
                               uint8_t      id,
                               const void **value,
                               uint32_t    *valueSize);

    /** \brief 设置属性 */
    int32_t (*pfn_set_uint32_property)(void *p_arg, uint8_t tag, uint32_t value);
};

/** \brief 属性标准服务 */
typedef struct am_boot_kft_property_serv {
    struct am_boot_kft_property_funcs *p_funcs;
    void                              *p_drv;
}am_boot_kft_property_serv_t;

/** \brief 服务句柄 */
typedef am_boot_kft_property_serv_t *am_boot_kft_property_handle_t;

typedef struct am_boot_kft_property_dev {
    /** \brief 属性服务 */
    am_boot_kft_property_serv_t     property_serv;

    /** \brief flash服务句柄 */
    am_boot_flash_handle_t          flash_handle;

    /** \brief 包服务句柄 */
    am_boot_kft_packet_handle_t     packet_handle;

    /** \brief 存放属性的结构体 */
    am_boot_kft_property_store_t    property_store;

    am_boot_kft_property_devinfo_t  property_devinfo;
}am_boot_kft_property_dev_t;

/**
 * \brief 初始化函数
 */
am_boot_kft_property_handle_t am_boot_kft_property_init(
    am_boot_flash_handle_t flash_handle, am_boot_kft_property_devinfo_t *p_property_devinfo);

#endif /* __AM_BOOT_KFT_PROPERTY_H */

/* end of file */
