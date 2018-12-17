
#include "ametal.h"
#include "am_board.h"
#include "am_vdebug.h"
void demo_am116_core_kft_application_entry (void)
{
    AM_DBG_INFO("application : zlg116_bootloader_kft_application start up successful!\r\n");

    while (1) {

        am_led_toggle(LED0);

        am_mdelay(1000);
    }
}
