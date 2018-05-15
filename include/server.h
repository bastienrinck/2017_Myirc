/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
** Created by rectoria
*/

#pragma once

int main(int ac, char **av)
{
	if (!ac != 2) {
		dprintf(2, "Usage: %s:\t[PORT]\n", av[0]);
		return (0);
	}
}