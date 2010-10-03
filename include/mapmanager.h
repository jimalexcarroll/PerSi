#ifndef __MAP_MANAGER_H__
#define __MAP_MANAGER_H__
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/ioctl.h>
#include<linux/slab.h>
#include<linux/poll.h>
#include<asm/uaccess.h>

#include"mapmanageruser.h"
#include"mapmanagerexports.h"
#include"kerneldebug.h"

/* Driver Functions */

int mapmanager_ioctl(struct inode *inode, struct file *filp,
                 unsigned int cmd, unsigned long arg);
int mapmanager_open(struct inode *inode, struct file *filp);
int mapmanager_release(struct inode *inode, struct file *filp);
static int __init mapmanager_init(void);
static void __exit mapmanager_exit(void);


/* Data Structures */
static struct file_operations mapmanager_fops =
{
    .owner   = THIS_MODULE,
    .ioctl   = mapmanager_ioctl,
    .open    = mapmanager_open,
    .release = mapmanager_release,
};

struct mapmanager 
{
    struct cdev dev;
};

/* Global Variables */
struct mapmanager device;

int mapmanagermajor = 0;
int mapmanagerminor = 0;
int devices = 1;

#define MAPSIZE 0x1000
int *map;
 
#endif //__MAP_MANAGER_H__



