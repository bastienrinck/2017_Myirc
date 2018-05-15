/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <arpa/inet.h>
#include "socket.h"

bool create_client_socket(socket_t *sck)
{
	if (!create_tcp_socket(&sck->fd, 6))
		return (false);
	sck->size = sizeof(sck->s_in);
	if (getsockname(sck->fd, &sck->s_in, &sck->size))
		return (print_errno(__func__, __LINE__, __FILE__));
	inet_aton(sck->ip, &((struct sockaddr_in *)&sck->s_in)->sin_addr);
	((struct sockaddr_in *)&sck->s_in)->sin_port = htons(sck->port);
	return (VALID_SOCKET(sck->fd));
}

bool client_connect(socket_t *sck)
{
	if (connect(sck->fd, &sck->s_in, sck->size))
		return (print_errno(__func__, __LINE__, __FILE__));
	return (true);
}