/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#pragma once

#include "socket.h"

#define NICK_LENGTH 100
#define CMD_BUFFER 512
#define MAX_CMD_LENGTH 12
#define CHANNEL_LENGTH 200
#define CMD_NBR 10

#define TRANSLATE_NICK(cli) (((cli)->nick[0] ? (cli)->nick : "*"))

/*
 * RPL_MSG
 */
#define RPL_WELCOME "001 %s :Welcome to the Internet Relay Network."
#define RPL_AUTH "020 %s :Please authenticate."
#define RPL_LIST "322 %s %s %d :%s"
#define RPL_LISTEND "323 %s :End of LIST command."
#define RPL_TOPIC "332 %s %s :%s"
#define RPL_NAMES "353 %s = %s :%s"
#define RPL_ENDOFNAMES "366 %s %s :End of NAMES list."
#define RPL_MOTD "372 %s :Welcome on board!"
#define RPL_MOTDSTART "375 %s :Server's Message of the day:"
#define RPL_ENDOFMOTD "376 %s :End of MOTD command."

/*
 * ERR_MSG
 */
#define ERR_NOSUCHCHANNEL "403 %s :No such channel."
#define ERR_NONICKNAMEGIVEN "431 %s :No nickname given."
#define ERR_NICKNAMEINUSE "433 %s :Nickname already reserved."
#define ERR_NEEDMOREPARAMS "461 %s :Invalid parameters."
#define ERR_ALREADYREGISTERED "462 %s :Already registered."

typedef struct ring_buffer_s {
	char buffer[2 * CMD_BUFFER];
	int start;
	int end;
	int size;
} ring_buffer_t;

typedef struct pending_s {
	char *res;
	struct pending_s *next;
} pending_t;

typedef struct cmd_s {
	ring_buffer_t rbuf;
	char cmd[CMD_BUFFER];
	char name[MAX_CMD_LENGTH];
	char **param;
	int psize;
} cmd_t;

typedef struct client_s {
	socket_t sck;
	char pass[512];
	char user[512];
	char username[512];
	char nick[NICK_LENGTH];
	char buffer[CMD_BUFFER];
	cmd_t cmd;
	pending_t *pending;
	bool logged;
	struct client_s *prev;
	struct client_s *next;
} client_t;

typedef struct channel_s {
	char name[CHANNEL_LENGTH];
	char topic[512];
	client_t **client;
	size_t amount;
	struct channel_s *prev;
	struct channel_s *next;
} channel_t;

typedef struct server_s {
	client_t *list;
	channel_t *channel;
	struct pollfd *pollfd;
	size_t size;
	int nevent;
} server_t;

typedef struct ptrfct_tuple_s {
	char *cmd;
	void (*func)(server_t *, client_t *);
} ptrfct_tuple_t;

bool proceed_poll(server_t *, client_t *);
void inc_accept(server_t *);
void parse_cmd(cmd_t *);
void proceed_cmd(server_t *, size_t, bool);
void send_cmd(server_t *, size_t);
void clear_cmd(cmd_t *);
void add_pending(client_t *, char *);
void leave_channel(server_t *, client_t *, channel_t *);
void list_users(client_t *, channel_t *);
ssize_t socket_recv(client_t *);
ssize_t socket_send(client_t *);

/*
 * commands
 */
void cmd_join(server_t *, client_t *);
void cmd_list(server_t *, client_t *);
void cmd_privmsg(server_t *, client_t *);
void cmd_msg_faccept(server_t *, client_t *);
void cmd_msg_fsend(server_t *, client_t *);
void cmd_names(server_t *, client_t *);
void cmd_nick(server_t *, client_t *);
void cmd_part(server_t *, client_t *);
void cmd_server(server_t *, client_t *);
void cmd_user(server_t *, client_t *);
void cmd_pass(server_t *, client_t *);
void cmd_unknown(server_t *, client_t *);
void cmd_quit(server_t *, client_t *);
void cmd_ping(server_t *, client_t *);

/*
 * Command's tools
 */
void welcome_newcomer(client_t *);
char *str_append(const char *, ...);