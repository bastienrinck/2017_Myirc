/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <string.h>
#include <malloc.h>
#include "server.h"

void destroy_channel(server_t *srv, channel_t *channel)
{
	channel_t *tmp = srv->channel;

	for (; tmp && tmp != channel; tmp = tmp->next);
	if (tmp && tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp && tmp->next)
		tmp->next->prev = tmp->prev;
	srv->channel = (tmp && tmp == srv->channel) ? tmp->next : srv->channel;
	free(tmp);
}

void leave_channel(server_t *srv, client_t *client, channel_t *channel)
{
	client_t *tmp;
	size_t i = 0;
	char *reason = (client->cmd.psize ? client->cmd.param[0] : "");

	for (; i < channel->amount &&
		strcmp(channel->client[i]->nick, client->nick) != 0; ++i);
	if (i == channel->amount)
		return;
	for (int k = 0; k < channel->amount; ++k)
		add_pending(channel->client[k],
			str_append(":%s!~%s@%s PART %s :%s\r\n", client->nick,
				client->user, client->sck.ip, channel->name, reason));
	tmp = channel->client[i];
	channel->client[i] = channel->client[channel->amount - 1];
	channel->client[channel->amount - 1] = tmp;
	channel->amount -= 1;
	channel->client = realloc(channel->client,
		sizeof(client_t *) * channel->amount);
	if (!channel->amount)
		destroy_channel(srv, channel);
}

void cmd_part(server_t *srv, client_t *client)
{
	channel_t *tmp = srv->channel;
	channel_t *ptr;

	for (; tmp;)
		if (!strcmp(tmp->name, client->cmd.param[0])) {
			ptr = tmp->next;
			leave_channel(srv, client, tmp);
			tmp = ptr;
		} else
			tmp = tmp->next;
}