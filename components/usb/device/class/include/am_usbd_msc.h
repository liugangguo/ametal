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
 * \brief USBD MSC
 *
 * \internal
 * \par Modification history
 * - 1.00 16-9-27  bob, first implementation.
 * \endinternal
 */

/**
 * \file
 * \brief     USB
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-27  bob, first implementation.
 * \endinternal
 */

#ifndef __AM_USBD_MSC_H
#define __AM_USBD_MSC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_usb.h"
#include "am_usb_dci.h"



/** \brief msc类设备代码标识  */
#define AM_USBD_CONFIG_MSC_CLASS_CODE                     (0x08U)
#define AM_USBD_MSC_SUBCLASS                              (0x06U)
#define AM_USBD_MSC_PROTOCOL                              (0x50U)

/** \brief 得到最大的LUN */
#define AM_USBD_MSC_GET_MAX_LUN                           (0xFEU)
/** \brief 仅批量大容量储存重置  */
#define AM_USBD_MSC_BULK_ONLY_MASS_STORAGE_RESET          (0xFFU)



/*******************************************************************************
  宏函数定义
*******************************************************************************/

/**< \brief 求出16位时间格式的高字节 */
#define AM_TIME_HB(H,M,S) (((((H)<<11))|((M)<<5)|(S))>>8)

/**< \brief 求出16位时间格式的低字节 */
#define AM_TIME_LB(H,M,S) ((((H)<<11))|((M)<<5)|(S))

/**< \brief 求出16位日期格式的高字节 */
#define AM_DATE_HB(Y,M,D) (((((Y)-1980)<<9)|((M)<<5)|(D))>>8)

/**< \brief 求出16位日期格式的低字节 */
#define AM_DATE_LB(Y,M,D) ((((Y)-1980)<<9)|((M)<<5)|(D))

//#define AM_BULK_MAX_PACKET_SIZE           (0x40)    /**< \brief 定义批量传输的最大字节数 */
#define AM_SCSI_COMMAND_SIZE              (0x20)      /**< \brief 定义SISI命令字节数 */

#define AM_USBD_MSC_DISD_SIZE             (256 * 1024U)
#define AM_USBD_MSC_SECTOR_SIZE           (512U)      /**< \brief 扇区大小 */
#define AM_USBD_MSC_RAMDISK_SIZE          (15*1024U)  /**< \brief 放FAT表及用户数据*/
#define AM_USBD_MSC_USE_DATE_OFST         (2048U)     /**< \brief 用户数据在FAT数据区偏移位置 */
#define AM_USBD_MSC_FAT1_OFST             (512U)      /**< \brief FAT1在FAT表中的偏移位置 */


/**< \brief CBW 标识符 */
#define AM_BOT_CBW_SIGNATURE             (0x43425355)

/**< \brief CSW 标识符 */
#define AM_BOT_CSW_SIGNATURE             (0x53425355)

/*******************************************************************************
  SBU_MSC SCSI命令运行阶段
*******************************************************************************/

#define AM_USBD_MSC_IDLE                 (0)  /**< \brief Idle state */
#define AM_USBD_MSC_DATA_OUT             (1)  /**< \brief Data Out state */
#define AM_USBD_MSC_DATA_IN              (2)  /**< \brief Data In state */
#define AM_USBD_MSC_DATA_IN_LAST         (3)  /**< \brief Last Data In Last */
#define AM_USBD_MSC_CSW_SEND             (4)  /**< \brief Command Status Wrapper */
#define AM_USBD_MSC_DATA_ERROR           (5)  /**< \brief error state */

/*******************************************************************************
  CSW状态返回数据长度/值
*******************************************************************************/

/**< \brief BYTCHK 字节检查位 */
#define AM_USBD_MSC_BLKVFY                          (0x04)
/**< \brief 设备不存在  */
#define AM_USBD_MSC_MEDIUM_NOT_PRESENT              (0x3A)
/**< \brief 地址超出范围  */
#define AM_USBD_MSC_ADDRESS_OUT_OF_RANGE            (0x21)
/**< \brief 命令参数表长度错误  */
#define AM_USBD_MSC_PARAMETER_LIST_LENGTH_ERROR     (0x1A)
/**< \brief REQUEST_SENSE_DATA CSW数据长度 */
#define AM_USBD_MSC_REQUEST_SENSE_DATA_LEN          (0x12)
/**< \brief MODE_SENSE10_DATA CSW数据长度 */
#define AM_USBD_MSC_MODE_SENSE10_DATA_LEN           (0x08)
/**< \brief READ_FORMAT_CAPACITY_DATA CSW数据长度 */
#define AM_USBD_MSC_READ_FORMAT_CAPACITY_DATA_LEN   (0x0C)
/**< \brief READ_CAPACITY10_DATA CSW数据长度 */
#define AM_USBD_MSC_READ_CAPACITY10_DATA_LEN        (0x08)
/**< \brief MODE_SENSE6_DATA CSW数据长度 */
#define AM_USBD_MSC_MODE_SENSE6_DATA_LEN            (0x04)
/**< \brief STANDARD_INQUIRY_DATA CSW数据长度 */
#define AM_USBD_MSC_STANDARD_INQUIRY_DATA_LEN       (0x24)


/*******************************************************************************
  SCSI Commands
*******************************************************************************/

#define AM_SCSI_FORMAT_UNIT                (0x04)  /**< \brief 格式化储存命令 */
#define AM_SCSI_INQUIRY                    (0x12)  /**< \brief 查询设备信息命令 */
#define AM_SCSI_MODE_SENSE6                (0x1A)  /**< \brief 模式感知命令 */
#define AM_SCSI_MODE_SENSE10               (0x5A)  /**< \brief 返回参数命令 */
#define AM_SCSI_ALLOW_MEDIUM_REMOVAL       (0x1E)  /**< \brief 写保护命令 */
#define AM_SCSI_READ10                     (0x28)  /**< \brief 从设备读取数据命令 */
#define AM_SCSI_READ_CAPACITY10            (0x25)  /**< \brief 读取设备容量命令 */
#define AM_SCSI_REQUEST_SENSE              (0x03)  /**< \brief 获取状态信息命令 */
#define AM_SCSI_START_STOP_UNIT            (0x1B)  /**< \brief 开始/停止命令 */
#define AM_SCSI_TEST_UNIT_READY            (0x00)  /**< \brief 查询设备是否ready命令 */
#define AM_SCSI_WRITE10                    (0x2A)  /**< \brief 写数据到储存设备命令 */
#define AM_SCSI_VERIFY10                   (0x2F)  /**< \brief 验证命令 */
#define AM_SCSI_READ_FORMAT_CAPACITIES     (0x23)  /**< \brief 读取当前设备容量和可格式化命令 */

/*******************************************************************************
  CSW Status Definitions
*******************************************************************************/

#define AM_USBD_MSC_CSW_DATA_LENGTH     (0x000D) /**< \brief CSW数据长度 */
#define AM_USBD_MSC_CSW_CMD_PASSED      (0x00)   /**< \brief 命令执行成功 */
#define AM_USBD_MSC_CSW_CMD_FAILED      (0x01)   /**< \brief 命令执行失败 */
#define AM_USBD_MSC_CSW_PHASE_ERROR     (0x02)   /**< \brief 命令执行失败 */
#define AM_USBD_MSC_SEND_CSW_DISABLE    (0)      /**< \brief SCW发送失败 */
#define AM_USBD_MSC_SEND_CSW_ENABLE     (1)      /**< \brief SCW发送成功 */
#define AM_USBD_MSC_ILLEGAL_REQUEST     (5)      /**< \brief Sence Key值 */
#define AM_USBD_MSC_NOT_READY           (2)      /**< \brief Sence Key值 */
#define AM_USBD_MSC_Max_LUN             (0)      /**< \brief 最大逻辑单元 */
#define AM_USBD_MSC_TXFR_IDLE           (0)      /**< \brief 空闲状态 */
#define AM_USBD_MSC_TXFR_ONGOING        (1)      /**< \brief 运行状态 */
#define AM_USBD_MSC_NO_SENSE            (0)      /**< \brief 无意义 */
#define AM_USBD_MSC_INVALID_CMD         (0x24)   /**< \brief 无效的命令 */


/**
 * \brief SICI Command Block Wrapper 数据结构
 *
 * \note 小端字节 (低字节在先)
 */
typedef struct am_bulk_only_cbw {
    uint32_t dsignature;    /**< \brief 该字段为CBW 标志 */
    uint32_t dtag;          /**< \brief CBW标签，由主机随机分配，需要在CSW中的dtag填入该标签 */
    uint32_t ddata_length;  /**< \brief 需要在数据传输阶段传输的数据长度 */
    uint8_t  bm_flags;      /**< \brief 表示数据传输方向 (D7位为1：输入数据，D7位为0：输出数据) */
    uint8_t  blun;          /**< \brief 逻辑单元的编号，(设置为0) */
    uint8_t  bcb_length;    /**< \brief 需要执行的命令的长度 有效范围1-16 */
    uint8_t  cb[16];        /**< \brief 需要执行的具体命令 */
} am_bulk_only_cbw_t;

/**
 * \brief SICI Command Status Wrapper 数据结构
 *
 */
typedef struct am_bulk_only_csw {
    uint32_t dsignature;    /**< \brief 该字段为CSW 标志 */
    uint32_t dtag;          /**< \brief 该命令状态封装包的标签 其值为 CBW 中的 dtag 一致 */
    uint32_t ddata_residue; /**< \brief 记录还需要传输的字节数 */
    uint8_t  bstatus;       /**< \brief 命令执行的状态 */
} am_bulk_only_csw_t;

/**
 * \brief usb_msc u盘信息
 *
 * \note 不同容量的u盘 各个区的地址不一样
 */
typedef struct am_usb_msc_diskinfo {
	uint8_t      is_win10;

    uint32_t     memory_size;        /**< \brief U盘容量大小 */
    uint16_t     block_size;         /**< \brief U盘扇区大小 */
    uint32_t     block_count;        /**< \brief U盘扇区总数 */
    uint32_t     fat2_addr;          /**< \brief FAT2 的地址 */
    uint32_t     rootdir_addr;       /**< \brief 根目录 的地址 */
    uint32_t     data_addr;          /**< \brief 数据区 的地址 */

    uint8_t     *p_cmd_buffer;
    uint8_t     *p_ram_buffer;

    const uint8_t *p_root_file;
    uint32_t       root_file_len;

    const uint8_t *p_file;
    uint32_t       file_len;

} am_usbd_msc_diskinfo_t;

/**
 * \brief usb_msc 传输状态信息
 *
 * \note usb枚举成功以后，通信的主要过程：
 *       主机发送CBW命令->设备发送数据(需要传输数据时才有此过程)->设备发送CSW状态
 */
typedef struct am_usb_msc_state {
    uint8_t     transfer_state;        /**< \brief 数据开始传输标志 */
    uint8_t     bot_state;             /**< \brief U盘传输的状态过程 */
    uint32_t    block_offset;          /**< \brief 记录读/写位置的偏移量 */
    uint32_t    scsi_lab;              /**< \brief 存放当前读/写数据的逻辑块地址 */
    uint32_t    scsi_blk_len;          /**< \brief 存放当前读/写数据的逻辑块个数 */
} am_usb_msc_state_t;

typedef struct am_usbd_msc_endpoint {
    uint8_t endpoint_in;
    uint8_t endpoint_out;
}am_usbd_msc_endpoint_t;


typedef void (*am_usbd_msc_recv_cb_t)(void *p_arg, uint8_t *p_buff, uint16_t len);

typedef struct am_usbd_msc_cb {
	am_usbd_msc_recv_cb_t   pfn_recv;
	void                   *p_arg;
}am_usbd_msc_cb_t;

/** \brief usb device msc class struct */
typedef struct am_usbd_msc {
    am_usbd_dev_t         *p_dev;
    am_bulk_only_cbw_t     cbw;
    am_bulk_only_csw_t     csw;
    am_usb_msc_state_t     state;

    volatile uint8_t       int_status_in;    /**< \brief 输入中断状态 */
    volatile uint8_t       int_status_out;   /**< \brief 输出中断状态 */

    uint32_t               w_offset;
    uint32_t               w_length;

    uint32_t               r_offset;
    uint32_t               r_length;

    am_usbd_msc_endpoint_t endpoint;

    am_usbd_msc_cb_t       msc_cb;

    const am_usbd_msc_diskinfo_t *p_info;
}am_usbd_msc_t;

typedef am_usbd_msc_t *am_usbd_msc_handle;
/**
 * \brief usb批量输出端点2中断函数处理
 *
 * \param[in] p_dev : 指向usb设备的指针
 *
 * \return 无
 */
void am_zlg217_usb_msc_enpoint2_bulk_out (am_usbd_msc_handle handle);

/**
 * \brief usb批量输入端点1中断函数处理
 *
 * \param[in] p_dev : 指向usb设备的指针
 *
 * \return 无
 */
void am_zlg217_usb_msc_enpoint1_bulk_in (am_usbd_msc_handle handle);



am_usbd_msc_handle am_usbd_msc_init (am_usbd_msc_t                    *p_dev,
                                     const am_usbd_msc_diskinfo_t     *p_info,
                                     am_usbd_dev_t                    *p_usbd);

void am_zlg217_usb_msc_deinit (am_usbd_msc_t *p_dev);

am_usb_status_t am_usbd_msc_vendor_request_callback(am_usbd_msc_handle    handle,
                                                    am_vendor_request_t   pfn_cb,
                                                    void                 *p_arg);

am_usb_status_t am_usbd_msc_recv_callback (am_usbd_msc_handle    handle,
										   am_usbd_msc_recv_cb_t pfun,
										   void                 *p_arg);

#ifdef __cplusplus
}
#endif

#endif /* __AM_USBD_MSC_H */

/* end of file */
