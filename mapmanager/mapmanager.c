#include "mapmanager.h"

MODULE_LICENSE("GPL");

module_init(mapmanager_init);
module_exit(mapmanager_exit);

int mapmanager_devicewrite(persiregister* reg)
{
    __TRACE__("mapmanager_devicewrite\n")

    map[reg->address] = reg->value;

    return 0;
}




int mapmanager_deviceread(persiregister* reg)
{
    __TRACE__("mapmanager_deviceread\n")

    reg->value = map[reg->address];

    return 0;
}




int mapmanager_driverwrite(persiregister* reg)
{
    __TRACE__("mapmanager_driverwrite\n")

    map[reg->address] = reg->value;

    return 0;
}




int mapmanager_driverread(persiregister* reg)
{
    __TRACE__("mapmanager_driverread\n")

    reg->value = map[reg->address];

    return 0;
}




long mapmanager_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    int err = 0;
    persiregister reg;

    __TRACE1__("mapmanager_ioctl - cmd %d\n", cmd)

    switch (cmd)
    {
        case readregister:
        {
            __TRACE__("readregister\n")
 
            err = copy_from_user((void*)&reg, (void*)arg, sizeof(persiregister));

            reg.value = map[reg.address];

            err = copy_to_user((void*)arg, (void*)&reg, sizeof(persiregister));

            break;
        }

        case writeregister:
        {
            __TRACE__("writeregister\n")
 
            err = copy_from_user((void*)&reg, (void*)arg, sizeof(persiregister));

            map[reg.address]=reg.value;

            break;
        }

        default:
            ;

    };

    return err;
}




int mapmanager_open(struct inode *inode, struct file *filp)
{
    __TRACE__("mapmanager_open\n")

    filp->private_data = &device;

    return 0;
}




int mapmanager_release(struct inode *inode, struct file *filp)
{
    __TRACE__("mapmanager_release\n")

    return 0;
}




static int __init mapmanager_init(void)
{
    dev_t dev;
    int err, count;

    __TRACE__("mapmanager_init\n")

    /* Set device numbers and register device driver*/
    err = alloc_chrdev_region(&dev, mapmanagerminor, devices, "mapmanager");
    mapmanagermajor=MAJOR(dev);

    if (err!=0) 
    {
        __TRACE2__("Map manager device number allocation failure - %d %d\n", 
            mapmanagermajor, mapmanagerminor)
    }
    else
    {
        __TRACE2__("Map manager device number - %d %d\n", 
            mapmanagermajor, mapmanagerminor)
    }

    /* Associate functions with driver */
    cdev_init(&device.dev,&mapmanager_fops);
    device.dev.owner = THIS_MODULE;
    device.dev.ops = &mapmanager_fops;
    cdev_add(&device.dev, dev, 1);

    if (err!=0) 
    {
        __TRACE1__("Map manager device add failure - %d\n", err)
    }
    else
    {
        __TRACE__("Map manager device add OK\n")
    }

    /* Initalise memory map */
    map = kmalloc(MAPSIZE,  GFP_KERNEL);

    for (count=0; count<MAPSIZE; count++)
       map[count]=0;  


    return err; 
}




static void __exit mapmanager_exit(void)
{
    dev_t dev;

    __TRACE__("mapmanager_exit\n")
    
    kfree(map);

    /* Unregister device driver */
    dev = MKDEV(mapmanagermajor, mapmanagerminor);
    unregister_chrdev_region(dev, devices);

    /* Disassociate functions from driver */
    cdev_del(&device.dev); 
}



EXPORT_SYMBOL(mapmanager_devicewrite);
EXPORT_SYMBOL(mapmanager_deviceread);
EXPORT_SYMBOL(mapmanager_driverwrite);
EXPORT_SYMBOL(mapmanager_driverread);



