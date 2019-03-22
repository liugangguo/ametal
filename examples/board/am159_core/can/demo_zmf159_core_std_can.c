/*******************************************************************************
*                                 AMorks
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2016 Guangzhou ZHIYUAN Electronics Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
*******************************************************************************/
/**
 * \file
 * \brief CAN演示例程
 *
 * - 操作步骤：
 *   1. 本例程需在am_prj_params.h头文件里使能
 *   - 对应平台的CAN设备宏(AM_DEV_XXXXX_CAN1);
 *   - AM_COM_CONSOLE;
 *   -  对应平台的串口设备宏(AM_DEV_XXXXX_UART1)。
 *   2. 连接CAN1的相关引脚到CAN收发器，再将CAN收发器接口与USBCAN-II设备相连。
 *   3. 打开CAN上位机后，设置波特率为500k。
 *   4. 打开串口调试终端，波特率115200-8-N-1.
 *
 * - 实验现象：
 *   1. 上位机发送数据后，收到发送的数据。
 *   2. 串口打印相关调试信息。
 *
 * - 备注：
 *   1. 其中 CAN ID 和 波特率配置 需要根据具体硬件平台修改。
 *
 * \par 源代码
 * \snippet test_flexcan.c src_test_flexcan
 *
 * \internal
 * \par modification history:
 * - 17-12-15, mex, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_can.h"
#include "am_delay.h"
#include "am_zmf159_inst_init.h"
#include "am_vdebug.h"

#define  CAN_CHN              0     /*CAN ID，根据具体平台修改*/
#define  CAN_RCV_BUFF_LENTH   1024

static am_can_message_t    can_rcv_msg;
static am_can_bus_err_t    can_bus_err_status;
static am_can_int_type_t   can_int_status;


static am_can_message_t can_send_test_msg = {
        0x111,
		AM_CAN_SELF_SEND_FLAG,          /**< \brief 自发自收类型 */
        8,                              /**< \brief msglen 报文长度 */
    {0x11,0x02,0x13,0x04,0x15,0x06,0x17,0x08}
};

/** \brief 波特率表的配置取决于具体硬件平台，需要根据具体硬件平台做出相应的修改*/
/** \brief 波特率表，使用CAN波特率计算工具计算得出,仅供参考(目前输入时钟为PLL3 6分频 再2分频 40MHz) */
/** \brief 6ul波特率计算与传统不同,使用时将工具计算值中的tseg1-1即可 */
/** \brief tseg1 tseg2 sjw brp smp */
//static am_can_bps_param_t can_btr_1000k = {4 - 1,   1,   1,   0,   4  };   /* 1000k, sample point 75% */
//static am_can_bps_param_t can_btr_800k  = {4 - 1,   3,   1,   0,   4  };   /* 800k,  sample point 60% */
static am_can_bps_param_t can_btr_500k  = {4 - 1,   1,   1,   0,   9  };   /* 500k,  sample point 75% */
//static dam_can_bps_param_t can_btr_250k  = {4 - 1,   1,   1,   0,   19 };   /* 250k,  sample point 75% */
//static am_can_bps_param_t can_btr_125k  = {4 - 1,   1,   1,   0,   39 };   /* 125k,  sample point 75% */
//static am_can_bps_param_t can_btr_100k  = {4 - 1,   1,   1,   0,   49 };   /* 100k,  sample point 75% */
//static am_can_bps_param_t can_btr_50k   = {4 - 1,   1,   1,   0,   99 };   /* 50k,   sample point 75% */
//static am_can_bps_param_t can_btr_20k   = {4 - 1,   1,   1,   0,   249};   /* 20k,   sample point 75% */
//static am_can_bps_param_t can_btr_10k   = {8 - 1,   5,   1,   0,   249};   /* 10k,   sample point 62.5% */
//static am_can_bps_param_t can_btr_6_25k = {15 - 1,  7,   1,   0,   255};   /* （最小波特率）6.25k, sample point 68% */

/******************************************************************************/
void __can_err_sta( am_can_bus_err_t err)
{

    if (err & AM_CAN_BUS_ERR_BIT) {    /**< \brief 位错误 */
        am_kprintf(("AM_CAN_BUS_ERR_BIT\n"));
    }
    if (err &AM_CAN_BUS_ERR_ACK) {     /**< \brief 应答错误 */
        am_kprintf(("AM_CAN_BUS_ERR_ACK\n"));
    }
    if (err &AM_CAN_BUS_ERR_CRC) {     /**< \brief CRC错误 */
        am_kprintf(("AM_CAN_BUS_ERR_CRC\n"));
    }
    if (err &AM_CAN_BUS_ERR_FORM) {    /**< \brief 格式错误 */
        am_kprintf(("AM_CAN_BUS_ERR_FORM\n"));
    }
    if (err &AM_CAN_BUS_ERR_STUFF) {   /**< \brief 填充错误 */
        am_kprintf(("AM_CAN_BUS_ERR_STUFF\n"));
    }

}

/**
 * \brief CAN demo
 *
 * \return 无
 */
void demo__zmf159_core_can_entry (void)
{
    am_can_err_t ret;

    /** \brief 初始化CAN */
    am_can_handle_t  can_handle = NULL;

    can_handle = am_zmf159_can_inst_init ();

    ret = am_can_baudrate_set (can_handle, &can_btr_500k);

    if (ret == AM_CAN_NOERROR) {
        AM_INFOF(("\r\nCAN: controller initialize ok. \r\n"));
    } else {
        AM_INFOF(("\r\nCAN: controller initialize error! %d \r\n", ret));
    }

    ret = am_can_start (can_handle);

    if (ret == AM_CAN_NOERROR) {
        AM_INFOF(("\r\nCAN: controller start ok. \r\n"));
    } else {
        AM_INFOF(("\r\nCAN: controller start error! %d \r\n", ret));
    }

    /** \brief 启动CAN */
    AM_INFOF(("CAN: controller start!\r\n"));

    AM_FOREVER {
    	ret = am_can_msg_send (can_handle, &can_send_test_msg);

        if (ret == AM_CAN_NOERROR) {
            AM_INFOF(("\r\nCAN: controller send ok. \r\n"));
        } else {
            AM_INFOF(("\r\nCAN: controller send error! %d \r\n", ret));
        }

        ret = am_can_msg_recv (can_handle, &can_rcv_msg);

        if (ret == AM_CAN_NOERROR) {
             AM_INFOF(("\r\nCAN: controller rcv ok. \r\n"));
        } else {
             AM_INFOF(("\r\nCAN: controller rcv error! %d \r\n", ret));
        }

        ret = am_can_status_get (can_handle, &can_int_status, &can_bus_err_status);

            am_mdelay(10); /* 延时10ms */
            if (can_bus_err_status != AM_CAN_BUS_ERR_NONE) {
            	__can_err_sta(can_bus_err_status);
            }

        am_mdelay(1000);
    }
}

/** [src_test_flexcan] */

/* end of file */
