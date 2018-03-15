#ifndef __INPUT_H__
#define __INPUT_H__

#include <stdio.h>
#include <stdarg.h>
#include "os.h"

/*
 * Input callback type definition
 */
typedef void(*CallBackType)(char *Buffer, uint32_t Len);

void Input_GetsAsync(char *Buffer, uint32_t Len, CallBackType CallBack);

#endif /* __INPUT_H__ */
