#include "zlg116_pin.h"
#include "am_boot.h"
#include "am_boot_kft.h"
#include "am_zlg116_inst_init.h"

/** \brief 固件升级引脚 */
#define __ENABLE_PIN          (PIOA_8)
/** \brief 应用代码起始地址  */
#define __APP_START_ADDR      0x08007000

void demo_am116_core_kft_bootloader_entry (void)
{
    am_gpio_pin_cfg(__ENABLE_PIN, AM_GPIO_INPUT | AM_GPIO_PULLUP);

    am_zlg116_std_boot_inst_init();

    if (am_gpio_get(__ENABLE_PIN)) {

        am_boot_source_release();
        am_gpio_pin_cfg(__ENABLE_PIN, AM_GPIO_INPUT | AM_GPIO_FLOAT);
        if(AM_OK != am_boot_go_application(__APP_START_ADDR)){
            while(1);
        }
    }

    am_zlg116_boot_kft_inst_init();
    while(1) {
        am_boot_kft_command_pump();
    }
}
