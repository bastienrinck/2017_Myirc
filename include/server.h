/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#pragma once

#include "socket.h"

#define TRANSLATE_NICK(cli) (((cli)->nick[0] ? (cli)->nick : "*"))


//Special replies
#define RPL_CHAN_QUIT ":%s!~%s@%s PART %s :%s\r\n"
#define RPL_CHAN_JOIN ":%s!~%s@%s JOIN :%s\r\n"
#define RPL_NICK_NOTIFY ":%s!~%s@%s NICK :%s\r\n"

//RPL_MSG
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

//ERR_MSG
#define ERR_NOT_REGISTERED "451 * :You have not registered."
#define ERR_NOSUCHCHANNEL "403 %s :No such channel."
#define ERR_NONICKNAMEGIVEN "431 %s :No nickname given."
#define ERR_NICKNAMEINUSE "433 %s :Nickname already reserved."
#define ERR_NEEDMOREPARAMS "461 %s :Invalid parameters."
#define ERR_PARTMOREPARAMS "461 %s PART :Invalid parameters."
#define ERR_ALREADYREGISTERED "462 %s :Already registered."

#define IRC_NICK_LEN 100
#define IRC_CMD_BUF 512
#define IRC_CMD_LEN 12
#define IRC_CHANNEL_LEN 200
#define IRC_NCMD 10

typedef struct ring_buffer_s {
	char buffer[2 * IRC_CMD_BUF];
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
	char cmd[IRC_CMD_BUF];
	char name[IRC_CMD_LEN];
	char **param;
	int psize;
} cmd_t;

typedef struct client_s {
	socket_t sck;
	char pass[512];
	char user[512];
	char username[512];
	char nick[IRC_NICK_LEN];
	char buffer[IRC_CMD_BUF];
	cmd_t cmd;
	pending_t *pending;
	bool logged;
	struct client_s *prev;
	struct client_s *next;
} client_t;

typedef struct channel_s {
	char name[IRC_CHANNEL_LEN];
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

//commands
void cmd_join(server_t *, client_t *);
void cmd_list(server_t *, client_t *);
void cmd_privmsg(server_t *, client_t *);
void cmd_names(server_t *, client_t *);
void cmd_nick(server_t *, client_t *);
void cmd_part(server_t *, client_t *);
void cmd_user(server_t *, client_t *);
void cmd_pass(server_t *, client_t *);
void cmd_unknown(server_t *, client_t *);
void cmd_quit(server_t *, client_t *);
void cmd_ping(server_t *, client_t *);

//Command's tools
char *str_append(const char *, ...);
void welcome_newcomer(client_t *);
void notify_channel(channel_t *, client_t *);
void send_topic(channel_t *, client_t *);
void join_existing_channel(client_t *, channel_t *);
void join_new_channel(server_t *, client_t *, char *);