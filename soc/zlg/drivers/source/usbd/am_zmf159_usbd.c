


#include "am_int.h"
#include "zmf159_pin.h"
#include "zmf159_inum.h"
#include "am_zmf159_usbd.h"
#include "zmf159_periph_map.h"


static void    __zmf159_reset(void *p_arg);
static uint8_t vcom_interface_get(uint8_t Interface, uint8_t AlternateSetting);

/* Exported constants --------------------------------------------------------*/
#define Recipient (p_dev->isa.setup_data.bm_request_type & (AM_USB_REQ_TYPE_TYPE_MASK | AM_USB_REQ_TYPE_RECIPIENT_MASK))

static uint8_t __buffer_out[64] = {0};

line_coding_t linecoding = {
    9600,   /* baud rate*/
    0x00,   /* stop bits-1*/
    0x00,   /* parity - none*/
    0x08    /* no. of bits 8*/
};

/*******************************************************************************
* Function Name  : UserToPMABufferCopy
* Description    : Copy a buffer from user memory area to packet memory area (PMA)
* Input          : - pbUsrBuf: pointer to user memory area.
*                  - wPMABufAddr: address into PMA.
*                  - wNBytes: no. of bytes to be copied.
* Output         : None.
* Return         : None    .
*******************************************************************************/
am_usb_status_t am_zmf159_usbd_send(void *p_arg, uint8_t ep, uint8_t *p_buf, uint32_t length)
{
    uint32_t i;
    uint8_t *pBuf;
    am_zmf159_device_t    *p_dev = (am_zmf159_device_t *)p_arg;
    amhw_zmf159_usb_bdt_t *pUSB_OTG_BDT = p_dev->p_usb_bdt;

    if (p_dev == NULL) {
        return AM_USB_STATUS_INVALID_PARAMETER;
    }

    if (ep >= AM_USBD_MAX_EP_CNT)
        return AM_USB_STATUS_INVALID_PARAMETER;

    pBuf = (uint8_t*)((pUSB_OTG_BDT+ep)->tx_buf[p_dev->tx_odd[ep]].adress) ;

    (pUSB_OTG_BDT+ep)->tx_buf[p_dev->tx_odd[ep]].format &= 0x00ff00;

    for (i = 0;i < length;  i++)
    {
        pBuf[i] = *p_buf;
        p_buf++;
    }

    pBuf[i] = '\0';  // 截断数据，防止脏数据

    (pUSB_OTG_BDT+ep)->tx_buf[p_dev->tx_odd[ep]].format |= (length<<16)|(p_dev->ep_indata_num[ep]<<6);
    p_dev->ep_indata_num[ep] = !p_dev->ep_indata_num[ep];

    (pUSB_OTG_BDT+ep)->tx_buf[p_dev->tx_odd[ep]].format |= 1<<7;
    p_dev->tx_odd[ep] = !p_dev->tx_odd[ep];

    return AM_USB_STATUS_SUCCESS;

}
/*******************************************************************************
* Function Name  : PMAToUserBufferCopy
* Description    : Copy a buffer from user memory area to packet memory area (PMA)
* Input          : - pbUsrBuf    = pointer to user memory area.
*                  - wPMABufAddr = address into PMA.
*                  - wNBytes     = no. of bytes to be copied.
* Output         : None.
* Return         : None.
*******************************************************************************/
am_usb_status_t am_zmf159_usbd_recv(void *p_arg, uint8_t ep, uint8_t *p_buf, uint32_t length)
{
    uint32_t i                 = 0;
    uint8_t *pBuf              = NULL;
    uint8_t  val_len           = 0;
    am_usb_status_t error      = AM_USB_STATUS_ERROR;
    am_zmf159_device_t  *p_dev = (am_zmf159_device_t *)p_arg;

    if (p_dev == NULL) {
        return AM_USB_STATUS_INVALID_PARAMETER;
    }

    if (ep >= AM_USBD_MAX_EP_CNT)
        return AM_USB_STATUS_INVALID_PARAMETER;

    amhw_zmf159_usb_bdt_t *pUSB_OTG_BDT = p_dev->p_usb_bdt;

    pBuf = (uint8_t*)((pUSB_OTG_BDT+ep)->rx_buf[p_dev->rx_odd[ep]].adress) ;

    val_len = (p_dev->p_usb_bdt+ENDP3)->rx_buf[p_dev->rx_odd[ENDP3]].format>>16;
    p_dev->isa.endpoint_info[ep].val_length = (val_len & 0x1FF);

    if (val_len == 0)
        return AM_USB_STATUS_ERROR;
    else if (val_len < length)
        error = AM_USB_STATUS_ALLOC_FAIL;
    else if (val_len == length)
        error = AM_USB_STATUS_SUCCESS;
    else if (val_len > length) {
        error = AM_USB_STATUS_SUCCESS;
        val_len = length;
    }

    for (i = 0;i < val_len; i++) {
        *p_buf = pBuf[i];
         p_buf++;
    }

    (pUSB_OTG_BDT+ep)->rx_buf[p_dev->rx_odd[ep]].format &= 0x00ff00;//清除计数,清除stall
    (pUSB_OTG_BDT+ep)->rx_buf[p_dev->rx_odd[ep]].format |= (64<<16);//设置最大接收字节
    (pUSB_OTG_BDT+ep)->rx_buf[p_dev->rx_odd[ep]].format |= 1<<7;

    return error;
}


/*******************************************************************************
* Function Name  : EP3_IN_Callback
* Description    : USB数据接收
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
static am_usb_status_t __vcom_recv_cb(void *p_arg)
{
    am_zmf159_device_t *p_dev = (am_zmf159_device_t * )p_arg;

    am_usbd_recv(p_dev->isa.ctrl_handle, ENDP3, __buffer_out, 0x40);

    am_kprintf("%x \r\n", p_dev->isa.endpoint_info[ENDP3].val_length);
    return AM_USB_STATUS_SUCCESS;
}

/*******************************************************************************
* Function Name  : EP1_IN_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
static am_usb_status_t __vcom_send_cb(void *p_arg)
{
    return AM_USB_STATUS_SUCCESS;
}


/*******************************************************************************
* Function Name  : Standard_GetConfiguration.
* Description    : Return the current configuration variable address.
* Input          : Length - How many bytes are needed.
* Output         : None.
* Return         : Return 1 , if the request is invalid when "Length" is 0.
*                  Return "Buffer" if the "Length" is not 0.
*****************************************************************·**************/
static uint8_t *std_config_get(void *p_arg, uint16_t length)
{
    am_zmf159_device_t *p_dev = (am_zmf159_device_t *)p_arg;

    if (length == 0) {
        p_dev->ctrl_info.Usb_wLength = sizeof(p_dev->cur_config);
        return 0;
    }
    return (uint8_t *)&p_dev->cur_config;
}

/*******************************************************************************
* Function Name  : Standard_SetConfiguration.
* Description    : This routine is called to set the configuration value
*                  Then each class should configure device themself.
* Input          : None.
* Output         : None.
* Return         : Return USB_SUCCESS, if the request is performed.
*                  Return USB_UNSUPPORT, if the request is invalid.
*******************************************************************************/
static uint8_t std_config_set(void *p_arg)
{
    am_zmf159_device_t *p_dev = (am_zmf159_device_t *)p_arg;

    if ((p_dev->isa.setup_data.w_value <=  p_dev->config_num)
        && (p_dev->isa.setup_data.w_index == 0)) {

        p_dev->cur_config = p_dev->isa.setup_data.w_value;
        return USB_SUCCESS;
    } else {
        return USB_UNSUPPORT;
    }
}

/*******************************************************************************
* Function Name  : Standard_GetInterface.
* Description    : Return the Alternate Setting of the current interface.
* Input          : Length - How many bytes are needed.
* Output         : None.
* Return         : Return 0, if the request is invalid when "Length" is 0.
*                  Return "Buffer" if the "Length" is not 0.
*******************************************************************************/
static uint8_t *std_interface_get(void *p_arg, uint16_t length)
{
    am_zmf159_device_t *p_dev = (am_zmf159_device_t *)p_arg;

    if (length == 0) {
        p_dev->ctrl_info.Usb_wLength = sizeof(p_dev->cur_alt);
        return 0;
    }
    return (uint8_t *)&p_dev->cur_alt;
}

/*******************************************************************************
* Function Name  : Standard_SetInterface.
* Description    : This routine is called to set the interface.
*                  Then each class should configure the interface them self.
* Input          : None.
* Output         : None.
* Return         : - Return USB_SUCCESS, if the request is performed.
*                  - Return USB_UNSUPPORT, if the request is invalid.
*******************************************************************************/
static uint8_t std_interface_set(void *p_arg)
{
    uint8_t Re = 0;
    am_zmf159_device_t *p_dev = (am_zmf159_device_t *)p_arg;

    Re = vcom_interface_get(p_dev->isa.setup_data.w_index, p_dev->isa.setup_data.w_value);

    if (p_dev->cur_config != 0) {
        if (Re != USB_SUCCESS) {
            return  USB_UNSUPPORT;
        } else if (Re == USB_SUCCESS) {
            p_dev->cur_interface        = p_dev->isa.setup_data.w_index;
            p_dev->cur_alt = p_dev->isa.setup_data.w_value;
            return USB_SUCCESS;
        }
    }

  return USB_UNSUPPORT;
}

/*******************************************************************************
* Function Name  : Standard_GetStatus.
* Description    : Copy the device request data to "StatusInfo buffer".
* Input          : - Length - How many bytes are needed.
* Output         : None.
* Return         : Return 0, if the request is at end of data block,
*                  or is invalid when "Length" is 0.
*******************************************************************************/
uint8_t *std_status_get(void *p_arg, uint16_t length)
{
    am_zmf159_device_t *p_dev   = (am_zmf159_device_t *)p_arg;
//    uint8_t             wIndex0 = p_dev->isa.setup_data.w_index;

    if (length == 0) {
        p_dev->ctrl_info.Usb_wLength = 2;
        return 0;
    }

    p_dev->sta_info = 0;

    switch (Recipient) {
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

/*******************************************************************************
* Function Name  : Standard_ClearFeature.
* Description    : Clear or disable a specific feature.
* Input          : None.
* Output         : None.
* Return         : - Return USB_SUCCESS, if the request is performed.
*                  - Return USB_UNSUPPORT, if the request is invalid.
*******************************************************************************/
uint8_t std_feature_clr(void *p_arg)
{
    uint32_t            Status   = 0;
    uint8_t             res      = USB_UNSUPPORT;
    am_zmf159_device_t *p_dev    = (am_zmf159_device_t *)p_arg;
    uint32_t            wIndex0  = p_dev->isa.setup_data.w_index;
    uint32_t            rEP      = wIndex0 & ~0x80;

    switch (Recipient) {

    case AM_USB_REQ_TYPE_RECIPIENT_DEVICE:
    {
        AM_BIT_CLR(p_dev->cur_feature, 5);
        res = USB_SUCCESS;
        break;
    }

    case AM_USB_REQ_TYPE_RECIPIENT_ENDPOINT:
    {
       if ((p_dev->isa.setup_data.w_value != AM_USB_REQ_STA_FEATURE_ENDPOINT_HALT)
           || (p_dev->isa.setup_data.w_index >> 7 != 0)) {
           res = USB_UNSUPPORT;
           break;
       }

       Status = amhw_zmf159_ep_stat_get(ZMF159_USB, rEP);

       if ((rEP >= p_dev->ep_num) || (Status == 0)
           || (p_dev->cur_config == 0)) {
           res = USB_UNSUPPORT;
           break;
       }

     /* OUT endpoint */
     amhw_zmf159_ep_stat_set(ZMF159_USB, rEP, 0);

       res = USB_SUCCESS;
        break;
    }

    default :
        break;
    }

  return res;
}

/*******************************************************************************
* Function Name  : Standard_SetEndPointFeature
* Description    : Set or enable a specific feature of EndPoint
* Input          : None.
* Output         : None.
* Return         : - Return USB_SUCCESS, if the request is performed.
*                  - Return USB_UNSUPPORT, if the request is invalid.
*******************************************************************************/
uint8_t std_ep_feature_set(void *p_arg)
{
    am_zmf159_device_t *p_dev = (am_zmf159_device_t *)p_arg;

    uint32_t    wIndex0       = p_dev->isa.setup_data.w_index;
    uint32_t    rEP           = wIndex0 & ~0x80;;
    uint32_t    Status        = 0;

    Status = amhw_zmf159_ep_stat_get(ZMF159_USB, rEP);

    if (p_dev->isa.setup_data.w_value != 0 || Status == 0
        || p_dev->cur_config == 0) {
        return USB_UNSUPPORT;
    }

    return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : Standard_SetDeviceFeature.
* Description    : Set or enable a specific feature of Device.
* Input          : None.
* Output         : None.
* Return         : - Return USB_SUCCESS, if the request is performed.
*                  - Return USB_UNSUPPORT, if the request is invalid.
*******************************************************************************/
uint8_t std_dev_feature_set(void *p_arg)
{
    am_zmf159_device_t *p_dev = (am_zmf159_device_t *)p_arg;

    AM_BIT_SET(p_dev->cur_feature, 5);
    return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : Standard_GetDescriptorData.
* Description    : Standard_GetDescriptorData is used for descriptors transfer.
*                : This routine is used for the descriptors resident in Flash
*                  or RAM
*                  pDesc can be in either Flash or RAM
*                  The purpose of this routine is to have a versatile way to
*                  response descriptors request. It allows user to generate
*                  certain descriptors with software or read descriptors from
*                  external storage part by part.
* Input          : - Length - Length of the data in this transfer.
*                  - pDesc - A pointer points to descriptor struct.
*                  The structure gives the initial address of the descriptor and
*                  its original size.
* Output         : None.
* Return         : Address of a part of the descriptor pointed by the Usb_
*                  wOffset The buffer pointed by this address contains at least
*                  Length bytes.
*******************************************************************************/
uint8_t *std_descriptor_get(void *p_arg, uint16_t length, const am_usbd_descriptor_t *p_desc)
{
    am_zmf159_device_t *p_dev = (am_zmf159_device_t *)p_arg;
    uint32_t  wOffset = p_dev->ctrl_info.Usb_wOffset;

    if (length == 0) {
        p_dev->ctrl_info.Usb_wLength = p_desc->desc_size - wOffset;
        return 0;
    }

    return (uint8_t *)(p_desc->p_desc + wOffset);
}

/*******************************************************************************
* Function Name  : SetDeviceAddress.
* Description    : Set the device and all the used Endpoints addresses.
* Input          : - Val: device adress.
* Output         : None.
* Return         : None.
*******************************************************************************/
void __usbd_add_set(uint8_t Val)
{
    amhw_zmf159_addr_set(ZMF159_USB, Val);
}


/*******************************************************************************
* Function Name  : Virtual_Com_Port_GetLineCoding.
* Description    : send the linecoding structure to the PC host.
* Input          : Length.
* Output         : None.
* Return         : Inecoding structure base address.
*******************************************************************************/
static uint8_t *__virtual_com_port_getlinecoding(void *p_arg, uint16_t Length)
{
    am_zmf159_device_t  *p_dev = (am_zmf159_device_t *)p_arg;
    if (Length == 0) {
        p_dev->ctrl_info.Usb_wLength = sizeof(linecoding);
        return NULL;
    }
    return(uint8_t *)&linecoding;
}

/*******************************************************************************
* Function Name  : Virtual_Com_Port_SetLineCoding.
* Description    : Set the linecoding structure fields.
* Input          : Length.
* Output         : None.
* Return         : Linecoding structure base address.
*******************************************************************************/
static uint8_t *__virtual_com_port_setlinecoding(void *p_arg, uint16_t Length)
{
    am_zmf159_device_t *p_dev = (am_zmf159_device_t *)p_arg;

    if (Length == 0) {
        p_dev->ctrl_info.Usb_wLength = sizeof(linecoding);
        return NULL;
    }
    return(uint8_t *)&linecoding;
}



/*******************************************************************************
* Function Name  : Virtual_Com_Port_init.
* Description    : Virtual COM Port Mouse init routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/

static am_usb_status_t __ep_init(am_zmf159_device_t       *p_dev,
                                    am_usbd_endpoint_init_t  *epinit)
{
    int i       = 0;
    uint8_t  ep = (epinit->endpoint_address & AM_USBD_ENDPOINT_NUMBER_MASK);

    amhw_zmf159_usb_bdt_t  *pUSB_OTG_BDT = p_dev->p_usb_bdt + ep;
    uint32_t                dataBufAdd   = (uint32_t)pUSB_OTG_BDT+0x200+0x100*ep;

    for (i = 0; i < AM_USBD_MAX_EP_CNT; i++) {
        /* 端点描述符中必须指定了这个端点 */
        if (p_dev->isa.endpoint_info[i].inuse == AM_TRUE &&
            p_dev->isa.endpoint_info[i].ep_address == epinit->endpoint_address) {
            break;
        }
    }

    if (i == AM_USBD_MAX_EP_CNT)
        return AM_USB_STATUS_INVALID_REQUEST;

    if (ep >= AM_USBD_MAX_EP_CNT)
        return AM_USB_STATUS_INVALID_PARAMETER;
    if (epinit->transfer_type > AM_USB_ENDPOINT_INTERRUPT)
        return AM_USB_STATUS_INVALID_PARAMETER;

    /* 设置端点能传输的最大字节个数 */
    if (epinit->max_packet_size > AM_USBD_MAX_EP_DATA_CNT)
        epinit->max_packet_size = AM_USBD_MAX_EP_DATA_CNT;

    pUSB_OTG_BDT->rx_buf[0].format = 0;
    pUSB_OTG_BDT->rx_buf[0].adress = dataBufAdd;
    pUSB_OTG_BDT->rx_buf[0].format |= 0x40<<16;//长度64byte
    pUSB_OTG_BDT->rx_buf[0].format |= 1<<7;

    pUSB_OTG_BDT->rx_buf[1].format = 0;
    pUSB_OTG_BDT->rx_buf[1].format |= 0x40<<16;//长度64byte
    pUSB_OTG_BDT->rx_buf[1].adress = pUSB_OTG_BDT->rx_buf[0].adress+0x40;
    pUSB_OTG_BDT->rx_buf[1].format |= 1<<6;
    pUSB_OTG_BDT->rx_buf[1].format |= 1<<7;

    pUSB_OTG_BDT->tx_buf[0].format = 0x00;
    pUSB_OTG_BDT->tx_buf[0].adress = pUSB_OTG_BDT->rx_buf[0].adress+0x80;

    pUSB_OTG_BDT->tx_buf[1].format = 0x00;
    pUSB_OTG_BDT->tx_buf[1].adress = pUSB_OTG_BDT->rx_buf[0].adress+0xC0;

    for(i = 0; i < 64; i++) {
        *(uint8_t*)(pUSB_OTG_BDT->tx_buf[0].adress + i) = 0;
        *(uint8_t*)(pUSB_OTG_BDT->tx_buf[1].adress + i) = 0;
        *(uint8_t*)(pUSB_OTG_BDT->rx_buf[0].adress + i) = 0;
        *(uint8_t*)(pUSB_OTG_BDT->rx_buf[1].adress + i) = 0;
    }

    if (ep == 0) {
        amhw_zmf159_ep_ctrl_set(ZMF159_USB, 0, 0x0d);
    } else if (epinit->endpoint_address >> 7) {
        amhw_zmf159_ep_ctrl_set(ZMF159_USB, ep, 0x05);
    } else {
    	amhw_zmf159_ep_ctrl_set(ZMF159_USB, ep, 0x09);
    }

    p_dev->isa.endpoint_info[ep].stalled         = 0;
    p_dev->isa.endpoint_info[ep].max_packet_size = epinit->max_packet_size;
    p_dev->isa.endpoint_info[ep].transfer_type   = epinit->transfer_type;

    return AM_USB_STATUS_SUCCESS;
}



static am_usb_status_t __zmf159_init(void *p_arg)
{
	uint8_t i = 0;
    am_usbd_endpoint_init_t endpoint;
    am_zmf159_device_t    *p_dev        = (am_zmf159_device_t *)p_arg;
    p_dev->cur_config        = 0;

    if (p_dev == NULL) {
    	return AM_USB_STATUS_INVALID_HANDLE;
    }

    amhw_zmf159_bdt_page_set(ZMF159_USB, 0x20007000);

    amhw_zmf159_addr_set(ZMF159_USB, 0);
    amhw_zmf159_ctrl_set(ZMF159_USB, ZMF159_USB_ODD_RST);
    amhw_zmf159_ctrl_reset(ZMF159_USB, ZMF159_USB_ODD_RST);

    p_dev->p_usb_bdt = (amhw_zmf159_usb_bdt_t *)amhw_zmf159_bdt_page_get(ZMF159_USB);

    /* 清除SETUP数据 */
    p_dev->isa.setup_data.bm_request_type = 0;
    p_dev->isa.setup_data.b_request       = 0;
    p_dev->isa.setup_data.w_value         = 0;
    p_dev->isa.setup_data.w_index         = 0;
    p_dev->isa.setup_data.w_length        = 0;

    /**< \brief 初始化端点 */
    for (i = 0; i < AM_USBD_MAX_EP_CNT; i++) {
        if (p_dev->isa.endpoint_info[i].inuse == 1) {
            endpoint.endpoint_address = p_dev->isa.endpoint_info[i].ep_address;
            endpoint.max_packet_size  = p_dev->isa.endpoint_info[i].max_packet_size;
            endpoint.transfer_type    = p_dev->isa.endpoint_info[i].transfer_type;
            __ep_init(p_dev, &endpoint);
        }
    }

    p_dev->tx_odd[0] = 0;

    amhw_zmf159_ctrl_set(ZMF159_USB, ZMF159_USB_EN);

    amhw_zmf159_usb_int_enable(ZMF159_USB,
                               ZMF159_USB_INT_STAT_RST | ZMF159_USB_INT_STAT_TOK_DNE);

    return AM_USB_STATUS_SUCCESS;
}


static am_usb_status_t __zmf159_deinit(void *p_arg)
{
	am_zmf159_device_t *p_dev  = (am_zmf159_device_t *)p_arg;

    if (p_dev == NULL) {
    	return AM_USB_STATUS_INVALID_HANDLE;
    }

    amhw_zmf159_ctrl_reset(ZMF159_USB, ZMF159_USB_EN);
    amhw_zmf159_usb_int_disable(ZMF159_USB,
                                ZMF159_USB_INT_STAT_RST | ZMF159_USB_INT_STAT_TOK_DNE);
    amhw_zmf159_addr_set(ZMF159_USB, 0);

    if (p_dev->p_info->pfn_plfm_deinit)
        p_dev->p_info->pfn_plfm_deinit();

    return AM_USB_STATUS_SUCCESS;
}
/*******************************************************************************
* Function Name  : Virtual_Com_Port_Reset
* Description    : Virtual_Com_Port Mouse reset routine
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
static void __zmf159_reset(void *p_arg)
{
	uint8_t i = 0;
    am_usbd_endpoint_init_t endpoint;
    am_zmf159_device_t     *p_dev = (am_zmf159_device_t *)p_arg;

    p_dev->cur_config = 0;

    /* Current Feature initialization */
    p_dev->cur_feature = p_dev->p_info->p_devinfo->p_descriptor[1].p_desc[7];  // 获取配置描述符中的值

    p_dev->cur_interface = 0;

    p_dev->p_usb_bdt = (amhw_zmf159_usb_bdt_t *)amhw_zmf159_bdt_page_get(ZMF159_USB);

    /* 清除SETUP数据 */
    p_dev->isa.setup_data.bm_request_type = 0;
    p_dev->isa.setup_data.b_request       = 0;
    p_dev->isa.setup_data.w_value         = 0;
    p_dev->isa.setup_data.w_index         = 0;
    p_dev->isa.setup_data.w_length        = 0;

    /**< \brief 初始化端点 */
    for (i = 0; i < AM_USBD_MAX_EP_CNT; i++) {
        if (p_dev->isa.endpoint_info[i].inuse == 1) {
            endpoint.endpoint_address = p_dev->isa.endpoint_info[i].ep_address;
            endpoint.max_packet_size  = p_dev->isa.endpoint_info[i].max_packet_size;
            endpoint.transfer_type    = p_dev->isa.endpoint_info[i].transfer_type;
            __ep_init(p_dev, &endpoint);
        }
    }

    amhw_zmf159_ep_ctrl_set(ZMF159_USB, 0, 0x0d);
    amhw_zmf159_ctrl_set(ZMF159_USB, ZMF159_USB_ODD_RST);
    amhw_zmf159_ctrl_reset(ZMF159_USB, ZMF159_USB_ODD_RST);

    p_dev->tx_odd[0] = 0;
    amhw_zmf159_addr_set(ZMF159_USB, 0);

}


/*******************************************************************************
* Function Name  : Virtual_Com_Port_Data_Setup
* Description    : handle the data class specific requests
* Input          : Request Nb.
* Output         : None.
* Return         : USB_UNSUPPORT or USB_SUCCESS.
*******************************************************************************/
static uint8_t vcom_class_req(void *p_arg, uint8_t num)
{
    am_zmf159_device_t  *p_dev = (am_zmf159_device_t *)p_arg;
    uint8_t  *(*CopyRoutine)(void *p_arg, uint16_t);

    CopyRoutine = NULL;

    switch (num) {

    case SET_COMM_FEATURE :
    {
    	return USB_SUCCESS;
    }
    case GET_LINE_CODING :
    {
        if (Recipient == (AM_USB_REQ_TYPE_TYPE_CLASS | AM_USB_REQ_TYPE_RECIPIENT_INTERFACE))
        {
//        	am_usbd_send();
            CopyRoutine = __virtual_com_port_getlinecoding;
        }
        break;
    }

    case SET_LINE_CODING:
    {
        if (Recipient == (AM_USB_REQ_TYPE_TYPE_CLASS | AM_USB_REQ_TYPE_RECIPIENT_INTERFACE))
        {
//            am_usbd_recv(p_dev->isa.ctrl_handle, 0, (uint8_t *)&linecoding, sizeof(linecoding));

            CopyRoutine = __virtual_com_port_setlinecoding;
        }
        break;
    }

    case SET_CONTROL_LINE_STATE:
    {
    	return USB_SUCCESS;
    }

    default :
        break;
    }

    if (CopyRoutine == NULL) {
        return USB_UNSUPPORT;
    }

    p_dev->ctrl_info.CopyData = CopyRoutine;
    p_dev->ctrl_info.Usb_wOffset = 0;

    (*CopyRoutine)(p_dev, 0);
    return USB_SUCCESS;
}


/*******************************************************************************
* Function Name  : Virtual_Com_Port_GetConfigDescriptor.
* Description    : get the configuration descriptor.
* Input          : Length.
* Output         : None.
* Return         : The address of the configuration descriptor.
*******************************************************************************/
static uint8_t *Virtual_Com_Port_GetDescriptor(void *p_arg, uint16_t Length)
{
    volatile uint8_t i = 0;
    am_zmf159_device_t  *p_dev = (am_zmf159_device_t *)p_arg;

    for (i = 0; i < p_dev->p_info->p_devinfo->descriptor_num; i++) {
        if (p_dev->isa.setup_data.w_value == p_dev->p_info->p_devinfo->p_descriptor[i].desc_wValue) {
            return std_descriptor_get(p_dev,
                                      Length,
                                     &p_dev->p_info->p_devinfo->p_descriptor[i]);
        }
    }
    return NULL;
}

/*******************************************************************************
* Function Name  : Virtual_Com_Port_Get_Interface_Setting.
* Description    : test the interface and the alternate setting according to the
*                  supported one.
* Input1         : uint8_t: Interface : interface number.
* Input2         : uint8_t: AlternateSetting : Alternate Setting number.
* Output         : None.
* Return         : The address of the string descriptors.
*******************************************************************************/
static uint8_t vcom_interface_get(uint8_t Interface, uint8_t AlternateSetting)
{
    if (AlternateSetting > 0) {
        return USB_UNSUPPORT;
    } else if (Interface > 1) {
        return USB_UNSUPPORT;
    }

    return USB_SUCCESS;
}

/**
 * \brief 终止某个端点正在进行的传输
 *
 * \param[in] handle        : 设备句柄
 * \param[in] endpoint_addr : 端点地址
 *
 * \retval USB错误码
 */
static am_usb_status_t __zmf159_usbd_cancel (am_usbd_handle_t handle,
                                            uint8_t           endpoint_addr)
{
    return AM_USB_STATUS_ERROR;
}

static am_usb_status_t __zmf159_usbd_control(am_usbd_handle_t         handle,
                                            am_usbd_control_type_t    type,
                                            void                     *param)
{
    return AM_USB_STATUS_SUCCESS;
}


static const am_usbd_interface_t __g_usb_device_interface = {
	__zmf159_init,
	__zmf159_deinit,
	am_zmf159_usbd_send,
	am_zmf159_usbd_recv,
	__zmf159_usbd_cancel,
	__zmf159_usbd_control,
};



/*******************************************************************************
* Function Name  : DataStageOut.
* Description    : Data stage of a Control Write Transfer.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/

static void __data_stage_out(am_zmf159_device_t *p_dev)
{
    uint8_t *Buffer       = NULL;
    uint32_t Length       = 0;
    uint32_t save_rLength = 0;
    am_endpoint_info *pEPinfo = &p_dev->ctrl_info;

    save_rLength = pEPinfo->Usb_wLength;

    if (pEPinfo->CopyData && save_rLength) {
        Length = pEPinfo->PacketSize;

        if (Length > save_rLength) {
            Length = save_rLength;
        }

        Buffer = (*pEPinfo->CopyData)(p_dev, Length);
        pEPinfo->Usb_wLength -= Length;
        pEPinfo->Usb_wOffset += Length;

        am_zmf159_usbd_recv(p_dev, ENDP0, Buffer, Length);//EP0接收OUT_PACK数据

        am_kprintf("bitrate:0x%x \r\n", linecoding.bitrate);
    }

    /* Set the next State*/
    if (pEPinfo->Usb_wLength >= pEPinfo->PacketSize) {
          p_dev->state = OUT_DATA;
    } else {

        if (pEPinfo->Usb_wLength > 0) {
            p_dev->state = LAST_OUT_DATA;

        } else if (pEPinfo->Usb_wLength == 0) {

            p_dev->state = WAIT_STATUS_IN;
            p_dev->ep_indata_num[0] = 1;
            am_zmf159_usbd_send(p_dev, ENDP0, (uint8_t *)(&p_dev->isa.setup_data), 0);
        }
    }
}

/*******************************************************************************
* Function Name  : DataStageIn.
* Description    : Data stage of a Control Read Transfer.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
static void __data_stage_in(am_zmf159_device_t *p_dev)
{
    am_endpoint_info *pEPinfo = &p_dev->ctrl_info;
    uint32_t save_wLength     = pEPinfo->Usb_wLength;
    uint32_t ControlState     = p_dev->state;

    uint8_t *DataBuffer;
    uint32_t Length;

    if ((save_wLength == 0) && (ControlState == LAST_IN_DATA)) {
        if(p_dev->data_mul == AM_TRUE) {

            /* No more data to send and empty packet */
            am_zmf159_usbd_send(p_dev, ENDP0, (uint8_t *)(&p_dev->isa.setup_data), 0);
            ControlState                  = LAST_IN_DATA;
            p_dev->data_mul = AM_FALSE;
        } else {

            /* No more data to send so STALL the TX Status*/
            ControlState = WAIT_STATUS_OUT;
        }

        goto Expect_Status_Out;
    }

    Length = pEPinfo->PacketSize;
    ControlState = (save_wLength <= Length) ? LAST_IN_DATA : IN_DATA;

    if (Length > save_wLength) {
        Length = save_wLength;
    }

    DataBuffer = (*pEPinfo->CopyData)(p_dev, Length);

    am_zmf159_usbd_send(p_dev, ENDP0, DataBuffer, Length);

    pEPinfo->Usb_wLength -= Length;
    pEPinfo->Usb_wOffset += Length;

Expect_Status_Out:
  p_dev->state = ControlState;
}

/*******************************************************************************
* Function Name  : NoData_Setup0.
* Description    : Proceed the processing of setup request without data stage.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
static void __nodata_setup0(am_zmf159_device_t *p_dev)
{
    uint8_t Result = USB_UNSUPPORT;
    uint32_t RequestNo = p_dev->isa.setup_data.b_request;
    uint32_t ControlState;

    if (Recipient == (AM_USB_REQ_TYPE_TYPE_STANDARD | AM_USB_REQ_TYPE_RECIPIENT_DEVICE)) {
        if (RequestNo == AM_USB_REQ_STANDARD_SET_CONFIGURATION) {
            Result = std_config_set(p_dev);
        } else if (RequestNo == AM_USB_REQ_STANDARD_SET_ADDRESS) {
            if ((p_dev->isa.setup_data.w_value > 127)
               || (p_dev->isa.setup_data.w_index != 0)
               || (p_dev->cur_config != 0)) {
                ControlState = STALLED;

                goto exit_NoData_Setup0;
            } else {
                Result = USB_SUCCESS;
            }
        } else if (RequestNo == AM_USB_REQ_STANDARD_SET_FEATURE) { /*SET FEATURE for Device*/

            if (((p_dev->isa.setup_data.w_value & (0xff)) == AM_USB_REQ_STA_FEATURE_DEVICE_REMOTE_WAKEUP)
                 && (p_dev->isa.setup_data.w_index == 0)
                 && (AM_BIT_ISSET(p_dev->cur_feature, 5))) {
                Result = std_dev_feature_set(p_dev);
            } else {
                Result = USB_UNSUPPORT;
            }
        } else if (RequestNo == AM_USB_REQ_STANDARD_CLEAR_FEATURE) {
        /*Clear FEATURE for Device */
            if ((p_dev->isa.setup_data.w_value & 0xff) == AM_USB_REQ_STA_FEATURE_DEVICE_REMOTE_WAKEUP
                 && p_dev->isa.setup_data.w_index  == 0
                 && AM_BIT_ISSET(p_dev->cur_feature, 5)) {
                Result = std_feature_clr(p_dev);
            } else {
                Result = USB_UNSUPPORT;
            }
        }
    } else if (Recipient == (AM_USB_REQ_TYPE_TYPE_STANDARD | AM_USB_REQ_TYPE_RECIPIENT_INTERFACE)) {
    /* Interface Request*/
    /*SET INTERFACE*/
        if (RequestNo == AM_USB_REQ_STANDARD_SET_INTERFACE) {
            Result = std_interface_set(p_dev);
        }
    }

    /* EndPoint Request*/
    else if (Recipient == (AM_USB_REQ_TYPE_TYPE_STANDARD | AM_USB_REQ_TYPE_RECIPIENT_ENDPOINT)) {
        /*CLEAR FEATURE for EndPoint*/
        if (RequestNo == AM_USB_REQ_STANDARD_CLEAR_FEATURE) {
            Result = std_feature_clr(p_dev);
        }
        /* SET FEATURE for EndPoint*/
        else if (RequestNo == AM_USB_REQ_STANDARD_SET_FEATURE) {
            Result = std_ep_feature_set(p_dev);
        }
    } else {
        Result = USB_UNSUPPORT;
    }

    // 类请求
    if (Result != USB_SUCCESS) {
    	am_kprintf("-----------------class nodata req :%x ----------------\r\n", RequestNo);

        Result = vcom_class_req(p_dev, RequestNo);

        if (Result == USB_NOT_READY) {
            ControlState = PAUSE;
            goto exit_NoData_Setup0;
        }
    }

    if (Result != USB_SUCCESS) {
        goto exit_NoData_Setup0;
   }

    ControlState = WAIT_STATUS_IN;/* After no data stage SETUP */

    // 发送空包
    p_dev->ep_indata_num[0] = 1;
    am_zmf159_usbd_send(p_dev, ENDP0, (uint8_t *)(&p_dev->isa.setup_data), 0);

exit_NoData_Setup0:
    p_dev->state = ControlState;
    return;
}

/*******************************************************************************
* Function Name  : Data_Setup0.
* Description    : Proceed the processing of setup request with data stage.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void __data_setup0(am_zmf159_device_t *p_dev)
{
  uint8_t *(*CopyRoutine)(void *p_arg, uint16_t);
  uint8_t res;
  uint32_t req_num = p_dev->isa.setup_data.b_request;

  uint32_t Related_Endpoint, Reserved;
  uint32_t wOffset = 0, Status;

  CopyRoutine = NULL;

  if (req_num == AM_USB_REQ_STANDARD_GET_DESCRIPTOR)
  {
    if (Recipient == (AM_USB_REQ_TYPE_TYPE_STANDARD | AM_USB_REQ_TYPE_RECIPIENT_DEVICE))
    {
        CopyRoutine = Virtual_Com_Port_GetDescriptor;
    }
  }

  /*GET STATUS*/
  else if ((req_num == AM_USB_REQ_STANDARD_GET_STATUS) && (p_dev->isa.setup_data.w_value == 0)
           && (p_dev->isa.setup_data.w_length == 0x0002)
           && ((p_dev->isa.setup_data.w_index>>7) == 0))
  {
    /* GET STATUS for Device*/
    if ((Recipient == (AM_USB_REQ_TYPE_TYPE_STANDARD | AM_USB_REQ_TYPE_RECIPIENT_DEVICE))
        && (p_dev->isa.setup_data.w_index == 0)) {
      CopyRoutine = std_status_get;
    }

    /* GET STATUS for Interface*/
    else if (Recipient == (AM_USB_REQ_TYPE_TYPE_STANDARD | AM_USB_REQ_TYPE_RECIPIENT_INTERFACE))
    {
      if ((vcom_interface_get(p_dev->isa.setup_data.w_index, 0) == USB_SUCCESS)
          && (p_dev->cur_config != 0)) {
            CopyRoutine = std_status_get;
        }
    }

    /* GET STATUS for EndPoint*/
    else if (Recipient == (AM_USB_REQ_TYPE_TYPE_STANDARD | AM_USB_REQ_TYPE_RECIPIENT_ENDPOINT))
    {
      Related_Endpoint = (p_dev->isa.setup_data.w_index & 0x0f);
      Reserved = p_dev->isa.setup_data.w_index & 0x70;

      Status = amhw_zmf159_ep_stat_get(ZMF159_USB, Related_Endpoint);
      if ((Related_Endpoint < p_dev->ep_num) && (Reserved == 0)
          && (Status != 0)) {
        CopyRoutine = std_status_get;
      }
    }
  }

  /*GET CONFIGURATION*/
  else if (req_num == AM_USB_REQ_STANDARD_GET_CONFIGURATION)
  {
    if (Recipient == (AM_USB_REQ_TYPE_TYPE_STANDARD | AM_USB_REQ_TYPE_RECIPIENT_DEVICE))
    {
      CopyRoutine = std_config_get;
    }
  }
  /*GET INTERFACE*/
  else if (req_num == AM_USB_REQ_STANDARD_GET_INTERFACE)
  {
    if ((Recipient == (AM_USB_REQ_TYPE_TYPE_STANDARD | AM_USB_REQ_TYPE_RECIPIENT_INTERFACE))
        && (p_dev->cur_config != 0) && (p_dev->isa.setup_data.w_value == 0)
        && ((p_dev->isa.setup_data.w_index>>7) == 0) && (p_dev->isa.setup_data.w_length == 0x0001)
        && (vcom_interface_get(p_dev->isa.setup_data.w_index, 0) == USB_SUCCESS))
    {
      CopyRoutine = std_interface_get;
    }

  }

  if (CopyRoutine)
  {
      p_dev->ctrl_info.Usb_wOffset = wOffset;
      p_dev->ctrl_info.CopyData    = CopyRoutine;
    /* usb in the original the cast to word was directly */
    /* now the cast is made step by step */
    (*CopyRoutine)(p_dev, 0);
    res = USB_SUCCESS;
  } else {
      am_kprintf("----------------class  data req %x ------------------\r\n", p_dev->isa.setup_data.b_request);

      res = vcom_class_req(p_dev, p_dev->isa.setup_data.b_request);

      if (res == USB_NOT_READY) {
          p_dev->state = PAUSE;
          return;
      }
  }

  if (p_dev->ctrl_info.Usb_wLength == 0xFFFF)
  {
    /* Data is not ready, wait it */
      p_dev->state = PAUSE;
      return;
  }
  if ((res == USB_UNSUPPORT) || (p_dev->ctrl_info.Usb_wLength == 0))
  {
    /* Unsupported request */
      p_dev->state = STALLED;

    return;
  }


  if (AM_BIT_ISSET(p_dev->isa.setup_data.bm_request_type, 7)) // in
  {
    /* Device ==> Host */
	  am_kprintf("Device ==> Host\r\n");
    __IO uint32_t wLength = p_dev->isa.setup_data.w_length;

    /* Restrict the data length to be the one host asks */
    if (p_dev->ctrl_info.Usb_wLength > wLength)
    {
        p_dev->ctrl_info.Usb_wLength = wLength;
    }

    else if (p_dev->ctrl_info.Usb_wLength < p_dev->isa.setup_data.w_length)
    {
      if (p_dev->ctrl_info.Usb_wLength < p_dev->max_packsizee)
      {
          p_dev->data_mul = AM_FALSE;
      }
      else if ((p_dev->ctrl_info.Usb_wLength % p_dev->max_packsizee) == 0)
      {
          p_dev->data_mul = AM_TRUE;
      }
    }

    p_dev->ctrl_info.PacketSize = p_dev->max_packsizee;
    __data_stage_in(p_dev);
  }
  else
  {
	  am_kprintf("Host ==> Device\r\n");
      p_dev->ctrl_info.Usb_wLength = p_dev->isa.setup_data.w_length;//
      p_dev->state = OUT_DATA;
  }

  return;
}

/*******************************************************************************
* Function Name  : Setup0_Process
* Description    : Get the device request data and dispatch to individual process.
* Input          : None.
* Output         : None.
* Return         : Post0_Process.
*******************************************************************************/
static void __setup0_process(am_zmf159_device_t *p_dev)
{
    if (p_dev->state != PAUSE) {
        am_zmf159_usbd_recv(p_dev, ENDP0, (uint8_t *)(&p_dev->isa.setup_data), 8);
    }
    p_dev->state = SETTING_UP;

    if (p_dev->isa.setup_data.w_length == 0) {
        __nodata_setup0(p_dev);
    } else {
        __data_setup0(p_dev);
    }
}

/*******************************************************************************
* Function Name  : In0_Process
* Description    : Process the IN token on all default endpoint.
* Input          : None.
* Output         : None.
* Return         : Post0_Process.
*******************************************************************************/
static void __in0_process(am_zmf159_device_t *p_dev)
{
    uint32_t ControlState = p_dev->state;

    if ((ControlState == IN_DATA) || (ControlState == LAST_IN_DATA)) {
        __data_stage_in(p_dev);
        ControlState = p_dev->state;
    } else if (ControlState == WAIT_STATUS_IN) {

        if ((p_dev->isa.setup_data.b_request == AM_USB_REQ_STANDARD_SET_ADDRESS) &&
            (Recipient == (AM_USB_REQ_TYPE_TYPE_STANDARD | AM_USB_REQ_TYPE_RECIPIENT_DEVICE)))
        {
            __usbd_add_set(p_dev->isa.setup_data.w_value);
        }
    } else {
        ControlState = STALLED;
    }

    p_dev->state = ControlState;

}

/*******************************************************************************
* Function Name  : Out0_Process
* Description    : Process the OUT token on all default endpoint.
* Input          : None.
* Output         : None.
* Return         : Post0_Process.
*******************************************************************************/
static void __out0_process(am_zmf159_device_t *p_dev)
{
    uint32_t ControlState = p_dev->state;

    if ((ControlState == OUT_DATA) || (ControlState == LAST_OUT_DATA)) {
        __data_stage_out(p_dev);
        ControlState = p_dev->state; /* may be changed outside the function */
    } else if (ControlState == WAIT_STATUS_OUT) {

        am_zmf159_usbd_recv(p_dev, ENDP0, (uint8_t *)(&p_dev->isa.setup_data), 0);
        ControlState = STALLED;

    } else if ((ControlState == IN_DATA) || (ControlState == LAST_IN_DATA)) {

        ControlState = STALLED;
    } else {
        ControlState = STALLED;
    }

    p_dev->state = ControlState;
}


/*******************************************************************************
* Function Name  : __token_isr.
* Description    : Low priority Endpoint Correct Transfer interrupt's service
*                  routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/

static void __token_isr(am_zmf159_device_t *p_dev)
{
    uint32_t wEpIntSta = 0,wEpxIntSta = 0;
    uint32_t wEpStat;
    uint8_t tx_oddtemp;
    uint8_t ep;

    wEpStat = amhw_zmf159_usb_stat_get(ZMF159_USB);
    amhw_zmf159_usb_int_clear(ZMF159_USB, ZMF159_USB_INT_STAT_TOK_DNE);
    wEpIntSta = (wEpStat>>4)&0xf;           //获取中断端点号

    if(wEpIntSta == 0) {
        ep = 0;
        if(((wEpStat>>3)&0x01) == 0) {//RX
            p_dev->rx_odd[0] = (wEpStat>>2)&0x1;
            wEpxIntSta = p_dev->p_usb_bdt->rx_buf[p_dev->rx_odd[0]].format;
        } else {
            tx_oddtemp = (wEpStat>>2)&0x1;
            wEpxIntSta = p_dev->p_usb_bdt->tx_buf[tx_oddtemp].format;
            p_dev->p_usb_bdt->tx_buf[tx_oddtemp].format = 0;
        }
        wEpxIntSta = (wEpxIntSta >> 2)&0xf;

        if(wEpxIntSta == 0x0D) {//setup
            amhw_zmf159_ctrl_reset(ZMF159_USB, ZMF159_USB_TXD_SUSPEND_TOKBSY);
            p_dev->ep_indata_num[0] = 1;
            am_kprintf("setup \r\n");
            __setup0_process(p_dev);
            return;
        }

        if(wEpxIntSta == 0x01) {//|EPn_INT_STATE_OUTNACK
        	am_kprintf("OUTNACK \r\n");
            __out0_process(p_dev);
            return;
        }

        if(wEpxIntSta == 0x9) {//|EPn_INT_STATE_ACK
        	am_kprintf("INACK \r\n");
            __in0_process(p_dev);
            return;
        }
    } else if(wEpIntSta != 0) {

        ep = wEpIntSta;
        if(((wEpStat>>3)&0x01) == 0) { //RX
            p_dev->rx_odd[wEpIntSta] = (wEpStat>>2)&0x1;
            wEpxIntSta = (p_dev->p_usb_bdt+ep)->rx_buf[p_dev->rx_odd[ep]].format;
        } else {
            tx_oddtemp = (wEpStat>>2)&0x1;
            wEpxIntSta = (p_dev->p_usb_bdt + ep)->rx_buf[tx_oddtemp].format;
           (p_dev->p_usb_bdt+ep)->rx_buf[tx_oddtemp].format = 0;
        }
        wEpxIntSta = (wEpxIntSta >> 2)&0xf;  // 判断输入输出

        if (p_dev->isa.endpoint_info[ep].pfn_callback != NULL) {
            (p_dev->isa.endpoint_info[ep].pfn_callback)(p_dev->isa.endpoint_info[ep].p_arg);
        }
    }/* if(EPindex != 0)*/
}

/*******************************************************************************
* Function Name  : USB_Istr.
* Description    : ISTR events interrupt service routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
static void __zmf159_usbd_istr(void *p_arg)
{
    __IO uint16_t wIstr = 0;
    am_zmf159_device_t  *p_dev = (am_zmf159_device_t *)p_arg;

    wIstr = amhw_zmf159_usb_int_get(ZMF159_USB);
    if(wIstr & ZMF159_USB_INT_STAT_RST) {
        amhw_zmf159_usb_int_clear(ZMF159_USB, ZMF159_USB_INT_STAT_RST);
        __zmf159_reset(p_dev);
    }

    if(wIstr & ZMF159_USB_INT_STAT_TOK_DNE) {
    	am_kprintf("token \r\n");
        __token_isr(p_dev);   //在子程序中清除中断标志
    }
} /* USB_Istr */


/**
 * \brief 通过wValue的值寻找指定的描述符
 *
 * \retval 成功返回描述符指针，失败返回NULL
 *
 * \note 配置描述符的下级描述符不能通过此法获得
 */
static uint8_t * __find_desc_by_wValue1 (am_zmf159_device_t    *p_dev,
                                         uint16_t               w_value)
{
    int i = 0;

    for (i = 0; i < p_dev->p_info->p_devinfo->descriptor_num; i++) {
        if (w_value == p_dev->p_info->p_devinfo->p_descriptor[i].desc_wValue) {
            return (uint8_t *)(p_dev->p_info->p_devinfo->p_descriptor[i].p_desc);
        }
    }
    return NULL;
}


/**
 * \brief （通过配置描述符）初始化端点信息（端点个数，输入输出属性，支持的最大包大小）
 *
 * \retval 成功返回该使用的端点个数，失败返回-1
 */
static am_err_t __init_ep_info (am_zmf159_device_t *p_dev)
{
    uint8_t  ret     = 0;       /* 定义返回值 */
    uint8_t *p_tmp   = NULL;    /* 数据缓存指针 */
    uint8_t  ep_num  = 0;       /* 端点号 */
    uint8_t  tmp     = 0;       /* 临时变量*/
    uint8_t  offset  = 0;       /* 偏移量*/
    uint8_t  len     = 0;       /* 描述符总长度 */
    am_usb_descriptor_endpoint_t  *p_desc_ep   = NULL;
    /* 获取配置描述符 */
    p_tmp = __find_desc_by_wValue1(p_dev, (AM_USB_DESC_TYPE_CONFIGURE << 8) | 0);
    if (p_tmp == NULL)
        return AM_ERROR;
    /*配置描述符及其下属描述符的总长度*/
    len = (uint8_t)( ( *(p_tmp + 2) ) | ( ( *(p_tmp + 3)) >> 8 ) );
    /* 找端点描述符*/
    while (tmp < len) {
        offset  = *(p_tmp);   /* 该描述符的字节数,第一次为配置描述符*/
        p_tmp  +=   offset;   /* 做偏移 */
        tmp    +=   offset;
        /* 如果是端点描述符*/
        if ((*(p_tmp + 1) == AM_USB_DESC_TYPE_ENDPOINT) && (*p_tmp = AM_USB_DESC_LENGTH_ENDPOINT)) {
            p_desc_ep = (am_usb_descriptor_endpoint_t *)p_tmp;  // 端点描述符
            // 端点号
            ep_num = (p_desc_ep->b_endpoint_address & AM_USB_DESC_ENDPOINT_ADDR_NUMBER_MASK);
//            am_kprintf("inuse endpoint: %d \n", ep_num);
            p_dev->isa.endpoint_info[ep_num].inuse           = 1;  // 表示端点被使用
            p_dev->isa.endpoint_info[ep_num].ep_address      = p_desc_ep->b_endpoint_address;
            p_dev->isa.endpoint_info[ep_num].max_packet_size = (p_desc_ep->wmax_packet_size[1] << 8) |
                                                                   p_desc_ep->wmax_packet_size[0];
            p_dev->isa.endpoint_info[ep_num].transfer_type   = p_desc_ep->bm_attributes;
            p_dev->isa.endpoint_info[ep_num].stalled = 0;
            ret++;
        }
    }
    return ret;
}

/*******************************************************************************
* Function Name  : USB_Init
* Description    : USB system initialization
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
am_zmf159_device_t *am_zmf159_usbd_init(am_zmf159_device_t              *p_dev,
                                       const am_zmf159_usbd_devinfo_t  *p_info)
{
    uint8_t i = 0;
    p_dev->isa.ctrl_handle = p_dev;

    p_dev->p_info = p_info;

    p_dev->state = 2;
    p_dev->isa.p_interface = &__g_usb_device_interface;

    p_dev->data_mul = AM_FALSE;

    /* Initialize devices one by one */
    p_dev->ep_num             = EP_NUM;
    p_dev->config_num = 1;

    p_dev->rx_buf   = NULL;
    p_dev->max_packsizee = 0x40; // 64

    /**< \brief 设置端点0的默认配置 */
    p_dev->isa.endpoint_info[0].stalled          = 0;
    p_dev->isa.endpoint_info[0].ep_address       = 0;
    p_dev->isa.endpoint_info[0].max_packet_size  = AM_USBD_MAX_EP_DATA_CNT;
    p_dev->isa.endpoint_info[0].transfer_type    = AM_USB_ENDPOINT_CONTROL;
    p_dev->isa.endpoint_info[0].inuse            = 1;
    p_dev->isa.endpoint_info[0].val_length       = 0;

    for (i = 1 ;i < AM_USBD_MAX_EP_CNT; i++) {
        p_dev->isa.endpoint_info[i].stalled          = 0;
        p_dev->isa.endpoint_info[i].ep_address       = 0;
        p_dev->isa.endpoint_info[i].max_packet_size  = 0;
        p_dev->isa.endpoint_info[i].transfer_type    = 0;
        p_dev->isa.endpoint_info[i].inuse            = 0;
        p_dev->isa.endpoint_info[i].val_length       = 0;
    }

    if (__init_ep_info(p_dev) == -1) {
        am_kprintf("fail to init endpoint\n");
    }

    if (p_dev->p_info->pfn_plfm_init) {
        p_dev->p_info->pfn_plfm_init();
    }

      p_dev->isa.p_interface->pfn_device_init(p_dev);

    am_int_connect(p_dev->p_info->inum, __zmf159_usbd_istr, p_dev);
    am_int_enable(p_dev->p_info->inum);

    // 临时
    p_dev->isa.endpoint_info[1].pfn_callback = __vcom_send_cb;
    p_dev->isa.endpoint_info[1].p_arg = p_dev;

    p_dev->isa.endpoint_info[3].pfn_callback = __vcom_recv_cb;
    p_dev->isa.endpoint_info[3].p_arg = p_dev;

    return p_dev;
}

