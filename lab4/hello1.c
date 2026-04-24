// SPDX-License-Identifier: Dual BSD/GPL
#include "hello1.h"

#include <linux/init.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/module.h>
#include <linux/printk.h>

MODULE_AUTHOR("Dovhan Maksym");
MODULE_DESCRIPTION("Module 1: list and time management");
MODULE_LICENSE("Dual BSD/GPL");

struct hello_event {
  struct list_head list;
  ktime_t time_before;
  ktime_t time_after;
};

static LIST_HEAD(hello_event_list);

void print_hello(void)
{
  struct hello_event *event;

  event = kmalloc(sizeof(*event), GFP_KERNEL);
  if (!event) {
    pr_err("Помилка виділення пам'яті!\n");
    return;
  }

  event->time_before = ktime_get();
  pr_info("Hello, world!\n");
  event->time_after = ktime_get();
  list_add_tail(&event->list, &hello_event_list);
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
  return 0;
}

static void __exit hello1_exit(void)
{
  struct hello_event *event, *tmp;
  s64 elapsed_time;

  list_for_each_entry_safe(event, tmp, &hello_event_list, list) {
    elapsed_time = ktime_to_ns(event->time_after) - ktime_to_ns(event->time_before);
    pr_info("Час друку: %lld нс\n", elapsed_time);
    list_del(&event->list);
    kfree(event);
  }
  pr_info("Модуль hello1 успішно вивантажено!\n");
}

module_init(hello1_init);
module_exit(hello1_exit);

