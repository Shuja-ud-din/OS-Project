#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#define MAX_URLS 1000

// Stores the downloaded content
typedef struct {
    char *url;
    char *content;
} UrlContent;

// Reads URLs from a file
int load_urls(const char *filepath, char ***urls_out, int *url_count);

// Downloads content from a URL (returns malloc'ed buffer)
char *download_text(const char *url);

// Downloads all URLs and returns UrlContent[]
UrlContent *download_all(const char **urls, int url_count);

void free_url_contents(UrlContent *list, int count);

#endif
