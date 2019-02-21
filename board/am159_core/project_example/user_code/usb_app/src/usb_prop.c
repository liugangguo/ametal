/******************** (C) COPYRIGHT 2018 MindMotion ********************
* File Name          : usb_prop.c 
* Version            : V1.0.0
* Date               : 2018/08/21
* Description        : All processing related to Virtual Com Port Demo
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, MindMotion SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "../../usb_lib/inc/usb_lib.h"
#include "../inc/usb_conf.h"
#include "../inc/usb_prop.h"
#include "../inc/usb_desc.h"
#include "../inc/usb_pwr.h"
#include "../inc/usb_istr.h"

#include "zmf159_periph_map.h"
#include "hw/amhw_zmf159_rcc.h"
#include "zmf159_inum.h"
#include "zmf159_pin.h"
#include "am_int.h"

extern amhw_zmf159_usb_bdt_t *pUSB_OTG_BDT;
extern uint8_t rxUsbBufOdd[16] ;
extern uint8_t txUsbBufOdd[16] ;
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

uint8_t Request = 0;

LINE_CODING linecoding =
  {
    9600, /* baud rate*/
    0x00,   /* stop bits-1*/
    0x00,   /* parity - none*/
    0x08    /* no. of bits 8*/
  };

/* -------------------------------------------------------------------------- */
/*  Structures initializations */
/* -------------------------------------------------------------------------- */

DEVICE Device_Table =
  {
    EP_NUM,
    1
  };

DEVICE_PROP Device_Property =
  {
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
    0,
    0x40 /*MAX PACKET SIZE*/
  };

USER_STANDARD_REQUESTS User_Standard_Requests =
  {
    Virtual_Com_Port_GetConfiguration,
    Virtual_Com_Port_SetConfiguration,
    Virtual_Com_Port_GetInterface,
    Virtual_Com_Port_SetInterface,
    Virtual_Com_Port_GetStatus,
    Virtual_Com_Port_ClearFeature,
    Virtual_Com_Port_SetEndPointFeature,
    Virtual_Com_Port_SetDeviceFeature,
    Virtual_Com_Port_SetDeviceAddress
  };

ONE_DESCRIPTOR Device_Descriptor =
  {
    (uint8_t*)Virtual_Com_Port_DeviceDescriptor,
    VIRTUAL_COM_PORT_SIZ_DEVICE_DESC
  };

ONE_DESCRIPTOR Config_Descriptor =
  {
    (uint8_t*)Virtual_Com_Port_ConfigDescriptor,
    VIRTUAL_COM_PORT_SIZ_CONFIG_DESC
  };

ONE_DESCRIPTOR String_Descriptor[4] =
  {
    {(uint8_t*)Virtual_Com_Port_StringLangID, VIRTUAL_COM_PORT_SIZ_STRING_LANGID},
    {(uint8_t*)Virtual_Com_Port_StringVendor, VIRTUAL_COM_PORT_SIZ_STRING_VENDOR},
    {(uint8_t*)Virtual_Com_Port_StringProduct, VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT},
    {(uint8_t*)Virtual_Com_Port_StringSerial, VIRTUAL_COM_PORT_SIZ_STRING_SERIAL}
  };

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : Virtual_Com_Port_init.
* Description    : Virtual COM Port Mouse init routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Virtual_Com_Port_init(void)
{
  /* Update the serial number string descriptor with the data from the unique
  ID*/ 
//  Get_SerialNum();
  pInformation->Current_Configuration = 0;
  /* Connect the device */
  PowerOn();
  /* USB interrupts initialization */

//  ZMF159_RCC->cfgr &= ~(0x3<<22);
//  ZMF159_RCC->cfgr |= (0x01<<22);
//  ZMF159_RCC->ahb2enr |= 1<<7;           //Enable usb clock
  amhw_zmf159_rcc_ahb2_enable(AMHW_ZMF159_RCC_AHB2_USBFS);
  
  am_int_connect(INUM_USB_FS, USB_Istr, NULL);
  am_int_enable(INUM_USB_FS);

//  USB_OTG_FS->OTG_CTRL = 0;
//  USB_OTG_FS->BDT_PAGE_03 = 0x20;
//  USB_OTG_FS->BDT_PAGE_02 = 0x00;
//  USB_OTG_FS->BDT_PAGE_01 = 0x70; //配置描述表地址
  amhw_zmf159_bdt_page_set(ZMF159_USB, 0x20007000);

//  USB_OTG_FS->ADDR = 0;
//  USB_OTG_FS->CTL |= 1 << 1;
//  USB_OTG_FS->CTL &= ~(1 << 1);//复位BDT ping/pang bits
    amhw_zmf159_addr_set(ZMF159_USB, 0);
    amhw_zmf159_ctrl_set(ZMF159_USB, ZMF159_USB_ODD_RST);
    amhw_zmf159_ctrl_reset(ZMF159_USB, ZMF159_USB_ODD_RST);

//  pUSB_OTG_BDT = (USB_OTG_BDT_TypeDef*)((USB_OTG_FS->BDT_PAGE_03<<24)|(USB_OTG_FS->BDT_PAGE_02<<16)|(USB_OTG_FS->BDT_PAGE_01<<8));
    pUSB_OTG_BDT = (amhw_zmf159_usb_bdt_t *)amhw_zmf159_bdt_page_get(ZMF159_USB);

  EndPointInit( pUSB_OTG_BDT + 0,(uint32_t)pUSB_OTG_BDT+0x200+0x100*0);
  EndPointInit( pUSB_OTG_BDT + 1,(uint32_t)pUSB_OTG_BDT+0x200+0x100*1);
  EndPointInit( pUSB_OTG_BDT + 2,(uint32_t)pUSB_OTG_BDT+0x200+0x100*2);
  EndPointInit( pUSB_OTG_BDT + 3,(uint32_t)pUSB_OTG_BDT+0x200+0x100*3);
  
  txUsbBufOdd[0] = 0;

//  USB_OTG_FS->EP_CTL[0] = 0x0d;     //使能端点0
//  USB_OTG_FS->EP_CTL[1] = 0x05;     //使能端点1
//  USB_OTG_FS->EP_CTL[2] = 0x05;     //使能端点2
//  USB_OTG_FS->EP_CTL[3] = 0x09;     //使能端点3
    amhw_zmf159_ep_ctrl_set(ZMF159_USB, 0, 0x0d);
    amhw_zmf159_ep_ctrl_set(ZMF159_USB, 1, 0x05);
    amhw_zmf159_ep_ctrl_set(ZMF159_USB, 2, 0x05);
    amhw_zmf159_ep_ctrl_set(ZMF159_USB, 3, 0x09);

//  USB_OTG_FS->CTL |= 1;           //使能USB
//  USB_OTG_FS->OTG_CTRL |= 0x80;   //连接

    amhw_zmf159_ctrl_set(ZMF159_USB, ZMF159_USB_EN);

//  USB_OTG_FS->INT_ENB = /*USB_INT_STAT_SOF_TOK| */USB_INT_STAT_RST|USB_INT_STAT_TOK_DNE;
//  USB_OTG_FS->OTG_CTRL |= 0x80;   //连接
    amhw_zmf159_usb_int_enable(ZMF159_USB,
                               USB_INT_STAT_RST | USB_INT_STAT_TOK_DNE);

  /* configure the USART 1 to the default settings */
	
  //UART_Config_Default(); //配置URAT默认参数
  bDeviceState = UNCONNECTED;
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
    /* Set Virtual_Com_Port DEVICE as not configured */
    pInformation->Current_Configuration = 0;

    /* Current Feature initialization */
    pInformation->Current_Feature = Virtual_Com_Port_ConfigDescriptor[7];

    /* Set Virtual_Com_Port DEVICE with the default Interface*/
    pInformation->Current_Interface = 0;

//    pUSB_OTG_BDT = (USB_OTG_BDT_TypeDef*)((USB_OTG_FS->BDT_PAGE_03<<24)|(USB_OTG_FS->BDT_PAGE_02<<16)|(USB_OTG_FS->BDT_PAGE_01<<8));
    pUSB_OTG_BDT = (amhw_zmf159_usb_bdt_t *)amhw_zmf159_bdt_page_get(ZMF159_USB);
    
    EndPointInit( pUSB_OTG_BDT + 0,(uint32_t)pUSB_OTG_BDT+0x200+0x100*0);
    EndPointInit( pUSB_OTG_BDT + 1,(uint32_t)pUSB_OTG_BDT+0x200+0x100*1);
    EndPointInit( pUSB_OTG_BDT + 2,(uint32_t)pUSB_OTG_BDT+0x200+0x100*2);
    EndPointInit( pUSB_OTG_BDT + 3,(uint32_t)pUSB_OTG_BDT+0x200+0x100*3);
  
//    USB_OTG_FS->EP_CTL[0] = 0x0d;     //使能端点0
//    USB_OTG_FS->CTL |= 1 << 1;
//    USB_OTG_FS->CTL &= ~(1 << 1);//复位BDT ping/pang bits
        amhw_zmf159_ep_ctrl_set(ZMF159_USB, 0, 0x0d);
        amhw_zmf159_ctrl_set(ZMF159_USB, ZMF159_USB_ODD_RST);
        amhw_zmf159_ctrl_reset(ZMF159_USB, ZMF159_USB_ODD_RST);

    txUsbBufOdd[0] = 0;
    SetDeviceAddress(0);
    
    //_SetUSB_Connect;
    bDeviceState = ATTACHED;
}

/*******************************************************************************
* Function Name  : Virtual_Com_Port_SetConfiguration.
* Description    : Udpade the device state to configured.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Virtual_Com_Port_SetConfiguration(void)
{
  DEVICE_INFO *pInfo = &Device_Info;

  if (pInfo->Current_Configuration != 0)
  {
    /* Device configured */
    bDeviceState = CONFIGURED;
  }
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
  SetDeviceAddress(pInformation->USBwValue0);
  bDeviceState = ADDRESSED;
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
  if (Request == SET_LINE_CODING)
  {
    //UART_Config();
    Request = 0;
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
    Request = SET_LINE_CODING;
  }

  if (CopyRoutine == NULL)
  {
    return USB_UNSUPPORT;
  }

  pInformation->Ctrl_Info.CopyData = CopyRoutine;
  pInformation->Ctrl_Info.Usb_wOffset = 0;
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
  uint8_t wValue0 = pInformation->USBwValue0;
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
    pInformation->Ctrl_Info.Usb_wLength = sizeof(linecoding);
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
    pInformation->Ctrl_Info.Usb_wLength = sizeof(linecoding);
    return NULL;
  }
  return(uint8_t *)&linecoding;
}

/******************* (C) COPYRIGHT 2018 MindMotion *****END OF FILE****/

