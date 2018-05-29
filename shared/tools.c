/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <malloc.h>
#include "socket.h"

static char *add_srvname(char *response, ...) {
	char *str;
	va_list ap;

	va_start(ap, response);
	vasprintf(&str, ":%s %s\r\n", ap);
	va_end(ap);
	free(response);
	return (str);
}

char *gen_rpl(const char *fmt, ...) {
	char *str;
	va_list ap;

	va_start(ap, fmt);
	vasprintf(&str, fmt, ap);
	va_end(ap);
	return (add_srvname(str, SRV_NAME, str));
}

char *str_append(const char *fmt, ...) {
	char *str;
	va_list ap;

	va_start(ap, fmt);
	vasprintf(&str, fmt, ap);
	va_end(ap);
	return (str);
}

bool print_errno(const char *fname, const int line, const char *filename)
{
	dprintf(2, "Error in %s line %d: %s: %s.\n", filename, line - 1, fname,
		strerror(errno));
	return (false);
}