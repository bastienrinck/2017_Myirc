/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "server.h"

static bool init_srv(socket_t *srv, uint16_t port)
{
	srv->port = port;
	return (create_server_socket(srv));
}

static bool myirc_server(uint16_t port)
{
	server_t srv = {0};
	client_t *client = malloc(sizeof(client_t));

	memset(client, 0, sizeof(client_t));
	memset(&srv, 0, sizeof(server_t));
	if (!init_srv(&client->sck, port))
		return (false);
	printf("[%s] Listening on port %d\n", client->sck.ip, client->sck.port);
	while (1)
		proceed_poll(&srv, client);
	//free_client();
	return (true);
}

static int print_usage(char *bin)
{
	printf("USAGE:\t%s port\n", bin);
	return (84);
}

int main(int ac, char **av)
{
	int ret = 0;

	if (ac != 2 || !strcmp(av[1], "-help"))
		ret = print_usage(av[0]);
	else if (!myirc_server((uint16_t)strtol(av[1], NULL, 10)))
		ret = 84;
}