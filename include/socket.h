/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#pragma once

#include <stdbool.h>
#include <netinet/in.h>

#define VALID_SOCKET(sck) ((sck) != -1)
#define SRV_NAME "localhost"

typedef struct socket_s {
	int fd;
	socklen_t size;
	uint16_t port;
	char ip[INET_ADDRSTRLEN];
	struct sockaddr s_in;
} socket_t;


//client_socket.c
bool create_client_socket(socket_t *);
bool client_connect(socket_t *);

//server_socket.c
bool create_server_socket(socket_t *sck);
bool server_accept(socket_t *, socket_t *);
bool bind_socket(int, struct sockaddr *, socklen_t);
bool listen_socket(int, int);

//socket.c
void free_socket(socket_t *);
bool create_tcp_socket(int *, int);

//tools.c
bool print_errno(const char *, int, const char *);
char *gen_rpl(const char *, ...);
