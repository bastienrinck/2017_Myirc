/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <stdio.h>
#include "server.h"

void cmd_quit(server_t *srv, client_t *client)
{
	channel_t *save;

	if (client->prev)
		client->prev->next = client->next;
	if (client->next)
		client->next->prev = client->prev;
	for (channel_t *tmp = srv->channel; tmp;) {
		save = tmp->next;
		leave_channel(srv, client, tmp);
		tmp = save;
	}
	printf("Leaving\n");
}