#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
	struct sockaddr_in serv_socket;
	int socket_fd;
	int conn_fd;
	int users[100];
	char message[100] = "";

	serv_socket.sin_family = AF_INET;
	serv_socket.sin_port = htons(8096);
	serv_socket.sin_addr.s_addr = INADDR_ANY;	 // bind to all
	socket_fd = socket(AF_INET, SOCK_STREAM, 0); // creates a new socket and returns the id for it

	// AF_INET is an address family that is used to designate the type of addresses that your socket can communicate with (in this case, Internet Protocol v4 addresses). When you create a socket, you have to specify its address family, and then you can only use addresses of that type with the socket. The Linux kernel, for example, supports 29 other address families such as UNIX (AF_UNIX) sockets and IPX (AF_IPX), and also communications with IRDA and Bluetooth (AF_IRDA and AF_BLUETOOTH, but it is doubtful you'll use these at such a low level).

	// For the most part, sticking with AF_INET for socket programming over a network is the safest option. There is also AF_INET6 for Internet Protocol v6 addresses.
	if (socket_fd <= 0)
	{
		printf("error socket id 0 or below");
	}
	bind(socket_fd, (struct sockaddr *)&serv_socket, sizeof(serv_socket)); // assign the address by serve_socket to the socket
	listen(socket_fd, 5);												   // max 5 connections

	while (conn_fd = accept(socket_fd, (struct sockaddr *)NULL, NULL))
	{
		int pid;
		if ((pid = fork()) == 0)
		{
			while (recv(conn_fd, message, 100, 0) > 0)
			{

				append(users, conn_fd);
				printf("server %i: %s\n", conn_fd, message);
				for (size_t i = 0; i < users; i++)
				{

					if (users[i] != conn_fd)
					{
						send(users[i], message, strlen(message), 0);
					}
				}

				// message="";
			}
			exit(0);
		}
	}
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