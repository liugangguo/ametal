/*******************************************************************************
*                                 AMetal
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2018 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/

/**
 * \file
 * \brief  Xmodem协议 应用接口文件
 *
 * \internal
 * \par Modification History
 * - 1.00 18-8-31 , xgg, first implementation.
 * \endinternal
 */
#ifndef __AM_XMODEM_H
#define __AM_XMODEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_uart_rngbuf.h"
#include "am_softimer.h"

/**
 * @addtogroup am_if_am_xmodem
 * @copydoc am_xmodem.h
 * @{
 */

#define AM_XMODEM_1K_MODE     0    /**< \brief 数据段是1K字节的工作模式*/
#define AM_XMODEM_128_MODE    1    /**< \brief 数据段是128字节的工作模式*/

#define AM_XMODEM_CRC_MODE    0    /**< \brief 采用CRC校验 */
#define AM_XMODEM_SUM_MODE    1    /**< \brief 采用累积和校验 */

#define AM_DATA_ERR           5    /**< \brief 接受到的数据错误 */
#define AM_DATA_CAN           15   /**< \brief 发送方取消发送*/
#define AM_DATA_SUC           20   /**< \brief 文件接收成功 */

#define AM_XMODEM_REC         3    /**< \brief Xmodem接收模式 */
#define AM_XMODEM_TRA         4    /**< \brief Xmodem发送模式 */


#define AM_XMODEM_SOH             0x01 /**< \brief 数据位为128字节工作模式传输的起始位*/
#define AM_XMODEM_STX             0x02 /**< \brief 数据位为1K字节工作模式传输的起始位*/
#define AM_XMODEM_EOT             0x04 /**< \brief 文件传输完毕的结束信号 */
#define AM_XMODEM_ACK             0x06 /**< \brief 接收方的确认信号，表示一帧数据接收完毕 */
#define AM_XMODEM_NAK             0x15 /**< \brief 第一次使用是决定工作模式，后续使用为重复发送 */
#define AM_XMODEM_CAN             0x18 /**< \brief 紧急取消传输 */
#define AM_XMODEM_CTRLZ           0x1A /**< \brief 最后一帧数据不足时用此填充 */
#define AM_XMODEM_1k              'C'  /**< \brief 定义Xmodem状态字符*/

#define AM_XMODEM_NAK_TIME              0x40 /**< \brief 已达到最大重发次数 */
#define AM_XMODEM_MOU_SUC               0x41 /**< \brief 文件发送完成 */

/**
 * \breif 用户接收回调函数
 * \param[in] p_arg    用户决定传入回调函数的参数，若用户需在回调函数中
 *                     使用Xmodem句柄，可将句柄传入此参数。
 * \param[in] p_frames Xmodem接收到的一帧数据保存的地址，用户可直接
 *                     使用该地址获取接收到的一帧数据
 * \param[in] result   先判断result值得正负，若大于0则这一帧数据接收
 *                     成功，result保存的是接收到的字节数，若result
 *                     值为负，则接收失败，可根据reslut的值判断是以下
 *                     那种错误。
 *                     -AM_ETIME:    这一帧数据超时未接收到
 *                     -AM_EBADMSG:  未超时但重发五次后数据仍然错误
 *                     -AM_DATA_CAN: 发送方紧急取消发送导致传输结束
 */
typedef void (*am_xmodem_user_rx_t) (void    *p_arg,
                                     void    *frames,
                                     int      result);

/**
 * \brief 用户发送回调函数
 *
 * \param[in] p_arg  用户需要传入的参数,由自己定义
 * \param[in] event  回调传回的事件，用户可根据事件来自主进行下一步操作
 *                   当event == AM_XMODEM_NAK时,Xmodem工作在128字节工作模式；
 *                   当event == AM_XMODEM_1K时,Xmodem工作在1K字节工作模式；
 *                   当event == AM_XMODEM_NAK_TIME时,重发次数达到规定值(内部已取消传输);
 *                   当event == AM_XMODEM_MOU_SUC时,文件传输完毕;
 *                   当event == AM_XMODEM_CAN时,表明接收方取消了传输;
 *                   当event == AM_XMODEM_ACK时，一帧数据发送完毕;
 *                   当event == -AM_ETIME时,接收方接收到一帧数据后未在规定的时间内回应;
 */
typedef void (*am_xmodem_user_tx_t) (void *p_arg, int event);

/** \brief xmodem协议接收设备实例 */
typedef struct am_xmodem_rec_dev_info {
    char          *frames_info;                 /**< \brief 保存Xmodem一帧信息的数组指针 */
    uint8_t        nak_max_times;               /**< \brief 重发最大次数 */
    uint32_t       frames_bytes;                /**< \brief 一帧数据的字节数 */
    uint32_t       data_mode;                   /**< \brief 工作模式  */
    uint32_t       parity_mode;                 /**< \brief 校验模式 */
    uint32_t       rx_timeout;                  /**< \brief 接收超时时间 */
} am_xmodem_rec_dev_info_t;


/** \brief Xmodem协议发送设备实例*/
typedef struct am_xmodem_tx_dev_info {
    uint32_t   tx_timeout;                       /**< \brief 发送超时时间*/
    uint8_t    nak_times_max;                    /**< \brief 允许最大的重发次数*/
} am_xmodem_tx_dev_info_t;

/**
 * \brief xmodem接收设备结构体
 */
typedef struct am_xmodem_rec_dev {
    int                             rx_bytes;       /**< \brief 当前接收到的字节数 */
    void                           *p_arg;          /**< \brief 用户回调函数类型 */
    void                           *state_handle;   /**< \brief 状态机函数句柄*/
    char                            fra_sum_parity; /**< \brief 保存累积和校验位 */
    uint8_t                         state_rx_char;  /**< \brief 状态标志位 */
    uint8_t                         nak_state;      /**< \brief 当前重发状态 */
    uint16_t                        fra_crc_pry;    /**< \brief 保存CRC校验码 */
    uint32_t                        frames_num;     /**< \brief 当前这一帧数据的序列号 */
    uint32_t                        tx_bytes;       /**< \brief 当前一帧已发送多少 */
    am_softimer_t                   softimer;       /**< \brief 接收超时定时器 */
    am_uart_handle_t                uart_handle;    /**< \brief 串口句柄 */
    am_xmodem_user_rx_t             pfn_rx_callback;/**< \brief 注册用户接受回调函数 */
    const am_xmodem_rec_dev_info_t *p_rec_devinfo;  /**< \brief 接收设备信息结构体指针 */
} am_xmodem_rec_dev_t;

/** \brief xmodem标准服务操作句柄类型定义 */
typedef am_xmodem_rec_dev_t *am_xmodem_rec_handle_t;

typedef struct am_xmodem_tx_dev {
    void                          *p_arg;          /**< \brief 用户回调函数类型 */
    void                          *state_handle;   /**< \brief 状态机函数句柄*/
    char                          *p_tx_arg;       /**< \brief 文件指针 */
    char                           fra_sum_parity; /**< \brief 保存累积和校验位 */
    uint8_t                        nake_state;     /**< \brief 当前重发状态 */
    uint8_t                        state_flag;     /**< \brief 用于分辨接收模式字符*/
    uint8_t                        state_rx_char;  /**< \brief 状态标志位 */
    int16_t                        fra_crc_pry;    /**< \brief 保存CRC校验码 */
    uint32_t                       frames_num;     /**< \brief 当前这一帧数据的序列号 */
    uint32_t                       tx_bytes;       /**< \brief 当前一帧已发送多少 */
    uint32_t                       frame_tx_bytes; /**< \brief 发送的一帧数据大小 */
    uint32_t                       doc_bytes;      /**< \brief 文件大小 */
    am_softimer_t                  softimer;       /**< \brief 接收超时定时器 */
    const am_xmodem_tx_dev_info_t *p_tra_devinfo;  /**< \brief 发送设备信息结构体指针*/
    am_xmodem_user_tx_t            pfn_tx_callback;/**< \brief 注册用户发送回调函数 */
    am_uart_handle_t               uart_handle;    /**< \brief 串口句柄 */
}am_xmodem_tx_dev_t;

typedef am_xmodem_tx_dev_t *am_xmodem_tx_handle_t;


/**
 * \brief 设备初始化函数
 *
 * \param[in] p_dev       xmodem设备句柄
 * \param[in] p_decinfo   设备信息结构体
 * \param[in] uart_handle 串口句柄
 *
 * \return Xmodem操作句柄
 */
am_xmodem_rec_handle_t  am_xmodem_rec_init (
    am_xmodem_rec_dev_t            *p_dev,
    const am_xmodem_rec_dev_info_t *p_devinfo,
    am_uart_handle_t                uart_handle);

/**
 * \brief xmodem接收回调函数注册
 *
 * \param[in] p_dev      xmodem设备句柄
 *            pfn_rec_cb 用户回调函数
 *            p_arg      用户传入的参数
 *
 * \retval AM_TRUE  执行成功
 *         AM_FALSE 执行失败
 */
am_bool_t am_xmodem_rec_cb_reg(am_xmodem_rec_dev_t  *p_dev,
                               am_xmodem_user_rx_t   pfn_rec_cb,
                               void                 *p_arg);

/**
 * \brief 开始接受函数
 *
 * \param[in] p_dev xmodem设备句柄
 *
 * \retval AM_TRUE  执行成功
 *         AM_FALSE 执行失败
 */
am_bool_t am_xmodem_rec_start (am_xmodem_rec_dev_t *p_dev);
/**
 * \brief 继续接收函数
 *
 * \param[in] p_dev xmodem设备句柄
 *
 * \retval AM_TRUE    执行成功
 *         -AM_EINVAL 参数错误
 */
am_err_t am_xmodem_rec_ack_set (am_xmodem_rec_dev_t   *p_dev);
/**
 * \brief 取消传输函数
 *
 * \param[in] p_dev xmodem设备句柄
 *
 * \retval AM_TRUE    执行成功
 *         -AM_EINVAL 参数错误
 */
am_err_t am_xmodem_rec_can_set (am_xmodem_rec_dev_t  *p_dev);

/*******************************************************************************/
/**
 * \brief 发送设备初始化函数
 *
 * \param[in] p_dev         Xmodem发送设备
 * \param[in] p_tra_devinfo Xmodem发送设备信息结构体
 * \param[in] uart_handle   串口句柄
 *
 * \return Xmodem发送句柄
 *
 */
am_xmodem_tx_handle_t  am_xmodem_tx_init (
                              am_xmodem_tx_dev_t            *p_dev,
                              const am_xmodem_tx_dev_info_t *p_tra_devinfo,
                              am_uart_handle_t               uart_handle);

/**
 * \brief 开始发送函数
 *
 * \param[in] p_dev     Xmodem发送设备
 * \param[in] p_doc     用户需要发送的数组的指针
 * \param[in] pack_size 需要发送的数组长度，若回调函数传入的事件为AM_XMODEM_NAK,则pack_size
 *                      传入的值为128,若回调函数传入的事件为AM_XMODEM_1K,则pack_size传入的
 *                      值为1024，如果文件最后一帧数据不满足128或者1024则pack_size的值用户可以
 *                      自己定义，但必须为文件剩下的字节数。
 *
 * \retval AM_TRUE    执行成功
 *         -AM_EINVAL 句柄为空，参数错误
 */
am_err_t am_xmodem_tx_pack (am_xmodem_tx_dev_t *p_dev,
                            char               *p_doc,
                            uint32_t            pack_size);

/**
 * \brief xmodem发送回调函数注册
 *
 * \param[in] p_dev      Xmodem发送设备
 * \param[in] pfn_tx_cb  用户回调函数指针
 * \param[in] p_arg      用户传入设备参数
 *
 * \retval AM_TRUE    执行成功
 *         -AM_EINVAL 句柄为空，参数错误
 */
am_err_t am_xmodem_tx_cb_reg (am_xmodem_tx_dev_t  *p_dev,
                              am_xmodem_user_tx_t  pfn_tx_cb,
                              void                *p_arg);

/**
 * \brief 文件发送结束函数
 *
 * \param[in] p_dev Xmodem发送设备
 *
 * \retval AM_TRUE    执行成功
 *         -AM_EINVAL 参数错误
 */
am_err_t am_xmodem_tx_over (am_xmodem_tx_dev_t *p_dev);

/**
 * \brief 用户取消发送函数
 *
 * \param[in] p_dev Xmodem发送设备
 *
 * \retval AM_TRUE    执行成功
 *         -AM_EINVAL 参数错误
 */
am_err_t am_xmodem_tx_can_set (am_xmodem_tx_dev_t *p_dev);
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_XMODEM_H */

/* end of file */
