#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "downloader.h"

#define URL_FILE "constants/urls.txt"
#define THREAD_COUNT 4
#define CHUNK_SIZE 500

int main()
{
    char **urls = NULL;
    int count = 0;

    if (!load_urls("constants/urls.txt", &urls, &count))
    {
        return 1;
    }

    UrlContent *data = download_all((const char **)urls, count);

    for (int i = 0; i < count; i++)
    {
        if (data[i].content)
        {
            printf("Downloaded %s [%lu bytes]\n", data[i].url, strlen(data[i].content));
        }
        free(urls[i]);
    }

    free(urls);
    free_url_contents(data, count);

    return 0;
}
