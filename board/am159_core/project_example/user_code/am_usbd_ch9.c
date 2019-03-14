/**
 * \file
 * \brief     USB
 * \endinternal
 */

#include "am_usbd_ch9.h"


/**
 * \brief 通过wValue的值寻找指定的描述符
 *
 * \retval 成功返回描述符指针，失败返回NULL
 *
 * \note 配置描述符的下级描述符不能通过此法获得
 */
static uint8_t * __find_desc_by_wvalue (am_usbd_dev_t *p_dev,
                                        uint16_t       w_value)
{
    int i = 0;

    for (i = 0; i < p_dev->p_info->descriptor_num; i++) {
        if (w_value == p_dev->p_info->p_descriptor[i].desc_wValue) {
            return (uint8_t *)(p_dev->p_info->p_descriptor[i].p_desc);
        }
    }
    return NULL;
}

/**
 * \brief 在配置描述符中找出指定的描述符
 *
 * \param[in] p_confdesc：配置描述符及下级描述符的地址
 * \param[in] bDescriptorTpye：描述符类型编号
 * \param[in] index：描述符索引或序号（从0开始），比如要获取第二个接口描述符，则此参数应为1
 *
 * \retval 成功返回描述符指针，失败返回NULL
 *
 * \note 输入的配置描述符必须是格式正确的描述符
 */
static uint8_t * __find_desc_by_confdesc (uint8_t *p_confdesc,
                                          uint8_t  bdescriptortpye,
                                          uint8_t  index)
{
    uint8_t *p_tmp = p_confdesc;
    uint16_t desc_size = 0;
    am_usb_descriptor_config_t *p_desc_conf = NULL;
    uint8_t index_tmp = index;

    /* 配置描述符 */
    if (bdescriptortpye == AM_USB_DESC_TYPE_CONFIGURE &&
        p_tmp[1] == AM_USB_DESC_TYPE_CONFIGURE) {
        return p_tmp;
    }

    p_desc_conf = (am_usb_descriptor_config_t *)p_confdesc;
    desc_size = (p_desc_conf->w_total_length[1] << 8) |
                 p_desc_conf->w_total_length[0];

    while (p_tmp - p_confdesc < desc_size) {
        if (p_tmp[1] == bdescriptortpye) {
            if (index_tmp == 0)
                return p_tmp;
            else
                index_tmp--;
        }
        p_tmp += p_tmp[0];
    }

    return NULL;
}

/**
 * \brief 获取状态请求    0x00 page 255
 */
static void __chap9_getstatus (am_usbd_dev_t *p_dev)
{
    uint8_t buffer[2] = { 0 };
    uint8_t endpoint = 0;
    am_usb_descriptor_config_t *p_desc_conf = NULL;
    uint8_t attibute = 0;
    uint8_t recip = p_dev->setup_data.bm_request_type & AM_USB_REQ_TYPE_RECIPIENT_MASK;

    switch(p_dev->running_ctrl_state) {
    case AM_USBD_CTRL_SETUP :
        p_dev->running_ctrl_state = AM_USBD_CTRL_IN;
        break;

    case AM_USBD_CTRL_IN:
        if ((p_dev->setup_data.bm_request_type & AM_USB_REQ_TYPE_DIR_MASK) == AM_USB_REQ_TYPE_DIR_IN) {
            switch (recip) {
            case AM_USB_REQ_TYPE_RECIPIENT_DEVICE:     /* 设备 */
                p_desc_conf = (am_usb_descriptor_config_t *)\
                 __find_desc_by_wvalue(p_dev, (AM_USB_DESC_TYPE_CONFIGURE << 8) | 0);

                attibute = p_desc_conf->bm_attributes;
                if (attibute & AM_USB_DESC_CONFIG_ATTR_SELF_POWERED_MASK)
                    buffer[0] |= (1 << 0);
                if (attibute & AM_USB_DESC_CONFIG_ATTR_REMOTE_WAKEUP_MASK)
                    buffer[0] |= (1 << 1);
                buffer[1] = 0;
                break;

            case AM_USB_REQ_TYPE_RECIPIENT_INTERFACE:      /* 接口 */
                buffer[0] = 0;
                buffer[1] = 0;
                break;

            case AM_USB_REQ_TYPE_RECIPIENT_ENDPOINT:      /* 端点 */
                endpoint = p_dev->setup_data.w_index & AM_USBD_ENDPOINT_NUMBER_MASK;

                if (p_dev->endpoint_info[endpoint].inuse)
                    buffer[0] = 1;
                else
                    buffer[0] = 0;
                buffer[1] = 0;
                break;
            }
            p_dev->p_interface->pfn_device_send(p_dev->ctrl_handle, 0, buffer, 2);
        }
        p_dev->running_ctrl_state = AM_USBD_CTRL_IDLE;
        break;

    default:
        p_dev->running_ctrl_state = AM_USBD_CTRL_IDLE;
    }
}

/**
 * \brief 清除特征请求    0x01
 */
static void __chap9_clearfeature (am_usbd_dev_t *p_dev)
{
    /* 命令接收者 */
    uint8_t recip = p_dev->setup_data.bm_request_type & AM_USB_REQ_TYPE_RECIPIENT_MASK;
    uint8_t endpoint = p_dev->setup_data.w_index & AM_USBD_ENDPOINT_NUMBER_MASK;
    uint8_t feature_selector = p_dev->setup_data.w_value;
    am_usb_descriptor_config_t *p_desc_conf = NULL;

    if ((p_dev->setup_data.bm_request_type & AM_USB_REQ_TYPE_DIR_MASK) == \
                                                    AM_USB_REQ_TYPE_DIR_OUT) {
        switch (feature_selector) {
        case AM_USB_REQ_STA_FEATURE_ENDPOINT_HALT:
            if (recip == AM_USB_REQ_TYPE_RECIPIENT_ENDPOINT)
                p_dev->p_interface->pfn_device_control(p_dev,
                                                   AM_USBD_CONTROL_ENDPOINT_UNSTALL,
                                                  (void *)&endpoint);
            break;

        case AM_USB_REQ_STA_FEATURE_DEVICE_REMOTE_WAKEUP:
            if (recip == AM_USB_REQ_TYPE_RECIPIENT_DEVICE) {
                p_desc_conf = (am_usb_descriptor_config_t *)\
                 __find_desc_by_wvalue(p_dev, (AM_USB_DESC_TYPE_CONFIGURE << 8) | 0);
                p_desc_conf->bm_attributes &= ~AM_USB_DESC_CONFIG_ATTR_REMOTE_WAKEUP_MASK; /* 支持远程唤醒 */
            }
            break;

        case AM_USB_REQ_STA_FEATURE_DEVICE_TEST_MODE:
            if (recip == AM_USB_REQ_TYPE_RECIPIENT_DEVICE) {
                /* 保留 */
            }
            break;
        }
    }
}

/**
 * \brief 设置特征请求    0x03
 */
static void __chap9_setfeature (am_usbd_dev_t *p_dev)
{
    /* 命令接收者 */
    uint8_t recip = p_dev->setup_data.bm_request_type & AM_USB_REQ_TYPE_RECIPIENT_MASK;
    uint8_t endpoint = p_dev->setup_data.w_index & AM_USBD_ENDPOINT_NUMBER_MASK;
    uint8_t feature_selector = p_dev->setup_data.w_value;
    am_usb_descriptor_config_t *p_desc_conf = NULL;

    if ((p_dev->setup_data.bm_request_type & AM_USB_REQ_TYPE_DIR_MASK) == \
                                                    AM_USB_REQ_TYPE_DIR_OUT) {
        switch (feature_selector) {
        case AM_USB_REQ_STA_FEATURE_ENDPOINT_HALT:
            if (recip == AM_USB_REQ_TYPE_RECIPIENT_ENDPOINT)
                //amhw_zlg217_usbd_ep_halt_set(1 << endpoint);   /* 禁用端点 */
                p_dev->p_interface->pfn_device_control(p_dev,
                                                   AM_USBD_CONTROL_ENDPOINT_STALL,
                                                  (void *)&endpoint);
            break;

        case AM_USB_REQ_STA_FEATURE_DEVICE_REMOTE_WAKEUP:
            if (recip == AM_USB_REQ_TYPE_RECIPIENT_DEVICE) {
                p_desc_conf = (am_usb_descriptor_config_t *)\
                 __find_desc_by_wvalue(p_dev, (AM_USB_DESC_TYPE_CONFIGURE << 8) | 0);
                p_desc_conf->bm_attributes |= AM_USB_DESC_CONFIG_ATTR_REMOTE_WAKEUP_MASK;         /* 支持远程唤醒 */
            }
            break;

        case AM_USB_REQ_STA_FEATURE_DEVICE_TEST_MODE:
            if (recip == AM_USB_REQ_TYPE_RECIPIENT_DEVICE) {
                /* 保留 */
            }
            break;
        }
    }
}

/**
 * \brief 设置地址请求    0x05
 */
static void __chap9_setaddress (am_usbd_dev_t *p_dev)
{
    /* zlg227 不用写设置地址的代码，硬件自动完成 */
    p_dev->device_address = p_dev->setup_data.w_value;

    am_kprintf("ch9 %x \r\n", p_dev->device_address);

    p_dev->p_interface->pfn_device_control(p_dev->ctrl_handle,
                                           AM_USBD_CONTROL_SET_DEVICE_ADDRESS,
										   (void *)&(p_dev->device_address));

}

/**
 * \brief 获取描述符     0x06
 */
static void __chap9_getdescriptor (am_usbd_dev_t *p_dev)
{
    int i = 0;
    int len = 0;
    static uint16_t ctrl_buf_ix = 0;

    switch(p_dev->running_ctrl_state) {
    case AM_USBD_CTRL_SETUP :
        p_dev->running_ctrl_state = AM_USBD_CTRL_IN;
        ctrl_buf_ix = 0;
        break;

    case AM_USBD_CTRL_IN:
        if ((p_dev->setup_data.bm_request_type & AM_USB_REQ_TYPE_DIR_MASK) == AM_USB_REQ_TYPE_DIR_IN) {
            for (i = 0; i < p_dev->p_info->descriptor_num; i++) {   /* 寻找匹配的描述符 */
                if (p_dev->setup_data.w_value == p_dev->p_info->p_descriptor[i].desc_wValue) {

                    if (p_dev->setup_data.w_length > p_dev->p_info->p_descriptor[i].desc_size)
                        len = p_dev->p_info->p_descriptor[i].desc_size;
                    else
                        len = p_dev->setup_data.w_length;

                    p_dev->p_interface->pfn_device_send(p_dev->ctrl_handle,
                                                    0,
                                                   (uint8_t *)&p_dev->p_info->p_descriptor[i].p_desc[ctrl_buf_ix],
                                                    len);
                    break;
                }
            }
            if (i == p_dev->p_info->descriptor_num) {
                /* 没有找到匹配的描述符则发送空包 */
            	p_dev->p_interface->pfn_device_send(p_dev->ctrl_handle, 0, NULL, 0);
            }
        }
        p_dev->running_ctrl_state = AM_USBD_CTRL_IDLE;
        break;

    default:
        p_dev->running_ctrl_state = AM_USBD_CTRL_IDLE;
    }
}

/**
 * \brief 设备描述符请求（修改或增加描述符）     0x07
 */
static void __chap9_setdescriptor (am_usbd_dev_t *p_dev)
{

}

/**
 * \brief 获取配置请求    0x08
 */
static void __chap9_getconfiguration (am_usbd_dev_t *p_dev)
{
    uint8_t bConfigurationValue = 0;
    am_usb_descriptor_config_t *p_desc_conf = NULL;

    switch(p_dev->running_ctrl_state) {
    case AM_USBD_CTRL_SETUP :
        p_dev->running_ctrl_state = AM_USBD_CTRL_IN;
        break;

    case AM_USBD_CTRL_IN:
        /* 方向为输入，接受者为设备 */
        if (p_dev->setup_data.bm_request_type == 0x80) {
            p_desc_conf = (am_usb_descriptor_config_t *)\
             __find_desc_by_wvalue(p_dev, (AM_USB_DESC_TYPE_CONFIGURE << 8) | 0);
            bConfigurationValue = p_desc_conf->b_configuration_value;
            p_dev->p_interface->pfn_device_send(p_dev->ctrl_handle,
                                            0,
                                           &bConfigurationValue,
                                            1);
        }
        p_dev->running_ctrl_state = AM_USBD_CTRL_IDLE;
        break;

    default:
        p_dev->running_ctrl_state = AM_USBD_CTRL_IDLE;
    }
}

/**
 * \brief 设置配置请求    0x09
 */
static void __chap9_setconfiguration (am_usbd_dev_t *p_dev)
{
    am_usb_descriptor_config_t *p_desc_conf = NULL;

    /* 方向为输出，接受者为设备 */
    if (p_dev->setup_data.bm_request_type == 0x00) {
        p_desc_conf = (am_usb_descriptor_config_t *)\
         __find_desc_by_wvalue(p_dev, (AM_USB_DESC_TYPE_CONFIGURE << 8) | 0);

        p_desc_conf->b_configuration_value = p_dev->setup_data.w_value;
    }
}

/**
 * \brief 获取接口请求    0x0a
 */
static void __chap9_getinterface (am_usbd_dev_t *p_dev)
{
    am_usb_descriptor_interface_t *p_desc_interface = NULL;
    uint8_t *p_desc_conf = NULL;

    switch(p_dev->running_ctrl_state) {
    case AM_USBD_CTRL_SETUP :
        p_dev->running_ctrl_state = AM_USBD_CTRL_IN;
        break;

    case AM_USBD_CTRL_IN:
        /* 输入，接受者为接口 */
        if (p_dev->setup_data.bm_request_type == 0x81 &&
            p_dev->setup_data.w_length == 1) {
            p_desc_conf = __find_desc_by_wvalue(p_dev, (AM_USB_DESC_TYPE_CONFIGURE << 8) | 0);

            p_desc_interface = (am_usb_descriptor_interface_t *)\
                 __find_desc_by_confdesc(p_desc_conf,
                                         AM_USB_DESC_TYPE_INTERFACE,
                                         p_dev->setup_data.w_index);

            p_dev->p_interface->pfn_device_send(p_dev->ctrl_handle,
                                            0,
                                            (uint8_t *)&p_desc_interface->b_alternate_setting,
                                             1);
            p_dev->running_ctrl_state = AM_USBD_CTRL_IDLE;
        }
        break;

    default:
        p_dev->running_ctrl_state = AM_USBD_CTRL_IDLE;
    }
}

/**
 * \brief 设置接口请求    0x0b
 */
static void __chap9_setinterface (am_usbd_dev_t *p_dev)
{
    am_usb_descriptor_interface_t *p_desc_interface = NULL;
    uint8_t *p_desc_conf = NULL;

    /* 输出，接受者为接口 */
    if (p_dev->setup_data.bm_request_type == 0x01) {
        p_desc_conf = __find_desc_by_wvalue(p_dev, (AM_USB_DESC_TYPE_CONFIGURE << 8) | 0);

        p_desc_interface = (am_usb_descriptor_interface_t *)\
             __find_desc_by_confdesc(p_desc_conf,
                                     AM_USB_DESC_TYPE_INTERFACE,
                                     p_dev->setup_data.w_index);

        p_desc_interface->b_alternate_setting = p_dev->setup_data.w_value;
    }
}

/**
 * \brief 同步帧请求 0x0c
 */
static void __chap9_sync_fram (am_usbd_dev_t *p_dev)
{

}

/**
 * \brief USB标准设备请求命令处理函数
 */
static void (*__std_device_request[AM_USB_REQ_STANDARD_SYNCH_FRAME + 1])
                (am_usbd_dev_t *p_dev) =
{
    __chap9_getstatus,        /* 0x00 */
    __chap9_clearfeature,     /* 0x01 */
    NULL,                     /* reserve */
    __chap9_setfeature,       /* 0x03 */
    NULL,                     /* reserve */
    __chap9_setaddress,       /* 0x05 */
    __chap9_getdescriptor,    /* 0x06 */
    __chap9_setdescriptor,    /* 0x07 */
    __chap9_getconfiguration, /* 0x08 */
    __chap9_setconfiguration, /* 0x09 */
    __chap9_getinterface,     /* 0x0a */
    __chap9_setinterface,     /* 0x0b */
    __chap9_sync_fram,        /* 0x0c */
};

// 该函数应该在设备初始化时候调用，将标准设备请求函数绑定
void am_usbd_ch9_std_request(am_usbd_dev_t *p_dev)
{
    p_dev->pfn_std_request = __std_device_request;
}


/* end of file*/


