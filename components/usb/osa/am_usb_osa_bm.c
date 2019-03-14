/**
 * \file
 * \brief     USB
 *
 * \internal
 * \par Modification History
 * - 1.00 16-9-27  bob, first implementation.
 * \endinternal
 */
#include "am_int.h"
#include "am_usb.h"
#include "am_memheap.h"
#include "am_usb_osa_bm.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define __USB_OSA_BM_EVENT_COUNT (2U)
#define __USB_OSA_BM_SEM_COUNT   (1U)
#define __USB_OSA_BM_MSGQ_COUNT  (1U)
#define __USB_OSA_BM_MSG_COUNT   (8U)
#define __USB_OSA_BM_MSG_SIZE    (4U)

/* BM Event status structure */
typedef struct _usb_osa_event
{
    uint32_t value;   /* Event mask */
    uint32_t flag;    /* Event flags, includes auto clear flag */
    uint8_t  is_used; /* Is used */
} usb_osa_event_t;

/* BM semaphore status structure */
typedef struct _usb_osa_sem
{
    uint32_t value;   /* Semaphore count */
    uint8_t  is_used; /* Is used */
} usb_osa_sem_t;

/* BM msg status structure */
typedef struct _usb_osa_msg
{
    uint32_t msg[__USB_OSA_BM_MSG_SIZE]; /* Message entity pointer */
} usb_osa_msg_t;

/* BM msgq status structure */
typedef struct _usb_osa_msgq
{
    usb_osa_msg_t msgs[__USB_OSA_BM_MSG_COUNT]; /* Message entity list */
    uint32_t count;                             /* Max message entity count */
    uint32_t msg_size;                          /* Size of each message */
    uint32_t msg_count;                         /* Valid messages */
    uint32_t index;                             /* The first empty message entity index */
    uint32_t current;                           /* The vaild message index */
    uint8_t  is_used;                           /* Is used */
} usb_osa_msgq_t;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static am_memheap_t __g_usb_memheap;
static uint8_t      __g_usb_memheap_buf[AM_USB_MEMHEAP_SIZE];
USB_GLOBAL static usb_osa_sem_t   s_UsbBmSemStruct[__USB_OSA_BM_SEM_COUNT];
USB_GLOBAL static usb_osa_event_t s_UsbBmEventStruct[__USB_OSA_BM_EVENT_COUNT];
USB_GLOBAL static usb_osa_msgq_t  s_UsbBmMsgqStruct[__USB_OSA_BM_MSGQ_COUNT];

/*******************************************************************************
 * Code
 ******************************************************************************/

void *am_usb_osa_memory_allocate(uint32_t length)
{
    void *p        = (void *)am_memheap_alloc(&__g_usb_memheap,length);
    uint8_t *temp  = (uint8_t *)p;
    uint32_t count = 0;

    if (p)
    {
        for (count = 0U; count < length; count++)
        {
            temp[count] = 0U;
        }
    }
    return p;
}

void am_usb_osa_memory_free(void *p)
{
	am_memheap_free(p);
}

void am_usb_osa_enter_critical(uint8_t *sr)
{
	*sr = am_int_cpu_lock();
}

void am_usb_osa_exit_critical(uint8_t sr)
{
	am_int_cpu_unlock(sr);
}

am_usb_osa_status_t am_usb_osa_event_create(am_usb_osa_event_handle_t *handle, uint32_t flag)
{
    usb_osa_event_t *event = NULL;
    uint32_t i;
    AM_USB_OSA_SR_ALLOC();

    if (!handle)
    {
        return AM_USB_OSA_STATUS_ERROR;
    }

    AM_USB_OSA_ENTER_CRITICAL();
    for (i = 0; i < __USB_OSA_BM_EVENT_COUNT; i++)
    {
        if (0 == s_UsbBmEventStruct[i].is_used)
        {
            event = &s_UsbBmEventStruct[i];
            break;
        }
    }

    if (NULL == event)
    {
        AM_USB_OSA_EXIT_CRITICAL();
        return AM_USB_OSA_STATUS_ERROR;
    }

    event->value = 0U;
    event->flag = flag;
    event->is_used = 1;
    *handle = event;
    AM_USB_OSA_EXIT_CRITICAL();
    return AM_USB_OSA_STATUS_SUCCESS;
}

am_usb_osa_status_t am_usb_osa_event_destroy(am_usb_osa_event_handle_t handle)
{
    usb_osa_event_t *event = (usb_osa_event_t *)handle;
    AM_USB_OSA_SR_ALLOC();

    if (handle)
    {
        AM_USB_OSA_ENTER_CRITICAL();
        event->is_used = 0;
        AM_USB_OSA_EXIT_CRITICAL();
        return AM_USB_OSA_STATUS_SUCCESS;
    }
    return AM_USB_OSA_STATUS_ERROR;
}

am_usb_osa_status_t am_usb_osa_event_set(am_usb_osa_event_handle_t handle, uint32_t bitMask)
{
    usb_osa_event_t *event = (usb_osa_event_t *)handle;
    AM_USB_OSA_SR_ALLOC();

    if (handle)
    {
        AM_USB_OSA_ENTER_CRITICAL();
        event->value |= bitMask;
        AM_USB_OSA_EXIT_CRITICAL();
        return AM_USB_OSA_STATUS_SUCCESS;
    }
    return AM_USB_OSA_STATUS_ERROR;
}

am_usb_osa_status_t am_usb_osa_event_wait(
    am_usb_osa_event_handle_t handle, uint32_t bitMask, uint32_t flag, uint32_t timeout, uint32_t *bitSet)
{
    usb_osa_event_t *event = (usb_osa_event_t *)handle;
    uint32_t bits;
    AM_USB_OSA_SR_ALLOC();

    if (handle)
    {
        AM_USB_OSA_ENTER_CRITICAL();
        bits = event->value & bitMask;
        if (flag)
        {
            if (bits != bitMask)
            {
                AM_USB_OSA_EXIT_CRITICAL();
                return AM_USB_OSA_STATUS_TIME_OUT;
            }
        }
        else
        {
            if (!bits)
            {
                AM_USB_OSA_EXIT_CRITICAL();
                return AM_USB_OSA_STATUS_TIME_OUT;
            }
        }
        if (bitSet)
        {
            *bitSet = bits;
        }
        if (event->flag)
        {
            event->value &= ~bits;
        }
        AM_USB_OSA_EXIT_CRITICAL();
        return AM_USB_OSA_STATUS_SUCCESS;
    }
    return AM_USB_OSA_STATUS_ERROR;
}

am_usb_osa_status_t am_usb_osa_event_check(am_usb_osa_event_handle_t handle, uint32_t bitMask, uint32_t *bitSet)
{
    usb_osa_event_t *event = (usb_osa_event_t *)handle;
    uint32_t bits;
    AM_USB_OSA_SR_ALLOC();

    if (handle)
    {
        AM_USB_OSA_ENTER_CRITICAL();
        bits = event->value & bitMask;

        if (!bits)
        {
            AM_USB_OSA_EXIT_CRITICAL();
            return AM_USB_OSA_STATUS_ERROR;
        }

        if (bitSet)
        {
            *bitSet = bits;
        }
        AM_USB_OSA_EXIT_CRITICAL();
        return AM_USB_OSA_STATUS_SUCCESS;
    }
    return AM_USB_OSA_STATUS_ERROR;
}

am_usb_osa_status_t am_usb_osa_event_clear(am_usb_osa_event_handle_t handle, uint32_t bitMask)
{
    usb_osa_event_t *event = (usb_osa_event_t *)handle;
    uint32_t bits;
    AM_USB_OSA_SR_ALLOC();

    if (handle)
    {
        AM_USB_OSA_ENTER_CRITICAL();
        bits = event->value & bitMask;
        event->value &= ~bits;
        AM_USB_OSA_EXIT_CRITICAL();
        return AM_USB_OSA_STATUS_SUCCESS;
    }
    return AM_USB_OSA_STATUS_ERROR;
}

am_usb_osa_status_t am_usb_osa_sem_create(am_usb_osa_sem_handle_t *handle, uint32_t count)
{
    usb_osa_sem_t *sem = NULL;
    uint32_t i;
    AM_USB_OSA_SR_ALLOC();

    if (!handle)
    {
        return AM_USB_OSA_STATUS_ERROR;
    }

    AM_USB_OSA_ENTER_CRITICAL();
    for (i = 0; i < __USB_OSA_BM_SEM_COUNT; i++)
    {
        if (0 == s_UsbBmSemStruct[i].is_used)
        {
            sem = &s_UsbBmSemStruct[i];
            break;
        }
    }
    if (NULL == sem)
    {
        AM_USB_OSA_EXIT_CRITICAL();
        return AM_USB_OSA_STATUS_ERROR;
    }

    sem->value = count;
    sem->is_used = 1;
    *handle = sem;
    AM_USB_OSA_EXIT_CRITICAL();
    return AM_USB_OSA_STATUS_SUCCESS;
}

am_usb_osa_status_t am_usb_osa_sem_destroy(am_usb_osa_sem_handle_t handle)
{
    usb_osa_sem_t *sem = (usb_osa_sem_t *)handle;
    AM_USB_OSA_SR_ALLOC();

    if (handle)
    {
        AM_USB_OSA_ENTER_CRITICAL();
        sem->is_used = 0;
        AM_USB_OSA_EXIT_CRITICAL();
        return AM_USB_OSA_STATUS_SUCCESS;
    }
    return AM_USB_OSA_STATUS_ERROR;
}

am_usb_osa_status_t am_usb_osa_sem_post(am_usb_osa_sem_handle_t handle)
{
    usb_osa_sem_t *sem = (usb_osa_sem_t *)handle;
    AM_USB_OSA_SR_ALLOC();

    if (!handle)
    {
        return AM_USB_OSA_STATUS_ERROR;
    }

    AM_USB_OSA_ENTER_CRITICAL();
    sem->value++;
    AM_USB_OSA_EXIT_CRITICAL();
    return AM_USB_OSA_STATUS_SUCCESS;
}

am_usb_osa_status_t am_usb_osa_sem_wait(am_usb_osa_sem_handle_t handle, uint32_t timeout)
{
    usb_osa_sem_t *sem = (usb_osa_sem_t *)handle;
    AM_USB_OSA_SR_ALLOC();

    if (!handle)
    {
        return AM_USB_OSA_STATUS_ERROR;
    }

    AM_USB_OSA_ENTER_CRITICAL();
    if (sem->value)
    {
        sem->value--;
    }
    else
    {
        AM_USB_OSA_EXIT_CRITICAL();
        return AM_USB_OSA_STATUS_TIME_OUT;
    }
    AM_USB_OSA_EXIT_CRITICAL();
    return AM_USB_OSA_STATUS_SUCCESS;
}

am_usb_osa_status_t am_usb_osa_mutex_create(am_usb_osa_mutex_handle_t *handle)
{
    if (!handle)
    {
        return AM_USB_OSA_STATUS_ERROR;
    }
    *handle = (am_usb_osa_mutex_handle_t)0xFFFF0000U;
    return AM_USB_OSA_STATUS_SUCCESS;
}

am_usb_osa_status_t am_usb_osa_mutex_destroy(am_usb_osa_mutex_handle_t handle)
{
    return AM_USB_OSA_STATUS_SUCCESS;
}
am_usb_osa_status_t am_usb_osa_mutex_lock(am_usb_osa_mutex_handle_t handle)
{
    return AM_USB_OSA_STATUS_SUCCESS;
}
am_usb_osa_status_t am_usb_osa_mutex_unlock(am_usb_osa_mutex_handle_t handle)
{
    return AM_USB_OSA_STATUS_SUCCESS;
}

am_usb_osa_status_t am_usb_osa_msgq_create(am_usb_osa_msgq_handle_t *handle, uint32_t count, uint32_t size)
{
    usb_osa_msgq_t *msgq = NULL;
    uint32_t i;
    AM_USB_OSA_SR_ALLOC();

    if (!handle)
    {
        return AM_USB_OSA_STATUS_ERROR;
    }
    AM_USB_OSA_ENTER_CRITICAL();

    for (i = 0; i < __USB_OSA_BM_MSGQ_COUNT; i++)
    {
        if (0 == s_UsbBmMsgqStruct[i].is_used)
        {
            msgq = &s_UsbBmMsgqStruct[i];
            break;
        }
    }
    if ((NULL == msgq) || (count > __USB_OSA_BM_MSG_COUNT) || (size > __USB_OSA_BM_MSG_SIZE))
    {
        AM_USB_OSA_EXIT_CRITICAL();
        return AM_USB_OSA_STATUS_ERROR;
    }
    msgq->count = count;
    msgq->msg_size = size;
    msgq->msg_count = 0U;
    msgq->index = 0U;
    msgq->current = 0U;
    msgq->is_used = 1;
    *handle = msgq;
    AM_USB_OSA_EXIT_CRITICAL();
    return AM_USB_OSA_STATUS_SUCCESS;
}

am_usb_osa_status_t am_usb_osa_msgq_destroy(am_usb_osa_msgq_handle_t handle)
{
    usb_osa_msgq_t *msgq = (usb_osa_msgq_t *)handle;
    AM_USB_OSA_SR_ALLOC();

    if (!handle)
    {
        return AM_USB_OSA_STATUS_ERROR;
    }
    AM_USB_OSA_ENTER_CRITICAL();
    msgq->is_used = 0;
    AM_USB_OSA_EXIT_CRITICAL();
    return AM_USB_OSA_STATUS_SUCCESS;
}

am_usb_osa_status_t am_usb_osa_msgq_send(am_usb_osa_msgq_handle_t handle, void *msg)
{
    usb_osa_msgq_t *msgq = (usb_osa_msgq_t *)handle;
    usb_osa_msg_t *msgEntity;
    uint32_t *p;
    uint32_t *q;
    uint32_t count;
    AM_USB_OSA_SR_ALLOC();

    if (!handle)
    {
        return AM_USB_OSA_STATUS_ERROR;
    }
    AM_USB_OSA_ENTER_CRITICAL();
    if (msgq->msg_count >= msgq->count)
    {
        AM_USB_OSA_EXIT_CRITICAL();
        return AM_USB_OSA_STATUS_ERROR;
    }

    msgEntity = &msgq->msgs[msgq->index];
    p = (uint32_t *)&msgEntity->msg[0];
    q = (uint32_t *)msg;

    for (count = 0U; count < msgq->msg_size; count++)
    {
        p[count] = q[count];
    }

    if (0U == msgq->msg_count)
    {
        msgq->current = msgq->index;
    }

    msgq->msg_count++;
    msgq->index++;
    msgq->index = msgq->index % msgq->count;

    AM_USB_OSA_EXIT_CRITICAL();

    return AM_USB_OSA_STATUS_SUCCESS;
}

am_usb_osa_status_t am_usb_osa_msgq_recv(am_usb_osa_msgq_handle_t handle, void *msg, uint32_t timeout)
{
    usb_osa_msgq_t *msgq = (usb_osa_msgq_t *)handle;
    usb_osa_msg_t *msgEntity;
    uint32_t *p;
    uint32_t *q;
    uint32_t count;
    AM_USB_OSA_SR_ALLOC();

    if (!handle)
    {
        return AM_USB_OSA_STATUS_ERROR;
    }
    AM_USB_OSA_ENTER_CRITICAL();
    if (msgq->msg_count < 1U)
    {
        AM_USB_OSA_EXIT_CRITICAL();
        return AM_USB_OSA_STATUS_TIME_OUT;
    }

    msgEntity = &msgq->msgs[msgq->current];
    q = (uint32_t *)&msgEntity->msg[0];
    p = (uint32_t *)msg;

    for (count = 0U; count < msgq->msg_size; count++)
    {
        p[count] = q[count];
    }

    msgq->msg_count--;
    msgq->current++;
    msgq->current = msgq->current % msgq->count;

    AM_USB_OSA_EXIT_CRITICAL();

    return AM_USB_OSA_STATUS_SUCCESS;
}

am_usb_osa_status_t am_usb_osa_msgq_check(am_usb_osa_msgq_handle_t handle, void *msg)
{
    usb_osa_msgq_t *msgq = (usb_osa_msgq_t *)handle;
    uint32_t msgCount;
    AM_USB_OSA_SR_ALLOC();

    if (!handle)
    {
        return AM_USB_OSA_STATUS_ERROR;
    }

    AM_USB_OSA_ENTER_CRITICAL();
    msgCount = msgq->msg_count;
    AM_USB_OSA_EXIT_CRITICAL();

    if (msgCount)
    {
        if (AM_USB_OSA_STATUS_SUCCESS == am_usb_osa_msgq_recv(msgq, msg, 0U))
        {
            return AM_USB_OSA_STATUS_SUCCESS;
        }
    }

    return AM_USB_OSA_STATUS_ERROR;
}

am_usb_osa_status_t am_usb_osa_memheap_init(void)
{
    am_memheap_init(&__g_usb_memheap,
                    "ametal_usb",
                     __g_usb_memheap_buf,
                     AM_USB_MEMHEAP_SIZE);

    return AM_USB_OSA_STATUS_SUCCESS;
}
