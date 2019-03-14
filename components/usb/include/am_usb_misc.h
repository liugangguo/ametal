/**
 * \file
 * \brief     USB
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-27  bob, first implementation.
 * \endinternal
 */

#ifndef __AM_USB_MISC_H
#define __AM_USB_MISC_H

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
 * Definitions
 ******************************************************************************/
extern int am_kprintf(const char  *fmt_s, ...);

#define usb_echo am_kprintf

#if defined(__ICCARM__)

#ifndef STRUCT_PACKED
#define STRUCT_PACKED __packed
#endif

#ifndef STRUCT_UNPACKED
#define STRUCT_UNPACKED
#endif

#elif defined(__GNUC__)

#ifndef STRUCT_PACKED
#define STRUCT_PACKED
#endif

#ifndef STRUCT_UNPACKED
#define STRUCT_UNPACKED __attribute__((__packed__))
#endif

#elif defined(__CC_ARM)

#ifndef STRUCT_PACKED
#define STRUCT_PACKED _Pragma("pack(1U)")
#endif

#ifndef STRUCT_UNPACKED
#define STRUCT_UNPACKED _Pragma("pack()")
#endif

#endif

#define AM_USB_SHORT_GET_LOW(x)  (((uint16_t)x) & 0xFFU)                  /* 获取高低位 */
#define AM_USB_SHORT_GET_HIGH(x) ((uint8_t)(((uint16_t)x) >> 8U) & 0xFFU) /* 获取高位. */

#define AM_USB_LONG_GET_BYTE0(x) ((uint8_t)(((uint32_t)(x))) & 0xFFU)
#define AM_USB_LONG_GET_BYTE1(x) ((uint8_t)(((uint32_t)(x)) >> 8U) & 0xFFU)
#define AM_USB_LONG_GET_BYTE2(x) ((uint8_t)(((uint32_t)(x)) >> 16U) & 0xFFU)
#define AM_USB_LONG_GET_BYTE3(x) ((uint8_t)(((uint32_t)(x)) >> 24U) & 0xFFU)

#define AM_USB_MEM4_ALIGN_MASK   (0x03U)

/* accessory macro */
#define AM_USB_MEM4_ALIGN(n)     ((n + 3U) & (0xFFFFFFFCu))
#define AM_USB_MEM32_ALIGN(n)    ((n + 31U) & (0xFFFFFFE0u))
#define AM_USB_MEM64_ALIGN(n)    ((n + 63U) & (0xFFFFFFC0u))

/* big/little endian */
#define AM_SWAP2BYTE_CONST(n)    ((((n)&0x00FFU) << 8U) | (((n)&0xFF00U) >> 8U))
#define AM_SWAP4BYTE_CONST(n)    ((((n)&0x000000FFU) << 24U) | \
                                 (((n)&0x0000FF00U) << 8U)   | \
                                 (((n)&0x00FF0000U) >> 8U)   | \
                                 (((n)&0xFF000000U) >> 24U))

#if (AM_ENDIANNESS == AM_USB_BIG_ENDIAN)

#define AM_USB_SHORT_TO_LITTLE_ENDIAN(n)   AM_SWAP2BYTE_CONST(n)
#define AM_USB_LONG_TO_LITTLE_ENDIAN(n)    AM_SWAP4BYTE_CONST(n)
#define AM_USB_SHORT_FROM_LITTLE_ENDIAN(n) AM_SWAP2BYTE_CONST(n)
#define AM_USB_LONG_FROM_LITTLE_ENDIAN(n)  AM_SWAP2BYTE_CONST(n)

#define AM_USB_SHORT_TO_BIG_ENDIAN(n)      (n)
#define AM_USB_LONG_TO_BIG_ENDIAN(n)       (n)
#define AM_USB_SHORT_FROM_BIG_ENDIAN(n)    (n)
#define AM_USB_LONG_FROM_BIG_ENDIAN(n)     (n)

#define AM_USB_LONG_TO_LITTLE_ENDIAN_ADDRESS(n, m) \
    {                                              \
        m[0] = ((n >> 24U) & 0xFFU);               \
        m[1] = ((n >> 16U) & 0xFFU);               \
        m[2] = ((n >> 8U) & 0xFFU);                \
        m[3] = (n & 0xFFU);                        \
    }

#define USB_LONG_FROM_LITTLE_ENDIAN_ADDRESS(n)     \
    ((uint32_t)(((uint32_t)n[0] << 24U) |          \
    ((uint32_t)n[1] << 16U)             |          \
    ((uint32_t)n[2] << 8U)              |          \
    ((uint32_t)n[3] << 0U)))

#define USB_LONG_TO_BIG_ENDIAN_ADDRESS(n, m)       \
    {                                              \
        m[3] = ((n >> 24U) & 0xFFU);               \
        m[2] = ((n >> 16U) & 0xFFU);               \
        m[1] = ((n >> 8U) & 0xFFU);                \
        m[0] = (n & 0xFFU);                        \
    }

#define USB_LONG_FROM_BIG_ENDIAN_ADDRESS(n)        \
    ((uint32_t)(((uint32_t)n[3] << 24U) |          \
    ((uint32_t)n[2] << 16U)             |          \
    ((uint32_t)n[1] << 8U)              |          \
    ((uint32_t)n[0] << 0U)))

#define USB_SHORT_TO_LITTLE_ENDIAN_ADDRESS(n, m)   \
    {                                              \
        m[0] = ((n >> 8U) & 0xFFU);                \
        m[1] = (n & 0xFFU);                        \
    }

#define USB_SHORT_FROM_LITTLE_ENDIAN_ADDRESS(n) ((uint32_t)(((uint32_t)n[0] << 8U) | ((uint32_t)n[1] << 0U)))

#define USB_SHORT_TO_BIG_ENDIAN_ADDRESS(n, m)      \
    {                                              \
        m[1] = ((n >> 8U) & 0xFFU);                \
        m[0] = (n & 0xFFU);                        \
    }

#define USB_SHORT_FROM_BIG_ENDIAN_ADDRESS(n) ((uint32_t)(((uint32_t)n[1] << 8U) | ((uint32_t)n[0] << 0U)))

#else

#define AM_USB_SHORT_TO_LITTLE_ENDIAN(n)     (n)
#define AM_USB_LONG_TO_LITTLE_ENDIAN(n)      (n)
#define AM_USB_SHORT_FROM_LITTLE_ENDIAN(n)   (n)
#define AM_USB_LONG_FROM_LITTLE_ENDIAN(n)    (n)

#define AM_USB_SHORT_TO_BIG_ENDIAN(n)        AM_SWAP2BYTE_CONST(n)
#define AM_USB_LONG_TO_BIG_ENDIAN(n)         AM_SWAP4BYTE_CONST(n)
#define AM_USB_SHORT_FROM_BIG_ENDIAN(n)      AM_SWAP2BYTE_CONST(n)
#define AM_USB_LONG_FROM_BIG_ENDIAN(n)       AM_SWAP4BYTE_CONST(n)

#define AM_USB_LONG_TO_LITTLE_ENDIAN_ADDRESS(n, m)  \
    {                                               \
        m[3] = ((n >> 24U) & 0xFFU);                \
        m[2] = ((n >> 16U) & 0xFFU);                \
        m[1] = ((n >> 8U) & 0xFFU);                 \
        m[0] = (n & 0xFFU);                         \
    }

#define AM_USB_LONG_FROM_LITTLE_ENDIAN_ADDRESS(n)   \
    ((uint32_t)(((uint32_t)n[3] << 24U) |           \
    ((uint32_t)n[2] << 16U)             |           \
    ((uint32_t)n[1] << 8U)              |           \
    ((uint32_t)n[0] << 0U)))

#define AM_USB_LONG_TO_BIG_ENDIAN_ADDRESS(n, m)     \
    {                                               \
        m[0] = ((n >> 24U) & 0xFFU);                \
        m[1] = ((n >> 16U) & 0xFFU);                \
        m[2] = ((n >> 8U) & 0xFFU);                 \
        m[3] = (n & 0xFFU);                         \
    }

#define AM_USB_LONG_FROM_BIG_ENDIAN_ADDRESS(n)      \
    ((uint32_t)(((uint32_t)n[0] << 24U)   |         \
    ((uint32_t)n[1] << 16U)               |         \
    ((uint32_t)n[2] << 8U)                |         \
    ((uint32_t)n[3] << 0U)))

#define AM_USB_SHORT_TO_LITTLE_ENDIAN_ADDRESS(n, m) \
    {                                               \
        m[1] = ((n >> 8U) & 0xFFU);                 \
        m[0] = (n & 0xFFU);                         \
    }

#define AM_USB_SHORT_FROM_LITTLE_ENDIAN_ADDRESS(n)  \
        ((uint32_t)(((uint32_t)n[1] << 8U) | ((uint32_t)n[0] << 0U)))

#define AM_USB_SHORT_TO_BIG_ENDIAN_ADDRESS(n, m)    \
    {                                               \
        m[0] = ((n >> 8U) & 0xFFU);                 \
        m[1] = (n & 0xFFU);                         \
    }

#define AM_USB_SHORT_FROM_BIG_ENDIAN_ADDRESS(n)     \
        ((uint32_t)(((uint32_t)n[0] << 8U) | ((uint32_t)n[1] << 0U)))
#endif



#if defined(__ICCARM__)

#define USB_GLOBAL _Pragma("location = \"m_usb_global\"")
#define USB_BDT _Pragma("location = \"m_usb_bdt\"")
#define USB_RAM_ADDRESS_ALGINMENT_512 _Pragma("data_alignment = 512U")

#elif defined(__CC_ARM)

#define USB_GLOBAL __attribute__((section("m_usb_global"))) __attribute__((zero_init))
#define USB_BDT __attribute__((section("m_usb_bdt"))) __attribute__((zero_init))
#define USB_RAM_ADDRESS_ALGINMENT_512 __attribute__((aligned(512U)))

#elif defined(__GNUC__)

#define USB_GLOBAL __attribute__((section("m_usb_global")))
#define USB_BDT __attribute__((section("m_usb_bdt")))

#define USB_RAM_ADDRESS_ALGINMENT_512 __attribute__((aligned(512U)))

#else
#error The tool-chain is not supported.
#endif

#ifdef __cplusplus
}
#endif

#endif /* __AM_USB_MISC_H */
