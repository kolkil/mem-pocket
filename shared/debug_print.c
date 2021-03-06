#include "debug_print.h"

#include <stdio.h>
#include <sys/time.h>

void debug_print(char *msg, int v)
{
#ifdef DEBUG
    static int k;
    if (v <= 0)
        k -= 1;
    for (int i = 0; i < k; ++i)
        printf("\t");
    if (v > 0)
        k += 1;
    if (v == 2)
    {
        printf("- value - \"%s\"\n", msg);
        k -= 1;
    }
    else
    {
        printf("- %s%s\n", msg, v ? "" : " ok");
    }
#endif
    if (msg == NULL && v)
        msg = NULL;
    return;
}

void debug_print_int(int msg)
{
#ifdef DEBUG
    char tmp[128] = {0};
    sprintf(tmp, "%d", msg);
    debug_print(tmp, 2);
#endif
    if (msg == 1)
        msg = 1;
    return;
}

void debug_print_raw(char *msg)
{
#ifdef DEBUG
    printf("%s\n", msg);
#endif
    if (msg == NULL)
        msg = NULL;
    return;
}

void debug_print_raw_int(int msg)
{
#ifdef DEBUG
    printf("%d\n", msg);
#endif
    if (msg == 1)
        msg = 1;
    return;
}

void debug_print_raw_string_int(char *str, int v)
{
#ifdef DEBUG
    printf("%s %d\n", str, v);
#endif
    if (v == 1)
        v = 1;
    if (str == NULL)
        str = NULL;
    return;
}

void debug_print_content_as_hex(char *title, void *str, size_t size)
{
#ifdef DEBUG
    printf("%s (%zu bytes):\n", title, size);
    for (size_t i = 0; i < size; ++i)
    {
        if (i > 0 && i % 4 == 0)
            printf("\n");
        printf("%.2x ", (((unsigned int)((char *)str)[i]) & 0xff));
    }
    printf("\n");
#endif
    if (title == NULL)
        title = NULL;
    if (str == NULL)
        str = NULL;
    if (size == 0)
        size = 0;
    return;
}

void debug_print_content_as_dec(char *title, void *str, size_t size)
{
#ifdef DEBUG
    printf("%s (%zu bytes):\n", title, size);
    for (size_t i = 0; i < size; ++i)
    {
        if (i > 0 && i % 4 == 0)
            printf("\n");
        printf("%3d ", (((unsigned int)((char *)str)[i])));
    }
    printf("\n");
#endif
    if (title == NULL)
        title = NULL;
    if (str == NULL)
        str = NULL;
    if (size == 0)
        size = 0;
    return;
}

long int microtime_now()
{
    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

float micro_to_seconds(long int a, long int b)
{
    return (float)(a - b) / (1000 * 1000);
}

float msd(long int a, long int b)
{
    return b == 0 ? 0.0 : (float)(a / b) / (1000 * 1000);
}
