#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdbool.h>

bool valueinarray(int val, int *arr)
{
	for (size_t i = 0; i < sizeof(arr) / sizeof(*arr); i++)
	{
		if (arr[i] == val)
		{
			return true;
		}
	}
	return false;
}

void append(int arr[], int *item)
{
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (arr[i] == 0)
		{
			arr[i] = item;
			return 0;
		}
	}
}

int main()
{
	struct sockaddr_in server_socket; // info about our servers socket
	int server_socket_fd;			  // file descriptor for server socket
	int conn_fd;
	int users[5];
	char message[100] = "";

	server_socket.sin_family = AF_INET;
	server_socket.sin_port = htons(8096);
	server_socket.sin_addr.s_addr = INADDR_ANY;			// bind to all
	server_socket_fd = socket(AF_INET, SOCK_STREAM, 0); // creates a new socket for us and returns the id for it

	// AF_INET is an address family that is used to designate the type of addresses that your socket can communicate with (in this case, Internet Protocol v4 addresses). When you create a socket, you have to specify its address family, and then you can only use addresses of that type with the socket. The Linux kernel, for example, supports 29 other address families such as UNIX (AF_UNIX) sockets and IPX (AF_IPX), and also communications with IRDA and Bluetooth (AF_IRDA and AF_BLUETOOTH, but it is doubtful you'll use these at such a low level).

	// For the most part, sticking with AF_INET for socket programming over a network is the safest option. There is also AF_INET6 for Internet Protocol v6 addresses.
	if (server_socket_fd <= 0)
	{
		printf("error socket id 0 or below");
	}
	bind(server_socket_fd, (struct sockaddr *)&server_socket, sizeof(server_socket)); // assign the address by serve_socket to the socket
	listen(server_socket_fd, 5);													  // start listening with upto 5 connections												  // just tells our server to start listening on this socket											   // max 5 connections
	/*
	The first important difference is that rather than creating a sockaddr_in with information about
	the machine we're connecting to, we create it with information about the server, and then we bind() it to the socket.
	This allows the machine to know the data received on the port specified in the sockaddr_in should be handled by our specified socket.
	*/
	while (conn_fd = accept(server_socket_fd, (struct sockaddr *)NULL, NULL))
	{

		if (!valueinarray(conn_fd, users))
		{
			append(users, conn_fd);
			for (size_t i = 0; i < sizeof(users) / sizeof(users[0]); i++)
			{
				// printf("outside");
				if (0 != users[i])
				{
					printf("user %i is fd %i", i, users[i]);
				}
			}
		}

		int pid;
		if ((pid = fork()) == 0)
		{
			while (recv(conn_fd, message, 100, 0) > 0)
			{

				printf("server %i: %s\n", conn_fd, message);

				//
				for (size_t i = 0; i < users; i++)
				{

					if (users[i] != conn_fd)
					{
						int r = send(users[i], message, strlen(message), 0);
						if (-1 == r)
						{
							printf("failed to send to %i", users[i]);
						}
					}
				}

				// message="";
			}

			exit(0);
		}
	}
}
