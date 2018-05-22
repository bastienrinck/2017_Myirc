/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <stdio.h>
#include "server.h"

void cmd_list(server_t *srv, client_t *client)
{
	for (channel_t *tmp = srv->channel; tmp; tmp = tmp->next)
		printf("[%s] %zu user(s) connected\n", tmp->name, tmp->amount);
}