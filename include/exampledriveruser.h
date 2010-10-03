#ifndef __EXAMPLE_DRIVER_USER_H__
#define __EXAMPLE_DRIVER_USER_H__

#include <linux/ioctl.h>

#define exampledrivermagic 'T'

/* IOCTLs */
#define readcounter   _IOR(exampledrivermagic, 1, int) 
#define resetcounter    _IOW(exampledrivermagic, 2, int)

#endif // __EXAMPLE_DRIVER_USER_H__


