#ifndef SOCKET_BUILDER_H
#define SOCKET_BUILDER_H

/**
 * Opens an internet streaming socket and returns the integer handler
 */
int open_listener_socket();

/**
 * Binds the input socket to the desired port
 */
void bind_to_port(int socket, int port);

/**
 * Starts the socket listening. Should be called after bind
 */
void socket_listen(int socket, int max_clients);

/**
 * Accepts connection to the client. 
 * @param socket - server socket listening for clients
 * @returns - socket to communicate with client
 */
int accept_connection(int socket);


/**
 * Sends the input message over the input socket
 */
void send_message(int socket, const char *s);

/**
 * @brief Reads the incoming data from the client. 
 * @param socket: socket to read the incoming data from
 * @param *buf: [out] The incoming data is stored in the buf.
 * @param len: Length of the buffer
 */
int read_in(int socket, char *buf, int len);

#endif
