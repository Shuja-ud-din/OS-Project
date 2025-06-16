#include <sys/time.h>
#include <stddef.h>
#include "utils.h"

double get_time_seconds()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}
