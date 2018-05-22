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
	{"PART", &cmd_part}, {"QUIT", &cmd_quit}, {"NAMES", &cmd_names}, {"PRIVMSG", &cmd_privmsg}};

void send_cmd(server_t *srv, size_t k)
{
	client_t *tmp = srv->list;

	for (size_t i = 0; ++i < k + 1; tmp = tmp->next);
	socket_send(tmp);
}

void proceed_cmd(server_t *srv, size_t k)
{
	client_t *tmp = srv->list;

	for (size_t i = 0; ++i < k + 1; tmp = tmp->next);
	if (!socket_recv(tmp)) {
		cmd_quit(NULL, tmp);
		return;
	}
	printf("[%s] %s\n", tmp->sck.ip, tmp->cmd.cmd);
	parse_cmd(&tmp->cmd);
	for (int i = 0; i < CMD_NBR; ++i)
		if (!strcmp(fcmd[i].cmd, tmp->cmd.name)) {
			fcmd[i].func(srv, tmp);
			break;
		} else if (i + 1 == CMD_NBR)
			cmd_unknown(NULL, tmp);
	clear_cmd(&tmp->cmd);
}