#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "thread_pool.h"

// Thread worker function
static void *thread_worker(void *arg)
{
    ThreadPool *pool = (ThreadPool *)arg;

    while (1)
    {
        int index;

        // Lock and get next index
        pthread_mutex_lock(&pool->index_mutex);
        if (pool->current_index >= pool->url_count)
        {
            pthread_mutex_unlock(&pool->index_mutex);
            break;
        }
        index = pool->current_index++;
        pthread_mutex_unlock(&pool->index_mutex);

        // Download the URL
        pool->results[index].url = strdup(pool->urls[index]);
        pool->results[index].content = download_text(pool->urls[index]);

        if (!pool->results[index].content)
        {
            fprintf(stderr, "Download failed for: %s\n", pool->urls[index]);
        }
    }

    return NULL;
}

void thread_pool_init(ThreadPool *pool, const char **urls, UrlContent *results, int url_count)
{
    pool->urls = urls;
    pool->results = results;
    pool->url_count = url_count;
    pool->current_index = 0;
    pthread_mutex_init(&pool->index_mutex, NULL);
}

void thread_pool_start(ThreadPool *pool, int num_threads)
{
    pthread_t *threads = malloc(sizeof(pthread_t) * num_threads);

    for (int i = 0; i < num_threads; i++)
    {
        pthread_create(&threads[i], NULL, thread_worker, pool);
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    free(threads);
}

void thread_pool_destroy(ThreadPool *pool)
{
    pthread_mutex_destroy(&pool->index_mutex);
}
