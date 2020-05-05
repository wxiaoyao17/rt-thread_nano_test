#include "config.h"
#include "task.h"

#define THREAD_LED_STACK_SIZE 256
#define THREAD_LED_PRIORITY 26
#define THREAD_LED_TIMESLICE 10

#define THREAD_IWDG_STACK_SIZE 256
#define THREAD_IWDG_PRIORITY 27
#define THREAD_IWDG_TIMESLICE 10

#define THREAD_UART1_STACK_SIZE 1024
#define THREAD_UART1_PRIORITY 25
#define THREAD_UART1_TIMESLICE 10

#define THREAD_CREATE_STACK_SIZE 256
#define THREAD_CREATE_PRIORITY 24
#define THREAD_CREATE_TIMESLICE 10

#define THREAD_DELETE_STACK_SIZE 256
#define THREAD_DELETE_PRIORITY 24
#define THREAD_DELETE_TIMESLICE 10

static rt_thread_t tid_led_blink = RT_NULL;
static rt_thread_t tid_feed_dog = RT_NULL;
static rt_thread_t tid_uart1_recv = RT_NULL;
static rt_thread_t tid_thread_create = RT_NULL;
static rt_thread_t tid_thread_delete = RT_NULL;

extern rt_sem_t uart1_recv_sem;
extern rt_mq_t uart1_recv_mq;
// extern uint8 g_USART1_RxBuf[];

static void thread_led_blink_entry(void *parameter)
{
    while (1)
    {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        rt_thread_mdelay(500);
    }
}

void task_led_blink(void)
{
    tid_led_blink = rt_thread_create("thread_led_blink",
                            thread_led_blink_entry,
                            RT_NULL,
                            THREAD_LED_STACK_SIZE,
                            THREAD_LED_PRIORITY,
                            THREAD_LED_TIMESLICE);

    if (tid_led_blink != RT_NULL)
    {
        rt_thread_startup(tid_led_blink);
    }
}

MSH_CMD_EXPORT(task_led_blink, task led blink);

static void thread_feed_dog_entry(void *parameter)
{
    while (1)
    {
        IWDG_Feed();
        // rt_kprintf("feed dog\r\n");
        rt_thread_mdelay(1000);
    }
}

void task_feed_dog(void)
{
    tid_feed_dog = rt_thread_create("thread_feed_dog",
                            thread_feed_dog_entry,
                            RT_NULL,
                            THREAD_IWDG_STACK_SIZE,
                            THREAD_IWDG_PRIORITY,
                            THREAD_IWDG_TIMESLICE);

    if (tid_feed_dog != RT_NULL)
    {
        rt_thread_startup(tid_feed_dog);
    }
}

MSH_CMD_EXPORT(task_feed_dog, feed dog);

static void thread_uart1_recv_entry(void *parameter)
{
    rt_err_t ret = RT_EOK;

    while (1)
    {
#if 0 // 信号量方式
        ret = rt_sem_take(uart1_recv_sem, RT_WAITING_FOREVER);
#else // 信息队列方式
        ret = rt_mq_recv(uart1_recv_mq, g_USART1_RxBuf, sizeof(g_USART1_RxBuf), RT_WAITING_FOREVER);
#endif
        if (RT_EOK == ret)
        {
            rt_kprintf("uart1 recv data:%s\n", g_USART1_RxBuf);

            if (strstr((char*)g_USART1_RxBuf, "led_blink") != NULL)
            {
                LED_Blink();
            }
            memset(g_USART1_RxBuf, 0, USART1_RX_BUF_SIZE);
        }
    }
}

void task_uart1_recv(void)
{
#if 0 // 信号量方式
    uart1_recv_sem = rt_sem_create("uart1_recv_sem", 0, RT_IPC_FLAG_FIFO);
    if (uart1_recv_sem != RT_NULL)
    {
        rt_kprintf("Semphore uart1_recv_sem created.\n");
    }
#else // 信息队列方式
    uart1_recv_mq = rt_mq_create("uart1_recv_mq", 64, 10, RT_IPC_FLAG_FIFO);
    if (uart1_recv_mq != RT_NULL)
    {
        rt_kprintf("MessageQueue uart1_recv_mq created.\n");
    }
#endif
    tid_uart1_recv = rt_thread_create("thread_uart1_recv",
                            thread_uart1_recv_entry,
                            RT_NULL,
                            THREAD_UART1_STACK_SIZE,
                            THREAD_UART1_PRIORITY,
                            THREAD_UART1_TIMESLICE);

    if (tid_uart1_recv != RT_NULL)
    {
        rt_thread_startup(tid_uart1_recv);
    }
}

MSH_CMD_EXPORT(task_uart1_recv, uart1 recv);

static void thread_create_entry(void *parameter)
{
    rt_uint32_t count = 0;

    while (1)
    {
        /* 线程1采用低优先级运行，一直打印计数值 */
        rt_kprintf("thread count: %d\n", count++);
        rt_thread_mdelay(1000);
    }
}

void task_create(void)
{
    tid_thread_create = rt_thread_create("thread_create",
                            thread_create_entry,
                            RT_NULL,
                            THREAD_CREATE_STACK_SIZE,
                            THREAD_CREATE_PRIORITY,
                            THREAD_CREATE_TIMESLICE);

    if (tid_thread_create != RT_NULL)
    {
        rt_thread_startup(tid_thread_create);
        rt_kprintf("task create success!\n");
    }
}

static void thread_delete_entry(void *parameter)
{
    if (rt_thread_delete(tid_thread_create) == RT_EOK)
    {
        rt_kprintf("task delete success!\n");
    }
    else
    {
        rt_kprintf("task delete fail!\n");
    }
    
}

void task_delete(void)
{
    tid_thread_delete = rt_thread_create("thread_delete",
                            thread_delete_entry,
                            RT_NULL,
                            THREAD_DELETE_STACK_SIZE,
                            THREAD_DELETE_PRIORITY,
                            THREAD_DELETE_TIMESLICE);

    if (tid_thread_delete != RT_NULL)
    {
        rt_thread_startup(tid_thread_delete);
        // rt_kprintf("task delete success!\n");
    }
}
