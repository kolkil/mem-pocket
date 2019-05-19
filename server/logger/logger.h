#include "queue.h"

typedef struct
{
    char *path;
    int fd,
        file_existed;
    log_queue *queue;
} logger;

logger *logger_new(char *);
int logger_log(logger *, char *);
int write_traffic_log_format(logger*);
