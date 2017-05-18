#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

#include "log.h"

static int logging_enabled = 0;

static char* loglevel_names[] = { "DEBUG", "INFO", "WARN", "ERROR" };

#define FORMAT_STRING(format, args, buf)                    \
    do {                                                    \
        va_start(args, format);                             \
        int size = vsnprintf(NULL, 0, format, args);        \
        va_end(args);                                       \
                                                            \
        if (size < 0) {                                     \
            return;                                         \
        }                                                   \
                                                            \
        buf = (char*)malloc(size + 1);                      \
        if (buf == NULL) {                                  \
            return;                                         \
        }                                                   \
                                                            \
        va_start(args, format);                             \
        size = vsnprintf(buf, size + 1, format, args);      \
        va_end(args);                                       \
                                                            \
        if (size < 0) {                                     \
            free(buf);                                      \
            return;                                         \
        }                                                   \
    } while (0)

void LOG_ENABLE() {
    logging_enabled = 1;
}

void LOG_DISABLE() {
    logging_enabled = 0;
}

void LOG(loglevel_t level, char* format, ...) {
    if (logging_enabled) {
        va_list args;
        char* formatted_string;
        FORMAT_STRING(format, args, formatted_string);
        printf("[ %5s ] %s\n", loglevel_names[level], formatted_string);
        free(formatted_string);
        fflush(stdout);
    }
}

void LOG_ERRNO(loglevel_t level, char* format, ...) {
    if (logging_enabled) {
        va_list args;
        char* formatted_string;
        int original_errno = errno;
        FORMAT_STRING(format, args, formatted_string);
        printf("[ %5s ] %s: %s (%d).\n", loglevel_names[level], formatted_string, strerror(original_errno), original_errno);
        free(formatted_string);
        fflush(stdout);
    }
}
