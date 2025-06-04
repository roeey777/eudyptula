// SPDX-License-Identifier: GPL-2.0+

#include <linux/module.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <linux/debugfs.h>
#include <linux/err.h>
#include <asm/page.h>
#include <linux/jiffies.h>
#include <linux/seq_file.h>
#include <linux/mutex.h>

#ifndef UNUSED
#define UNUSED(x) ((void)x)
#endif

#define EUDYPTULA_DIRECTORY_NAME "eudyptula"
#define EUDYPTULA_ID_BUFFER_SIZE 256
#define EUDYPTULA_FOO_BUFFER_SIZE PAGE_SIZE

static const char ID[] = "roeey777";
static const size_t ID_LENGTH = sizeof(ID) / sizeof(*ID);
static const char SECRET[] = "eudyptula";
static const size_t SECRET_LENGTH = sizeof(SECRET) / sizeof(*SECRET);

/* read/write for all */
static const umode_t ID_FILE_MODE = 0666;
/* read/write for root, read for all */
static const umode_t FOO_FILE_MODE = 0644;
/* read for all */
static const umode_t JIFFIES_FILE_MODE = 0444;

static char id_buffer[EUDYPTULA_ID_BUFFER_SIZE];
static DEFINE_MUTEX(foo_mutex);
static char foo_buffer[EUDYPTULA_FOO_BUFFER_SIZE];
static struct dentry *root;

static ssize_t eudyptula_id_read(struct file *fp, char __user *user_buf, size_t length, loff_t *offset);
static ssize_t eudyptula_id_write(struct file *fp, const char __user *user_buf,
				size_t count, loff_t *offset);
static ssize_t eudyptula_foo_read(struct file *fp, char __user *user_buf, size_t length, loff_t *offset);
static ssize_t eudyptula_foo_write(struct file *fp, const char __user *user_buf,
				size_t count, loff_t *offset);
static int show_jiffies(struct seq_file *m, void *priv);
static int open_jiffies(struct inode *inode, struct  file *fp);
static int __init hello_init(void);
static void __exit hello_exit(void);

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("roeey777");
MODULE_DESCRIPTION("eudyptula challange #8 - debugfs");

static const struct file_operations id_fops = {
	.owner =    THIS_MODULE,
	.read  =    eudyptula_id_read,
	.write =    eudyptula_id_write,
};

static const struct file_operations jiffies_fops = {
	.owner   =    THIS_MODULE,
	.open    =    open_jiffies,
	.read    =    seq_read,
	.llseek  =    seq_lseek,
	.release =    single_release,
};

static const struct file_operations foo_fops = {
	.owner =    THIS_MODULE,
	.read  =    eudyptula_foo_read,
	.write =    eudyptula_foo_write,
};

static ssize_t eudyptula_id_read(struct file *fp, char __user *user_buf, size_t length, loff_t *offset)
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

static ssize_t eudyptula_id_write(struct file *fp, const char __user *user_buf,
				size_t count, loff_t *offset)
{
	int status = -EINVAL;

	UNUSED(fp);

	(void)memset(id_buffer, '\0', EUDYPTULA_ID_BUFFER_SIZE);

	/* copy data from userspace */
	status = simple_write_to_buffer(id_buffer,
					EUDYPTULA_ID_BUFFER_SIZE,
					offset,
					user_buf,
					count);
	if (status < 0) {
		pr_err("failed to copy buffer from userspace to kernelspace with error: %d\n", -status);
		return (ssize_t)status;
	}

	if (strncmp(SECRET, id_buffer, EUDYPTULA_ID_BUFFER_SIZE)) {
		pr_warn("The given data (%s) isn't the secret!\n", id_buffer);
		return -EINVAL;
	}

	return (ssize_t)status;
}

static ssize_t eudyptula_foo_read(struct file *fp, char __user *user_buf, size_t length, loff_t *offset)
{
	int status = -EINVAL;

	UNUSED(fp);

	mutex_lock(&foo_mutex);

	/* copy the ID from kernel-space to user-space */
	status = simple_read_from_buffer(user_buf,
					 length,
					 offset,
					 foo_buffer,
					 EUDYPTULA_FOO_BUFFER_SIZE);

	mutex_unlock(&foo_mutex);
	return (ssize_t)status;
}

static ssize_t eudyptula_foo_write(struct file *fp, const char __user *user_buf,
				size_t count, loff_t *offset)
{
	int status = -EINVAL;

	UNUSED(fp);

	mutex_lock(&foo_mutex);
	(void)memset(foo_buffer, '\0', EUDYPTULA_FOO_BUFFER_SIZE);

	/* copy data from userspace */
	status = simple_write_to_buffer(foo_buffer,
					EUDYPTULA_FOO_BUFFER_SIZE,
					offset,
					user_buf,
					count);
	if (status < 0) {
		pr_err("failed to copy buffer from userspace to kernelspace with error: %d\n", -status);
		goto unlock_mutex;
	}

unlock_mutex:
	mutex_unlock(&foo_mutex);
	return (ssize_t)status;
}

static int show_jiffies(struct seq_file *m, void *priv)
{
	UNUSED(priv);

	seq_printf(m, "%lu\n", jiffies);
	return 0;
}

static int open_jiffies(struct inode *inode, struct  file *fp)
{
	UNUSED(inode);

	return single_open(fp, show_jiffies, NULL);
}

static int __init hello_init(void)
{
	int status = -EINVAL;
	struct dentry *retval = NULL;

	pr_info("hello world\n");

	root = debugfs_create_dir(EUDYPTULA_DIRECTORY_NAME, NULL);
	if (IS_ERR_OR_NULL(root)) {
		status = root ? PTR_ERR(root) : -ENODEV;

		if (-ENODEV == PTR_ERR(root)) {
			pr_err("debugfs wasn't enabled in config, please check CONFIG_DEBUG_FS\n");
			return -ENODEV;
		}

		pr_err("Can't create %s debugfs directory, error is: %d\n",
		       EUDYPTULA_DIRECTORY_NAME,
		       status);
		return status;
	}

	retval = debugfs_create_file("id",
				     ID_FILE_MODE,
				     root,
				     NULL,
				     &id_fops);
	if (IS_ERR_OR_NULL(retval)) {
		status = root ? PTR_ERR(retval) : -ENODEV;
		pr_err("Failed to create id file with error %d\n", -status);
		goto error;
	}

	retval = debugfs_create_file("jiffies",
				     JIFFIES_FILE_MODE,
				     root,
				     NULL,
				     &jiffies_fops);
	if (IS_ERR_OR_NULL(retval)) {
		status = root ? PTR_ERR(retval) : -ENODEV;
		pr_err("Failed to create jiffies file with error %d\n", -status);
		goto error;
	}

	retval = debugfs_create_file("foo",
				     FOO_FILE_MODE,
				     root,
				     NULL,
				     &foo_fops);
	if (IS_ERR_OR_NULL(retval)) {
		status = root ? PTR_ERR(retval) : -ENODEV;
		pr_err("Failed to create foo file with error %d\n", -status);
		goto error;
	}

	pr_info("%s module loaded\n", module_name(THIS_MODULE));
	return 0;

error:
	debugfs_remove_recursive(root);
	return status;
}

static void __exit hello_exit(void)
{
	pr_info("goodbye world\n");

	if (!IS_ERR_OR_NULL(root)) {
		debugfs_remove_recursive(root);
		pr_debug("debugfs directory %s was successfully removed\n",
			 EUDYPTULA_DIRECTORY_NAME);
	}
}

