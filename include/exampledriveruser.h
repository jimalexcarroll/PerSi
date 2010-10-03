#ifndef __EXAMPLE_DRIVER_USER_H__
#define __EXAMPLE_DRIVER_USER_H__

#include <linux/ioctl.h>

#define exampledrivermagic 'K'

/* IOCTLs */
#define readcounter   _IOR(exampledrivermagic, 1, int) 
#define resetcounter    _IO(exampledrivermagic, 2)

#endif // __EXAMPLE_DRIVER_USER_H__


