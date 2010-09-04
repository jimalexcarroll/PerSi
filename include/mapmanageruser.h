#ifndef __MAP_MANAGER_USER_H__
#define __MAP_MANAGER_USER_H__

#include <linux/ioctl.h>

#define mapmanagermagic 'S'

/* Structures */
typedef struct _persiregister
{
    int address;
    int value;
} persiregister;

/* IOCTLs */
#define readregister   _IOR(mapmanagermagic, 1, persiregister) 
#define writeregister  _IOW(mapmanagermagic, 2, persiregister)

#endif // __MAP_MANAGER_USER_H__


