#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

void error(const char*);
struct sockaddr_in socket_create(int socket, char* buf, int len);

int main() 
{
    // Create socket and bind it to a port
    int listener_d = socket(PF_INET, SOCK_STREAM, 0);
    if (listener_d == -1)
        error("Unable to open socket");
    
    struct sockaddr_in name;
    name.sin_family = PF_INET;
    name.sin_port = (in_port_t)htons(30000);
    name.sin_addr.s_addr = htonl(INADDR_ANY);
    int c = bind (listener_d, (struct sockaddr *) &name, sizeof(name));
    if (c == -1)
        error("Can't bind to socket");

    // Allow up to ten clients to listen
    if(listen(listener_d, 10) == -1)
        error("Can't listen on the socket");

    while (1)
    {
         // Accept connections
         struct sockaddr_storage client_addr;
         unsigned int address_size = sizeof(client_addr);
         int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
         if (connect_d == -1)
             error("Can't open secondary socket");

         // send a message over the connection for testing
         char *msg = "HTTP protocol here would be great\n";
         if (send(connect_d, msg, strlen(msg), 0) == -1)
             error("Unable to send data");

         close(connect_d);
    }
    
    return 0;
}

/**
 * @brief Reads the incoming data from the client. 
 * @param socket: socket to read the incoming data from
 * @param *buf: [out] The incoming data is stored in the buf.
 * @param len: Length of the buffer
 */
int read_in(int socket, char *buf, int len)
{
    char *s = buf;
    int slen = len;
    int c = recv(socket, s, slen, 0);
    // Keep reading until a new line is reached
    while ((c > 0) && (s[c - 1] != '\n'))
    {
        s += c;
        slen -= c;
        c = recv(socket, s, slen, 0);
    }
    // Replace the \r with \0
    s[c-1] = '\0';
    return len - slen;
}


