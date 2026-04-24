// SPDX-License-Identifier: Dual BSD/GPL
#include "hello1.h"

#include <linux/init.h>
#include <linux/printk.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

MODULE_AUTHOR("Dovhan Maksym");
MODULE_DESCRIPTION("Module 2: parameter parsing");
MODULE_LICENSE("Dual BSD/GPL");

static uint hello_count = 1;
module_param(hello_count, uint, 0444);
MODULE_PARM_DESC(hello_count, "Кількість виводів рядка 'Hello, world!'");

static int __init hello2_init(void)
{
  uint i;

  if (hello_count == 0 || (hello_count >= 5 && hello_count <= 10)) {
    pr_warn("Warning: hello_count дорівнює %u\n", hello_count);
  } else if (hello_count > 10) {
    pr_err("Error: hello_count занадто велике! (%u). Модуль не завантажено\n", hello_count);
    return -EINVAL;
  }

  for (i = 0; i < hello_count; i++)
    print_hello();

  return 0;
}

static void __exit hello2_exit(void)
{
  pr_info("Модуль hello2 успішно вивантажено!\n");
}

module_init(hello2_init);
module_exit(hello2_exit);

