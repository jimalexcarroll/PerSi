#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#include "mapmanageruser.h"

int main (int argc, char* argv[])
{
    int filedesc, err, event;
    persiregister reg;

    reg.value=0;
    reg.address=0;

    /* Call driver functions */
    /* Open  */
    filedesc = open("/dev/mapmanager", O_RDWR);

    switch (argc)
    {
        case 1:
	case 2: 
        {
            printf("Usage: persi command addr [value]\n");
            printf("command = r : Read specified register\n");
            printf("command = w : Write specified value to specified register\n");
            break;
        }

        case 3:
        {
            if (argv[1][0]=='r')
	    {
                reg.address = atoi(argv[2]);
                err = ioctl(filedesc, readregister, &reg);
                printf("PerSi READ:\n");
                printf("Address = 0x%08X\n", reg.address);
                printf("Value   = 0x%08X\n", reg.value);
            }
            else
                printf("Incorrect READ usage!\n");

            break;
        }

        case 4:
        {
            if (argv[1][0]=='w')
            {
                reg.address = atoi(argv[2]);
                reg.value = atoi(argv[3]);
                err = ioctl(filedesc, writeregister, &reg);
                printf("PerSi WRITE:\n");
                printf("Address = 0x%08X\n", reg.address);
                printf("Value   = 0x%08X\n", reg.value);
            }
            else
                printf("Incorrect WRITE uage\n");

            break;
        }

        default:
            printf("Incorrect usage!\n");
    }

    /* Close */
    err = close(filedesc);

    return err;
}

