#include <stdio.h>

#define URL_FILE "constants/urls.txt"
#define THREAD_COUNT 4
#define CHUNK_SIZE 500

int main()
{
    printf("Starting crawler...\n");
    printf("URL File: %s\n", URL_FILE);
    printf("Threads: %d, Chunk Size: %d words\n", THREAD_COUNT, CHUNK_SIZE);

    // Call your logic here using these constants
    return 0;
}
