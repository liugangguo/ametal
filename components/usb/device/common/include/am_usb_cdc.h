/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief USBD CDC
 *
 * \internal
 * \par Modification history
 * - 1.00 19-02-21  adw, first implementation.
 * \endinternal
 */

#ifndef __AM_USB_CDC_H
#define __AM_USB_CDC_H

#include "am_usb.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/
/**
 * \brief class specific codes
 * \name @{
 */

/** \beief usb cdc code */
#define AM_USB_CDC_CODE                        (0x02U)

/** \beief usb cdc interface code */
#define AM_USB_CDC_COMM_CLASS                  (0x02U)
#define AM_USB_CDC_DATA_CLASS                  (0x0AU)

/** \brief usb cdc communication class subclass codes */
#define AM_USB_CDC_COMM_SUB_DIRE               (0x01U)
#define AM_USB_CDC_COMM_SUB_ABS                (0x02U)
#define AM_USB_CDC_COMM_SUB_TEL                (0x03U)
#define AM_USB_CDC_COMM_SUB_MULTI_CHAN         (0x04U)
#define AM_USB_CDC_COMM_SUB_CAPI               (0x05U)
#define AM_USB_CDC_COMM_SUB_ETH_NET            (0x06U)
#define AM_USB_CDC_COMM_SUB_ATM_NET            (0x07U)
#define AM_USB_CDC_COMM_SUB_WIRE_HANDSET       (0x08U)
#define AM_USB_CDC_COMM_SUB_DEVICE_MANAGE      (0x09U)
#define AM_USB_CDC_COMM_SUB_MOBILE_DIRE_LINE   (0x0AU)
#define AM_USB_CDC_COMM_SUB_OBEX               (0x0BU)
#define AM_USB_CDC_COMM_SUB_ETH_EMULATION      (0x0CU)
#define AM_USB_CDC_COMM_SUB_NETWORK            (0x0DU)

/** \brief data interface class protocol codes*/
#define AM_USB_CDC_DATA_INTERFACE_SUB          (0X00U)

/** \brief communications class protocol code*/
#define AM_USB_CDC_COMM_PROT_NO_PROT           (0x00U)
#define AM_USB_CDC_COMM_PROT_AT_ITU_T          (0x01U)
#define AM_USB_CDC_COMM_PROT_AT_PCCA           (0x02U)
#define AM_USB_CDC_COMM_PROT_AT_PCCA_O         (0x03U)
#define AM_USB_CDC_COMM_PROT_AT_GSM            (0x04U)
#define AM_USB_CDC_COMM_PROT_AT_3GPP           (0x05U)
#define AM_USB_CDC_COMM_PROT_AT_C_S0017        (0x06U)
#define AM_USB_CDC_COMM_PROT_AT_USB_EEM        (0x07U)
#define AM_USB_CDC_COMM_PROT_CUSTOMER          (0xFEU)
#define AM_USB_CDC_COMM_PROT_VENDOR            (0xFFU)

/** \brief data interface class protocol codes */
#define AM_USB_CDC_INTER_PROT_NO_PROT          (0X00U)
#define AM_USB_CDC_INTER_PROT_NCM              (0X01U)
#define AM_USB_CDC_INTER_PROT_I430             (0X30U)
#define AM_USB_CDC_INTER_PROT_HDLC             (0X31U)
#define AM_USB_CDC_INTER_PROT_TRANSPARENT      (0X32U)
#define AM_USB_CDC_INTER_PROT_Q921M            (0X50U)
#define AM_USB_CDC_INTER_PROT_Q921             (0X51U)
#define AM_USB_CDC_INTER_PROT_Q921TM           (0X52U)
#define AM_USB_CDC_INTER_PROT_V42BIS           (0X90U)
#define AM_USB_CDC_INTER_PROT_EURO_ISDN        (0X91U)
#define AM_USB_CDC_INTER_PROT_V120             (0X92U)
#define AM_USB_CDC_INTER_PROT_CAPI20           (0X93U)
#define AM_USB_CDC_INTER_PROT_HOST_BASED       (0XFDU)
#define AM_USB_CDC_INTER_PROT_CDC_SPEC         (0XFEU)
#define AM_USB_CDC_INTER_PROT_USB_SPEC         (0XFFU)

/** }@ */

/**
 * \brief bDescriptor Type in Communications Class Functional Descriptors
 * \name {
 */
#define AM_USB_CDC_FUNC_DESC_TYPE_CS_INTERFACE      (0x24U)
#define AM_USB_CDC_FUNC_DESC_TYPE_CS_ENDPOINT       (0x25U)
/** }@ */

/**
 * \brief bDescriptor SubType in Communications Class Functional Descriptors
 * \name {
 */

#define AM_USB_CDC_SUBTYPE_HEADER              (0X00U)
#define AM_USB_CDC_SUBTYPE_CALL_MANAGE         (0X01U)
#define AM_USB_CDC_SUBTYPE_ABST_CTRL           (0X02U)
#define AM_USB_CDC_SUBTYPE_DIRECT_LINE         (0X03U)
#define AM_USB_CDC_SUBTYPE_TEL_RANGER          (0X04U)
#define AM_USB_CDC_SUBTYPE_TEL_CALL_LINESTA    (0X05U)
#define AM_USB_CDC_SUBTYPE_UNION               (0X06U)
#define AM_USB_CDC_SUBTYPE_COUNTRY_SELECT      (0X07U)
#define AM_USB_CDC_SUBTYPE_TEL_OPERATION       (0X08U)
#define AM_USB_CDC_SUBTYPE_USB_TERM            (0X09U)
#define AM_USB_CDC_SUBTYPE_NET_CHAN_TERM       (0X0AU)
#define AM_USB_CDC_SUBTYPE_PROT_UNIT           (0X0BU)
#define AM_USB_CDC_SUBTYPE_EXTENSION_UINT      (0X0CU)
#define AM_USB_CDC_SUBTYPE_MULTI_CHAN          (0X0DU)
#define AM_USB_CDC_SUBTYPE_CAPI_CTRL           (0X0EU)
#define AM_USB_CDC_SUBTYPE_ETH_NET             (0X0FU)
#define AM_USB_CDC_SUBTYPE_ATM_NET             (0X10U)
#define AM_USB_CDC_SUBTYPE_WIRE_HANDSET        (0X11U)
#define AM_USB_CDC_SUBTYPE_MOBILE_LINE         (0X12U)
#define AM_USB_CDC_SUBTYPE_MDLM                (0X13U)
#define AM_USB_CDC_SUBTYPE_DEV_MANAGE          (0X14U)
#define AM_USB_CDC_SUBTYPE_OBEX                (0X15U)
#define AM_USB_CDC_SUBTYPE_CMD_SET             (0X16U)
#define AM_USB_CDC_SUBTYPE_CMD_DETAIL          (0X17U)
#define AM_USB_CDC_SUBTYPE_TEL_CTRL            (0X18U)
#define AM_USB_CDC_SUBTYPE_OBEX_SERV           (0X19U)
#define AM_USB_CDC_SUBTYPE_NCM                 (0X1AU)

/** @} */

/**
 * \brief  USB CDC Class specific request Codes
 * \name @{
 */
#define AM_USB_CDC_REQ_SEND_ENCAP_CMD           (0x00U)
#define AM_USB_CDC_REQ_GET_ENCAP_RESPONSE       (0x01U)
#define AM_USB_CDC_REQ_SET_COMM_FEATURE         (0x02U)
#define AM_USB_CDC_REQ_GET_COMM_FEATURE         (0x03U)
#define AM_USB_CDC_REQ_CLEAR_COMM_FEATURE       (0x04U)
#define AM_USB_CDC_REQ_SET_AUX_LINE_STATE       (0x10U)
#define AM_USB_CDC_REQ_SET_HOOK_STATE           (0x11U)
#define AM_USB_CDC_REQ_PULSE_SETUP              (0x12U)
#define AM_USB_CDC_REQ_SEND_PULSE               (0x13U)
#define AM_USB_CDC_REQ_SET_PULSE_TIME           (0x14U)
#define AM_USB_CDC_REQ_RING_AUX_JACK            (0x15U)
#define AM_USB_CDC_REQ_SET_LINE_CODING          (0x20U)
#define AM_USB_CDC_REQ_GET_LINE_CODING          (0x21U)
#define AM_USB_CDC_REQ_SET_CTRL_LINE_STATE      (0x22U)
#define AM_USB_CDC_REQ_SEND_BREAK               (0x23U)
#define AM_USB_CDC_REQ_SET_RINGER_PAR           (0x30U)
#define AM_USB_CDC_REQ_GET_RINGER_PAR           (0x31U)
#define AM_USB_CDC_REQ_SET_OPERATION_PAR        (0x32U)
#define AM_USB_CDC_REQ_GET_OPERATION_PAR        (0x33U)
#define AM_USB_CDC_REQ_SET_LINE_PAR             (0x34U)
#define AM_USB_CDC_REQ_GET_LINE_PAR             (0x35U)
#define AM_USB_CDC_REQ_DIAL_DIGITS              (0x36U)
#define AM_USB_CDC_REQ_SET_UNIT_PAR             (0x37U)
#define AM_USB_CDC_REQ_GET_UNIT_PAR             (0x38U)
#define AM_USB_CDC_REQ_CLEAR_UNIT_PAR           (0x39U)
#define AM_USB_CDC_REQ_GET_PROFILE              (0x3AU)
#define AM_USB_CDC_REQ_SET_ETH_MULT_FILTERS     (0x40U)
#define AM_USB_CDC_REQ_SET_ETH_POW_PAT_FILTER   (0x41U)
#define AM_USB_CDC_REQ_GET_ETH_POW_PAT_FILTER   (0x42U)
#define AM_USB_CDC_REQ_SET_ETH_PACKET_FILTER    (0x43U)
#define AM_USB_CDC_REQ_GET_ETH_STAT             (0x44U)
#define AM_USB_CDC_REQ_SET_ATM_DATA_FORMAT      (0x50U)
#define AM_USB_CDC_REQ_GET_ATM_DEVICE_STAT      (0x51U)
#define AM_USB_CDC_REQ_SET_ATM_DEFAULT_VC       (0x52U)
#define AM_USB_CDC_REQ_GET_ATM_VC_STAT          (0x53U)
#define AM_USB_CDC_REQ_MDLM_SPEC_REQ_MASK       (0x7FU)

#define AM_USB_CDC_REQ_GET_NTB_PAR              (0x80U)
#define AM_USB_CDC_REQ_GET_NET_ADDR             (0x81U)
#define AM_USB_CDC_REQ_SET_NET_ADDR             (0x82U)
#define AM_USB_CDC_REQ_GET_NTB_FORMAT           (0x83U)
#define AM_USB_CDC_REQ_SET_NTB_FORMAT           (0x84U)
#define AM_USB_CDC_REQ_GET_NTB_INPUT_SIZE       (0x85U)
#define AM_USB_CDC_REQ_SET_NTB_INPUT_SIZE       (0x86U)
#define AM_USB_CDC_REQ_GET_MAX_DATA_SIZE        (0x87U)
#define AM_USB_CDC_REQ_SET_MAX_DATA_SIZE        (0x88U)
#define AM_USB_CDC_REQ_GET_CRC_MODE             (0x89U)
#define AM_USB_CDC_REQ_SET_CRC_MODE             (0x8AU)
/** @} */

/**
 * \brief Class Specific Notification Codes
 * \name @{
 */
#define AM_USB_CDC_REQ_NET_CONNECTION           (0x00U)
#define AM_USB_CDC_REQ_RESPONSE_AVAIL           (0x01U)
#define AM_USB_CDC_REQ_AUX_JACK_HOOK_STATE      (0x08U)
#define AM_USB_CDC_REQ_RING_DETECT              (0x09U)
#define AM_USB_CDC_REQ_SERIAL_STATE             (0x20U)
#define AM_USB_CDC_REQ_CALL_STATE_CHANGE        (0x28U)
#define AM_USB_CDC_REQ_LINE_STATE_CHANGE        (0x29U)
#define AM_USB_CDC_REQ_CONNECT_SPEED_CHAN       (0x2AU)
/** @} */

/**
 * \brief Communications Feature Selector Codes
 * \name @{
 */
#define AM_USB_CDC_FEATURE_ABST_STATE           (0x01U)
#define AM_USB_CDC_FEATURE_COUNTRY_SET          (0x02U)
/** @} */

/**
 * \brief Control Signal Bitmap Values
 * \name @{
 */
#define AM_USB_CDC_CTRL_SIG_BITMAP_CARRIER_ACT  (0x02U)
#define AM_USB_CDC_CTRL_SIG_BITMAP_DTE_PRESENCE (0x01U)
/** @} */

/**
 * \brief UART State Bitmap Values
 * \name @{
 */
#define AM_USB_CDC_UART_STATE_RX_CARRIER        (0x01U)
#define AM_USB_CDC_UART_STATE_TX_CARRIER        (0x02U)
#define AM_USB_CDC_UART_STATE_BREAK             (0x04U)
#define AM_USB_CDC_UART_STATE_RING_SIGNAL       (0x08U)
#define AM_USB_CDC_UART_STATE_FRAMING           (0x10U)
#define AM_USB_CDC_UART_STATE_PARITY            (0x20U)
#define AM_USB_CDC_UART_STATE_OVERRUN           (0x40U)
/** @} */

/* usb descritpor length */
#define AM_USB_DESC_LENGTH_CDC_HEADER_FUNC      (5)
#define AM_USB_DESC_LENGTH_CDC_CALL_MANAG       (5)
#define AM_USB_DESC_LENGTH_CDC_ABSTRACT         (4)
#define AM_USB_DESC_LENGTH_CDC_UNION_FUNC       (5)

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

// todo will test
typedef struct am_usb_cdc_descriptor_spec_class {
    /* header Functional Descriptor*/
    uint8_t b_function_length_h;             /**< \brief Size of this functional descriptor. */
    uint8_t b_Descriptor_Type_h;             /**< \brief CS_INTERFACE*/
    uint8_t b_Descriptor_Subtype_h;          /**< \brief Header*/
    uint8_t b_cdCDC_h[2];                    /**< \brief release number in binary-coded decimal*/

    /* call management functional descriptor */
    uint8_t b_FunctionLength_c;              /**< \brief Size of this functional descriptor*/
    uint8_t b_DescriptorType_c;              /**< \brief CS_INTERFACE*/
    uint8_t b_DescriptorSubtype_c;           /**< \brief Call Management Functional Descriptor subtype */
    uint8_t b_mCapabilities_c;               /**< \brief Indicate that the device handles call management itself*/
    uint8_t b_DataInterface_c;               /**< \brief Indicates that multiplexed commands are handled via data interface */

    /* Abstract control  management functional descriptor */
    uint8_t b_Function_Length_a;             /**< \brief Size of this functional descriptor*/
    uint8_t b_Descriptor_Type_a;             /**< \brief CS_INTERFACE*/
    uint8_t b_Descriptor_Subtype_a;          /**< \brief Abstract Control Management functional descriptor subtype*/
    uint8_t bm_Capabilities_a;               /**< \brief  the device supports all the corresponding commands*/

    /* union functional Descriptor */
    uint8_t b_FunctionLength_u;              /**< \brief Size of this functional descriptor*/
    uint8_t b_Descriptor_Type_u;             /**< \brief CS_INTERFACE*/
    uint8_t b_DescriptorSubtype_u;           /**< \brief Union Descriptor Functional Descriptor subtype */
    uint8_t b_ControlInterface_u;            /**< \brief Interface number of the control */
    uint8_t b_SubordinateInterface0_u;       /**< \brief Interface number of the subordinate */

} am_usb_cdc_descriptor_spec_class_t;

#if defined(__cplusplus)
}
#endif


#endif /* __AM_USB_CDC_H */

/* end of file */



