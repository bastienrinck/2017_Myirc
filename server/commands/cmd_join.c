/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <malloc.h>
#include <string.h>
#include "server.h"

void print_channel(channel_t *channel)
{
	for (size_t i = 0; i < channel->amount; ++i)
		printf("[%zu] %s\n", i, channel->client[i]->nick);
	printf("\n");
}

void notify_channel(channel_t *channel, client_t *client)
{
	char *str = malloc(2048);

	sprintf(str, ":%s!%s@localhost JOIN %s", client->nick, client->user,
		channel->name);
	for (size_t i = 0; i < channel->amount; ++i)
		add_pending(channel->client[i], strdup(str));
	free(str);
}

void send_topic(channel_t *channel, client_t *client)
{
	char *str = malloc(2048);

	sprintf(str, ":localhost 332 %s %s: Just a basic channel", client->user,
		channel->name);
}

void join_new_channel(server_t *srv, client_t *client, char *name)
{
	channel_t *ptr;
	channel_t *tmp = srv->channel;

	ptr = malloc(sizeof(channel_t));
	memset(ptr, 0, sizeof(channel_t));
	memcpy(ptr->name, name, strlen(name) % CHANNEL_LENGTH);
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
	print_channel(ptr);
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
	print_channel(channel);
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
	if (client->cmd.psize == 1) {
		join_channel(srv, client, client->cmd.param[0]);
	}
}