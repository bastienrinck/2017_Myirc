/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "socket.h"

bool print_errno(const char *fname, const int line, const char *filename)
{
	dprintf(2, "Error in %s line %d: %s: %s.\n", filename, line - 1, fname,
		strerror(errno));
	return (false);
}