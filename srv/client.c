/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <malloc.h>
#include <string.h>
#include "server.h"

void add_pending(client_t *client, char *str)
{
	pending_t *tmp = client->pending;
	pending_t *ptr = malloc(sizeof(pending_t));

	ptr->res = str;
	ptr->next = 0;
	for (; tmp && tmp->next; tmp = tmp->next);
	if (tmp)
		tmp->next = ptr;
	client->pending = (tmp) ? client->pending : ptr;
}

ssize_t socket_recv(client_t *client)
{
	char data[CMD_BUFFER];
	ssize_t ret = 0;
	int *epos = &client->cmd.rbuf.end;
	int len = client->cmd.rbuf.size;
	char *rbuf = client->cmd.rbuf.buffer;

	ret = recv(client->sck.fd, data, CMD_BUFFER, 0);
	if (ret) {
		for (int i = 0; i < ret; ++i) {
			rbuf[*epos] = data[i];
			*epos = (*epos + 1) % len;
		}
	}
	return (ret);
}

ssize_t socket_send(client_t *client)
{
	pending_t *tmp = client->pending;
	size_t len;

	if (!client->pending)
		return (0);
	len = strlen(client->pending->res);
	send(client->sck.fd, client->pending->res, len, 0);
	client->pending = client->pending->next;
	free(tmp->res);
	free(tmp);
	return (socket_send(client));
}

void inc_accept(server_t *srv)
{
	client_t *tmp = srv->list;
	client_t *client = malloc(sizeof(client_t));

	memset(client, 0, sizeof(client_t));
	client->cmd.rbuf.size = 2 * CMD_BUFFER;
	server_accept(&srv->list->sck, &client->sck);
	for (; tmp && tmp->next; tmp = tmp->next);
	srv->list = (tmp) ? srv->list : client;
	client->prev = (tmp) ? tmp : 0;
	if (tmp && tmp != client)
		tmp->next = client;
	add_pending(client, gen_rpl(RPL_AUTH, TRANSLATE_NICK(client)));
}