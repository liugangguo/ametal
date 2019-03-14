/******************** (C) COPYRIGHT 2018 MindMotion ********************
* File Name          : usb_istr.c 
* Version            : V1.0.0
* Date               : 2018/08/21
* Description        : ISTR events interrupt service routines
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
#include "../inc/usb_prop.h"
#include "../inc/usb_istr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint16_t wIstr;  /* ISTR register last read value */
__IO uint8_t bIntPackSOF = 0;  /* SOFs received between 2 consecutive packets */

void (*pEpInt_IN[7])(void) =
  {
    EP1_IN_Callback,
    EP2_IN_Callback,
    EP3_IN_Callback,
    EP4_IN_Callback,
    EP5_IN_Callback,
    EP6_IN_Callback,
    EP7_IN_Callback,
  };

void (*pEpInt_OUT[7])(void) =
  {
    EP1_OUT_Callback,
    EP2_OUT_Callback,
    EP3_OUT_Callback,
    EP4_OUT_Callback,
    EP5_OUT_Callback,
    EP6_OUT_Callback,
    EP7_OUT_Callback,
  };


/*******************************************************************************
* Function Name  : USB_Istr.
* Description    : ISTR events interrupt service routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USB_Istr(void *p_arg)
{
//  wIstr = _GetUSB_INT_STA();
    wIstr = amhw_zmf159_usb_int_get(ZMF159_USB);
  if(wIstr&OTG_FS_INT_STAT_RST)
  {
	  am_kprintf("reset\r\n");
//    _ClrUSB_INT_STA(OTG_FS_INT_STAT_RST) ;
      amhw_zmf159_usb_int_clear(ZMF159_USB, OTG_FS_INT_STAT_RST);
    am_device_property.Reset();
    
  }

  if(wIstr/*&USB_INT_STATE_SOFF*/)
  {

  }

  if(wIstr&OTG_FS_INT_STAT_DNE)
  {
	  am_kprintf("token\r\n");
    CTR_LP();   //在子程序中清除中断标志
  }
} /* USB_Istr */

/******************* (C) COPYRIGHT 2018 MindMotion *****END OF FILE****/
