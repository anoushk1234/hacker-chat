#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <pthread.h>

// #define MAXRCVLEN 500
#define PORTNUM 8096

void *send_messages(char message[100], int user_socket_fd)
{
    while (1)
    {
        printf("Enter a message: ");
        fgets(message, 100, stdin);
        send(user_socket_fd, message, strlen(message), 0);
        // An extra breaking condition can be added here (to terminate the while loop)
    }

    // while (recv(conn_fd, message, 100, 0) > 0)
    // {
    //     printf("Message Received: %s\n", message);
    // }
}
int main()
{
    struct sockaddr_in server_socket;
    struct sockaddr_in user_socket; // This is our main socket variable.
    int user_socket_fd;             // This is the socket file descriptor that will be used to identify the socket
    int server_socket_fd;
    // int conn;                       // This is the connection file descriptor that will be used to distinguish client connections.
    char message[100] = ""; // This array will store the messages that are sent by the server
                            // user_socket.sin_family = AF_INET;
                            // user_socket.sin_port = htons(8096); // Define the port at which the server will listen for connections.
    user_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&server_socket, 0, sizeof(server_socket));
    server_socket.sin_addr.s_addr = htonl(INADDR_LOOPBACK); /* set destination IP number - localhost, 127.0.0.1*/
    server_socket.sin_family = AF_INET;
    server_socket.sin_port = htons(PORTNUM);
    // inet_pton(AF_INET, "127.0.0.1", &user_socket.sin_addr);                        // This binds the client to localhost
    /*this connect method will connect users socket to servers socket*/
    int c = connect(user_socket_fd, (struct sockaddr *)&server_socket, sizeof(struct sockaddr_in));
    printf("connection made: %i", c);
    // pthread_t thread_id;
    // pthread_create(&thread_id, NULL, send_messages(message, user_socket_fd), NULL);
    // // recv_messages(message, user_socket_fd, conn)

    // pthread_join(thread_id, NULL);
    while (1)
    {
        printf("Enter a message: ");
        fgets(message, 100, stdin);
        send(user_socket_fd, message, strlen(message), 0);
        // An extra breaking condition can be added here (to terminate the while loop)
    }
    close(user_socket_fd);
}
