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
 * \brief I2C 从机例程，通过标准接口实现
 *
 * - 操作步骤：
 *   1. 连接对应引脚。
 *
 * \par 源代码
 * \snippet demo_std_i2c_slave.c src_std_i2c_slave
 *
 * \internal
 * \par Modification history
 * - 1.00  19-01-22  bzq, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_i2c_slave
 * \copydoc demo_std_i2c_slave.c
 */

/** [src_std_i2c_slave] */
#include "ametal.h"
#include "string.h"
#include "am_vdebug.h"
#include "am_i2c_slv.h"


/**
 * \brief 接收从机数据结构体
 */
typedef struct am_i2c_smoke_slv_data {
    uint16_t              cmd;         /**< \brief 接收的命令  */
    uint8_t               sum_cail;    /**< \brief 校验和  */
    uint8_t               un_sum_cail; /**< \brief 校验和 取反 */
    uint8_t               i2c_cail;    /**< \brief i2c通讯校验*/
} am_smoke_slv_data_t;

/**
 * \brief 接收主机数据结构体
 */
typedef struct am_smoke_master_data {
    uint8_t               status;      /**< \brief 状态位   */
    uint8_t               elec;        /**< \brief 电量   */
    uint8_t               recv;        /**< \brief 保留值   */
    uint8_t               sum_cail;    /**< \brief 校验和  */
    uint8_t               un_sum_cail; /**< \brief 校验和 取反 */
} am_smoke_master_data_t;

/**
 * \brief 地址匹配回调函数
 */

static am_smoke_master_data_t  smoke_master_data = {0};

static am_smoke_slv_data_t     smoke_slv_data = {
        0x5566,
        0xaa,
        0xbb,
        0xcc
};

static uint8_t   read_flag  = AM_FALSE;

volatile static uint8_t  *__g_p_data = NULL;

static int __addr_matching ( void * p_arg, am_bool_t is_rx)
{
    /* do some thing */
    return AM_OK;
}

uint8_t data = 0;

/**
 * \brief 获取发送一个字节回调
 */

static int __txbyte_get (void *p_arg, uint8_t *p_byte)
{
    if (__g_p_data == NULL) {
        __g_p_data = (uint8_t *)&smoke_slv_data;
    }

    if ((__g_p_data - (uint8_t *)&smoke_slv_data) > sizeof(smoke_slv_data)) {
        __g_p_data = (uint8_t *)&smoke_slv_data;
    	*p_byte = *__g_p_data;
        return AM_OK;
    }

    *p_byte = *(__g_p_data + 1);
    __g_p_data++;
    return AM_OK;
}

/**
 * \brief 接受一个字节回调
 */
static int __rxbyte_put(void *p_arg, uint8_t byte)
{
    if (__g_p_data == NULL) {
        __g_p_data = (uint8_t *)&smoke_master_data;
        read_flag  = AM_TRUE;
    }

    if ((__g_p_data - (uint8_t *)&smoke_master_data) > sizeof(smoke_master_data)) {
        __g_p_data = NULL;
        return AM_OK;
    }

    *__g_p_data = byte;
    __g_p_data++;

    return AM_OK;
}

/**
 * \brief 停止传输回调
 */
static void  __tran_stop(void *p_arg)
{
    __g_p_data = NULL;
}

static am_i2c_slv_cb_funcs_t __g_i2c_slv_cb_funs = {
    __addr_matching,
    __txbyte_get,
    __rxbyte_put,
    __tran_stop,
};

/**
 * \brief 例程入口
 */
void demo_std_i2c_smoke_slave_entry (am_i2c_slv_handle_t handle, uint16_t dev_addr)
{
    am_i2c_slv_device_t i2c_slv_dev;
    uint8_t              count = 0;
    am_i2c_slv_mkdev(&i2c_slv_dev,
                      handle,
                     &__g_i2c_slv_cb_funs,
                      dev_addr,
                      AM_I2C_SLV_ADDR_7BIT,
                      NULL);

    /* 开始运行从机设备 */
    am_i2c_slv_setup (&i2c_slv_dev);

    AM_FOREVER {
        if (read_flag == AM_TRUE ) {
            am_kprintf("status = 0x%x\r\n", smoke_master_data.status);
            am_kprintf("elec   = 0x%x\r\n", smoke_master_data.elec);
            am_kprintf("recv   = 0x%x\r\n", smoke_master_data.recv);
            am_kprintf("sum_cail    = 0x%x\r\n", smoke_master_data.sum_cail);
            am_kprintf("un_sum_cail = 0x%x\r\n", smoke_master_data.un_sum_cail);

            am_kprintf("smoke_maste recive %d \r\n\r\n", ++count);

            memset(&smoke_master_data, 0 , sizeof(smoke_master_data));
            read_flag = AM_FALSE;
        }
    }
}
/** [src_std_i2c_slave] */

/* end of file */
