#ifndef __EXAMPLE_SIMULATOR_H__
#define __EXAMPLE_SIMULATOR_H__
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/ioctl.h>
#include<linux/slab.h>
#include<linux/poll.h>
#include<linux/timer.h>
#include<asm/uaccess.h>

#include"kerneldebug.h"
#include"mapmanageruser.h"

/* Driver Functions */
int examplesimulator_open(struct inode *inode, struct file *filp);
int examplesimulator_release(struct inode *inode, struct file *filp);
static int __init examplesimulator_init(void);
static void __exit examplesimulator_exit(void);
void examplesimulator_countercallback(unsigned long ptr);
void examplesimulator_starttimer(void);


/* Data Structures */
static struct file_operations examplesimulator_fops =
{
    .owner   = THIS_MODULE,
    .open    = examplesimulator_open,
    .release = examplesimulator_release,
};

struct examplesimulator 
{
    struct cdev dev;
};

/* Global Variables */
struct examplesimulator device;

struct timer_list countertimer;

int examplesimulatormajor = 0;
int examplesimulatorminor = 0;
int simulators  = 1;

extern int mapmanager_devicewrite(persiregister* reg);
extern int mapmanager_deviceread(persiregister* reg);
extern int mapmanager_driverwrite(persiregister* reg);
extern int mapmanager_driverread(persiregister* reg);



#endif //__EXAMPLE_SIMULATOR_H__



