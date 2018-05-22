/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#pragma once

#include "socket.h"

#define NICK_LENGTH 9
#define CMD_BUFFER 512
#define MAX_CMD_LENGTH 12
#define CHANNEL_LENGTH 200
#define CMD_NBR 9

typedef enum {
	ERR_NOSUCHNICK = 401,
	ERR_NOSUCHSERVER = 402,
	ERR_NOSUCHCHANNEL = 403,
	ERR_CANNOTSENDTOCHAN = 404,
	ERR_TOMANYCHANNELS = 405,
	ERR_WASNOSUCHNICK = 406,
	ERR_TOOMANYTARGETS = 407,
	ERR_NOORIGIN = 409,
	ERR_NORECIPIENT = 411,
	ERR_NOTEXTTOSEND = 412,
	ERR_NOTOPLEVEL = 413,
	ERR_WILDTOPLEVEL = 414,
	ERR_UNKNOWNCOMMAND = 421,
	ERR_NOMOTD = 422,
	ERR_NOADMININFO = 423,
	ERR_FILEERROR = 424,
	ERR_NONICKNAMEGIVEN = 431,
	ERR_ERRONEUSNICKNAME = 432,
	ERR_NICKNAMEINUSE = 433,
	ERR_NICKCOLLISION = 436,
	ERR_USERNOTINCHANNEL = 441,
	ERR_NOTONCHANNEL = 442,
	ERR_USERONCHANNEL = 443,
	ERR_NOLOGIN = 444,
	ERR_SUMMONDISABLED = 445,
	ERR_USERSDISABLED = 446,
	ERR_NOTREGISTERED = 451,
	ERR_NOEEDMOREPARAMS = 461,
	ERR_ALREADYREGISTERED = 462,
	ERR_NOPERMFORHOST = 463,
	ERR_PASSWDMISMATCH = 464,
	ERR_YOUREBANNEDCREEP = 465,
	ERR_KEYSET = 467,
	ERR_CHANNELISFULL = 471,
	ERR_UNKNOWNMODE = 472,
	ERR_INVITEONLYCHAN = 473,
	ERR_BANNEDFROMCHAN = 474,
	ERR_BADCHANNELKEY = 475,
	ERR_NOPRIVILEGES = 481,
	ERR_CHANOPRIVSNEEDED = 482,
	ERR_CANTKILLSERVER = 483,
	ERR_NOOPERHOST = 491,
	ERR_UMODEUNKNOWNFLAG = 501,
	ERR_USERSDONTMATCH = 502,
	RPL_NONE = 300,
	RPL_USERHOST = 302,
	RPL_ISON = 303,
	RPL_AWAY = 301,
	RPL_UNAWAY = 305,
	RPL_NOAWAY = 306,
	RPL_WHOISUSER = 311,
	RPL_WHOISSERVER = 312,
	RPL_WHOISOPERATOR = 313,
	RPL_WHOISIDLE = 317,
	RPL_ENDOFWHOIS = 318,
	RPL_WHOISCHANNELS = 319,
	RPL_WHOWASUSER = 314,
	RPL_ENDOFWHOWAS = 369,
	RPL_LISTSTART = 321,
	RPL_LIST = 322,
	RPL_LISTEND = 323,
	RPL_CHANNELMODEIS = 324,
	RPL_NOTOPIC = 331,
	RPL_TOPIC = 332,
	RPL_INVITING = 341,
	RPL_SUMMONING = 342,
	RPL_VERSION = 351,
	RPL_WHOREPLY = 352,
	RPL_ENDOFWHO = 315,
	RPL_NAMREPLY = 353,
	RPL_ENDOFNAMES = 366,
	RPL_LINKS = 364,
	RPL_ENDOFLINKS= 365,
	RPL_BANLIST = 367,
	RPL_ENDOFBANLIST = 368,
	RPL_INFO = 371,
	RPL_ENDOFINFO = 374,
	RPL_MOTDSTART = 375,
	RPL_MOTD = 372,
	RPL_ENDOFMOTD = 376,
	RPL_YOUREOPER = 381,
	RPL_REHASHING = 382,
	RPL_TIME = 391,
	RPL_USERSTART = 392,
	RPL_USERS = 393,
	RPL_ENDOFUSERS = 394,
	RPL_NOUSERS = 395,
	RPL_TRACELINK = 200,
	RPL_TRACECONNECTING = 201,
	RPL_TRACEHANDSHAKE = 202,
	RPL_TRACEUNKNOWN = 203,
	RPL_TRACEOPERATOR = 204,
	RPL_TRACEUSER = 205,
	RPL_TRACESERVER = 206,
	RPL_TRACENEWTYPE = 208,
	RPL_TRACELOG = 261,
	RPL_STATSLINKINFO = 211,
	RPL_STATSCOMMANDS = 212,
	RPL_STATSCLINE = 213,
	RPL_STATSNLINE = 214,
	RPL_STATSILINE = 215,
	RPL_STATSKLINE = 216,
	RPL_STATSYLINE = 218,
	RPL_ENDOFSTATS = 219,
	RPL_STATSLLINE = 241,
	RPL_STATSUPDATE = 242,
	RPL_STATSOLINE = 243,
	RPL_STATSHLINE = 244,
	RPL_UMODEIS = 221,
	RPL_LUSERCLIENT = 251,
	RPL_LUSEROP = 252,
	RPL_LUSERUNKNOWN = 253,
	RPL_USERCHANNELS = 254,
	RPL_LUSERME = 255,
	RPL_ADMINME = 256,
	RPL_ADMINLOC1 = 257,
	RPL_ADMINLOC2 = 258,
	RPL_ADMINEMAIL = 259,
	RPL_WELCOME = 001
} reply_code_t;

typedef struct pending_s {
	char *res;
	struct pending_s *next;
} pending_t;

typedef struct cmd_s {
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
	cmd_t cmd;
	pending_t *pending;
	bool logged;
	struct client_s *prev;
	struct client_s *next;
} client_t;

typedef struct channel_s {
	char name[CHANNEL_LENGTH];
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
void proceed_cmd(server_t *, size_t);
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