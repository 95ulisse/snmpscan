#ifndef __LOG_H__
#define __LOG_H__

typedef enum {
    L_DEBUG = 0,
    L_INFO = 1,
    L_WARN = 2,
    L_ERROR = 3
} loglevel_t;

void LOG_ENABLE();

void LOG_DISABLE();

void LOG(loglevel_t level, char* format, ...);
void LOG_ERRNO(loglevel_t level, char* format, ...);

#endif
