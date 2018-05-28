/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <stdio.h>
#include <zconf.h>
#include <string.h>
#include <malloc.h>
#include "server.h"

static void display_quitmsg(client_t *client)
{
	char *reason;

	if (client->cmd.psize)
		reason = str_append(
			"ERROR :Closing Link: %s[~%s@%s] (\"%s\")\r\n",
			client->nick, client->user, client->sck.ip,
			client->cmd.param[0]);
	else
		reason = str_append(
			"ERROR :Closing Link: %s[~%s@%s] (\"\")\r\n",
			client->nick, client->user, client->sck.ip);
	write(client->sck.fd, reason, strlen(reason));
	free(reason);
}

void cmd_quit(server_t *srv, client_t *client)
{
	channel_t *save;

	display_quitmsg(client);
	if (client->prev)
		client->prev->next = client->next;
	if (client->next)
		client->next->prev = client->prev;
	if (srv) {
		for (channel_t *tmp = srv->channel; tmp;) {
			save = tmp->next;
			leave_channel(srv, client, tmp);
			tmp = save;
		}
	}
	close(client->sck.fd);
}