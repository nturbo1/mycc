#include "log.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#ifdef DEBUG
static const LogLevel logLevel = LOG_LEVEL_Debug;
#else
static const LogLevel logLevel = LOG_LEVEL_Info;
#endif

static const char* lvl_name(LogLevel lvl)
{
    switch (lvl)
    {
        case LOG_LEVEL_Debug:
            return "DEBUG";
        case LOG_LEVEL_Info:
            return "INFO";
        case LOG_LEVEL_Warn:
            return "WARN";
        case LOG_LEVEL_Error:
            return "ERROR";
        case LOG_LEVEL_Fatal:
            return "FATAL";
        case LOG_LEVEL_Fixme:
            return "FIXME";
        default:
            return "INFO";
    }
}

void log_write(LogLevel lvl, const char* file, int line, const char* fmt, ...)
{
    if (lvl < logLevel)
    {
        return;
    }

    const char* lvlname = lvl_name(lvl);

    va_list args;
    va_start(args, fmt);

    fprintf(stderr, "[%s] %s:%d: ", lvlname, file, line);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");

    va_end(args);

    if (lvl == LOG_LEVEL_Fatal)
        abort();
}
