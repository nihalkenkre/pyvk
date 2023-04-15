#include "log.h"
#include <stdio.h>
#include <stdarg.h>

void DEBUG_LOG(const char *fmt, ...)
{
#ifdef DEBUG
    va_list args;
    va_start(args, fmt);
    vfprintf(stdout, fmt, args);
    va_end(args);
#endif
}