/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <string.h>
#include <stdio.h>
#include "socket.h"
#include "server.h"

static ptrfct_tuple_t fcmd[] = {{"PASS", &cmd_pass}, {"NICK", &cmd_nick},
	{"USER", &cmd_user}, {"JOIN", &cmd_join}, {"LIST", &cmd_list},
	{"PART", &cmd_part}, {"QUIT", &cmd_quit}, {"NAMES", &cmd_names},
	{"PRIVMSG", &cmd_privmsg}, {"PING", &cmd_ping}};

bool retrieve_cmd(client_t *client)
{
	bool loop = false;
	int csize = 0;
	int epos = client->cmd.rbuf.end;
	int len = client->cmd.rbuf.size;
	int spos = client->cmd.rbuf.start;
	char *rbuf = client->cmd.rbuf.buffer;
	char tmp[2 * CMD_BUFFER] = {0};

	for (; !loop && spos != epos; spos = (spos + 1) % len) {
		tmp[csize] = rbuf[spos];
		csize += 1;
		loop = (rbuf[spos] == '\r' && rbuf[(spos + 1) % len] == '\n');
	}
	if (loop) {
		memset(&tmp[csize - 1], 0, 2);
		csize += 1;
		for (int i = 0; i < csize; ++i) {
			client->cmd.cmd[i % CMD_BUFFER] = tmp[i];
			rbuf[(client->cmd.rbuf.start + i) % len] = 0;
		}
		client->cmd.rbuf.start = (client->cmd.rbuf.start + csize) % len;
	}
	return (loop);
}

void send_cmd(server_t *srv, size_t k)
{
	client_t *tmp = srv->list;

	for (size_t i = 0; ++i < k + 1; tmp = tmp->next);
	socket_send(tmp);
}

void proceed_cmd(server_t *srv, size_t k, bool recv)
{
	client_t *tmp = srv->list;

	for (size_t i = 0; ++i < k + 1; tmp = tmp->next);
	if (recv && !socket_recv(tmp)) {
		cmd_quit(NULL, tmp);
		return;
	}
	while (tmp && retrieve_cmd(tmp)) {
		printf("[%s] %s\n", tmp->sck.ip, tmp->cmd.cmd);
		parse_cmd(&tmp->cmd);
		for (int i = 0; i < CMD_NBR; ++i)
			if (!strcasecmp(fcmd[i].cmd, tmp->cmd.name)) {
				fcmd[i].func(srv, tmp);
				break;
			} else if (i + 1 == CMD_NBR)
				cmd_unknown(NULL, tmp);
		clear_cmd(&tmp->cmd);
	}
}