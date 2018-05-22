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
	char *str;

	for (; tmp &&
		strcmp(tmp->nick, client->cmd.param[0]) != 0; tmp = tmp->next);
	if (tmp) {
		str = malloc(2048 + strlen(client->cmd.param[1]));
		sprintf(str, ":%s!%s@localhost PRIVMSG %s :%s", client->nick,
			client->user, tmp->nick,
			client->cmd.param[1]);
		add_pending(tmp, str);
	}
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
		if (tmp->client[i] != client) {
			str = malloc(2048 + strlen(client->cmd.param[1]));
			sprintf(str, ":%s!%s@localhost PRIVMSG %s :%s",
				client->nick, client->user,
				tmp->client[i]->nick, client->cmd.param[1]);
			add_pending(tmp->client[i], str);

		}
	}
}

void cmd_privmsg(server_t *srv, client_t *client)
{
	if (client->cmd.psize) {
		if (client->cmd.param[0][0] != '#' &&
			client->cmd.param[0][0] != '$')
			msg_user(srv, client);
		else
			msg_channel(srv, client);
	}
}