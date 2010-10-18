#ifndef __EXAMPLE_DRIVER_H__
#define __EXAMPLE_DRIVER_H__
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/ioctl.h>
#include<linux/slab.h>
#include<linux/poll.h>
#include<asm/uaccess.h>

#include"exampledriveruser.h"
#include"kerneldebug.h"

/* Driver Functions */

long exampledriver_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);
int exampledriver_open(struct inode *inode, struct file *filp);
int exampledriver_release(struct inode *inode, struct file *filp);
static int __init exampledriver_init(void);
static void __exit exampledriver_exit(void);

/* Data Structures */
static struct file_operations exampledriver_fops =
{
    .owner            = THIS_MODULE,
    .unlocked_ioctl   = exampledriver_ioctl,
    .open             = exampledriver_open,
    .release          = exampledriver_release,
};

struct exampledriver 
{
    struct cdev dev;
};

/* Global Variables */
struct exampledriver exampledriverdevice;

int exampledrivermajor = 0;
int exampledriverminor = 0;
int exampledriverdevices = 1;

#endif //__EXAMPLE_DRIVER_H__



