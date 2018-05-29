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
			str_append(":%s!~%s@%s JOIN :%s\r\n", client->nick,
				client->user, client->sck.ip, channel->name));
}

void send_topic(channel_t *channel, client_t *client)
{
	add_pending(client, gen_rpl(RPL_TOPIC, client->user, channel->name,
		channel->topic));
}

void join_new_channel(server_t *srv, client_t *client, char *name)
{
	channel_t *ptr;
	channel_t *tmp = srv->channel;

	ptr = malloc(sizeof(channel_t));
	memset(ptr, 0, sizeof(channel_t));
	memcpy(ptr->name, name, strlen(name) % CHANNEL_LENGTH);
	memmove(ptr->topic, "Just a basic channel.", 21);
	for (; tmp && tmp->next; tmp = tmp->next);
	srv->channel = (srv->channel) ? srv->channel : ptr;
	ptr->next = 0;
	ptr->prev = tmp;
	if (tmp)
		tmp->next = ptr;
	ptr->client = malloc(sizeof(client_t *));
	ptr->client[0] = client;
	ptr->amount = 1;
	notify_channel(ptr, client);
	send_topic(ptr, client);
	list_users(client, ptr);
}

void join_existing_channel(client_t *client, channel_t *channel)
{
	channel->client = realloc(channel->client,
		sizeof(client_t *) * (channel->amount + 1));
	channel->client[channel->amount] = client;
	channel->amount += 1;
	notify_channel(channel, client);
	send_topic(channel, client);
	list_users(client, channel);
}

void join_channel(server_t *srv, client_t *client, char *name)
{
	channel_t *tmp = srv->channel;

	for (; tmp && strcmp(tmp->name, name) != 0; tmp = tmp->next);
	if (tmp)
		join_existing_channel(client, tmp);
	else
		join_new_channel(srv, client, name);
}

void cmd_join(server_t *srv, client_t *client)
{
	if (!client->logged)
		return;
	if (client->cmd.psize == 1 && (client->cmd.param[0][0] == '#' ||
		client->cmd.param[0][0] == '$'))
		join_channel(srv, client, client->cmd.param[0]);
	else if (client->cmd.psize == 1)
		add_pending(client,
			gen_rpl(ERR_NOSUCHCHANNEL, TRANSLATE_NICK(client)));
	else
		add_pending(client,
			gen_rpl(ERR_NEEDMOREPARAMS, TRANSLATE_NICK(client)));
}