#include "socket.h"
#include "../utils/debug_print.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

socket_params *prepare_socket(char *address, int port)
{
    debug_print("prepare_socket", 1);
    socket_params *params = calloc(1, sizeof(socket_params));
    int opt = 1;

    if ((params->fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        printf("socket failed");
        return params;
    }

    if (setsockopt(params->fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        printf("setsockopt");
        return params;
    }
    params->address.sin_family = AF_INET;
    params->address.sin_addr.s_addr = inet_addr(address);
    params->address.sin_port = htons(port);

    if (bind(params->fd, (struct sockaddr *)&(params->address), sizeof(params->address)) < 0)
    {
        printf("bind failed");
        return params;
    }
    debug_print("prepare_socket", 0);
    return params;
}

int socket_listen_and_accept(socket_params *params)
{
    int new_socket = -1;
    if (listen(params->fd, 128) < 0)
        return -1;
    if ((new_socket = accept(params->fd, (struct sockaddr *)NULL, NULL)) < 1)
    {
        debug_print_int(new_socket);
        return -1;
    }
    return new_socket;
}
