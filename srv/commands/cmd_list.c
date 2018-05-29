/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

void cmd_list(server_t *srv, client_t *client)
{
	if (!client->logged) {
		add_pending(client, gen_rpl(ERR_NOT_REGISTERED));
		return;
	}
	for (channel_t *tmp = srv->channel; tmp; tmp = tmp->next)
		if (!client->cmd.psize || (client->cmd.psize == 1 &&
			!strcmp(client->cmd.param[0], tmp->name))) {
			add_pending(client,
				gen_rpl(RPL_LIST, TRANSLATE_NICK(client),
			tmp->name, tmp->amount, tmp->topic));
		}
	add_pending(client, gen_rpl(RPL_LISTEND, TRANSLATE_NICK(client)));
}