#ifndef SRC_INCLUDE_LOG_H
#define SRC_INCLUDE_LOG_H

typedef enum
{
    LOG_LEVEL_Debug,
    LOG_LEVEL_Info,
    LOG_LEVEL_Warn,
    LOG_LEVEL_Error,
    LOG_LEVEL_Fatal,
    LOG_LEVEL_Fixme
}
LogLevel;

void log_write(LogLevel lvl, const char* file, int line, const char* fmt, ...);

#define log_fixme(fmt, ...) \
    log_write(LOG_LEVEL_Fixme, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

# ifdef DEBUG
# define log_debug(fmt, ...) \
    log_write(LOG_LEVEL_Debug, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
# else
# define log_debug(fmt, ...) \
    do {} while (0);
# endif

#define log_info(fmt, ...) \
    log_write(LOG_LEVEL_Info, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define log_warn(fmt, ...) \
    log_write(LOG_LEVEL_Warn, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define log_error(fmt, ...) \
    log_write(LOG_LEVEL_Error, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define log_fatal(fmt, ...) \
    log_write(LOG_LEVEL_Fatal, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#endif // SRC_INCLUDE_LOG_H
