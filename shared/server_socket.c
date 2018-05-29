/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <stdbool.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include "socket.h"

bool listen_socket(int fd, int capacity)
{
	if (listen(fd, capacity))
		return (print_errno(__func__, __LINE__, __FILE__));
	return (true);
}

bool bind_socket(int fd, struct sockaddr *s_in, socklen_t size)
{
	int reuse = 1;

	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&reuse,
		sizeof(reuse)) ||
		setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, (const char *)&reuse,
			sizeof(reuse)))
		return (print_errno(__func__, __LINE__, __FILE__));
	if (bind(fd, s_in, size))
		return (print_errno(__func__, __LINE__, __FILE__));
	return (true);
}

bool create_server_socket(socket_t *sck)
{
	char *temp;

	if (!create_tcp_socket(&sck->fd, 6))
		return (false);
	sck->size = sizeof(sck->s_in);
	if (getsockname(sck->fd, &sck->s_in, &sck->size))
		return (print_errno(__func__, __LINE__, __FILE__));
	((struct sockaddr_in *)&sck->s_in)->sin_addr.s_addr = INADDR_ANY;
	((struct sockaddr_in *)&sck->s_in)->sin_port = htons(sck->port);
	if (!bind_socket(sck->fd, &sck->s_in, sck->size) ||
		!listen_socket(sck->fd, 42))
		return (false);
	temp = inet_ntoa(((struct sockaddr_in *)&sck->s_in)->sin_addr);
	memset(sck->ip, 0, INET_ADDRSTRLEN);
	memcpy(sck->ip, temp, INET_ADDRSTRLEN);
	return (VALID_SOCKET(sck->fd));
}

bool server_accept(socket_t *sck, socket_t *client)
{
	char *temp;

	client->fd = accept(sck->fd, &client->s_in, &client->size);
	if (getsockname(client->fd, &client->s_in, &client->size))
		return (print_errno(__func__, __LINE__, __FILE__));
	temp = inet_ntoa(((struct sockaddr_in *)&client->s_in)->sin_addr);
	memset(client->ip, 0, INET_ADDRSTRLEN);
	memcpy(client->ip, temp, INET_ADDRSTRLEN);
	return (VALID_SOCKET(client->fd));
}
