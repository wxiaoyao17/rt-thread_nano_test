#include "config.h"
#include "task.h"

#define THREAD_LED_PRIORITY 26
#define THREAD_LED_STACK_SIZE 256
#define THREAD_LED_TIMESLICE 10

#define THREAD_PRIORITY 25
#define THREAD_STACK_SIZE 512
#define THREAD_TIMESLICE 5

static rt_thread_t tid_led = RT_NULL;
static rt_thread_t tid1 = RT_NULL;

static void thread_led_entry(void *parameter)
{
    while (1)
    {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        rt_thread_mdelay(500);
    }
}

void task_led_blink(void)
{
    tid_led = rt_thread_create("thread_led_blink",
                            thread_led_entry,
                            RT_NULL,
                            THREAD_LED_STACK_SIZE,
                            THREAD_LED_PRIORITY,
                            THREAD_LED_TIMESLICE);

    if (tid_led != RT_NULL)
    {
        rt_thread_startup(tid_led);
    }
}

MSH_CMD_EXPORT(task_led_blink, task led blink);

static void thread1_entry(void *parameter)
{
    rt_uint32_t count = 0;

    while (1)
    {
        rt_kprintf("thread1 count: %d\n", count++);
        rt_thread_mdelay(500);
    }
}

static char thread2_stack[1024];
static struct rt_thread thread2;
static void thread2_entry(void *param)
{
    rt_uint32_t count = 0;

    for (count = 0; count < 10; count++)
    {
        rt_kprintf("thread2 count: %d\n", count);
    }
    rt_kprintf("thread2 exit\n");
}

int task_init(void)
{
    tid1 = rt_thread_create("thread1",
                            thread1_entry,
                            RT_NULL,
                            THREAD_STACK_SIZE,
                            THREAD_PRIORITY,
                            THREAD_TIMESLICE);

    if (tid1 != RT_NULL)
    {
        rt_thread_startup(tid1);
    }

    rt_thread_mdelay(1000);

    rt_thread_init(&thread2,
                   "thread2",
                   thread2_entry,
                   RT_NULL,
                   &thread2_stack[0],
                   sizeof(thread2_stack),
                   THREAD_PRIORITY - 1,
                   THREAD_TIMESLICE);
    rt_thread_startup(&thread2);

    return 0;
}

MSH_CMD_EXPORT(task_init, task init);
