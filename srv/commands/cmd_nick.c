/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <string.h>
#include "server.h"

bool cli_in_channel(client_t *client, channel_t *channel)
{
	bool res = false;
	for (size_t i = 0; !res && i < channel->amount; ++i)
		res = client == channel->client[i];
	return (res);
}

static void notify_channels(server_t *srv, client_t *client, char *old)
{
	for (channel_t *tmp = srv->channel; tmp; tmp = tmp->next) {
		if (cli_in_channel(client, tmp)) {
			for (size_t i = 0; i < tmp->amount; ++i) {
				if (client != tmp->client[i])
					add_pending(tmp->client[i], str_append(
						":%s!~%s@%s NICK :%s\r\n", old,
						client->user, client->sck.ip,
						client->nick));
			}
		}
	}
	add_pending(client,
		str_append(":%s!~%s@%s NICK :%s\r\n", old, client->user,
			client->sck.ip, client->nick));
}

bool nick_available(server_t *srv, client_t *client)
{
	bool ret = true;

	for (client_t *tmp = srv->list; ret && tmp; tmp = tmp->next)
		ret = strcmp(client->cmd.param[0], tmp->nick) != 0;
	return (ret);
}

void cmd_nick(server_t *srv, client_t *client)
{
	char *msg = client->cmd.psize != 1 ? ERR_NONICKNAMEGIVEN :
		ERR_NICKNAMEINUSE;
	char backup[NICK_LENGTH] = {0};

	if (client->cmd.psize == 1) {
		if (nick_available(srv, client)) {
			memcpy(backup, client->nick, strlen(client->nick));
			memset(client->nick, 0, NICK_LENGTH);
			memcpy(client->nick, client->cmd.param[0],
				strlen(client->cmd.param[0]) % NICK_LENGTH);
			if (!client->logged && client->user[0] &&
				client->nick[0])
				welcome_newcomer(client);
			else if (client->logged && client->nick[0])
				notify_channels(srv, client, backup);
			return;
		}
	}
	add_pending(client, gen_rpl(msg, TRANSLATE_NICK(client)));
}