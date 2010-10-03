#ifndef __MAP_MANAGER_EXPORTS_H__
#define __MAP_MANAGER_EXPORTS_H__

#include"mapmanageruser.h"

/* Driver Exports */
int mapmanager_devicewrite(persiregister* reg);
int mapmanager_deviceread(persiregister* reg);
int mapmanager_driverwrite(persiregister* reg);
int mapmanager_driverread(persiregister* reg);

#endif //__MAP_MANAGER_EXPORTS_H__


