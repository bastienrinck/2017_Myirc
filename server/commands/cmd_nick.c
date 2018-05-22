/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <string.h>
#include "server.h"

void cmd_nick(server_t *srv, client_t *client)
{
	if (client->cmd.psize == 1)
		memcpy(client->nick, client->cmd.param[0],
			strlen(client->cmd.param[0]) % NICK_LENGTH);
}