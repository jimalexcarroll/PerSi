#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#include "exampledriveruser.h"

int main (int argc, char* argv[])
{
    int filedesc, err, count;

    /* Call driver functions */
    /* Open  */
    filedesc = open("/dev/exampledriver", O_RDWR);

    /* Display usage */
    printf("Usage: counter [0]\n");
    printf("counter   : Reads counter\n");
    printf("counter 0 : Resets counter\n");

    switch (argc)
    {
        case 1:
        {
            err = ioctl(filedesc, readcounter, &count);

            printf("\nCurrent count = %d\n", count);

            break;
        }
	case 2: 
        {
            if (argv[1][0]=='0')
            {
                err = ioctl(filedesc, resetcounter, &count);

                printf("\nCounter reset!\n");
            }
            else
                printf("Incorrect RESET usage\n");

           break;
        }

        default:
            printf("Incorrect usage!\n");
    }

    /* Close */
    err = close(filedesc);

    return err;
}

