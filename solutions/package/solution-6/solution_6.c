// SPDX-License-Identifier: GPL-2.0+

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/string.h>

#ifndef UNUSED
#define UNUSED(x) ((void)x)
#endif

#define EUDYPTULA_DEVICE_NAME "eudyptula"
#define EUDYPTULA_MISC_BUFFER_SIZE 256

static const char *ID = "roeey777";
static const size_t ID_LENGTH = sizeof(ID) / sizeof(*ID);
static const char *SECRET = "eudyptula";
static const size_t SECRET_LENGTH = sizeof(SECRET) / sizeof(*SECRET);
static char misc_buffer[EUDYPTULA_MISC_BUFFER_SIZE];

static ssize_t eudyptula_read(struct file *fp, char __user *user_buf, size_t length, loff_t *offset)
{
	int status = -EINVAL;

	UNUSED(fp);

	/* copy the ID from kernel-space to user-space */
	status = simple_read_from_buffer(user_buf,
					 length,
					 offset,
					 ID,
					 ID_LENGTH);

	return (ssize_t)status;
}

static ssize_t eudyptula_write(struct file *fp, const char __user *user_buf,
				size_t count, loff_t *offset)
{
	int status = -EINVAL;

	UNUSED(fp);

	(void)memset(misc_buffer, '\0', EUDYPTULA_MISC_BUFFER_SIZE);

	/* copy data from userspace */
	status = simple_write_to_buffer(misc_buffer,
					EUDYPTULA_MISC_BUFFER_SIZE,
					offset,
					user_buf,
					count);
	if (status < 0) {
		pr_err("failed to copy buffer from userspace to kernelspace with error: %d\n", -status);
		return (ssize_t)status;
	}

	if (strncmp(SECRET, misc_buffer, EUDYPTULA_MISC_BUFFER_SIZE)) {
		pr_warn("The given data (%s) isn't the secret!\n", misc_buffer);
		return -EINVAL;
	}

	return (ssize_t)status;
}

static const struct file_operations eudyptula_fops = {
	.owner =    THIS_MODULE,
	.read  =    eudyptula_read,
	.write =    eudyptula_write,
};

static struct miscdevice eudyptula_misc = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = EUDYPTULA_DEVICE_NAME,
	.fops = &eudyptula_fops,
};

static int __init hello_init(void)
{
	int status = -EINVAL;

	pr_info("hello world\n");

	status = misc_register(&eudyptula_misc);
	if (status < 0) {
		pr_err("misc_register failed to register eudyptula_misc with error: %d\n", -status);
		return status;
	}

	return 0;
}

static void __exit hello_exit(void)
{
	pr_info("goodbye world\n");

	misc_deregister(&eudyptula_misc);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("misc char device - eudyptula challange #6");
