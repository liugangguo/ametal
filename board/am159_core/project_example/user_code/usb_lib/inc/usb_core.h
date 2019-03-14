
#ifndef __USB_CORE_H
#define __USB_CORE_H

#include "amhw_zmf159_usb.h"

typedef enum _CONTROL_STATE
{
  WAIT_SETUP,       /* 0 */
  SETTING_UP,       /* 1 */
  IN_DATA,          /* 2 */
  OUT_DATA,         /* 3 */
  LAST_IN_DATA,     /* 4 */
  LAST_OUT_DATA,    /* 5 */
  WAIT_STATUS_IN,   /* 6 */
  WAIT_STATUS_OUT,  /* 7 */
  STALLED,          /* 8 */
  PAUSE             /* 9 */
} CONTROL_STATE;    /* The state machine states of a control pipe */

typedef struct OneDescriptor
{
  uint8_t *Descriptor;
  uint16_t Descriptor_Size;
}
ONE_DESCRIPTOR, *PONE_DESCRIPTOR;

typedef enum _RESULT
{
  USB_SUCCESS = 0,    /* Process sucessfully */
  USB_ERROR,
  USB_UNSUPPORT,
  USB_NOT_READY       /* The process has not been finished, endpoint will be
                         NAK to further rquest */
} RESULT;


typedef struct __endpoint_info
{
  uint16_t  Usb_wLength;
  uint16_t  Usb_wOffset;
  uint16_t  PacketSize;
  uint8_t   *(*CopyData)(uint16_t Length);
}am_endpoint_info;


typedef union
{
  uint16_t w;
  struct BW
  {
    uint8_t bb1;
    uint8_t bb0;
  }
  bw;
} uint16_t_uint8_t;


typedef struct _device_prop
{
  void (*Init)(void);        /* Initialize the device */
  void (*Reset)(void);       /* Reset routine of this device */

  void (*Process_Status_IN)(void);
  void (*Process_Status_OUT)(void);

  RESULT (*Class_Data_Setup)(uint8_t RequestNo);

  RESULT (*Class_NoData_Setup)(uint8_t RequestNo);

  RESULT  (*Class_Get_Interface_Setting)(uint8_t Interface, uint8_t AlternateSetting);

  uint8_t* (*GetDeviceDescriptor)(uint16_t Length);
  uint8_t* (*GetConfigDescriptor)(uint16_t Length);
  uint8_t* (*GetStringDescriptor)(uint16_t Length);

  void (*User_SetDeviceAddress)(void);       /* Set Device Address */

} am_device_prop;

typedef struct zmf159_device
{
    uint8_t USBbmRequestType;       /* bmRequestType */
    uint8_t USBbRequest;            /* bRequest */
    uint16_t_uint8_t USBwValues;    /* wValue */
    uint16_t_uint8_t USBwIndexs;    /* wIndex */
    uint16_t_uint8_t USBwLengths;   /* wLength */

    uint8_t ControlState;            /* of type CONTROL_STATE */
    uint8_t Current_Feature;
    uint8_t Current_Configuration;   /* Selected configuration */
    uint8_t Current_Interface;       /* Selected interface of current configuration */
    uint8_t Current_AlternateSetting;/* Selected Alternate Setting of current
                                       interface*/

    uint8_t Total_Endpoint;        /* Number of endpoints that are used */
    uint8_t Total_Configuration;   /* Number of configuration available */

    uint8_t rxUsbBufOdd[16] ;
    uint8_t txUsbBufOdd[16] ;

    uint8_t epInDataNum[16] ;


    uint8_t* RxEP_buffer;
    uint8_t MaxPacketSize;

    amhw_zmf159_usb_bdt_t *pUSB_OTG_BDT;

    am_device_prop *pProperty;

  am_endpoint_info Ctrl_Info;
}zmf159_device_t;

/* Exported constants --------------------------------------------------------*/
#define Type_Recipient (zmf159_handle->USBbmRequestType & (REQUEST_TYPE | RECIPIENT))


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint8_t Setup0_Process(void);
uint8_t Post0_Process(void);
uint8_t Out0_Process(void);
uint8_t In0_Process(void);

RESULT Standard_SetEndPointFeature(void);
RESULT Standard_SetDeviceFeature(void);

uint8_t *Standard_GetConfiguration(uint16_t Length);
RESULT Standard_SetConfiguration(void);
uint8_t *Standard_GetInterface(uint16_t Length);
RESULT Standard_SetInterface(void);
uint8_t *Standard_GetDescriptorData(uint16_t Length, PONE_DESCRIPTOR pDesc);

uint8_t *Standard_GetStatus(uint16_t Length);
RESULT Standard_ClearFeature(void);
void SetDeviceAddress(uint8_t);
void NOP_Process(void);

extern am_device_prop am_device_property;
extern zmf159_device_t zmf159_dev;



#endif /* __USB_CORE_H */

