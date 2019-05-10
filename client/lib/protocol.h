#include <stdint.h>

enum
{
    INSERT = 1,
    GET = 2,
    POP = 3,
    KEYS = 4,
    ALL = 5
} COMMANDS;

enum
{
    OK = 0,
    ERROR = 1,
    UNKNOWN_ERROR = 2
} RESULT_INFO;

enum
{
    NO_DATA = 0,
    VALUE = 1,
    RKEYS = 2,
    RALL = 3
} RESPONSE_TYPE;

/*
    mcache_request_header
    _____________
    |_|____|____|

    first byte - command
    next four bytes - key length
    next four bytes - data length
*/

typedef struct
{
    uint8_t command;
    uint32_t key_len,
        data_len;
} mcache_request_header;

/*
    mcache_response_header
    __________
    |_|_|____|
    
    first byte - execution info
    second byte - type of response
    next four bytes - number of items
*/

typedef struct
{
    uint8_t info,
        response_type;
    uint32_t items_count;
} mcache_response_header;

typedef struct
{
    uint8_t *data;
    uint32_t length;
} data_and_length;