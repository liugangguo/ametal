
/* Includes ------------------------------------------------------------------*/
#include "../../usb_lib/inc/usb_lib.h"
#include "../inc/usb_conf.h"
#include "../inc/usb_prop.h"
#include "../inc/usb_desc.h"
#include "../inc/usb_istr.h"

#include "zmf159_periph_map.h"
#include "hw/amhw_zmf159_rcc.h"
#include "zmf159_inum.h"
#include "zmf159_pin.h"
#include "am_int.h"


static uint8_t __Request = 0;

line_coding_t linecoding = {
    9600, /* baud rate*/
    0x00,   /* stop bits-1*/
    0x00,   /* parity - none*/
    0x08    /* no. of bits 8*/
  };


am_device_prop am_device_property = {
    Virtual_Com_Port_init,
    Virtual_Com_Port_Reset,
    Virtual_Com_Port_Status_In,
    Virtual_Com_Port_Status_Out,
    Virtual_Com_Port_Data_Setup,
    Virtual_Com_Port_NoData_Setup,
    Virtual_Com_Port_Get_Interface_Setting,
    Virtual_Com_Port_GetDeviceDescriptor,
    Virtual_Com_Port_GetConfigDescriptor,
    Virtual_Com_Port_GetStringDescriptor,
    Virtual_Com_Port_SetDeviceAddress,
};


ONE_DESCRIPTOR Device_Descriptor = {
    (uint8_t*)Virtual_Com_Port_DeviceDescriptor,
    VIRTUAL_COM_PORT_SIZ_DEVICE_DESC
  };

ONE_DESCRIPTOR Config_Descriptor = {
    (uint8_t*)Virtual_Com_Port_ConfigDescriptor,
    VIRTUAL_COM_PORT_SIZ_CONFIG_DESC
  };

ONE_DESCRIPTOR String_Descriptor[4] = {
    {(uint8_t*)Virtual_Com_Port_StringLangID, VIRTUAL_COM_PORT_SIZ_STRING_LANGID},
    {(uint8_t*)Virtual_Com_Port_StringVendor, VIRTUAL_COM_PORT_SIZ_STRING_VENDOR},
    {(uint8_t*)Virtual_Com_Port_StringProduct, VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT},
    {(uint8_t*)Virtual_Com_Port_StringSerial, VIRTUAL_COM_PORT_SIZ_STRING_SERIAL}
  };

/*******************************************************************************
* Function Name  : Virtual_Com_Port_init.
* Description    : Virtual COM Port Mouse init routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/

void EndPointInit( amhw_zmf159_usb_bdt_t *pUSB_OTG_BDT,uint32_t dataBufAdd)
{
  int i;
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

  for(i = 0;i < 64;i ++)
  {
    *(uint8_t*)(pUSB_OTG_BDT->tx_buf[0].adress + i) = 0;
    *(uint8_t*)(pUSB_OTG_BDT->tx_buf[1].adress + i) = 0;
    *(uint8_t*)(pUSB_OTG_BDT->rx_buf[0].adress + i) = 0;
    *(uint8_t*)(pUSB_OTG_BDT->rx_buf[1].adress + i) = 0;
  }
}



void Virtual_Com_Port_init(void)
{
  amhw_zmf159_usb_bdt_t *pUSB_OTG_BDT = NULL;

  zmf159_handle->Current_Configuration = 0;

  /* USB interrupts initialization */
  amhw_zmf159_rcc_ahb2_enable(AMHW_ZMF159_RCC_AHB2_USBFS);
  
  am_int_connect(INUM_USB_FS, USB_Istr, NULL);
  am_int_enable(INUM_USB_FS);

  amhw_zmf159_bdt_page_set(ZMF159_USB, 0x20007000);

    amhw_zmf159_addr_set(ZMF159_USB, 0);
    amhw_zmf159_ctrl_set(ZMF159_USB, ZMF159_USB_ODD_RST);
    amhw_zmf159_ctrl_reset(ZMF159_USB, ZMF159_USB_ODD_RST);

    zmf159_handle->pUSB_OTG_BDT = (amhw_zmf159_usb_bdt_t *)amhw_zmf159_bdt_page_get(ZMF159_USB);

    pUSB_OTG_BDT = zmf159_handle->pUSB_OTG_BDT;

  EndPointInit( pUSB_OTG_BDT + 0,(uint32_t)pUSB_OTG_BDT+0x200+0x100*0);
  EndPointInit( pUSB_OTG_BDT + 1,(uint32_t)pUSB_OTG_BDT+0x200+0x100*1);
  EndPointInit( pUSB_OTG_BDT + 2,(uint32_t)pUSB_OTG_BDT+0x200+0x100*2);
  EndPointInit( pUSB_OTG_BDT + 3,(uint32_t)pUSB_OTG_BDT+0x200+0x100*3);
  
  zmf159_handle->txUsbBufOdd[0] = 0;

    amhw_zmf159_ep_ctrl_set(ZMF159_USB, 0, 0x0d);
    amhw_zmf159_ep_ctrl_set(ZMF159_USB, 1, 0x05);
    amhw_zmf159_ep_ctrl_set(ZMF159_USB, 2, 0x05);
    amhw_zmf159_ep_ctrl_set(ZMF159_USB, 3, 0x09);


    amhw_zmf159_ctrl_set(ZMF159_USB, ZMF159_USB_EN);

    amhw_zmf159_usb_int_enable(ZMF159_USB,
                               USB_INT_STAT_RST | USB_INT_STAT_TOK_DNE);

}

/*******************************************************************************
* Function Name  : Virtual_Com_Port_Reset
* Description    : Virtual_Com_Port Mouse reset routine
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Virtual_Com_Port_Reset(void)
{
	  amhw_zmf159_usb_bdt_t *pUSB_OTG_BDT = NULL;

    zmf159_handle->Current_Configuration = 0;

    /* Current Feature initialization */
    zmf159_handle->Current_Feature = Virtual_Com_Port_ConfigDescriptor[7];

    zmf159_handle->Current_Interface = 0;

    zmf159_handle->pUSB_OTG_BDT = (amhw_zmf159_usb_bdt_t *)amhw_zmf159_bdt_page_get(ZMF159_USB);
    pUSB_OTG_BDT = zmf159_handle->pUSB_OTG_BDT;
    
    EndPointInit( pUSB_OTG_BDT + 0,(uint32_t)pUSB_OTG_BDT+0x200+0x100*0);
    EndPointInit( pUSB_OTG_BDT + 1,(uint32_t)pUSB_OTG_BDT+0x200+0x100*1);
    EndPointInit( pUSB_OTG_BDT + 2,(uint32_t)pUSB_OTG_BDT+0x200+0x100*2);
    EndPointInit( pUSB_OTG_BDT + 3,(uint32_t)pUSB_OTG_BDT+0x200+0x100*3);
  
    amhw_zmf159_ep_ctrl_set(ZMF159_USB, 0, 0x0d);
    amhw_zmf159_ctrl_set(ZMF159_USB, ZMF159_USB_ODD_RST);
    amhw_zmf159_ctrl_reset(ZMF159_USB, ZMF159_USB_ODD_RST);

    zmf159_handle->txUsbBufOdd[0] = 0;
    SetDeviceAddress(0);
    
}


/*******************************************************************************
* Function Name  : Virtual_Com_Port_SetConfiguration.
* Description    : Udpade the device state to addressed.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Virtual_Com_Port_SetDeviceAddress (void)
{
  SetDeviceAddress(zmf159_handle->USBwValues.bw.bb0);
}

/*******************************************************************************
* Function Name  : Virtual_Com_Port_Status_In.
* Description    : Virtual COM Port Status In Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Virtual_Com_Port_Status_In(void)
{
  if (__Request == SET_LINE_CODING)
  {
    __Request = 0;
  }
}

/*******************************************************************************
* Function Name  : Virtual_Com_Port_Status_Out
* Description    : Virtual COM Port Status OUT Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Virtual_Com_Port_Status_Out(void)
{
  uint8_t temp;
  PMAToUserBufferCopy(&temp, ENDP0, 0);
}

/*******************************************************************************
* Function Name  : Virtual_Com_Port_Data_Setup
* Description    : handle the data class specific requests
* Input          : Request Nb.
* Output         : None.
* Return         : USB_UNSUPPORT or USB_SUCCESS.
*******************************************************************************/
RESULT Virtual_Com_Port_Data_Setup(uint8_t RequestNo)
{
  uint8_t    *(*CopyRoutine)(uint16_t);

  CopyRoutine = NULL;

  if (RequestNo == GET_LINE_CODING)
  {
    if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
    {
      CopyRoutine = Virtual_Com_Port_GetLineCoding;
    }
  }
  else if (RequestNo == SET_LINE_CODING)
  {
    if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
    {
      CopyRoutine = Virtual_Com_Port_SetLineCoding;
    }
    __Request = SET_LINE_CODING;
  }

  if (CopyRoutine == NULL)
  {
    return USB_UNSUPPORT;
  }

  zmf159_handle->Ctrl_Info.CopyData = CopyRoutine;
  zmf159_handle->Ctrl_Info.Usb_wOffset = 0;
  (*CopyRoutine)(0);
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : Virtual_Com_Port_NoData_Setup.
* Description    : handle the no data class specific requests.
* Input          : Request Nb.
* Output         : None.
* Return         : USB_UNSUPPORT or USB_SUCCESS.
*******************************************************************************/
RESULT Virtual_Com_Port_NoData_Setup(uint8_t RequestNo)
{

  if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
  {
    if (RequestNo == SET_COMM_FEATURE)
    {
      return USB_SUCCESS;
    }
    else if (RequestNo == SET_CONTROL_LINE_STATE)
    {
      return USB_SUCCESS;
    }
  }

  return USB_UNSUPPORT;
}

/*******************************************************************************
* Function Name  : Virtual_Com_Port_GetDeviceDescriptor.
* Description    : Gets the device descriptor.
* Input          : Length.
* Output         : None.
* Return         : The address of the device descriptor.
*******************************************************************************/
uint8_t *Virtual_Com_Port_GetDeviceDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &Device_Descriptor);
}

/*******************************************************************************
* Function Name  : Virtual_Com_Port_GetConfigDescriptor.
* Description    : get the configuration descriptor.
* Input          : Length.
* Output         : None.
* Return         : The address of the configuration descriptor.
*******************************************************************************/
uint8_t *Virtual_Com_Port_GetConfigDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &Config_Descriptor);
}

/*******************************************************************************
* Function Name  : Virtual_Com_Port_GetStringDescriptor
* Description    : Gets the string descriptors according to the needed index
* Input          : Length.
* Output         : None.
* Return         : The address of the string descriptors.
*******************************************************************************/
uint8_t *Virtual_Com_Port_GetStringDescriptor(uint16_t Length)
{
  uint8_t wValue0 = zmf159_handle->USBwValues.bw.bb0;
  if (wValue0 > 4)
  {
    return NULL;
  }
  else
  {
    return Standard_GetDescriptorData(Length, &String_Descriptor[wValue0]);
  }
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
RESULT Virtual_Com_Port_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
{
  if (AlternateSetting > 0)
  {
    return USB_UNSUPPORT;
  }
  else if (Interface > 1)
  {
    return USB_UNSUPPORT;
  }
  return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : Virtual_Com_Port_GetLineCoding.
* Description    : send the linecoding structure to the PC host.
* Input          : Length.
* Output         : None.
* Return         : Inecoding structure base address.
*******************************************************************************/
uint8_t *Virtual_Com_Port_GetLineCoding(uint16_t Length)
{
  if (Length == 0)
  {
    zmf159_handle->Ctrl_Info.Usb_wLength = sizeof(linecoding);
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
uint8_t *Virtual_Com_Port_SetLineCoding(uint16_t Length)
{
  if (Length == 0)
  {
    zmf159_handle->Ctrl_Info.Usb_wLength = sizeof(linecoding);
    return NULL;
  }
  return(uint8_t *)&linecoding;
}

/******************* (C) COPYRIGHT 2018 MindMotion *****END OF FILE****/

