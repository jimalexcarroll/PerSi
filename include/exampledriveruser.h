#ifndef __EXAMPLE_DRIVER_USER_H__
#define __EXAMPLE_DRIVER_USER_H__

#include <linux/ioctl.h>

#define exampledrivermagic 'S'

/* IOCTLs */
#define readcounter   _IOR(exampledrivermagic, 11, int) 
#define resetcounter  _IO(exampledrivermagic, 12)

#endif // __EXAMPLE_DRIVER_USER_H__


