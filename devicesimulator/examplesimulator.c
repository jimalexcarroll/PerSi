#include "examplesimulator.h"
#include "mapmanageruser.h"

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

void test()
{
    int err;
    persiregister reg;

    reg.address=1;
    reg.value=1;

    err=mapmanager_deviceread(&reg);
    err=mapmanager_devicewrite(&reg);
    err=mapmanager_driverread(&reg);
    err=mapmanager_driverwrite(&reg);

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

    return err; 
}




static void __exit examplesimulator_exit(void)
{
    dev_t dev;

    __TRACE__("examplesimulator_exit\n")
  
    /* Unregister device driver */
    dev = MKDEV(examplesimulatormajor, examplesimulatorminor);
    unregister_chrdev_region(dev, simulators);

    /* Disassociate functions from driver */
    cdev_del(&device.dev); 
}
