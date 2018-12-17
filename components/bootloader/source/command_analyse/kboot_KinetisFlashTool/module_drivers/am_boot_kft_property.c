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
 * \brief bootloader kboot KinetisFlashTool  Ù–‘ µœ÷
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-10-25  yrh, first implementation
 * \endinternal
 */
#include <string.h>
#include "am_boot_kft_command_packet.h"
#include "am_boot_kft_common.h"
#include "am_boot_kft_property.h"
#include "am_boot_kft_serial_packet.h"
#include "am_boot_kft_version.h"
#include "am_boot_memory.h"
#include "am_common.h"
#include "am_boot.h"

/** \brief Storage for property values */
property_store_t g_property_store;

static status_t __bootloader_property_load_user_config(void *p_arg);
static status_t __bootloader_property_init(void *p_arg);
static status_t __bootloader_property_get(void *p_arg, uint8_t tag, uint8_t id, const void **pp_value, uint32_t *p_value_size);
static status_t __bootloader_property_set_uint32(void *p_arg, uint8_t tag, uint32_t value);

/** \brief Storage for property values computed every time they are read */
static uint32_t __g_property_return_value;

static struct am_boot_kft_property_funcs __g_property_funcs = {
    __bootloader_property_load_user_config,
    __bootloader_property_get,
    __bootloader_property_set_uint32,
};
static am_boot_kft_property_dev_t __g_property_dev;

am_boot_kft_property_handle_t am_boot_kft_property_init(am_boot_flash_handle_t flash_handle,
                                                        uint32_t               app_start_addr)
{
    __g_property_dev.property_serv.p_funcs = &__g_property_funcs;
    __g_property_dev.property_serv.p_drv   = &__g_property_dev;
    __g_property_dev.flash_handle          = flash_handle;
    __g_property_dev.app_start_addr        = app_start_addr;

    __bootloader_property_init(&__g_property_dev);
    __bootloader_property_load_user_config(&__g_property_dev);

    return &__g_property_dev.property_serv;
}

/**
 * \brief Early initialization function to get user configuration data
 */
static status_t __bootloader_property_load_user_config(void *p_arg)
{
    am_boot_kft_property_dev_t *p_dev = (am_boot_kft_property_dev_t *)p_arg;
    bootloader_configuration_data_t *config = &p_dev->property_store.configuration_data;
    {
        /* Copy bootloader configuration data from the flash into the property store. */
        memcpy(config, (const void *)p_dev->app_start_addr + 0x3c0, sizeof(bootloader_configuration_data_t));

        /* Verify tag. If it is invalid, wipe the config data to all 0xff. */
        if (KFT_PROPERTY_STORE_TAG != config->tag) {
            memset(config, 0xff, sizeof(bootloader_configuration_data_t));
        }
    }

    return KFT_STATUS_SUCCESS;
}

/**
 * \brief Initialize the property store.
 */
static status_t __bootloader_property_init(void *p_arg)
{
    am_boot_kft_property_dev_t *p_dev = (am_boot_kft_property_dev_t *)p_arg;
    am_boot_mem_info_t *p_mem_info = NULL;
    am_boot_base_mem_info_get(&p_mem_info);

    property_store_t   *property_store = &p_dev->property_store;//g_bootloader_context.p_property_interface->store;
    /* Fill in default values */
    property_store->bootloader_version.name   = KBOOTLOADER_VERSION_NAME;
    property_store->bootloader_version.major  = KBOOTLOADER_VERSION_MAJOR;
    property_store->bootloader_version.minor  = KBOOTLOADER_VERSION_MINOR;
    property_store->bootloader_version.bugfix = KBOOTLOADER_VERSION_BUGFIX;

    property_store->serial_protocol_version.name   = KFT_SERIAL_PROTOCOL_VERSION_NAME;
    property_store->serial_protocol_version.major  = KFT_SERIAL_PROTOCOL_VERSION_MAJOR;
    property_store->serial_protocol_version.minor  = KFT_SERIAL_PROTOCOL_VERSION_MINOR;
    property_store->serial_protocol_version.bugfix = KFT_SERIAL_PROTOCOL_VERSION_BUGFIX;

    property_store->target_version.name   = 'T';
    property_store->target_version.major  = 1;
    property_store->target_version.minor  = 0;
    property_store->target_version.bugfix = 0;

    property_store->verify_writes      = true;
    property_store->available_commands = 61407;

    am_boot_flash_info_t *flash_info = NULL;

    am_boot_flash_info_get(p_dev->flash_handle, &flash_info);

    property_store->flash_start_address = flash_info->flash_start_addr;
    property_store->flash_size_in_bytes = flash_info->flash_size;
    property_store->flash_sector_size   = flash_info->flash_sector_size;
    property_store->flash_block_size    = flash_info->flash_sector_size * 4;
    property_store->flash_block_count   = flash_info->flash_size / property_store->flash_block_size;

    // Fill in reserved regions.
    uint32_t flashStart = 0;
    uint32_t flashEnd   = 0;
    uint32_t ramStart   = 0;
    uint32_t ramEnd     = 0;

    property_store->reserved_regions[KFT_PROPERTY_FLASH_RESERVED_REGION_INDEX].start_address = flashStart;
    property_store->reserved_regions[KFT_PROPERTY_FLASH_RESERVED_REGION_INDEX].end_address = flashEnd;
    property_store->reserved_regions[KFT_PROPERTY_RAM_RESERVED_REGION_INDEX].start_address = ramStart;
    property_store->reserved_regions[KFT_PROPERTY_RAM_RESERVED_REGION_INDEX].end_address = ramEnd;


    /* Set address range of RAM in property interface */
    property_store->ram_start_address[KFT_INDEX_RAM - 1] = p_mem_info->ram_start_addr;
    property_store->ram_size_in_bytes[KFT_INDEX_RAM - 1] = p_mem_info->ram_size;


#if BL_FEATURE_CRC_CHECK
    // Initialize crc check status property based on BCA related fields.
    init_crc_check_status(property_store);
#endif

    return KFT_STATUS_SUCCESS;
}


/**
 * \brief Get a property
 *
 * \param[in] tag      : tag Tag of the requested property
 * \param[in] memoryId : memoryId Id for specified external memory, for example: 1 represent QuadSPI 0
 * \param[in] value    : value Pointer to where to write a pointer to the result, may be NULL
 * \param[in] valueSize: valueSize Size in bytes of the property value, may be NULL
 *
 * \retval BL_STATUS_SUCCESS
 * \retval BL_STATUS_UNKNOWN_PROPERTY
 */
static status_t __bootloader_property_get(void        *p_arg,
                                          uint8_t      tag,
                                          uint8_t      id,
                                          const void **pp_value,
                                          uint32_t    *p_value_size)
{
    am_boot_kft_property_dev_t *p_dev = (am_boot_kft_property_dev_t *)p_arg;
    property_store_t *property_store = &(p_dev->property_store);

    /* Set default value size, may be modified below. */
    uint32_t return_size = sizeof(uint32_t);
    const void *return_value;
    switch (tag) {
        case KFT_PROPERTY_TAG_BOOTLOADER_VERSION:
            return_value = &property_store->bootloader_version.version;
            break;

        case KFT_PROPERTY_TAG_FLASH_START_ADDRESS:
            return_value = &property_store->flash_start_address;
            break;

        case KFT_PROPERTY_TAG_FLASH_SIZE_IN_BYTES:
            return_value = &property_store->flash_size_in_bytes;
            break;

        case KFT_PROPERTY_TAG_FLASH_SECTOR_SIZE:
            return_value = &property_store->flash_sector_size;
            break;

        case KFT_PROPERTY_TAG_FLASH_BLOCK_COUNT:
            return_value = &property_store->flash_block_count;
            break;

        case KFT_PROPERTY_TAG_RAM_START_ADDRESS:
            return_value = &property_store->ram_start_address[0];

            break;

        case KFT_PROPERTY_TAG_RAM_SIZE_IN_BYTES:
            return_value = &property_store->ram_size_in_bytes[0];

            break;

#if BL_FEATURE_CRC_CHECK
        case PROPERTY_TAG_CRC_CHECK_STATUS:
            return_value = &property_store->crcCheckStatus;
            break;
#endif // else falls through to unknown
        case KFT_PROPERTY_TAG_AVAILABLE_COMMANDS:
            return_value =&property_store->available_commands;
            break;

        case KFT_PROPERTY_TAG_VERIFY_WRITES:
            return_value = &property_store->verify_writes;
            break;

        case KFT_PROPERTY_TAG_MAX_PACKET_SIZE:
            // Read the max packet size from the active peripheral.
            __g_property_return_value =
                    p_dev->packet_handle->p_funcs->pfn_get_max_packet_size(p_dev->packet_handle->p_drv);
            return_value = &__g_property_return_value;
            break;

        case KFT_PROPERTY_TAG_RESERVED_REGIONS:
            return_size = sizeof(property_store->reserved_regions);
            return_value = property_store->reserved_regions;
            break;

        case KFT_PROPERTY_TAG_FLASH_SECURITY_STATE: {

            __g_property_return_value = 1;
            return_value = &__g_property_return_value;
            break;
        }

        case KFT_PROPERTY_TAG_FLASH_READ_MARGIN:
            return_size = sizeof(property_store->flash_read_margin);
            return_value = &property_store->flash_read_margin;
            break;

        case KFT_PROPERTY_TAG_TARGET_VERSION:
            return_value = &property_store->target_version.version;
            break;

        default:
            return KFT_STATUS_UNKNOWN_PROPERTY;
    }
    /* Set the return size */
    if (p_value_size) {
        *p_value_size = return_size;
    }
    /* Set the return value */
    if (pp_value) {
        *pp_value = return_value;
    }
    return KFT_STATUS_SUCCESS;
}


/**
 * \brief Set a property
 *
 * \param[in] tag      : tag Tag of the property to set
 * \param[in] value : value New property value
 *
 * \retval BL_STATUS_SUCCESS
 * \retval BL_STATUS_UNKNOWN_PROPERTY
 * \retval BL_STATUS_READONLY_PROPERTY
 */
static status_t __bootloader_property_set_uint32(void *p_arg, uint8_t tag, uint32_t value)
{
    am_boot_kft_property_dev_t *p_dev = (am_boot_kft_property_dev_t *)p_arg;
    property_store_t     *property_store = &p_dev->property_store;

    switch (tag) {
        case KFT_PROPERTY_TAG_VERIFY_WRITES:
            if (value != 0 && value != 1) {
                return KFT_STATUS_INVALID_PROPERTY_VALUE;
            }
            property_store->verify_writes = value;
            return KFT_STATUS_SUCCESS;

        case KFT_PROPERTY_TAG_FLASH_READ_MARGIN:
            if (value >= 3)
            {
                return KFT_STATUS_INVALID_PROPERTY_VALUE;
            }
            property_store->flash_read_margin = value;
            return KFT_STATUS_SUCCESS;

        case KFT_PROPERTY_TAG_BOOTLOADER_VERSION:
        case KFT_PROPERTY_TAG_AVAILABLE_PERIPHERALS:
        case KFT_PROPERTY_TAG_FLASH_START_ADDRESS:
        case KFT_PROPERTY_TAG_FLASH_SIZE_IN_BYTES:
        case KFT_PROPERTY_TAG_FLASH_SECTOR_SIZE:
        case KFT_PROPERTY_TAG_FLASH_BLOCK_COUNT:
        case KFT_PROPERTY_TAG_RAM_START_ADDRESS:
        case KFT_PROPERTY_TAG_RAM_SIZE_IN_BYTES:
        case KFT_PROPERTY_TAG_AVAILABLE_COMMANDS:
#if BL_FEATURE_CRC_CHECK
        case KFT_PROPERTY_TAG_CRC_CHECK_STATUS:
#endif

#if BL_FEATURE_RELIABLE_UPDATE
        case KFT_PROPERTY_TAG_RELIABLE_UPDATE_STATUS:
#endif // BL_FEATURE_RELIABLE_UPDATE
        case KFT_PROPERTY_TAG_MAX_PACKET_SIZE:
        case KFT_PROPERTY_TAG_RESERVED_REGIONS:
        case KFT_PROPERTY_TAG_FLASH_SECURITY_STATE:
        case KFT_PROPERTY_TAG_TARGET_VERSION:
            return KFT_STATUS_READONLY_PROPERTY;
        default:
            return KFT_STATUS_UNKNOWN_PROPERTY;
    }
}

/* end of file */
