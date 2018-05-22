/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <malloc.h>
#include <string.h>
#include "server.h"

void add_pending(client_t *client, char *str) {
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
	bool loop = true;
	char *c1, *c2;
	ssize_t ret = 0;

	for (ssize_t tmp = 1; tmp && loop;) {
		c1 = client->cmd.cmd + ret % CMD_BUFFER;
		tmp = recv(client->sck.fd, c1, 1, 0);
		ret += tmp;
		c1 = &client->cmd.cmd[ret % 512 - 2];
		c2 = &client->cmd.cmd[ret % 512 - 1];
		loop = !(*c1 == '\r' && *c2 == '\n');
		*c1 = (char)(loop ? *c1 : 0);
		*c2 = (char)(loop ? *c2 : 0);
	}
	printf("Receiving [%s] to %s\n", client->cmd.cmd, client->nick);
	return (ret);
}

ssize_t socket_send(client_t *client)
{
	pending_t *tmp = client->pending;
	size_t len;
	ssize_t res;

	if (!client->pending)
		return (0);
	len = strlen(client->pending->res);
	printf("Sending [%s] to %s\n", client->pending->res, client->nick);
	res = send(client->sck.fd, client->pending->res, len, 0);
	res += send(client->sck.fd, "\r\n", 2, 0);
	client->pending = client->pending->next;
	free(tmp->res);
	free(tmp);
	return (res);
}

void inc_accept(server_t *srv)
{
	client_t *tmp = srv->list;
	client_t *client = malloc(sizeof(client_t));

	memset(client, 0, sizeof(client_t));
	server_accept(&srv->list->sck, &client->sck);
	for (; tmp && tmp->next; tmp = tmp->next);
	srv->list = (tmp) ? srv->list : client;
	client->prev = (tmp) ? tmp : 0;
	if (tmp && tmp != client)
		tmp->next = client;
}