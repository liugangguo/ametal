
/* Includes ------------------------------------------------------------------*/
#include "../inc/usb_lib.h"

zmf159_device_t *zmf159_handle;

/*******************************************************************************
* Function Name  : USB_Init
* Description    : USB system initialization
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
zmf159_device_t *USB_Init(zmf159_device_t *p_dev)
{
  zmf159_handle = p_dev;
  zmf159_handle->ControlState = 2;
  zmf159_handle->pProperty = &am_device_property;

  /* Initialize devices one by one */
  zmf159_handle->Total_Endpoint      = EP_NUM;
  zmf159_handle->Total_Configuration = 1;

  zmf159_handle->RxEP_buffer   = NULL;
  zmf159_handle->MaxPacketSize = 0x40;

  zmf159_handle->pProperty->Init();

  return (&zmf159_dev);
}

