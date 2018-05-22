/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include "server.h"

void cmd_user(server_t *srv, client_t *client)
{
	char *str;

	if (client->cmd.psize == 4) {
		memcpy(client->username, client->cmd.param[0],
			strlen(client->cmd.param[0]) % 512);
		memcpy(client->user, client->cmd.param[3],
			strlen(client->cmd.param[3]) % 512);
		str = malloc(2048);
		client->logged = true;
		sprintf(str,
			":localhost 001 %s: Welcome to the Internet Relay Network %s!%s@localhost",
			client->nick, client->nick, client->user);
		add_pending(client, str);
	}
}