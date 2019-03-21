/*
 * am_usb_ch9.c
 *
 *  Created on: 2019Äê3ÔÂ21ÈÕ
 *      Author: yanghai
 */

#include "am_usb.h"
#include "am_usbd_ch9.h"

//#include "am_zmf159_usbd.h"

/* __interface_get */
static uint8_t __interface_get(uint8_t interface, uint8_t alt)
{
    if (alt > 0) {
        return AM_USB_STATUS_NOT_SUPPORTED;
    } else if (interface > 1) {
        return AM_USB_STATUS_NOT_SUPPORTED;
    }

    return AM_USB_STATUS_SUCCESS;
}



#define std_Recipient (p_dev->setup_data.bm_request_type &  \
                      (AM_USB_REQ_TYPE_TYPE_MASK | AM_USB_REQ_TYPE_RECIPIENT_MASK))

/* std_config_get */
uint8_t *am_usb_ch9_config_get(void *p_arg, uint16_t length)
{
	am_usbd_dev_t *p_dev = (am_usbd_dev_t *)p_arg;

    if (length == 0) {
        p_dev->ctrl_info.Usb_wLength = sizeof(p_dev->cur_config);
        return 0;
    }
    return (uint8_t *)&p_dev->cur_config;
}

/* std_config_set */
uint8_t am_usb_ch9_config_set(void *p_arg)
{
	am_usbd_dev_t *p_dev = (am_usbd_dev_t *)p_arg;

    if (p_dev->setup_data.w_index == 0) {

        p_dev->cur_config = p_dev->setup_data.w_value;
        return AM_USB_STATUS_SUCCESS;
    } else {
        return AM_USB_STATUS_NOT_SUPPORTED;
    }
}

/* std interface get*/
uint8_t *am_usb_ch9_interface_get(void *p_arg, uint16_t length)
{
	am_usbd_dev_t *p_dev = (am_usbd_dev_t *)p_arg;

    if (length == 0) {
        p_dev->ctrl_info.Usb_wLength = sizeof(p_dev->cur_alt);
        return 0;
    }
    return (uint8_t *)&p_dev->cur_alt;
}

/* interface set*/
uint8_t am_usb_ch9_interface_set(void *p_arg)
{
    uint8_t Re = 0;
    am_usbd_dev_t *p_dev = (am_usbd_dev_t *)p_arg;

    Re = __interface_get(p_dev->setup_data.w_index, p_dev->setup_data.w_value);

    if (p_dev->cur_config != 0) {
        if (Re != AM_USB_STATUS_SUCCESS) {
            return  AM_USB_STATUS_NOT_SUPPORTED;
        } else if (Re == AM_USB_STATUS_SUCCESS) {
            p_dev->cur_interface        = p_dev->setup_data.w_index;
            p_dev->cur_alt              = p_dev->setup_data.w_value;
            return AM_USB_STATUS_SUCCESS;
        }
    }

  return AM_USB_STATUS_NOT_SUPPORTED;
}

/* std status get*/
uint8_t *am_usb_ch9_status_get(void *p_arg, uint16_t length)
{
	am_usbd_dev_t *p_dev   = (am_usbd_dev_t *)p_arg;

    if (length == 0) {
        p_dev->ctrl_info.Usb_wLength = 2;
        return 0;
    }

    p_dev->sta_info = 0;

    switch (std_Recipient) {
    case AM_USB_REQ_TYPE_RECIPIENT_DEVICE:
    {
         /* Remote Wakeup enabled */
         if (AM_BIT_ISSET(p_dev->cur_feature, 5)) {
             AM_BIT_SET(p_dev->sta_info, 1);
         }

         /* Bus-powered */
         if (AM_BIT_ISSET(p_dev->cur_feature, 6)) {
             AM_BIT_CLR(p_dev->sta_info, 0);
         } else {/* Self-powered */
             AM_BIT_SET(p_dev->sta_info, 0);
         }

        break;
    }

    case AM_USB_REQ_TYPE_RECIPIENT_INTERFACE:
    {
        break;
    }

    case AM_USB_REQ_TYPE_RECIPIENT_ENDPOINT:
    {
         AM_BIT_SET(p_dev->sta_info, 0);
         break;
    }

    default :
        return NULL;
    }

  return (uint8_t *)&p_dev->sta_info;
}

/* feature clr*/
uint8_t am_usb_ch9_feature_clr(void *p_arg)
{
//    uint32_t            Status   = 0;
    uint8_t             res      = AM_USB_STATUS_NOT_SUPPORTED;
    am_usbd_dev_t      *p_dev    = (am_usbd_dev_t *)p_arg;
    uint32_t            wIndex0  = p_dev->setup_data.w_index;
    uint8_t             rEP      = wIndex0 & ~0x80;

    am_usbd_ep_status_t endpointStatus ;

    endpointStatus.endpoint_address = rEP;
    endpointStatus.endpoint_status  = 0;


    switch (std_Recipient) {

    case AM_USB_REQ_TYPE_RECIPIENT_DEVICE:
    {
        AM_BIT_CLR(p_dev->cur_feature, 5);
        res = AM_USB_STATUS_SUCCESS;
        break;
    }

    case AM_USB_REQ_TYPE_RECIPIENT_ENDPOINT:
    {
       if ((p_dev->setup_data.w_value != AM_USB_REQ_STA_FEATURE_ENDPOINT_HALT)
           || (p_dev->setup_data.w_index >> 7 != 0)) {
           res = AM_USB_STATUS_NOT_SUPPORTED;
           break;
       }

//       Status = amhw_zmf159_ep_stat_get(ZMF159_USB, rEP);
       am_usbd_control(p_dev,
       				AM_USBD_CONTROL_GET_ENDPOINT_STATUS,
   				   &endpointStatus);

       if ((endpointStatus.endpoint_status == 0) || (p_dev->cur_config == 0)) {
           res = AM_USB_STATUS_NOT_SUPPORTED;
           break;
       }

       endpointStatus.endpoint_address = rEP;
       endpointStatus.endpoint_status  = 0;

       am_usbd_control(p_dev,
       				   AM_USBD_CONTROL_SET_ENDPOINT_STATUS,
   				      &endpointStatus);

//     amhw_zmf159_ep_stat_set(ZMF159_USB, rEP, 0);

       res = AM_USB_STATUS_SUCCESS;
        break;
    }

    default :
        break;
    }

  return res;
}

/* ep feature set*/
uint8_t am_usb_ch9_ep_feature_set(void *p_arg)
{
	am_usbd_dev_t *p_dev      = (am_usbd_dev_t *)p_arg;

    uint32_t    wIndex0       = p_dev->setup_data.w_index;
    uint8_t     rEP           = wIndex0 & ~0x80;;
//    uint32_t    Status        = 0;

    am_usbd_ep_status_t endpointStatus ;

    endpointStatus.endpoint_address = rEP;
    endpointStatus.endpoint_status  = 0;

    am_usbd_control(p_dev,
    				AM_USBD_CONTROL_GET_ENDPOINT_STATUS,
				   &endpointStatus);

//    Status = amhw_zmf159_ep_stat_get(ZMF159_USB, rEP);

    if (p_dev->setup_data.w_value != 0 || endpointStatus.endpoint_status == 0) {
        return AM_USB_STATUS_NOT_SUPPORTED;
    }

    return AM_USB_STATUS_SUCCESS;
}

/* std feature set */
uint8_t am_usb_ch9_dev_feature_set(void *p_arg)
{
	am_usbd_dev_t *p_dev = (am_usbd_dev_t *)p_arg;

    AM_BIT_SET(p_dev->cur_feature, 5);
    return AM_USB_STATUS_SUCCESS;
}

/* std_descriptor_get */
uint8_t *std_descriptor_get(void *p_arg, uint16_t length, const am_usbd_descriptor_t *p_desc)
{
	am_usbd_dev_t *p_dev = (am_usbd_dev_t *)p_arg;
    uint32_t     wOffset = p_dev->ctrl_info.Usb_wOffset;

    if (length == 0) {
        p_dev->ctrl_info.Usb_wLength = p_desc->desc_size - wOffset;
        return 0;
    }

    return (uint8_t *)(p_desc->p_desc + wOffset);
}

/* address set */
void am_usb_ch9_addr_set(am_usbd_dev_t *p_dev)
{
	am_usbd_control(p_dev,
					AM_USBD_CONTROL_SET_DEVICE_ADDRESS,
					(void *)&(p_dev->setup_data.w_value));
}


/*__std_descriptor_get */
uint8_t *am_usb_ch9_descriptor_get(void *p_arg, uint16_t length)
{
    volatile uint8_t    i = 0;
    am_usbd_dev_t  *p_dev = (am_usbd_dev_t *)p_arg;

    for (i = 0; i < p_dev->p_info->descriptor_num; i++) {
        if (p_dev->setup_data.w_value == p_dev->p_info->p_descriptor[i].desc_wValue) {
            return std_descriptor_get(p_dev,
                                      length,
                                     &p_dev->p_info->p_descriptor[i]);
        }
    }
    return NULL;
}




