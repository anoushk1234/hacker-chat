#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <pthread.h>

void *recv_messages(char message[100], int socket_fd, int conn_fd)
{
    while (conn_fd = accept(socket_fd, (struct sockaddr *)NULL, NULL))
    {
        int pid;
        if ((pid = fork()) == 0)
        {
            while (recv(conn_fd, message, 100, 0) > 0)
            {
                printf("Message Received: %s\n", message);
            }
            exit(0);
        }
    }
}
int main()
{
    struct sockaddr_in serv; // This is our main socket variable.
    int fd;                  // This is the socket file descriptor that will be used to identify the socket
    int conn;                // This is the connection file descriptor that will be used to distinguish client connections.
    char message[100] = "";  // This array will store the messages that are sent by the server
    // serv.sin_family = AF_INET;
    // serv.sin_port = htons(8096); // Define the port at which the server will listen for connections.
    serv.sin_addr.s_addr = INADDR_ANY;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8096);
    inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr);     // This binds the client to localhost
    connect(fd, (struct sockaddr *)&serv, sizeof(serv)); // This connects the client to the server.

    
    while (1)
    {
        printf("Enter a message: ");
        fgets(message, 100, stdin);
        send(fd, message, strlen(message), 0);
        // An extra breaking condition can be added here (to terminate the while loop)
    }
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, recv_messages(message, fd, conn), NULL);
    pthread_join(thread_id, NULL);
}
