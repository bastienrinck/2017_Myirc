/*
** EPITECH PROJECT, 2018
** PSU_myirc_2017
** File description:
** main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

static int print_help(char *str)
{
	if (str == NULL)
		return 84;
	printf("USAGE: ./client port\n");
	return 0;
}

int main(int ac, char **av)
{
	int ret = 84;

	if (ac != 2 || (strcmp(av[1], "-help") == 0))
		ret = print_help(av[1]);
	else if (ac == 2)
		ret = client(atoi(av[1]));
	return ret;
}