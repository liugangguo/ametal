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
 * \brief bootloader kboot KinetisFlashTool 串行数据包处理实现
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 18-10-25  yrh, first implementation
 * \endinternal
 */
#include "ametal.h"
#include "am_crc.h"
#include "am_crc_soft.h"
#include "am_crc_table_def.h"
#include "am_boot_kft.h"
#include "am_boot_kft_command_packet.h"
#include "am_boot_kft_common.h"
#include "am_boot_kft_serial_packet.h"
#include <string.h>

#include "am_system.h"

static int32_t __write_data(am_boot_kft_packet_dev_t *p_dev,
                            const uint8_t            *p_buffer,
                            uint32_t                  byte_count);
static int32_t __read_data(uint8_t *p_buffer, uint32_t byte_ount, uint32_t timeout_ms);
static int32_t __read_data_packet(am_boot_kft_packet_dev_t          *p_dev,
                                  am_boot_kft_framing_data_packet_t *p_packet,
                                  uint8_t                           *p_data,
                                  am_boot_kft_packet_type_t          packet_type);
static int32_t __read_start_byte(am_boot_kft_framing_header_t *p_header);
static int32_t __read_header(am_boot_kft_framing_header_t *p_header);
static int32_t __read_length(am_boot_kft_framing_data_packet_t *p_packet);
static int32_t __read_crc16(am_boot_kft_framing_data_packet_t *p_packet);
static int32_t __wait_for_ack_packet(am_boot_kft_packet_dev_t *p_dev);
static int32_t __send_deferred_ack(am_boot_kft_packet_dev_t *p_dev);
static uint16_t __calculate_framing_crc16(am_boot_kft_framing_data_packet_t *p_packet,
                                          const uint8_t                     *p_data);


/**
 * \brief Read packet using serial framing
 *
 * \note On return, caller must call flow control method to send AckContinue or AckWait followed by Continue.
 */
static int32_t __serial_packet_read(void                     *p_arg,
                                  uint8_t                 **packet,
                                  uint32_t                 *packetLength,
                                  am_boot_kft_packet_type_t packetType);

/**
 * \brief Write packet using serial framing.
 */
static int32_t __serial_packet_write(void                      *p_arg,
                                   const uint8_t             *packet,
                                   uint32_t                   byteCount,
                                   am_boot_kft_packet_type_t  packetType);

/**
 * \brief  Abort data phase
 * Respond to next host data packet with AckAbort instead of Ack
 */
static void __serial_packet_abort(void *p_arg);

/**
 * \brief 串行包终止
 */
static int32_t __serial_packet_finalize(void *p_arg);

/**
 * \brief Get max packet size.
 */
static uint32_t __serial_packet_get_max_packet_size(void *p_arg);

/**
 * \brief Queues a byte received by the active peripheral
 */
static void __serial_packet_queue_byte(uint8_t byte);


/**
 * \brief Send a sync packet of the specified type
 */
static int32_t __serial_packet_send_sync(am_boot_kft_packet_dev_t *p_dev,
                                         uint8_t                   framing_packet_type);

/**
 * \brief Send a ping message back in response to a ping
 */
static int32_t __serial_send_ping_response(am_boot_kft_packet_dev_t *p_dev);

/**
 * \brief ping回应
 */
const am_boot_kft_ping_response_t kft_ping_response = {
    {
        {
          AM_BOOT_KFT_SERIAL_PROTOCOL_VERSION_BUGFIX,
          AM_BOOT_KFT_SERIAL_PROTOCOL_VERSION_MINOR,
          AM_BOOT_KFT_SERIAL_PROTOCOL_VERSION_MAJOR,
          AM_BOOT_KFT_SERIAL_PROTOCOL_VERSION_NAME }
        },
        0,      /** \brief 选择，如果此值更改，则重新计算crc16 */
        0xeaaa  /** \brief crc16的开始字节，包类型，版本，选项  */
                /** \brief i.e. [5a a7 00 00 01 50 00 00]， Calculated using CRC-16/XMODEM. */
};
static struct am_boot_kft_packet_funcs __g_packet_funcs = {
    __serial_packet_read,
    __serial_packet_write,
    __serial_packet_abort,
    __serial_packet_finalize,
    __serial_packet_get_max_packet_size,
    __serial_packet_queue_byte,
};

static am_boot_kft_serial_data_t __g_serial_context;
static am_boot_kft_packet_dev_t  __g_packet_dev;
static am_crc_soft_t             __g_crc_dev;

am_boot_kft_packet_handle_t am_boot_kft_packet_init(am_boot_serial_handle_t serial_handle)
{
    __g_packet_dev.packet_serv.p_funcs = &__g_packet_funcs;
    __g_packet_dev.packet_serv.p_drv   = &__g_packet_dev;
    __g_packet_dev.serial_handle       = serial_handle;

    __g_packet_dev.crc_handle = am_crc_soft_init (&__g_crc_dev,
                                                  &g_crc_table_16_1021);

    am_boot_serial_int_recev_callback_enable(
        serial_handle,
        __g_packet_dev.packet_serv.p_funcs->pfn_byte_received_callback);

    return &__g_packet_dev.packet_serv;
}


static void __serial_packet_queue_byte(uint8_t byte)
{
    __g_serial_context.callback_buffer[__g_serial_context.write_offset++] = byte;
    __g_serial_context.write_offset &= AM_BOOT_KFT_CALLBACK_BUFFER_SIZE - 1;
}

/**
 * \brief 串行包终止
 */
static int32_t __serial_packet_finalize(void *p_arg)
{
    am_boot_kft_packet_dev_t *p_dev = (am_boot_kft_packet_dev_t *)p_arg;

    return __send_deferred_ack(p_dev);
}

/**
 * \brief 串行包读
 */
static int32_t __serial_packet_read(void                     *p_arg,
                                    uint8_t                 **pp_packet,
                                    uint32_t                 *p_packet_length,
                                    am_boot_kft_packet_type_t packet_type)
{
    am_boot_kft_framing_data_packet_t framing_packet;
    am_boot_kft_packet_dev_t *p_dev = (am_boot_kft_packet_dev_t *)p_arg;
    am_bool_t is_packet_ok;
    int32_t   status;
    if (!pp_packet || !p_packet_length) {
        am_kprintf("Error: invalid packet\r\n");
        return AM_BOOT_KFT_STATUS_INVALID_ARGUMENT;
    }


    *p_packet_length = 0;

    __g_serial_context.is_back_to_back_write = AM_FALSE;

    /* Send ACK if needed */
    status = __send_deferred_ack(p_dev);
    if (status != AM_BOOT_KFT_STATUS_SUCCESS) {
        return status;
    }


    do {
        /* Clear the packet data area so unsent parameters default to zero */
        memset(__g_serial_context.data, 0, sizeof(__g_serial_context.data));

        /* Receive the framing data packet */
        is_packet_ok = AM_TRUE;
        int32_t status = __read_data_packet(p_dev,
                                            &framing_packet,
                                            __g_serial_context.data,
                                            packet_type);
        if (status != AM_BOOT_KFT_STATUS_SUCCESS) {
            /* No packet available */
            *p_packet_length = 0;
            return status;
        }

        /* Verify crc. */
        uint16_t calculated_crc = __calculate_framing_crc16(
                &framing_packet,  __g_serial_context.data);
        if (framing_packet.crc16 != calculated_crc) {
            am_kprintf("Error: invalid crc 0x%x, expected 0x%x\r\n", framing_packet.crc16, calculated_crc);
            is_packet_ok = AM_FALSE;
        }

        /*  Send Nak if necessary. */
        if (!is_packet_ok) {
            __serial_packet_send_sync(p_dev,AM_BOOT_KFT_FRAMING_PACKET_TYPE_NAK);
        }
    } while (!is_packet_ok);

    /* Indicate an ACK must be sent. */
    __g_serial_context.is_ack_needed = AM_TRUE;

    /* Set caller's data buffer and length */
   *pp_packet       = __g_serial_context.data;
   *p_packet_length = framing_packet.length;

    return AM_BOOT_KFT_STATUS_SUCCESS;
}

/**
 * \brief 串行包写
 */
static int32_t __serial_packet_write(void                      *p_arg,
                                     const uint8_t             *p_packet,
                                     uint32_t                   byte_count,
                                     am_boot_kft_packet_type_t  packet_type)
{
    if (!p_packet || (byte_count > AM_BOOT_KFT_OUTGOING_PACKET_BUFFER_SIZE)) {
        am_kprintf("Error: invalid packet or packet size %d\r\n", byte_count);
        return AM_BOOT_KFT_STATUS_INVALID_ARGUMENT;
    }

    am_boot_kft_packet_dev_t *p_dev = (am_boot_kft_packet_dev_t *)p_arg;

    /* Send ACK if needed. */
    int32_t status = __send_deferred_ack(p_dev);
    if (status != AM_BOOT_KFT_STATUS_SUCCESS) {
        return status;
    }

    /* Back-to-back writes require delay for receiver to enter peripheral read routine. */
    if (__g_serial_context.is_back_to_back_write) {
        __g_serial_context.is_back_to_back_write = false;

    }

    /* Initialize the framing data packet. */
    am_boot_kft_serial_framing_packet_t *framing_packet = &__g_serial_context.framing_packet;
    framing_packet->data_packet.header.start_byte       = AM_BOOT_KFT_FRAMING_PACKET_START_BYTE;
    framing_packet->data_packet.header.packet_type      = AM_BOOT_KFT_FRAMING_PACKET_TYPE_COMMAND;
    if (packet_type != AM_BOOT_KFT_PACKET_TYPE_COMMAND) {
        framing_packet->data_packet.header.packet_type = AM_BOOT_KFT_FRAMING_PACKET_TYPE_DATA;
    }
    framing_packet->data_packet.length = (uint16_t)byte_count;

    /* Copy the caller's data buffer into the framing packet. */
    if (byte_count) {
        memcpy(framing_packet->data, p_packet, byte_count);
    }

    /* Calculate and set the framing packet crc. */
    framing_packet->data_packet.crc16 = __calculate_framing_crc16(
            &framing_packet->data_packet, (uint8_t *)framing_packet->data);
    /* Send the framing data packet. */
    status = __write_data(p_dev,
                         (uint8_t *)framing_packet,
                          sizeof(am_boot_kft_framing_data_packet_t) + byte_count);
    if (status != AM_BOOT_KFT_STATUS_SUCCESS) {
        return status;
    }

    return __wait_for_ack_packet(p_dev);
}

static void __serial_packet_abort(void *p_arg)
{

    assert(__g_serial_context.is_ack_needed);
    __g_serial_context.is_ack_abort_needed = AM_TRUE;
    __g_serial_context.is_ack_needed = AM_FALSE;
}

static uint32_t __serial_packet_get_max_packet_size(void *p_arg)
{
    return AM_BOOT_KFT_MIN_PACKET_BUFFER_SIZE;
}

/**
 * \brief See serial_packet.h for documentation on this function.
 */
static int32_t __serial_packet_send_sync(am_boot_kft_packet_dev_t *p_dev,
                                         uint8_t                   framing_packet_type)
{
    am_boot_kft_framing_sync_packet_t sync;
    sync.header.start_byte  = AM_BOOT_KFT_FRAMING_PACKET_START_BYTE;
    sync.header.packet_type = framing_packet_type;

    /* Indicate last transaction was a write. */
    __g_serial_context.is_back_to_back_write = true;

    int32_t status = __write_data(p_dev,(uint8_t *)&sync, sizeof(sync));
    if (status != AM_BOOT_KFT_STATUS_SUCCESS) {
        am_kprintf("Error: cannot send sync packet 0x%x, status = 0x%x\r\n", framing_packet_type, status);
        return status;
    }

    return status;
}

/**
 * \brief 等待一个ack
 */
static int32_t __wait_for_ack_packet(am_boot_kft_packet_dev_t *p_dev)
{
    am_boot_kft_framing_sync_packet_t sync;
    do {
        /* Receive the sync packet. */
        int32_t status = __read_header(&sync.header);
        if (status != AM_BOOT_KFT_STATUS_SUCCESS) {
            return status;
        }

        if ((sync.header.packet_type != AM_BOOT_KFT_FRAMING_PACKET_TYPE_ACK) &&
            (sync.header.packet_type != AM_BOOT_KFT_FRAMING_PACKET_TYPE_NAK) &&
            (sync.header.packet_type != AM_BOOT_KFT_FRAMING_PACKET_TYPE_ACK_ABORT)) {

            am_kprintf("Error: Unexpected sync byte 0x%x received, expected Ack, AckAbort or Nak\r\n",
                         sync.header.packet_type);
            return AM_BOOT_KFT_STATUS_INVALID_ARGUMENT;
        }

        if (sync.header.packet_type == AM_BOOT_KFT_FRAMING_PACKET_TYPE_ACK_ABORT) {
            return  AM_BOOT_KFT_STATUS_ABORT_DATA_PHASE;
        }

        if (sync.header.packet_type == AM_BOOT_KFT_FRAMING_PACKET_TYPE_NAK) {
            /* Re-transmit the last packet. */
            status = __write_data(p_dev,
                                 (uint8_t *)&__g_serial_context.framing_packet,
                                  sizeof(am_boot_kft_framing_data_packet_t) + \
                                  __g_serial_context.framing_packet.data_packet.length);
            if (status != AM_BOOT_KFT_STATUS_SUCCESS) {
                return status;
            }
        }
    } while (sync.header.packet_type == AM_BOOT_KFT_FRAMING_PACKET_TYPE_NAK);

    return AM_BOOT_KFT_STATUS_SUCCESS;
}

/**
 * \brief 发送ping回应
 */
static int32_t __serial_send_ping_response(am_boot_kft_packet_dev_t *p_dev)
{
    const uint8_t header[] = \
        { AM_BOOT_KFT_FRAMING_PACKET_START_BYTE, AM_BOOT_KFT_FRAMING_PACKET_TYPE_PING_RESPONSE };
    assert(p_dev);

    /* Only reply if we're in an idle state */
    if (!__g_serial_context.is_ack_needed ||
        !__g_serial_context.is_back_to_back_write ||
        !__g_serial_context.is_ack_abort_needed) {

        am_boot_serial_byte_send(p_dev->serial_handle,
                                (const uint8_t *)&header,
                                 sizeof(header));
        am_boot_serial_byte_send(p_dev->serial_handle,
                                (uint8_t *)&kft_ping_response,
                                 sizeof(kft_ping_response));

    }
    return  AM_BOOT_KFT_STATUS_PING;
}

/**
 * \brief 发送ACK，如果需要
 */
static int32_t __send_deferred_ack(am_boot_kft_packet_dev_t *p_dev)
{
    if (__g_serial_context.is_ack_needed) {
        /* Send Ack for last received packet. */
        __g_serial_context.is_ack_needed = false;
        return __serial_packet_send_sync(p_dev, AM_BOOT_KFT_FRAMING_PACKET_TYPE_ACK);
    }
    else if (__g_serial_context.is_ack_abort_needed) {
        /* Send AckAbort for last received packet. */
        __g_serial_context.is_ack_abort_needed = false;
        return __serial_packet_send_sync(p_dev, AM_BOOT_KFT_FRAMING_PACKET_TYPE_ACK_ABORT);
    }
    else {
        return AM_BOOT_KFT_STATUS_SUCCESS;
    }
}

/**
 * \brief 写 buff 到外设直到所有字节被发送
 */
static int32_t __write_data(am_boot_kft_packet_dev_t *p_dev,const uint8_t *p_buffer, uint32_t byte_count)
{
    int32_t ret_val;
    ret_val =  am_boot_serial_byte_send(p_dev->serial_handle, p_buffer, byte_count);
    if(ret_val == byte_count) {
        return AM_BOOT_KFT_STATUS_SUCCESS;
    }
    return AM_BOOT_KFT_STATUS_FAIL;

}

/**
 * \brief 从外设读取直到收到规定的字节数
 */
static int32_t __read_data(uint8_t *p_buffer, uint32_t byte_count, uint32_t timeout_ms)
{
    /* On the target we read from our interrupt buffer */
    uint32_t current_bytes_read = 0;
//    uint64_t startTicks = am_sys_tick_get();
//    uint64_t timeOutTicks = am_ms_to_ticks(timeout_ms * 1000);
//    uint64_t endTicks = startTicks;
//    uint64_t deltaTicks = 0;

    while (current_bytes_read != byte_count)
    {
//        endTicks = am_sys_tick_get();
//        deltaTicks = endTicks - startTicks;

        // Check timer roll over
//        if (endTicks < startTicks)
//        {
//            deltaTicks = endTicks + (~startTicks) + 1;
//        }
//
//        if (timeOutTicks && (deltaTicks >= timeOutTicks))
//        {
//            return BL_int32_tIMEOUT;
//        }

        if (__g_serial_context.read_offset != __g_serial_context.write_offset)
        {
            p_buffer[current_bytes_read++] = __g_serial_context.callback_buffer[__g_serial_context.read_offset++];

            __g_serial_context.read_offset &= AM_BOOT_KFT_CALLBACK_BUFFER_SIZE - 1;
        }
    }

    return AM_BOOT_KFT_STATUS_SUCCESS;
}

/**
 * \brief 从外设读取直到读到整个数据帧
 */
static int32_t __read_data_packet(
    am_boot_kft_packet_dev_t               *p_dev,
    am_boot_kft_framing_data_packet_t      *packet,
    uint8_t                                *data,
    am_boot_kft_packet_type_t               packetType)
{
    /* Read the packet header. */
    int32_t status = __read_header(&packet->header);
    if (status != AM_BOOT_KFT_STATUS_SUCCESS) {
        return status;
    }
    if (packet->header.packet_type == AM_BOOT_KFT_FRAMING_PACKET_TYPE_PING) {
        return __serial_send_ping_response(p_dev);
    }

    uint8_t expected_packet_type = AM_BOOT_KFT_FRAMING_PACKET_TYPE_COMMAND;

    if (packetType != AM_BOOT_KFT_PACKET_TYPE_COMMAND) {
        expected_packet_type = AM_BOOT_KFT_FRAMING_PACKET_TYPE_DATA;
    }
    if (packet->header.packet_type != expected_packet_type) {
        am_kprintf("Error: read_data_packet found unexpected packet type 0x%x\r\n", packet->header.packet_type);
        return AM_BOOT_KFT_STATUS_FAIL;
    }

    /* Read the packet length. */
    status = __read_length(packet);
    if (status != AM_BOOT_KFT_STATUS_SUCCESS) {
        return status;
    }

    /* Make sure the packet doesn't exceed the allocated buffer size. */
    packet->length = min(AM_BOOT_KFT_INCOMING_PACKET_BUFFER_SIZE, packet->length);

    /* Read the crc */
    status = __read_crc16(packet);
    if (status != AM_BOOT_KFT_STATUS_SUCCESS) {
        return status;
    }

    /* Read the data. */
    if (packet->length > 0) {
        /* Clear the data area so unsent parameters default to zero. */
        memset(data, 0, packet->length);

        status = __read_data(data, packet->length, AM_BOOT_KFT_DEFAULT_BYTE_READ_TIMEOUT_MS * packet->length);
    }

    return status;
}

/**
 * \brief 从外设读取直到起始字节被找到
 */
static int32_t __read_start_byte(am_boot_kft_framing_header_t *header)
{
    /* Read until start byte found. */
    do {
        int32_t status = __read_data(&header->start_byte, 1, 0); // no timeout for first byte of packet
        if (status != AM_BOOT_KFT_STATUS_SUCCESS) {
            return status;
        }

    } while (header->start_byte != AM_BOOT_KFT_FRAMING_PACKET_START_BYTE);

    return AM_BOOT_KFT_STATUS_SUCCESS;
}

/**
 * \brief 从外设读取直到包头部被找到
 */
static int32_t __read_header(am_boot_kft_framing_header_t *header)
{
    /*  Wait for start byte. */
    int32_t status = __read_start_byte(header);
    if (status != AM_BOOT_KFT_STATUS_SUCCESS) {
        return status;
    }

    return __read_data(&header->packet_type,
                       sizeof(header->packet_type),
                       AM_BOOT_KFT_DEFAULT_BYTE_READ_TIMEOUT_MS * sizeof(header->packet_type));
}

/**
 * \brief 从外设读取直到包长度被找到
 */
static int32_t __read_length(am_boot_kft_framing_data_packet_t *packet)
{
    union {
        uint8_t bytes[sizeof(uint16_t)];
        uint16_t halfword;
    } buffer;

    int32_t status = __read_data((uint8_t *)&buffer.bytes,
                                  sizeof(buffer),
                                  AM_BOOT_KFT_DEFAULT_BYTE_READ_TIMEOUT_MS * sizeof(buffer));

    packet->length = buffer.halfword;
    return status;
}

/**
 * \brief 从外设读取直到crc16被找到
 */
static int32_t __read_crc16(am_boot_kft_framing_data_packet_t *p_packet)
{
    union {
        uint8_t bytes[sizeof(uint16_t)];
        uint16_t halfword;
    } buffer;

    int32_t status = __read_data((uint8_t *)&buffer.bytes,
                                  sizeof(buffer),
                                  AM_BOOT_KFT_DEFAULT_BYTE_READ_TIMEOUT_MS * sizeof(buffer));

    p_packet->crc16 = buffer.halfword;
    return status;
}

/**
 * \brief 计算帧数据包上的crc
 */
static uint16_t __calculate_framing_crc16(am_boot_kft_framing_data_packet_t *p_packet, const uint8_t *p_data)
{
    uint32_t crc16;
    am_crc_pattern_t crc_pattern;

    crc_pattern.width     = 16;
    crc_pattern.poly      = 0x1021;
    crc_pattern.initvalue = 0x0000;
    crc_pattern.refin     = AM_FALSE;
    crc_pattern.refout    = AM_FALSE;
    crc_pattern.xorout    = 0x0000;

    am_crc_init (__g_packet_dev.crc_handle, &crc_pattern);

    am_crc_cal (__g_packet_dev.crc_handle,
               (uint8_t *)&p_packet->header.start_byte,
                sizeof(am_boot_kft_framing_data_packet_t) - sizeof(uint16_t));

    am_crc_cal (__g_packet_dev.crc_handle,
                p_data,
                p_packet->length);

    am_crc_final (__g_packet_dev.crc_handle, &crc16);

    return crc16;
}

/* end of file */
