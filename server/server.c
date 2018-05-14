/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

static int print_usage(char *bin)
{
	printf("USAGE:\t%s port\n", bin);
	return (84);
}

int main(int ac, char **av)
{
	int ret = 0;

	if (ac != 2 || strcmp(av[1], "-help") != 0)
		ret = print_usage(av[0]);
	else
		ret = myirc_server(av[1]);
}