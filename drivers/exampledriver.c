/* An example peripheral device driver: 
   Character driver for counter
   Supported APIs, reset count and read count */

#define __PERSI__
// #undef __PERSI__

#ifdef __PERSI__
#include "mapmanagerexports.h"
#endif

#include "exampledriver.h"
#include "memorymap.h"

MODULE_LICENSE("GPL");

module_init(exampledriver_init);
module_exit(exampledriver_exit);

long exampledriver_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    int err = 0;

#ifdef __PERSI__
    persiregister reg;
#endif

    __TRACE1__("exampledriver_ioctl - cmd %d\n", cmd)

    switch (cmd)
    {
        case readcounter:
        {
            __TRACE__("readcounter\n")
 
#ifdef __PERSI__
            reg.address = countercount;

            err = mapmanager_driverread(&reg);
#else
            /* read the counter register using one of the following:
	       unsigned readb(countercount);
               unsigned readw(countercount);
               unsigned readl(countercount); */
#endif

            err = copy_to_user((void*)arg, (void*)&reg.value, sizeof(reg.value));


            break;
        }

        case resetcounter:
        {
            __TRACE__("resetcounter\n")

#ifdef __PERSI__
            reg.address = counterreset;
            reg.value = counterresetbit;

            err = mapmanager_driverwrite(&reg);
#else
            /* write to the counter reset register using one of the following:
	       unsigned writeb(countercount, counterresetbit);
               unsigned writew(countercount, counterresetbit);
               unsigned writel(countercount, counterresetbit); */
#endif

            break;
        }

        default:
            ;

    };

    return err;
}




int exampledriver_open(struct inode *inode, struct file *filp)
{
    __TRACE__("exampledriver_open\n")

    filp->private_data = &exampledriverdevice;

    return 0;
}




int exampledriver_release(struct inode *inode, struct file *filp)
{
    __TRACE__("exampledriver_release\n")

    return 0;
}




static int __init exampledriver_init(void)
{
    dev_t dev;
    int err;

    __TRACE__("exampledriver_init\n")

    /* Set device numbers and register device driver*/
    err = alloc_chrdev_region(&dev, exampledriverminor, exampledriverdevices, "exampledriver");
    exampledrivermajor=MAJOR(dev);

    if (err!=0) 
    {
        __TRACE2__("Example driver device number allocation failure - %d %d\n", 
            exampledrivermajor, exampledriverminor)
    }
    else
    {
        __TRACE2__("Example driver device number - %d %d\n", 
            exampledrivermajor, exampledriverminor)
    }

    /* Associate functions with driver */
    cdev_init(&exampledriverdevice.dev,&exampledriver_fops);
    exampledriverdevice.dev.owner = THIS_MODULE;
    exampledriverdevice.dev.ops = &exampledriver_fops;
    cdev_add(&exampledriverdevice.dev, dev, 1);

    if (err!=0) 
    {
        __TRACE1__("Example driver device add failure - %d\n", err)
    }
    else
    {
        __TRACE__("Example driver device add OK\n")
    }

    return err; 
}




static void __exit exampledriver_exit(void)
{
    dev_t dev;

    __TRACE__("exampledriver_exit\n")
    
    /* Unregister device driver */
    dev = MKDEV(exampledrivermajor, exampledriverminor);
    unregister_chrdev_region(dev, exampledriverdevices);

    /* Disassociate functions from driver */
    cdev_del(&exampledriverdevice.dev); 
}



