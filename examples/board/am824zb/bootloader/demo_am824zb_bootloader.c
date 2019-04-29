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
 * \brief ZM516无线固件升级例程，本demo实现zigbee固件接收，是作为B板的bootloader。
 * \note
 *    1. 串口0需要与PC连接，通过串口助手发送固件，波特率为115200，引脚连接关系如下：
 * <pre>
 *           PIO0_0   <-->  PC_TX
 *           PIO0_4   <-->  PC_RX
 *
 *    注意：  B板程序下载运行后会串口打印5s倒计时的信息，
 *            需要在这5s内发送任意命令(通A板发送串口任意字符，不能超过64字节)，这时进入固件
 *            接收状态，此时会等待超时10s，等待接收固件。如果A板没有发送任意字符，则该
 *            程序会检测B板的flash用户代码区是否有可执行的代码，如果有则跳转到该代码处运行，
 *            否则程序会重新等待固件接收命令(打印倒计时5s信息)。
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 18-12-18  yrh, first implementation
 * \endinternal
 */

/**
 * \addtogroup demo_if_am824zb_bootloader
 * \copydoc demo_am824zb_bootloader.c
 */

#include "ametal.h"
#include "am_vdebug.h"
#include "am_board.h"
#include "am_boot.h"
#include "am_uart.h"
#include "am_boot_firmware.h"
#include "am_boot_flash.h"
#include "am_lpc82x_inst_init.h"
#include "am_bootconf_lpc824.h"
#include "am_int.h"
#include <string.h>
#include "am_lpc824_boot_firmware_flash.h"

/* 是否通过远程接收的命令修改本地地址 */
#define  CHANGE_MY_ADDR             0

/**
 * \name bootloader状态
 * @{
 */
/** \brief 启动延时等待状态 */
#define BOOT_WAIT_STATE             0

/** \brief bootloader启动状态 */
#define BOOT_STARTUP_STATE          1

/** \brief 应用启动状态 */
#define APP_STARTUP_STATE           2

/** \brief 应用固件接收状态 */
#define APP_RECEIVE_STATE           3

/** \brief 应用固件接收结束状态 */
#define APP_RECEIVE_END             4
/** @} */


/** \brief 启动延时时间（秒） */
#define BOOT_WAITE_TIME             5

/** \brief 定时器定时时间 */
static volatile uint16_t timer = BOOT_WAITE_TIME;

/** \brief bootloader状态*/
static volatile uint8_t boot_state = BOOT_WAIT_STATE;

/** \brief 一秒超时标志 */
static volatile uint8_t second_flag   = 0;

/**
 * \brief  启动延时等待软件定时器回调函数
 */
static void __startup_wait_timer_handle(void *p_arg)
{
    timer++;
    if(boot_state == BOOT_WAIT_STATE) {
        second_flag = 1;
    } 
}


static void __delay(void)
{
    volatile uint32_t i = 1000000;
    while(i--){
		}
}
static uint8_t __attribute__((aligned(256))) recv_buf[64] = {0};

/**
 * \brief bootloader demo入口
 */
void demo_am824zb_bootloader_entry (void)
{
    am_boot_firmware_verify_info_t firmware_head;
    am_boot_firmware_handle_t      firmware_handle;
	  am_zm516x_cfg_info_t           zm516x_cfg_info;

    am_zm516x_handle_t zm516x_handle = am_zm516x_inst_init();  
  
	/** \brief bootloader启动延时软件定时器结构体 */
    am_softimer_t        startup_wait_timer;
	
    int      ret;
	  uint32_t count   = 0; 
		
    /* 获取 ZigBee 模块的配置信息（永久命令：D1） */
    if (am_zm516x_cfg_info_get(zm516x_handle, &zm516x_cfg_info) != AM_OK) {
		    am_kprintf("zm516x_cfg_info_get fiald\r\n");
		}

	  zm516x_cfg_info.chan         = 20;
    zm516x_cfg_info.serial_rate  = 3; /* 波特率9600 */
		
		zm516x_cfg_info.dst_addr[0]  = 0x00;
	  zm516x_cfg_info.dst_addr[1]  = 0x00;
		
		zm516x_cfg_info.panid[0]     = 0x10;
		zm516x_cfg_info.panid[1]     = 0x01;
		
	  zm516x_cfg_info.my_addr[0]   = 0x20;
	  zm516x_cfg_info.my_addr[1]   = 0x02;
		
    /* 修改 ZigBee 模块的配置信息（永久命令：D6），设置成功需复位 */
    if (am_zm516x_cfg_info_set(zm516x_handle, &zm516x_cfg_info) != AM_OK) {
				am_kprintf("zm516x_cfg_info_set fiald\r\n");
		}
		
    /* 使 ZigBee 模块复位（永久命令：D9） */
    am_zm516x_reset(zm516x_handle);
    __delay();
		
		am_uart_ioctl(zm516x_handle->uart_handle->handle, 
		              AM_UART_BAUD_SET, 
		              (void *)9600);
		
    /* bootloader flash初始化  */
    am_boot_flash_handle_t flash_handle = am_lpc824_boot_flash_inst_init();
    /* 固件存放标准接口初始化  */
    firmware_handle = am_lpc824_boot_firmware_flash(flash_handle);
	
      /* bootloader 标准接口初始化  */
    am_lpc824_std_boot_inst_init(flash_handle);
	
    am_uart_handle_t uart_handle = am_lpc82x_usart0_inst_init();
    am_debug_init(uart_handle, 115200);
		
    /* 启动延时回调定时器初始化  */
    am_softimer_init(&startup_wait_timer, __startup_wait_timer_handle, &startup_wait_timer);
		
		am_softimer_start(&startup_wait_timer, 1000);
		
		am_kprintf("Device will enter application, if don't input anything after %ds\r\n",timer);
		
		timer = 0;
		/* 延时等待，如果用户有数据发来，就进入bootloader，否者跳转到应用程序 */
		while(boot_state == BOOT_WAIT_STATE) {
			
		    /* 若接收到数据，则切换到Bootloader状态 */
		    ret = am_zm516x_receive(zm516x_handle, (uint8_t *)&recv_buf, sizeof(recv_buf));
				if (ret > 0) {
					boot_state = BOOT_STARTUP_STATE;
					break;
			  }
			
			  /* 若超时， 则进入用户代码区 */
				if (timer > BOOT_WAITE_TIME){
					boot_state = APP_STARTUP_STATE;
					break;
				}
			
				/* 每秒打印一次 */
				if(timer < BOOT_WAITE_TIME && second_flag == 1){
			      am_kprintf("Device will enter application, if don't input anything after %ds\r\n", BOOT_WAITE_TIME - timer);	
					  second_flag = 0;
				}
		 }
		
    while(1) {
		    am_kprintf("bootloader : running...\r\n");

		    /* 如果进入固件接收状态 */
		    if (boot_state == BOOT_STARTUP_STATE) {
			 
			 	    /* 准备固件存放 */
            am_boot_firmware_store_start(firmware_handle, 18 * 1024);
			      am_kprintf("bootloader : firmware transmission is ready\r\n");

			      timer = 0;
				    while(am_zm516x_receive(zm516x_handle, &firmware_head, sizeof(firmware_head)) != 8) {
					      if (timer > 10) {
							      continue;
						    }
				    }
					 
				    timer = 0;
			 
				    while(boot_state == BOOT_STARTUP_STATE) {		
						    ret = am_zm516x_receive(zm516x_handle, recv_buf, sizeof(recv_buf));					  
						    if (ret > 0) {
						        /* 固件存放  ，每次存放字节 */ 
							      am_boot_firmware_store_bytes(firmware_handle, recv_buf, sizeof(recv_buf));

							      timer = 0;
							      count += ret;
						    }
								
						    if (timer > 2) {
								    if (count > 0) {
									      boot_state = APP_RECEIVE_END;
								    }							
								    break;
						    }					
				    }
        }
		  
        /* 如果固件接收结束 */
			  if (boot_state == APP_RECEIVE_END) {
				    /* 固件存放结束  */
            am_boot_firmware_store_final(firmware_handle);

			      /* 打印接收的数据大小，减去2字节的my_addr 加上8字节头*/
            am_kprintf("bootloader : firmware receive successful\r\n");
				
            /* 固件校验  */
            ret = am_boot_firmware_verify(firmware_handle, &firmware_head);
            if(ret != AM_OK) {
                am_kprintf("bootloader : firmware verify error, bootloader will restart!\r\n");
					      count = 0;
					      boot_state = BOOT_STARTUP_STATE;
                continue;
            }
				    boot_state = APP_STARTUP_STATE;
								
#if CHANGE_MY_ADDR				
				/* 获取 ZigBee 模块的配置信息（永久命令：D1） */
        am_zm516x_cfg_info_get(zm516x_handle, &zm516x_cfg_info);
				
				zm516x_cfg_info.my_addr[0] = recv_buf[1];
				zm516x_cfg_info.my_addr[1] = recv_buf[0];
				
				    /* 修改 ZigBee 模块的配置信息（永久命令：D6），设置成功需复位 */
				if (am_zm516x_cfg_info_set(zm516x_handle, &zm516x_cfg_info) != AM_OK) {
					am_kprintf("addr set error!!!\r\n");
				}
	
				/* 使 ZigBee 模块复位（永久命令：D9） */
				am_zm516x_reset(zm516x_handle);
				am_mdelay(10);
				
				am_zm516x_send(zm516x_handle, "recvOK", sizeof("recvOK"));
#endif		
        }
		
        if(am_boot_app_is_ready() && boot_state == APP_STARTUP_STATE) {
            //am_kprintf("bootloader : go to application...\r\n");

            __delay();
            am_lpc82x_usart0_inst_deinit(uart_handle);
            /* 跳转到应用程序  */
            if(AM_OK != am_boot_go_application()){
					      count = 0;
							  boot_state = BOOT_STARTUP_STATE;
                continue;
            }
        }
	
    }
}

/* end of file */
