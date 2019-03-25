/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      ametal.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief USBD keyboard
 *
 * \internal
 * \par Modification history
 * - 1.00 19-02-19  adw, first implementation.
 * \endinternal
 */

#ifndef __AM_USBD_KEYBOARD_H
#define __AM_USBD_KEYBOARD_H

#include "am_usb.h"
#include "am_usb_dci.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/** \brief 打印机类设备代码标识  */
#define AM_USBD_CONFIG_KEYBOARD_CLASS_CODE             (0x03U)

/** \brief USB keyboard 设备子类码*/
#define AM_USBD_KEYBOARD_SUBCLASS                      (0x01U)

/** \brief usb keyboard协议码*/
#define AM_USBD_KEYBOARD_PROTOCOL                      (0x01U)

/** \brief usb keyboard specific class codes */
#define AM_USBD_KEYBOARD_REPORT_GET                    (0x01U)
#define AM_USBD_KEYBOARD_IDLE_GET                      (0x02U)
#define AM_USBD_KEYBOARD_PROTOCOL_GET                  (0x03U)
#define AM_USBD_KEYBOARD_REPORT_SET                    (0x09U)
#define AM_USBD_KEYBOARD_IDLE_SET                      (0x0AU)
#define AM_USBD_KEYBOARD_PROTOCOL_SET                  (0x0BU)


/*Key Code,键盘键值*/
#define AM_USBD_KEY_ERRORROLLOVER                       0x01U
#define AM_USBD_KEY_POSTFAIL                            0x02U
#define AM_USBD_KEY_ERRORUNDEFINED                      0x03U
#define AM_USBD_KEY_A                                   0x04U
#define AM_USBD_KEY_B                                   0x05U
#define AM_USBD_KEY_C                                   0x06U
#define AM_USBD_KEY_D                                   0x07U
#define AM_USBD_KEY_E                                   0x08U
#define AM_USBD_KEY_F                                   0x09U
#define AM_USBD_KEY_G                                   0x0AU
#define AM_USBD_KEY_H                                   0x0BU
#define AM_USBD_KEY_I                                   0x0CU
#define AM_USBD_KEY_J                                   0x0DU
#define AM_USBD_KEY_K                                   0x0EU
#define AM_USBD_KEY_L                                   0x0FU
#define AM_USBD_KEY_M                                   0x10U
#define AM_USBD_KEY_N                                   0x11U
#define AM_USBD_KEY_O                                   0x12U
#define AM_USBD_KEY_P                                   0x13U
#define AM_USBD_KEY_Q                                   0x14U
#define AM_USBD_KEY_R                                   0x15U
#define AM_USBD_KEY_S                                   0x16U
#define AM_USBD_KEY_T                                   0x17U
#define AM_USBD_KEY_U                                   0x18U
#define AM_USBD_KEY_V                                   0x19U
#define AM_USBD_KEY_W                                   0x1AU
#define AM_USBD_KEY_X                                   0x1BU
#define AM_USBD_KEY_Y                                   0x1CU
#define AM_USBD_KEY_Z                                   0x1DU
#define AM_USBD_KEY_1_EXCLAMATION_MARK                  0x1EU
#define AM_USBD_KEY_2_AT                                0x1FU
#define AM_USBD_KEY_3_NUMBER_SIGN                       0x20U
#define AM_USBD_KEY_4_DOLLAR                            0x21U
#define AM_USBD_KEY_5_PERCENT                           0x22U
#define AM_USBD_KEY_6_CARET                             0x23U
#define AM_USBD_KEY_7_AMPERSAND                         0x24U
#define AM_USBD_KEY_8_ASTERISK                          0x25U
#define AM_USBD_KEY_9_OPARENTHESIS                      0x26U
#define AM_USBD_KEY_0_CPARENTHESIS                      0x27U
#define AM_USBD_KEY_ENTER                               0x28U
#define AM_USBD_KEY_ESCAPE                              0x29U
#define AM_USBD_KEY_BACKSPACE                           0x2AU
#define AM_USBD_KEY_TAB                                 0x2BU
#define AM_USBD_KEY_SPACEBAR                            0x2CU
#define AM_USBD_KEY_MINUS_UNDERSCORE                    0x2DU
#define AM_USBD_KEY_EQUAL_PLUS                          0x2EU
#define AM_USBD_KEY_OBRACKET_AND_OBRACE                 0x2FU
#define AM_USBD_KEY_CBRACKET_AND_CBRACE                 0x30U
#define AM_USBD_KEY_BACKSLASH_VERTICAL_BAR              0x31U
#define AM_USBD_KEY_NONUS_NUMBER_SIGN_TILDE             0x32U
#define AM_USBD_KEY_SEMICOLON_COLON                     0x33U
#define AM_USBD_KEY_SINGLE_AND_DOUBLE_QUOTE             0x34U
#define AM_USBD_KEY_GRAVE_ACCENT_AND_TILDE              0x35U
#define AM_USBD_KEY_COMMA_AND_LESS                      0x36U
#define AM_USBD_KEY_DOT_GREATER                         0x37U
#define AM_USBD_KEY_SLASH_QUESTION                      0x38U
#define AM_USBD_KEY_CAPS_LOCK                           0x39U
#define AM_USBD_KEY_F1                                  0x3AU
#define AM_USBD_KEY_F2                                  0x3BU
#define AM_USBD_KEY_F3                                  0x3CU
#define AM_USBD_KEY_F4                                  0x3DU
#define AM_USBD_KEY_F5                                  0x3EU
#define AM_USBD_KEY_F6                                  0x3FU
#define AM_USBD_KEY_F7                                  0x40U
#define AM_USBD_KEY_F8                                  0x41U
#define AM_USBD_KEY_F9                                  0x42U
#define AM_USBD_KEY_F10                                 0x43U
#define AM_USBD_KEY_F11                                 0x44U
#define AM_USBD_KEY_F12                                 0x45U
#define AM_USBD_KEY_PRINTSCREEN                         0x46U
#define AM_USBD_KEY_SCROLL_LOCK                         0x47U
#define AM_USBD_KEY_PAUSE                               0x48U
#define AM_USBD_KEY_INSERT                              0x49U
#define AM_USBD_KEY_HOME                                0x4AU
#define AM_USBD_KEY_PAGEUP                              0x4BU
#define AM_USBD_KEY_DELETE                              0x4CU
#define AM_USBD_KEY_END1                                0x4DU
#define AM_USBD_KEY_PAGEDOWN                            0x4EU
#define AM_USBD_KEY_RIGHTARROW                          0x4FU
#define AM_USBD_KEY_LEFTARROW                           0x50U
#define AM_USBD_KEY_DOWNARROW                           0x51U
#define AM_USBD_KEY_UPARROW                             0x52U
#define AM_USBD_KEY_KEYPAD_NUM_LOCK_AND_CLEAR           0x53U
#define AM_USBD_KEY_KEYPAD_SLASH                        0x54U
#define AM_USBD_KEY_KEYPAD_ASTERIKS                     0x55U
#define AM_USBD_KEY_KEYPAD_MINUS                        0x56U
#define AM_USBD_KEY_KEYPAD_PLUS                         0x57U
#define AM_USBD_KEY_KEYPAD_ENTER                        0x58U
#define AM_USBD_KEY_KEYPAD_1_END                        0x59U
#define AM_USBD_KEY_KEYPAD_2_DOWN_ARROW                 0x5AU
#define AM_USBD_KEY_KEYPAD_3_PAGEDN                     0x5BU
#define AM_USBD_KEY_KEYPAD_4_LEFT_ARROW                 0x5CU
#define AM_USBD_KEY_KEYPAD_5                            0x5DU
#define AM_USBD_KEY_KEYPAD_6_RIGHT_ARROW                0x5EU
#define AM_USBD_KEY_KEYPAD_7_HOME                       0x5FU
#define AM_USBD_KEY_KEYPAD_8_UP_ARROW                   0x60U
#define AM_USBD_KEY_KEYPAD_9_PAGEUP                     0x61U
#define AM_USBD_KEY_KEYPAD_0_INSERT                     0x62U
#define AM_USBD_KEY_KEYPAD_DECIMAL_SEPARATOR_DELETE     0x63U
#define AM_USBD_KEY_NONUS_BACK_SLASH_VERTICAL_BAR       0x64U
#define AM_USBD_KEY_APPLICATION                         0x65U
#define AM_USBD_KEY_POWER                               0x66U
#define AM_USBD_KEY_KEYPAD_EQUAL                        0x67U
#define AM_USBD_KEY_F13                                 0x68U
#define AM_USBD_KEY_F14                                 0x69U
#define AM_USBD_KEY_F15                                 0x6AU
#define AM_USBD_KEY_F16                                 0x6BU
#define AM_USBD_KEY_F17                                 0x6CU
#define AM_USBD_KEY_F18                                 0x6DU
#define AM_USBD_KEY_F19                                 0x6EU
#define AM_USBD_KEY_F20                                 0x6FU
#define AM_USBD_KEY_F21                                 0x70U
#define AM_USBD_KEY_F22                                 0x71U
#define AM_USBD_KEY_F23                                 0x72U
#define AM_USBD_KEY_F24                                 0x73U
#define AM_USBD_KEY_EXECUTE                             0x74U
#define AM_USBD_KEY_HELP                                0x75U
#define AM_USBD_KEY_MENU                                0x76U
#define AM_USBD_KEY_SELECT                              0x77U
#define AM_USBD_KEY_STOP                                0x78U
#define AM_USBD_KEY_AGAIN                               0x79U
#define AM_USBD_KEY_UNDO                                0x7AU
#define AM_USBD_KEY_CUT                                 0x7BU
#define AM_USBD_KEY_COPY                                0x7CU
#define AM_USBD_KEY_PASTE                               0x7DU
#define AM_USBD_KEY_FIND                                0x7EU
#define AM_USBD_KEY_MUTE                                0x7FU
#define AM_USBD_KEY_VOLUME_UP                           0x80U
#define AM_USBD_KEY_VOLUME_DOWN                         0x81U
#define AM_USBD_KEY_LOCKING_CAPS_LOCK                   0x82U
#define AM_USBD_KEY_LOCKING_NUM_LOCK                    0x83U
#define AM_USBD_KEY_LOCKING_SCROLL_LOCK                 0x84U
#define AM_USBD_KEY_KEYPAD_COMMA                        0x85U
#define AM_USBD_KEY_KEYPAD_EQUAL_SIGN                   0x86U
#define AM_USBD_KEY_INTERNATIONAL1                      0x87U
#define AM_USBD_KEY_INTERNATIONAL2                      0x88U
#define AM_USBD_KEY_INTERNATIONAL3                      0x89U
#define AM_USBD_KEY_INTERNATIONAL4                      0x8AU
#define AM_USBD_KEY_INTERNATIONAL5                      0x8BU
#define AM_USBD_KEY_INTERNATIONAL6                      0x8CU
#define AM_USBD_KEY_INTERNATIONAL7                      0x8DU
#define AM_USBD_KEY_INTERNATIONAL8                      0x8EU
#define AM_USBD_KEY_INTERNATIONAL9                      0x8FU
#define AM_USBD_KEY_LANG1                               0x90U
#define AM_USBD_KEY_LANG2                               0x91U
#define AM_USBD_KEY_LANG3                               0x92U
#define AM_USBD_KEY_LANG4                               0x93U
#define AM_USBD_KEY_LANG5                               0x94U
#define AM_USBD_KEY_LANG6                               0x95U
#define AM_USBD_KEY_LANG7                               0x96U
#define AM_USBD_KEY_LANG8                               0x97U
#define AM_USBD_KEY_LANG9                               0x98U
#define AM_USBD_KEY_ALTERNATE_ERASE                     0x99U
#define AM_USBD_KEY_SYSREQ                              0x9AU
#define AM_USBD_KEY_CANCEL                              0x9BU
#define AM_USBD_KEY_CLEAR                               0x9CU
#define AM_USBD_KEY_PRIOR                               0x9DU
#define AM_USBD_KEY_RETURN                              0x9EU
#define AM_USBD_KEY_SEPARATOR                           0x9FU
#define AM_USBD_KEY_OUT                                 0xA0U
#define AM_USBD_KEY_OPER                                0xA1U
#define AM_USBD_KEY_CLEAR_AGAIN                         0xA2U
#define AM_USBD_KEY_CRSEL                               0xA3U
#define AM_USBD_KEY_EXSEL                               0xA4U
#define AM_USBD_KEY_KEYPAD_00                           0xB0U
#define AM_USBD_KEY_KEYPAD_000                          0xB1U
#define AM_USBD_KEY_THOUSANDS_SEPARATOR                 0xB2U
#define AM_USBD_KEY_DECIMAL_SEPARATOR                   0xB3U
#define AM_USBD_KEY_CURRENCY_UNIT                       0xB4U
#define AM_USBD_KEY_CURRENCY_SUB_UNIT                   0xB5U
#define AM_USBD_KEY_KEYPAD_OPARENTHESIS                 0xB6U
#define AM_USBD_KEY_KEYPAD_CPARENTHESIS                 0xB7U
#define AM_USBD_KEY_KEYPAD_OBRACE                       0xB8U
#define AM_USBD_KEY_KEYPAD_CBRACE                       0xB9U
#define AM_USBD_KEY_KEYPAD_TAB                          0xBAU
#define AM_USBD_KEY_KEYPAD_BACKSPACE                    0xBBU
#define AM_USBD_KEY_KEYPAD_A                            0xBCU
#define AM_USBD_KEY_KEYPAD_B                            0xBDU
#define AM_USBD_KEY_KEYPAD_C                            0xBEU
#define AM_USBD_KEY_KEYPAD_D                            0xBFU
#define AM_USBD_KEY_KEYPAD_E                            0xC0U
#define AM_USBD_KEY_KEYPAD_F                            0xC1U
#define AM_USBD_KEY_KEYPAD_XOR                          0xC2U
#define AM_USBD_KEY_KEYPAD_CARET                        0xC3U
#define AM_USBD_KEY_KEYPAD_PERCENT                      0xC4U
#define AM_USBD_KEY_KEYPAD_LESS                         0xC5U
#define AM_USBD_KEY_KEYPAD_GREATER                      0xC6U
#define AM_USBD_KEY_KEYPAD_AMPERSAND                    0xC7U
#define AM_USBD_KEY_KEYPAD_LOGICAL_AND                  0xC8U
#define AM_USBD_KEY_KEYPAD_VERTICAL_BAR                 0xC9U
#define AM_USBD_KEY_KEYPAD_LOGIACL_OR                   0xCAU
#define AM_USBD_KEY_KEYPAD_COLON                        0xCBU
#define AM_USBD_KEY_KEYPAD_NUMBER_SIGN                  0xCCU
#define AM_USBD_KEY_KEYPAD_SPACE                        0xCDU
#define AM_USBD_KEY_KEYPAD_AT                           0xCEU
#define AM_USBD_KEY_KEYPAD_EXCLAMATION_MARK             0xCFU
#define AM_USBD_KEY_KEYPAD_MEMORY_STORE                 0xD0U
#define AM_USBD_KEY_KEYPAD_MEMORY_RECALL                0xD1U
#define AM_USBD_KEY_KEYPAD_MEMORY_CLEAR                 0xD2U
#define AM_USBD_KEY_KEYPAD_MEMORY_ADD                   0xD3U
#define AM_USBD_KEY_KEYPAD_MEMORY_SUBTRACT              0xD4U
#define AM_USBD_KEY_KEYPAD_MEMORY_MULTIPLY              0xD5U
#define AM_USBD_KEY_KEYPAD_MEMORY_DIVIDE                0xD6U
#define AM_USBD_KEY_KEYPAD_PLUSMINUS                    0xD7U
#define AM_USBD_KEY_KEYPAD_CLEAR                        0xD8U
#define AM_USBD_KEY_KEYPAD_CLEAR_ENTRY                  0xD9U
#define AM_USBD_KEY_KEYPAD_BINARY                       0xDAU
#define AM_USBD_KEY_KEYPAD_OCTAL                        0xDBU
#define AM_USBD_KEY_KEYPAD_DECIMAL                      0xDCU
#define AM_USBD_KEY_KEYPAD_HEXADECIMAL                  0xDDU
#define AM_USBD_KEY_LEFTCONTROL                         0xE0U
#define AM_USBD_KEY_LEFTSHIFT                           0xE1U
#define AM_USBD_KEY_LEFTALT                             0xE2U
#define AM_USBD_KEY_LEFT_GUI                            0xE3U
#define AM_USBD_KEY_RIGHTCONTROL                        0xE4U
#define AM_USBD_KEY_RIGHTSHIFT                          0xE5U
#define AM_USBD_KEY_RIGHTALT                            0xE6U
#define AM_USBD_KEY_RIGHT_GUI                           0xE7U

#define AM_USBD_KEY_MODIFERKEYS_LEFT_CTRL               0x01U
#define AM_USBD_KEY_MODIFERKEYS_LEFT_SHIFT              0x02U
#define AM_USBD_KEY_MODIFERKEYS_LEFT_ALT                0x04U
#define AM_USBD_KEY_MODIFERKEYS_LEFT_GUI                0x08U
#define AM_USBD_KEY_MODIFERKEYS_RIGHT_CTRL              0x10U
#define AM_USBD_KEY_MODIFERKEYS_RIGHT_SHIFT             0x20U
#define AM_USBD_KEY_MODIFERKEYS_RIGHT_ALT               0x40U
#define AM_USBD_KEY_MODIFERKEYS_RIGHT_GUI               0x80U

/*键值返回*/
#define AM_USBD_NUM_LOCK_LIGHT                          0x01U
#define AM_USBD_CAP_LOCK_LIGHT                          0x02U
#define AM_USBD_SCROLL_LOCK_LIGHT                       0x04U
#define AM_USBD_COMPOSE_LIGHT                           0x08U
#define AM_USBD_KANA_LIGHT                              0x10U
/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif


/** \brief 打印机信息结构体 */
typedef struct am_usbd_keyboard_info {
    uint8_t ep_in;
    uint8_t ep_out;
} am_usbd_keyboard_info_t;


/** \brief usb device printer struct */
typedef struct am_usbd_keyboard {
    am_usbd_dev_t                 *p_dev;      /**< \brief 保存usb设备类指针*/
    const am_usbd_keyboard_info_t *p_info;     /**< \brief 打印机设备信息*/
} am_usbd_keyboard_t;

/*USBD keyboard 通用句柄*/
typedef am_usbd_keyboard_t  *am_usbd_keyboard_handle;



/**
 * \brief 初始化USB
 *
 * \param[in] p_dev     : 指向USB设备
 * \param[in] p_info    : 指向USB设备信息
 *
 * \return USB标准服务操作句柄。如果为 NULL，表明初始化失败。
 */
am_usbd_keyboard_handle am_usbd_keyboard_init (am_usbd_keyboard_t            *p_dev,
                                               const am_usbd_keyboard_info_t *p_info,
                                               am_usbd_dev_t                 *p_usbd);


/**
 * \brief USB Device 去初始化
 *
 * \param[in] p_dev : 指向USB设备信息
 */
void am_usbd_keyboard_deinit (am_usbd_keyboard_t *p_dev);

/**
 * \brief 键盘发送函数
 */
am_usb_status_t am_usbd_keyboard_send(am_usbd_keyboard_handle   handle,
                                      uint8_t                  *p_buff,
                                      uint8_t                   len);

am_usb_status_t am_usbd_keyboard_recv_req(am_usbd_keyboard_handle handle,
                                          uint8_t                *p_buff,
                                          uint8_t                 len);
/**
 * \brief USB Device keyboard 厂商请求
 *
 * \param[in] handle : 设备句柄
 * \param[in] pfn_cb : 回调函数
 * \param[in] p_arg  : 回调函数参数
 */
am_usb_status_t am_usbd_keyboard_vendor_request_callback(am_usbd_keyboard_handle handle,
                                                         am_vendor_request_t     pfn_cb,
                                                         void                   *p_arg);

#if defined(__cplusplus)
}
#endif


#endif /* __AM_USBD_KEYBOARD_H */

/* end of file */



