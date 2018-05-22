/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <stdio.h>
#include "server.h"

void cmd_unknown(server_t *srv, client_t *client)
{

	printf("Unknown %s command\n", client->cmd.name);
}