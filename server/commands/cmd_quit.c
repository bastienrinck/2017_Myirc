/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <stdio.h>
#include <zconf.h>
#include "server.h"

void cmd_quit(server_t *srv, client_t *client)
{
	channel_t *save;

	write(client->sck.fd, "Closing link\r\n", 14);
	if (client->prev)
		client->prev->next = client->next;
	if (client->next)
		client->next->prev = client->prev;
	printf("Channel: %p\n", srv->channel);
	for (channel_t *tmp = srv->channel; tmp;) {
		save = tmp->next;
		leave_channel(srv, client, tmp);
		//close(client->sck.fd);
		tmp = save;
		printf("Channel: %p\n", tmp);
	}
	printf("Quit\n");
}