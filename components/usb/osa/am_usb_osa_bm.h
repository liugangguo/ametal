/**
 * \file
 * \brief     USB
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-27  bob, first implementation.
 * \endinternal
 */

#ifndef __AM_USB_OSA_BM_H
#define __AM_USB_OSA_BM_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define AM_USB_OSA_SR_ALLOC()       uint8_t usbOsaCurrentSr;
#define AM_USB_OSA_ENTER_CRITICAL() am_usb_osa_enter_critical(&usbOsaCurrentSr)
#define AM_USB_OSA_EXIT_CRITICAL()  am_usb_osa_exit_critical(usbOsaCurrentSr)

/*******************************************************************************
 * API
 ******************************************************************************/
void am_usb_osa_enter_critical(uint8_t *p_sr);
void am_usb_osa_exit_critical(uint8_t sr);

#ifdef __cplusplus
}
#endif

#endif /* __AM_USB_OSA_BM_H */
