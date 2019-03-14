/******************** (C) COPYRIGHT 2018 MindMotion ********************
* File Name          : usb_mem.c
* Version            : V1.0.0
* Date               : 2018/08/21
* Description        : Utility functions for memory transfers to/from PMA
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, MindMotion SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "../inc/usb_lib.h"

/*******************************************************************************
* Function Name  : UserToPMABufferCopy
* Description    : Copy a buffer from user memory area to packet memory area (PMA)
* Input          : - pbUsrBuf: pointer to user memory area.
*                  - wPMABufAddr: address into PMA.
*                  - wNBytes: no. of bytes to be copied.
* Output         : None.
* Return         : None	.
*******************************************************************************/
void UserToPMABufferCopy(uint8_t *pbUsrBuf, uint16_t EPNum, uint16_t wNBytes)
{
    uint32_t i;
    uint8_t *pBuf;
    amhw_zmf159_usb_bdt_t *pUSB_OTG_BDT = zmf159_handle->pUSB_OTG_BDT;

    pBuf = (uint8_t*)((pUSB_OTG_BDT+EPNum)->tx_buf[zmf159_handle->txUsbBufOdd[EPNum]].adress) ;
  
    (pUSB_OTG_BDT+EPNum)->tx_buf[zmf159_handle->txUsbBufOdd[EPNum]].format &= 0x00ff00;

    for (i = 0;i < wNBytes;  i++)
    {
        pBuf[i] = *pbUsrBuf;
        pbUsrBuf++;
    }   
    
    (pUSB_OTG_BDT+EPNum)->tx_buf[zmf159_handle->txUsbBufOdd[EPNum]].format |= (wNBytes<<16)|(zmf159_handle->epInDataNum[EPNum]<<6)/**/;
    zmf159_handle->epInDataNum[EPNum] = !zmf159_handle->epInDataNum[EPNum];
    (pUSB_OTG_BDT+EPNum)->tx_buf[zmf159_handle->txUsbBufOdd[EPNum]].format |= 1<<7;
    zmf159_handle->txUsbBufOdd[EPNum] = !zmf159_handle->txUsbBufOdd[EPNum];

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
void PMAToUserBufferCopy(uint8_t *pbUsrBuf, uint16_t EPNum, uint16_t wNBytes)
{
  uint32_t i;
  uint8_t *pBuf;
  amhw_zmf159_usb_bdt_t *pUSB_OTG_BDT = zmf159_handle->pUSB_OTG_BDT;

  pBuf = (uint8_t*)((pUSB_OTG_BDT+EPNum)->rx_buf[zmf159_handle->rxUsbBufOdd[EPNum]].adress) ;

  for (i = 0;i < wNBytes;  i++)
  {
      *pbUsrBuf = pBuf[i];
      pbUsrBuf++;
  }   



  (pUSB_OTG_BDT+EPNum)->rx_buf[zmf159_handle->rxUsbBufOdd[EPNum]].format &= 0x00ff00;//清除计数,清除stall
  (pUSB_OTG_BDT+EPNum)->rx_buf[zmf159_handle->rxUsbBufOdd[EPNum]].format |= (64<<16);//设置最大接收字节
  (pUSB_OTG_BDT+EPNum)->rx_buf[zmf159_handle->rxUsbBufOdd[EPNum]].format |= 1<<7;
}

/******************* (C) COPYRIGHT 2018 MindMotion *****END OF FILE****/
