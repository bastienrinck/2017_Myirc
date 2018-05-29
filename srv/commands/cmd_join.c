/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <malloc.h>
#include <string.h>
#include "server.h"

void notify_channel(channel_t *channel, client_t *client)
{
	for (size_t i = 0; i < channel->amount; ++i)
		add_pending(channel->client[i],
			str_append(RPL_CHAN_JOIN, client->nick, client->user,
				client->sck.ip, channel->name));
}

void send_topic(channel_t *channel, client_t *client)
{
	add_pending(client, gen_rpl(RPL_TOPIC, client->user, channel->name,
		channel->topic));
}

static void join_channel(server_t *srv, client_t *client)
{
	char *res;
	channel_t *tmp;

	res = strtok(client->cmd.param[0], ",");
	do {
		tmp = srv->channel;
		if (res[0] == '#' || res[0] == '$') {
			for (; tmp &&
				strcmp(tmp->name, res) != 0; tmp = tmp->next);
			if (tmp)
				join_existing_channel(client, tmp);
			else
				join_new_channel(srv, client, res);
		}
		res = strtok(NULL, ",");
	} while (res);
}

void cmd_join(server_t *srv, client_t *client)
{
	if (!client->logged)
		return;
	if (client->cmd.psize == 1)
		join_channel(srv, client);
	else if (client->cmd.psize == 1)
		add_pending(client,
			gen_rpl(ERR_NOSUCHCHANNEL, TRANSLATE_NICK(client)));
	else
		add_pending(client,
			gen_rpl(ERR_NEEDMOREPARAMS, TRANSLATE_NICK(client)));
}