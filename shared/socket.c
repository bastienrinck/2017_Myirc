/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <unistd.h>
#include "server.h"

bool create_tcp_socket(int *fd, int protocol)
{
	*fd = socket(AF_INET, SOCK_STREAM, protocol);
	if (!VALID_SOCKET(*fd))
		return (print_errno(__func__, __LINE__, __FILE__));
	return (true);
}

void free_socket(socket_t *sck)
{
	close(sck->fd);
}