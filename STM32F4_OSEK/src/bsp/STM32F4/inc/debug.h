
#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>

#ifdef 	DEBUG
#define	DBG(...)  (printf("-D- "),printf(__VA_ARGS__))
#else	  
#define	DBG(...)
#endif

#define INFO(...) (printf("-I- "),printf(__VA_ARGS__))
#define ERR(...)  (printf("-E- "),printf(__VA_ARGS__)) 

#endif  /* __DEBUG_H__ */
