// SPDX-License-Identifier: Dual BSD/GPL
#include <linux/bug.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>

MODULE_AUTHOR("Dovhan Maksym");
MODULE_DESCRIPTION("Lab 6: BUG_ON and OOPS");
MODULE_LICENSE("Dual BSD/GPL");

static uint hello_count = 1;
module_param(hello_count, uint, 0444);
MODULE_PARM_DESC(hello_count, "Кількість виводів рядка 'Hello, world!'");

struct hello_event {
	struct list_head list;
	ktime_t time_before;
	ktime_t time_after;
};

static LIST_HEAD(hello_event_list);

static int __init hello_init(void)
{
	uint i;
	struct hello_event *event;
	BUG_ON(hello_count > 10);

	if (hello_count == 0 || (hello_count >= 5 && hello_count <= 10)) {
		pr_warn("Warning: hello_count дорівнює %u\n", hello_count);
	}

	for (i = 0; i < hello_count; i++) {
		event = kmalloc(sizeof(*event), GFP_KERNEL);

		if (i == 4)
			event = NULL;
		event->time_before = ktime_get();
		pr_info("Hello, world!\n");
		event->time_after = ktime_get();
		list_add_tail(&event->list, &hello_event_list);
	}
	return 0;
}

static void __exit hello_exit(void)
{
	struct hello_event *event, *tmp;
	list_for_each_entry_safe(event, tmp, &hello_event_list, list) {
		pr_info("Час події: %lld нс\n", ktime_to_ns(event->time_after) - ktime_to_ns(event->time_before));
		list_del(&event->list);
		kfree(event);
	}
	pr_info("Модуль успішно вивантажено!\n");
}

module_init(hello_init);
module_exit(hello_exit);
