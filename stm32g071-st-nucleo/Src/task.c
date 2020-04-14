#include "config.h"
#include "task.h"

#define THREAD_LED_PRIORITY 26
#define THREAD_LED_STACK_SIZE 256
#define THREAD_LED_TIMESLICE 10

#define THREAD_IWDG_PRIORITY 15
#define THREAD_IWDG_STACK_SIZE 256
#define THREAD_IWDG_TIMESLICE 10

static rt_thread_t tid_led = RT_NULL;
static rt_thread_t tid_feeddog = RT_NULL;

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

static void thread_feeddog_entry(void *parameter)
{
    while (1)
    {
        IWDG_Feed();
        // rt_kprintf("feed dog\r\n");
        rt_thread_mdelay(1000);
    }
}

void task_feeddog(void)
{
    tid_feeddog = rt_thread_create("thread_feeddog",
                            thread_feeddog_entry,
                            RT_NULL,
                            THREAD_IWDG_STACK_SIZE,
                            THREAD_IWDG_PRIORITY,
                            THREAD_IWDG_TIMESLICE);

    if (tid_feeddog != RT_NULL)
    {
        rt_thread_startup(tid_feeddog);
    }
}

MSH_CMD_EXPORT(task_feeddog, feed dog);
