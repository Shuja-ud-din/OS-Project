#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "downloader.h"

typedef struct
{
    const char **urls;
    UrlContent *results;
    int url_count;
    int current_index;
    pthread_mutex_t index_mutex;
} ThreadPool;

// Initialize the thread pool
void thread_pool_init(ThreadPool *pool, const char **urls, UrlContent *results, int url_count);

// Start the download process using threads
void thread_pool_start(ThreadPool *pool, int num_threads);

// Destroy the thread pool (free mutexes, etc.)
void thread_pool_destroy(ThreadPool *pool);

#endif
