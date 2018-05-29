/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <malloc.h>
#include <string.h>
#include "server.h"

void join_new_channel(server_t *srv, client_t *client, char *name)
{
	channel_t *ptr;
	channel_t *tmp = srv->channel;

	ptr = malloc(sizeof(channel_t));
	memset(ptr, 0, sizeof(channel_t));
	memcpy(ptr->name, name, strlen(name) % IRC_CHANNEL_LEN);
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