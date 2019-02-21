/******************** (C) COPYRIGHT 2018 MindMotion ********************
* File Name          : usb_endp.c
* Version            : V1.0.0
* Date               : 2018/08/21
* Description        : Endpoint routines
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
#include "../inc/usb_desc.h"
#include "../../usb_lib/inc/usb_mem.h"
#include "../inc/usb_istr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t buffer_out[VIRTUAL_COM_PORT_DATA_SIZE];
uint8_t buffer_in[VIRTUAL_COM_PORT_DATA_SIZE];

uint8_t status_UsbUart = 0;
uint8_t len_UsbToUart = 0;
uint8_t len_UartToUsb = 0;
__IO uint32_t count_out = 0;
uint32_t count_in = 0;
uint8_t empty_flag = 0;
extern uint8_t rxUsbBufOdd[16] ;
extern amhw_zmf159_usb_bdt_t *pUSB_OTG_BDT;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : EP3_IN_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP3_OUT_Callback(void)
{
  count_out = (pUSB_OTG_BDT+ENDP3)->rx_buf[rxUsbBufOdd[ENDP3]].format>>16;
  count_out &= 0x1FF;
  PMAToUserBufferCopy(buffer_out, ENDP3, count_out);
  status_UsbUart |= 0x1<<1;
  //USB数据接收
}

/*******************************************************************************
* Function Name  : EP1_IN_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP1_IN_Callback(void)
{
//可设置USB发送完成标志
}

/******************* (C) COPYRIGHT 2018 MindMotion *****END OF FILE****/

