#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "thread_pool.h"
#include "downloader.h"
#include "processor.h"

typedef struct
{
    const char **urls;
    int start;
    int end;
    SharedStats *stats;
} ThreadTask;

static void *process_urls(void *arg)
{
    ThreadTask *task = (ThreadTask *)arg;

    for (int i = task->start; i < task->end; i++)
    {
        UrlContent item = {0};
        item.url = strdup(task->urls[i]);
        item.content = download_text(task->urls[i]);

        if (!item.content)
        {
            fprintf(stderr, "Failed to download: %s\n", item.url);
            free(item.url);
            continue;
        }

        int words = count_words(item.content);
        int sentences = count_sentences(item.content);

        CharFrequency local_freq = {0};
        analyze_character_frequency(&item, 1, &local_freq);

        // Lock before writing shared data
        pthread_mutex_lock(&task->stats->lock);

        task->stats->word_counts[i].url = item.url;
        task->stats->word_counts[i].word_count = words;

        task->stats->sentence_counts[i].url = item.url;
        task->stats->sentence_counts[i].sentence_count = sentences;

        for (int j = 0; j < 26; j++)
        {
            task->stats->frequency.frequencies[j] += local_freq.frequencies[j];
        }

        pthread_mutex_unlock(&task->stats->lock);

        free(item.content); // content freed here, url is stored in shared stats
    }

    return NULL;
}

void run_thread_pool(const char **urls, int url_count, int num_threads, SharedStats *stats)
{
    pthread_t *threads = malloc(sizeof(pthread_t) * num_threads);
    ThreadTask *tasks = malloc(sizeof(ThreadTask) * num_threads);

    int chunk_size = (url_count + num_threads - 1) / num_threads;

    for (int i = 0; i < num_threads; i++)
    {
        int start = i * chunk_size;
        int end = (start + chunk_size > url_count) ? url_count : start + chunk_size;

        tasks[i].urls = urls;
        tasks[i].start = start;
        tasks[i].end = end;
        tasks[i].stats = stats;

        pthread_create(&threads[i], NULL, process_urls, &tasks[i]);
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    free(tasks);
}
