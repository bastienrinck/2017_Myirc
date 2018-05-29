/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <string.h>
#include "server.h"

static bool cli_in_channel(client_t *client, channel_t *channel)
{
	bool res = false;
	for (size_t i = 0; !res && i < channel->amount; ++i)
		res = client == channel->client[i];
	return (res);
}

static void notify_chan_users(client_t *client, channel_t *tmp, char *old)
{
	for (size_t i = 0; i < tmp->amount; ++i) {
		if (client != tmp->client[i])
			add_pending(tmp->client[i],
				str_append(RPL_NICK_NOTIFY, old, client->user,
					client->sck.ip, client->nick));
	}
}

static void notify_channels(server_t *srv, client_t *client, char *old)
{
	for (channel_t *tmp = srv->channel; tmp; tmp = tmp->next)
		if (cli_in_channel(client, tmp))
			notify_chan_users(client, tmp, old);
	add_pending(client,
		str_append(RPL_NICK_NOTIFY, old, client->user, client->sck.ip,
			client->nick));
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
	char backup[IRC_NICK_LEN] = {0};

	if (client->cmd.psize == 1) {
		if (nick_available(srv, client)) {
			memcpy(backup, client->nick, strlen(client->nick));
			memset(client->nick, 0, IRC_NICK_LEN);
			memcpy(client->nick, client->cmd.param[0],
				strlen(client->cmd.param[0]) % IRC_NICK_LEN);
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