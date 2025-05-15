#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "processor.h"

int count_words(const char *text)
{
    int count = 0;
    int in_word = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isspace((unsigned char)text[i]))
        {
            in_word = 0;
        }
        else if (!in_word)
        {
            in_word = 1;
            count++;
        }
    }

    return count;
}

UrlWordCount *analyze_words(UrlContent *data, int count)
{
    UrlWordCount *results = malloc(sizeof(UrlWordCount) * count);
    if (!results)
        return NULL;

    for (int i = 0; i < count; i++)
    {
        results[i].url = data[i].url;
        results[i].word_count = data[i].content ? count_words(data[i].content) : 0;
    }

    return results;
}

int count_sentences(const char *text)
{
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        char c = text[i];
        if (c == '.' || c == '?' || c == '!')
        {
            count++;
        }
    }
    return count;
}

UrlSentenceCount *analyze_sentences(UrlContent *data, int count)
{
    UrlSentenceCount *results = malloc(sizeof(UrlSentenceCount) * count);
    if (!results)
        return NULL;

    for (int i = 0; i < count; i++)
    {
        results[i].url = data[i].url;
        results[i].sentence_count = data[i].content ? count_sentences(data[i].content) : 0;
    }

    return results;
}

void analyze_character_frequency(UrlContent *data, int count, CharFrequency *freq_out)
{
    memset(freq_out->frequencies, 0, sizeof(freq_out->frequencies));

    for (int i = 0; i < count; i++)
    {
        const char *text = data[i].content;
        if (!text)
            continue;

        for (int j = 0; text[j] != '\0'; j++)
        {
            char c = tolower((unsigned char)text[j]);
            if (c >= 'a' && c <= 'z')
            {
                freq_out->frequencies[c - 'a']++;
            }
        }
    }
}

void print_char_frequency(CharFrequency *freq)
{
    printf("\n--- Character Frequencies (a-z) ---\n");
    for (int i = 0; i < 26; i++)
    {
        printf("%c: %d\n", 'a' + i, freq->frequencies[i]);
    }
}
