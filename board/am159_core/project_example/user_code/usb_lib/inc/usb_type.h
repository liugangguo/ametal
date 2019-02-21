/******************** (C) COPYRIGHT 2018 MindMotion ********************
* File Name          : usb_type.h
* Version            : V1.0.0
* Date               : 2018/08/21
* Description        : Type definitions used by the USB Library
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, MindMotion SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_TYPE_H
#define __USB_TYPE_H

/* Includes ------------------------------------------------------------------*/
#include "ametal.h"
#include "zmf159_periph_map.h"
#include "../../usb_app/inc/usb_conf.h"
#ifndef NULL
#define NULL ((void *)0)
#endif
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* External variables --------------------------------------------------------*/

///**
//* @brief USB_OTG_FS
//*/
//typedef struct
//{
//  __IO uint32_t PER_ID;       //0x00
//  __IO uint32_t ID_COMP;
//  __IO uint32_t REV;
//  __IO uint32_t ADD_INFO;
//  __IO uint32_t OTG_INT_STAT; //0x10
//  __IO uint32_t OTG_INT_EN;   //0x14
//  __IO uint32_t OTG_STATUS;   //0x18
//  __IO uint32_t OTG_CTRL;     //0x1c
//  __IO uint32_t RESERVED1;    //0x20
//  __IO uint32_t RESERVED2;    //0x24
//  __IO uint32_t RESERVED3;    //0x28
//  __IO uint32_t RESERVED4;    //0x2c
//  __IO uint32_t RESERVED5;    //0x30
//  __IO uint32_t RESERVED6;    //0x34
//  __IO uint32_t RESERVED7;    //0x38
//  __IO uint32_t RESERVED8;    //0x3c
//  __IO uint32_t RESERVED9;    //0x40
//  __IO uint32_t RESERVED10;    //0x44
//  __IO uint32_t RESERVED11;   //0x48
//  __IO uint32_t RESERVED12;   //0x4c
//  __IO uint32_t RESERVED13;   //0x50
//  __IO uint32_t RESERVED14;   //0x54
//  __IO uint32_t RESERVED15;   //0x58
//  __IO uint32_t RESERVED16;   //0x5c
//  __IO uint32_t RESERVED17;   //0x60
//  __IO uint32_t RESERVED18;   //0x64
//  __IO uint32_t RESERVED19;   //0x68
//  __IO uint32_t RESERVED20;   //0x6c
//  __IO uint32_t RESERVED21;   //0x70
//  __IO uint32_t RESERVED22;   //0x74
//  __IO uint32_t RESERVED23;   //0x78
//  __IO uint32_t RESERVED24;   //0x7c
//  __IO uint32_t INT_STAT;     //0x80
//  __IO uint32_t INT_ENB;
//  __IO uint32_t ERR_STAT;
//  __IO uint32_t ERR_ENB;
//  __IO uint32_t STAT;         //0x90
//  __IO uint32_t CTL;
//  __IO uint32_t ADDR;
//  __IO uint32_t BDT_PAGE_01;
//  __IO uint32_t FRM_NUML;     //0xa0
//  __IO uint32_t FRM_NUMH;
//  __IO uint32_t TOKEN;
//  __IO uint32_t SOF_THLD;
//  __IO uint32_t BDT_PAGE_02;  //0xb0
//  __IO uint32_t BDT_PAGE_03;  //0xb4
//  __IO uint32_t RESERVED25;   //0xb8
//  __IO uint32_t RESERVED26;   //0xbc
//  __IO uint32_t EP_CTL[16];   //0xc0
////  __IO uint32_t EP_CTL0;      //0xc0
////  __IO uint32_t EP_CTL1;      //0xc4
////  __IO uint32_t EP_CTL2;      //0xc8
////  __IO uint32_t EP_CTL3;      //0xcc
////  __IO uint32_t EP_CTL4;      //0xd0
////  __IO uint32_t EP_CTL5;      //0xd4
////  __IO uint32_t EP_CTL6;      //0xd8
////  __IO uint32_t EP_CTL7;      //0xdc
////  __IO uint32_t EP_CTL8;      //0xe0
////  __IO uint32_t EP_CTL9;      //0xe4
////  __IO uint32_t EP_CTL10;     //0xe8
////  __IO uint32_t EP_CTL11;     //0xec
////  __IO uint32_t EP_CTL12;     //0xf0
////  __IO uint32_t EP_CTL13;     //0xf4
////  __IO uint32_t EP_CTL14;     //0xf8
////  __IO uint32_t EP_CTL15;     //0xfc
//
//} USB_OTG_FS_TypeDef;
//
//typedef struct
//{
//    __IO uint32_t FORMAT;
//    __IO uint32_t ADRESS;
//} BDT_DATA_TypeDef;
//
//typedef struct
//{
//    BDT_DATA_TypeDef RX_BUF[2];
//    BDT_DATA_TypeDef TX_BUF[2];
//} USB_OTG_BDT_TypeDef;
//
//#define USB_OTG_FS          ((USB_OTG_FS_TypeDef *) ZMF159_USB_BASE)

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

#endif /* __USB_TYPE_H */

/******************* (C) COPYRIGHT 2018 MindMotion *****END OF FILE****/
