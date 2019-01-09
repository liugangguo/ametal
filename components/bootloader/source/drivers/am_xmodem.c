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
 * \brief  Xmodem协议 驱动
 *
 * \internal
 * \par Modification History
 * - 1.00 18-8-31 , xgg, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_types.h"
#include "am_uart.h"
#include "string.h"
#include "am_errno.h"
#include "am_xmodem.h"
#include "am_softimer.h"
#include "string.h"


#define __AM_XMODEM_DATA_EOT         0x50   /**< \brief 文件最后一帧数据填充完成*/
#define __AM_XMODEM_DOC_EOT          0x51   /**< \brief 文件发送完成 */
#define AM_XMODEM_EOT_ACK            0x52   /**< \brief 文件结束信号已发送并应答*/
/** \brief 定义Xmodem接收状态机函数指针类型 */
typedef am_bool_t (*am_xmodem_rec_pfn_handle)(void *p_arg, char inchar);

/** \brief 定义Xmodem发送状态机函数指针类型 */
typedef am_bool_t (*am_xmodem_tra_pfn_handle)(void *p_arg, char *outchar);


/**
 * \brief 重新接收上一帧函数
 */
am_static_inline
void __xmodem_rx_nak_set (am_xmodem_rec_dev_t  *p_dev)
{
    /* 向发送方发送NAK重发信号*/
    p_dev->p_rec_devinfo->frames_info[0] = AM_XMODEM_NAK;
    p_dev->state_rx_char = 1;
    /* 启动发送*/
    am_uart_tx_startup(p_dev->uart_handle);
    /*启动软件定时器 */
    am_softimer_start(&p_dev->softimer, p_dev->p_rec_devinfo->rx_timeout);
    /* 计算重发次数 */
    ++p_dev->nak_state;
    if (p_dev->nak_state == p_dev->p_rec_devinfo->nak_max_times) {
        /* 要求最大次数的重发完成 */
        p_dev->nak_state = AM_OK;
        p_dev->rx_bytes  = -AM_EBADMSG;
        /* 未能接受到正确的数据，调用用户回调函数通知用户数据错误 */
        p_dev->pfn_rx_callback(p_dev->p_arg,
                            p_dev->p_rec_devinfo->frames_info,
                            p_dev->rx_bytes);
    }
}
/**
 * \brief 发送方紧急取消发送函数
 */
am_static_inline
void __xmodem_rec_can (am_xmodem_rec_dev_t *p_dev, char inchar)
{
    p_dev->rx_bytes = -AM_DATA_CAN;
    /* 回调通知用户 发送方紧急取消传输*/
    p_dev->pfn_rx_callback(p_dev->p_arg,
                        p_dev->p_rec_devinfo->frames_info,
                        p_dev->rx_bytes);
}
/**
 * \brief 生成CRC校验码函数
 *
 * \param[in]  ptr    存放数据的数组的指针
 * \param[in]  count  存放数据的数组的字节数
 *
 * \return crc 校验码
 */
am_static_inline
int16_t __xmodem_check_mode_crc (char  *ptr, int16_t count)
{
    int16_t  crc = 0;
    char i;

    crc = 0;
    while (--count >= 0) {
        crc = crc ^ (((int)*ptr++) << 8); /*每次先与需要计算的数据异或，计算完再指向下一个数据*/
        i = 8;
        do
        {
           if (crc & 0x8000) {            /*判断CRC的第16位是否为0*/
              /* 高位为1则左移一位后异或*/
              crc = (crc << 1) ^ 0x1021;
           }
           else {
              /* 若高位不为1则左移一位再判断下一位是否为1*/
              crc = crc << 1;
           }
         } while (--i);
      }
    /*返回的crc是一个16位数*/
    return (crc);
}
/**
 * \brief 接收方检验判断函数
 */
am_static_inline
int __xmodem_data_check(am_xmodem_rec_dev_t *p_dev)
{
    if (p_dev->p_rec_devinfo->parity_mode == AM_XMODEM_CRC_MODE)
    {
        /* 获取crc校验码*/
        int16_t crc = __xmodem_check_mode_crc(p_dev->p_rec_devinfo->frames_info,
                                              p_dev->p_rec_devinfo->frames_bytes);
        int16_t tcrc = p_dev->fra_crc_pry;
        /* 将自己计算的校验码和传输得到的校验码进行比较*/
        if (crc == tcrc)
            return AM_TRUE;
    }
    else
    {
        int i;
        char cks = 0;
        /* 将数据累加求和*/
        for (i = 0; i < p_dev->p_rec_devinfo->frames_bytes; i++)
        {
            cks += p_dev->p_rec_devinfo->frames_info[i];
        }
        /* 将自行计算的累加和与传输过来的累加和进行比较*/
        if (cks == p_dev->fra_sum_parity)
            return AM_TRUE;
    }
    return AM_FALSE;
}

/**
 * \brief 接收到EOT结束函数
 */
am_static_inline
am_bool_t __xmodem_rec_eot (am_xmodem_rec_dev_t *p_dev, char inchar)
{
    /* 接受到结束字符后回应发送方 */
    p_dev->p_rec_devinfo->frames_info[0] = AM_XMODEM_ACK;
    p_dev->state_rx_char = 1;
    /* 使能中断*/
    am_uart_tx_startup(p_dev->uart_handle);
    p_dev->state_rx_char = 2;
    p_dev->rx_bytes = -AM_DATA_SUC;
    /* 回调通知用户 传输结束*/
    p_dev->pfn_rx_callback(p_dev->p_arg,
                        p_dev->p_rec_devinfo->frames_info,
                        p_dev->rx_bytes);
    return AM_TRUE;
}
/**
 * \brief 数据错误状态函数
 */
am_static_inline
am_bool_t __xmodem_rec_data_err (am_xmodem_rec_dev_t *p_dev, char inchar)
{
    /* 判断错误信息，若发送方紧急取消发送，则回调通知用户*/
    if (inchar == AM_XMODEM_CAN) {
        __xmodem_rec_can(p_dev, inchar);
        return AM_TRUE;
    }
    if (inchar == AM_XMODEM_EOT) {
        __xmodem_rec_eot(p_dev, inchar);
        return AM_TRUE;
    }
    if (inchar == AM_XMODEM_ACK) {
        return AM_TRUE;
    }
    __xmodem_rx_nak_set(p_dev);
    return AM_FALSE;
}

/**
 * \brief SUM校验函数
 */
am_static_inline
am_bool_t __xmodem_rec_sum (am_xmodem_rec_dev_t *p_dev, char inchar)
{
    p_dev->fra_sum_parity = inchar;
    if (AM_TRUE == __xmodem_data_check(p_dev))
       {
          if (p_dev->pfn_rx_callback != NULL) {
              p_dev->pfn_rx_callback(p_dev->p_arg,
                                     p_dev->p_rec_devinfo->frames_info,
                                     p_dev->rx_bytes);
              p_dev->rx_bytes = 0;
              p_dev->frames_num++;
              return AM_TRUE;
          }
       }
    return AM_FALSE;
}
/**
 * \brief CRC校验函数
 */
am_static_inline
am_bool_t __xmodem__rec_crc (am_xmodem_rec_dev_t *p_dev, char inchar)
{
    uint8_t u_inchar = (uint8_t)inchar;
    if (p_dev->rx_bytes == p_dev->p_rec_devinfo->frames_bytes) {
        p_dev->fra_crc_pry |= (u_inchar << 8);
        p_dev->rx_bytes ++;
        return AM_TRUE;
    }
    if (p_dev->rx_bytes == p_dev->p_rec_devinfo->frames_bytes + 1) {
        p_dev->fra_crc_pry |= u_inchar;
        if (AM_TRUE == __xmodem_data_check(p_dev)) {
            p_dev->pfn_rx_callback(p_dev->p_arg,
                                p_dev->p_rec_devinfo->frames_info,
                                p_dev->p_rec_devinfo->frames_bytes);
            p_dev->rx_bytes = 0;
            p_dev->frames_num++;
            p_dev->fra_crc_pry = 0;
            return AM_TRUE;
        }
    }
    return AM_FALSE;
}

/*****************************************************************************/

/**
 * \brief 数据段保存函数
 */
am_static_inline
am_bool_t __xmodem_rec_data_rec (am_xmodem_rec_dev_t *p_dev, char inchar)
{
    if (p_dev->rx_bytes < p_dev->p_rec_devinfo->frames_bytes) {
        p_dev->p_rec_devinfo->frames_info[p_dev->rx_bytes] = inchar;
        p_dev->rx_bytes++;
        return AM_TRUE;
    }
    if (AM_XMODEM_SUM_MODE == p_dev->p_rec_devinfo->parity_mode) {
        __xmodem_rec_sum(p_dev, inchar);
        return AM_TRUE;
    }
    if (AM_XMODEM_CRC_MODE == p_dev->p_rec_devinfo->parity_mode) {
    	__xmodem__rec_crc(p_dev, inchar);
        return AM_TRUE;
    }
    return AM_FALSE;
}
/**
 * \brief 序列号反码判断
 */
am_static_inline
am_bool_t __xmodem_rec_rad (am_xmodem_rec_dev_t *p_dev, char inchar)
{
    if (inchar == ~p_dev->frames_num) {
        /* 更改到下一个接受状态*/
        p_dev->state_handle = (am_xmodem_rec_pfn_handle)__xmodem_rec_data_rec;
        return AM_TRUE;
    }
    return AM_FALSE;
}

/**
 * \brief 序列号接受函数
 */
am_static_inline
am_bool_t __xmodem_rec_pack (am_xmodem_rec_dev_t *p_dev, char inchar)
{
    p_dev->frames_num = inchar;
    p_dev->state_handle = (am_xmodem_rec_pfn_handle)__xmodem_rec_rad;
    return AM_TRUE;
}

/**
 * \brief 状态机开始传输函数
 */
am_bool_t am_xmodem_rec_frames (am_xmodem_rec_dev_t *p_dev, char inchar)
{
    if (inchar == AM_XMODEM_SOH || inchar == AM_XMODEM_STX) {
        p_dev->state_handle = (am_xmodem_rec_pfn_handle)__xmodem_rec_pack;
        return AM_TRUE;
    }
    return AM_FALSE;
}

/*****************************************************************************/

/**
 * \brief 取消发送函数
 */
am_err_t am_xmodem_rec_can_set (am_xmodem_rec_dev_t  *p_dev)
{
   int i = 0;
   if (p_dev == NULL) {
      return -AM_EINVAL;
   }
   /* 取消发送命令，连发三次防止发送方未能接到*/
   for (i = 0; i < 3; i++) {
      p_dev->p_rec_devinfo->frames_info[0] = AM_XMODEM_CAN;
      p_dev->state_rx_char = 1;
      /* 开启发送中断 */
      am_uart_tx_startup(p_dev->uart_handle);
      p_dev->state_rx_char = 2;
   }
   return AM_TRUE;
}

/**
 * \brief 继续接收函数
 */
am_err_t am_xmodem_rec_ack_set (am_xmodem_rec_dev_t *p_dev)
{
    if (p_dev == NULL) {
       return -AM_EINVAL;
    }
    /* 发送ACK确认信号， 响应发送方发送下一帧数据 */
    p_dev->p_rec_devinfo->frames_info[0] = AM_XMODEM_ACK;
    p_dev->state_rx_char = 1;
    /* 开启发送中断 */
    am_uart_tx_startup(p_dev->uart_handle);
    p_dev->state_rx_char = 2;
    p_dev->state_handle = am_xmodem_rec_frames;
    /* 开启软件定时器计算接受时间*/
    am_softimer_start(&p_dev->softimer, p_dev->p_rec_devinfo->rx_timeout);
    return AM_TRUE;
}

/**
 * \brief xmodem接收回调函数注册
 */
am_bool_t am_xmodem_rec_cb_reg (am_xmodem_rec_dev_t        *p_dev,
                               am_xmodem_user_rx_t          pfn_rec_cb,
                               void                        *p_arg)
{
    if (pfn_rec_cb == NULL) {
       return AM_EINVAL;
    }
    p_dev->pfn_rx_callback = pfn_rec_cb;
    p_dev->p_arg        = p_arg;
    return AM_OK;
}

/**
 * \brief 软件定时器回调函数
 *
 * \param[in] p_arg 指向XMODEM 设备结构体的指针
 *
 * \return 无
 */
static void __xmodem_rec_softimer_callback (void *p_arg)
{
    am_xmodem_rec_dev_t *p_dev = (am_xmodem_rec_dev_t *)p_arg;
    /* 关闭软件定时器 */
    am_softimer_stop(&p_dev->softimer);
    /*设立标志位，超时未接收到数据*/
    p_dev->rx_bytes = -AM_ETIME;
    if (p_dev->pfn_rx_callback != NULL) {
        p_dev->pfn_rx_callback(p_dev->p_arg,
                               p_dev->p_rec_devinfo->frames_info,
                               p_dev->rx_bytes);
     }
}

/**
 * \brief 字符获取函数
 */
static int __xmodem_rec_getchar (am_xmodem_rec_dev_t  *p_dev, char *p_data)
{
    /* 接受状态时，只发送数组的第一个字节中的数据 */
    if (p_dev->state_rx_char == 1) {
       *p_data = p_dev->p_rec_devinfo->frames_info[0];
        p_dev->state_rx_char = 0;
        return 1;
    }
    return AM_OK;
}
/**
 * \brief Xmodem获取一个字符发送函数
 */
static int __xmodem_rec_txchar_get (void *p_arg, char *p_outchar)
{
    am_xmodem_rec_dev_t *p_dev = (am_xmodem_rec_dev_t *)p_arg;
    if (__xmodem_rec_getchar(p_dev, p_outchar) != 1) {
        return -AM_EEMPTY;
    }
    return AM_OK;
}

/**
 * \brief Xmodem数据接收函数
 */
am_static_inline
void __xmodem_rx_char (void *p_arg, char inchar)
{
    am_xmodem_rec_dev_t *p_dev = (am_xmodem_rec_dev_t *)p_arg;
    am_softimer_stop (&p_dev->softimer);
    am_xmodem_rec_pfn_handle pfn_handle = (am_xmodem_rec_pfn_handle)p_dev->state_handle;
    if (AM_FALSE == pfn_handle(p_dev, inchar)) {
        __xmodem_rec_data_err(p_dev, inchar);
    }
}

/**
 * \brief Xmodem开始接收函数
 */
am_static_inline
void  __xmodem_rx_startup (am_xmodem_rec_dev_t  *p_dev)
{
    /* 根据工作模式来选择发送给发送方的字符*/
    switch (p_dev->p_rec_devinfo->parity_mode) {
       /* 工作模式为数据位为128字节时，发送字符NAK*/
       case AM_XMODEM_SUM_MODE:
                 p_dev->p_rec_devinfo->frames_info[0] = AM_XMODEM_NAK;
                 break;
       /* 工作模式为数据位为1K字节时，发送字符C*/
       case AM_XMODEM_CRC_MODE:
                 p_dev->p_rec_devinfo->frames_info[0] = 'C';
                 break;
    }
    p_dev->state_rx_char = 1;
    /* 启动发送中断 */
    am_uart_tx_startup(p_dev->uart_handle);
    p_dev->state_rx_char = 0;
    am_softimer_start(&p_dev->softimer, p_dev->p_rec_devinfo->rx_timeout);
}

/**
 * \brief Xmodem文件接收函数
 */
am_bool_t am_xmodem_rec_start (am_xmodem_rec_dev_t *p_dev)
{
    /* 开始接收 */
    if (p_dev != NULL) {
    	__xmodem_rx_startup(p_dev);
        return AM_TRUE;
    }
    return AM_FALSE;
}

/**
 * \brief 接收设备初始化函数
 */
am_xmodem_rec_handle_t  am_xmodem_rec_init (
                                am_xmodem_rec_dev_t        *p_dev,
                                const am_xmodem_rec_dev_info_t *p_rec_devinfo,
                                am_uart_handle_t                uart_handle)
{
    if ((NULL == p_dev) || (NULL == p_rec_devinfo) || (NULL == uart_handle)) {
        return NULL;
    }

    p_dev->p_rec_devinfo = (am_xmodem_rec_dev_info_t *)p_rec_devinfo;
    /* 获取串口句柄 */
    p_dev->uart_handle = uart_handle;
    p_dev->frames_num    = 0;         /**< \brief 序列号初始值为0*/
    p_dev->fra_sum_parity = 0;        /**< \brief 初始化校验位 */
    p_dev->fra_crc_pry = 0;           /**< \brief 初始化CRC校验 */
    p_dev->pfn_rx_callback = NULL;       /**< \brief 初始化回调函数 */
    p_dev->state_rx_char = 0;         /**< \brief 状态位默认为0 */
    p_dev->rx_bytes = 0;              /**< \brief 初始化当前接收字节数 */
    p_dev->nak_state = 1;             /**< \brief 初始化当前重发状态为1 */
    p_dev->tx_bytes = 0;              /**< \brief 初始化发送文件大小*/
    /** 状态机函数句柄*/
    p_dev->state_handle = (am_xmodem_rec_pfn_handle)am_xmodem_rec_frames;
    /* 使能串口中断模式 */
    am_uart_ioctl(p_dev->uart_handle, AM_UART_MODE_SET, (void *)AM_UART_MODE_INT);
    /* 注册发送回调函数 */
    am_uart_callback_set(p_dev->uart_handle,
                         AM_UART_CALLBACK_TXCHAR_GET,
                         __xmodem_rec_txchar_get,
                         (void *)(p_dev));
    /* 注册接收回调函数 */
    am_uart_callback_set(p_dev->uart_handle,
                         AM_UART_CALLBACK_RXCHAR_PUT,
                         __xmodem_rx_char,
                         (void *)(p_dev));

    if (p_rec_devinfo->rx_timeout != 0) {
        if (am_softimer_init(&p_dev->softimer,
                              __xmodem_rec_softimer_callback,
                              p_dev) != AM_OK) {
            return NULL;
        }
    }
    return (am_xmodem_rec_handle_t)(p_dev);
}

/********************************************************************************
Xmodem发送驱动
********************************************************************************/

/**
 * \brief 获取文件发送结束字符
 */
am_static_inline
void __xmodem_tx_eot (am_xmodem_tx_dev_t *p_dev,
                             uint8_t            *outchar)
{
    *outchar = AM_XMODEM_EOT;
}
/**
 * \brief 文件发送结束函数
 */
am_err_t am_xmodem_tx_over (am_xmodem_tx_dev_t *p_dev)
{
    if (NULL == p_dev) {
       return -AM_EINVAL;
    }
    /* 开启获取字符发送标志位*/
    p_dev->state_rx_char = 0;
    /* 开启定时器*/
    am_softimer_start(&p_dev->softimer, p_dev->p_tra_devinfo->tx_timeout);
    /* 切换到文件发送结束状态*/
    p_dev->state_handle = __xmodem_tx_eot;
    /* 开启发送中断 */
    am_uart_tx_startup(p_dev->uart_handle);
    /*关闭字符获取*/
    p_dev->state_rx_char = 2;
    p_dev->state_flag = __AM_XMODEM_DOC_EOT;
    return AM_TRUE;
}

/**
 * \brief 获取取消发送函数字符
 */
am_static_inline
void __xmodem_tx_can_get (void *p_arg, char *outchar)
{
    *outchar = AM_XMODEM_CAN;
}
/**
 * \brief 用户取消发送函数
 */
am_err_t am_xmodem_tx_can_set (am_xmodem_tx_dev_t *p_dev)
{
    int i = 0;
    if (NULL == p_dev) {
        return -AM_EINVAL;
    }
    p_dev->state_rx_char = 0;
    /* 切换到紧急取消发送文件状态，并连续发送三次紧急取消信号*/
    for (i = 0; i < 3; i++) {
        p_dev->state_handle = __xmodem_tx_can_get;
        am_uart_tx_startup(p_dev->uart_handle);
    }
    /* 关闭中断获取发送字符*/
    p_dev->state_rx_char = 2;
    p_dev->state_flag = AM_XMODEM_EOT_ACK;
    return AM_TRUE;
}
/**
 * \brief 字符获取函数
 */
am_static_inline
int __xmodem_tx_getchar (am_xmodem_tx_dev_t  *p_dev, char *p_data)
{
    if (p_dev->state_rx_char == 0) {
        am_xmodem_tra_pfn_handle pfn_handle = (am_xmodem_tra_pfn_handle)p_dev->state_handle;
        pfn_handle(p_dev, p_data);
        return 1;
    }
    return AM_OK;
}
/**
 * \brief Xmodem发送模式获取一个字符发送函数
 */
am_static_inline
int __xmodem_tx_char_get (void *p_arg, char *p_outchar)
{
    am_xmodem_tx_dev_t *p_dev = (am_xmodem_tx_dev_t *)p_arg;
    if (__xmodem_tx_getchar(p_dev, p_outchar) != 1) {
        return -AM_EEMPTY;
    }
    return AM_OK;
}
/**
 * \brief xmodem发送回调函数注册
 */
am_err_t am_xmodem_tx_cb_reg (am_xmodem_tx_dev_t       *p_dev,
                              am_xmodem_user_tx_t       pfn_tx_cb,
                              void                     *p_arg)
{
    if (pfn_tx_cb == NULL) {
       return AM_EINVAL;
    }
    p_dev->pfn_tx_callback = pfn_tx_cb;
    p_dev->p_arg        = p_arg;
    return AM_TRUE;
}

/**
 * \brief 发送校验码函数
 */
am_static_inline
void __xmodem_tx_frames_parity (am_xmodem_tx_dev_t *p_dev,
                                char               *outchar)
{
    int16_t crc_high = 0;
    /* 若工作模式为1K则获取CRC校验码*/
    if (p_dev->frame_tx_bytes == 1024) {
        crc_high = __xmodem_check_mode_crc((char *)p_dev->p_tx_arg, p_dev->frame_tx_bytes);
        if (p_dev->fra_crc_pry == crc_high >> 8) {
            p_dev->fra_crc_pry = crc_high;
            p_dev->state_rx_char = 2;
        } else {
            p_dev->fra_crc_pry = crc_high >> 8;
        }
       *outchar = p_dev->fra_crc_pry;
    }
    /* 若工作模式为128则获取SUM校验码*/
    if (p_dev->frame_tx_bytes == 128) {
        int i;
        char cks = 0;
        /* 将数据累加求和*/
        for (i = 0; i < p_dev->frame_tx_bytes; i++)
        {
            cks += p_dev->p_tx_arg[i];
        }
        p_dev->fra_sum_parity = cks;
        /* 开启计时器*/
        am_softimer_start(&p_dev->softimer, p_dev->p_tra_devinfo->tx_timeout);
       *outchar = p_dev->fra_sum_parity;
        p_dev->state_rx_char = 2;
    }

}
/**
 * \brief 数据不足一帧填充函数
 */
am_static_inline
am_bool_t __xmodem_tx_ctrlz_set (am_xmodem_tx_dev_t *p_dev,
                                 char               *outchar)
{
    if (p_dev->tx_bytes < p_dev->doc_bytes) {
       *outchar = p_dev->p_tx_arg[p_dev->tx_bytes];
        p_dev->tx_bytes++;
        return AM_TRUE;
    } else {
       *outchar = AM_XMODEM_CTRLZ;
        p_dev->p_tx_arg[p_dev->tx_bytes] = AM_XMODEM_CTRLZ;
        p_dev->tx_bytes++;
        return AM_TRUE;
    }
    //return AM_FALSE;
}
/**
 * \brief 发送数据段函数
 */
am_static_inline
am_bool_t __xmodem_tx_frames_data (am_xmodem_tx_dev_t *p_dev,
                                   char               *outchar)
{
    if (p_dev->doc_bytes == p_dev->frame_tx_bytes) {
       *outchar = p_dev->p_tx_arg[p_dev->tx_bytes];
        p_dev->tx_bytes++;
        if (p_dev->tx_bytes == p_dev->frame_tx_bytes) {
            p_dev->state_handle = __xmodem_tx_frames_parity;
            p_dev->tx_bytes = 0;
        }
        return AM_TRUE;
    }
    if (p_dev->doc_bytes < p_dev->frame_tx_bytes ) {
        __xmodem_tx_ctrlz_set(p_dev, outchar);
        if (p_dev->tx_bytes == p_dev->frame_tx_bytes) {
            p_dev->state_handle = __xmodem_tx_frames_parity;
            p_dev->tx_bytes = 0;
            p_dev->state_flag = AM_XMODEM_MOU_SUC;
         }
        return AM_TRUE;
    }
    return AM_FALSE;
}

/**
 * \brief 发送序列号反码函数
 */
am_static_inline
am_bool_t __xmodem_tx_frames_pack_rmoc (am_xmodem_tx_dev_t *p_dev,
                                        char               *outchar)
{
    /* 中断发送函数获取序列号反码*/
   *outchar = ~p_dev->frames_num;
    /* 切换到数据发送状态*/
    p_dev->state_handle = __xmodem_tx_frames_data;
    return AM_TRUE;
}
/**
 * \brief 发送序列号函数
 */
am_static_inline
am_bool_t  __xomdem_tx_frames_packetno (am_xmodem_tx_dev_t *p_dev,
                                        char               *outchar)
{
    /* 序列号加1*/
    p_dev->frames_num++;
    /* 中断发送函数获取序列号*/
   *outchar = p_dev->frames_num;
    /* 切换到获取序列号反码状态*/
    p_dev->state_handle = __xmodem_tx_frames_pack_rmoc;
    return AM_TRUE;
}
/**
 * \brief 发送帧头函数
 */
am_static_inline
am_bool_t __xmodem_tx_frames_head (am_xmodem_tx_dev_t *p_dev,
                                   char               *outchar)
{
    if (p_dev->frame_tx_bytes == 1024) {
       /* 1K工作模式的帧头为STX*/
       *outchar = AM_XMODEM_STX;
    }
    if (p_dev->frame_tx_bytes == 128) {
        /* 128工作模式的帧头为SOH*/
       *outchar = AM_XMODEM_SOH;
    }
    /* 切换到序列号发送状态*/
    p_dev->state_handle = __xomdem_tx_frames_packetno;
    return AM_TRUE;
}
/**
 * \brief 开始发送函数
 */
am_err_t am_xmodem_tx_pack (am_xmodem_tx_dev_t *p_dev,
                            char               *p_doc,
                            uint32_t            pack_size)
{
    if (p_dev == NULL) {
        return -AM_EINVAL;
    }
    if (p_dev->state_flag != 1) {
        p_dev->state_flag = 1;
    }
    /* 获取发送文件的指针*/
    p_dev->p_tx_arg     = p_doc;
    /* 一次发送的模块大小*/
    p_dev->doc_bytes    = pack_size;
    /* 切换到帧头发送状态*/
    p_dev->state_handle = __xmodem_tx_frames_head;
    am_uart_tx_startup(p_dev->uart_handle);

    return AM_TRUE;
}

am_static_inline
void __xmodem_tx_eot_ack_char (am_xmodem_tx_dev_t *p_dev,
                               char               *outchar)
{
     *outchar = AM_XMODEM_ACK;
}
am_static_inline
void __xmodem_tx_eot_ack (am_xmodem_tx_dev_t *p_dev)
{
    p_dev->state_rx_char = 0;
    p_dev->state_handle = __xmodem_tx_eot_ack_char;
    am_uart_tx_startup(p_dev->uart_handle);
    p_dev->state_rx_char = 2;
    p_dev->state_flag = AM_XMODEM_EOT_ACK;
}

/**
 * \brief 接收方要求重发函数
 */
am_static_inline
void __xmodem_tx_nak (am_xmodem_tx_dev_t *p_dev)
{
    if (p_dev->nake_state < p_dev->p_tra_devinfo->nak_times_max) {
        p_dev->tx_bytes = 0;
        p_dev->state_rx_char = 0;
        p_dev->frames_num = p_dev->frames_num - 1;
        p_dev->state_handle = __xmodem_tx_frames_head;
        am_uart_tx_startup(p_dev->uart_handle);
    }
    if (p_dev->nake_state == p_dev->p_tra_devinfo->nak_times_max) {
       am_xmodem_tx_can_set(p_dev);
       p_dev->nake_state = 0;
       /* 通知用户当前数据包重发次数达到规定的最大重发次数, 并已经取消了发送*/
       p_dev->pfn_tx_callback(p_dev->p_arg, AM_XMODEM_NAK_TIME);
    }
    p_dev->nake_state++;
}
/**
 * \brief 应答信号判断函数
 */
am_static_inline
int __xmodem_tx_result_mode (am_xmodem_tx_dev_t *p_dev,
                             char                inchar)
{
    if (p_dev->state_flag == 0) {
        p_dev->state_flag = 1;
        if (inchar == AM_XMODEM_1k) {
            p_dev->frame_tx_bytes = 1024;
        }
        if (inchar == AM_XMODEM_NAK) {
            p_dev->frame_tx_bytes = 128;
        }
        if (p_dev->frame_tx_bytes == 128 || p_dev->frame_tx_bytes == 1024) {
           p_dev->state_rx_char = 0;
           p_dev->pfn_tx_callback(p_dev->p_arg, inchar);
           return AM_TRUE;
        }
    }
    if (p_dev->state_flag == 1) {
        if (inchar == AM_XMODEM_ACK) {
            p_dev->pfn_tx_callback(p_dev->p_arg, inchar);
            am_uart_tx_startup(p_dev->uart_handle);
        }
        if (inchar == AM_XMODEM_NAK) {
            __xmodem_tx_nak(p_dev);
        }
        if (inchar == AM_XMODEM_CAN) {
           p_dev->state_rx_char = 0;
           p_dev->pfn_tx_callback(p_dev->p_arg, inchar);
        }
        return AM_TRUE;
    }
    if (p_dev->state_flag == AM_XMODEM_MOU_SUC) {
        p_dev->pfn_tx_callback(p_dev->p_arg, AM_XMODEM_MOU_SUC);
    }
    return AM_FALSE;
}

/**
 * \brief 模块发送完或者接收方准备好发送通知用户
 */
am_static_inline
int __xmodem_tx_user_inform (am_xmodem_tx_dev_t *p_dev,
                             char                inchar)
{
    int result;
    /*当前状态为文件发送结束时，接收到的应答信号将自动回复*/
    if (p_dev->state_flag == __AM_XMODEM_DOC_EOT) {
        __xmodem_tx_eot_ack(p_dev);
        return AM_TRUE;
    }
    if (p_dev->tx_bytes == 0 ) {
       p_dev->state_rx_char = 0;
       result = __xmodem_tx_result_mode(p_dev, inchar);
    }
    return result;
}
/**
 * \brief 中断接收字符函数
 */
am_static_inline
void __xmodem_tx_char (void *p_arg, uint8_t inchar)
{
    am_xmodem_tx_dev_t *p_dev = (am_xmodem_tx_dev_t *)p_arg;
    am_softimer_stop(&p_dev->softimer);
    if (AM_FALSE == __xmodem_tx_user_inform(p_dev, inchar)) {
        return;
    }
}

/**
 * \brief Xmodem发送超时函数
 */
am_static_inline
void __xmodem_tx_time_callback(void *p_arg)
{
    am_xmodem_tx_dev_t *p_dev = (am_xmodem_tx_dev_t *)p_arg;
    /* 关闭软件定时器 */
    am_softimer_stop(&p_dev->softimer);
    if (p_dev->pfn_tx_callback != NULL) {
        am_xmodem_tx_can_set(p_dev);
        p_dev->pfn_tx_callback(p_dev->p_arg, -AM_ETIME);
     }
}
/**
 * \brief 发送设备初始化函数
 */
am_xmodem_tx_handle_t  am_xmodem_tx_init (
                           am_xmodem_tx_dev_t            *p_dev,
                           const am_xmodem_tx_dev_info_t *p_tx_devinfo,
                           am_uart_handle_t               uart_handle)
{
    if ((NULL == p_dev) || (NULL == p_tx_devinfo) || (NULL == uart_handle)) {
        return NULL;
    }

    p_dev->p_tra_devinfo = (am_xmodem_tx_dev_info_t *)p_tx_devinfo;
    /* 获取串口句柄 */
    p_dev->uart_handle = uart_handle;

    p_dev->tx_bytes = 0;              /**< \brief 初始化发送文件大小*/
    p_dev->p_tx_arg = NULL;           /**< \brief 初始化文件指针 */
    p_dev->state_rx_char = 0;         /**< \brief 默认接收中断不为空 */
    p_dev->state_flag = 0;            /**< \brief 默认第一个接收到的字符为模式判断字符 */
    p_dev->nake_state = 0;            /**< \brief 初始化重发状态为0*/
    p_dev->state_handle = am_xmodem_tx_pack; /**< \brief 初始化状态句柄 */
    /* 使能串口中断模式 */
    am_uart_ioctl(p_dev->uart_handle, AM_UART_MODE_SET, (void *)AM_UART_MODE_INT);
    am_uart_callback_set(p_dev->uart_handle,
                         AM_UART_CALLBACK_RXCHAR_PUT,
                         __xmodem_tx_char,
                         (void *)(p_dev));

    /* 注册发送回调函数 */
    am_uart_callback_set(p_dev->uart_handle,
                         AM_UART_CALLBACK_TXCHAR_GET,
                         __xmodem_tx_char_get,
                         (void *)(p_dev));

    if (p_tx_devinfo->tx_timeout != 0) {
        if (am_softimer_init(&p_dev->softimer,
                              __xmodem_tx_time_callback,
                              p_dev) != AM_OK) {
            return NULL;
        }
    }
    return (am_xmodem_tx_handle_t)(p_dev);
}

