#include <stdio.h>
#include <stdarg.h>
#include "debug.h"

static int curr_debug_level = 0;

void set_debug_level(int debug_level) {
    curr_debug_level = debug_level;
}

int dprintf(int debug_level, const char *fmt, ...) {
    if (debug_level <= curr_debug_level) {
        va_list args;
        va_start(args, fmt);
        fprintf(stderr, "[DBG%d] ", debug_level);
        vfprintf(stderr, fmt, args);
        va_end(args);
    }
    return 0;
}
