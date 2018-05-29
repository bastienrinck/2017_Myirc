/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <string.h>
#include <malloc.h>
#include "server.h"

void msg_user(server_t *srv, client_t *client)
{
	client_t *tmp = srv->list;

	for (; tmp &&
		strcmp(tmp->nick, client->cmd.param[0]) != 0; tmp = tmp->next);
	if (tmp)
		add_pending(tmp,
			str_append(":%s!%s@localhost PRIVMSG %s :%s\r\n",
				client->nick, client->user, tmp->nick,
				client->cmd.param[1]));
}

void msg_channel(server_t *srv, client_t *client)
{
	char *str;
	channel_t *tmp = srv->channel;

	for (; tmp &&
		strcmp(tmp->name, client->cmd.param[0]) != 0; tmp = tmp->next);
	if (!tmp)
		return;
	for (size_t i = 0; i < tmp->amount; ++i) {
		if (tmp->client[i] != client)
			add_pending(tmp->client[i], str_append(
				":%s!%s@localhost PRIVMSG %s :%s\r\n",
				client->nick, client->user, tmp->name,
				client->cmd.param[1]));
	}
}

void cmd_privmsg(server_t *srv, client_t *client)
{
	if (client->logged && client->cmd.psize) {
		if (client->cmd.param[0][0] != '#' &&
			client->cmd.param[0][0] != '$')
			msg_user(srv, client);
		else
			msg_channel(srv, client);
	}
}