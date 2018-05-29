/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#include <malloc.h>
#include <string.h>
#include "server.h"

void clear_cmd(cmd_t *cmd)
{
	if (cmd->param) {
		for (int i = 0; i < cmd->psize && cmd->param[i]; ++i)
			free(cmd->param[i]);
		free(cmd->param);
	}
	memset(&cmd->psize, 0, sizeof(cmd->psize));
	memset(cmd->cmd, 0, IRC_CMD_BUF);
	cmd->param = 0;
	memset(cmd->name, 0, IRC_CMD_LEN);
}

static void extract_name(cmd_t *cmd, int *idx)
{
	memset(cmd->name, 0, IRC_CMD_LEN);
	while (cmd->cmd && cmd->cmd[*idx] && cmd->cmd[*idx] != ' ')
		*idx += 1;
	if (!*idx || *idx > IRC_CMD_LEN)
		return;
	memcpy(cmd->name, cmd->cmd, (size_t)*idx);
}

static void add_param(cmd_t *cmd, int *idx, int i)
{
	if (!(i - *idx))
		return;
	cmd->param = realloc(cmd->param, sizeof(char *) * (cmd->psize + 1));
	if (cmd->param) {
		cmd->param[cmd->psize] = strndup(cmd->cmd + *idx,
			(size_t)(i - *idx));
		cmd->psize += 1;
		*idx = i;
	}
}

static void extract_params(cmd_t *cmd, int *idx, int i)
{
	if (!cmd->cmd || !cmd->cmd[i]) {
		add_param(cmd, idx, i);
		return;
	}
	if (cmd->cmd[i] == ':') {
		*idx = i + 1;
		add_param(cmd, idx, (int)strlen(cmd->cmd));
		return;
	} else if (cmd->cmd[i] == ' ') {
		add_param(cmd, idx, i);
		*idx = i + 1;
	}
	extract_params(cmd, idx, i + 1);
}

void parse_cmd(cmd_t *cmd)
{
	int idx = 0;

	extract_name(cmd, &idx);
	extract_params(cmd, &idx, idx);
	for (int i = 0; i < cmd->psize; ++i)
		printf("[%d] %s\n", i, cmd->param[i]);
}