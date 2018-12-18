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

enum kft_serial_protocol_version_constants
{
    KFT_SERIAL_PROTOCOL_VERSION_NAME   = 'P',
    KFT_SERIAL_PROTOCOL_VERSION_MAJOR  = 1,
    KFT_SERIAL_PROTOCOL_VERSION_MINOR  = 2,
    KFT_SERIAL_PROTOCOL_VERSION_BUGFIX = 0
};

/** \brief
 * Serial framing packet constants
 */
enum kft_framing_packet_constants
{
    KFT_FRAMING_PACKET_START_BYTE         = 0x5a,
    KFT_FRAMING_PACKET_TYPE_ACK           = 0xa1,
    KFT_FRAMING_PACKET_TYPE_NAK           = 0xa2,
    KFT_FRAMING_PACKET_TYPE_ACK_ABORT     = 0xa3,
    KFT_FRAMING_PACKET_TYPE_COMMAND       = 0xa4,
    KFT_FRAMING_PACKET_TYPE_DATA          = 0xa5,
    KFT_FRAMING_PACKET_TYPE_PING          = 0xa6,
    KFT_FRAMING_PACKET_TYPE_PING_RESPONSE = 0xa7
};

/**
 *  \brief Timeout and other constants
 */
enum kft_timing_constants
{
    //HostMaxStartByteReadCount = 2,
    /** \brief Default value for receiving 1 byte timeout */
    KFT_DEFAULT_BYTE_READ_TIMEOUT_MS = 10,
    /** \brief Size for callback buffer, Must be power of 2 for easy wrap */
    KFT_CALLBACK_BUFFER_SIZE = 64
};

/**
 *  \brief Incoming data buffer allocation size
 */
enum kft_serial_packet_constants
{
    KFT_INCOMING_PACKET_BUFFER_SIZE = KFT_MIN_PACKET_BUFFER_SIZE,
    KFT_OUTGOING_PACKET_BUFFER_SIZE = KFT_MIN_PACKET_BUFFER_SIZE
};


/**
 *  \brief Serial framing header
 */
typedef struct framing_header
{
    uint8_t start_byte; /** \brief kFramingPacketStartByte */
    uint8_t packet_type;/** \brief Framing packet type */
} framing_header_t;

/**
 *  \brief Serial framing sync packet
 */
typedef struct framing_sync_packet
{
    framing_header_t header;
} framing_sync_packet_t;

/**
 *  \brief Serial framing data packet
 */
typedef struct framing_data_packet
{
    framing_header_t header; /** \brief Framing packet header */
    uint16_t         length; /** \brief Number of data bytes that follow */
    uint16_t         crc16;  /** \brief CRC-16 of data packet header and data */
} framing_data_packet_t;


/**
 *  \brief Framing packet with data area
 */
typedef struct serial_framing_packet
{
    framing_data_packet_t data_packet;        /** \brief Framing packet header */
    uint8_t               data[KFT_OUTGOING_PACKET_BUFFER_SIZE]; /** \brief Payload */
} serial_framing_packet_t;

/**
 * \brief Format of global context data
 */
typedef struct serial_data
{
    /** \brief Buffer for incomming packet data payload, must be uint32_t aligned. */
    uint8_t                 data[KFT_INCOMING_PACKET_BUFFER_SIZE];

    /** \brief Buffer for incoming data from the byte callback */
    uint8_t                 callback_buffer[KFT_CALLBACK_BUFFER_SIZE];
    serial_framing_packet_t framing_packet;       /** \brief Buffer for outgoing packet */
    volatile uint32_t       write_offset;         /** \brief The offset into the buffer that the ISR will queue data into */
    uint32_t                read_offset;          /** \brief The offset into the buffer that the app has read out */
    am_bool_t               is_ack_needed;        /** \brief True if need to send ACK to previously received packet */
    am_bool_t               is_back_to_back_write; /** \brief True if executing back-to-back write */
    am_bool_t               is_ack_abort_needed;   /** \brief True if next ACK should be ACK Abort */
} serial_data_t;


/**
 * \brief Serial ping response format
 *
 * \note This is the format of the response to a Ping packet
 */
typedef struct ping_response
{
    standard_version_t version; /** \brief Serial framing protocol version */
    uint16_t           options; /** \brief Serial framing protocol options bitfield */
    uint16_t           crc16;   /** \brief CRC-16 of other fields */
} ping_response_t;

/**
 * \brief  Packet types
 */
typedef enum kft_packet_type
{
    KFT_PACKET_TYPE_COMMAND, /** \brief Send or expect a command packet */
    KFT_PACKET_TYPE_DATA     /** \brief Send or expect a data packet */
} packet_type_t;


struct am_boot_kft_packet_funcs {
    status_t (*pfn_read_packet)(void *p_arg,
                                uint8_t **packet,
                                uint32_t *packet_length,
                                packet_type_t packet_type);
    status_t (*pfn_write_packet)(void *p_arg,
                                 const uint8_t *packet,
                                 uint32_t byte_count,
                                 packet_type_t packet_type);
    void     (*pfn_abort_data_phase)(void *p_arg);
    status_t (*pfn_finalize)(void *p_arg);
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
    serial_data_t               serial_context;
    am_boot_serial_handle_t     serial_handle;
    am_crc_handle_t             crc_handle;

}am_boot_kft_packet_dev_t;


#if defined(__cplusplus)
extern "C" {
#endif

am_boot_kft_packet_handle_t am_boot_kft_packet_init(am_boot_serial_handle_t serial_handle);


/**
 * \brief Read packet using serial framing
 *
 * \note On return, caller must call flow control method to send AckContinue or AckWait followed by Continue.
 */
status_t serial_packet_read(void         *p_arg,
                            uint8_t     **packet,
                            uint32_t     *packetLength,
                            packet_type_t packetType);

/**
 * \brief Write packet using serial framing.
 */
status_t serial_packet_write(void          *p_arg,
                             const uint8_t *packet,
                             uint32_t       byteCount,
                             packet_type_t  packetType);

/**
 * \brief  Abort data phase
 * Respond to next host data packet with AckAbort instead of Ack
 */
void serial_packet_abort(void *p_arg);

/**
 * \brief Finalize.
 */
status_t serial_packet_finalize(void *p_arg);

/**
 * \brief Get max packet size.
 */
uint32_t serial_packet_get_max_packet_size(void *p_arg);

/**
 * \brief Send a sync packet of the specified type
 */
status_t serial_packet_send_sync(am_boot_kft_packet_dev_t *p_dev,
                                 uint8_t                   framing_packet_type);

/**
 * \brief Send a ping message back in response to a ping
 */
status_t serial_send_ping_response(am_boot_kft_packet_dev_t *p_dev);

/**
 * \brief Queues a byte received by the active peripheral
 */
void serial_packet_queue_byte(uint8_t byte);

#if defined(__cplusplus)
}
#endif // __cplusplus

#endif /* __AM_BOOT_KFT_SERIAL_PACKET_H */
/* end of file */
