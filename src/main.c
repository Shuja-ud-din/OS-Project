#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "downloader.h"
#include "processor.h"
#include "thread_pool.h"
#include "utils.h"

#define URL_FILE "constants/urls.txt"
#define THREAD_COUNT 2

int main()
{
    char **urls = NULL;
    int count = 0;

    if (!load_urls(URL_FILE, &urls, &count))
    {
        return 1;
    }

    printf("Loaded %d URLs\n", count);

    SharedStats stats;
    pthread_mutex_init(&stats.lock, NULL);
    stats.word_counts = malloc(sizeof(UrlWordCount) * count);
    stats.sentence_counts = malloc(sizeof(UrlSentenceCount) * count);
    memset(&stats.frequency, 0, sizeof(CharFrequency));

    double start_time = get_time_seconds();

    run_thread_pool((const char **)urls, count, THREAD_COUNT, &stats);

    double end_time = get_time_seconds();
    printf("\nExecution time: %.3f seconds\n", end_time - start_time);

    printf("\n--- Word Counts ---\n");
    for (int i = 0; i < count; i++)
    {
        printf("%s: %d words\n", stats.word_counts[i].url, stats.word_counts[i].word_count);
    }

    printf("\n--- Sentence Counts ---\n");
    for (int i = 0; i < count; i++)
    {
        printf("%s: %d sentences\n", stats.sentence_counts[i].url, stats.sentence_counts[i].sentence_count);
    }

    print_char_frequency(&(stats.frequency));

    pthread_mutex_destroy(&stats.lock);
    free(stats.word_counts);
    free(stats.sentence_counts);

    for (int i = 0; i < count; i++)
    {
        free(urls[i]);
    }
    free(urls);

    return 0;
}
