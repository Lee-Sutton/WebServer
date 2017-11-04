#ifndef SOCKET_BUILDER_H
#define SOCKET_BUILDER_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#include "error.h"
#include "socket_builder.h"

int socket_create()
{
    int listener_d = socket(PF_INET, SOCK_STREAM, 0);
    if (listener_d == -1)
        error("Unable to open socket");
 
    return listener_d;
}

void bind_to_port(int socket, int port)
{
    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(port);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    int c = bind (socket, (struct sockaddr *) &name, sizeof(name));
    if (c == -1)
        error("Can't bind to socket");
}

void socket_listen(int socket, int max_clients)
{
    // Allow up to ten clients to listen
    if(listen(socket, 10) == -1)
        error("Can't listen on the socket");
}

int accept_connection(int socket)
{
    struct sockaddr_storage client_addr;
    unsigned int address_size = sizeof(client_addr);
    int client_socket = accept(socket, (struct sockaddr *)&client_addr, &address_size);
    if (client_socket == -1)
        error("Can't open secondary socket");
    return  client_socket;
}

void send_message(int client_socket, const char* message)
{
    if (send(client_socket, message, strlen(message), 0) == -1)
        error("Unable to send data");
}

#endif
