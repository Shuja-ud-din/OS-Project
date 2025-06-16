#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "downloader.h"
#include "processor.h"
#include "thread_pool.h"
#include "utils.h"

#define URL_FILE "constants/urls.txt"
#define THREAD_COUNT 2
#define CHUNK_SIZE 500
#define URL_COUNT 5

int main()
{
    double start_time = get_time_seconds();

    char **urls = NULL;
    int count = 0;

    if (!load_urls("constants/urls.txt", &urls, &count))
    {
        return 1;
    }

    UrlContent *data = download_all((const char **)urls, count);
    if (!data)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    ThreadPool pool;
    thread_pool_init(&pool, (const char **)urls, data, count);
    thread_pool_start(&pool, THREAD_COUNT);
    thread_pool_destroy(&pool);

    for (int i = 0; i < count; i++)
    {
        if (data[i].content)
        {
            printf("Downloaded %s [%lu bytes]\n", data[i].url, strlen(data[i].content));
        }
        free(urls[i]);
    }

    UrlWordCount *stats = analyze_words(data, count);
    if (stats)
    {
        printf("\n--- Word Counts ---\n");
        for (int i = 0; i < count; i++)
        {
            printf("%s: %d words\n", stats[i].url, stats[i].word_count);
        }
        free(stats);
    }

    UrlSentenceCount *sentence_stats = analyze_sentences(data, count);
    if (sentence_stats)
    {
        printf("\n--- Sentence Counts ---\n");
        for (int i = 0; i < count; i++)
        {
            printf("%s: %d sentences\n", sentence_stats[i].url, sentence_stats[i].sentence_count);
        }
        free(sentence_stats);
    }

    CharFrequency freq;
    analyze_character_frequency(data, count, &freq);
    print_char_frequency(&freq);

    free(urls);
    free_url_contents(data, count);

    double end_time = get_time_seconds();
    printf("Total time: %.2f seconds\n", end_time - start_time);

    return 0;
}
