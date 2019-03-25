/**
 * \file
 * \brief
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-27  bob, first implementation.
 * \endinternal
 */

#ifndef __AM_USB_OSA_H
#define __AM_USB_OSA_H

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @addtogroup usb_os_abstraction
 * @{
 */

/** \brief USB memory size */
#define AM_USB_MEMHEAP_SIZE  1024

/** \brief Define big endian */
#define AM_USB_BIG_ENDIAN    (0U)
/** \brief Define little endian */
#define AM_USB_LITTLE_ENDIAN (1U)

/** \brief Define current endian */
#define AM_ENDIANNESS AM_USB_LITTLE_ENDIAN

/** \brief Define USB OSA event handle */
typedef void *am_usb_osa_event_handle_t;

/** \brief Define USB OSA semaphore handle */
typedef void *am_usb_osa_sem_handle_t;

/** \brief Define USB OSA mutex handle */
typedef void *am_usb_osa_mutex_handle_t;

/** \brief Define USB OSA message queue handle */
typedef void *am_usb_osa_msgq_handle_t;

/** \brief USB OSA error code */
typedef enum am_usb_osa_status
{
    AM_USB_OSA_STATUS_SUCCESS = 0x00U, /**< \brief Success */
    AM_USB_OSA_STATUS_ERROR,           /**< \brief Failed */
    AM_USB_OSA_STATUS_TIME_OUT,         /**< \brief Timeout occurs while waiting */
} am_usb_osa_status_t;

/** \brief The event flags are cleared automatically or manually.*/
typedef enum am_usb_osa_event_mode
{
    AM_USB_OSA_EVENT_MANUAL_CLEAR = 0U, /**< \brief The flags of the event is cleared manually. */
    AM_USB_OSA_EVENT_AUTO_CLEAR = 1U,   /**< \brief The flags of the event is cleared automatically. */
} am_usb_osa_event_mode_t;

/* Include required header file based on RTOS selection */
#if defined(USB_STACK_BM)

#include "am_usb_osa_bm.h"

#elif defined(USB_STACK_FREERTOS)

#include "am_usb_osa_freertos.h"

#elif defined(USB_STACK_UCOSII)

#include "am_usb_osa_ucosii.h"

#elif defined(USB_STACK_UCOSIII)

#include "am_usb_osa_ucosiii.h"

#else

//#error Not define RTOS in file "usb_osa.h".

#endif


/*!
 * @name USB OSA Memory Management
 * @{
 */

/*!
 * @brief Reserves the requested amount of memory in bytes.
 *
 * The function is used to reserve the requested amount of memory in bytes and initializes it to 0.
 *
 * @param length Amount of bytes to reserve.
 *
 * @return Pointer to the reserved memory. NULL if memory can't be allocated.
 */
void *am_usb_osa_memory_allocate(uint32_t length);

/*!
 * @brief Frees the memory previously reserved.
 *
 * The function is used to free the memory block previously reserved.
 *
 * @param p Pointer to the start of the memory block previously reserved.
 *
 */
void am_usb_osa_memory_free(void *p);

/* @} */

/*!
 * @name USB OSA Event
 * @{
 */

/*!
 * @brief Creates an event object with all flags cleared.
 *
 * This function creates an event object and sets its clear mode. If the clear mode
 * is AM_USB_OSA_EVENT_AUTO_CLEAR, when a task gets the event flags, these flags are
 * cleared automatically. If the clear mode is AM_USB_OSA_EVENT_MANUAL_CLEAR, the flags must
 * be cleared manually.
 *
 * @param handle    It is an out parameter, which is used to return the pointer of the event object.
 * @param flag      The event is auto-clear or manual-clear. See the enumeration #usb_osa_event_mode_t.
 *
 * @return A USB OSA error code or kStatus_OSA_Success.
 *
 * Example:
   @code
   am_usb_osa_event_handle_t eventHandle;
   am_usb_osa_status_t     usbOsaStatus;
   usbOsaStatus = USB_OsaEventCreate(&eventHandle, AM_USB_OSA_EVENT_MANUAL_CLEAR);
   @endcode
 *
 */
am_usb_osa_status_t am_usb_osa_event_create(am_usb_osa_event_handle_t *handle,
                                            uint32_t                   flag);

/*!
 * @brief Destroys a created event object.
 *
 * @param handle    Pointer to the event object.
 *
 * @return A USB OSA error code or kStatus_OSA_Success.
 *
 * Example:
   @code
   am_usb_osa_status_t     usbOsaStatus;
   ...
   usbOsaStatus = USB_OsaEventDestroy(eventHandle);
   @endcode
 *
 */
am_usb_osa_status_t am_usb_osa_event_destroy(am_usb_osa_event_handle_t handle);

/*!
 * @brief Sets an event flag.
 *
 * Sets specified flags for an event object.
 *
 * @param handle    Pointer to the event object.
 * @param bitMask   Event flags to be set.
 *
 * @return A USB OSA error code or kStatus_OSA_Success.
 *
 * Example:
   @code
   am_usb_osa_status_t     usbOsaStatus;
   ...
   usbOsaStatus = USB_OsaEventSet(eventHandle, 0x01U);
   @endcode
 *
 */
am_usb_osa_status_t am_usb_osa_event_set(am_usb_osa_event_handle_t handle,
                                         uint32_t                bit_mask);

/*!
 * @brief Waits for an event flag.
 *
 * This function waits for a combination of flags to be set in an event object.
 * An applications can wait for any/all bits to be set. This function can
 * get the flags that wake up the waiting task.
 *
 * @param handle    Pointer to the event object.
 * @param bitMask   Event flags to wait.
 * @param flag      Wait all flags or any flag to be set. 0U - wait any flag, others, wait all flags.
 * @param timeout   The maximum number of milliseconds to wait for the event.
 *                  If the wait condition is not met, passing 0U
 *                  waits indefinitely when the environment is an RTOS and returns the kStatus_OSA_Timeout
 *                  immediately. Pass any value for the bare metal.
 * @param bitSet    Flags that wake up the waiting task are obtained by this parameter.
 *
 * @return An USB OSA error code or kStatus_OSA_Success.
 *
 * Example:
   @code
   am_usb_osa_status_t     usbOsaStatus;
   uint32_t             bitSet;
   ...
   usbOsaStatus = USB_OsaEventWait(eventHandle, 0x01U, 0U, 0U, &bitSet);
   @endcode
 *
 */
am_usb_osa_status_t am_usb_osa_event_wait(am_usb_osa_event_handle_t handle,
                                          uint32_t                bit_mask,
                                          uint32_t                flag,
                                          uint32_t                timeout,
                                          uint32_t               *p_bit_set);

/*!
 * @brief Checks an event flag.
 *
 * This function checks for a combination of flags to be set in an event object.
 *
 * @param handle   Pointer to the event object.
 * @param bitMask  Event flags to check.
 * @param bitSet   Flags have been set.
 *
 * @return An USB OSA error code or kStatus_OSA_Success.
 *
 * Example:
   @code
   am_usb_osa_status_t     usbOsaStatus;
   uint32_t             bitSet;
   ...
   usbOsaStatus = USB_OsaEventCheck(eventHandle, 0x01U, &bitSet);
   @endcode
 *
 */
am_usb_osa_status_t am_usb_osa_event_check(am_usb_osa_event_handle_t handle,
                                           uint32_t                bit_mask,
                                           uint32_t               *p_bitSet);

/*!
 * @brief Clears an event flag.
 *
 * This function clears flags of an event object.
 *
 * @param handle    Pointer to the event object
 * @param bitMask   Event flags to be cleared.
 *
 * @return An USB OSA error code or kStatus_OSA_Success.
 *
 * Example:
   @code
   am_usb_osa_status_t     usbOsaStatus;
   ...
   usbOsaStatus = USB_OsaEventClear(eventHandle, 0x01U);
   @endcode
 */
am_usb_osa_status_t am_usb_osa_event_clear(am_usb_osa_event_handle_t handle,
                                           uint32_t                bit_mask);
/* @} */

/*!
 * @name USB OSA Semaphore
 * @{
 */

/*!
 * @brief Creates a semaphore with a given value.
 *
 * This function creates a semaphore and sets the default count.
 *
 * @param handle    It is an out parameter, which is used to return pointer of the semaphore object.
 * @param count     Initializes a value of the semaphore.
 *
 * @return An USB OSA error code or kStatus_OSA_Success.
 *
 * Example:
   @code
   am_usb_osa_sem_handle_t   semHandle;
   am_usb_osa_status_t     usbOsaStatus;
   usbOsaStatus = USB_OsaSemCreate(&semHandle, 1U);
   @endcode
 *
 */
am_usb_osa_status_t am_usb_osa_sem_create(am_usb_osa_sem_handle_t *handle,
                                          uint32_t               count);

/*!
 * @brief Destroys a semaphore object.
 *
 * This function destroys a semaphore object.
 *
 * @param handle    Pointer to the semaphore.
 *
 * @return An USB OSA error code or kStatus_OSA_Success.
 *
 * Example:
   @code
   am_usb_osa_sem_handle_t   semHandle;
   am_usb_osa_status_t     usbOsaStatus;
   ...
   usbOsaStatus = USB_OsaSemDestroy(semHandle);
   @endcode
 *
 */
am_usb_osa_status_t am_usb_osa_sem_destroy(am_usb_osa_sem_handle_t handle);

/*!
 * @brief Posts a semaphore.
 *
 * This function wakes up a task waiting on the semaphore. If a task is not pending, increases the semaphore's
 value.
 *
 * @param handle    Pointer to the semaphore.
 *
 * @return A USB OSA error code or kStatus_OSA_Success.
 *
 * Example:
   @code
   am_usb_osa_sem_handle_t   semHandle;
   am_usb_osa_status_t     usbOsaStatus;
   ...
   usbOsaStatus = USB_OsaSemPost(semHandle);
   @endcode
 *
 */
am_usb_osa_status_t am_usb_osa_sem_post(am_usb_osa_sem_handle_t handle);

/*!
 * @brief Waits on a semaphore.
 *
 * This function checks the semaphore's value. If it is positive, it decreases the semaphore's value and return
 kStatus_OSA_Success.
 *
 * @param handle    Pointer to the semaphore.
 * @param timeout   The maximum number of milliseconds to wait for the semaphore.
 *                  If the wait condition is not met, pass 0U
 *                  waits indefinitely when environment is RTOS. And return kStatus_OSA_Timeout
 *                  immediately for bare metal no matter what value has been passed.
 *
 * @return A USB OSA error code or kStatus_OSA_Success.
 *
 * Example:
   @code
   am_usb_osa_sem_handle_t   semHandle;
   am_usb_osa_status_t     usbOsaStatus;
   ...
   usbOsaStatus = USB_OsaSemWait(semHandle, 0U);
   @endcode
 *
 */
am_usb_osa_status_t am_usb_osa_sem_wait(am_usb_osa_sem_handle_t handle,
                                        uint32_t              timeout);
/* @} */

/*!
 * @name USB OSA Mutex
 * @{
 */

/*!
 * @brief Creates a mutex.
 *
 * This function creates a mutex and sets it to an unlocked status.
 *
 * @param handle    It is out parameter, which is used to return the pointer of the mutex object.
 *
 * @return A USB OSA error code or kStatus_OSA_Success.
 *
 * Example:
   @code
   am_usb_osa_mutex_handle_t mutexHandle;
   am_usb_osa_status_t     usbOsaStatus;
   usbOsaStatus = USB_OsaMutexCreate(&mutexHandle);
   @endcode
 *
 */
am_usb_osa_status_t am_usb_osa_mutex_create(am_usb_osa_mutex_handle_t *handle);

/*!
 * @brief Destroys a mutex.
 *
 * This function destroys a mutex and sets it to an unlocked status.
 *
 * @param handle    Pointer to the mutex.
 *
 * @return A USB OSA error code or kStatus_OSA_Success.
 *
 * Example:
   @code
   am_usb_osa_mutex_handle_t mutexHandle;
   am_usb_osa_status_t     usbOsaStatus;
   ...
   usbOsaStatus = USB_OsaMutexDestroy(mutexHandle);
   @endcode
 *
 */
am_usb_osa_status_t am_usb_osa_mutex_destroy(am_usb_osa_mutex_handle_t handle);

/*!
 * @brief Waits for a mutex and locks it.
 *
 * This function checks the mutex status. If it is unlocked, it locks it and returns the
 * kStatus_OSA_Success. Otherwise, it waits forever to lock in RTOS and returns the
 * kStatus_OSA_Success immediately for bare metal.
 *
 * @param handle    Pointer to the mutex.
 *
 * @return A USB OSA error code or kStatus_OSA_Success.
 *
 * Example:
   @code
   am_usb_osa_mutex_handle_t mutexHandle;
   am_usb_osa_status_t     usbOsaStatus;
   ...
   usbOsaStatus = USB_OsaMutexLock(mutexHandle);
   @endcode
 *
 */
am_usb_osa_status_t am_usb_osa_mutex_lock(am_usb_osa_mutex_handle_t handle);

/*!
 * @brief Unlocks a mutex.
 *
 * This function unlocks a mutex.
 *
 * @param handle    Pointer to the mutex.
 *
 * @return A USB OSA error code or kStatus_OSA_Success.
 *
 * Example:
   @code
   am_usb_osa_mutex_handle_t mutexHandle;
   am_usb_osa_status_t     usbOsaStatus;
   ...
   usbOsaStatus = USB_OsaMutexUnlock(mutexHandle);
   @endcode
 *
 */
am_usb_osa_status_t am_usb_osa_mutex_unlock(am_usb_osa_mutex_handle_t handle);
/* @} */

/*!
 * @name USB OSA Message Queue
 * @{
 */

/*!
 * @brief Creates a message queue.
 *
 * This function creates a message queue.
 *
 * @param handle    It is an out parameter, which is used to return a pointer of the message queue object.
 * @param count     The count of elements in the queue.
 * @param size      Size of every elements in words.
 *
 * @return A USB OSA error code or kStatus_OSA_Success.
 *
 * Example:
   @code
   am_usb_osa_msgq_handle_t  msgqHandle;
   am_usb_osa_status_t     usbOsaStatus;
   usbOsaStatus = USB_OsaMsgqCreate(msgqHandle, 8U, 4U);
   @endcode
 *
 */
am_usb_osa_status_t am_usb_osa_msgq_create(am_usb_osa_msgq_handle_t *handle,
                                           uint32_t                count,
                                           uint32_t                size);

/*!
 * @brief Destroys a message queue.
 *
 * This function destroys a message queue.
 *
 * @param handle    Pointer to a message queue.
 *
 * @return A USB OSA error code or kStatus_OSA_Success.
 *
 * Example:
   @code
   am_usb_osa_msgq_handle_t  msgqHandle;
   am_usb_osa_status_t     usbOsaStatus;
   ...
   usbOsaStatus = USB_OsaMsgqDestroy(msgqHandle);
   @endcode
 *
 */
am_usb_osa_status_t am_usb_osa_msgq_destroy(am_usb_osa_msgq_handle_t handle);

/*!
 * @brief Sends a message.
 *
 * This function sends a message to the tail of the message queue.
 *
 * @param handle    Pointer to a message queue.
 * @param msg       The pointer to a message to be put into the queue.
 *
 * @return A USB OSA error code or kStatus_OSA_Success.
 *
 * Example:
   @code
   am_usb_osa_msgq_handle_t      msgqHandle;
   message_struct_t         message;
   am_usb_osa_status_t         usbOsaStatus;
   ...
   usbOsaStatus = USB_OsaMsgqSend(msgqHandle, &message);
   @endcode
 *
 */
am_usb_osa_status_t am_usb_osa_msgq_send(am_usb_osa_msgq_handle_t handle,
                                         void                  *p_msg);

/*!
 * @brief Receives a message.
 *
 * This function receives a message from the head of the message queue.
 *
 * @param handle    Pointer to a message queue.
 * @param msg       The pointer to save a received message.
 * @param timeout   The maximum number of milliseconds to wait for a message.
 *                  If the wait condition is not met, passing 0U
 *                  waits indefinitely when an environment is RTOS and returns the kStatus_OSA_Timeout
 *                  immediately for bare metal.
 *
 * @return A USB OSA error code or kStatus_OSA_Success.
 *
 * Example:
   @code
   am_usb_osa_msgq_handle_t      msgqHandle;
   message_struct_t         message;
   am_usb_osa_status_t         usbOsaStatus;
   ...
   usbOsaStatus = USB_OsaMsgqRecv(msgqHandle, &message, 0U);
   @endcode
 *
 */
am_usb_osa_status_t am_usb_osa_msgq_recv(am_usb_osa_msgq_handle_t handle,
                                         void                  *p_msg,
                                         uint32_t               timeout);

/*!
 * @brief Checks a message queue and receives a message if the queue is not empty.
 *
 * This function checks a message queue and receives a message if the queue is not empty.
 *
 * @param handle    Pointer to a message queue.
 * @param msg       The pointer to save a received message.
 *
 * @return A USB OSA error code or kStatus_OSA_Success.
 *
 * Example:
   @code
   am_usb_osa_msgq_handle_t      msgqHandle;
   message_struct_t         message;
   am_usb_osa_status_t         usbOsaStatus;
   ...
   usbOsaStatus = USB_OsaMsgqCheck(msgqHandle, &message);
   @endcode
 *
 */
am_usb_osa_status_t am_usb_osa_msgq_check(am_usb_osa_msgq_handle_t handle,
                                          void                  *p_msg);

am_usb_osa_status_t am_usb_osa_memheap_init(void);


/* @} */

#ifdef __cplusplus
}
#endif

#endif /* __AM_USB_OSA_H */
