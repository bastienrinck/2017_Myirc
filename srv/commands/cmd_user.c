/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <string.h>
#include "server.h"

void welcome_newcomer(client_t *client)
{
	client->logged = true;
	add_pending(client, gen_rpl(RPL_WELCOME, client->nick));
	add_pending(client, gen_rpl(RPL_MOTDSTART, client->nick));
	add_pending(client, gen_rpl(RPL_MOTD, client->nick));
	add_pending(client, gen_rpl(RPL_ENDOFMOTD, client->nick));
}

static void user_invalid(client_t *client)
{
	char *tr = TRANSLATE_NICK(client);
	char *msg = client->logged ? ERR_ALREADYREGISTERED : ERR_NEEDMOREPARAMS;

	add_pending(client, gen_rpl(msg, tr));
}

void cmd_user(server_t *srv, client_t *client)
{
	size_t lparam;

	(void)srv;
	if (client->cmd.psize == 4 && !client->logged) {
		lparam = strlen(client->cmd.param[0]) % 512;
		memcpy(client->user, client->cmd.param[0], lparam);
		lparam = strlen(client->cmd.param[3]) % 512;
		memcpy(client->username, client->cmd.param[3], lparam);
		if (client->nick[0])
			welcome_newcomer(client);
	} else
		user_invalid(client);
}