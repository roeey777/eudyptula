// SPDX-License-Identifier: GPL-2.0+

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/string.h>
#include <asm/page.h>
#include <linux/jiffies.h>
#include <linux/mutex.h>
#include <linux/kobject.h>

#ifndef UNUSED
#define UNUSED(x) ((void)x)
#endif

#define EUDYPTULA_DIRECTORY_NAME "eudyptula"
#define EUDYPTULA_ID_BUFFER_SIZE 256
#define EUDYPTULA_FOO_BUFFER_SIZE PAGE_SIZE

static const char ID[] = "roeey777";
static const char SECRET[] = "eudyptula";

static char id_buffer[EUDYPTULA_ID_BUFFER_SIZE];
static DEFINE_MUTEX(foo_mutex);
static char foo_buffer[EUDYPTULA_FOO_BUFFER_SIZE];
static size_t foo_occupied_bytes;

static int __init hello_init(void);
static void __exit hello_exit(void);

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("roeey777");
MODULE_DESCRIPTION("eudyptula challange #8 - debugfs");
MODULE_VERSION("0.0.1");

static ssize_t id_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t id_store(struct kobject *kobj,
			struct kobj_attribute *attr, const char *buf, size_t count);
static struct kobj_attribute id_attribute = __ATTR(id, 0644, id_show, id_store);

static ssize_t jiffies_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static struct kobj_attribute jiffies_attribute = __ATTR_RO(jiffies);

static ssize_t foo_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf);
static ssize_t foo_store(struct kobject *kobj,
				struct kobj_attribute *attr, const char *buf, size_t count);
static struct kobj_attribute foo_attribute = __ATTR(foo, 0644, foo_show, foo_store);

static void eudyptula_release(struct kobject *kobj);

static struct attribute *eudyptula_attrs[] = {
	&id_attribute.attr,
	&jiffies_attribute.attr,
	&foo_attribute.attr,
	NULL,
};
ATTRIBUTE_GROUPS(eudyptula);

static const struct kobj_type eudyptula_ktype = {
	.sysfs_ops      = &kobj_sysfs_ops,
	.default_groups = eudyptula_groups,
	.release        = eudyptula_release,
};

static struct kobject eudyptula_kobj;

static ssize_t id_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	UNUSED(kobj);
	UNUSED(attr);

	return scnprintf(buf, PAGE_SIZE, ID);
}

static ssize_t id_store(struct kobject *kobj,
			struct kobj_attribute *attr, const char *buf, size_t count)
{
	ssize_t status = -EINVAL;
	size_t len = min(count, EUDYPTULA_ID_BUFFER_SIZE - 1) + 1;

	UNUSED(kobj);
	UNUSED(attr);

	(void)memset(id_buffer, '\0', EUDYPTULA_ID_BUFFER_SIZE);
	status = strscpy(id_buffer, buf, len);
	if (status < 0) {
		pr_warn("String truncated! (with error: %lu)\n", -status);
		return status;
	}

	if (strncmp(SECRET, id_buffer, EUDYPTULA_ID_BUFFER_SIZE)) {
		pr_warn("The given data (%s) isn't the secret!\n", id_buffer);
		return -EINVAL;
	}

	return count;
}

static ssize_t foo_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	size_t len = min(EUDYPTULA_FOO_BUFFER_SIZE, foo_occupied_bytes);

	UNUSED(kobj);
	UNUSED(attr);

	mutex_lock(&foo_mutex);

	(void)memcpy(buf, foo_buffer, len);
	mutex_unlock(&foo_mutex);

	return len;
}

static ssize_t foo_store(struct kobject *kobj,
				struct kobj_attribute *attr, const char *buf, size_t count)
{
	size_t len = min(EUDYPTULA_FOO_BUFFER_SIZE, count);

	UNUSED(kobj);
	UNUSED(attr);

	mutex_lock(&foo_mutex);

	(void)memset(foo_buffer, '\0', EUDYPTULA_FOO_BUFFER_SIZE);
	(void)memcpy(foo_buffer, buf, len);
	foo_occupied_bytes = len;

	mutex_unlock(&foo_mutex);

	return len;
}

static ssize_t jiffies_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	UNUSED(kobj);
	UNUSED(attr);

	return scnprintf(buf, PAGE_SIZE, "%lu\n", jiffies);
}

static void eudyptula_release(struct kobject *kobj)
{
	pr_debug("kobject release called for %s\n", kobject_name(kobj));
}

static int __init hello_init(void)
{
	int status = -EINVAL;

	pr_info("hello world\n");

	foo_occupied_bytes = 0;

	status = kobject_init_and_add(&eudyptula_kobj,
				      &eudyptula_ktype,
				      kernel_kobj,
				      EUDYPTULA_DIRECTORY_NAME);
	if (status < 0) {
		pr_err("Failed to add kobject with error: %d\n", -status);
		kobject_put(&eudyptula_kobj);
		return -ENOMEM;
	}

	pr_info("%s module loaded\n", module_name(THIS_MODULE));
	return 0;
}

static void __exit hello_exit(void)
{
	kobject_put(&eudyptula_kobj);

	pr_info("goodbye world\n");
}

