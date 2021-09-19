// SPDX-License-Identifier: MIT

#include <linux/module.h>
#include <linux/init.h>

static int __init hello_init(void)
{
	pr_info("hello world\n");

	return 0;
}

static void __exit hello_exit(void)
{
	pr_info("goodbye world\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("MIT");
MODULE_DESCRIPTION("Hello World module - eudyptula challange #4");
