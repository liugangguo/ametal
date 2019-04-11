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
 * \brief bootloader kboot KinetisFlashTool 串行数据包声明
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-10-25  yrh, first implementation
 * \endinternal
 */
#ifndef __AM_BOOT_KFT_SERIAL_PACKET_H
#define __AM_BOOT_KFT_SERIAL_PACKET_H

#include "am_boot_kft_common.h"
#include "am_boot_kft_command_packet.h"
#include "am_boot_serial_byte.h"
#include "am_crc.h"

enum am_boot_kft_serial_protocol_version_constants
{
    AM_BOOT_KFT_SERIAL_PROTOCOL_VERSION_NAME   = 'P',
    AM_BOOT_KFT_SERIAL_PROTOCOL_VERSION_MAJOR  = 1,
    AM_BOOT_KFT_SERIAL_PROTOCOL_VERSION_MINOR  = 2,
    AM_BOOT_KFT_SERIAL_PROTOCOL_VERSION_BUGFIX = 0
};

/**
 * \name framing packet constants
 * @{
 */
#define  AM_BOOT_KFT_FRAMING_PACKET_START_BYTE          0x5a
#define  AM_BOOT_KFT_FRAMING_PACKET_TYPE_ACK            0xa1
#define  AM_BOOT_KFT_FRAMING_PACKET_TYPE_NAK            0xa2
#define  AM_BOOT_KFT_FRAMING_PACKET_TYPE_ACK_ABORT      0xa3
#define  AM_BOOT_KFT_FRAMING_PACKET_TYPE_COMMAND        0xa4
#define  AM_BOOT_KFT_FRAMING_PACKET_TYPE_DATA           0xa5
#define  AM_BOOT_KFT_FRAMING_PACKET_TYPE_PING           0xa6
#define  AM_BOOT_KFT_FRAMING_PACKET_TYPE_PING_RESPONSE  0xa7
/** @} */

/**
 * \name Timeout and other constants
 * @{
 */
/** \brief Default value for receiving 1 byte timeout */
#define  AM_BOOT_KFT_DEFAULT_BYTE_READ_TIMEOUT_MS   10

/** \brief Size for callback buffer, Must be power of 2 for easy wrap */
#define  AM_BOOT_KFT_CALLBACK_BUFFER_SIZE           64
/** @} */

/**
 * \name Incoming data buffer allocation size
 * @{
 */
#define  AM_BOOT_KFT_INCOMING_PACKET_BUFFER_SIZE AM_BOOT_KFT_MIN_PACKET_BUFFER_SIZE
#define  AM_BOOT_KFT_OUTGOING_PACKET_BUFFER_SIZE AM_BOOT_KFT_MIN_PACKET_BUFFER_SIZE
/** @} */

/**
 * \brief  Packet types
 */
typedef enum am_boot_kft_packet_type
{
    AM_BOOT_KFT_PACKET_TYPE_COMMAND, /** \brief Send or expect a command packet */
    AM_BOOT_KFT_PACKET_TYPE_DATA     /** \brief Send or expect a data packet */
} am_boot_kft_packet_type_t;


/**
 *  \brief Serial framing header
 */
typedef struct am_boot_kft_framing_header
{
    uint8_t start_byte; /** \brief kFramingPacketStartByte */
    uint8_t packet_type;/** \brief Framing packet type */
} am_boot_kft_framing_header_t;

/**
 *  \brief Serial framing sync packet
 */
typedef struct am_boot_kft_framing_sync_packet
{
    am_boot_kft_framing_header_t header;
} am_boot_kft_framing_sync_packet_t;

/**
 *  \brief Serial framing data packet
 */
typedef struct am_boot_kft_framing_data_packet
{
    am_boot_kft_framing_header_t header; /** \brief Framing packet header */
    uint16_t                     length; /** \brief Number of data bytes that follow */
    uint16_t                     crc16;  /** \brief CRC-16 of data packet header and data */
} am_boot_kft_framing_data_packet_t;


/**
 *  \brief Framing packet with data area
 */
typedef struct am_boot_kft_serial_framing_packet
{
    /** \brief Framing packet header */
    am_boot_kft_framing_data_packet_t data_packet;

    /** \brief Payload */
    uint8_t                           data[AM_BOOT_KFT_OUTGOING_PACKET_BUFFER_SIZE];
} am_boot_kft_serial_framing_packet_t;

/**
 * \brief Format of global context data
 */
typedef struct am_boot_kft_serial_data
{
    /** \brief Buffer for incomming packet data payload, must be uint32_t aligned. */
    uint8_t                             data[AM_BOOT_KFT_INCOMING_PACKET_BUFFER_SIZE];

    /** \brief Buffer for incoming data from the byte callback */
    uint8_t                             callback_buffer[AM_BOOT_KFT_CALLBACK_BUFFER_SIZE];

    /** \brief Buffer for outgoing packet */
    am_boot_kft_serial_framing_packet_t framing_packet;

    /** \brief The offset into the buffer that the ISR will queue data into */
    volatile uint32_t                   write_offset;

    /** \brief The offset into the buffer that the app has read out */
    uint32_t                            read_offset;

    /** \brief True if need to send ACK to previously received packet */
    am_bool_t                           is_ack_needed;

    /** \brief True if executing back-to-back write */
    am_bool_t                           is_back_to_back_write;

    /** \brief True if next ACK should be ACK Abort */
    am_bool_t                           is_ack_abort_needed;
} am_boot_kft_serial_data_t;


/**
 * \brief Serial ping response format
 *
 * \note This is the format of the response to a Ping packet
 */
typedef struct am_boot_kft_ping_response
{
    /** \brief Serial framing protocol version */
    am_boot_kft_standard_version_t version;

    /** \brief Serial framing protocol options bitfield */
    uint16_t                       options;

    /** \brief CRC-16 of other fields */
    uint16_t                       crc16;
} am_boot_kft_ping_response_t;

struct am_boot_kft_packet_funcs {
    int32_t (*pfn_read_packet)(void                      *p_arg,
                               uint8_t                  **pp_packet,
                               uint32_t                  *p_packet_length,
                               am_boot_kft_packet_type_t  packet_type);
    int32_t (*pfn_write_packet)(void                     *p_arg,
                                const uint8_t            *p_packet,
                                uint32_t                  byte_count,
                                am_boot_kft_packet_type_t packet_type);
    void     (*pfn_abort_data_phase)(void *p_arg);
    int32_t  (*pfn_finalize)(void *p_arg);
    uint32_t (*pfn_get_max_packet_size)(void *p_arg);
    void     (*pfn_byte_received_callback)(uint8_t byte);
};

typedef struct am_boot_kft_packet_serv {
    struct am_boot_kft_packet_funcs *p_funcs;
    void                            *p_drv;
}am_boot_kft_packet_serv_t;

typedef am_boot_kft_packet_serv_t *am_boot_kft_packet_handle_t;

typedef struct am_boot_kft_packet_dev
{
    am_boot_kft_packet_serv_t   packet_serv;
    am_boot_kft_serial_data_t   serial_context;
    am_boot_serial_handle_t     serial_handle;
    am_crc_handle_t             crc_handle;

}am_boot_kft_packet_dev_t;


#if defined(__cplusplus)
extern "C" {
#endif

am_boot_kft_packet_handle_t am_boot_kft_packet_init(am_boot_serial_handle_t serial_handle);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif /* __AM_BOOT_KFT_SERIAL_PACKET_H */
/* end of file */
