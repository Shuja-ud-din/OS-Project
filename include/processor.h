#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "downloader.h"

typedef struct
{
    const char *url;
    int word_count;
} UrlWordCount;

typedef struct
{
    const char *url;
    int sentence_count;
} UrlSentenceCount;

typedef struct
{
    int frequencies[26]; // 'a' to 'z'
} CharFrequency;

void analyze_character_frequency(UrlContent *data, int count, CharFrequency *freq_out);
void print_char_frequency(CharFrequency *freq);

int count_sentences(const char *text);
UrlSentenceCount *analyze_sentences(UrlContent *data, int count);

int count_words(const char *text);
UrlWordCount *analyze_words(UrlContent *data, int count);

#endif
