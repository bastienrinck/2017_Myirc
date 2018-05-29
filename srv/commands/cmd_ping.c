/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include "server.h"

void cmd_ping(server_t *srv, client_t *client)
{
	(void)srv;
	if (!client->logged)
		return;
	add_pending(client, str_append(":%s!~%s@%s PONG :%s\r\n", client->nick,
		client->user, client->sck.ip, client->cmd.param[0]));
}