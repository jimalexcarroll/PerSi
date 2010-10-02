/* An example peripheral simulator: a counter
   2 registers: reset and count */


#include "examplesimulator.h"
#include "mapmanageruser.h"
#include "memorymap.h"

MODULE_LICENSE("Dual BSD/GPL");

module_init(examplesimulator_init);
module_exit(examplesimulator_exit);

int examplesimulator_open(struct inode *inode, struct file *filp)
{
    __TRACE__("examplesimulator_open\n")
    filp->private_data = &device;
    return 0;
}




int examplesimulator_release(struct inode *inode, struct file *filp)
{
    __TRACE__("examplesimulator_release\n")
    return 0;
}




void examplesimulator_starttimer()
{
    __TRACE__("examplesimulator_starttimer\n")

    init_timer(&countertimer);

    countertimer.function = examplesimulator_countercallback;
    countertimer.expires = jiffies + HZ; /* one second */
    add_timer(&countertimer);
}




void examplesimulator_countercallback(unsigned long ptr)
{
    int err;
    persiregister resetreg, counterreg;

    __TRACE__("examplesimulator_countercallback\n")

    /* Read reset register */
    resetreg.address = counterreset;
    err = mapmanager_deviceread(&resetreg);

    /* Read counter register */
    counterreg.address = countercount;
    err = mapmanager_deviceread(&counterreg);

   /* If reset register is high, reset the counter to zero */
    if ((resetreg.value && counterresetbit) == bit0)
    {
        counterreg.value=0x0000;
        err = mapmanager_devicewrite(&counterreg);
    }
    /* Else increment the counter */
    else
    {
        counterreg.value++;
        err = mapmanager_devicewrite(&counterreg);
    }

    /* Clear the reset register */
    resetreg.value = 0x0000;
    err = mapmanager_devicewrite(&resetreg);

    /* Start again! */
    examplesimulator_starttimer();
}



static int __init examplesimulator_init(void)
{
    dev_t dev;
    int err;

    __TRACE__("examplesimulator_init\n")

    /* Set device numbers and register device driver*/
    err = alloc_chrdev_region(&dev, examplesimulatorminor, simulators, "examplesimulator");
    examplesimulatormajor=MAJOR(dev);

    if (err!=0) 
    {
        __TRACE2__("Example simulator device number allocation failure - %d %d\n", 
            examplesimulatormajor, examplesimulatorminor)
    }
    else
    {
        __TRACE2__("Example simulator device number - %d %d\n", 
            examplesimulatormajor, examplesimulatorminor)
    }

    /* Associate functions with driver */
    cdev_init(&device.dev,&examplesimulator_fops);
    device.dev.owner = THIS_MODULE;
    device.dev.ops = &examplesimulator_fops;
    cdev_add(&device.dev, dev, 1);

    if (err!=0) 
    {
        __TRACE1__("Example simulator device add failure - %d\n", err)
    }
    else
    {
        __TRACE__("Example simulator device add OK\n")
    }

    /* Start counter */
    examplesimulator_starttimer();

    return err; 
}




static void __exit examplesimulator_exit(void)
{
    dev_t dev;

    __TRACE__("examplesimulator_exit\n")
  
    /* Remove timer */
    del_timer(&countertimer);

    /* Unregister device driver */
    dev = MKDEV(examplesimulatormajor, examplesimulatorminor);
    unregister_chrdev_region(dev, simulators);

    /* Disassociate functions from driver */
    cdev_del(&device.dev); 
}
