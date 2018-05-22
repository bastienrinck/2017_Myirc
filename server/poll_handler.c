/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <zconf.h>
#include <malloc.h>
#include <poll.h>
#include "server.h"

size_t client_linkedllen(client_t *client)
{
	size_t size = (size_t)(client != 0);

	for (client_t *temp = client; temp && temp->next; temp = temp->next)
		size += 1;
	return (size);
}

void *build_pollfd(server_t *srv)
{
	srv->size = client_linkedllen(srv->list);
	client_t *tmp = srv->list;

	srv->pollfd = calloc(srv->size, sizeof(struct pollfd));
	for (size_t i = 0; i < srv->size; ++i) {
		srv->pollfd[i].fd = tmp->sck.fd;
		srv->pollfd[i].events = (short)(tmp->pending ? POLLOUT : POLLIN);
		tmp = tmp->next;
	}
}

void apply_revent(server_t *srv)
{
	for (size_t k = 0; k < srv->size; ++k) {
		if (!k && srv->pollfd[k].revents & POLLIN) {
			inc_accept(srv);
			continue;
		}
		if (srv->pollfd[k].revents & POLLIN)
			proceed_cmd(srv, k);
		if (srv->pollfd[k].revents & POLLOUT)
			send_cmd(srv, k);
	}
}

bool proceed_poll(server_t *srv, client_t *client)
{
	printf("Processing\n");
	srv->list = client;
	build_pollfd(srv);
	srv->nevent = poll(srv->pollfd, srv->size, -1);
	apply_revent(srv);
	free(srv->pollfd);
}