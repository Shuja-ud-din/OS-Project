#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "processor.h"

void run_thread_pool(const char **urls, int url_count, int num_threads, SharedStats *stats);

#endif
