#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "downloader.h"

// --- CURL Write Callback ---
struct MemoryBuffer
{
    char *data;
    size_t size;
};

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t total_size = size * nmemb;
    struct MemoryBuffer *mem = (struct MemoryBuffer *)userp;

    char *ptr = realloc(mem->data, mem->size + total_size + 1);
    if (!ptr)
        return 0; // Out of memory

    mem->data = ptr;
    memcpy(&(mem->data[mem->size]), contents, total_size);
    mem->size += total_size;
    mem->data[mem->size] = '\0';

    return total_size;
}

// --- Load URLs from file ---
int load_urls(const char *filepath, char ***urls_out, int *url_count)
{
    FILE *file = fopen(filepath, "r");
    if (!file)
    {
        perror("Error opening URL file");
        return 0;
    }

    char **urls = malloc(sizeof(char *) * MAX_URLS);
    if (!urls)
        return 0;

    char line[1024];
    int count = 0;

    while (fgets(line, sizeof(line), file) && count < MAX_URLS)
    {
        line[strcspn(line, "\r\n")] = 0; // remove newline
        urls[count] = strdup(line);
        count++;
    }

    fclose(file);
    *urls_out = urls;
    *url_count = count;
    return 1;
}

// --- Download single URL ---
char *download_text(const char *url)
{
    CURL *curl = curl_easy_init();
    if (!curl)
        return NULL;

    struct MemoryBuffer chunk = {0};

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // follow redirects
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        fprintf(stderr, "Download failed for %s: %s\n", url, curl_easy_strerror(res));
        free(chunk.data);
        chunk.data = NULL;
    }

    curl_easy_cleanup(curl);
    return chunk.data;
}

// --- Download All URLs ---
UrlContent *download_all(const char **urls, int url_count)
{
    UrlContent *results = malloc(sizeof(UrlContent) * url_count);
    if (!results)
        return NULL;

    for (int i = 0; i < url_count; i++)
    {
        results[i].url = strdup(urls[i]);
        results[i].content = download_text(urls[i]);

        if (!results[i].content)
        {
            fprintf(stderr, "Skipping URL due to failure: %s\n", urls[i]);
        }
    }

    return results;
}

// --- Free all contents ---
void free_url_contents(UrlContent *list, int count)
{
    for (int i = 0; i < count; i++)
    {
        free(list[i].url);
        free(list[i].content);
    }
    free(list);
}
