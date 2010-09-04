#ifndef __USER_DEBUG_H__
#define __USER_DEBUG_H__

#include <stdio.h>

#ifdef __DEBUG_TRACE__

#define __TRACE__(a) printf(a);
#define __TRACE1__(a,b) printf(a,b);
#define __TRACE2__(a,b,c) printf(a,b,c);

#else // not __DEBUG_TRACE__

#define __TRACE__(a)
#define __TRACE__(a,b)
#define __TRACE__(a,b,c)

#endif // __DEBUG_TRACE__

#endif // __USER_DEBUG_H__
