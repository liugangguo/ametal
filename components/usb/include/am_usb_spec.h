/**
 * \file
 * \brief     USB
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-27  bob, first implementation.
 * \endinternal
 */

#ifndef __AM_USB_SPEC_H
#define __AM_USB_SPEC_H

#include "am_usb.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* USB speed */
#define AM_USB_SPEED_FULL (0x00U)
#define AM_USB_SPEED_LOW  (0x01U)
#define AM_USB_SPEED_HIGH (0x02U)

/* USB 端点类型
 * @{
 */
#define AM_USB_ENDPOINT_CONTROL                      (0x00U)
#define AM_USB_ENDPOINT_ISOCHRONOUS                  (0x01U)
#define AM_USB_ENDPOINT_BULK                         (0x02U)
#define AM_USB_ENDPOINT_INTERRUPT                    (0x03U)
/*}@*/

/* USB传输方向 */
#define AM_USB_OUT   (0U)
#define AM_USB_IN    (1U)

/* USB 各描述符长度 */
#define AM_USB_DESC_LENGTH_DEVICE              (0x12U)
#define AM_USB_DESC_LENGTH_CONFIGURE           (0x09U)
#define AM_USB_DESC_LENGTH_INTERFACE           (0x09U)
#define AM_USB_DESC_LENGTH_HID                 (0x09U)
#define AM_USB_DESC_LENGTH_ENDPOINT            (0x07U)
#define AM_USB_DESC_LENGTH_ALL(x)        \
		(AM_USB_DESC_LENGTH_CONFIGURE +  \
		 AM_USB_DESC_LENGTH_INTERFACE +  \
		 (x * AM_USB_DESC_LENGTH_ENDPOINT))

#define AM_USB_DESC_LENGTH_DEVICE_QUALITIER    (0x0AU)

/* USB 描述符类型 */
#define AM_USB_DESC_TYPE_DEVICE                (0x01U)        /* 设备描述符. */
#define AM_USB_DESC_TYPE_CONFIGURE             (0x02U)        /* 配置型描述符. */
#define AM_USB_DESC_TYPE_STRING                (0x03U)        /* 字符串描述符. */
#define AM_USB_DESC_TYPE_INTERFACE             (0x04U)        /* 接口描述符 */
#define AM_USB_DESC_TYPE_ENDPOINT              (0x05U)        /* 端点描述符.  */
#define AM_USB_DESC_TYPE_DEVICE_QUALITIER      (0x06U)
#define AM_USB_DESC_TYPE_OTHER_SPEED_CONFIG    (0x07U)
#define AM_USB_DESC_TYPE_INTERFAACE_POWER      (0x08U)
#define AM_USB_DESC_TYPE_OTG                   (0x09U)
#define AM_USB_DESC_TYPE_INTERFACE_ASSOC       (0x0BU)

#define AM_USB_DESC_TYPE_HID                   (0x21U)     /* 人机接口类描述符. */
#define AM_USB_DESC_TYPE_HID_REPORT            (0x22U)     /* 报表描述符 */
#define AM_USB_DESC_TYPE_HID_PHY               (0x23U)     /* 实体描述符 */

/* USB 标准请求类型 */
#define AM_USB_REQ_TYPE_DIR_MASK                 (0x80U)
#define AM_USB_REQ_TYPE_DIR_SHIFT                (7U)
#define AM_USB_REQ_TYPE_DIR_OUT                  (0x00U)
#define AM_USB_REQ_TYPE_DIR_IN                   (0x80U)

#define AM_USB_REQ_TYPE_TYPE_MASK                (0x60U)
#define AM_USB_REQ_TYPE_TYPE_SHIFT               (5U)
#define AM_USB_REQ_TYPE_TYPE_STANDARD            (0U)
#define AM_USB_REQ_TYPE_TYPE_CLASS               (0x20U)
#define AM_USB_REQ_TYPE_TYPE_VENDOR              (0x40U)

#define AM_USB_REQ_TYPE_RECIPIENT_MASK           (0x1FU)
#define AM_USB_REQ_TYPE_RECIPIENT_SHIFT          (0U)
#define AM_USB_REQ_TYPE_RECIPIENT_DEVICE         (0x00U)
#define AM_USB_REQ_TYPE_RECIPIENT_INTERFACE      (0x01U)
#define AM_USB_REQ_TYPE_RECIPIENT_ENDPOINT       (0x02U)
#define AM_USB_REQ_TYPE_RECIPIENT_OTHER          (0x03U)

/* USB 标准请求 */
#define AM_USB_REQ_STANDARD_GET_STATUS           (0x00U)
#define AM_USB_REQ_STANDARD_CLEAR_FEATURE        (0x01U)
#define AM_USB_REQ_STANDARD_SET_FEATURE          (0x03U)
#define AM_USB_REQ_STANDARD_SET_ADDRESS          (0x05U)
#define AM_USB_REQ_STANDARD_GET_DESCRIPTOR       (0x06U)
#define AM_USB_REQ_STANDARD_SET_DESCRIPTOR       (0x07U)
#define AM_USB_REQ_STANDARD_GET_CONFIGURATION    (0x08U)
#define AM_USB_REQ_STANDARD_SET_CONFIGURATION    (0x09U)
#define AM_USB_REQ_STANDARD_GET_INTERFACE        (0x0AU)
#define AM_USB_REQ_STANDARD_SET_INTERFACE        (0x0BU)
#define AM_USB_REQ_STANDARD_SYNCH_FRAME          (0x0CU)

/* USB 标准请求设置或清除特性 */
#define AM_USB_REQ_STA_FEATURE_ENDPOINT_HALT        (0U)
#define AM_USB_REQ_STA_FEATURE_DEVICE_REMOTE_WAKEUP (1U)
#define AM_USB_REQ_STA_FEATURE_DEVICE_TEST_MODE     (2U)

/* USB 描述符配置属性 */
#define AM_USB_DESC_CONFIG_ATTR_D7_MASK                 (0x80U)
#define AM_USB_DESC_CONFIG_ATTR_D7_SHIFT                (7U)

#define AM_USB_DESC_CONFIG_ATTR_SELF_POWERED_MASK       (0x40U)
#define AM_USB_DESC_CONFIG_ATTR_SELF_POWERED_SHIFT      (6U)

#define AM_USB_DESC_CONFIG_ATTR_REMOTE_WAKEUP_MASK      (0x20U)
#define AM_USB_DESC_CONFIG_ATTR_REMOTE_WAKEUP_SHIFT     (5U)

/* USB 端点属性 */
#define AM_USB_DESC_ENDPOINT_ADDR_DIR_MASK             (0x80U)
#define AM_USB_DESC_ENDPOINT_ADDR_DIR_SHIFT            (7U)
#define AM_USB_DESC_ENDPOINT_ADDR_DIR_OUT              (0U)
#define AM_USB_DESC_ENDPOINT_ADDR_DIR_IN               (0x80U)

#define AM_USB_DESC_ENDPOINT_ADDR_NUMBER_MASK          (0x0FU)
#define AM_USB_DESC_ENDPOINT_ADDR_NUMBER_SHFIT         (0U)

#define AM_USB_DESC_ENDPOINT_ATTR_TYPE_MASK            (0x03U)
#define AM_USB_DESC_ENDPOINT_ATTR_NUMBER_SHFIT         (0U)

#define AM_USB_DESC_ENDPOINT_ATTR_SYNC_TYPE_MASK       (0x0CU)
#define AM_USB_DESC_ENDPOINT_ATTR_SYNC_TYPE_SHFIT      (2U)
#define AM_USB_DESC_ENDPOINT_ATTR_SYNC_TYPE_NSYNC      (0x00U)
#define AM_USB_DESC_ENDPOINT_ATTR_SYNC_TYPE_ASYNC      (0x04U)
#define AM_USB_DESC_ENDPOINT_ATTR_SYNC_TYPE_ADAPT      (0x08U)
#define AM_USB_DESC_ENDPOINT_ATTR_SYNC_TYPE_SYNC       (0x0CU)

#define AM_USB_DESC_ENDPOINT_ATTR_USAGE_TYPE_MASK           (0x30U)
#define AM_USB_DESC_ENDPOINT_ATTR_USAGE_TYPE_SHFIT          (4U)
#define AM_USB_DESC_ENDPOINT_ATTR_USAGE_TYPE_DATA           (0x00U)
#define AM_USB_DESC_ENDPOINT_ATTR_USAGE_TYPE_FEEDBACK       (0x10U)
#define AM_USB_DESC_ENDPOINT_ATTR_USAGE_TYPE_IFEEDBACK_DATA (0x20U)

#define AM_USB_DESC_ENDPOINT_MAXPACKETSIZE_MASK              (0x07FFu)
#define AM_USB_DESC_ENDPOINT_MAXPACKETSIZE_MULT_TRANS_MASK   (0x1800u)
#define AM_USB_DESC_ENDPOINT_MAXPACKETSIZE_MULT_TRANS_SHFIT  (11U)

/* Set up 包结构 */
typedef struct am_usb_setup {
    uint8_t  bm_request_type;        /**<\brief 请求特性 */
    uint8_t  b_request;              /**<\brief 请求代码*/
    uint16_t w_value;                /**<\brief 当前请求的参数*/
    uint16_t w_index;                /**<\brief 接口或者端点索引*/
    uint16_t w_length;               /**<\brief 数据过程所需要传输的字节数*/
} am_usb_setup_t;

typedef struct am_usb_descriptor_dev {
    uint8_t b_length;                /**<\brief 描述符字节数 */
    uint8_t b_descriptor_type;       /**<\brief 描述符类型  */
    uint8_t bcd_usb[2];              /**<\brief USB版本号(BCD码) */
    uint8_t b_device_class;          /**<\brief 设备类 码*/
    uint8_t b_device_sub_class;      /**<\brief 设备子类码 */
    uint8_t b_device_protocol;       /**<\brief 设备协议码 */
    uint8_t bmax_packet_size0;       /**<\brief 端点0最大包大小 */
    uint8_t id_vendor[2];            /**<\brief 厂商标识（由USB-IF组织赋值） */
    uint8_t id_product[2];           /**<\brief 产品表记 */
    uint8_t bcd_device[2];           /**<\brief 设备版本号 */
    uint8_t i_manufacturer;          /**<\brief 厂商信息字符串描述符索引值 */
    uint8_t i_product;               /**<\brief 产品信息字符串描述符索引值 */
    uint8_t i_serial_number;         /**<\brief 厂商信息字符串描述符索引值设备序列号信息的索引值 */
    uint8_t b_num_configurations;    /**<\brief 配置描述符数目 */
} am_usb_descriptor_dev_t;

typedef struct am_usb_descriptor_config {
    uint8_t b_length;                /**<\brief 配置描述表的长度 */
    uint8_t b_descriptor_type;       /**<\brief 配置描述符类型 */
    uint8_t w_total_length[2];       /**<\brief 配置信息的总长 */
    uint8_t b_num_interfaces;        /**<\brief 配置支持的接口 */
    uint8_t b_configuration_value;   /**<\brief 配置值 */
    uint8_t i_configuration;         /**<\brief 该配置值的字符串索引 */
    uint8_t bm_attributes;           /**<\brief 配置特性 */
    uint8_t b_max_power;             /**<\brief 配置电流（2mA为一个单位） */
} am_usb_descriptor_config_t;

typedef struct am_usb_descriptor_interface {
    uint8_t b_length;                /**< \brief 接口描述符的字节大小 */
    uint8_t b_descriptor_type;       /**< \brief 接口描述符的类型编号 */
    uint8_t b_interface_number;      /**< \brief 接口编号 */
    uint8_t b_alternate_setting;     /**< \brief 接口描述符的编号 */
    uint8_t b_num_endpoints;         /**< \brief 端点数（不包括端点0） */
    uint8_t b_interface_class;       /**< \brief 接口类 */
    uint8_t b_interface_sub_class;   /**< \brief 接口子类 */
    uint8_t b_interface_protocol;    /**< \brief 接口协议 */
    uint8_t i_interface;             /**< \brief 该接口的字符串索引值 */
} am_usb_descriptor_interface_t;


typedef struct am_usb_hid_descriptor
{
    uint8_t b_length;                /**< \brief HID描述符大小 */
    uint8_t b_descriptor_type;       /**< \brief 描述符类型*/
    uint8_t bcd_hid[2];              /**< \brief HID版本号*/
    uint8_t b_country_code;          /**< \brief 表示本地硬件的国家代码*/
    uint8_t b_num_descriptors;       /**< \brief 描述符数量(至少有一个，及报告描述符)*/
    uint8_t b_hid_descriptor_type;   /**< \brief 类描述符号类型*/
    uint8_t w_descriptor_length[2];  /**< \brief 报表描述符总大小*/
} am_usb_hid_descriptor_t;

typedef struct am_usb_descriptor_endpoint {
    uint8_t b_length;                /**<\brief 端点描述符字节数大小 */
    uint8_t b_descriptor_type;       /**<\brief 端点描述符的类型编号*/
    uint8_t b_endpoint_address;      /**<\brief 端点地址及其方向*/
    uint8_t bm_attributes;           /**<\brief 端点传输特性*/
    uint8_t wmax_packet_size[2];     /**<\brief 端点最大的传输包大小*/

    /**
     * \brief 该端点被主机的访问周期
     * 定义了该端点被主机访问的周期，此域值对于批量传输和控制传输毫无意义。对于同步传输，其值必须为 1，
     * 即 1ms 为标准的同步帧周期。对于中断传输，该值为1~255，即 1ms~255ms
     */
    uint8_t b_interval;
} am_usb_descriptor_endpoint_t;

#ifdef __cplusplus
}
#endif

#endif /* __AM_USB_SPEC_H */
