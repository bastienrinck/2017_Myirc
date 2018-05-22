/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <string.h>
#include <malloc.h>
#include "server.h"

void list_users(client_t *client, channel_t *channel)
{
	char *str = malloc(2048 + channel->amount * 10);
	char *str2 = malloc(2048);

	memset(str, 0, 2048 + channel->amount * 10);
	sprintf(str, ":localhost 353 %s = %s :", client->nick, channel->name);
	sprintf(str2, ":localhost 366 %s %s :End of NAMES list", client->nick,
		channel->name);
	for (size_t i = 0; i < channel->amount; ++i) {
		if (i)
			strcat(str, " ");
		strcat(str, channel->client[i]->nick);
	}
	add_pending(client, str);
	add_pending(client, str2);
}

void cmd_names(server_t *srv, client_t *client)
{
	channel_t *tmp = srv->channel;

	for (tmp; tmp && strcmp(srv->channel->name, client->cmd.param[0]) !=
		0; tmp = tmp->next);
	if (tmp)
		list_users(client, tmp);
}