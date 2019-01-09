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

static int32_t __bootloader_property_load_user_config(void *p_arg);
static int32_t __bootloader_property_init(void *p_arg);
static int32_t __bootloader_property_get(void *p_arg, uint8_t tag, uint8_t id, const void **pp_value, uint32_t *p_value_size);
static int32_t __bootloader_property_set_uint32(void *p_arg, uint8_t tag, uint32_t value);

/** \brief Storage for property values computed every time they are read */
static uint32_t __g_property_return_value;

static struct am_boot_kft_property_funcs __g_property_funcs = {
    __bootloader_property_load_user_config,
    __bootloader_property_get,
    __bootloader_property_set_uint32,
};
static am_boot_kft_property_dev_t __g_property_dev;

am_boot_kft_property_handle_t am_boot_kft_property_init(
    am_boot_flash_handle_t flash_handle,am_boot_kft_property_devinfo_t *p_property_devinfo)
{
    __g_property_dev.property_serv.p_funcs = &__g_property_funcs;
    __g_property_dev.property_serv.p_drv   = &__g_property_dev;
    __g_property_dev.flash_handle          = flash_handle;

    am_boot_kft_property_devinfo_t *p_devinfo = &__g_property_dev.property_devinfo;

    p_devinfo->app_start_addr   = p_property_devinfo->app_start_addr;
    p_devinfo->flash_size       = p_property_devinfo->flash_size;
    p_devinfo->flash_start_addr = p_property_devinfo->flash_start_addr;
    p_devinfo->ram_size         = p_property_devinfo->ram_size;
    p_devinfo->ram_start_addr   = p_property_devinfo->ram_start_addr;

    __bootloader_property_init(&__g_property_dev);
    __bootloader_property_load_user_config(&__g_property_dev);

    return &__g_property_dev.property_serv;
}

/**
 * \brief Early initialization function to get user configuration data
 */
static int32_t __bootloader_property_load_user_config(void *p_arg)
{
    am_boot_kft_property_dev_t *p_dev = (am_boot_kft_property_dev_t *)p_arg;
    am_boot_kft_configuration_data_t *config = &p_dev->property_store.configuration_data;

    /* Copy bootloader configuration data from the flash into the property store. */
    memcpy((void *)config,
           (const void *)(p_dev->property_devinfo.app_start_addr + 0x3c0),
            sizeof(am_boot_kft_configuration_data_t));

    /* Verify tag. If it is invalid, wipe the config data to all 0xff. */
    if (AM_BOOT_KFT_PROPERTY_STORE_TAG != config->tag) {
        memset(config, 0xff, sizeof(am_boot_kft_configuration_data_t));
    }


    return AM_BOOT_KFT_STATUS_SUCCESS;
}

/**
 * \brief Initialize the property store.
 */
static int32_t __bootloader_property_init(void *p_arg)
{
    am_boot_kft_property_dev_t *p_dev = (am_boot_kft_property_dev_t *)p_arg;
    am_boot_kft_property_devinfo_t *p_devinfo = &p_dev->property_devinfo;


    am_boot_kft_property_store_t   *property_store = &p_dev->property_store;
    /* Fill in default values */
    property_store->bootloader_version.ver.name   = AM_BOOT_KFT_VERSION_NAME;
    property_store->bootloader_version.ver.major  = AM_BOOT_KFT_VERSION_MAJOR;
    property_store->bootloader_version.ver.minor  = AM_BOOT_KFT_VERSION_MINOR;
    property_store->bootloader_version.ver.bugfix = AM_BOOT_KFT_VERSION_BUGFIX;

    property_store->serial_protocol_version.ver.name   = AM_BOOT_KFT_SERIAL_PROTOCOL_VERSION_NAME;
    property_store->serial_protocol_version.ver.major  = AM_BOOT_KFT_SERIAL_PROTOCOL_VERSION_MAJOR;
    property_store->serial_protocol_version.ver.minor  = AM_BOOT_KFT_SERIAL_PROTOCOL_VERSION_MINOR;
    property_store->serial_protocol_version.ver.bugfix = AM_BOOT_KFT_SERIAL_PROTOCOL_VERSION_BUGFIX;

    property_store->target_version.ver.name   = 'T';
    property_store->target_version.ver.major  = 1;
    property_store->target_version.ver.minor  = 0;
    property_store->target_version.ver.bugfix = 0;

    property_store->verify_writes      = true;
    property_store->available_commands = 61407;

    am_boot_flash_info_t *flash_info = NULL;

    am_boot_flash_info_get(p_dev->flash_handle, &flash_info);

    property_store->flash_start_address = flash_info->flash_start_addr;
    property_store->flash_size_in_bytes = flash_info->flash_size;
    property_store->flash_sector_size   = flash_info->flash_sector_size;
    property_store->flash_block_size    = flash_info->flash_sector_size * 4;
    property_store->flash_block_count   = flash_info->flash_size / property_store->flash_block_size;

    /* Fill in reserved regions. */
    uint32_t flashStart = 0;
    uint32_t flashEnd   = 0;
    uint32_t ramStart   = 0;
    uint32_t ramEnd     = 0;

    property_store->reserved_regions[AM_BOOT_KFT_PROPERTY_FLASH_RESERVED_REGION_INDEX].start_address = flashStart;
    property_store->reserved_regions[AM_BOOT_KFT_PROPERTY_FLASH_RESERVED_REGION_INDEX].end_address = flashEnd;
    property_store->reserved_regions[AM_BOOT_KFT_PROPERTY_RAM_RESERVED_REGION_INDEX].start_address = ramStart;
    property_store->reserved_regions[AM_BOOT_KFT_PROPERTY_RAM_RESERVED_REGION_INDEX].end_address = ramEnd;


    /* Set address range of RAM in property interface */
    property_store->ram_start_address[AM_BOOT_KFT_INDEX_RAM - 1] = p_devinfo->ram_start_addr;
    property_store->ram_size_in_bytes[AM_BOOT_KFT_INDEX_RAM - 1] = p_devinfo->ram_size;


#if BL_FEATURE_CRC_CHECK
    /* Initialize crc check status property based on BCA related fields. */
    init_crc_check_status(property_store);
#endif

    return AM_BOOT_KFT_STATUS_SUCCESS;
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
static int32_t __bootloader_property_get(void        *p_arg,
                                          uint8_t      tag,
                                          uint8_t      id,
                                          const void **pp_value,
                                          uint32_t    *p_value_size)
{
    am_boot_kft_property_dev_t *p_dev = (am_boot_kft_property_dev_t *)p_arg;
    am_boot_kft_property_store_t *property_store = &(p_dev->property_store);

    /* Set default value size, may be modified below. */
    uint32_t return_size = sizeof(uint32_t);
    const void *return_value;
    switch (tag) {

    case AM_BOOT_KFT_PROPERTY_TAG_BOOTLOADER_VERSION:
        return_value = &property_store->bootloader_version.version;
        break;

    case AM_BOOT_KFT_PROPERTY_TAG_FLASH_START_ADDRESS:
        return_value = &property_store->flash_start_address;
        break;

    case AM_BOOT_KFT_PROPERTY_TAG_FLASH_SIZE_IN_BYTES:
        return_value = &property_store->flash_size_in_bytes;
        break;

    case AM_BOOT_KFT_PROPERTY_TAG_FLASH_SECTOR_SIZE:
        return_value = &property_store->flash_sector_size;
        break;

    case AM_BOOT_KFT_PROPERTY_TAG_FLASH_BLOCK_COUNT:
        return_value = &property_store->flash_block_count;
        break;

    case AM_BOOT_KFT_PROPERTY_TAG_RAM_START_ADDRESS:
        return_value = &property_store->ram_start_address[0];

        break;

    case AM_BOOT_KFT_PROPERTY_TAG_RAM_SIZE_IN_BYTES:
        return_value = &property_store->ram_size_in_bytes[0];

        break;

#if BL_FEATURE_CRC_CHECK
    case PROPERTY_TAG_CRC_CHECK_STATUS:
        return_value = &property_store->crcCheckStatus;
        break;
#endif /* else falls through to unknown */
    case AM_BOOT_KFT_PROPERTY_TAG_AVAILABLE_COMMANDS:
        return_value =&property_store->available_commands;
        break;

    case AM_BOOT_KFT_PROPERTY_TAG_VERIFY_WRITES:
        return_value = &property_store->verify_writes;
        break;

    case AM_BOOT_KFT_PROPERTY_TAG_MAX_PACKET_SIZE:
        /* Read the max packet size from the active peripheral. */
        __g_property_return_value =
                p_dev->packet_handle->p_funcs->pfn_get_max_packet_size(p_dev->packet_handle->p_drv);
        return_value = &__g_property_return_value;
        break;

    case AM_BOOT_KFT_PROPERTY_TAG_RESERVED_REGIONS:
        return_size = sizeof(property_store->reserved_regions);
        return_value = property_store->reserved_regions;
        break;

    case AM_BOOT_KFT_PROPERTY_TAG_FLASH_SECURITY_STATE: {

        __g_property_return_value = 1;
        return_value = &__g_property_return_value;
        break;
    }

    case AM_BOOT_KFT_PROPERTY_TAG_FLASH_READ_MARGIN:
        return_size = sizeof(property_store->flash_read_margin);
        return_value = &property_store->flash_read_margin;
        break;

    case AM_BOOT_KFT_PROPERTY_TAG_TARGET_VERSION:
        return_value = &property_store->target_version.version;
        break;

    default:
        return AM_BOOT_KFT_STATUS_UNKNOWN_PROPERTY;
    }
    /* Set the return size */
    if (p_value_size) {
        *p_value_size = return_size;
    }
    /* Set the return value */
    if (pp_value) {
        *pp_value = return_value;
    }
    return AM_BOOT_KFT_STATUS_SUCCESS;
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
static int32_t __bootloader_property_set_uint32(void *p_arg, uint8_t tag, uint32_t value)
{
    am_boot_kft_property_dev_t   *p_dev = (am_boot_kft_property_dev_t *)p_arg;
    am_boot_kft_property_store_t *property_store = &p_dev->property_store;

    switch (tag) {

    case AM_BOOT_KFT_PROPERTY_TAG_VERIFY_WRITES:
        if (value != 0 && value != 1) {
            return AM_BOOT_KFT_STATUS_INVALID_PROPERTY_VALUE;
        }
        property_store->verify_writes = value;
        return AM_BOOT_KFT_STATUS_SUCCESS;

    case AM_BOOT_KFT_PROPERTY_TAG_FLASH_READ_MARGIN:
        if (value >= 3)
        {
            return AM_BOOT_KFT_STATUS_INVALID_PROPERTY_VALUE;
        }
        property_store->flash_read_margin = value;
        return AM_BOOT_KFT_STATUS_SUCCESS;

    case AM_BOOT_KFT_PROPERTY_TAG_BOOTLOADER_VERSION:
    case AM_BOOT_KFT_PROPERTY_TAG_AVAILABLE_PERIPHERALS:
    case AM_BOOT_KFT_PROPERTY_TAG_FLASH_START_ADDRESS:
    case AM_BOOT_KFT_PROPERTY_TAG_FLASH_SIZE_IN_BYTES:
    case AM_BOOT_KFT_PROPERTY_TAG_FLASH_SECTOR_SIZE:
    case AM_BOOT_KFT_PROPERTY_TAG_FLASH_BLOCK_COUNT:
    case AM_BOOT_KFT_PROPERTY_TAG_RAM_START_ADDRESS:
    case AM_BOOT_KFT_PROPERTY_TAG_RAM_SIZE_IN_BYTES:
    case AM_BOOT_KFT_PROPERTY_TAG_AVAILABLE_COMMANDS:
#if BL_FEATURE_CRC_CHECK
    case KFT_PROPERTY_TAG_CRC_CHECK_STATUS:
#endif

#if BL_FEATURE_RELIABLE_UPDATE
        case KFT_PROPERTY_TAG_RELIABLE_UPDATE_STATUS:
#endif // BL_FEATURE_RELIABLE_UPDATE
    case AM_BOOT_KFT_PROPERTY_TAG_MAX_PACKET_SIZE:
    case AM_BOOT_KFT_PROPERTY_TAG_RESERVED_REGIONS:
    case AM_BOOT_KFT_PROPERTY_TAG_FLASH_SECURITY_STATE:
    case AM_BOOT_KFT_PROPERTY_TAG_TARGET_VERSION:
        return AM_BOOT_KFT_STATUS_READONLY_PROPERTY;
    default:
        return AM_BOOT_KFT_STATUS_UNKNOWN_PROPERTY;
    }
}

/* end of file */
