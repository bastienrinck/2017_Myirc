/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#define _GNU_SOURCE

#include <string.h>
#include <malloc.h>
#include "server.h"

void list_users(client_t *client, channel_t *channel)
{
	char *str = 0;
	char *tmp = 0;

	for (size_t i = 0; i < channel->amount; ++i) {
		tmp = str;
		if (!i)
			str = str_append("%s", channel->client[i]->nick);
		else {
			str = str_append("%s %s", str,
				channel->client[i]->nick);
			free(tmp);
		}
	}
	add_pending(client,
		gen_rpl(RPL_NAMES, TRANSLATE_NICK(client), channel->name, str));
	add_pending(client,
		gen_rpl(RPL_ENDOFNAMES, TRANSLATE_NICK(client), channel->name));
	free(str);
}

void cmd_names(server_t *srv, client_t *client)
{
	channel_t *tmp = srv->channel;

	for (; tmp; tmp = tmp->next)
		if (client->cmd.psize &&
			!strcmp(srv->channel->name, client->cmd.param[0]))
			list_users(client, tmp);
		else if (!client->cmd.psize)
			list_users(client, tmp);
}